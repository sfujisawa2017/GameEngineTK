#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// CollisionNodeのメンバ関数
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetObjParent(parent);
}

/// <summary>
/// SphereNodeのメンバ関数
/// </summary>

/// <summary>
/// コンストラクタ
/// </summary>
SphereNode::SphereNode()
{
	// デフォルト半径
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	// デバッグ表示用モデルを読み込む
	m_Obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetScale(Vector3(m_LocalRadius));

	// 行列を更新
	m_Obj.Update();
}

void SphereNode::Draw()
{
	// デバッグ用モデルを描画
	m_Obj.Draw();
}

