#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 球の球のあたり判定
/// </summary>
/// <param name="sphereA">球A</param>
/// <param name="sphereB">球B</param>
/// <returns>true: 当たっている false: 当たっていない</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// 中心座標間の差を計算
	Vector3 sub = sphereB.Center - sphereA.Center;
	// 中心座標間の距離を計算
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	// 半径の和
	float radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	// 距離が半径の和より大きければ、当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}