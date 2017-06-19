#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// CollisionNode�̃����o�֐�
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetObjParent(parent);
}

/// <summary>
/// SphereNode�̃����o�֐�
/// </summary>

/// <summary>
/// �R���X�g���N�^
/// </summary>
SphereNode::SphereNode()
{
	// �f�t�H���g���a
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	// �f�o�b�O�\���p���f����ǂݍ���
	m_Obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetScale(Vector3(m_LocalRadius));

	// �s����X�V
	m_Obj.Update();
}

void SphereNode::Draw()
{
	// �f�o�b�O�p���f����`��
	m_Obj.Draw();
}

