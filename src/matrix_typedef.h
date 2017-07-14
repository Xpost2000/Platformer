#ifndef MATRIX_TYPEDEFS_H
#define MATRIX_TYPEDEFS_H

template<typename t>
class Matrix4;

using Matrix4f = Matrix4<float>;
using Matrix4i = Matrix4<int>;
using Matrix4ui = Matrix4<unsigned int>;
using Matrix4d = Matrix4<double>;
using Matrix4b = Matrix4<bool>;

#endif