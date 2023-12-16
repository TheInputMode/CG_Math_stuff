//? I'M TEMPLATING SO HARD RIGHT NOW!!!

/// this file will contain all of the math classes and other utilities that I've been working on.
/// I'll be using these files instead of 3rd party math libraries, so I can understand the math
/// that goes into developing 3d applications better.
/// 
/// the implementations are ASS, they seem VERY VERY slow, they shouldn't be, this is a problem.
/// ...
/// will address at a later date.

#pragma once
#ifndef DENDS_MATH__HPP
#define DENDS_MATH__HPP

#include <cmath>
#include <algorithm>

// this is here if needed, but I can't think of a use for this file...
// I had a use, but I found it was easier to not be dumb about it...
//#include "d_defines.h"

// For experimental features (redefined math functions, new math functions, etc...)
#ifdef EXPERIMENTAL
#include "experimental.hpp"
#endif

// sacrifices of accuracy are fine... no?
// 
// The main point of this file at first was to find faster ways of implementing
// common math functions already in C++, but now I think I wanna implement those
// math functions anyways, even if they're slow, to better understand C++ and
// programming in general.
#ifdef USE_ALT_MATH
#include "common_math.hpp"
#endif

///~~~~~~~~~~~~~~~~ Constants/Macros/Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Useful math constants to save on typing, and to improve readability.
// Useful macros to save on typing, and/or improve readability.
// Useful Functions for conversion and other things.

///|===== Constants ============================|
// I know I could just define _MATH_DEFINES_DEFINED
// but I prefer to know "where" exactly ALL constants
// in the program are.

#ifndef PI
#define PI    3.141'592'653'589'793'238
#endif//PI
#ifndef EULER
#define EULER 2.718'281'828'459'045'235
#endif//EULER

// I don't know if I'll use these, but they're here...
#define PI_OVER_ONE_EIGHTY  0.017'453'292
#define ONE_EIGHTY_OVER_PI 57.295'779'513

///|===== Macros ===============================|
// no macros I could think of yet...


///|===== Functions ============================|
// The functions here shouldn't be to complicated.
// contemplating putting these in a namespace...

template <typename UserType = float>
inline constexpr UserType Degs_to_Rads(const UserType& degrees)
{
	return degrees * static_cast<UserType>(PI / 180);
}
template <typename UserType = float>
inline constexpr UserType Rads_to_Degs(const UserType& radians)
{
	return radians * static_cast<UserType>(180 / PI);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


///~~~~~~~~~~~~~~~~ CG Math | Main Modules ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Header files for Dends Mathematics for Computer Graphics.
// Though each file included in this file can be used separately, Including this file will include
// every class, function, constant, and macro necessary for moving points around in a 3-dimensional
// virtual space (and probably 2d as well).
// It'll also include the necessary standard headers.

#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"
#include "typedefs.hpp"


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif//_DENDS_MATH_