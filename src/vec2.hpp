#include <iostream>
#include <cmath>
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

/*
 * Vector2D : A class that performs mathematic operations on a vector with n components.
 * 		in this case n = 2.
 * Used for simple 2D graphics calculations
 */
// This is a templated class
template<typename t>
class Vector2{
	public:
#ifdef VEC2_GLM_TYPES
#include <glm/glm.hpp>
		Vector2(const glm::vec2 v) : X(v.x), Y(v.y){}
#endif
		// Have defaulted constructor
		Vector2() = default;
		// The compiler shall make the copy constructor for this class as I can not make something as efficient
		Vector2(const Vector2& other) = default ; 
		// Scalar constructor
		Vector2(const auto scalar) : X(scalar), Y(scalar){
		}
		// Standard X Y constructor
		Vector2(const auto x , const auto y ) : X(x), Y(y){	
		}
		// Using an array to construct
		Vector2(const auto d[2]) : X(d[0]), Y(d[1]){
		}
		~Vector2() = default;
	private:
		/*
		 * This section of the class contains the functions that are called when the operators are used.
		 * for now they are set to private because I do not think it neccessary to use them directly.
		 */
		const Vector2 divide(const Vector2& other) const{
			Vector2 nVec;
			nVec.X = X / other.X;
			nVec.Y = Y / other.Y;
			return nVec;
		}
		const Vector2 divideSelf(const Vector2& other) {
			X /= other.X;
			Y /= other.Y;
			return *this;
		}
		const Vector2 divideScalar(const auto scalar)const{
			Vector2 nVec;
			nVec.X = X / scalar;
			nVec.Y = Y / scalar;
			return nVec;
		}
		const Vector2 divideScalarSelf(const auto scalar) {
			X /= scalar;
			Y /= scalar;
			return *this;
		}
		const Vector2 add(const Vector2& other) const {
			Vector2 nVec;
			nVec.X = X+other.X;
			nVec.Y = Y+other.Y;
			return nVec;
		}
		const Vector2 selfAdd(const Vector2& other) {
			X += other.X;
			Y += other.Y;
			return *this;
		}
		const Vector2 selfSub(const Vector2& other) {
			X -= other.X;
			Y -= other.Y;
			return *this;
		}
		const Vector2 sub(const Vector2& other)const {
			Vector2 nVec;
			nVec.X = X - other.X;
			nVec.y = Y - other.Y;
			return nVec;
		}
		const Vector2 selfMul(const Vector2& other) {
			X *= other.X;
			Y *= other.Y;
			return *this;
		}
		const Vector2 mul(const Vector2& other)const {
			Vector2 nVec;
			nVec.X = X*other.X;
			nVec.Y = Y*other.Y;
			return nVec;
		}
		const Vector2 multiplyScalarSelf(const auto scalar){
			X *= scalar;
			Y *= scalar;
			return *this;
		}
		const Vector2 multiplyScalar(const auto scalar)const {
			Vector2 nVec;
			nVec.X *= scalar;
			nVec.Y *= scalar;
			return nVec;
		}
	public:
#ifdef VEC2_GLM_TYPES
#include <glm/glm.hpp>
		inline constexpr const glm::vec2 asGlmVec2(){ return glm::vec2(X, Y); }	
#endif
		const Vector2 operator+(const Vector2& other) {
			return add(other);
		}
		const Vector2 operator+=(const Vector2& other){
			return selfAdd(other);
		}
		const Vector2 operator-(const Vector2& other){
			return sub(other);
		}
		const Vector2 operator-=(const Vector2& other){
			return selfSub(other);
		}
		const Vector2 operator*(const Vector2& other){
			return mul(other);
		}
		const Vector2 operator*=(const Vector2& other){
			return selfMul(other);

		}
		const Vector2 operator*(const auto val){
			return multiplyScalar(val);
		}
		const Vector2 operator*=(const auto val){
			return multiplyScalarSelf(const_cast<t>(val));
		}
		const Vector2 operator/(const Vector2 & other){
			return divide(other);
		}
		const Vector2 operator/=(const Vector2 &other){
			return divideSelf(other);
		}
		const Vector2 operator/(const auto scalar){
			return divideScalar(scalar);
		}

		const Vector2 normalize() const{
			return Vector2(X / magnitude(), Y / magnitude());
		}
		const Vector2 operator/=(const auto scalar){
			return divideScalarSelf(scalar);
		}
		const auto dot(const Vector2& other){
			return (X * other.X) + (Y*other.Y);
		}
#ifdef VEC2_CROSS_PRODUCT
		const auto cross(const Vector2& other){
		}
#endif VEC2_CROSS_PRODUCT
		friend std::ostream& operator<<(std::ostream& os, const Vector2& other){
			// So ostream doesn't accept << ????
			// oh wait I know why it didn't work. I set ostream as const. when << is modifying it. Idiot.
			os << "(" << other.x() << "," << other.y() << ")";
			return os;
		}
		/*
		 * Using C++ 11 optimizations to slightly speed up the program and using close to standard library
		 * getter naming conventions.
		 *
		 * These functions return a respective component of the union they are in
		 */
		inline auto &x() { return X; }
		inline auto &y() { return Y; }
		inline auto &u() { x(); }; // u and v are the same as x and y.
		inline auto constexpr const magnitude() const{ return sqrt(X*X + Y*Y);}
		inline auto &v() { y(); }; //
		// return the greater of two components
		inline auto constexpr const max() const { return X > Y ? X : Y;}
		// return the lesser of two components
		inline auto constexpr const min() const { return X < Y ? X : Y;}
		inline size_t constexpr const components() const { return C;}
		inline size_t constexpr const c() const { return C; }
		inline constexpr auto* data() { return d ; }	
	private:
	/*
	 * The problem was just me temporarily being dumb. That took btw 10 seconds to figure out.
	 * See what I did was.
	 */
	constexpr const static size_t C = 2;

	union{
		struct{
			t X ;
			t Y ;
		};
		struct{
			t U ;
			t V ;
		};
		t d[C];
	};
#ifdef BROKEN_CODE_FOREXAMPLE
	// Something like this.
	// See I thought I could just make a struct in a struct. Just no. just no.
	struct{
	union{
		T x;
		T y;
	};
	};
#endif
};


// Whatever this is it.
#endif 
