#ifndef VIEW_FRUSTUM_CONFIG_H
#define VIEW_FRUSTUM_CONFIG_H

#include "../../Config/AbstractConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				using namespace PreEngine::Core::Config;
				
				class ViewFrustumConfig : public AbstractConfig
				{
				protected:
					float m_fieldOfView;

					float m_nearClippingPlane;

					float m_farClippingPlane;

				public:
					ViewFrustumConfig(Json::Value root);

					virtual ~ViewFrustumConfig();

				public:
					ViewFrustumConfig(const ViewFrustumConfig& other);

					ViewFrustumConfig& operator=(const ViewFrustumConfig& other);

				public:
					void Init();

					Json::Value GetValue() const;

				public:
					float GetFieldOfView() const;

					void SetFieldOfView(float fov);

					float GetNearClippingPlane() const;

					void SetNearClippingPlane(float ncp);

					float GetFarClippingPlane() const;

					void SetFarClippingPlane(float fcp);
				};
			}
		}
	}
}

#endif