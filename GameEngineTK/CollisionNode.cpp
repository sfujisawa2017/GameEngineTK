#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

bool CollisionNode::m_DebugVisible = false;

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

	{// ���苅�̗v�f���v�Z
		const Matrix& worldm = m_Obj.GetWorld();

		// ���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		Vector3 right(1, 0, 0);

		// ���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// ���苅�̗v�f����
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	// �f�o�b�O�p���f����`��
	m_Obj.Draw();
}

