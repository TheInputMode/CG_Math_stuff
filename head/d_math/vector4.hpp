#pragma once
#ifndef DENDS_MATH__VECTOR_4__HPP
#define DENDS_MATH__VECTOR_4__HPP

///------------------------------------------------------------------------------------------------
/// vector4.hpp | Vector4 | No Inheritance
///------------------------------------------------------------------------------------------------
// 4-Dimension Vector class.
// Supports common operations on 4-dimensional vectors through member functions manipulating the 
// variables: x, y, z, and w.
template <class UserType>
struct Vector4
{
///|===== Class Variable(s) ====================|

	UserType x, y, z, w;


///|===== Constructor(s) | Destructor(s) =======|

	Vector4()
	{}
};//Vector4

#endif//DENDS_MATH__VECTOR_4__HPP