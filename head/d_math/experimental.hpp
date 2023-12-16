/*
* This file is generating conversion errors.
* Don't include when not testing.
*/

#pragma once
#ifndef DENDS_MATH__EXPERIMENTAL__HPP
#define DENDS_MATH__EXPERIMENTAL__HPP

#ifndef _CMATH_
#include <cmath>
#endif

namespace EXP { /******************************************************************************************/

// reciprocal square root from Quake III arena source
// 1 / std::sqrt(number)
float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float three_halves = 1.5f;
	x2 = number * 0.5f;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (three_halves - (x2 * y * y));
	y = y * (three_halves - (x2 * y * y));// copy this line down for better accuracy, but twice was good for Quake.
	return y;
}
// This square root function was also found within the Quake III arena source.
// found in path "*\code\game\bg_lib.c"
double sqrt(double x)
{
	float	y;
	float	delta;
	float	maxError;
	// handle bullshit
	if (x == 0) {
		return x;
	}
	if (x < 0) {
		return (-(float)(((float)(1e+300 * 1e+300)) * 0.0F)); // what is this... just use macro NAN?
	}
	// initial guess. (y = x/2)
	y = x * 0.5f;
	// refining
	maxError = x * 0.001;
	do {
		delta = (y * y) - x;
		y -= delta / (2 * y);
	} while (delta > maxError || delta < -maxError);
	return y;
}

}//namespace EXP /******************************************************************************************/

#endif//DENDS_MATH__EXPERIMENTAL__HPP