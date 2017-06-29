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