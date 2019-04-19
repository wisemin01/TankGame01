#include "DXUT.h"

#include <random>

void D3DXVec3Multiply(D3DXVECTOR3 * pOut, CONST D3DXVECTOR3 * p1, CONST D3DXVECTOR3 * p2)
{
	pOut->x = p1->x * p2->x;
	pOut->y = p1->y * p2->y;
	pOut->z = p1->z * p2->z;
}

int RandomNumber(int min, int max)
{
	random_device rn;

	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}

float FRandomNumber(float min, float max)
{
	random_device rn;

	mt19937_64 rnd(rn());

	uniform_real_distribution<float> range(min, max);

	return range(rnd);
}

bool IntersectPointInRect(const RECT * pRect, const D3DXVECTOR3 * pPt)
{
	return ( pRect->left	< pPt->x &&
			 pRect->right	> pPt->x &&
			 pRect->top		< pPt->y &&
			 pRect->bottom	> pPt->y);
}

ostream& operator <<(ostream& os, const Vector3& pos)
{
	os << "[ " << pos.x << ", " << pos.y << ", " << pos.z << " ]";

	return os;
}