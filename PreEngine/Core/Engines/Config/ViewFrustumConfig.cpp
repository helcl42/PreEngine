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

				ViewFrustumConfig::ViewFrustumConfig(const ViewFrustumConfig& other)
					: AbstractConfig(other), m_fieldOfView(other.m_fieldOfView), m_nearClippingPlane(other.m_nearClippingPlane), m_farClippingPlane(other.m_farClippingPlane)
				{
				}

				ViewFrustumConfig& ViewFrustumConfig::operator=(const ViewFrustumConfig& other)
				{
					if (&other != this)
					{
						AbstractConfig::operator=(other);
						m_fieldOfView = other.m_fieldOfView; 
						m_nearClippingPlane = other.m_nearClippingPlane;
						m_farClippingPlane = other.m_farClippingPlane;
					}
					return *this;
				}

				void ViewFrustumConfig::Init()
				{	
					m_fieldOfView = (float)m_root["FieldOfView"].asDouble();
					m_nearClippingPlane = (float)m_root["NearClippingPlane"].asDouble();
					m_farClippingPlane = (float)m_root["FarClippingPlane"].asDouble();
				}

				Json::Value ViewFrustumConfig::GetValue() const
				{
					Json::Value newRoot;
					newRoot["FieldOfView"] = m_fieldOfView;
					newRoot["NearClippingPlane"] = m_nearClippingPlane;
					newRoot["FarClippingPlane"] = m_farClippingPlane;
					return newRoot;
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