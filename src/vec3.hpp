#include <algorithm>
#include <array>
#include <iostream>
#include "vec2.hpp"
#ifndef VECTOR3_HPP
#define VECTOR3_HPP
	/*
	 * Vector3D : A class that performs mathematic operations on a vector with n
	 * 		components in this case n = 3.
	 *
	 * 		Used for simple 3D graphics calculations
	 *
	 * 	This is a templated class
	 */
template<typename t>
class Vector3{
	public:
#ifdef VEC3_GLM_TYPES
#include <glm/glm.hpp>
		Vector3(const glm::vec3 v) : X(v.x), Y(v.y), Z(v.z){ }
#endif
		Vector3() = default;
		Vector3(const Vector3& other) = default;
		~Vector3() = default;
		Vector3(const auto x, const auto y, const auto z) : X(x), Y(y), Z(z){
		}
		Vector3(const Vector2<t> other) : X(other.x()), Y(other.y()){}
		Vector3(const auto scalar) : X(scalar), Y(scalar), Z(scalar){}
		Vector3(const auto d[3]) : X(d[0]), Y(d[1]), Z(d[2]) {}
	private:
		constexpr const static size_t C = 3;
		union{
			struct{
				t X;
				t Y;
				t Z;
			};
			struct{
				t R;
				t G;
				t B;
			};
			t d[C];
		};
	private:
		// Division
		const Vector3 divide(const Vector3& other) const{
			Vector3 nVec;
			nVec.X = X / other.X;
			nVec.Y = Y / other.Y;
			nVec.Z = Z / other.Z;
			return nVec;
		}
		const Vector3 divideSelf(const Vector3& other){

			X /= other.X;
			Y /= other.Y;
			Z /= other.Z;
			return *this;
		}
		const Vector3 divideScalar(const auto scalar) const {
			Vector3 nVec;	
			nVec.X = X / scalar;
			nVec.Y = Y / scalar;
			nVec.Z = Z / scalar;
			return nVec;
		}
		const Vector3 divideScalarSelf(const auto scalar) {
			X /= scalar;
			Y /= scalar;
			Z /= scalar;
			return *this;
		}
		// Multiplication
		const Vector3 mul(const Vector3& other) const{
			Vector3 nVec;
			nVec.X = X * other.X;
			nVec.Y = Y *other.Y;
			nVec.Z = Z * other.Z;
			return nVec;
		}
		const Vector3 mulSelf(const Vector3& other) {
			X *= other.X;
			Y *= other.Y;
			Z *= other.Z;
			return *this;
		}
		const Vector3 mulScalar(const auto scalar) const{
			Vector3 nVec;
			nVec.X = X * scalar;
			nVec.Y = Y * scalar;
			nVec.Z = Z * scalar;
			return nVec;
		}
		const Vector3 mulScalarSelf(const auto scalar){
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
			return *this;
		}
		// Subtraction
		const Vector3 sub(const Vector3& other) const{
			Vector3 nVec;
			nVec.X = X - other.X;
			nVec.Y = Y - other.Y;
			nVec.Z = Z - other.Z;
			return nVec;
		}
		const Vector3 subSelf(const Vector3& other) {
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			return *this;
		}
		const Vector3 subScalar(const auto scalar) const{
			Vector3 nVec;
			nVec.X = X - scalar;
			nVec.Y = Y - scalar;
			nVec.Z = Z - scalar;
			return nVec;
		}
		const Vector3 subScalarSelf(const auto scalar){
			X -= scalar;
			Y -= scalar;
			Z -= scalar;
			return *this;
		}
		
		//Addition
		const Vector3 add(const Vector3& other) const{
			Vector3 nVec;
			nVec.X = X + other.X;
			nVec.Y = Y + other.Y;
			nVec.Z = Z + other.Z;
			return nVec;
		}
		const Vector3 addSelf(const Vector3& other) {
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			return *this;
		}
		const Vector3 addScalar(const auto scalar) const{
			Vector3 nVec;
			nVec.X = X + scalar;
			nVec.Y = Y + scalar;
			nVec.Z = Z + scalar;
			return nVec;
		}
		const Vector3 addScalarSelf(const auto scalar){
			X += scalar;
			Y += scalar;
			Z += scalar;
			return* this;
		}
	public:	
		const Vector3 operator*(const Vector3& other){
			return mul(other);
		}
		const Vector3 operator*(const auto scalar){
			return mulScalar(scalar);
		}
		const Vector3 operator*=(const Vector3& other){
			return mulSelf(other);
		}
		const Vector3 operator*=(const auto scalar){
			return mulScalarSelf(scalar);
		}
		const Vector3 operator/(const Vector3& other){
			return divide(other);
		}
		const Vector3 operator/(const auto scalar){
			return divideScalar(scalar);
		}
		const Vector3 operator/=(const auto scalar){
			return divideScalarSelf(scalar);
		}
		const Vector3 operator/=(const Vector3& other){
			return divideSelf(other);
		}
		const Vector3 operator-(const Vector3& other){
		}
		friend std::ostream& operator<<(std::ostream &os, const Vector3& other){
			os << "(" << other.x() << "," << other.y() << "," << other.z() << ")";
			return os;
		}
		const auto dot(const Vector3& other) const{
			return (X*other.X) + (Y*other.Y) + (Z*other.Z);
		}
		const auto cross(const Vector3& other) const{
			Vector3 nVec;
			nVec.X = Y*other.Z - Z*other.Y;
			nVec.Y = Z*other.X - X*other.Z ;
			nVec.Z = X*other.Y - Y*other.X;
			return nVec;
		}
		const Vector3 normalize()const{
			return Vector3(X / magnitude(), Y / magnitude(), Z / magnitude());
		}
		// Return it normalize an rgb color
		const Vector3 rgb8_normalize() const{
			if( X < 256 && Y < 256 && Z < 256 ){
			return Vector3(X / 255, Y / 255, Z / 255);
			}
			else{
				// Return an empty vector if it doesn't fit
				return Vector3(0);
			}
		}
	private:
	public:
		inline auto constexpr const magnitude() const { return sqrt(X*X + Y*Y + Z*Z);}
		inline auto constexpr const x() const{ return X;}
		inline auto constexpr const y() const{ return Y;}
		inline auto constexpr const z() const{ return Z;}
		inline auto constexpr const r() const{ return x();}
		inline auto constexpr const g() const{ return y();}
		inline auto constexpr const b() const{ return z();}
		inline constexpr auto* data() { return d; }
		inline size_t constexpr const components() const{ return C; }
		inline size_t constexpr const c() const { return C; }
		inline auto constexpr max() const{
			std::array<t, C> arr = {d[0], d[1], d[2]};
			std::sort(arr.begin(), arr.end(), std::greater<t>());
			return arr[0];
		}
		inline auto constexpr min() const{
			std::array<t, C> arr = {d[0], d[1], d[2]};
			std::sort(arr.begin(), arr.end(), std::less<t>());
			return arr[0];
		}
};


#endif
