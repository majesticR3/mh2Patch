#include "pch.h"
#include "mh2Vector.h"
#include "mh2Matrix.h"

CVector CVector::ms_xAxis(1.0f, 0.0f, 0.0f);
CVector CVector::ms_yAxis(0.0f, 1.0f, 0.0f);
CVector CVector::ms_zAxis(0.0f, 0.0f, 1.0f);
CVector CVector::ms_zero;

float CVector2D::Magnitude()
{
	return sqrtf(x * x + y * y);
}

CVector2D& CVector2D::Normalize()
{
	float mag = Magnitude();

	if (mag > VECTOR_MIN_FLOAT)
		x /= mag, y /= mag;

	return *this;
}

bool CVector2D::IsZeroLength()
{
	return VECTOR_MIN_FLOAT >= fabsf(x) && VECTOR_MIN_FLOAT >= fabsf(y);
}

CVector2D& CVector2D::operator=(CVector2D const& other)
{
	x = other.x, y = other.y;
	return *this;
}

CVector2D& CVector2D::operator+=(CVector2D const& other)
{
	x += other.x, y += other.y;
	return *this;
}

CVector2D& CVector2D::operator-=(CVector2D const& other)
{
	x -= other.x, y -= other.y;
	return *this;
}

CVector2D& CVector2D::operator*=(float scalar)
{
	x *= scalar, y *= scalar;
	return *this;
}

CVector2D& CVector2D::operator/=(float scalar)
{
	x /= scalar, y /= scalar;
	return *this;
}

CVector2D operator+(CVector2D const& lhs, CVector2D const& rhs)
{
	return CVector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

CVector2D operator-(CVector2D const& lhs, CVector2D const& rhs)
{
	return CVector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

CVector2D operator*(CVector2D const& lhs, float rhs)
{
	return CVector2D(lhs.x * rhs, lhs.y * rhs);
}

CVector2D operator*(float lhs, CVector2D const& rhs)
{
	return CVector2D(lhs + rhs.x, lhs + rhs.y);
}

CVector2D operator/(CVector2D const& lhs, float rhs)
{
	return CVector2D(lhs.x / rhs, lhs.y / rhs);
}

float CVector::Magnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

CVector& CVector::Normalize()
{
	float mag = Magnitude();

	if (mag > VECTOR_MIN_FLOAT)
		x /= mag, y /= mag, z /= mag;

	return *this;
}

bool CVector::IsZeroLength()
{
	return VECTOR_MIN_FLOAT >= fabsf(x) && VECTOR_MIN_FLOAT >= fabsf(y) &&
		VECTOR_MIN_FLOAT >= fabsf(z);
}

CVector& CVector::operator=(CVector const& other)
{
	x = other.x; y = other.y, z = other.z;
	return *this;
}

CVector& CVector::operator+=(CVector const& other)
{
	x += other.x; y += other.y, z += other.z;
	return *this;
}

CVector& CVector::operator-=(CVector const& other)
{
	x -= other.x; y -= other.y, z -= other.z;
	return *this;
}

CVector& CVector::operator*=(float scalar)
{
	x *= scalar; y *= scalar, z *= scalar;
	return *this;
}

CVector& CVector::operator/=(float scalar)
{
	x /= scalar; y /= scalar, z /= scalar;
	return *this;
}

CVector operator+(CVector const& lhs, CVector const& rhs)
{
	return CVector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

CVector operator-(CVector const& lhs, CVector const& rhs)
{
	return CVector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

CVector operator*(CVector const& lhs, float rhs)
{
	return CVector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

CVector operator*(float lhs, CVector const& rhs)
{
	return CVector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

CVector operator/(CVector const& lhs, float rhs)
{
	return CVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

void CVector::FastSum(CVector const* vec1, CVector const* vec2)
{
	x = vec1->x + vec2->x;
	y = vec1->y + vec2->y;
	z = vec1->z + vec2->z;
}

void CVector::FastTransformVector(CVector const* vec, CMatrix const* mtx)
{
	CVector result(
		vec->x * mtx->m11 + vec->y * mtx->m21 + vec->z * mtx->m31,
		vec->x * mtx->m12 + vec->y * mtx->m22 + vec->z * mtx->m32,
		vec->x * mtx->m13 + vec->y * mtx->m23 + vec->z * mtx->m33
	);

	*this = result;
}

