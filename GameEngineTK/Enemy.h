/**
*	@file	Enemy.h
*
*	@brief	自機
*
*	@author	藤澤　伸治
*/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"


// 自機
class Enemy
{
public:
	// パーツ
	enum PARTS
	{
		PARTS_TOWER,	// 塔
		PARTS_BASE,	// 基地
		PARTS_ENGINE_R,	// 右エンジン
		PARTS_ENGINE_L,	// 左エンジン
		PARTS_FAN,	// 換気扇
		PARTS_SCORE,	// 音符

		PARTS_NUM
	};

	// コンストラクタ
	Enemy(DirectX::Keyboard* keyboard);
	// デストラクタ
	~Enemy();
	// 初期化
	void Initialize();
	// 毎フレーム更新
	void Update();
	// 行列の計算
	void Calc();
	// 描画
	void Draw();
	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	// 当たり判定球を取得
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }
protected:
	// メンバ変数
	// ロボットの構成パーツ
	std::vector<Obj3d>	m_Obj;
	// キーボード
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// 自機のギミックに使う角度
	float m_sinAngle;
	// タイマー
	int m_Timer;
	// 目標角度
	float m_DistAngle;

	// 当たり判定球
	SphereNode m_CollisionNodeBody;
};

