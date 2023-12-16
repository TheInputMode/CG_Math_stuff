#pragma once
#ifndef DENDS_MATH__MATRIX_4__HPP
#define DENDS_MATH__MATRIX_4__HPP

#ifndef _CMATH_
#include <cmath>
#endif

///------------------------------------------------------------------------------------------------
/// | matrix4.hpp | Matrix4 | No Inheritance
///------------------------------------------------------------------------------------------------
// Square Matrix class (4 x 4 dimensions).
// Supports common operations on 4x4 matrices through member functions. 
// Individual cells of a matrix are initialized with a value of 0 by default, but initializing with
// one number argument will assign the diagonal numbers in the matrix to that number.
template <class UserType>
struct Matrix4
{
///|===== Class Variable(s) ====================|

	UserType user_matrix[4][4];


///|===== Constructor(s) | Destructor(s) =======|

	Matrix4() :
		user_matrix{ { UserType(0) } }
	{}
	Matrix4(UserType value) :
		user_matrix{
			{UserType(value), UserType(0), UserType(0), UserType(0)},
			{UserType(0), UserType(value), UserType(0), UserType(0)},
			{UserType(0), UserType(0), UserType(value), UserType(0)},
			{UserType(0), UserType(0), UserType(0), UserType(value)}
		}
	{}
	// don't even know if this is faster, or if this is even necessary...
	// but no loop is used to assign them sooo...
	Matrix4(UserType arr[4][4])
	{
		user_matrix[0][0] = arr[0][0];
		user_matrix[0][1] = arr[0][1];
		user_matrix[0][2] = arr[0][2];
		user_matrix[0][3] = arr[0][3];

		user_matrix[1][0] = arr[1][0];
		user_matrix[1][1] = arr[1][1];
		user_matrix[1][2] = arr[1][2];
		user_matrix[1][3] = arr[1][3];

		user_matrix[2][0] = arr[2][0];
		user_matrix[2][1] = arr[2][1];
		user_matrix[2][2] = arr[2][2];
		user_matrix[2][3] = arr[2][3];

		user_matrix[3][0] = arr[3][0];
		user_matrix[3][1] = arr[3][1];
		user_matrix[3][2] = arr[3][2];
		user_matrix[3][3] = arr[3][3];
	
	}
//TODO: make this work, what I want is to write this:
/*	
	Matrix4<float> test =
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	} 
*/
//TODO: but I can't figure this out...
	Matrix4(UserType row1[4], UserType row2[4], UserType row3[4], UserType row4[4])
	{
		
	}

	~Matrix4()
	{}


///|===== Member Functions =====================|

	// Muliplies each cell of the matrix by the scalar
	// not sure why you'd want to do this, or if you'd
	// even do this normally, but though I'd add it.
	Matrix4<UserType>& matrix_scale(const UserType& scalar)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				user_matrix[i][j] *= scalar;
			}
		}
		return *this;
	}
#ifdef DENDS_MATH__VECTOR_3__HPP
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
#endif//ROWMAJOR
	}
#endif//_VECTOR_3_

	Matrix4<UserType> transpose() const
	{
		Matrix4<UserType> transposed_matrix;
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				transposed_matrix[i][j] = user_matrix[j][i];
			}
		}
		return transposed_matrix;
	}

#ifdef _IOSTREAM_
	// this function is ass for performance and should not be called.
	void print_to_console()
	{
		for (int i = 0; i < 4; i++) {
			std::cout << "[";
			for (int j = 0; j < 4; j++) {
				std::cout << user_matrix[i][j];
				if (j != 3) {
					std::cout << ", ";
				}
			}
			std::cout << "]\n";
		}
	}
#else
	void print_to_console() { return; }
#endif 

///|===== Overloaded Operators =================|

	const UserType* operator[](size_t index) const
	{
		return user_matrix[index];
	}

	UserType* operator[](size_t index)
	{
		return user_matrix[index];
	}

	Matrix4<UserType> operator*(const Matrix4<UserType>& other_matrix) const
	{
		Matrix4<UserType> temp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int ops = 0; ops < 4; ops++) {
					temp[i][j] += user_matrix[i][ops] * other_matrix[ops][j];
				}
			}
		}
		return temp;
	}
};//Matrix4

#endif//DENDS_MATH__MATRIX_4__HPP