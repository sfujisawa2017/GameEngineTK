/// <summary>
/// �����蔻��m�[�h
/// </summary>
#pragma once

#include "Obj3d.h"
#include "Collision.h"

/// <summary>
/// �����蔻��m�[�h
/// </summary>
class CollisionNode
{
public:
	// ������
	virtual void Initialize() = 0;
	// ���t���[���X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
	// �e���Z�b�g
	void SetParent(Obj3d* parent);
	// �e����̃I�t�Z�b�g���Z�b�g
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	// �f�o�b�O�\���I�u�W�F�N�g
	Obj3d m_Obj;
	// �e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_Trans;

};

// �����蔻�苅�m�[�h
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	// ������
	void Initialize();
	// ���t���[���X�V
	void Update();
	// �`��
	void Draw();
	// ���[�J�����a���Z�b�g
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }
protected:
	// ���[�J�����a
	float m_LocalRadius;
};