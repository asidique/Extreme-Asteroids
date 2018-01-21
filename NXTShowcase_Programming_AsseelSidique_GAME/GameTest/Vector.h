/* Author: ASSEEL SIDIQUE
REV: 1.5 */
#pragma once
#include <math.h>

typedef float real;

class Vector {

public:
	real x, y, z;

	/// <summary>
	///	Initializes empty vector
	/// </summary>
	Vector() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	/// <summary>
	///	Loads the Vector with components in argument.
	/// </summary>
	Vector(real x, real y, real z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector(real x, real y) {
		this->x = x;
		this->y = y;
		this->z = 0;
	}

	/// <summary>
	///	Initializes all vector components with x
	/// </summary>
	Vector(real x) {
		this->x = x;
		this->y = x;
		this->z = x;
	}

	const real getX() const {
		return x;
	}

	const real getY() const {
		return y;
	}

	const real getZ() const {
		return z;
	}

	void clear() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	/// <summary>
	///	Loads the Vector with components in argument.
	/// </summary>
	void Load(real x, real y, real z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/// <summary>
	///	Returns the magnitude of the vector.
	/// </summary>
	real GetMagnitude() {
		return sqrtf((x*x) + (y*y) + (z*z));
	}

	/// <summary>
	///	Normalizes the current vector and changes its values.
	/// </summary>
	void NormalizeThis() {
		Vector tmp;
		tmp.Load(this->x, this->y, this->z);
		x = tmp.x / tmp.GetMagnitude();
		y = tmp.y / tmp.GetMagnitude();
		z = tmp.z / tmp.GetMagnitude();
	}

	static real DotProduct(const Vector& a, const Vector& b) {
		return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
	}

	static Vector CrossProduct(const Vector& a, const Vector& b) {
		return Vector((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
	}

	static Vector Normalized(Vector& a) {
		return Vector(a.x / a.GetMagnitude(), a.y / a.GetMagnitude(), a.z / a.GetMagnitude());
	}

	static real GetDistance(Vector one, Vector two) {
		//return real((sqrt(abs(((two.x - one.x)*(two.x - one.x)) - ((two.y - one.y)*(two.y - one.y))))));
	}

	static real GetMagnitude(Vector one) {
		return sqrt(pow(one.x, 2) + pow(one.y, 2) + pow(one.z, 2));
	}


	inline void Vector::operator*=(real a) {
		Load(this->x*a, this->y*a, this->z*a);
	}

	inline void Vector::operator*=(const Vector & a) {
		Load(this->x*a.x, this->y*a.y, this->z*a.z);
	}

	inline void Vector::operator/=(const Vector & a) {
		Load(this->x / a.x, this->y / a.y, this->z / a.z);
	}

	inline void Vector::operator+=(const Vector & a) {
		Load(this->x + a.x, this->y + a.y, this->z + a.z);
	}

	inline void Vector::operator-=(const Vector & a) {
		Load(this->x - a.x, this->y - a.y, this->z - a.z);
	}

	inline const Vector operator+(const Vector & a) const {
		return Vector(this->x + a.x, this->y + a.y, this->z + a.z);
	}

	inline const Vector operator-(const Vector & a) const {
		return Vector(this->x - a.x, this->y - a.y, this->z - a.z);
	}

	inline const Vector operator*(const real a) const {
		return Vector(this->x*a, this->y*a, this->z*a);
	}

	inline const Vector operator*(const Vector & a) const {
		return Vector(this->x*a.x, this->y*a.y, this->z*a.z);
	}

	inline const Vector operator/(const real a) const {
		return Vector(this->x / a, this->y / a, this->z / a);
	}

	static Vector rotate_point(float cx, float cy, float angle, Vector p)
	{
		float s = sin(angle);
		float c = cos(angle);
		p.x -= cx;
		p.y -= cy;
		float xnew = p.x * c - p.y * s;
		float ynew = p.x * s + p.y * c;
		p.x = xnew + cx;
		p.y = ynew + cy;
		return p;
	}


};

inline const Vector operator*(real scale, const Vector & v)
{
	return Vector(v.x * scale, v.y * scale, v.z * scale);
}





