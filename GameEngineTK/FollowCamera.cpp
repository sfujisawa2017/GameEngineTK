#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	: Camera(width, height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	isFPS = false;
	InitializeTPS();
}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	// キーボードの状態を取得
	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboardTracker.Update(keystate);

	// Cキーを押したら
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		// フラグを切り替え
		isFPS = !isFPS;
		if (!isFPS)
		{
			InitializeTPS();
		}
	}

	// 追従対象の座標等設定
	SetTargetPos(m_Player->GetTrans());
	SetTargetAngle(m_Player->GetRot().y);

	if (isFPS)
	{ // FPSカメラ
		Vector3 position;
		// 自機の上方0.2ｍの位置にカメラを置く
		position = m_targetPos + Vector3(0, 0.2f, 0);
		// 参照点から視点への差分
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		// 自機の後ろに回り込むための回転
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// 差分ベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		// ちょっと進んだ位置が視点
		eyepos = position + cameraV * 0.1f;
		// がっつり進んだ位置が参照点
		refpos = position + cameraV;
	}
	else 
	{ // TPSカメラ
		// 自機の上方２ｍの位置を捉える
		refpos = m_targetPos + Vector3(0, 2, 0);
		// 参照点から視点への差分
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);
		// 自機の後ろに回り込むための回転
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// 差分ベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		// 視点座標を計算
		eyepos = refpos + cameraV;
		// 視点を現在位置から補間
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		// 参照点を現在位置から補間
		refpos = m_refpos + (refpos - m_refpos) * 0.20f;
	}

	


	SetEyePos(eyepos);
	SetRefPos(refpos);

	// 基底クラスの更新
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	// 自機の上方２ｍの位置を捉える
	refpos = m_targetPos + Vector3(0, 2, 0);
	// 参照点から視点への差分
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);
	// 自機の後ろに回り込むための回転
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	// 差分ベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	// 視点座標を計算
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetPos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
