#pragma once

#include "mh2Types.h"
#include "mh2Vector.h"

class CQuaternion {
private:

	float qx, qy, qz, qw;

	friend class CVector;
	friend class CMatrix;

public:

	CQuaternion() :
		qx(0.0f), qy(0.0f), qz(0.0f), qw(0.0f) {}

	CQuaternion(CQuaternion const& other) :
		qx(other.qx), qy(other.qy), qz(other.qz), qw(other.qw) {}

	CQuaternion(float qx, float qy, float qz, float qw) :
		qx(qx), qy(qy), qz(qz), qw(qw) {}

	~CQuaternion() {}

	void Set(CVector const& axis, float eulerAngle);
};