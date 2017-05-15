#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera(int width, int height)
{
	// メンバ変数の初期化
	m_eyepos = Vector3(0, 0, 5.0f);
	m_refpos = Vector3(0, 0, 0);
	m_upvec = Vector3(0, 1, 0);

	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = (float)width / height;
	m_nearclip = 0.1f;
	m_farclip = 1000.0f;

	// ビュー行列を生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	// 射影行列を生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(
		m_fovY, m_aspect, m_nearclip, m_farclip);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	// ビュー行列を生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	// 射影行列を生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(
		m_fovY, m_aspect, m_nearclip, m_farclip);
}

const DirectX::SimpleMath::Matrix& Camera::GetView()
{
	return m_view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}

void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}

void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}

void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}
