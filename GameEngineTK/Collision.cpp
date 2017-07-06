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

//--------------------------------------------------------------------------------------------
// 説　明 : 点と三角形の最近接点を計算
// 引　数 : _point	点
//			_segment	線分
//			_closest	最近接点(結果出力用）
// 戻り値 : なし
// メ　モ : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _triangle, Vector3* _closest)
{
	// _pointがP0の外側の頂点領域の中にあるかどうかチェック
	Vector3 P0_P1 = _triangle.P1 - _triangle.P0;
	Vector3 P0_P2 = _triangle.P2 - _triangle.P0;
	Vector3 P0_PT = _point - _triangle.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);
	
	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0が最近傍
		*_closest = _triangle.P0;
		return;
	}
	
	// _pointがP1の外側の頂点領域の中にあるかどうかチェック
	Vector3 P1_PT = _point - _triangle.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);
	
	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1が最近傍
		*_closest = _triangle.P1;
		return;
	}

	// _pointがP0_P1の辺領域の中にあるかどうかチェックし、あれば_pointのP0_P1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;

	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);

		*_closest = _triangle.P0 + v * P0_P1;

		return;

	}

	// _pointがP2の外側の頂点領域の中にあるかどうかチェック
	Vector3 P2_PT = _point - _triangle.P2;

	float d5 = P0_P1.Dot(P2_PT);

	float d6 = P0_P2.Dot(P2_PT);

	if (d6 >= 0.0f && d5 <= d6)
	{
		*_closest = _triangle.P2;
		return;
	}

	// _pointがP0_P2の辺領域の中にあるかどうかチェックし、あれば_pointのP0_P2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;

	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)

	{
		float w = d2 / (d2 - d6);
		*_closest = _triangle.P0 + w * P0_P2;

		return;
	}
	
	// _pointがP1_P2の辺領域の中にあるかどうかチェックし、あれば_pointのP1_P2上に対する射影を返す
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

// 三角形と点の当たり判定
bool CheckPoint2Triangle(const Vector3& _point, const Triangle& _triangle)
{
	//点と三角形は同一平面上にあるものとしています。同一平面上に無い場合は正しい結果になりません
	//線上は外とみなします。
	//ABCが三角形かどうかのチェックは省略...
	// 点0→1、 1→2、 2→0 のベクトルをそれぞれ計算
	Vector3 v01 = _triangle.P1 - _triangle.P0;
	Vector3 v12 = _triangle.P2 - _triangle.P1;
	Vector3 v20 = _triangle.P0 - _triangle.P2;

	// 三角形の各頂点から点へのベクトルをそれぞれ計算
	Vector3 v0p = _point - _triangle.P0;
	Vector3 v1p = _point - _triangle.P1;
	Vector3 v2p = _point - _triangle.P2;

	// 各辺ベクトルと、点へのベクトルの外積を計算
	Vector3 c0 = v01.Cross(v0p);
	Vector3 c1 = v12.Cross(v1p);
	Vector3 c2 = v20.Cross(v2p);

	// 内積で同じ方向かどうか調べる
	float dot01 = c0.Dot(c1);
	float dot02 = c0.Dot(c2);

	// 外積ベクトルが全て同じ方向なら、三角形の内側に点がある
	if (dot01 > 0 && dot02 > 0)
	{
		return true;
	}

	//三角形の外側に点がある
	return false;
}

//--------------------------------------------------------------------------------------------

// 説　明 : 球と法線付き三角形の当たりチェック

// 引　数 : _sphere		球

//			_tri		法線付き三角形

//			_inter		交点（省略可）

// 戻り値 : 交差しているか否か

// メ　モ : 裏面の当たりはとらない

//--------------------------------------------------------------------------------------------
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, Vector3 *_inter)
{

	Vector3 p;

	// 球の中心に対する最近接点である三角形上にある点pを見つける
	ClosestPtPoint2Triangle(_sphere.Center, _triangle, &p);
	
	Vector3 v = p - _sphere.Center;
	
	// 球と三角形が交差するのは、球の中心から点pまでの距離が球の半径よりも小さい場合
	if (v.Dot(v) <= _sphere.Radius * _sphere.Radius)
	{
		if (_inter)
		{
			*_inter = p;
		}

		return true;
	}
	
	return false;
	
	// 球と平面（三角形が乗っている平面）の当たり判定
	// 球と平面の距離を計算
	float ds = _sphere.Center.Dot(_triangle.Normal);
	float dt = _triangle.P0.Dot(_triangle.Normal);
	float dist = ds - dt;
	// 距離が半径以上なら、当たらない
	if (fabsf(dist) > _sphere.Radius)	return false;
	// 中心点を平面に射影したとき、三角形の内側にあれば、当たっている
	// 射影した座標
	Vector3 center = -dist * _triangle.Normal + _sphere.Center;
	
	// 三角形の外側になければ、当たっていない
	if (!CheckPoint2Triangle(center, _triangle))	return false;
	
	if (_inter)
	{
		*_inter = center;	// 交点をコピー
	}

	return true;
}