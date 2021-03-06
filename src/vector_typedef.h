#ifndef VECTOR_TYPES_H
#define VECTOR_TYPES_H
template<typename t>
class Vector3;
template<typename t>
class Vector2;
template<typename t>
class Vector4;

using iVec3 = Vector3<signed int>;
using Vec3 = Vector3<float>;
using dVec3 = Vector3<double>;
using bVec3 = Vector3<bool>;
using uiVec3 = Vector3<unsigned int>;
using cVec3 = Vector3<char>;
using ucVec3 = Vector3<unsigned char>;
using lVec3 = Vector3<long>;
using llVec3 = Vector3<long long>;

// Just making simple typedefs for most types;
using iVec2 = Vector2<signed int>;
using Vec2 = Vector2<float>;
using dVec2 = Vector2<double>;
using bVec2 = Vector2<bool>;
using uiVec2 = Vector2<unsigned int>;
using cVec2 = Vector2<signed char>;
using ucVec2 = Vector2<unsigned char>;
using lVec2 = Vector2<long>;
using llVec2 = Vector2<long long>;

using iVec4 = Vector4<signed int>;
using Vec4 = Vector4<float>;
using dVec4 = Vector4<double>;
using bVec4 = Vector4<bool>;
using uiVec4 = Vector4<unsigned int>;
using cVec4 = Vector4<signed char>;
using ucVec4 = Vector4<unsigned char>;
using lVec4 = Vector4<long>;
using llVec4 = Vector4<long long>;

#endif
