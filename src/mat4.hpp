#ifndef MAT4_INC
#include <cmath>
#include "math_etc.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include <cstddef>

/*
 * Templated Matrix4 class.
 * Header only implementation.
 */

template<typename t>
class Matrix4{
	private:
		const Matrix4 sub(const Matrix4& other) const{
			Matrix4 nMat;
			nMat.m00 = m00 - other.m00;
			nMat.m01 = m01 - other.m01;
			nMat.m02 = m02 - other.m02;
			nMat.m03 = m03 - other.m03;


			nMat.m10 = m10 - other.m10;
			nMat.m11 = m11 - other.m11;
			nMat.m12 = m12 - other.m12;
			nMat.m13 = m13 - other.m13;

			nMat.m20 = m20 - other.m20;
			nMat.m21 = m21 - other.m21;
			nMat.m22 = m22 - other.m22;
			nMat.m23 = m23 - other.m23;

			nMat.m30 = m30 - other.m30;
			nMat.m31 = m31 - other.m31;
			nMat.m32 = m32 - other.m32;
			nMat.m33 = m33 - other.m33;
			return nMat;
		}
		const Matrix4 subSelf(const Matrix4 & other){	
			m00 -= other.m00;
			m01 -= other.m01;
			m02 -= other.m02;
			m03 -= other.m03;

			m10 -= other.m10;
			m11 -= other.m11;
			m12 -= other.m12;
			m13 -= other.m13;

			m20 -= other.m20;
			m21 -= other.m21;
			m22 -= other.m22;
			m23 -= other.m23;

			m30 -= other.m30;
			m31 -= other.m31;
			m32 -= other.m32;
			m33 -= other.m33;
			return *this;
		}

		const Matrix4 add(const Matrix4& other) const{
			Matrix4 nMat;
			nMat.m00 = m00 + other.m00;
			nMat.m01 = m01 + other.m01;
			nMat.m02 = m02 + other.m02;
			nMat.m03 = m03 + other.m03;


			nMat.m10 = m10 + other.m10;
			nMat.m11 = m11 + other.m11;
			nMat.m12 = m12 + other.m12;
			nMat.m13 = m13 + other.m13;

			nMat.m20 = m20 + other.m20;
			nMat.m21 = m21 + other.m21;
			nMat.m22 = m22 + other.m22;
			nMat.m23 = m23 + other.m23;

			nMat.m30 = m30 + other.m30;
			nMat.m31 = m31 + other.m31;
			nMat.m32 = m32 + other.m32;
			nMat.m33 = m33 + other.m33;
			return nMat;
		}
		const Matrix4 addSelf(const Matrix4 & other){	
			m00 += other.m00;
			m01 += other.m01;
			m02 += other.m02;
			m03 += other.m03;

			m10 += other.m10;
			m11 += other.m11;
			m12 += other.m12;
			m13 += other.m13;

			m20 += other.m20;
			m21 += other.m21;
			m22 += other.m22;
			m23 += other.m23;

			m30 += other.m30;
			m31 += other.m31;
			m32 += other.m32;
			m33 += other.m33;
			return *this;
		}

		const Matrix4 mul(const Matrix4& other) const{
			Matrix4 nMat;
			nMat.m00 = m00 * other.m00;
			nMat.m01 = m01 * other.m10;
			nMat.m02 = m02 * other.m20;
			nMat.m03 = m03 * other.m30;


			nMat.m10 = m10 * other.m01;
			nMat.m11 = m11 * other.m11;
			nMat.m12 = m12 * other.m21;
			nMat.m13 = m13 * other.m31;

			nMat.m20 = m20 * other.m02;
			nMat.m21 = m21 * other.m12;
			nMat.m22 = m22 * other.m22;
			nMat.m23 = m23 * other.m32;

			nMat.m30 = m30 * other.m03;
			nMat.m31 = m31 * other.m13;
			nMat.m32 = m32 * other.m23;
			nMat.m33 = m33 * other.m33;
			return nMat;
		}
		const Matrix4 mulSelf(const Matrix4 & other){	
			m00 *= other.m00;
			m01 *= other.m10;
			m02 *= other.m20;
			m03 *= other.m30;

			m10 *= other.m01;
			m11 *= other.m11;
			m12 *= other.m21;
			m13 *= other.m31;

			m20 *= other.m02;
			m21 *= other.m12;
			m22 *= other.m22;
			m23 *= other.m32;

			m30 *= other.m03;
			m31 *= other.m13;
			m32 *= other.m23;
			m33 *= other.m33;
			return *this;
		}
	public:
		const Matrix4 operator*(const Matrix4 &other){
			return mul(other);
		}
		const Matrix4 operator*=(const Matrix4 &other){
			return mulSelf(other);
		}
		const Matrix4 operator+(const Matrix4 &other){
			return add(other);
		}
		const Matrix4 operator+=(const Matrix4 &other){
			return addSelf(other);
		}
		const Matrix4 operator-(const Matrix4 &other){
			return sub(other);
		}
		const Matrix4 operator-=(const Matrix4 &other){
			return subSelf(other);
		}

		const static Matrix4 orthographic(const auto left, const auto right, const auto bottom, const auto top, const auto near = -1, const auto far = 1){
			Matrix4 mat = Matrix4::Identity();
			mat.m00 = 2 / right - left;
			mat.m11 = 2 / top - bottom;
			mat.m22 = 2 / near - far;
			mat.m03 = left+right/left-right;
			mat.m13 = bottom+top/bottom-top;
			mat.m23 = far+near/far-near;
			return mat;
		}

		const static Matrix4 perspective(const auto fov, const auto aspectRatio, const auto near = -1, const auto far = 1000){
			Matrix4 mat = Matrix4::Identity();
			t q = 1.0 / tan(toRadians(0.5*fov));
			t a = q / aspectRatio;
			t b = (near + far) / (near - far);
			t c = (2.0 * near * far) / (near - far);
			mat.d[0+0*4] = a;
			mat.d[1+1*4] = q;
			mat.d[2+2*4] = b;
			mat.d[3+2*4] = -1.0;
			mat.d[2+3*4] = c;
			return mat;
		}

		const static Matrix4 translate(const Matrix4 m, const Vector3<t> translation){
			Matrix4 mat = m;
			mat.m30 = translation.x();
			mat.m31 = translation.y();
			mat.m32 = translation.z();
			mat.m33 = m.m33;
			return mat;
		}
		const static Matrix4 scale(Matrix4 m ,const Vector3<t> scale){
			Matrix4 mat = m;
			mat.m00 = scale.x();
			mat.m11 = scale.y();
			mat.m22 = scale.z();
			mat.m33 = m.m33;
			return mat;
		}

		const static Matrix4 rotate(const Matrix4 m,const auto angle, const Vector3<t> axis){
			Matrix4 mat = m;
			t r = toRadians(angle);
			t c = cos(r);
			t s = sin(r);
			t omc = 1.0f - c;
			t x = axis.x();
			t y = axis.y();
			t z = axis.z();

			mat.d[0 + 0 * 4] = x*omc+c;
			mat.d[1 + 0 * 4] = y* x * omc+ z * s;
			mat.d[2 + 0 * 4] = x* z * omc + y * s;
			mat.d[0 + 1 * 4] = x* y * omc - z * s;
			mat.d[1 + 1 * 4] = y * omc + c;
			mat.d[2 + 1 * 4] = y*z*omc + x * s;

			mat.d[0 + 2 * 4] = x * z * omc + y * s;
			mat.d[1 + 2 * 4] = y * z * omc - x * s;
			mat.d[2 + 2 * 4] = z *omc + c;


			return mat;
		}

		Matrix4(t val){
			for(auto &element : d){
				element = val;
			}
		}

		Matrix4(){
			m00=1; m10=0; m20=0; m30=0;
			m01=0; m11=1; m21=0; m31=0;
			m02=0; m12=0; m22=1; m32=0;
			m03=0; m13=0; m23=0; m33=1;
		}
		Matrix4(const Matrix4& other) = default;
		~Matrix4() = default;
		inline static Matrix4 Identity(){
			Matrix4 mat;
			mat.m00=1; mat.m10=0; 
			mat.m01=0; mat.m11=1;
			mat.m02=0; mat.m12=0;
			mat.m03=0; mat.m13=0;


			mat.m20=0; mat.m30=0;
			mat.m21=0; mat.m31=0;
			mat.m22=1; mat.m32=0;
			mat.m23=0; mat.m33=1;

			return mat;
		}
		inline constexpr const size_t components() const { return C; }
		inline constexpr const size_t c() const { return C; }
		inline constexpr const auto index(const size_t i){ if(i < 16) return d[i]; else return 0;  }
		inline constexpr const auto data() { return d; }
		inline const auto& value_ptr() { return data; } // fix error
	private:
		static constexpr const size_t C = 16;
		union{
			struct{
				t m00;
				t m01;
				t m02;
				t m03;
				t m10;
				t m11;
				t m12;
				t m13;
				t m20;
				t m21;
				t m22;
				t m23;
				t m30;
				t m31;
				t m32;
				t m33;
			};
			t d[C];
		};
};

#endif
