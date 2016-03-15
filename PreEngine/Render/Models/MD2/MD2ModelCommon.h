#ifndef MD2_MODEL_COMMON_H
#define MD2_MODEL_COMMON_H

#include "AnimationType.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				// md2 header
				struct AnimationHeader
				{
					int     ident;              // magic number. must be equal to "IDP2"
					int     version;            // md2 version. must be equal to 8

					int     skinwidth;          // width of the texture
					int     skinheight;         // height of the texture
					int     framesize;          // size of one frame in bytes

					int     num_skins;          // number of textures
					int     num_xyz;            // number of vertices
					int     num_st;             // number of texture coordinates
					int     num_tris;           // number of triangles
					int     num_glcmds;         // number of opengl commands
					int     num_frames;         // total number of frames

					int     ofs_skins;          // offset to skin names (64 bytes each)
					int     ofs_st;             // offset to s-t texture coordinates
					int     ofs_tris;           // offset to triangles
					int     ofs_frames;         // offset to frame data
					int     ofs_glcmds;         // offset to opengl commands
					int     ofs_end;            // offset to end of file

				};

				// md2 compressed vertex
				struct AnimationCompressedVertex
				{
					unsigned char   v[3];                // compressed vertex (x, y, z) coordinates
					unsigned char   lightnormalindex;    // index to a normal vector for the lighting

				};

				// md2 frame data (vertices are stored here)
				struct AnimationFrame
				{
					float       scale[3];       // scale values
					float       translate[3];   // translation vector
					char        name[16];       // frame name
					AnimationCompressedVertex    verts[1];       // first vertex of this frame

				};

				// animation data - first and last frame and FPS to know how fast should it run
				struct AnimationData
				{
					int		first_frame;			// first frame of the animation
					int		last_frame;				// number of frames
					int		fps;					// number of frames per second

				};

				// status animation
				struct AnimationState
				{
					int		startframe;				// first frame
					int		endframe;				// last frame
					int		fps;					// frame per second for this animation

					float	curr_time;				// current time
					float	old_time;				// old time
					float	interpol;				// percent of interpolation

					int		type;					// animation type

					int		curr_frame;				// current frame
					int		next_frame;				// next frame

				};
			}
		}
	}
}

#endif