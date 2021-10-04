#include "pch.h"
#include "mh2Matrix.h"
#include "mh2Quaternion.h"

CVector const* CMatrix::GetRight()
{
	return &right;
}

CVector const* CMatrix::GetUp()
{
	return &up;
}

CVector const* CMatrix::GetView()
{
	return &view;
}

CVector const* CMatrix::GetPos()
{
	return &pos;
}

void CMatrix::SetIdentity()
{
	m11 = 1.0f, m12 = 0.0f, m13 = 0.0f, m14 = 0.0f;
	m21 = 0.0f, m22 = 1.0f, m23 = 0.0f, m24 = 0.0f;
	m31 = 0.0f, m32 = 0.0f, m33 = 1.0f, m34 = 0.0f;
	m41 = 0.0f, m42 = 0.0f, m43 = 0.0f, m44 = 1.0f;
}

void CMatrix::SetRotation(CVector const& axis, float eulerAngle)
{
	CQuaternion quat;

	quat.Set(axis, eulerAngle);
	SetQuaternion(quat);

	m41 = 0.0f, m42 = 0.0f, m43 = 0.0f;
}

void CMatrix::SetQuaternion(CQuaternion const& quat)
{
	float tmp1, tmp2, tmp3;

	tmp1 = quat.qx * quat.qx;
	tmp2 = quat.qy * quat.qy;
	tmp3 = quat.qz * quat.qz;

	m11 = 1.0f - 2.0f * (tmp2 + tmp3);
	m22 = 1.0f - 2.0f * (tmp1 + tmp3);
	m33 = 1.0f - 2.0f * (tmp1 + tmp2);

	tmp1 = quat.qx * quat.qy;
	tmp2 = quat.qz * quat.qw;
	m12 = 2.0f * (tmp1 + tmp2);
	m21 = 2.0f * (tmp1 - tmp2);

	tmp1 = quat.qx * quat.qz;
	tmp2 = quat.qy * quat.qw;
	m13 = 2.0f * (tmp1 - tmp2);
	m31 = 2.0f * (tmp1 + tmp2);

	tmp1 = quat.qy * quat.qz;
	tmp2 = quat.qx * quat.qw;
	m23 = 2.0f * (tmp1 + tmp2);
	m32 = 2.0f * (tmp1 - tmp2);

	m14 = 0.0f, m24 = 0.0f, m34 = 0.0f, m44 = 1.0f;
}
