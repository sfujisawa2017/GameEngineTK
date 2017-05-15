/// <summary>
/// 自機に追従するカメラクラス
/// </summary>
#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	// カメラと自機の距離
	static const float CAMERA_DISTANCE;
	// コンストラクタ
	FollowCamera(int width, int height);
	// 毎フレーム更新
	void Update() override;

	// 追従対象座標をセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);

	// 追従対象角度をセット
	void SetTargetAngle(float targetAngle);

protected:
	// 追従対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;
	// 追従対象の角度
	float m_targetAngle;
};
