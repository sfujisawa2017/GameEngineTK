#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ‹…‚Ì‹…‚Ì‚ ‚½‚è”»’è
/// </summary>
/// <param name="sphereA">‹…A</param>
/// <param name="sphereB">‹…B</param>
/// <returns>true: “–‚½‚Á‚Ä‚¢‚é false: “–‚½‚Á‚Ä‚¢‚È‚¢</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// ’†SÀ•WŠÔ‚Ì·‚ðŒvŽZ
	Vector3 sub = sphereB.Center - sphereA.Center;
	// ’†SÀ•WŠÔ‚Ì‹——£‚ðŒvŽZ
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	// ”¼Œa‚Ì˜a
	float radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}