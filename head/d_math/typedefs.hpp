///~~~~~~~~~~~~~~~~ Standard Typedefs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// files to save on typing. Is included with "d_math.hpp".
#pragma once
#ifndef DENDS_MATH__TYPEDEFS_HPP
#define DENDS_MATH__TYPEDEFS_HPP

///|===== Vector3 ==============================|

using Vec3f = Vector3<float>;
using Vec3d = Vector3<double>;
using Vec3ld = Vector3<long double>;

using Vec3i = Vector3<int>;


///|===== Vector4 ==============================|

using Vec4f = Vector4<float>;
using Vec4d = Vector4<double>;
using Vec4ld = Vector4<long double>;

using Vec4i = Vector4<int>;


///|===== Matrix4 ==============================|

// 4 x 4 matrices

using Mat4f = Matrix4<float>;
using Mat4d = Matrix4<double>;
using Mat4ld = Matrix4<long double>;

using Mat4i = Matrix4<int>;

#endif DENDS_MATH__TYPEDEFS_HPP
