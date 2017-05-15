//------------------------
// カメラを制御するクラス
//------------------------
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int width, int height);

	virtual ~Camera();

	// 更新
	virtual void Update();

	// ビュー行列を取得
	const DirectX::SimpleMath::Matrix& GetView();

	// 射影行列を取得
	const DirectX::SimpleMath::Matrix& GetProj();

	// 視点座標をセット
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);

	// 参照点座標をセット
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);

	// 上方向ベクトルをセット
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);

	// 垂直方向視野角をセット
	void SetFovY(float fovY);

	// アスペクト比をセット
	void SetAspect(float aspect);

	// ニアクリップをセット
	void SetNearClip(float nearclip);

	// ファークリップをセット
	void SetFarClip(float farclip);

protected:
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// カメラの位置（視点座標）
	DirectX::SimpleMath::Vector3 m_eyepos;
	// どこのみるのか（注視点/参照点)
	DirectX::SimpleMath::Vector3 m_refpos;
	// 上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;
	// 射影行列
	DirectX::SimpleMath::Matrix m_proj;
	// 垂直方向視野角
	float m_fovY;
	// 画面横幅と縦幅の比率（アスペクト比）
	float m_aspect;
	// 手前の表示限界距離
	float m_nearclip;
	// 奥の表示限界距離
	float m_farclip;
};
