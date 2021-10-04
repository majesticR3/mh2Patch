#pragma once

#include "mh2Types.h"

constexpr float VECTOR_MIN_FLOAT = 0.00001f;

class CVector2D {
public:

	float x, y;

	CVector2D() :
		x(0.0f), y(0.0f) {}

	CVector2D(CVector2D const& other) :
		x(other.x), y(other.y) {}

	CVector2D(float x, float y) :
		x(x), y(y) {}

	~CVector2D() {}

	float      Magnitude();
	CVector2D& Normalize();
	bool       IsZeroLength();

	CVector2D& operator= (CVector2D const& other);
	CVector2D& operator+=(CVector2D const& other);
	CVector2D& operator-=(CVector2D const& other);
	CVector2D& operator*=(float scalar);
	CVector2D& operator/=(float scalar);

	friend CVector2D operator+(CVector2D const& lhs, CVector2D const& rhs);
	friend CVector2D operator-(CVector2D const& lhs, CVector2D const& rhs);
	friend CVector2D operator*(CVector2D const& lhs, float rhs);
	friend CVector2D operator*(float lhs, CVector2D const& rhs);
	friend CVector2D operator/(CVector2D const& lhs, float rhs);
};

class ALIGNED CVector {
public:	

	float x, y, z, w;

	static CVector ms_xAxis, ms_yAxis, ms_zAxis, ms_zero;

	CVector() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	CVector(CVector const& other) :
		x(other.x), y(other.y), z(other.z), w(other.w) {}

	CVector(SVector const& vector) :
		x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	CVector(float x, float y, float z) :
		x(x), y(y), z(z), w(0.0f) {}
	
	float    Magnitude();
	CVector& Normalize();
	bool     IsZeroLength();

	CVector& operator=(CVector const& other);
	CVector& operator+=(CVector const& other);
	CVector& operator-=(CVector const& other);
	CVector& operator*=(float scalar);
	CVector& operator/=(float scalar);

	friend CVector operator+(CVector const& lhs, CVector const& rhs);
	friend CVector operator-(CVector const& lhs, CVector const& rhs);
	friend CVector operator*(CVector const& lhs, float rhs);
	friend CVector operator*(float lhs, CVector const& rhs);
	friend CVector operator/(CVector const& lhs, float rhs);

	void FastSum(CVector const* vec1, CVector const* vec2);
	void FastTransformVector(CVector const* vec, class CMatrix const* mtx);
};