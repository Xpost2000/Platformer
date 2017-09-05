#ifndef VECTOR4D_HPP
#define VECTOR4D_HPP

#include <array>
#include <algorithm>
#include <iostream>
template<typename t>
/*
 *	Vector4D : A class that performs mathematics
 *	on a 4 dimensional vector.
 */
class Vector4{
	public:
#ifdef VEC4_GLM_TYPES
#include <glm/glm.hpp>
	Vector4(const glm::vec4 v) : X(v.x), Y(v.y), Z(v.z), W(v.w) {}
#endif
	Vector4() = default;
	Vector4(const Vector4& other) = default;
	~Vector4() = default;
	Vector4(const auto x, const auto y, const auto z, const auto w) : X(x), Y(y), Z(z), W(w){
	}
	Vector4(const auto scalar) : X(scalar), Y(scalar), Z(scalar), W(scalar){
	}	
	Vector4 (const auto d[4]) : X(d[0]), Y(d[1]), Z(d[2]), W(d[3]){}
	private:
		constexpr const static size_t C = 4;
		union{
			struct{
				t X;
				t Y;
				t Z;
				t W;
			 };
			struct{
				t R;
				t G;
				t B;
				t A;
			 };
			t d[C];
		};
		const Vector4 divide(const Vector4& other) const{
			Vector4 nVec;
			nVec.X = X / other.X;
			nVec.Y = Y / other.Y;
			nVec.Z = Z / other.Z;
			nVec.W = W / other.W;
			return nVec;
		}
		const Vector4 divideSelf(const Vector4& other){
			X /= other.X;
			Y /= other.Y;
			Z /= other.Z;
			W /= other.W;
			return *this;
		}
		const Vector4 divideScalar(const auto scalar) const {
			Vector4 nVec;	
			nVec.X = X / scalar;
			nVec.Y = Y / scalar;
			nVec.Z = Z / scalar;
			nVec.W = W / scalar;
			return nVec;
		}
		const Vector4 divideScalarSelf(const auto scalar) {
			X /= scalar;
			Y /= scalar;
			Z /= scalar;
			W /= scalar;
			return *this;
		}
		// Multiplication
		const Vector4 mul(const Vector4& other) const{
			Vector4 nVec;
			nVec.X = X * other.X;
			nVec.Y = Y *other.Y;
			nVec.Z = Z * other.Z;
			nVec.W = W * other.W;
			return nVec;
		}
		const Vector4 mulSelf(const Vector4& other) {
			X *= other.X;
			Y *= other.Y;
			Z *= other.Z;
			W *= other.W;
			return *this;
		}
		const Vector4 mulScalar(const auto scalar) const{
			Vector4 nVec;
			nVec.X = X * scalar;
			nVec.Y = Y * scalar;
			nVec.Z = Z * scalar;
			nVec.W = W * scalar;
			return nVec;
		}
		const Vector4 mulScalarSelf(const auto scalar){
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
			W *= scalar;
			return *this;
		}
		// Subtraction
		const Vector4 sub(const Vector4& other) const{
			Vector4 nVec;
			nVec.X = X - other.X;
			nVec.Y = Y - other.Y;
			nVec.Z = Z - other.Z;
			nVec.W = W - other.W;
			return nVec;
		}
		const Vector4 subSelf(const Vector4& other) {
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			W -= other.W;
			return *this;
		}
		const Vector4 subScalar(const auto scalar) const{
			Vector4 nVec;
			nVec.X = X - scalar;
			nVec.Y = Y - scalar;
			nVec.Z = Z - scalar;
			nVec.W = W - scalar;
			return nVec;
		}
		const Vector4 subScalarSelf(const auto scalar){
			X -= scalar;
			Y -= scalar;
			Z -= scalar;
			W -= scalar;
			return *this;
		}
		
		//Addition
		const Vector4 add(const Vector4& other) const{
			Vector4 nVec;
			nVec.X = X + other.X;
			nVec.Y = Y + other.Y;
			nVec.Z = Z + other.Z;
			nVec.W = W + other.W;
			return nVec;
		}
		const Vector4 addSelf(const Vector4& other) {
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			W += other.W;
			return *this;
		}
		const Vector4 addScalar(const auto scalar) const{
			Vector4 nVec;
			nVec.X = X + scalar;
			nVec.Y = Y + scalar;
			nVec.Z = Z + scalar;
			nVec.W = W + scalar;
			return nVec;
		}
		const Vector4 addScalarSelf(const auto scalar){
			X += scalar;
			Y += scalar;
			Z += scalar;
			W += scalar;
			return* this;
		}
	private:
	public:
		const Vector4 operator*(const Vector4& other){
			return mul(other);
		}
		const Vector4 operator*(const auto scalar){
			return mulScalar(scalar);
		}
		const Vector4 operator*=(const Vector4& other){
			return mulSelf(other);
		}
		const Vector4 operator*=(const auto scalar){
			return mulScalarSelf(scalar);
		}
		const Vector4 operator/(const Vector4& other){
			return divide(other);
		}
		const Vector4 operator/(const auto scalar){
			return divideScalar(scalar);
		}
		const Vector4 operator/=(const Vector4& other){
			return divideSelf(other);
		}
		const Vector4 operator/=(const auto scalar){
			return divideScalarSelf(scalar);
		}
		const Vector4 operator+(const Vector4& other){
			return add(other);
		}
		const Vector4 operator+=(const Vector4& other){
			return addSelf(other);
		}
		const Vector4 operator-(const Vector4& other){
			return sub(other);
		}
		const Vector4 operator-=(const Vector4& other){
			return subSelf(other);
		}
		const Vector4 operator+(const auto scalar){
			return addScalar(scalar);
		}
		const Vector4 operator+=(const auto scalar){
			return addScalarSelf(scalar);
		}
		const Vector4 operator-(const auto scalar){
			return subScalar(scalar);
		}
		const Vector4 operator-=(const auto scalar){
			return subScalarSelf(scalar);
		}
		/*
		 * TODO : Finish this class
		 */
		const Vector4 rgb8_normalize() const{
			if( X < 256 && Y < 256 && Z < 256 && W < 256){
				return Vector4(X/255.0f,Y/255.0f,Z/255.0f,W/255.0f);
			}else{
				return Vector4(0);
			}
		}
		const auto dot(const Vector4& other) const{
			return (X*other.X) + (Y*other.Y) + (Z*other.Z) + (W*other.W);
		}
		const Vector4 normalize()const{
			return Vector4(X / magnitude(), Y / magnitude(), Z / magnitude(), W / magnitude());
		}
		inline auto constexpr const magnitude() const { return sqrt(X*X+Y*Y+Z*Z+W*W); }
		/*
		 * I return references that are not const. Cause I realized I need to modify these. Except for the ones that should obviously stay constant.
		 */
		inline auto& x() { return X; }
		inline auto& y() { return Y; }
		inline auto& z() { return Z; }
		inline auto& w() { return W; }
		inline auto& r() { return x(); }
		inline auto& g() { return y(); }
		inline auto& b() { return z(); }
		inline auto& a() { return w(); }
		inline auto* data() { return d; }
		inline size_t constexpr const components() const { return C; }
		inline size_t constexpr const c() const { return C; }
		inline auto constexpr const max() const{
			std::array<t, C> arr = {d[0], d[1], d[2], d[3]};
			std::sort(arr.begin(), arr.end(), std::greater<t>());
			return arr[0];
		}
		inline auto constexpr const min() const{
			std::array<t, C> arr = {d[0], d[1], d[2], d[3]};
			std::sort(arr.begin(), arr.end(), std::less<t>());
			return arr[0];
		}
};

#endif
