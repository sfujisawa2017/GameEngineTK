/// <summary>
/// 当たり判定ノード
/// </summary>
#pragma once

#include "Obj3d.h"
#include "Collision.h"

/// <summary>
/// 当たり判定ノード
/// </summary>
class CollisionNode
{
public:
	// 初期化
	virtual void Initialize() = 0;
	// 毎フレーム更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// 親をセット
	void SetParent(Obj3d* parent);
	// 親からのオフセットをセット
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	// デバッグ表示オブジェクト
	Obj3d m_Obj;
	// 親からのオフセット
	DirectX::SimpleMath::Vector3 m_Trans;

};

// 当たり判定球ノード
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	// 初期化
	void Initialize();
	// 毎フレーム更新
	void Update();
	// 描画
	void Draw();
	// ローカル半径をセット
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }
protected:
	// ローカル半径
	float m_LocalRadius;
};