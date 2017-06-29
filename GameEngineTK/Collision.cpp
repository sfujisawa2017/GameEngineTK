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

/// <summary>
/// 3点の座標から三角形を計算（反時計回りに頂点を指定）
/// </summary>
/// <param name="_p0">点０</param>
/// <param name="_p1">点１</param>
/// <param name="_p2">点２</param>
/// <param name="_triangle">三角形（結果出力用）</param>
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	// 座標をコピー
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// 法線ベクトルを計算
	Vector3 P0_P1 = _p1 - _p0;
	Vector3 P1_P2 = _p2 - _p1;

	// 外積で２辺に直角なベクトルを算出
	_triangle->Normal = P0_P1.Cross(P1_P2);
	// 単位ベクトルにする
	_triangle->Normal.Normalize();
}