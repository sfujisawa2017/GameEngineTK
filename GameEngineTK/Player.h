/**
*	@file	Player.h
*
*	@brief	���@
*
*	@date	2015/05/08
*
*	@author	���V�@�L��
*/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"

// ���@
class Player
{
public:
	// �d�͉����x
	const float GRAVITY_ACC = 0.03f;
	// �W�����v����
	const float JUMP_SPEED_FIRST = 0.5f;
	// �W�����v�ō���
	const float JUMP_SPEED_MAX = 0.3f;
	// �p�[�c
	enum PARTS
	{
		PARTS_TOWER,	// ��
		PARTS_BASE,	// ��n
		PARTS_ENGINE_R,	// �E�G���W��
		PARTS_ENGINE_L,	// ���G���W��
		PARTS_FAN,	// ���C��
		PARTS_SCORE,	// ����

		PARTS_NUM
	};

	// �R���X�g���N�^
	Player(DirectX::Keyboard* keyboard);
	// �f�X�g���N�^
	~Player();
	// ������
	void Initialize();
	// ���t���[���X�V
	void Update();
	// �s��̌v�Z
	void Calc();
	// �`��
	void Draw();
	// �e����
	void FireBullet();
	// �e���Z�b�g
	void ResetBullet();

	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	void StartJump();
	void StartFall();
	void StopJump();
	// �����蔻�苅���擾
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }
	// �����蔻�苅���擾
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }

	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_Velocity; }
protected:
	// �����o�ϐ�
	// ���{�b�g�̍\���p�[�c
	std::vector<Obj3d>	m_Obj;
	// �L�[�{�[�h
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// ���@�̃M�~�b�N�Ɏg���p�x
	float m_sinAngle;
	// �e�̑��x
	DirectX::SimpleMath::Vector3 m_BulletVel;
	// �e�۔��˒��t���O
	bool m_FireFlag;

	// �����蔻�苅
	SphereNode m_CollisionNodeBullet;
	// �����蔻�苅
	SphereNode m_CollisionNodeBody;

	// ���x�x�N�g��
	DirectX::SimpleMath::Vector3 m_Velocity;
	// �W�����v���t���O
	bool m_isJump;
};

