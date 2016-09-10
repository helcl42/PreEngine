#ifndef TERRAIN_SCENE_NODE_H
#define TERRAIN_SCENE_NODE_H

#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Render/HeightMaps/HeightMapFactory.h>

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::HeightMaps;

		template <class RootType>
		class TerrainSceneNode : public BaseSceneNode<TerrainSceneNode<RootType>, RootType>
		{
		private:
			const int COUNT_OF_TEXTURES = 5;

			ITexture** m_textures;

			ITexture* m_grassTexture;

			ITextureFactory* m_textureFactory;

			IHeightMap* m_heightMap;

			IHeightMapFactory* m_heightMapFactory;

			IShaderProgram* m_heightMapProgram;

			IShaderProgram* m_heightMaGrasspProgram;

			std::string m_heightMapPath;

			IShaderProgram* m_normalsProgram;

			float m_minAlpha = 0.25f;

			float m_alphaMultiplier = 1.5f;

			float m_windStrength = 4.0f;

			glm::vec3 m_windDirection = glm::vec3(1.0f, 0.0f, 1.0f);

			float m_grassPatchSize = 5.0f;

			float m_minGrassLevel = 0.251f;

			float m_maxGrassLevel = 0.675f;

		public:
			TerrainSceneNode(RootType* root, std::string heightMapPath)
				: BaseSceneNode<TerrainSceneNode<RootType>, RootType>(root), m_heightMapPath(heightMapPath)
			{
				m_textures = new ITexture*[COUNT_OF_TEXTURES];

				m_textureFactory = new TextureFactory();
				m_heightMapFactory = new HeightMapFactory();
			}

			virtual ~TerrainSceneNode()
			{
				SAFE_DELETE(m_heightMapFactory);
				SAFE_DELETE(m_heightMap);
				SAFE_DELETE(m_textureFactory);

				for (int i = 0; i < COUNT_OF_TEXTURES; i++)
				{
					SAFE_DELETE(m_textures[i]);
				}
				SAFE_DELETE_ARRAY(m_textures);

				SAFE_DELETE(m_normalsProgram);
			}

		public:
			void Init()
			{
				std::string textureNames[] = { "fungus.dds", "sand_grass_02.png", "rock_2_4w.png", "sand.png", "path_2.png" };
				for (int i = 0; i < COUNT_OF_TEXTURES; i++)
				{
					m_textures[i] = m_textureFactory->CreateTexture("./TestScene/Assets/Textures/" + textureNames[i], true);
					m_textures[i]->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
				}

				std::string grassTexture = "./TestScene/Assets/Textures/grassPack.dds";
				m_grassTexture = m_textureFactory->CreateTexture(grassTexture, true);
				m_grassTexture->SetFiltering(MagnificationTextureFilterType::TEXTURE_FILTER_MAG_BILINEAR, MinificationTextureFilterType::TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/NormalsShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Normals/Normals.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::GEOMETRY_SHADER, "./TestScene/Assets/Shaders/Normals/Normals.geom.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Normals/Normals.frag.hlsl");
				m_normalsProgram = m_programBuilder->Build();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/HeightMapGrassShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Terrain/Grass.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::GEOMETRY_SHADER, "./TestScene/Assets/Shaders/Terrain/Grass.geom.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Terrain/Grass.frag.hlsl");
				m_heightMaGrasspProgram = m_programBuilder->Build();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/HeightMapShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Terrain/Terrain.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Terrain/Terrain.frag.hlsl");
				m_heightMapProgram = m_programBuilder->Build(true, false);

				m_heightMapProgram->Use();
				for (int i = 0; i < COUNT_OF_TEXTURES; i++)
				{
					std::stringstream ss;
					ss << "gSampler[" << i << "]";
					m_heightMapProgram->SetUniform(ss.str(), i);
				}

				CameraSceneNode<RootType>* camera = FindSingleByType<CameraSceneNode<RootType>>();
				m_heightMapProgram->SetUniform("eyePosition", camera->GetCamera()->GetEye());

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(COUNT_OF_TEXTURES);
				shadows->GetShadows()->SetUniformData(m_heightMapProgram, "shadows");

				m_heightMapProgram->Validate();

				m_heightMap = m_heightMapFactory->CreateHeightMap(m_heightMapPath);
				m_heightMap->Init();
				m_heightMap->SetHasGrass(true);
				m_heightMap->SetRenderScale(300.0f, 37.0f, 300.0f);
				m_heightMap->SetMinGrassLevel(m_minGrassLevel);
				m_heightMap->SetMaxGrassLevel(m_maxGrassLevel);
				m_heightMap->SetShaderProgram(m_heightMapProgram);
				m_heightMap->SetGrassShaderProgram(m_heightMaGrasspProgram);
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
				m_heightMap->Update(deltaTime);
			}

			void PreRender()
			{
			}

			void PostRender()
			{
				m_model = m_heightMap->GetScaleMatrix();
				m_normalsProgram->Use();
				m_normalsProgram->SetUniform("normalLength", m_normalLength);
				SetMatrices(m_normalsProgram);
				m_heightMap->RenderNormals();
			}

			void Render()
			{
				m_heightMapProgram->Use();

				for (int i = 0; i < COUNT_OF_TEXTURES; i++)
				{
					std::stringstream ss;
					ss << "gSampler[" << i << "]";
					m_textures[i]->Bind(i);
					m_heightMapProgram->SetUniform(ss.str(), i);
				}

				ShadowsSceneNode<RootType>* shadows = FindSingleByType<ShadowsSceneNode<RootType>>();
				shadows->GetShadows()->SetTextureUnit(COUNT_OF_TEXTURES);
				shadows->GetShadows()->SetUniformData(m_heightMapProgram, "shadows");
				shadows->GetShadows()->BindFrameBufferTexture();

				m_model = glm::mat4(1.0f);
				SetMatrices(m_heightMapProgram);

				m_heightMapProgram->SetUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

				FindSingleByType<SunSceneNode<RootType>>()->GetSunLight().SetUniformData(m_heightMapProgram, "sunLight");

				m_heightMap->Render();

				if (m_heightMap->HasGrass())
				{
					m_heightMaGrasspProgram->Use();
					m_grassTexture->Bind();
					m_model = glm::mat4(1.0);
					SetMatrices(m_heightMaGrasspProgram);
					m_heightMaGrasspProgram->SetUniform("gSampler", 0);
					m_heightMaGrasspProgram->SetUniform("alphaMin", m_minAlpha);
					m_heightMaGrasspProgram->SetUniform("alphaMultiplier", m_alphaMultiplier);
					m_heightMaGrasspProgram->SetUniform("grassPatchSize", m_grassPatchSize);
					m_heightMaGrasspProgram->SetUniform("windStrength", m_windStrength);
					m_heightMaGrasspProgram->SetUniform("windDirection", m_windDirection);
					m_heightMaGrasspProgram->SetUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
					m_heightMap->RenderGrass();
				}
			}

			void ShutDown()
			{
				for (int i = 0; i < COUNT_OF_TEXTURES; i++)
				{
					m_textures[i]->Delete();
				}

				m_heightMap->ShutDown();

				m_normalsProgram->DeleteShaders();
				m_normalsProgram->Delete();
				SAFE_DELETE(m_normalsProgram);

				m_grassTexture->Delete();
				SAFE_DELETE(m_grassTexture);			
			}

			glm::mat4 GetScaleMatrix() const
			{
				return m_heightMap->GetScaleMatrix();
			}

			float GetHeightFromRealVector(glm::vec3 position) const
			{
				return m_heightMap->GetHeightFromRealVector(position);
			}
		};
	}
}

#endif