#ifndef MATH_ETC_HPP
#define MATH_ETC_HPP
#define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086

inline constexpr const float toRadians(float deg){
	return deg*(M_PI / 180.0f);
}

inline constexpr const float toDegrees(float rad){
	return rad*(180.0f / M_PI);
}

#endif
