#pragma once

#ifdef _THIS_FILE_IS_DEPRECATED__MATH_HPP_

#include <cmath>
#include <algorithm>

//? I'M TEMPLATING SO HARD RIGHT NOW!!!
/// also try to keep this file COMPLETELY INDEPENDENT
/// of other files, I want this file to be good enough
/// to where I can copy JUST THIS ONE FILE into ANY 
/// other project without ANY issues.

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


///|===== Macros/Functions ===============================|

// This function is only meant for use on floating-point numbers.
// While you "can" use integer types, it isn't recommended as this
// function will return '0' most of the time when integers are used.
template <typename UserType = float>
constexpr UserType Degs_to_Rads(const UserType& degrees)
{
	return degrees * static_cast<UserType>(PI / 180);
}
template <typename UserType = float>
constexpr UserType Rads_to_Degs(const UserType& radians)
{
	return radians * static_cast<UserType>(180 / PI);
}

///~~~~~~~~~~~~~~~~ Classes/Structs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Math classes that are designed primarily for operating on numbers and systems used heavily in
// Computer Graphics.


///------------------------------------------------------------------------------------------------
/// math.hpp | Vector3 | No Inheritance
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

//TODO: didn't work, delete
	Vector3<UserType> unchanging_normalize()
	{
		static Vector3<UserType> points;
		UserType len = x * x + y * y + z * z;
		if (len > 0) {
			UserType inverse_len = 1 / std::sqrt(len);
			points.x *= inverse_len;
			points.y *= inverse_len;
			points.z *= inverse_len;
		}
		return points;
	}

	UserType theta(const UserType& z_coordinate)
	{
		return std::acos(std::clamp<UserType>(z_coordinate, -1, 1));
	}

	UserType phi(const UserType& x_coordinate, const UserType& y_coordinate)
	{
		UserType p = UserType(std::atan2(y_coordinate, x_coordinate));
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

template <typename UserType>
inline UserType Spherical_Theta(const Vector3<UserType>& vec3)
{
	if (vec3.length() != 1) {
		vec3.normalize();
	}
	return std::acos(vec3.z);
}

template <typename UserType>
inline UserType Spherical_Phi(const Vector3<UserType>& vec3)
{
	UserType phi = std::atan2(vec3.y, vec3.x);
	return (phi < 0) ? phi + 2 * PI : phi;
}


///------------------------------------------------------------------------------------------------
/// math.hpp | Vector4 | Inheritance: Vector3->Vector4
///------------------------------------------------------------------------------------------------
// 4-Dimension Vector class.
// Supports common operations on 4-dimensional vectors through member functions manipulating the 
// variables: x, y, z, and w.
// This class only exists to allow multiplication of 4x4 matrices for projective tranforms, and I'm
// not even sure it'll work the way I expect. But I'll implement it anyways and figure out later.
template<class UserType>
struct Vector4 : public Vector3<UserType>
{
	UserType w;

	Vector4() :
		w(UserType(0))
	{}
};

///~~~~~~~~~~~~~~~~ Utility Functions for class Vector3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename UserType>
UserType Vector4_Length(const Vector4<UserType>& vec4)
{
	return std::sqrt(vec4.x * vec4.x + vec4.y * vec4.y + vec4.z * vec4.z);
}

template <typename UserType>
UserType Vector4_DotProduct(const Vector4<UserType>& vec4A, const Vector4<UserType>& vec4B)
{
	return vec4A.x * vec4B.x + vec4A.y * vec4B.y + vec4A.z * vec4B.z;
}

template <typename UserType>
Vector3<UserType> Vector4_CrossProduct(const Vector4<UserType>& vec4A, const Vector4<UserType>& vec4B)
{
	return Vector3<UserType>(
		vec4A.y * vec4B.z - vec4A.z * vec4B.y,
		vec4A.z * vec4B.x - vec4A.x * vec4B.z,
		vec4A.x * vec4B.y - vec4A.y * vec4B.x
	);
}

template <typename UserType>
void Vector4_Normalize(Vector3<UserType>& vec4)
{
	UserType len = vec4.x * vec4.x + vec4.y * vec4.y + vec4.z * vec4.z;
	if (len > 0) {
		UserType inverse_len = 1 / std::sqrt(len);
		vec4.x *= inverse_len;
		vec4.y *= inverse_len;
		vec4.z *= inverse_len;
	}
}

///------------------------------------------------------------------------------------------------
/// | math.hpp | SquareMatrix | No Inheritance
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

	SquareMatrix() :
		user_matrix{ { UserType(0) } }
	{
		
	}
	SquareMatrix(UserType value) :
		user_matrix{ { UserType(0) } }
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

	size_t size()
	{
		return dimensions;
	}

	Vector3<UserType> transform_w_matrix(const Vector3<UserType>& vector)
	{
#ifdef ROWMAJOR
		return Vector3<UserType>(
			vector.x * user_matrix[0][0] + vector.y * user_matrix[1][0] + vector.z * user_matrix[2][0],
			vector.x * user_matrix[0][1] + vector.y * user_matrix[1][1] + vector.z * user_matrix[2][1],
			vector.x * user_matrix[0][2] + vector.y * user_matrix[1][2] + vector.z * user_matrix[2][2]
		);
#else 
		return Vector3<UserType>(
			vector.x * user_matrix[0][0] + vector.y * user_matrix[0][1] + vector.z * user_matrix[0][2],
			vector.x * user_matrix[1][0] + vector.y * user_matrix[1][1] + vector.z * user_matrix[1][2],
			vector.x * user_matrix[2][0] + vector.y * user_matrix[2][1] + vector.z * user_matrix[2][2]
		);
#endif 
	}

	SquareMatrix<UserType, dimensions> transpose() const
	{
		SquareMatrix<UserType, dimensions> transposed_matrix;
		for (size_t i = 0; i < dimensions; i++) {
			for (size_t j = 0; j < dimensions; j++) {
				transposed_matrix[i][j] = user_matrix[j][i];
			}
		}
		return transposed_matrix;
	}

#ifdef _IOSTREAM_
	void print_to_console()
	{
		for (int i = 0; i < dimensions; i++) {
			std::cout << "[";
			for (int j = 0; j < dimensions; j++) {
				std::cout << user_matrix[i][j] << ", ";
			}
			std::cout << "]\n";
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
UserType Spherical_Theta(const UserType& z_coordinate)
{
	return std::acos(std::clamp<UserType>(z_coordinate, -1, 1));
}
template <typename UserType>
UserType Spherical_Phi(const UserType& x_coordinate, const UserType& y_coordinate)
{
	UserType p = UserType(std::atan2(y_coordinate, x_coordinate));
	return UserType((p < 0) ? p + 2 * PI : p);
}

#endif//DONTUSETHIS