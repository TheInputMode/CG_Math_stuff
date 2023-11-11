#pragma once

#include <cmath>

//? I'M TEMPLATING SO HARD RIGHT NOW!!!
/// also try to keep this file COMPLETELY INDEPENDENT
/// of other files, I want this file to be good enough
/// to where I can copy JUST THIS ONE FILE into ANY 
/// other project without ANY issues.
/// 
/// I've thought of a good idea for handling vectors and
/// matrices, but it'll require re-writing all of this,
/// which I kinda want to do anyways, but it already 
/// took a half-day to write this, so if I do it again,
/// I'll take even longer considering what I want the
/// class to be, but I believe it would be worth it...

//todo: implement a matrix class that create a matrix of
//todo: any size and can perform operations on them, it
//todo: seems like it'll be difficult, but it should be
//todo: possible...
//todo: also I figured out how to have overloaded ops
//todo: without having to include <iostream>, get it dun


///~~~~~~~~~~~~~~~~ Constants/Macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Useful math constants to save on typing, and to improve readability.
// Useful macros to save on typing, and/or improve readability.

//! THESE SHOULDN'T BE USED WHEN ADDING TO THIS FILE, THESE ARE
//! FOR USE IN OTHER FILES THAT INCLUDE THIS ONE
// Define macro before adding math.hpp if you want to use these.
// 
//#define USE_SHORTER_TYPES
//#include "math.hpp"
//
#ifdef USE_SHORTER_TYPES
using ushort  = unsigned short;
using uint    = unsigned int;
using ulong   = unsigned long;
using ull     = unsigned long long;
using ll      = long long;
using uchar   = unsigned char;
using ldouble = long double;
#endif

///|===== Constants ============================|
// I know I could just define _MATH_DEFINES_DEFINED
// but I prefer to know "where" exactly ALL constants
// in the program are.

#define PI  3.141'592'653'589'793'238
#define E   2.718'281'828'459'045'235

// this is weird, but it also seems useful.
template <typename UserType>
static constexpr UserType IDENTITY_MATRIX4[4][4] =
{
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1}
};


///|===== Macros/Functions ===============================|

// This function is only meant for use on floating-point numbers.
// While you "can" use integer types, it isn't recommended as this
// function will return '0' most of the time when integers are used.
template <typename UserType = float>
constexpr UserType degrees_to_rads(const UserType& degrees)
{
	return degrees * static_cast<UserType>(PI / 180);
}


///~~~~~~~~~~~~~~~~ Classes/Structs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Math classes that are designed primarily for operating on numbers and systems used heavily in
// Computer Graphics.

///------------------------------------------------------------------------------------------------
/// | math.hpp | Vector3 |
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


///|===== Member functions =====================|

	UserType length()
	{
		return std::sqrt(x * x + y * y + z * z);
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
			UserType inverse_len = 1 / std::sqrt(len);
			x *= inverse_len;
			y *= inverse_len;
			z *= inverse_len;
		}

		return *this;
	}


///|===== Overloaded operators =================|

#ifdef _IOSTREAM_
	template <typename OverloadType>
	friend std::ostream& operator<<(std::ostream&, const Vector3<OverloadType>&);
	template <typename OverloadType>
	friend std::istream& operator>>(std::istream&, const Vector3<OverloadType>&);
#endif 

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
};// END OF: Vector3



///~~~~~~~~~~~~~~~~ Overloaded Operators for class Vector3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifdef _IOSTREAM_
template <typename OverloadType>
std::ostream& operator<<(std::ostream& cout, const Vector3<OverloadType>& vec3)
{
	cout << "[" << vec3.x << " " << vec3.y << " " << vec3.z << "]";
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
#endif

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


///------------------------------------------------------------------------------------------------
/// | math.hpp | SquareMatrix |
///------------------------------------------------------------------------------------------------
// Square Matrix class (N x N dimensions).
// Supports common operations on square matrices through member functions. 
// Individual cells of a matrix are initialized with a value of 0 by defualt
template <class UserType, size_t dimensions>
struct SquareMatrix
{
///|===== Class Variable(s) ====================|

	UserType user_matrix[dimensions][dimensions];


///|===== Constructor(s) | Destructor(s) =======|

	SquareMatrix()
	{
		for (size_t i = 0; i < dimensions; i++) {
			for (size_t j = 0; j < dimensions; j++) {
				user_matrix[i][j] = 0;
			}
		}
	}
	SquareMatrix(UserType value)
	{
		for (size_t i = 0; i < dimensions; i++) {
			user_matrix[i][i] = value;
		}
	}
	~SquareMatrix()
	{}


///|===== Member functions =====================|

	// Muliplies each cell of the matrix by the scalar
	// not sure why you'd want to do this, or if you'd
	// even do this normally, but though I'd add it.
	SquareMatrix<UserType, dimensions>& matrix_scale(const UserType& scalar)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				user_matrix[i][j] *= scalar;
			}
		}

		return *this;
	}

	// Muliplies diagonal cells of the matrix by the scalar
	SquareMatrix<UserType, dimensions>& scale(const UserType& scalar)
	{
		for (size_t i = 0; i < dimensions; i++) {
			user_matrix[i][i] *= scalar;
		}

		return *this;
	}

	size_t size()
	{
		return dimensions;
	}

#ifdef _IOSTREAM_
	void print_to_console()
	{
		for (int i = 0; i < dimensions; i++) {
			for (int j = 0; j < dimensions; j++) {
				std::cout << user_matrix[i][j] << " ";
			}
			std::cout << '\n';
		}
	}
#else
	void print_to_console() { return; }
#endif 

///|===== Overloaded operators =================|

	const UserType* operator[](size_t index) const
	{
		return user_matrix[index];
	}

	UserType* operator[](size_t index)
	{
		return user_matrix[index];
	}

	SquareMatrix<UserType, dimensions> operator*(const SquareMatrix<UserType, dimensions>& other_matrix) const
	{
		SquareMatrix<UserType, dimensions> temp;
		for (int i = 0; i < dimensions; i++) {
			for (int j = 0; j < dimensions; j++) {
				for (int ops = 0; ops < dimensions; ops++) {
					temp[i][j] += user_matrix[i][ops] * other_matrix[ops][j];
				}
			}
		}
		return temp;
	}
};// END OF: SquareMatrix



///~~~~~~~~~~~~~~~~ Utility Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename UserType>
void cw_x_rotate4(SquareMatrix<UserType, 4>& mat4, UserType degrees)
{
	SquareMatrix<UserType, 4> x_rotate_mat;

	degrees *= degrees_to_rads(degrees);

// holy fuck my eyes!?
//TODO: FIX THIS PLEASE CAUSE IT SUCKS ASSHOLES...
//note: some more research into class designing for c++ should get this looking good ;)
	x_rotate_mat[0][0] = 1;
	x_rotate_mat[0][1] = 0;
	x_rotate_mat[0][2] = 0;
	x_rotate_mat[0][3] = 0;
	
	x_rotate_mat[1][0] = 0;
	x_rotate_mat[1][1] = static_cast<UserType>(std::cos(degrees));
	x_rotate_mat[1][2] = static_cast<UserType>(std::sin(degrees));
	x_rotate_mat[1][3] = 0;
	
	x_rotate_mat[2][0] = 0;
	x_rotate_mat[2][1] = static_cast<UserType>(-std::sin(degrees));
	x_rotate_mat[2][2] = static_cast<UserType>(std::cos(degrees));
	x_rotate_mat[2][3] = 0;
	
	x_rotate_mat[3][0] = 0;
	x_rotate_mat[3][1] = 0;
	x_rotate_mat[3][2] = 0;
	x_rotate_mat[3][3] = 1;


	//{
	//	{1,  0,                                          0,                                         0},
	//	{0,  static_cast<UserType>(std::cos(degrees)),   static_cast<UserType>(std::sin(degrees)),  0},
	//	{0,  static_cast<UserType>(-std::sin(degrees)),  static_cast<UserType>(std::cos(degrees)),  0},
	//	{0,  0,                                          0,                                         1}
	//};

	mat4 = mat4 * x_rotate_mat;
}