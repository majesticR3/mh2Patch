#include "pch.h"
#include "mh2Quaternion.h"

void CQuaternion::Set(CVector const& axis, float eulerAngle)
{
	float angleDeg = eulerAngle * fPi / 360.0f;
	float angleSin = sinf(angleDeg);

	qx = axis.x * angleSin;
	qy = axis.y * angleSin;
	qz = axis.z * angleSin;
	qw = cosf(angleDeg);
}
