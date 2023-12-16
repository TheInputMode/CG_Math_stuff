#pragma once
#ifndef DENDS_MATH__VECTOR_2__HPP
#define DENDS_MATH__VECTOR_2__HPP

#ifndef _CMATH_
#include <cmath>
#endif

///------------------------------------------------------------------------------------------------
/// vector2.hpp | Vector2 | No Inheritance
///------------------------------------------------------------------------------------------------
// 2-Dimension Vector class.
// Supports common operations on 2-dimensional vectors through member functions manipulating the 
// variables: x, and y.
template <class UserType>
struct Vector2
{
///|===== Class Variable(s) ====================|

	UserType x, y;


///|===== Constructor(s) | Destructor(s) =======|

	Vector2() :
		x(UserType(0)), y(UserType(0))
	{}

	Vector2(const UserType& ii) :
		x(ii), y(ii)
	{}

	Vector2(UserType xx, UserType yy) :
		x(xx), y(yy)
	{}

	~Vector2()
	{}


///|===== Member Functions =====================|

	UserType length()
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2<UserType>& scale_add(UserType scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}

	Vector2<UserType>& scale_mul(UserType scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	UserType dot_product(const Vector2<UserType>& vec2) const
	{
		return x * vec2.x + y * vec2.y;
	}

	Vector2<UserType>& normalize()
	{
		UserType len = x * x + y * y;
		if (len > 0) {
			UserType inverse_len = 1 / std::sqrt(len);
			x *= inverse_len;
			y *= inverse_len;
		}
		return *this;
	}


///|===== Overloaded Operators =================|

#ifdef _IOSTREAM_
	template <typename OverloadType>
	friend std::ostream& operator<<(std::ostream&, const Vector2<OverloadType>&);
	template <typename OverloadType>
	friend std::istream& operator>>(std::istream&, const Vector2<OverloadType>&);
#endif 
};//Vector2


#ifdef _IOSTREAM_
template <typename OverloadType>
std::ostream& operator<<(std::ostream& cout, const Vector2<OverloadType>& vec2)
{
	cout << "[" << vec2.x << ", " << vec2.y << "]";
	return cout;
}
template <typename OverloadType>
std::istream& operator>>(std::istream& cin, Vector2<OverloadType>& vec2)
{
	std::cout << "\nEnter Vector2 \"x\" value: ";
	cin >> vec2.x;
	std::cout << "\nEnter Vector2 \"y\" value: ";
	cin >> vec2.y;

	return cin;
}
#endif

#endif//DENDS_MATH__VECTOR_2__HPP