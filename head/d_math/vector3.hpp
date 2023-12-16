#pragma once
#ifndef DENDS_MATH__VECTOR_3__HPP
#define DENDS_MATH__VECTOR_3__HPP

#ifndef _CMATH_
#include <cmath>
#endif
#ifndef _ALGORITHM_
#include <algorithm>
#endif

///------------------------------------------------------------------------------------------------
/// vector3.hpp | Vector3 | No Inheritance
///------------------------------------------------------------------------------------------------
// 3-Dimension Vector class.
// Supports common operations on 3-dimensional vectors through member functions manipulating the 
// variables: x, y, and z.
template <class UserType>
struct Vector3
{
///|===== Class Variable(s) ====================|

	UserType x, y, z;


///|===== Constructor(s) | Destructor(s) =======|

	Vector3() :
		x(UserType(0)), y(UserType(0)), z(UserType(0))
	{}
	Vector3(const UserType& ii) :
		x(ii), y(ii), z(ii)
	{}
	Vector3(UserType xx, UserType yy, UserType zz) :
		x(xx), y(yy), z(zz)
	{}

	~Vector3()
	{}


///|===== Member Functions =====================|

	UserType length()
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3<UserType>& scale_add(UserType scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	Vector3<UserType>& scale_mul(UserType scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	UserType dot_product(const Vector3<UserType>& vec3) const
	{
		return x * vec3.x + y * vec3.y + z * vec3.z;
	}

	Vector3<UserType> cross_product(const Vector3<UserType>& vec3) const
	{
		return Vector3<UserType>(
			y * vec3.z - z * vec3.y,
			z * vec3.x - x * vec3.z,
			x * vec3.y - y * vec3.x
		);
	}

	Vector3<UserType>& normalize()
	{
		UserType len = x * x + y * y + z * z;
		if (len > 0) {
#ifdef EXPERIMENTAL 
			UserType inverse_len = EXP::Q_rsqrt(len);
#else
			UserType inverse_len = 1 / std::sqrt(len);
#endif
			x *= inverse_len;
			y *= inverse_len;
			z *= inverse_len;
		}
		return *this;
	}

	UserType theta()
	{
		return std::acos(std::clamp<UserType>(z, -1, 1));
	}

	UserType phi()
	{
		UserType p = UserType(std::atan2(y, x));
		return UserType((p < 0) ? p + 2 * PI : p);
	}

	// This function seems a little weird, but I think if I made it change the coordinates of the points
	// in this class, that might be useful, I'll have to get to actually using this class in 3d
	// rendering to find out if it will be useful though.

		// This function expects theta and phi in DEGREES, NOT RADIANS, they'll be automatically converted
		// IF you don't want that, enter third parameter as TRUE.
	Vector3<UserType> spherical_to_cartesian(const UserType& theta, const UserType& phi, bool no_convert = false)
	{
		if (no_convert) {
			return Vector3<UserType>(
				std::cos(phi) * std::sin(theta),
				std::sin(phi) * std::sin(theta),
				std::cos(theta)
			);
		}
		else {
			return Vector3<UserType>(
				std::cos(Degs_to_Rads(phi)) * std::sin(Degs_to_Rads(theta)),
				std::sin(Degs_to_Rads(phi)) * std::sin(Degs_to_Rads(theta)),
				std::cos(Degs_to_Rads(theta))
			);
		}
	}


///|===== Overloaded Operators =================|

#ifdef _IOSTREAM_
	template <typename OverloadType>
	friend std::ostream& operator<<(std::ostream&, const Vector3<OverloadType>&);
	template <typename OverloadType>
	friend std::istream& operator>>(std::istream&, const Vector3<OverloadType>&);
#endif//_IOSTREAM

	Vector3<UserType> operator=(const Vector3<UserType>& vec3)
	{
		if (this == &vec3) {
			return *this;
		}
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;
		return *this;
	}
	Vector3<UserType> operator+(const Vector3<UserType>& vec3) const
	{
		return Vector3<UserType>(x + vec3.x, y + vec3.y, z + vec3.z);
	}
	Vector3<UserType> operator-(const Vector3<UserType>& vec3) const
	{
		return Vector3<UserType>(x - vec3.x, y - vec3.y, z - vec3.z);
	}
	Vector3<UserType> operator*(const Vector3<UserType>& vec3) const
	{
		return Vector3<UserType>(x * vec3.x, y * vec3.y, z * vec3.z);
	}
};//Vector3

///~~~~~~~~~~~~~~~~ Overloaded Operators for class Vector3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifdef _IOSTREAM_
template <typename OverloadType>
std::ostream& operator<<(std::ostream& cout, const Vector3<OverloadType>& vec3)
{
	cout << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
	return cout;
}
template <typename OverloadType>
std::istream& operator>>(std::istream& cin, Vector3<OverloadType>& vec3)
{
	std::cout << "\nEnter Vector3 \"x\" value: ";
	cin >> vec3.x;
	std::cout << "\nEnter Vector3 \"y\" value: ";
	cin >> vec3.y;
	std::cout << "\nEnter Vector3 \"z\" value: ";
	cin >> vec3.z;

	return cin;
}
#endif//_IOSTREAM

///~~~~~~~~~~~~~~~~ Utility Functions for class Vector3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename UserType>
UserType Vector3_Length(const Vector3<UserType>& vec3)
{
	return std::sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
}

template <typename UserType>
UserType Vector3_DotProduct(const Vector3<UserType>& vec3A, const Vector3<UserType>& vec3B)
{
	return vec3A.x * vec3B.x + vec3A.y * vec3B.y + vec3A.z * vec3B.z;
}

template <typename UserType>
Vector3<UserType> Vector3_CrossProduct(const Vector3<UserType>& vec3A, const Vector3<UserType>& vec3B)
{
	return Vector3<UserType>(
		vec3A.y * vec3B.z - vec3A.z * vec3B.y,
		vec3A.z * vec3B.x - vec3A.x * vec3B.z,
		vec3A.x * vec3B.y - vec3A.y * vec3B.x
	);
}

template <typename UserType>
void Vector3_Normalize(Vector3<UserType>& vec3)
{
	UserType len = vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z;
	if (len > 0) {
		UserType inverse_len = 1 / std::sqrt(len);
		vec3.x *= inverse_len;
		vec3.y *= inverse_len;
		vec3.z *= inverse_len;
	}
}

template <typename UserType>
inline UserType Vector3_Spherical_Theta(const Vector3<UserType>& vec3)
{
	return std::acos(std::clamp<UserType>(vec3.z, -1, 1));
}

template <typename UserType>
inline UserType Vector3_Spherical_Phi(const Vector3<UserType>& vec3)
{
	UserType p = UserType(std::atan2(vec3.y, vec3.x));
	return UserType((p < 0) ? p + 2 * PI : p);
}

#endif//DENDS_MATH__VECTOR_3__HPP
