#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���̋��̂����蔻��
/// </summary>
/// <param name="sphereA">��A</param>
/// <param name="sphereB">��B</param>
/// <returns>true: �������Ă��� false: �������Ă��Ȃ�</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// ���S���W�Ԃ̍����v�Z
	Vector3 sub = sphereB.Center - sphereA.Center;
	// ���S���W�Ԃ̋������v�Z
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	// ���a�̘a
	float radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	// ���������a�̘a���傫����΁A�������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}

/// <summary>
/// 3�_�̍��W����O�p�`���v�Z�i�����v���ɒ��_���w��j
/// </summary>
/// <param name="_p0">�_�O</param>
/// <param name="_p1">�_�P</param>
/// <param name="_p2">�_�Q</param>
/// <param name="_triangle">�O�p�`�i���ʏo�͗p�j</param>
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	// ���W���R�s�[
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// �@���x�N�g�����v�Z
	Vector3 P0_P1 = _p1 - _p0;
	Vector3 P1_P2 = _p2 - _p1;

	// �O�ςłQ�ӂɒ��p�ȃx�N�g�����Z�o
	_triangle->Normal = P0_P1.Cross(P1_P2);
	// �P�ʃx�N�g���ɂ���
	_triangle->Normal.Normalize();
}

//--------------------------------------------------------------------------------------------
// ���@�� : �_�ƎO�p�`�̍ŋߐړ_���v�Z
// ���@�� : _point	�_
//			_segment	����
//			_closest	�ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _triangle, Vector3* _closest)
{
	// _point��P0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P0_P1 = _triangle.P1 - _triangle.P0;
	Vector3 P0_P2 = _triangle.P2 - _triangle.P0;
	Vector3 P0_PT = _point - _triangle.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);
	
	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0���ŋߖT
		*_closest = _triangle.P0;
		return;
	}
	
	// _point��P1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P1_PT = _point - _triangle.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);
	
	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1���ŋߖT
		*_closest = _triangle.P1;
		return;
	}

	// _point��P0_P1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P0_P1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;

	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);

		*_closest = _triangle.P0 + v * P0_P1;

		return;

	}

	// _point��P2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P2_PT = _point - _triangle.P2;

	float d5 = P0_P1.Dot(P2_PT);

	float d6 = P0_P2.Dot(P2_PT);

	if (d6 >= 0.0f && d5 <= d6)
	{
		*_closest = _triangle.P2;
		return;
	}

	// _point��P0_P2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P0_P2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;

	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)

	{
		float w = d2 / (d2 - d6);
		*_closest = _triangle.P0 + w * P0_P2;

		return;
	}
	
	// _point��P1_P2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P1_P2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;

	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*_closest = _triangle.P1 + w * (_triangle.P2 - _triangle.P1);
		return;
	}
	
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;

	*_closest = _triangle.P0 + P0_P1 * v + P0_P2 * w;
}

// �O�p�`�Ɠ_�̓����蔻��
bool CheckPoint2Triangle(const Vector3& _point, const Triangle& _triangle)
{
	//�_�ƎO�p�`�͓��ꕽ�ʏ�ɂ�����̂Ƃ��Ă��܂��B���ꕽ�ʏ�ɖ����ꍇ�͐��������ʂɂȂ�܂���
	//����͊O�Ƃ݂Ȃ��܂��B
	//ABC���O�p�`���ǂ����̃`�F�b�N�͏ȗ�...
	// �_0��1�A 1��2�A 2��0 �̃x�N�g�������ꂼ��v�Z
	Vector3 v01 = _triangle.P1 - _triangle.P0;
	Vector3 v12 = _triangle.P2 - _triangle.P1;
	Vector3 v20 = _triangle.P0 - _triangle.P2;

	// �O�p�`�̊e���_����_�ւ̃x�N�g�������ꂼ��v�Z
	Vector3 v0p = _point - _triangle.P0;
	Vector3 v1p = _point - _triangle.P1;
	Vector3 v2p = _point - _triangle.P2;

	// �e�Ӄx�N�g���ƁA�_�ւ̃x�N�g���̊O�ς��v�Z
	Vector3 c0 = v01.Cross(v0p);
	Vector3 c1 = v12.Cross(v1p);
	Vector3 c2 = v20.Cross(v2p);

	// ���ςœ����������ǂ������ׂ�
	float dot01 = c0.Dot(c1);
	float dot02 = c0.Dot(c2);

	// �O�σx�N�g�����S�ē��������Ȃ�A�O�p�`�̓����ɓ_������
	if (dot01 > 0 && dot02 > 0)
	{
		return true;
	}

	//�O�p�`�̊O���ɓ_������
	return false;
}

//--------------------------------------------------------------------------------------------

// ���@�� : ���Ɩ@���t���O�p�`�̓�����`�F�b�N

// ���@�� : _sphere		��

//			_tri		�@���t���O�p�`

//			_inter		��_�i�ȗ��j

// �߂�l : �������Ă��邩�ۂ�

// ���@�� : ���ʂ̓�����͂Ƃ�Ȃ�

//--------------------------------------------------------------------------------------------
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, Vector3 *_inter)
{

	Vector3 p;

	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(_sphere.Center, _triangle, &p);
	
	Vector3 v = p - _sphere.Center;
	
	// ���ƎO�p�`����������̂́A���̒��S����_p�܂ł̋��������̔��a�����������ꍇ
	if (v.Dot(v) <= _sphere.Radius * _sphere.Radius)
	{
		if (_inter)
		{
			*_inter = p;
		}

		return true;
	}
	
	return false;
	
	// ���ƕ��ʁi�O�p�`������Ă��镽�ʁj�̓����蔻��
	// ���ƕ��ʂ̋������v�Z
	float ds = _sphere.Center.Dot(_triangle.Normal);
	float dt = _triangle.P0.Dot(_triangle.Normal);
	float dist = ds - dt;
	// ���������a�ȏ�Ȃ�A������Ȃ�
	if (fabsf(dist) > _sphere.Radius)	return false;
	// ���S�_�𕽖ʂɎˉe�����Ƃ��A�O�p�`�̓����ɂ���΁A�������Ă���
	// �ˉe�������W
	Vector3 center = -dist * _triangle.Normal + _sphere.Center;
	
	// �O�p�`�̊O���ɂȂ���΁A�������Ă��Ȃ�
	if (!CheckPoint2Triangle(center, _triangle))	return false;
	
	if (_inter)
	{
		*_inter = center;	// ��_���R�s�[
	}

	return true;
}