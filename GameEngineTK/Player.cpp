//--------------------------------------------------------------------------------------
// �t�@�C����: Player.cpp
// �쐬��:
// �쐬��:
// ����:
//--------------------------------------------------------------------------------------

#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
}

Player::~Player()
{
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Player::Initialize()
{
	// ���@�p�[�c�̃��[�h
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_TOWER].LoadModel(L"Resources/tower.cmo");
	m_Obj[PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_Obj[PARTS_ENGINE_R].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_ENGINE_L].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_FAN].LoadModel(L"Resources/fan.cmo");
	m_Obj[PARTS_SCORE].LoadModel(L"Resources/score.cmo");
	// �e�q�֌W�̍\�z�i�q���ɐe���Z�b�g�j
	m_Obj[PARTS_BASE].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_SCORE].SetObjParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_ENGINE_R].SetObjParent(
		&m_Obj[PARTS_TOWER]);
	m_Obj[PARTS_ENGINE_L].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_FAN].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	// �e����̃I�t�Z�b�g�i���[�J���̍��W����j
	m_Obj[PARTS_TOWER].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_BASE].SetTranslation(
		Vector3(0, 0.7f, 0));

	m_Obj[PARTS_SCORE].SetTranslation(
		Vector3(0, 1.0f, 0));
	m_Obj[PARTS_SCORE].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_ENGINE_R].SetTranslation(
		Vector3(0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_R].SetRotation(
		Vector3(0, XMConvertToRadians(45), 0));

	m_Obj[PARTS_ENGINE_L].SetTranslation(
		Vector3(-0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_L].SetRotation(
		Vector3(0, XMConvertToRadians(-45), 0));

	m_Obj[PARTS_FAN].SetTranslation(
		Vector3(0, 0.3f, 1.0f));

	// ���˒��ł͂Ȃ�
	m_FireFlag = false;
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Player::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	// ���@�p�[�c�̃M�~�b�N
	{
		// ���@�̊p�x��ϓ�
		Vector3 angle;

		angle = m_Obj[PARTS_SCORE].GetRotation();
		m_Obj[PARTS_SCORE].SetRotation(
			angle + Vector3(0.2f, 0.1f, 0));

		// �T�C���̈����̊p�x�����񂾂񑝂���
		m_sinAngle += 0.1f;
		// �t�@���̊p�x���������肫���肷��(-1�`+1)
		float fan_angle = sinf(m_sinAngle) * 3.0f;
		/*m_Obj[PLAYER_PARTS_FAN].SetRotation(
		Vector3(0, 0, fan_angle));*/
		//m_Obj[PARTS_FAN].SetTranslation(
		//	Vector3(sinf(m_sinAngle), 0, cosf(m_sinAngle)*3.0f));
	}


	// A�L�[�������Ă����
	if (keystate.A)
	{
		// ���@�̊p�x��ϓ�
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(
			Vector3(0, angle + 0.03f, 0));
	}

	// D�L�[�������Ă����
	if (keystate.D)
	{
		// ���@�̊p�x��ϓ�
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(
			Vector3(0, angle - 0.03f, 0));
	}

	// W�L�[�������Ă����
	if (keystate.W)
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		// ��]�s��
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	// S�L�[�������Ă����
	if (keystate.S)
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, +0.1f);
		// ��]�s��
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		if (m_FireFlag)
		{
			ResetBullet();
		}
		else
		{
			FireBullet();
		}
	}

	// �e�ۂ��i�ޏ���
	if (m_FireFlag)
	{		
		// ���@�̍��W���ړ�
		Vector3 pos = m_Obj[PARTS_SCORE].GetTranslation();
		pos += m_BulletVel;
		m_Obj[PARTS_SCORE].SetTranslation(pos);
	}

	// �s��X�V
	Calc();

	//FireBullet();
}

//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}
}

void Player::FireBullet()
{
	if (m_FireFlag) return;

	// ���[���h�s����擾
	Matrix worldm = m_Obj[PARTS_SCORE].GetWorld();

	Vector3 scale;	// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

	// ���[���h�s�񂩂�e�v�f�����o��
	worldm.Decompose(scale, rotation, translation);

	// �e�q�֌W���������ăp�[�c��Ɨ�������
	m_Obj[PARTS_SCORE].SetObjParent(nullptr);
	m_Obj[PARTS_SCORE].SetScale(scale);
	m_Obj[PARTS_SCORE].SetRotationQ(rotation);
	m_Obj[PARTS_SCORE].SetTranslation(translation);

	// �e�̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.1f);
	// �e�̌����ɍ��킹�Đi�s��������]
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	m_Obj[PARTS_SCORE].SetObjParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_SCORE].SetTranslation(
		Vector3(0, 1.0f, 0));
	m_Obj[PARTS_SCORE].SetScale(
		Vector3(2, 2, 2));
	m_Obj[PARTS_SCORE].SetRotation(Vector3(0, 0, 0));

	m_FireFlag = false;

}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_Obj[0].GetWorld();
}
