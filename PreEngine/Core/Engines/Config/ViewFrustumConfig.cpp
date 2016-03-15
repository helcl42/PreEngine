#include "ViewFrustumConfig.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Engines
		{
			namespace Config
			{
				ViewFrustumConfig::ViewFrustumConfig(Json::Value root)
					: AbstractConfig(root)
				{
					Init();
				}

				ViewFrustumConfig::~ViewFrustumConfig()
				{
				}

				void ViewFrustumConfig::Init()
				{	
					m_fieldOfView = (float)m_root["FieldOfView"].asDouble();
					m_nearClippingPlane = (float)m_root["NearClippingPlane"].asDouble();
					m_farClippingPlane = (float)m_root["FarClippingPlane"].asDouble();
				}

				float ViewFrustumConfig::GetFieldOfView() const
				{
					return m_fieldOfView;
				}

				void ViewFrustumConfig::SetFieldOfView(float fov)
				{
					m_fieldOfView = fov;
				}

				float ViewFrustumConfig::GetNearClippingPlane() const
				{
					return m_nearClippingPlane;
				}

				void ViewFrustumConfig::SetNearClippingPlane(float ncp)
				{
					m_nearClippingPlane = ncp;
				}

				float ViewFrustumConfig::GetFarClippingPlane() const
				{
					return m_farClippingPlane;
				}

				void ViewFrustumConfig::SetFarClippingPlane(float fcp)
				{
					m_farClippingPlane = fcp;
				}
			}
		}
	}
}