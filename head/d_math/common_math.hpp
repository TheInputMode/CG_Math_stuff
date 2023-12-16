/*
* Standard Math function redefines
*
* PURPOSE:
*	To better understand programming and
*	mathematical techniques.
*/

#error This file isn't ready, do not include yet

#pragma once
#ifndef DENDS_MATH__COMMON_MATH__HPP
#define DENDS_MATH__COMMON_MATH__HPP

namespace dend
{
	// when I write functions to replace standard, put them here, and use them instead.
	// THEY HAVE TO BE COMPLETELY SEPARATE FROM ANY OTHER LIBRARY, AND HAVE TO BE GOOD
	// ENOUGH TO MAKE SENSE USING (I know it doesn't make sense to redefine something
	// that already works, this is for educational purposes... duh?).
	// - sin
	// - cos
	// - tan
	// - atan
	// - acos2
	// - acos
	// - sqrt
	// - division operations?+
	// etc
	
	// What the functions may look like:

	template <typename UserType>
	UserType sqrt(UserType number)
	{
		// implement this when you can
		return 0;
	}
	template <typename UserType>
	UserType sin(UserType number)
	{
		// implement this when you can
		return 0;
	}
	template <typename UserType>
	UserType cos(UserType number)
	{
		// implement this when you can
		return 0;
	}
	template <typename UserType>
	UserType tan(UserType number)
	{
		// implement this when you can
		return 0;
	}
	// ... etc.
}

#endif//_COMMON_MATH