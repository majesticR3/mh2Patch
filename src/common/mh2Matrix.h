#pragma once

#include "mh2Types.h"
#include "mh2Vector.h"

class ALIGNED CMatrix {
private:
	union {

		float m[4][4];

		struct {
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};

		struct {
			CVector right, up, view, pos;
		};
	};

	friend class CVector;
	friend class CQuaternion;

public:

	CMatrix() :
		m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f),
		m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f),
		m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f),
		m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f) {}

	CMatrix(CMatrix const& other) :
		m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14),
		m21(other.m21), m22(other.m22), m23(other.m23), m24(other.m24),
		m31(other.m31), m32(other.m32), m33(other.m33), m34(other.m34),
		m41(other.m41), m42(other.m42), m43(other.m43), m44(other.m44) {}

	~CMatrix() {}

	CVector const* GetRight();
	CVector const* GetUp();
	CVector const* GetView();
	CVector const* GetPos();

	void SetIdentity();
	void SetRotation(CVector const& axis, float eulerAngle);
	void SetQuaternion(class CQuaternion const& quat);
};