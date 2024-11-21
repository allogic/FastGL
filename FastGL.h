#pragma warning(disable : 4191)
#pragma warning(disable : 4201)
#pragma warning(disable : 4255)
#pragma warning(disable : 4668)
#pragma warning(disable : 4710)
#pragma warning(disable : 4711)
#pragma warning(disable : 4774)
#pragma warning(disable : 4820)
#pragma warning(disable : 5039)
#pragma warning(disable : 5045)
#pragma warning(disable : 5246)
#pragma warning(disable : 6011)
#pragma warning(disable : 6308)
#pragma warning(disable : 6387)
#pragma warning(disable : 28182)

#pragma comment(lib, "Opengl32.lib")

#define _CRT_SECURE_NO_WARNINGS

#ifndef FAST_GL_H
#define FAST_GL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <gl/GL.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	///////////////////////////////////////////////////////////////
	// Feature Detection
	///////////////////////////////////////////////////////////////

#if defined(__SSE__) && defined(__SSE2__)
#define FAST_GL_SSE2_SUPPORTED
#elif defined(__SSE__)
#define FAST_GL_SSE_SUPPORTED
#endif // SSE_SUPPORT

#if defined (__AVX512F__) && defined(__AVX512DQ__) && defined(__AVX512CD__) && defined(__AVX512BW__) && defined(__AVX512VL__)
#define FAST_GL_AVX512_SUPPORTED
#elif defined(__AVX__) && defined(__AVX2__)
#define FAST_GL_AVX2_SUPPORTED
#elif defined(__AVX__)
#define FAST_GL_AVX_SUPPORTED
#endif // AVX_SUPPORT

#if defined(FAST_GL_SSE_SUPPORTED) || defined(FAST_GL_SSE2_SUPPORTED)
#include <xmmintrin.h>
#endif // SSE_SUPPORT

#if defined(FAST_GL_AVX_SUPPORTED) || defined(FAST_GL_AVX2_SUPPORTED) || defined(FAST_GL_AVX512_SUPPORTED)
#include <immintrin.h>
#endif // AVX_SUPPORT

	///////////////////////////////////////////////////////////////
	// FastGL Configuration
	///////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define FAST_GL_DEBUG
#define FAST_GL_REFERENCE_COUNT
#endif // _DEBUG

	///////////////////////////////////////////////////////////////
	// Global Utility Macros
	///////////////////////////////////////////////////////////////

#define STATIC_ASSERT(EXPRESSION, MESSAGE) typedef char static_assertion_##MESSAGE[(EXPRESSION) ? 1 : -1]

#define OFFSET_OF(TYPE, MEMBER_NAME) ((long long unsigned)&(((TYPE*)0)->MEMBER_NAME))
#define MEMBER_OF(INSTANCE, TYPE, MEMBER_NAME, MEMBER_TYPE) ((MEMBER_TYPE*)(((long long unsigned)(INSTANCE)) + ((long long unsigned)&(((TYPE*)0)->MEMBER_NAME))))
#define BASE_OF(INSTANCE, TYPE, MEMBER_NAME) ((TYPE*)(((long long unsigned)(INSTANCE)) - ((long long unsigned)&(((TYPE*)0)->MEMBER_NAME))))

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

#define PI (3.1415926F)
#define SQRT_3 (1.7320508F)
#define EPSILON_2 (1E-2F)
#define EPSILON_3 (1E-3F)
#define EPSILON_4 (1E-4F)
#define EPSILON_5 (1E-5F)
#define EPSILON_6 (1E-6F)
#define EPSILON_7 (1E-7F)

#define DEG_TO_RAD(DEGREES) ((DEGREES) * 0.0174532F)
#define RAD_TO_DEG(RADIANS) ((RADIANS) * 57.2957795F)

#define ALIGN_DOWN_BY(VALUE, ALIGNMENT) (((long long unsigned)(VALUE)) & ~(((long long unsigned)(ALIGNMENT)) - 1ULL))
#define ALIGN_UP_BY(VALUE, ALIGNMENT) ((((long long unsigned)(VALUE)) + (((long long unsigned)(ALIGNMENT)) - 1ULL)) & ~(((long long unsigned)(ALIGNMENT)) - 1ULL))

#define L2B_ENDIAN_S16(VALUE) \
		((short)((((VALUE) & 0xFFULL) << 8) | \
				 (((VALUE) & 0xFF00ULL) >> 8)))

#define B2L_ENDIAN_S16(VALUE) \
		((short)((((VALUE) & 0xFFULL) << 8) | \
				 (((VALUE) & 0xFF00ULL) >> 8)))

#define L2B_ENDIAN_U16(VALUE) \
		((short unsigned)((((VALUE) & 0xFFULL) << 8) | \
						  (((VALUE) & 0xFF00ULL) >> 8)))

#define B2L_ENDIAN_U16(VALUE) \
		((short unsigned)((((VALUE) & 0xFFULL) << 8) | \
						  (((VALUE) & 0xFF00ULL) >> 8)))

#define L2B_ENDIAN_S32(VALUE) \
		((int)((((VALUE) & 0xFFULL) << 24) | \
			   (((VALUE) & 0xFF00ULL) << 8) | \
			   (((VALUE) & 0xFF0000ULL) >> 8) | \
			   (((VALUE) & 0xFF000000ULL) >> 24)))

#define B2L_ENDIAN_S32(VALUE) \
		((int)((((VALUE) & 0xFFULL) << 24) | \
			   (((VALUE) & 0xFF00ULL) << 8) | \
			   (((VALUE) & 0xFF0000ULL) >> 8) | \
			   (((VALUE) & 0xFF000000ULL) >> 24)))

#define L2B_ENDIAN_U32(VALUE) \
		((int unsigned)((((VALUE) & 0xFFULL) << 24) | \
						(((VALUE) & 0xFF00ULL) << 8) | \
						(((VALUE) & 0xFF0000ULL) >> 8) | \
						(((VALUE) & 0xFF000000ULL) >> 24)))

#define B2L_ENDIAN_U32(VALUE) \
		((int unsigned)((((VALUE) & 0xFFULL) << 24) | \
						(((VALUE) & 0xFF00ULL) << 8) | \
						(((VALUE) & 0xFF0000ULL) >> 8) | \
						(((VALUE) & 0xFF000000ULL) >> 24)))

#define L2B_ENDIAN_S64(VALUE) \
		((long long)((((VALUE) & 0xFFULL) << 56) | \
					 (((VALUE) & 0xFF00ULL) << 40) | \
					 (((VALUE) & 0xFF0000ULL) << 24) | \
					 (((VALUE) & 0xFF000000ULL) << 8) | \
					 (((VALUE) & 0xFF00000000ULL) >> 8) | \
					 (((VALUE) & 0xFF0000000000ULL) >> 24) | \
					 (((VALUE) & 0xFF000000000000ULL) >> 40) | \
					 (((VALUE) & 0xFF00000000000000ULL) >> 56)))

#define B2L_ENDIAN_S64(VALUE) \
		((long long)((((VALUE) & 0xFFULL) << 56) | \
					 (((VALUE) & 0xFF00ULL) << 40) | \
					 (((VALUE) & 0xFF0000ULL) << 24) | \
					 (((VALUE) & 0xFF000000ULL) << 8) | \
					 (((VALUE) & 0xFF00000000ULL) >> 8) | \
					 (((VALUE) & 0xFF0000000000ULL) >> 24) | \
					 (((VALUE) & 0xFF000000000000ULL) >> 40) | \
					 (((VALUE) & 0xFF00000000000000ULL) >> 56)))

#define L2B_ENDIAN_U64(VALUE) \
		((long long unsigned)((((VALUE) & 0xFFULL) << 56) | \
							  (((VALUE) & 0xFF00ULL) << 40) | \
							  (((VALUE) & 0xFF0000ULL) << 24) | \
							  (((VALUE) & 0xFF000000ULL) << 8) | \
							  (((VALUE) & 0xFF00000000ULL) >> 8) | \
							  (((VALUE) & 0xFF0000000000ULL) >> 24) | \
							  (((VALUE) & 0xFF000000000000ULL) >> 40) | \
							  (((VALUE) & 0xFF00000000000000ULL) >> 56)))

#define B2L_ENDIAN_U64(VALUE) \
		((long long unsigned)((((VALUE) & 0xFFULL) << 56) | \
							  (((VALUE) & 0xFF00ULL) << 40) | \
							  (((VALUE) & 0xFF0000ULL) << 24) | \
							  (((VALUE) & 0xFF000000ULL) << 8) | \
							  (((VALUE) & 0xFF00000000ULL) >> 8) | \
							  (((VALUE) & 0xFF0000000000ULL) >> 24) | \
							  (((VALUE) & 0xFF000000000000ULL) >> 40) | \
							  (((VALUE) & 0xFF00000000000000ULL) >> 56)))

#define IS_BIT_SET(VALUE, POSITION) (((long long unsigned)(VALUE)) & (1ULL << (POSITION)))
#define IS_BIT_NOT_SET(VALUE, POSITION) (!(((long long unsigned)(VALUE)) & (1ULL << (POSITION))))

#define SET_BIT(VALUE, POSITION) (((long long unsigned)(VALUE)) | (1ULL << (POSITION)))
#define CLEAR_BIT(VALUE, POSITION) (((long long unsigned)(VALUE)) & (~(1ULL << (POSITION))))
#define TOGGLE_BIT(VALUE, POSITION) (((long long unsigned)(VALUE)) ^ (1ULL << (POSITION)))

	///////////////////////////////////////////////////////////////
	// Common Shader Stuff
	///////////////////////////////////////////////////////////////

#define GLSL_GL_VERSION \
	"\n#version 460 core\n"

#define GLSL_BEGIN_INCLUDE_GUARD(NAME) \
	"\n#ifndef " #NAME "\n" \
	"\n#define " #NAME "\n"

#define GLSL_END_INCLUDE_GUARD(NAME) \
	"\n#endif\n"

#define GLSL_CONSTANTS \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_CONSTANTS) \
	"const float PI = 3.1415926;" \
	"const float TAU = 6.2831853;" \
	GLSL_END_INCLUDE_GUARD(GLSL_CONSTANTS)

#define GLSL_MATH_UTILITY_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_MATH_UTILITY_IMPLEMENTATION) \
	"float RemapTo01(float Value, float Min, float Max) {" \
	"	return (Value - Min) / (Max - Min);" \
	"}" \
	"float Remap(float Value, float OldMin, float OldMax, float NewMin, float NewMax) {" \
	"	return NewMin + ((Value - OldMin) / (OldMax - OldMin)) * (NewMax - NewMin);" \
	"}" \
	"float Gradiant01(float Position, float Size) {" \
	"	return Position / Size;" \
	"}" \
	"float Gradiant(float Position, float Size, float Min, float Max) {" \
	"	return Remap(Position / Size, 0.0, 1.0, Min, Max);" \
	"}" \
	"float HardTerrace(float Value, int TerraceLevels) {" \
	"	float StepSize = 1.0 / float(TerraceLevels);" \
	"	return floor(Value / StepSize) * StepSize;" \
	"}" \
	"float SoftTerrace(float Value, int TerraceLevels, float Sharpness) {" \
	"	float StepSize = 1.0 / float(TerraceLevels);" \
	"	float Level = floor(Value / StepSize);" \
	"	float LowerStep = Level * StepSize;" \
	"	float UpperStep = (Level + 1.0) * StepSize;" \
	"	float MixFactor = smoothstep(0.0, 1.0, pow((Value - LowerStep) / StepSize, Sharpness));" \
	"	return mix(LowerStep, UpperStep, MixFactor);" \
	"}" \
	"float Binarize(float Value, float Threshold) {" \
	"	return (Value > Threshold) ? 1.0 : 0.0;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_MATH_UTILITY_IMPLEMENTATION)

#define GLSL_SCREEN_SPACE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_SCREEN_SPACE_IMPLEMENTATION) \
	"vec4 ScreenToClipSpace(vec3 ScreenPosition, vec2 ScreenSize) {" \
	"	float NdcX = (2.0F * ScreenPosition.x) / ScreenSize.x - 1.0F;" \
	"	float NdcY = (2.0F * (ScreenSize.y - ScreenPosition.y)) / ScreenSize.y - 1.0F;" \
	"	float NdcZ = ScreenPosition.z;" \
	"	return vec4(NdcX, NdcY, NdcZ, 1.0F);" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_SCREEN_SPACE_IMPLEMENTATION)

#define GLSL_ROTATION_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_ROTATION_IMPLEMENTATION) \
	"vec2 RotateVector2D(vec2 Vector, float Angle) {" \
	"	float CA = cos(Angle);" \
	"	float SA = sin(Angle);" \
	"	return vec2(Vector.x * CA - Vector.y * SA, Vector.x * SA + Vector.y * CA);" \
	"}" \
	"vec3 RotateVector3D(vec3 Vector, vec4 Rotation) {" \
	"	vec3 U = Rotation.xyz;" \
	"	float S = Rotation.w;" \
	"	return 2.0 * dot(U, Vector) * U + (S * S - dot(U, U)) * Vector + 2.0 * S * cross(U, Vector);" \
	"}" \
	"vec4 EulerAnglesToQuaternion(float Pitch, float Yaw, float Roll) {" \
	"	float CX = cos(Pitch * 0.5);" \
	"	float SX = sin(Pitch * 0.5);" \
	"	float CY = cos(Yaw * 0.5);" \
	"	float SY = sin(Yaw * 0.5);" \
	"	float CZ = cos(Roll * 0.5);" \
	"	float SZ = sin(Roll * 0.5);" \
	"	vec4 Q;" \
	"	Q.x = SX * CY * CZ - CX * SY * SZ;" \
	"	Q.y = CX * SY * CZ + SX * CY * SZ;" \
	"	Q.z = CX * CY * SZ - SX * SY * CZ;" \
	"	Q.w = CX * CY * CZ + SX * SY * SZ;" \
	"	return Q;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_ROTATION_IMPLEMENTATION)

#define GLSL_UNSIGNED_RANDOM_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_UNSIGNED_RANDOM_IMPLEMENTATION) \
	"const vec4 UNSIGNED_RANDOM_SCALE = vec4(443.897, 441.423, .0973, .1099);" \
	"float random(float x) {" \
	"	x = fract(x * UNSIGNED_RANDOM_SCALE.x);" \
	"	x *= x + 33.33;" \
	"	x *= x + x;" \
	"	return fract(x);" \
	"}" \
	"float random(vec2 st) {" \
	"	vec3 p3 = fract(vec3(st.xyx) * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 33.33);" \
	"	return fract((p3.x + p3.y) * p3.z);" \
	"}" \
	"float random(vec3 pos) {" \
	"	pos = fract(pos * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	pos += dot(pos, pos.zyx + 31.32);" \
	"	return fract((pos.x + pos.y) * pos.z);" \
	"}" \
	"float random(vec4 pos) {" \
	"	pos = fract(pos * UNSIGNED_RANDOM_SCALE);" \
	"	pos += dot(pos, pos.wzxy + 33.33);" \
	"	return fract((pos.x + pos.y) * (pos.z + pos.w));" \
	"}" \
	"vec2 random2(float p) {" \
	"	vec3 p3 = fract(vec3(p) * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 19.19);" \
	"	return fract((p3.xx + p3.yz) * p3.zy);" \
	"}" \
	"vec2 random2(vec2 p) {" \
	"	vec3 p3 = fract(p.xyx * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 19.19);" \
	"	return fract((p3.xx + p3.yz) * p3.zy);" \
	"}" \
	"vec2 random2(vec3 p3) {" \
	"	p3 = fract(p3 * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 19.19);" \
	"	return fract((p3.xx + p3.yz) * p3.zy);" \
	"}" \
	"vec3 random3(float p) {" \
	"	vec3 p3 = fract(vec3(p) * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 19.19);" \
	"	return fract((p3.xxy + p3.yzz) * p3.zyx);" \
	"}" \
	"vec3 random3(vec2 p) {" \
	"	vec3 p3 = fract(vec3(p.xyx) * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yxz + 19.19);" \
	"	return fract((p3.xxy + p3.yzz) * p3.zyx);" \
	"}" \
	"vec3 random3(vec3 p) {" \
	"	p = fract(p * UNSIGNED_RANDOM_SCALE.xyz);" \
	"	p += dot(p, p.yxz + 19.19);" \
	"	return fract((p.xxy + p.yzz) * p.zyx);" \
	"}" \
	"vec4 random4(float p) {" \
	"	vec4 p4 = fract(p * UNSIGNED_RANDOM_SCALE);" \
	"	p4 += dot(p4, p4.wzxy + 19.19);" \
	"	return fract((p4.xxyz + p4.yzzw) * p4.zywx);" \
	"}" \
	"vec4 random4(vec2 p) {" \
	"	vec4 p4 = fract(p.xyxy * UNSIGNED_RANDOM_SCALE);" \
	"	p4 += dot(p4, p4.wzxy + 19.19);" \
	"	return fract((p4.xxyz + p4.yzzw) * p4.zywx);" \
	"}" \
	"vec4 random4(vec3 p) {" \
	"	vec4 p4 = fract(p.xyzx * UNSIGNED_RANDOM_SCALE);" \
	"	p4 += dot(p4, p4.wzxy + 19.19);" \
	"	return fract((p4.xxyz + p4.yzzw) * p4.zywx);" \
	"}" \
	"vec4 random4(vec4 p4) {" \
	"	p4 = fract(p4 * UNSIGNED_RANDOM_SCALE);" \
	"	p4 += dot(p4, p4.wzxy + 19.19);" \
	"	return fract((p4.xxyz + p4.yzzw) * p4.zywx);" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_UNSIGNED_RANDOM_IMPLEMENTATION)

#define GLSL_SIGNED_RANDOM_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_SIGNED_RANDOM_IMPLEMENTATION) \
	"float srandom(float x) {" \
	"	return -1. + 2. * fract(sin(x) * 43758.5453);" \
	"}" \
	"float srandom(vec2 st) {" \
	"	return -1. + 2. * fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);" \
	"}" \
	"float srandom(vec3 pos) {" \
	"	return -1. + 2. * fract(sin(dot(pos.xyz, vec3(70.9898, 78.233, 32.4355))) * 43758.5453123);" \
	"}" \
	"float srandom(vec4 pos) {" \
	"	float dot_product = dot(pos, vec4(12.9898, 78.233, 45.164, 94.673));" \
	"	return -1. + 2. * fract(sin(dot_product) * 43758.5453);" \
	"}" \
	"vec2 srandom2(vec2 st) {" \
	"	const vec2 k = vec2(.3183099, .3678794);" \
	"	st = st * k + k.yx;" \
	"	return -1. + 2. * fract(16. * k * fract(st.x * st.y * (st.x + st.y)));" \
	"}" \
	"vec3 srandom3(vec3 p) {" \
	"	p = vec3(dot(p, vec3(127.1, 311.7, 74.7)), dot(p, vec3(269.5, 183.3, 246.1)), dot(p, vec3(113.5, 271.9, 124.6)));" \
	"	return -1. + 2. * fract(sin(p) * 43758.5453123);" \
	"}" \
	"vec2 srandom2(vec2 p, float tileLength) {" \
	"	p = mod(p, vec2(tileLength));" \
	"	return srandom2(p);" \
	"}" \
	"vec3 srandom3(vec3 p, float tileLength) {" \
	"	p = mod(p, vec3(tileLength));" \
	"	return srandom3(p);" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_SIGNED_RANDOM_IMPLEMENTATION)

#define GLSL_MOD289_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_MOD289_IMPLEMENTATION) \
	"float mod289(float x) { return x - floor(x * (1. / 289.)) * 289.; }" \
	"vec2 mod289(vec2 x) { return x - floor(x * (1. / 289.)) * 289.; }" \
	"vec3 mod289(vec3 x) { return x - floor(x * (1. / 289.)) * 289.; }" \
	"vec4 mod289(vec4 x) { return x - floor(x * (1. / 289.)) * 289.; }" \
	GLSL_END_INCLUDE_GUARD(GLSL_MOD289_IMPLEMENTATION)


#define GLSL_PERMUTE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_PERMUTE_IMPLEMENTATION) \
	"float permute(float v) { return mod289(((v * 34.0) + 1.0) * v); }" \
	"vec2 permute(vec2 v) { return mod289(((v * 34.0) + 1.0) * v); }" \
	"vec3 permute(vec3 v) { return mod289(((v * 34.0) + 1.0) * v); }" \
	"vec4 permute(vec4 v) { return mod289(((v * 34.0) + 1.0) * v); }" \
	GLSL_END_INCLUDE_GUARD(GLSL_PERMUTE_IMPLEMENTATION)

#define GLSL_TAYLOR_INV_SQRT_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_TAYLOR_INV_SQRT_IMPLEMENTATION) \
	"float taylorInvSqrt(float r) { return 1.79284291400159 - 0.85373472095314 * r; }" \
	"vec2 taylorInvSqrt(vec2 r) { return 1.79284291400159 - 0.85373472095314 * r; }" \
	"vec3 taylorInvSqrt(vec3 r) { return 1.79284291400159 - 0.85373472095314 * r; }" \
	"vec4 taylorInvSqrt(vec4 r) { return 1.79284291400159 - 0.85373472095314 * r; }" \
	GLSL_END_INCLUDE_GUARD(GLSL_TAYLOR_INV_SQRT_IMPLEMENTATION)

#define GLSL_GRAD4_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_GRAD4_IMPLEMENTATION) \
	"vec4 grad4(float j, vec4 ip) {" \
	"	const vec4 ones = vec4(1.0, 1.0, 1.0, -1.0);" \
	"	vec4 p, s;" \
	"	p.xyz = floor(fract(vec3(j) * ip.xyz) * 7.0) * ip.z - 1.0;" \
	"	p.w = 1.5 - dot(abs(p.xyz), ones.xyz);" \
	"	s = vec4(lessThan(p, vec4(0.0)));" \
	"	p.xyz = p.xyz + (s.xyz * 2.0 - 1.0) * s.www;" \
	"	return p;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_GRAD4_IMPLEMENTATION)

#define GLSL_CUBIC_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_CUBIC_IMPLEMENTATION) \
	"float cubic(float v) { return v*v*(3.0-2.0*v); }" \
	"vec2 cubic(vec2 v) { return v * v * (3.0 - 2.0 * v); }" \
	"vec3 cubic(vec3 v) { return v * v * (3.0 - 2.0 * v); }" \
	"vec4 cubic(vec4 v) { return v * v * (3.0 - 2.0 * v); }" \
	"float cubic(float v, float slope0, float slope1) {" \
	"	float a = slope0 + slope1 - 2.;" \
	"	float b = -2. * slope0 - slope1 + 3.;" \
	"	float c = slope0;" \
	"	float v2 = v * v;" \
	"	float v3 = v * v2;" \
	"	return a * v3 + b * v2 + c * v;" \
	"}" \
	"vec2 cubic(vec2 v, float slope0, float slope1) {" \
	"	float a = slope0 + slope1 - 2.;" \
	"	float b = -2. * slope0 - slope1 + 3.;" \
	"	float c = slope0;" \
	"	vec2 v2 = v * v;" \
	"	vec2 v3 = v * v2;" \
	"	return a * v3 + b * v2 + c * v;" \
	"}" \
	"vec3 cubic(vec3 v, float slope0, float slope1) {" \
	"	float a = slope0 + slope1 - 2.;" \
	"	float b = -2. * slope0 - slope1 + 3.;" \
	"	float c = slope0;" \
	"	vec3 v2 = v * v;" \
	"	vec3 v3 = v * v2;" \
	"	return a * v3 + b * v2 + c * v;" \
	"}" \
	"vec4 cubic(vec4 v, float slope0, float slope1) {" \
	"	float a = slope0 + slope1 - 2.;" \
	"	float b = -2. * slope0 - slope1 + 3.;" \
	"	float c = slope0;" \
	"	vec4 v2 = v * v;" \
	"	vec4 v3 = v * v2;" \
	"	return a * v3 + b * v2 + c * v;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_CUBIC_IMPLEMENTATION)

#define GLSL_QUINTIC_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_QUINTIC_IMPLEMENTATION) \
	"float quintic(float v) { return v*v*v*(v*(v*6.0-15.0)+10.0); }" \
	"vec2 quintic(vec2 v) { return v * v * v * (v * (v * 6.0 - 15.0) + 10.0); }" \
	"vec3 quintic(vec3 v) { return v * v * v * (v * (v * 6.0 - 15.0) + 10.0); }" \
	"vec4 quintic(vec4 v) { return v * v * v * (v * (v * 6.0 - 15.0) + 10.0); }" \
	GLSL_END_INCLUDE_GUARD(GLSL_QUINTIC_IMPLEMENTATION)

#define GLSL_SIMPLEX_NOISE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_SIMPLEX_NOISE_IMPLEMENTATION) \
	GLSL_MOD289_IMPLEMENTATION \
	GLSL_PERMUTE_IMPLEMENTATION \
	GLSL_TAYLOR_INV_SQRT_IMPLEMENTATION \
	GLSL_GRAD4_IMPLEMENTATION \
	"float SimplexNoise2D(vec2 Position) {" \
	"	const vec4 C = vec4(0.211324865405187, 0.366025403784439, -0.577350269189626, 0.024390243902439);" \
	"	vec2 i = floor(Position + dot(Position, C.yy));" \
	"	vec2 x0 = Position - i + dot(i, C.xx);" \
	"	vec2 i1;" \
	"	i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);" \
	"	vec4 x12 = x0.xyxy + C.xxzz;" \
	"	x12.xy -= i1;" \
	"	i = mod289(i);" \
	"	vec3 p = permute(permute(i.y + vec3(0.0, i1.y, 1.0)) + i.x + vec3(0.0, i1.x, 1.0));" \
	"	vec3 m = max(0.5 - vec3(dot(x0, x0), dot(x12.xy, x12.xy), dot(x12.zw, x12.zw)), 0.0);" \
	"	m = m * m;" \
	"	m = m * m;	" \
	"	vec3 x = 2.0 * fract(p * C.www) - 1.0;" \
	"	vec3 h = abs(x) - 0.5;" \
	"	vec3 ox = floor(x + 0.5);" \
	"	vec3 a0 = x - ox;" \
	"	m *= 1.79284291400159 - 0.85373472095314 * (a0 * a0 + h * h);" \
	"	vec3 g;" \
	"	g.x = a0.x * x0.x + h.x * x0.y;" \
	"	g.yz = a0.yz * x12.xz + h.yz * x12.yw;" \
	"	return 130.0 * dot(m, g);" \
	"}" \
	"float SimplexNoise3D(vec3 Position) {" \
	"	const vec2  C = vec2(1.0 / 6.0, 1.0 / 3.0);" \
	"	const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);" \
	"	vec3 i = floor(Position + dot(Position, C.yyy));" \
	"	vec3 x0 = Position - i + dot(i, C.xxx);" \
	"	vec3 g = step(x0.yzx, x0.xyz);" \
	"	vec3 l = 1.0 - g;" \
	"	vec3 i1 = min(g.xyz, l.zxy);" \
	"	vec3 i2 = max(g.xyz, l.zxy);" \
	"	vec3 x1 = x0 - i1 + C.xxx;" \
	"	vec3 x2 = x0 - i2 + C.yyy;" \
	"	vec3 x3 = x0 - D.yyy;" \
	"	i = mod289(i);" \
	"	vec4 p = permute(permute(permute(i.z + vec4(0.0, i1.z, i2.z, 1.0)) + i.y + vec4(0.0, i1.y, i2.y, 1.0)) + i.x + vec4(0.0, i1.x, i2.x, 1.0));" \
	"	float n_ = 0.142857142857;" \
	"	vec3  ns = n_ * D.wyz - D.xzx;" \
	"	vec4 j = p - 49.0 * floor(p * ns.z * ns.z);" \
	"	vec4 x_ = floor(j * ns.z);" \
	"	vec4 y_ = floor(j - 7.0 * x_);" \
	"	vec4 x = x_ * ns.x + ns.yyyy;" \
	"	vec4 y = y_ * ns.x + ns.yyyy;" \
	"	vec4 h = 1.0 - abs(x) - abs(y);" \
	"	vec4 b0 = vec4(x.xy, y.xy);" \
	"	vec4 b1 = vec4(x.zw, y.zw);" \
	"	vec4 s0 = floor(b0) * 2.0 + 1.0;" \
	"	vec4 s1 = floor(b1) * 2.0 + 1.0;" \
	"	vec4 sh = -step(h, vec4(0.0));" \
	"	vec4 a0 = b0.xzyw + s0.xzyw * sh.xxyy;" \
	"	vec4 a1 = b1.xzyw + s1.xzyw * sh.zzww;" \
	"	vec3 p0 = vec3(a0.xy, h.x);" \
	"	vec3 p1 = vec3(a0.zw, h.y);" \
	"	vec3 p2 = vec3(a1.xy, h.z);" \
	"	vec3 p3 = vec3(a1.zw, h.w);" \
	"	vec4 norm = taylorInvSqrt(vec4(dot(p0, p0), dot(p1, p1), dot(p2, p2), dot(p3, p3)));" \
	"	p0 *= norm.x;" \
	"	p1 *= norm.y;" \
	"	p2 *= norm.z;" \
	"	p3 *= norm.w;" \
	"	vec4 m = max(0.6 - vec4(dot(x0, x0), dot(x1, x1), dot(x2, x2), dot(x3, x3)), 0.0);" \
	"	m = m * m;" \
	"	return 42.0 * dot(m * m, vec4(dot(p0, x0), dot(p1, x1), dot(p2, x2), dot(p3, x3)));" \
	"}" \
	"float SimplexNoise4D(vec4 Position) {" \
	"	const vec4  C = vec4(0.138196601125011, 0.276393202250021, 0.414589803375032, -0.447213595499958);" \
	"	vec4 i = floor(Position + dot(Position, vec4(.309016994374947451)));" \
	"	vec4 x0 = Position - i + dot(i, C.xxxx);" \
	"	vec4 i0;" \
	"	vec3 isX = step(x0.yzw, x0.xxx);" \
	"	vec3 isYZ = step(x0.zww, x0.yyz);" \
	"	i0.x = isX.x + isX.y + isX.z;" \
	"	i0.yzw = 1.0 - isX;" \
	"	i0.y += isYZ.x + isYZ.y;" \
	"	i0.zw += 1.0 - isYZ.xy;" \
	"	i0.z += isYZ.z;" \
	"	i0.w += 1.0 - isYZ.z;" \
	"	vec4 i3 = clamp(i0, 0.0, 1.0);" \
	"	vec4 i2 = clamp(i0 - 1.0, 0.0, 1.0);" \
	"	vec4 i1 = clamp(i0 - 2.0, 0.0, 1.0);" \
	"	vec4 x1 = x0 - i1 + C.xxxx;" \
	"	vec4 x2 = x0 - i2 + C.yyyy;" \
	"	vec4 x3 = x0 - i3 + C.zzzz;" \
	"	vec4 x4 = x0 + C.wwww;" \
	"	i = mod289(i);" \
	"	float j0 = permute(permute(permute(permute(i.w) + i.z) + i.y) + i.x);" \
	"	vec4 j1 = permute(permute(permute(permute(i.w + vec4(i1.w, i2.w, i3.w, 1.0)) + i.z + vec4(i1.z, i2.z, i3.z, 1.0)) + i.y + vec4(i1.y, i2.y, i3.y, 1.0)) + i.x + vec4(i1.x, i2.x, i3.x, 1.0));" \
	"	vec4 ip = vec4(1.0 / 294.0, 1.0 / 49.0, 1.0 / 7.0, 0.0);" \
	"	vec4 p0 = grad4(j0, ip);" \
	"	vec4 p1 = grad4(j1.x, ip);" \
	"	vec4 p2 = grad4(j1.y, ip);" \
	"	vec4 p3 = grad4(j1.z, ip);" \
	"	vec4 p4 = grad4(j1.w, ip);" \
	"	vec4 norm = taylorInvSqrt(vec4(dot(p0, p0), dot(p1, p1), dot(p2, p2), dot(p3, p3)));" \
	"	p0 *= norm.x;" \
	"	p1 *= norm.y;" \
	"	p2 *= norm.z;" \
	"	p3 *= norm.w;" \
	"	p4 *= taylorInvSqrt(dot(p4, p4));" \
	"	vec3 m0 = max(0.6 - vec3(dot(x0, x0), dot(x1, x1), dot(x2, x2)), 0.0);" \
	"	vec2 m1 = max(0.6 - vec2(dot(x3, x3), dot(x4, x4)), 0.0);" \
	"	m0 = m0 * m0;" \
	"	m1 = m1 * m1;" \
	"	return 49.0 * (dot(m0 * m0, vec3(dot(p0, x0), dot(p1, x1), dot(p2, x2))) + dot(m1 * m1, vec2(dot(p3, x3), dot(p4, x4))));" \
	"}" \
	"vec2 VectorSimplexNoise2D(vec2 Position) {"\
	"	float s = SimplexNoise2D(vec2(Position));"\
	"	float s1 = SimplexNoise2D(vec2(Position.y - 19.1, Position.x + 47.2));"\
	"	return vec2(s, s1);"\
	"}"\
	"vec3 VectorSimplexNoise3D(vec3 Position) {"\
	"	float s = SimplexNoise3D(vec3(Position));"\
	"	float s1 = SimplexNoise3D(vec3(Position.y - 19.1, Position.z + 33.4, Position.x + 47.2));"\
	"	float s2 = SimplexNoise3D(vec3(Position.z + 74.2, Position.x - 124.5, Position.y + 99.4));"\
	"	return vec3(s, s1, s2);"\
	"}"\
	"vec3 VectorSimplexNoise3D(vec4 Position) {"\
	"	float s = SimplexNoise4D(vec4(Position));"\
	"	float s1 = SimplexNoise4D(vec4(Position.y - 19.1, Position.z + 33.4, Position.x + 47.2, Position.w));"\
	"	float s2 = SimplexNoise4D(vec4(Position.z + 74.2, Position.x - 124.5, Position.y + 99.4, Position.w));"\
	"	return vec3(s, s1, s2);"\
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_SIMPLEX_NOISE_IMPLEMENTATION)

#define GLSL_GRADIENT_NOISE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_GRADIENT_NOISE_IMPLEMENTATION) \
	GLSL_UNSIGNED_RANDOM_IMPLEMENTATION \
	GLSL_SIGNED_RANDOM_IMPLEMENTATION \
	GLSL_CUBIC_IMPLEMENTATION \
	GLSL_QUINTIC_IMPLEMENTATION \
	"float GradientNoise1D(float Value) {" \
	"	float i = floor(Value);" \
	"	float f = fract(Value);" \
	"	return mix(random(i), random(i + 1.0), smoothstep(0., 1., f));" \
	"}" \
	"float GradientNoise2D(vec2 Position) {" \
	"	vec2 i = floor(Position);" \
	"	vec2 f = fract(Position);" \
	"	float a = random(i);" \
	"	float b = random(i + vec2(1.0, 0.0));" \
	"	float c = random(i + vec2(0.0, 1.0));" \
	"	float d = random(i + vec2(1.0, 1.0));" \
	"	vec2 u = cubic(f);" \
	"	return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;" \
	"}" \
	"float GradientNoise3D(vec3 Position) {" \
	"	vec3 i = floor(Position);" \
	"	vec3 f = fract(Position);" \
	"	vec3 u = quintic(f);" \
	"	return -1.0 + 2.0 * mix(mix(mix(random(i + vec3(0.0, 0.0, 0.0)), random(i + vec3(1.0, 0.0, 0.0)), u.x), mix(random(i + vec3(0.0, 1.0, 0.0)), random(i + vec3(1.0, 1.0, 0.0)), u.x), u.y), mix(mix(random(i + vec3(0.0, 0.0, 1.0)), random(i + vec3(1.0, 0.0, 1.0)), u.x), mix(random(i + vec3(0.0, 1.0, 1.0)), random(i + vec3(1.0, 1.0, 1.0)), u.x), u.y), u.z);" \
	"}" \
	"float GradientNoise3D(vec3 Position, float TileLength) {" \
	"	vec3 i = floor(Position);" \
	"	vec3 f = fract(Position);" \
	"	vec3 u = quintic(f);" \
	"	return mix(mix(mix(dot(srandom3(i + vec3(0.0, 0.0, 0.0), TileLength), f - vec3(0.0, 0.0, 0.0)), dot(srandom3(i + vec3(1.0, 0.0, 0.0), TileLength), f - vec3(1.0, 0.0, 0.0)), u.x), mix(dot(srandom3(i + vec3(0.0, 1.0, 0.0), TileLength), f - vec3(0.0, 1.0, 0.0)), dot(srandom3(i + vec3(1.0, 1.0, 0.0), TileLength), f - vec3(1.0, 1.0, 0.0)), u.x), u.y), mix(mix(dot(srandom3(i + vec3(0.0, 0.0, 1.0), TileLength), f - vec3(0.0, 0.0, 1.0)), dot(srandom3(i + vec3(1.0, 0.0, 1.0), TileLength), f - vec3(1.0, 0.0, 1.0)), u.x), mix(dot(srandom3(i + vec3(0.0, 1.0, 1.0), TileLength), f - vec3(0.0, 1.0, 1.0)), dot(srandom3(i + vec3(1.0, 1.0, 1.0), TileLength), f - vec3(1.0, 1.0, 1.0)), u.x), u.y), u.z);" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_GRADIENT_NOISE_IMPLEMENTATION)

#define GLSL_VORONOI_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_VORONOI_IMPLEMENTATION) \
	GLSL_CONSTANTS \
	GLSL_UNSIGNED_RANDOM_IMPLEMENTATION \
	"float Voronoi2D(vec2 Position, float AngleOffset, float Radius, float Density) {" \
	"	vec2 n = floor(Position * Density);" \
	"	vec2 f = fract(Position * Density);" \
	"	float f1 = 8.0;" \
	"	for (int j = -1; j <= 1; j++) {" \
	"		for (int i = -1; i <= 1; i++) {" \
	"			vec2 g = vec2(i, j);" \
	"			vec2 o = random2(n + g);" \
	"			o = 0.5 + 0.41 * sin(AngleOffset + TAU * o);" \
	"			vec2 r = (g - f + o) * Radius;" \
	"			float d = sqrt(dot(r,r));" \
	"			if (d < f1) {" \
	"				f1 = d;" \
	"			}" \
	"		}" \
	"	}" \
	"	return f1;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_VORONOI_IMPLEMENTATION)

#define GLSL_VORO_NOISE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_VORO_NOISE_IMPLEMENTATION) \
	GLSL_UNSIGNED_RANDOM_IMPLEMENTATION \
	"float VoroNoise2D(vec2 Position, float U, float V) {" \
	"	float k = 1.0 + 63.0 * pow(1.0 - V, 6.0);" \
	"	vec2 i = floor(Position);" \
	"	vec2 f = fract(Position);" \
	"	vec2 a = vec2(0.0, 0.0);" \
	"	vec2 g = vec2(-2.0);" \
	"	for (g.y = -2.0; g.y <= 2.0; g.y++) {" \
	"		for (g.x = -2.0; g.x <= 2.0; g.x++) {" \
	"			vec3 o = random3(i + g) * vec3(U, U, 1.0);" \
	"			vec2 d = g - f + o.xy;" \
	"			float w = pow(1.0 - smoothstep(0.0, 1.414, length(d)), k);" \
	"			a += vec2(o.z * w, w);" \
	"		}" \
	"	}" \
	"	return a.x / a.y;" \
	"}" \
	"float VoroNoise3D(vec3 Position, float U, float V) {" \
	"	float k = 1.0 + 63.0 * pow(1.0 - V, 6.0);" \
	"	vec3 i = floor(Position);" \
	"	vec3 f = fract(Position);" \
	"	float s = 1.0 + 31.0 * V;" \
	"	vec2 a = vec2(0.0, 0.0);" \
	"	vec3 g = vec3(-2.0);" \
	"	for (g.z = -2.0; g.z <= 2.0; g.z++) {" \
	"		for (g.y = -2.0; g.y <= 2.0; g.y++) {" \
	"			for (g.x = -2.0; g.x <= 2.0; g.x++) {" \
	"				vec3 o = random3(i + g) * vec3(U, U, 1.);" \
	"				vec3 d = g - f + o + 0.5;" \
	"				float w = pow(1.0 - smoothstep(0.0, 1.414, length(d)), k);" \
	"				a += vec2(o.z * w, w);" \
	"			}" \
	"		}" \
	"	}" \
	"	return a.x / a.y;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_VORO_NOISE_IMPLEMENTATION)

#define GLSL_FBM_NOISE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_FBM_NOISE_IMPLEMENTATION) \
	GLSL_SIMPLEX_NOISE_IMPLEMENTATION \
	GLSL_GRADIENT_NOISE_IMPLEMENTATION \
	"float FbmNoise2D(vec2 Position, float Scale, float Amplitude, int Octaves) {" \
	"	float v = 0.0;" \
	"	float a = 0.5;" \
	"	for (int i = 0; i < Octaves; i++) {" \
	"		v += a * SimplexNoise2D(Position);" \
	"		Position *= Scale;" \
	"		a *= Amplitude;" \
	"	}" \
	"	return v;" \
	"}" \
	"float FbmNoise3D(vec3 Position, float Scale, float Amplitude, int Octaves) {" \
	"	float v = 0.0;" \
	"	float a = 0.5;" \
	"	for (int i = 0; i < Octaves; i++) {" \
	"		v += a * SimplexNoise3D(Position);" \
	"		Position *= Scale;" \
	"		a *= Amplitude;" \
	"	}" \
	"	return v;" \
	"}" \
	"float FbmNoise3D(vec3 Position, float TileLength, float Lacunarity, float Persistence, int Octaves) {" \
	"	float a = 0.5;" \
	"	float t = 0.0;" \
	"	float n = 0.0;" \
	"	for (int i = 0; i < Octaves; ++i) {" \
	"		float v = GradientNoise3D(Position, TileLength * Lacunarity * 0.5) * 0.5 + 0.5;" \
	"		t += v * a;" \
	"		n += a;" \
	"		a *= Persistence;" \
	"		Position = Position * Lacunarity;" \
	"	}" \
	"	return t / n;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_FBM_NOISE_IMPLEMENTATION)

#define GLSL_CURL_NOISE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_CURL_NOISE_IMPLEMENTATION) \
	GLSL_SIMPLEX_NOISE_IMPLEMENTATION \
	"vec2 CurlNoise2D(vec2 Position) {" \
	"	const float e = 0.1;" \
	"	vec2 dx = vec2(e, 0.0);" \
	"	vec2 dy = vec2(0.0, e);" \
	"	vec2 p_x0 = VectorSimplexNoise2D(Position - dx);" \
	"	vec2 p_x1 = VectorSimplexNoise2D(Position + dx);" \
	"	vec2 p_y0 = VectorSimplexNoise2D(Position - dy);" \
	"	vec2 p_y1 = VectorSimplexNoise2D(Position + dy);" \
	"	float x = p_x1.y + p_x0.y;" \
	"	float y = p_y1.x - p_y0.x;" \
	"	const float divisor = 1.0 / (2.0 * e);" \
	"	return normalize(vec2(x, y) * divisor);" \
	"}" \
	"vec3 CurlNoise3D(vec3 Position) {" \
	"	const float e = 0.1;" \
	"	vec3 dx = vec3(e, 0.0, 0.0);" \
	"	vec3 dy = vec3(0.0, e, 0.0);" \
	"	vec3 dz = vec3(0.0, 0.0, e);" \
	"	vec3 p_x0 = VectorSimplexNoise3D(Position - dx);" \
	"	vec3 p_x1 = VectorSimplexNoise3D(Position + dx);" \
	"	vec3 p_y0 = VectorSimplexNoise3D(Position - dy);" \
	"	vec3 p_y1 = VectorSimplexNoise3D(Position + dy);" \
	"	vec3 p_z0 = VectorSimplexNoise3D(Position - dz);" \
	"	vec3 p_z1 = VectorSimplexNoise3D(Position + dz);" \
	"	float x = p_y1.z - p_y0.z - p_z1.y + p_z0.y;" \
	"	float y = p_z1.x - p_z0.x - p_x1.z + p_x0.z;" \
	"	float z = p_x1.y - p_x0.y - p_y1.x + p_y0.x;" \
	"	const float divisor = 1.0 / (2.0 * e);" \
	"	return normalize(vec3(x, y, z) * divisor);" \
	"}" \
	"vec3 CurlNoise4D(vec4 Position) {" \
	"	const float e = 0.1;" \
	"	vec4 dx = vec4(e, 0.0, 0.0, 1.0);" \
	"	vec4 dy = vec4(0.0, e, 0.0, 1.0);" \
	"	vec4 dz = vec4(0.0, 0.0, e, 1.0);" \
	"	vec3 p_x0 = VectorSimplexNoise3D(Position - dx);" \
	"	vec3 p_x1 = VectorSimplexNoise3D(Position + dx);" \
	"	vec3 p_y0 = VectorSimplexNoise3D(Position - dy);" \
	"	vec3 p_y1 = VectorSimplexNoise3D(Position + dy);" \
	"	vec3 p_z0 = VectorSimplexNoise3D(Position - dz);" \
	"	vec3 p_z1 = VectorSimplexNoise3D(Position + dz);" \
	"	float x = p_y1.z - p_y0.z - p_z1.y + p_z0.y;" \
	"	float y = p_z1.x - p_z0.x - p_x1.z + p_x0.z;" \
	"	float z = p_x1.y - p_x0.y - p_y1.x + p_y0.x;" \
	"	const float divisor = 1.0 / (2.0 * e);" \
	"	return normalize(vec3(x, y, z) * divisor);" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_CURL_NOISE_IMPLEMENTATION)

#define GLSL_PERLIN_NOISE_IMPLEMENTATION \
	GLSL_BEGIN_INCLUDE_GUARD(GLSL_PERLIN_NOISE_IMPLEMENTATION) \
	GLSL_MOD289_IMPLEMENTATION \
	GLSL_PERMUTE_IMPLEMENTATION \
	GLSL_QUINTIC_IMPLEMENTATION \
	GLSL_TAYLOR_INV_SQRT_IMPLEMENTATION \
	"float PerlinNoise2D(vec2 Position) {" \
	"	vec4 Pi = floor(Position.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);" \
	"	vec4 Pf = fract(Position.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);" \
	"	Pi = mod289(Pi);" \
	"	vec4 ix = Pi.xzxz;" \
	"	vec4 iy = Pi.yyww;" \
	"	vec4 fx = Pf.xzxz;" \
	"	vec4 fy = Pf.yyww;" \
	"	vec4 i = permute(permute(ix) + iy);" \
	"	vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0;" \
	"	vec4 gy = abs(gx) - 0.5;" \
	"	vec4 tx = floor(gx + 0.5);" \
	"	gx = gx - tx;" \
	"	vec2 g00 = vec2(gx.x, gy.x);" \
	"	vec2 g10 = vec2(gx.y, gy.y);" \
	"	vec2 g01 = vec2(gx.z, gy.z);" \
	"	vec2 g11 = vec2(gx.w, gy.w);" \
	"	vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));" \
	"	g00 *= norm.x;" \
	"	g01 *= norm.y;" \
	"	g10 *= norm.z;" \
	"	g11 *= norm.w;" \
	"	float n00 = dot(g00, vec2(fx.x, fy.x));" \
	"	float n10 = dot(g10, vec2(fx.y, fy.y));" \
	"	float n01 = dot(g01, vec2(fx.z, fy.z));" \
	"	float n11 = dot(g11, vec2(fx.w, fy.w));" \
	"	vec2 fade_xy = quintic(Pf.xy);" \
	"	vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);" \
	"	float n_xy = mix(n_x.x, n_x.y, fade_xy.y);" \
	"	return 2.3 * n_xy;" \
	"}" \
	"float PerlinNoise3D(vec3 Position) {" \
	"	vec3 Pi0 = floor(Position);" \
	"	vec3 Pi1 = Pi0 + vec3(1.0);" \
	"	Pi0 = mod289(Pi0);" \
	"	Pi1 = mod289(Pi1);" \
	"	vec3 Pf0 = fract(Position);" \
	"	vec3 Pf1 = Pf0 - vec3(1.0);" \
	"	vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);" \
	"	vec4 iy = vec4(Pi0.yy, Pi1.yy);" \
	"	vec4 iz0 = Pi0.zzzz;" \
	"	vec4 iz1 = Pi1.zzzz;" \
	"	vec4 ixy = permute(permute(ix) + iy);" \
	"	vec4 ixy0 = permute(ixy + iz0);" \
	"	vec4 ixy1 = permute(ixy + iz1);" \
	"	vec4 gx0 = ixy0 * (1.0 / 7.0);" \
	"	vec4 gy0 = fract(floor(gx0) * (1.0 / 7.0)) - 0.5;" \
	"	gx0 = fract(gx0);" \
	"	vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);" \
	"	vec4 sz0 = step(gz0, vec4(0.0));" \
	"	gx0 -= sz0 * (step(0.0, gx0) - 0.5);" \
	"	gy0 -= sz0 * (step(0.0, gy0) - 0.5);" \
	"	vec4 gx1 = ixy1 * (1.0 / 7.0);" \
	"	vec4 gy1 = fract(floor(gx1) * (1.0 / 7.0)) - 0.5;" \
	"	gx1 = fract(gx1);" \
	"	vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);" \
	"	vec4 sz1 = step(gz1, vec4(0.0));" \
	"	gx1 -= sz1 * (step(0.0, gx1) - 0.5);" \
	"	gy1 -= sz1 * (step(0.0, gy1) - 0.5);" \
	"	vec3 g000 = vec3(gx0.x, gy0.x, gz0.x);" \
	"	vec3 g100 = vec3(gx0.y, gy0.y, gz0.y);" \
	"	vec3 g010 = vec3(gx0.z, gy0.z, gz0.z);" \
	"	vec3 g110 = vec3(gx0.w, gy0.w, gz0.w);" \
	"	vec3 g001 = vec3(gx1.x, gy1.x, gz1.x);" \
	"	vec3 g101 = vec3(gx1.y, gy1.y, gz1.y);" \
	"	vec3 g011 = vec3(gx1.z, gy1.z, gz1.z);" \
	"	vec3 g111 = vec3(gx1.w, gy1.w, gz1.w);" \
	"	vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));" \
	"	g000 *= norm0.x;" \
	"	g010 *= norm0.y;" \
	"	g100 *= norm0.z;" \
	"	g110 *= norm0.w;" \
	"	vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));" \
	"	g001 *= norm1.x;" \
	"	g011 *= norm1.y;" \
	"	g101 *= norm1.z;" \
	"	g111 *= norm1.w;" \
	"	float n000 = dot(g000, Pf0);" \
	"	float n100 = dot(g100, vec3(Pf1.x, Pf0.yz));" \
	"	float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));" \
	"	float n110 = dot(g110, vec3(Pf1.xy, Pf0.z));" \
	"	float n001 = dot(g001, vec3(Pf0.xy, Pf1.z));" \
	"	float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));" \
	"	float n011 = dot(g011, vec3(Pf0.x, Pf1.yz));" \
	"	float n111 = dot(g111, Pf1);" \
	"	vec3 fade_xyz = quintic(Pf0);" \
	"	vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);" \
	"	vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);" \
	"	float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x);" \
	"	return 2.2 * n_xyz;" \
	"}" \
	"float PerlinNoise4D(vec4 Position) {" \
	"	vec4 Pi0 = floor(Position);" \
	"	vec4 Pi1 = Pi0 + 1.0;" \
	"	Pi0 = mod289(Pi0);" \
	"	Pi1 = mod289(Pi1);" \
	"	vec4 Pf0 = fract(Position);" \
	"	vec4 Pf1 = Pf0 - 1.0;" \
	"	vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);" \
	"	vec4 iy = vec4(Pi0.yy, Pi1.yy);" \
	"	vec4 iz0 = vec4(Pi0.zzzz);" \
	"	vec4 iz1 = vec4(Pi1.zzzz);" \
	"	vec4 iw0 = vec4(Pi0.wwww);" \
	"	vec4 iw1 = vec4(Pi1.wwww);" \
	"	vec4 ixy = permute(permute(ix) + iy);" \
	"	vec4 ixy0 = permute(ixy + iz0);" \
	"	vec4 ixy1 = permute(ixy + iz1);" \
	"	vec4 ixy00 = permute(ixy0 + iw0);" \
	"	vec4 ixy01 = permute(ixy0 + iw1);" \
	"	vec4 ixy10 = permute(ixy1 + iw0);" \
	"	vec4 ixy11 = permute(ixy1 + iw1);" \
	"	vec4 gx00 = ixy00 * (1.0 / 7.0);" \
	"	vec4 gy00 = floor(gx00) * (1.0 / 7.0);" \
	"	vec4 gz00 = floor(gy00) * (1.0 / 6.0);" \
	"	gx00 = fract(gx00) - 0.5;" \
	"	gy00 = fract(gy00) - 0.5;" \
	"	gz00 = fract(gz00) - 0.5;" \
	"	vec4 gw00 = vec4(0.75) - abs(gx00) - abs(gy00) - abs(gz00);" \
	"	vec4 sw00 = step(gw00, vec4(0.0));" \
	"	gx00 -= sw00 * (step(0.0, gx00) - 0.5);" \
	"	gy00 -= sw00 * (step(0.0, gy00) - 0.5);" \
	"	vec4 gx01 = ixy01 * (1.0 / 7.0);" \
	"	vec4 gy01 = floor(gx01) * (1.0 / 7.0);" \
	"	vec4 gz01 = floor(gy01) * (1.0 / 6.0);" \
	"	gx01 = fract(gx01) - 0.5;" \
	"	gy01 = fract(gy01) - 0.5;" \
	"	gz01 = fract(gz01) - 0.5;" \
	"	vec4 gw01 = vec4(0.75) - abs(gx01) - abs(gy01) - abs(gz01);" \
	"	vec4 sw01 = step(gw01, vec4(0.0));" \
	"	gx01 -= sw01 * (step(0.0, gx01) - 0.5);" \
	"	gy01 -= sw01 * (step(0.0, gy01) - 0.5);" \
	"	vec4 gx10 = ixy10 * (1.0 / 7.0);" \
	"	vec4 gy10 = floor(gx10) * (1.0 / 7.0);" \
	"	vec4 gz10 = floor(gy10) * (1.0 / 6.0);" \
	"	gx10 = fract(gx10) - 0.5;" \
	"	gy10 = fract(gy10) - 0.5;" \
	"	gz10 = fract(gz10) - 0.5;" \
	"	vec4 gw10 = vec4(0.75) - abs(gx10) - abs(gy10) - abs(gz10);" \
	"	vec4 sw10 = step(gw10, vec4(0.0));" \
	"	gx10 -= sw10 * (step(0.0, gx10) - 0.5);" \
	"	gy10 -= sw10 * (step(0.0, gy10) - 0.5);" \
	"	vec4 gx11 = ixy11 * (1.0 / 7.0);" \
	"	vec4 gy11 = floor(gx11) * (1.0 / 7.0);" \
	"	vec4 gz11 = floor(gy11) * (1.0 / 6.0);" \
	"	gx11 = fract(gx11) - 0.5;" \
	"	gy11 = fract(gy11) - 0.5;" \
	"	gz11 = fract(gz11) - 0.5;" \
	"	vec4 gw11 = vec4(0.75) - abs(gx11) - abs(gy11) - abs(gz11);" \
	"	vec4 sw11 = step(gw11, vec4(0.0));" \
	"	gx11 -= sw11 * (step(0.0, gx11) - 0.5);" \
	"	gy11 -= sw11 * (step(0.0, gy11) - 0.5);" \
	"	vec4 g0000 = vec4(gx00.x, gy00.x, gz00.x, gw00.x);" \
	"	vec4 g1000 = vec4(gx00.y, gy00.y, gz00.y, gw00.y);" \
	"	vec4 g0100 = vec4(gx00.z, gy00.z, gz00.z, gw00.z);" \
	"	vec4 g1100 = vec4(gx00.w, gy00.w, gz00.w, gw00.w);" \
	"	vec4 g0010 = vec4(gx10.x, gy10.x, gz10.x, gw10.x);" \
	"	vec4 g1010 = vec4(gx10.y, gy10.y, gz10.y, gw10.y);" \
	"	vec4 g0110 = vec4(gx10.z, gy10.z, gz10.z, gw10.z);" \
	"	vec4 g1110 = vec4(gx10.w, gy10.w, gz10.w, gw10.w);" \
	"	vec4 g0001 = vec4(gx01.x, gy01.x, gz01.x, gw01.x);" \
	"	vec4 g1001 = vec4(gx01.y, gy01.y, gz01.y, gw01.y);" \
	"	vec4 g0101 = vec4(gx01.z, gy01.z, gz01.z, gw01.z);" \
	"	vec4 g1101 = vec4(gx01.w, gy01.w, gz01.w, gw01.w);" \
	"	vec4 g0011 = vec4(gx11.x, gy11.x, gz11.x, gw11.x);" \
	"	vec4 g1011 = vec4(gx11.y, gy11.y, gz11.y, gw11.y);" \
	"	vec4 g0111 = vec4(gx11.z, gy11.z, gz11.z, gw11.z);" \
	"	vec4 g1111 = vec4(gx11.w, gy11.w, gz11.w, gw11.w);" \
	"	vec4 norm00 = taylorInvSqrt(vec4(dot(g0000, g0000), dot(g0100, g0100), dot(g1000, g1000), dot(g1100, g1100)));" \
	"	g0000 *= norm00.x;" \
	"	g0100 *= norm00.y;" \
	"	g1000 *= norm00.z;" \
	"	g1100 *= norm00.w;" \
	"	vec4 norm01 = taylorInvSqrt(vec4(dot(g0001, g0001), dot(g0101, g0101), dot(g1001, g1001), dot(g1101, g1101)));" \
	"	g0001 *= norm01.x;" \
	"	g0101 *= norm01.y;" \
	"	g1001 *= norm01.z;" \
	"	g1101 *= norm01.w;" \
	"	vec4 norm10 = taylorInvSqrt(vec4(dot(g0010, g0010), dot(g0110, g0110), dot(g1010, g1010), dot(g1110, g1110)));" \
	"	g0010 *= norm10.x;" \
	"	g0110 *= norm10.y;" \
	"	g1010 *= norm10.z;" \
	"	g1110 *= norm10.w;" \
	"	vec4 norm11 = taylorInvSqrt(vec4(dot(g0011, g0011), dot(g0111, g0111), dot(g1011, g1011), dot(g1111, g1111)));" \
	"	g0011 *= norm11.x;" \
	"	g0111 *= norm11.y;" \
	"	g1011 *= norm11.z;" \
	"	g1111 *= norm11.w;" \
	"	float n0000 = dot(g0000, Pf0);" \
	"	float n1000 = dot(g1000, vec4(Pf1.x, Pf0.yzw));" \
	"	float n0100 = dot(g0100, vec4(Pf0.x, Pf1.y, Pf0.zw));" \
	"	float n1100 = dot(g1100, vec4(Pf1.xy, Pf0.zw));" \
	"	float n0010 = dot(g0010, vec4(Pf0.xy, Pf1.z, Pf0.w));" \
	"	float n1010 = dot(g1010, vec4(Pf1.x, Pf0.y, Pf1.z, Pf0.w));" \
	"	float n0110 = dot(g0110, vec4(Pf0.x, Pf1.yz, Pf0.w));" \
	"	float n1110 = dot(g1110, vec4(Pf1.xyz, Pf0.w));" \
	"	float n0001 = dot(g0001, vec4(Pf0.xyz, Pf1.w));" \
	"	float n1001 = dot(g1001, vec4(Pf1.x, Pf0.yz, Pf1.w));" \
	"	float n0101 = dot(g0101, vec4(Pf0.x, Pf1.y, Pf0.z, Pf1.w));" \
	"	float n1101 = dot(g1101, vec4(Pf1.xy, Pf0.z, Pf1.w));" \
	"	float n0011 = dot(g0011, vec4(Pf0.xy, Pf1.zw));" \
	"	float n1011 = dot(g1011, vec4(Pf1.x, Pf0.y, Pf1.zw));" \
	"	float n0111 = dot(g0111, vec4(Pf0.x, Pf1.yzw));" \
	"	float n1111 = dot(g1111, Pf1);" \
	"	vec4 fade_xyzw = quintic(Pf0);" \
	"	vec4 n_0w = mix(vec4(n0000, n1000, n0100, n1100), vec4(n0001, n1001, n0101, n1101), fade_xyzw.w);" \
	"	vec4 n_1w = mix(vec4(n0010, n1010, n0110, n1110), vec4(n0011, n1011, n0111, n1111), fade_xyzw.w);" \
	"	vec4 n_zw = mix(n_0w, n_1w, fade_xyzw.z);" \
	"	vec2 n_yzw = mix(n_zw.xy, n_zw.zw, fade_xyzw.y);" \
	"	float n_xyzw = mix(n_yzw.x, n_yzw.y, fade_xyzw.x);" \
	"	return 2.2 * n_xyzw;" \
	"}" \
	GLSL_END_INCLUDE_GUARD(GLSL_PERLIN_NOISE_IMPLEMENTATION)

	///////////////////////////////////////////////////////////////
	// Platform Type Checks
	///////////////////////////////////////////////////////////////

	STATIC_ASSERT(sizeof(char) == 1, invalid_size_detected);
	STATIC_ASSERT(sizeof(short) == 2, invalid_size_detected);
	STATIC_ASSERT(sizeof(int) == 4, invalid_size_detected);
	STATIC_ASSERT(sizeof(long) == 4, invalid_size_detected);
	STATIC_ASSERT(sizeof(long long) == 8, invalid_size_detected);
	STATIC_ASSERT(sizeof(float) == 4, invalid_size_detected);
	STATIC_ASSERT(sizeof(double) == 8, invalid_size_detected);

	///////////////////////////////////////////////////////////////
	// WindowsGL Definition
	///////////////////////////////////////////////////////////////

	typedef HGLRC(*glCreateContext_PROC)(HDC DeviceContext);
	typedef BOOL(*glMakeCurrent_PROC)(HDC DeviceContext, HGLRC GraphicsContext);
	typedef PROC(*glGetProcAddress_PROC)(LPCSTR ProcedureName);
	typedef BOOL(*glDeleteContext_PROC)(HGLRC GraphicsContext);

#ifdef FAST_GL_IMPLEMENTATION
	static glCreateContext_PROC glCreateContext = 0;
	static glMakeCurrent_PROC glMakeCurrent = 0;
	static glGetProcAddress_PROC glGetProcAddress = 0;
	static glDeleteContext_PROC glDeleteContext = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// OpenGL Definition
	///////////////////////////////////////////////////////////////

#define GL_DEBUG_OUTPUT (0x92E0)
#define GL_DEBUG_SEVERITY_NOTIFICATION (0x826B)
#define GL_DEBUG_SEVERITY_HIGH (0x9146)
#define GL_DEBUG_SEVERITY_MEDIUM (0x9147)
#define GL_DEBUG_SEVERITY_LOW (0x9148)
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT (0x00000001)
#define GL_ELEMENT_ARRAY_BARRIER_BIT (0x00000002)
#define GL_UNIFORM_BARRIER_BIT (0x00000004)
#define GL_SHADER_STORAGE_BARRIER_BIT (0x00002000)
#define GL_BUFFER_UPDATE_BARRIER_BIT (0x00000200)
#define GL_LINES_ADJACENCY (0x000A)
#define GL_LINE_STRIP_ADJACENCY (0x000B)
#define GL_TRIANGLES_ADJACENCY (0x000C)
#define GL_TRIANGLE_STRIP_ADJACENCY (0x000D)
#define GL_GEOMETRY_SHADER (0x8DD9)
#define GL_VERTEX_SHADER (0x8B31)
#define GL_FRAGMENT_SHADER (0x8B30)
#define GL_COMPUTE_SHADER (0x91B9)
#define GL_COMPILE_STATUS (0x8B81)
#define GL_LINK_STATUS (0x8B82)
#define GL_INFO_LOG_LENGTH (0x8B84)
#define GL_STREAM_DRAW (0x88E0)
#define GL_STREAM_READ (0x88E1)
#define GL_STREAM_COPY (0x88E2)
#define GL_STATIC_DRAW (0x88E4)
#define GL_STATIC_READ (0x88E5)
#define GL_STATIC_COPY (0x88E6)
#define GL_DYNAMIC_DRAW (0x88E8)
#define GL_DYNAMIC_READ (0x88E9)
#define GL_DYNAMIC_COPY (0x88EA)
#define GL_ARRAY_BUFFER (0x8892)
#define GL_ELEMENT_ARRAY_BUFFER (0x8893)
#define GL_UNIFORM_BUFFER (0x8A11)
#define GL_SHADER_STORAGE_BUFFER (0x90D2)
#define GL_MAP_READ_BIT (0x0001)
#define GL_MAP_WRITE_BIT (0x0002)
#define GL_MAP_INVALIDATE_RANGE_BIT (0x0004)
#define GL_MAP_INVALIDATE_BUFFER_BIT (0x0008)
#define GL_MAP_PERSISTENT_BIT (0x0040)
#define GL_MAP_COHERENT_BIT (0x0080)
#define GL_READ_ONLY (0x88B8)
#define GL_WRITE_ONLY (0x88B9)
#define GL_READ_WRITE (0x88BA)
#define GL_MIRRORED_REPEAT (0x8370)
#define GL_CLAMP_TO_EDGE (0x812F)
#define GL_CLAMP_TO_BORDER (0x812D)
#define GL_UNSIGNED_INT_24_8 (0x84FA)
#define GL_RG (0x8227)
#define GL_DEPTH_STENCIL (0x84F9)
#define GL_R8UI (0x8232)
#define GL_R32F (0x822E)
#define GL_RGB8UI (0x8D7D)
#define GL_RGB32F (0x8815)
#define GL_RGBA8UI (0x8D7C)
#define GL_RGBA32F (0x8814)
#define GL_DEPTH24_STENCIL8 (0x88F0)
#define GL_FRAMEBUFFER (0x8D40)
#define GL_READ_FRAMEBUFFER (0x8CA8)
#define GL_DRAW_FRAMEBUFFER (0x8CA9)
#define GL_FRAMEBUFFER_DEFAULT_WIDTH (0x9310)
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT (0x9311)
#define GL_COLOR_ATTACHMENT0 (0x8CE0)
#define GL_COLOR_ATTACHMENT1 (0x8CE1)
#define GL_COLOR_ATTACHMENT2 (0x8CE2)
#define GL_COLOR_ATTACHMENT3 (0x8CE3)
#define GL_COLOR_ATTACHMENT4 (0x8CE4)
#define GL_COLOR_ATTACHMENT5 (0x8CE5)
#define GL_COLOR_ATTACHMENT6 (0x8CE6)
#define GL_COLOR_ATTACHMENT7 (0x8CE7)
#define GL_COLOR_ATTACHMENT8 (0x8CE8)
#define GL_COLOR_ATTACHMENT9 (0x8CE9)
#define GL_COLOR_ATTACHMENT10 (0x8CEA)
#define GL_COLOR_ATTACHMENT11 (0x8CEB)
#define GL_COLOR_ATTACHMENT12 (0x8CEC)
#define GL_COLOR_ATTACHMENT13 (0x8CED)
#define GL_COLOR_ATTACHMENT14 (0x8CEE)
#define GL_COLOR_ATTACHMENT15 (0x8CEF)
#define GL_COLOR_ATTACHMENT16 (0x8CF0)
#define GL_COLOR_ATTACHMENT17 (0x8CF1)
#define GL_COLOR_ATTACHMENT18 (0x8CF2)
#define GL_COLOR_ATTACHMENT19 (0x8CF3)
#define GL_COLOR_ATTACHMENT20 (0x8CF4)
#define GL_COLOR_ATTACHMENT21 (0x8CF5)
#define GL_COLOR_ATTACHMENT22 (0x8CF6)
#define GL_COLOR_ATTACHMENT23 (0x8CF7)
#define GL_COLOR_ATTACHMENT24 (0x8CF8)
#define GL_COLOR_ATTACHMENT25 (0x8CF9)
#define GL_COLOR_ATTACHMENT26 (0x8CFA)
#define GL_COLOR_ATTACHMENT27 (0x8CFB)
#define GL_COLOR_ATTACHMENT28 (0x8CFC)
#define GL_COLOR_ATTACHMENT29 (0x8CFD)
#define GL_COLOR_ATTACHMENT30 (0x8CFE)
#define GL_COLOR_ATTACHMENT31 (0x8CFF)
#define GL_DEPTH_STENCIL_ATTACHMENT (0x821A)
#define GL_FUNC_ADD (0x8006)
#define GL_FUNC_SUBTRACT (0x800A)
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT (0x00000001)
#define GL_UNIFORM_BARRIER_BIT (0x00000004)
#define GL_TEXTURE_FETCH_BARRIER_BIT (0x00000008)
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT (0x00000020)
#define GL_COMMAND_BARRIER_BIT (0x00000040)
#define GL_BUFFER_UPDATE_BARRIER_BIT (0x00000200)
#define GL_FRAMEBUFFER_BARRIER_BIT (0x00000400)
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT (0x00000800)
#define GL_ATOMIC_COUNTER_BARRIER_BIT (0x00001000)
#define GL_SHADER_STORAGE_BARRIER_BIT (0x00002000)
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT (0x00004000)
#define GL_QUERY_BUFFER_BARRIER_BIT (0x00008000)
#define GL_TIME_ELAPSED (0x88BF)
#define GL_QUERY_RESULT (0x8866)

	typedef void(*glDebug_PROC)(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);
	typedef void(*glDebugMessageCallback_PROC)(glDebug_PROC Callback, void const* UserParam);
	typedef void(*glGenQueries_PROC)(int unsigned Num, int unsigned* IDs);
	typedef void(*glBeginQuery_PROC)(int unsigned Target, int unsigned ID);
	typedef void(*glEndQuery_PROC)(int unsigned Target);
	typedef void(*glDeleteQueries_PROC)(int unsigned Num, int unsigned const* IDs);
	typedef void(*glGetQueryObjectui64v_PROC)(int unsigned ID, int unsigned Name, long long unsigned* Params);
	typedef void(*glClearBufferfv_PROC)(int unsigned Buffer, int DrawBuffer, float const* Value);
	typedef void(*glClearBufferiv_PROC)(int unsigned Buffer, int DrawBuffer, int const* Value);
	typedef void(*glBlendFunci_PROC)(int unsigned Buffer, int unsigned Source, int unsigned Destination);
	typedef void(*glBlendEquation_PROC)(int unsigned Mode);
	typedef void(*glMemoryBarrier_PROC)(int unsigned Barriers);
	typedef void(*glDrawElementsInstanced_PROC)(int unsigned Mode, int Count, int unsigned Type, void const* Indices, int InstanceCount);
	typedef void(*glDrawArraysInstanced_PROC)(int unsigned Mode, int First, int Count, int InstanceCount);
	typedef int unsigned(*glCreateProgram_PROC)(void);
	typedef int unsigned(*glCreateShader_PROC)(int unsigned ShaderType);
	typedef void(*glShaderSource_PROC)(int unsigned Shader, int unsigned Count, char const* const* String, int unsigned const* Length);
	typedef void(*glCompileShader_PROC)(int unsigned Shader);
	typedef void(*glAttachShader_PROC)(int unsigned Program, int unsigned Shader);
	typedef void(*glLinkProgram_PROC)(int unsigned Program);
	typedef void(*glDeleteShader_PROC)(int unsigned Shader);
	typedef void(*glUseProgram_PROC)(int unsigned Program);
	typedef void(*glDeleteProgram_PROC)(int unsigned Program);
	typedef int(*glGetUniformLocation_PROC)(int unsigned Program, char const* Name);
	typedef void(*glUniform1i_PROC)(int Location, int Value);
	typedef void(*glUniform1ui_PROC)(int Location, int unsigned Value);
	typedef void(*glUniform1f_PROC)(int Location, float Value);
	typedef void(*glUniform2fv_PROC)(int Location, int Count, float const* Value);
	typedef void(*glUniform3fv_PROC)(int Location, int Count, float const* Value);
	typedef void(*glUniform4fv_PROC)(int Location, int Count, float const* Value);
	typedef void(*glUniformMatrix4fv_PROC)(int Location, int unsigned Count, char unsigned Transpose, float const* Value);
	typedef void(*glDispatchCompute_PROC)(int unsigned NumGroupsX, int unsigned NumGroupsY, int unsigned NumGroupsZ);
	typedef void(*glGetShaderiv_PROC)(int unsigned Shader, int unsigned Name, int* Params);
	typedef void(*glGetShaderInfoLog_PROC)(int unsigned Shader, int BufferSize, int* Length, char* InfoLog);
	typedef void(*glGetProgramiv_PROC)(int unsigned Program, int unsigned Name, int* Params);
	typedef void(*glGetProgramInfoLog_PROC)(int unsigned Program, int BufferSize, int* Length, char* InfoLog);
	typedef void(*glGenVertexArrays_PROC)(int unsigned Num, int unsigned* Arrays);
	typedef void(*glDeleteVertexArrays_PROC)(int unsigned Num, int unsigned const* Arrays);
	typedef void(*glBindVertexArray_PROC)(int unsigned Array);
	typedef void(*glEnableVertexAttribArray_PROC)(int unsigned Index);
	typedef void(*glVertexAttribDivisor_PROC)(int unsigned Index, int unsigned Divisor);
	typedef void(*glVertexAttribPointer_PROC)(int unsigned Index, int Size, int unsigned Type, char unsigned Normalized, int unsigned Stride, void const* Pointer);
	typedef void(*glVertexAttribIPointer_PROC)(int unsigned Index, int Size, int unsigned Type, int unsigned Stride, void const* Pointer);
	typedef void(*glGenBuffers_PROC)(int unsigned Num, int unsigned* Buffers);
	typedef void(*glBindBuffer_PROC)(int unsigned Target, int unsigned Buffer);
	typedef void(*glBufferData_PROC)(int unsigned Target, int unsigned Size, void const* Data, int unsigned Usage);
	typedef void(*glBufferStorage_PROC)(int unsigned Target, int unsigned Size, void const* Data, int unsigned Flags);
	typedef void(*glDeleteBuffers_PROC)(int unsigned Num, int unsigned const* Buffers);
	typedef void(*glBufferSubData_PROC)(int unsigned Target, int unsigned Offset, int unsigned Size, void const* Data);
	typedef void(*glGetBufferSubData_PROC)(int unsigned Target, int unsigned Offset, int unsigned Size, void* Data);
	typedef void(*glBindBufferBase_PROC)(int unsigned Target, int unsigned Index, int unsigned Buffer);
	typedef void* (*glMapBuffer_PROC)(int unsigned Target, int unsigned Access);
	typedef void* (*glMapBufferRange_PROC)(int unsigned Target, int unsigned Offset, int unsigned Length, int unsigned Access);
	typedef char unsigned(*glUnmapBuffer_PROC)(int unsigned Target);
	typedef void(*glBindTextureUnit_PROC)(int unsigned Unit, int unsigned Texture);
	typedef void(*glBindImageTexture_PROC)(int unsigned Unit, int unsigned Texture, int Level, char unsigned Layered, int Layer, int unsigned Access, int unsigned Format);
	typedef void(*glGenerateMipmap_PROC)(int unsigned Target);
	typedef void(*glGenFramebuffers_PROC)(int unsigned Num, int unsigned* FrameBuffers);
	typedef void(*glBindFramebuffer_PROC)(int unsigned Target, int unsigned FrameBuffer);
	typedef void(*glFramebufferParameteri_PROC)(int unsigned Target, int unsigned ParamName, int Param);
	typedef void(*glFramebufferTexture2D_PROC)(int unsigned Target, int unsigned Attachment, int unsigned TexureTarget, int unsigned Texture, int Level);
	typedef void(*glDrawBuffers_PROC)(int unsigned Num, int unsigned const* Buffers);
	typedef void(*glDeleteFramebuffers_PROC)(int unsigned Num, int unsigned const* FrameBuffers);

#ifdef FAST_GL_IMPLEMENTATION
	glDebugMessageCallback_PROC glDebugMessageCallback = 0;
	glGetQueryObjectui64v_PROC glGetQueryObjectui64v = 0;
	glGenQueries_PROC glGenQueries = 0;
	glBeginQuery_PROC glBeginQuery = 0;
	glEndQuery_PROC glEndQuery = 0;
	glDeleteQueries_PROC glDeleteQueries = 0;
	glClearBufferfv_PROC glClearBufferfv = 0;
	glClearBufferiv_PROC glClearBufferiv = 0;
	glBlendFunci_PROC glBlendFunci = 0;
	glBlendEquation_PROC glBlendEquation = 0;
	glMemoryBarrier_PROC glMemoryBarrier = 0;
	glDrawElementsInstanced_PROC glDrawElementsInstanced = 0;
	glDrawArraysInstanced_PROC glDrawArraysInstanced = 0;
	glCreateProgram_PROC glCreateProgram = 0;
	glCreateShader_PROC glCreateShader = 0;
	glShaderSource_PROC glShaderSource = 0;
	glCompileShader_PROC glCompileShader = 0;
	glAttachShader_PROC glAttachShader = 0;
	glLinkProgram_PROC glLinkProgram = 0;
	glDeleteShader_PROC glDeleteShader = 0;
	glUseProgram_PROC glUseProgram = 0;
	glDeleteProgram_PROC glDeleteProgram = 0;
	glGetUniformLocation_PROC glGetUniformLocation = 0;
	glUniform1i_PROC glUniform1i = 0;
	glUniform1ui_PROC glUniform1ui = 0;
	glUniform1f_PROC glUniform1f = 0;
	glUniform2fv_PROC glUniform2fv = 0;
	glUniform3fv_PROC glUniform3fv = 0;
	glUniform4fv_PROC glUniform4fv = 0;
	glUniformMatrix4fv_PROC glUniformMatrix4fv = 0;
	glDispatchCompute_PROC glDispatchCompute = 0;
	glGetShaderiv_PROC glGetShaderiv = 0;
	glGetShaderInfoLog_PROC glGetShaderInfoLog = 0;
	glGetProgramiv_PROC glGetProgramiv = 0;
	glGetProgramInfoLog_PROC glGetProgramInfoLog = 0;
	glGenVertexArrays_PROC glGenVertexArrays = 0;
	glDeleteVertexArrays_PROC glDeleteVertexArrays = 0;
	glBindVertexArray_PROC glBindVertexArray = 0;
	glEnableVertexAttribArray_PROC glEnableVertexAttribArray = 0;
	glVertexAttribDivisor_PROC glVertexAttribDivisor = 0;
	glVertexAttribPointer_PROC glVertexAttribPointer = 0;
	glVertexAttribIPointer_PROC glVertexAttribIPointer = 0;
	glGenBuffers_PROC glGenBuffers = 0;
	glBindBuffer_PROC glBindBuffer = 0;
	glBufferData_PROC glBufferData = 0;
	glBufferStorage_PROC glBufferStorage = 0;
	glDeleteBuffers_PROC glDeleteBuffers = 0;
	glBufferSubData_PROC glBufferSubData = 0;
	glGetBufferSubData_PROC glGetBufferSubData = 0;
	glBindBufferBase_PROC glBindBufferBase = 0;
	glMapBuffer_PROC glMapBuffer = 0;
	glMapBufferRange_PROC glMapBufferRange = 0;
	glUnmapBuffer_PROC glUnmapBuffer = 0;
	glBindTextureUnit_PROC glBindTextureUnit = 0;
	glBindImageTexture_PROC glBindImageTexture = 0;
	glGenerateMipmap_PROC glGenerateMipmap = 0;
	glGenFramebuffers_PROC glGenFramebuffers = 0;
	glBindFramebuffer_PROC glBindFramebuffer = 0;
	glFramebufferParameteri_PROC glFramebufferParameteri = 0;
	glFramebufferTexture2D_PROC glFramebufferTexture2D = 0;
	glDrawBuffers_PROC glDrawBuffers = 0;
	glDeleteFramebuffers_PROC glDeleteFramebuffers = 0;
#else
	extern glDebugMessageCallback_PROC glDebugMessageCallback;
	extern glGetQueryObjectui64v_PROC glGetQueryObjectui64v;
	extern glGenQueries_PROC glGenQueries;
	extern glBeginQuery_PROC glBeginQuery;
	extern glEndQuery_PROC glEndQuery;
	extern glDeleteQueries_PROC glDeleteQueries;
	extern glClearBufferfv_PROC glClearBufferfv;
	extern glClearBufferiv_PROC glClearBufferiv;
	extern glBlendFunci_PROC glBlendFunci;
	extern glBlendEquation_PROC glBlendEquation;
	extern glMemoryBarrier_PROC glMemoryBarrier;
	extern glDrawElementsInstanced_PROC glDrawElementsInstanced;
	extern glDrawArraysInstanced_PROC glDrawArraysInstanced;
	extern glCreateProgram_PROC glCreateProgram;
	extern glCreateShader_PROC glCreateShader;
	extern glShaderSource_PROC glShaderSource;
	extern glCompileShader_PROC glCompileShader;
	extern glAttachShader_PROC glAttachShader;
	extern glLinkProgram_PROC glLinkProgram;
	extern glDeleteShader_PROC glDeleteShader;
	extern glUseProgram_PROC glUseProgram;
	extern glDeleteProgram_PROC glDeleteProgram;
	extern glGetUniformLocation_PROC glGetUniformLocation;
	extern glUniform1i_PROC glUniform1i;
	extern glUniform1ui_PROC glUniform1ui;
	extern glUniform1f_PROC glUniform1f;
	extern glUniform2fv_PROC glUniform2fv;
	extern glUniform3fv_PROC glUniform3fv;
	extern glUniform4fv_PROC glUniform4fv;
	extern glUniformMatrix4fv_PROC glUniformMatrix4fv;
	extern glDispatchCompute_PROC glDispatchCompute;
	extern glGetShaderiv_PROC glGetShaderiv;
	extern glGetShaderInfoLog_PROC glGetShaderInfoLog;
	extern glGetProgramiv_PROC glGetProgramiv;
	extern glGetProgramInfoLog_PROC glGetProgramInfoLog;
	extern glGenVertexArrays_PROC glGenVertexArrays;
	extern glDeleteVertexArrays_PROC glDeleteVertexArrays;
	extern glBindVertexArray_PROC glBindVertexArray;
	extern glEnableVertexAttribArray_PROC glEnableVertexAttribArray;
	extern glVertexAttribDivisor_PROC glVertexAttribDivisor;
	extern glVertexAttribPointer_PROC glVertexAttribPointer;
	extern glVertexAttribIPointer_PROC glVertexAttribIPointer;
	extern glGenBuffers_PROC glGenBuffers;
	extern glBindBuffer_PROC glBindBuffer;
	extern glBufferData_PROC glBufferData;
	extern glBufferStorage_PROC glBufferStorage;
	extern glDeleteBuffers_PROC glDeleteBuffers;
	extern glBufferSubData_PROC glBufferSubData;
	extern glGetBufferSubData_PROC glGetBufferSubData;
	extern glBindBufferBase_PROC glBindBufferBase;
	extern glMapBuffer_PROC glMapBuffer;
	extern glMapBufferRange_PROC glMapBufferRange;
	extern glUnmapBuffer_PROC glUnmapBuffer;
	extern glBindTextureUnit_PROC glBindTextureUnit;
	extern glBindImageTexture_PROC glBindImageTexture;
	extern glGenerateMipmap_PROC glGenerateMipmap;
	extern glGenFramebuffers_PROC glGenFramebuffers;
	extern glBindFramebuffer_PROC glBindFramebuffer;
	extern glFramebufferParameteri_PROC glFramebufferParameteri;
	extern glFramebufferTexture2D_PROC glFramebufferTexture2D;
	extern glDrawBuffers_PROC glDrawBuffers;
	extern glDeleteFramebuffers_PROC glDeleteFramebuffers;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Memory Definition
	///////////////////////////////////////////////////////////////

	extern void* Memory_Alloc(long long unsigned Size, void const* Reference);
	extern void* Memory_Realloc(void* Block, long long unsigned Size);
	extern void Memory_Free(void* Block);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedBytes = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Math Definition
	///////////////////////////////////////////////////////////////

#define VECTOR2_ZERO { .X = 0.0F, .Y = 0.0F }
#define VECTOR3_ZERO { .X = 0.0F, .Y = 0.0F, .Z = 0.0F }
#define VECTOR4_ZERO { .X = 0.0F, .Y = 0.0F, .Z = 0.0F, .W = 0.0F }

#define VECTOR2_ONE { .X = 1.0F, .Y = 1.0F }
#define VECTOR3_ONE { .X = 1.0F, .Y = 1.0F, .Z = 1.0F }
#define VECTOR4_ONE { .X = 1.0F, .Y = 1.0F, .Z = 1.0F, .W = 1.0F }

#define VECTOR3_RIGHT { .X = 1.0F, .Y = 0.0F, .Z = 0.0F }
#define VECTOR3_UP { .X = 0.0F, .Y = 1.0F, .Z = 0.0F }
#define VECTOR3_FORWARD { .X = 0.0F, .Y = 0.0F, .Z = 1.0F }
#define VECTOR3_LEFT { .X = -1.0F, .Y = 0.0F, .Z = 0.0F }
#define VECTOR3_DOWN { .X = 0.0F, .Y = -1.0F, .Z = 0.0F }
#define VECTOR3_BACK { .X = 0.0F, .Y = 0.0F, .Z = -1.0F }

#define COLOR2_ZERO { .R = 0.0F, .G = 0.0F }
#define COLOR3_ZERO { .R = 0.0F, .G = 0.0F, .B = 0.0F }
#define COLOR4_ZERO { .R = 0.0F, .G = 0.0F, .B = 0.0F, .A = 0.0F }

#define QUATERNION_ZERO { .X = 0.0F, .Y = 0.0F, .Z = 0.0F, .W = 0.0F }
#define QUATERNION_IDENTITY { .X = 0.0F, .Y = 0.0F, .Z = 0.0F, .W = 1.0F }

#define RECT_ZERO { .Left = 0.0F, .Right = 0.0F, .Top = 0.0F, .Bottom = 0.0F }

#define MATRIX2X2_ZERO \
{ \
	.M00 = 0.0F, .M01 = 0.0F, \
	.M10 = 0.0F, .M11 = 0.0F, \
}
#define MATRIX3X3_ZERO \
{ \
	.M00 = 0.0F, .M01 = 0.0F, .M02 = 0.0F, \
	.M10 = 0.0F, .M11 = 0.0F, .M12 = 0.0F, \
	.M20 = 0.0F, .M21 = 0.0F, .M22 = 0.0F, \
}
#define MATRIX4X4_ZERO \
{ \
	.M00 = 0.0F, .M01 = 0.0F, .M02 = 0.0F, .M03 = 0.0F, \
	.M10 = 0.0F, .M11 = 0.0F, .M12 = 0.0F, .M13 = 0.0F, \
	.M20 = 0.0F, .M21 = 0.0F, .M22 = 0.0F, .M23 = 0.0F, \
	.M30 = 0.0F, .M31 = 0.0F, .M32 = 0.0F, .M33 = 0.0F, \
}

#define MATRIX2X2_IDENTITY \
{ \
	.M00 = 1.0F, .M01 = 0.0F, \
	.M10 = 0.0F, .M11 = 1.0F, \
}
#define MATRIX3X3_IDENTITY \
{ \
	.M00 = 1.0F, .M01 = 0.0F, .M02 = 0.0F, \
	.M10 = 0.0F, .M11 = 1.0F, .M12 = 0.0F, \
	.M20 = 0.0F, .M21 = 0.0F, .M22 = 1.0F, \
}
#define MATRIX4X4_IDENTITY \
{ \
	.M00 = 1.0F, .M01 = 0.0F, .M02 = 0.0F, .M03 = 0.0F, \
	.M10 = 0.0F, .M11 = 1.0F, .M12 = 0.0F, .M13 = 0.0F, \
	.M20 = 0.0F, .M21 = 0.0F, .M22 = 1.0F, .M23 = 0.0F, \
	.M30 = 0.0F, .M31 = 0.0F, .M32 = 0.0F, .M33 = 1.0F, \
}

	typedef union _Vector2
	{
		struct
		{
			float X;
			float Y;
		};
		float Data[2];
	} Vector2;
	typedef union _Color2
	{
		struct
		{
			float R;
			float G;
		};
		float Data[2];
	} Color2;
	typedef union _Vector3
	{
		struct
		{
			float X;
			float Y;
			float Z;
		};
		float Data[3];
	} Vector3;
	typedef union _Color3
	{
		struct
		{
			float R;
			float G;
			float B;
		};
		float Data[3];
	} Color3;
	typedef union _Vector4
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float Data[4];
	} Vector4;
	typedef union _Color4
	{
		struct
		{
			float R;
			float G;
			float B;
			float A;
		};
		float Data[4];
	} Color4;
	typedef union _Quaternion
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float Data[4];
	} Quaternion;
	typedef union _Rect
	{
		struct
		{
			float Left;
			float Right;
			float Top;
			float Bottom;
		};
		float Data[4];
	} Rect;
	typedef union _Matrix2x2
	{
		struct
		{
			float M00, M01;
			float M10, M11;
		};
		float Data[2 * 2];
	} Matrix2x2;
	typedef union _Matrix3x3
	{
		struct
		{
			float M00, M01, M02;
			float M10, M11, M12;
			float M20, M21, M22;
		};
		float Data[3 * 3];
	} Matrix3x3;
	typedef union _Matrix4x4
	{
		struct
		{
			float M00, M01, M02, M03;
			float M10, M11, M12, M13;
			float M20, M21, M22, M23;
			float M30, M31, M32, M33;
		};
		float Data[4 * 4];
	} Matrix4x4;

	extern void Vector2_Zero(Vector2* Result);
	extern void Vector2_Set(Vector2* const Value, Vector2* Result);
	extern void Vector2_SetSimple(float X, float Y, Vector2* Result);
	extern void Vector2_Add(Vector2* const A, Vector2* const B, Vector2* Result);
	extern void Vector2_Sub(Vector2* const A, Vector2* const B, Vector2* Result);
	extern void Vector2_Mul(Vector2* const A, Vector2* const B, Vector2* Result);
	extern void Vector2_Div(Vector2* const A, Vector2* const B, Vector2* Result);
	extern void Vector2_AddScalar(Vector2* const Value, float Scalar, Vector2* Result);
	extern void Vector2_SubScalar(Vector2* const Value, float Scalar, Vector2* Result);
	extern void Vector2_MulScalar(Vector2* const Value, float Scalar, Vector2* Result);
	extern void Vector2_DivScalar(Vector2* const Value, float Scalar, Vector2* Result);
	extern void Vector2_MulAdd(Vector2* const Value, float Scalar, Vector2* Result);
	extern float Vector2_Dot(Vector2* const A, Vector2* const B);
	extern float Vector2_Length(Vector2* const Value);
	extern float Vector2_Length2(Vector2* const Value);
	extern void Vector2_Print(Vector2* const Value);

	extern void Vector3_Zero(Vector3* Result);
	extern void Vector3_Set(Vector3* const Value, Vector3* Result);
	extern void Vector3_SetSimple(float X, float Y, float Z, Vector3* Result);
	extern void Vector3_Add(Vector3* const A, Vector3* const B, Vector3* Result);
	extern void Vector3_Sub(Vector3* const A, Vector3* const B, Vector3* Result);
	extern void Vector3_Mul(Vector3* const A, Vector3* const B, Vector3* Result);
	extern void Vector3_Div(Vector3* const A, Vector3* const B, Vector3* Result);
	extern void Vector3_AddScalar(Vector3* const Value, float Scalar, Vector3* Result);
	extern void Vector3_SubScalar(Vector3* const Value, float Scalar, Vector3* Result);
	extern void Vector3_MulScalar(Vector3* const Value, float Scalar, Vector3* Result);
	extern void Vector3_DivScalar(Vector3* const Value, float Scalar, Vector3* Result);
	extern void Vector3_MulAdd(Vector3* const Value, float Scalar, Vector3* Result);
	extern void Vector3_Norm(Vector3* const Value, Vector3* Result);
	extern float Vector3_Dot(Vector3* const A, Vector3* const B);
	extern float Vector3_Length(Vector3* const Value);
	extern float Vector3_Length2(Vector3* const Value);
	extern void Vector3_Cross(Vector3* const A, Vector3* const B, Vector3* Result);
	extern void Vector3_Rotate(Vector3* const Value, Quaternion* const Rotation, Vector3* Result);
	extern void Vector3_Print(Vector3* const Value);

	extern void Vector4_Zero(Vector4* Result);
	extern void Vector4_Set(Vector4* const Value, Vector4* Result);
	extern void Vector4_SetSimple(float X, float Y, float Z, float W, Vector4* Result);
	extern void Vector4_Add(Vector4* const A, Vector4* const B, Vector4* Result);
	extern void Vector4_Sub(Vector4* const A, Vector4* const B, Vector4* Result);
	extern void Vector4_Mul(Vector4* const A, Vector4* const B, Vector4* Result);
	extern void Vector4_Div(Vector4* const A, Vector4* const B, Vector4* Result);
	extern void Vector4_AddScalar(Vector4* const Value, float Scalar, Vector4* Result);
	extern void Vector4_SubScalar(Vector4* const Value, float Scalar, Vector4* Result);
	extern void Vector4_MulScalar(Vector4* const Value, float Scalar, Vector4* Result);
	extern void Vector4_DivScalar(Vector4* const Value, float Scalar, Vector4* Result);
	extern void Vector4_MulAdd(Vector4* const Value, float Scalar, Vector4* Result);
	extern void Vector4_Print(Vector4* const Value);

	extern void Quaternion_Zero(Quaternion* Result);
	extern void Quaternion_Identity(Quaternion* Result);
	extern void Quaternion_Set(Quaternion* const Value, Quaternion* Result);
	extern void Quaternion_SetSimple(float X, float Y, float Z, float W, Quaternion* Result);
	extern void Quaternion_Mul(Quaternion* const A, Quaternion* const B, Quaternion* Result);
	extern void Quaternion_MulScalar(Quaternion* const Value, float Scalar, Quaternion* Result);
	extern void Quaternion_Conjugate(Quaternion* const Value, Quaternion* Result);
	extern void Quaternion_EulerAngles(Quaternion* const Value, Vector3* Result);
	extern void Quaternion_AngleAxis(float Angle, Vector3* const Axis, Quaternion* Result);
	extern void Quaternion_Norm(Quaternion* const Value, Quaternion* Result);
	extern void Quaternion_Print(Quaternion* const Value);

	extern void Rect_Zero(Rect* Result);
	extern void Rect_Set(Rect const* Value, Rect* Result);
	extern void Rect_SetSimple(float Left, float Right, float Top, float Bottom, Rect* Result);
	extern void Rect_SetPosition(float PositionX, float PositionY, Rect* Result);
	extern void Rect_SetSize(float SizeX, float SizeY, Rect* Result);
	extern float Rect_PositionX(Rect const* Value);
	extern float Rect_PositionZ(Rect const* Value);
	extern float Rect_Width(Rect const* Value);
	extern float Rect_Height(Rect const* Value);
	extern bool Rect_Overlap(Rect const* Value, float PositionX, float PositionY);
	extern void Rect_Print(Rect const* Value);

	extern void Matrix4x4_Set(Matrix4x4* const Value, Matrix4x4* Result);
	extern void Matrix4x4_Zero(Matrix4x4* Result);
	extern void Matrix4x4_One(Matrix4x4* Result);
	extern void Matrix4x4_Identity(Matrix4x4* Result);
	extern void Matrix4x4_GetPosition(Matrix4x4* const Value, Vector3* Result);
	extern void Matrix4x4_GetRotation(Matrix4x4* const Value, Quaternion* Result);
	extern void Matrix4x4_GetRotationEulerAngles(Matrix4x4* const Value, Vector3* Result);
	extern void Matrix4x4_GetScale(Matrix4x4* const Value, Vector3* Result);
	extern void Matrix4x4_SetPosition(Vector3* const Value, Matrix4x4* Result);
	extern void Matrix4x4_SetPositionSimple(float ValueX, float ValueY, float ValueZ, Matrix4x4* Result);
	extern void Matrix4x4_SetRotation(Quaternion* const Value, Matrix4x4* Result);
	extern void Matrix4x4_SetRotationSimple(float ValueX, float ValueY, float ValueZ, float ValueW, Matrix4x4* Result);
	extern void Matrix4x4_SetRotationEulerAngles(Vector3* const Value, Matrix4x4* Result);
	extern void Matrix4x4_SetRotationEulerAnglesSimple(float Pitch, float Yaw, float Roll, Matrix4x4* Result);
	extern void Matrix4x4_SetScale(Vector3* const Value, Matrix4x4* Result);
	extern void Matrix4x4_SetScaleSimple(float ValueX, float ValueY, float ValueZ, Matrix4x4* Result);
	extern void Matrix4x4_Decompose(Matrix4x4* const Value, Vector3* Position, Quaternion* Rotation, Vector3* Scale);
	extern void Matrix4x4_Mul(Matrix4x4* const A, Matrix4x4* const B, Matrix4x4* Result);
	extern void Matrix4x4_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, Matrix4x4* Result);
	extern void Matrix4x4_Perspective(float FieldOfView, float AspectRatio, float NearZ, float FarZ, Matrix4x4* Result);
	extern void Matrix4x4_LookAt(Vector3* const Eye, Vector3* const Center, Vector3* const Up, Matrix4x4* Result);
	extern void Matrix4x4_Print(Matrix4x4* const Value);

	extern float Math_StepTowards(float Current, float Target, float Step);

	///////////////////////////////////////////////////////////////
	// List Definition
	///////////////////////////////////////////////////////////////

#define LIST_FIRST_ENTRY(LIST) ((LIST).Next)
#define LIST_LAST_ENTRY(LIST) ((LIST).Prev)

	typedef struct _ListEntry
	{
		struct _ListEntry* Next;
		struct _ListEntry* Prev;
	} ListEntry;

	extern void List_InitHead(ListEntry* List);
	extern void List_InsertTail(ListEntry* List, ListEntry* Entry);
	extern void List_InsertAfter(ListEntry* Curr, ListEntry* Entry);
	extern void List_InsertBefore(ListEntry* Curr, ListEntry* Entry);
	extern void List_Remove(ListEntry* Entry);
	extern ListEntry* List_RemoveHead(ListEntry* List);
	extern bool List_IsEmpty(ListEntry* List);
	extern long long unsigned List_Num(ListEntry* List);

	///////////////////////////////////////////////////////////////
	// Vector Definition
	///////////////////////////////////////////////////////////////

#ifndef FAST_GL_VECTOR_INITIAL_CAPACITY
#define FAST_GL_VECTOR_INITIAL_CAPACITY (16ULL)
#endif // FAST_GL_VECTOR_INITIAL_CAPACITY

	typedef struct _Vector
	{
		char unsigned* Buffer;
		long long unsigned ValueSize;
		long long unsigned BufferSize;
		long long unsigned BufferNum;
		long long unsigned BufferIndex;
		long long unsigned BufferOffset;
	} Vector;

	extern void Vector_Alloc(Vector* Vtor, long long unsigned ValueSize);
	extern void Vector_Push(Vector* Vtor, void* Item);
	extern void Vector_Pop(Vector* Vtor, void* Item);
	extern void Vector_Resize(Vector* Vtor, long long unsigned Num);
	extern void Vector_Clear(Vector* Vtor);
	extern void* Vector_At(Vector* Vtor, long long unsigned Index);
	extern void* Vector_Buffer(Vector* Vtor);
	extern bool Vector_Empty(Vector* Vtor);
	extern long long unsigned Vector_Num(Vector* Vtor);
	extern long long unsigned Vector_Size(Vector* Vtor);
	extern void Vector_Free(Vector* Vtor);

	extern void Vector_ExpandInternal(Vector* Vtor);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedVectors = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// HashMap Definition
	///////////////////////////////////////////////////////////////

#ifndef FAST_GL_HASH_MAP_INITIAL_CAPACITY
#define FAST_GL_HASH_MAP_INITIAL_CAPACITY (128ULL)
#endif // FAST_GL_HASH_MAP_INITIAL_CAPACITY

#ifndef FAST_GL_HASH_MAP_INITIAL_HASH
#define FAST_GL_HASH_MAP_INITIAL_HASH (5381ULL)
#endif // FAST_GL_HASH_MAP_INITIAL_HASH

#ifndef FAST_GL_HASH_MAP_LOAD_FACTOR
#define FAST_GL_HASH_MAP_LOAD_FACTOR (0.75F)
#endif // FAST_GL_HASH_MAP_LOAD_FACTOR

	typedef struct _HashMapPair
	{
		struct _HashMapPair* Next;
		void* Key;
		void* Value;
		long long unsigned KeySize;
		long long unsigned ValueSize;
	} HashMapPair;
	typedef struct _HashMap
	{
		HashMapPair** Table;
		long long unsigned TableSize;
		long long unsigned TableCount;
	} HashMap;

	extern void HashMap_Alloc(HashMap* Map);
	extern void HashMap_Insert(HashMap* Map, void const* Key, long long unsigned KeySize, void const* Value, long long unsigned KeyValue);
	extern void HashMap_InsertSimple(HashMap* Map, char const* Key, void const* Value, long long unsigned KeyValue);
	extern void HashMap_Remove(HashMap* Map, void const* Key, long long unsigned KeySize);
	extern void HashMap_RemoveSimple(HashMap* Map, char const* Key);
	extern void* HashMap_At(HashMap* Map, void const* Key, long long unsigned KeySize);
	extern void* HashMap_AtSimple(HashMap* Map, char const* Key);
	extern void HashMap_Free(HashMap* Map);

	extern HashMapPair* HashMap_PairAllocInternal(void const* Key, long long unsigned KeySize, void const* Value, long long unsigned ValueSize);
	extern long long unsigned HashMap_ComputeHashInternal(char* Key, long long unsigned Modulus);
	extern void HashMap_ResizeInternal(HashMap* Map);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedHashMaps = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// FileSystem Definition
	///////////////////////////////////////////////////////////////

	extern void FileSystem_ReadText(char** Buffer, int unsigned* BufferSize, char const* FilePath);
	extern void FileSystem_ReadBinary(char unsigned** Buffer, int unsigned* BufferSize, char const* FilePath);
	extern void FileSystem_WriteText(char const* Buffer, int unsigned BufferSize, char const* FilePath);
	extern void FileSystem_WriteBinary(char unsigned const* Buffer, int unsigned BufferSize, char const* FilePath);

	///////////////////////////////////////////////////////////////
	// FileReader Definition
	///////////////////////////////////////////////////////////////

	typedef struct _FileReader
	{
		char unsigned const* Buffer;
		int unsigned BufferSize;
		int unsigned BufferOffset;
	} FileReader;

	extern void FileReader_Alloc(FileReader* Reader, char unsigned const* Buffer, int unsigned BufferSize);
	extern void FileReader_SeekAbs(FileReader* Reader, int unsigned Offset);
	extern void FileReader_SeekRel(FileReader* Reader, int Offset);
	extern int unsigned FileReader_Offset(FileReader* Reader);
	extern char FileReader_ReadInt8(FileReader* Reader);
	extern char unsigned FileReader_ReadUInt8(FileReader* Reader);
	extern short FileReader_ReadInt16(FileReader* Reader, bool BigEndian);
	extern short unsigned FileReader_ReadUInt16(FileReader* Reader, bool BigEndian);
	extern int FileReader_ReadInt32(FileReader* Reader, bool BigEndian);
	extern int unsigned FileReader_ReadUInt32(FileReader* Reader, bool BigEndian);
	extern long long FileReader_ReadInt64(FileReader* Reader, bool BigEndian);
	extern long long unsigned FileReader_ReadUInt64(FileReader* Reader, bool BigEndian);
	extern void FileReader_ReadInt8Array(FileReader* Reader, char* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt8Array(FileReader* Reader, char unsigned* Values, int unsigned NumValues);
	extern void FileReader_ReadInt16Array(FileReader* Reader, bool BigEndian, short* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt16Array(FileReader* Reader, bool BigEndian, short unsigned* Values, int unsigned NumValues);
	extern void FileReader_ReadInt32Array(FileReader* Reader, bool BigEndian, int* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt32Array(FileReader* Reader, bool BigEndian, int unsigned* Values, int unsigned NumValues);
	extern void FileReader_ReadInt64Array(FileReader* Reader, bool BigEndian, long long* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt64Array(FileReader* Reader, bool BigEndian, long long unsigned* Values, int unsigned NumValues);

	///////////////////////////////////////////////////////////////
	// Random Definition
	///////////////////////////////////////////////////////////////

	extern void Random_Seed(char const* Seed);
	extern char Random_Int8(void);
	extern short Random_Int16(void);
	extern int Random_Int32(void);
	extern long long Random_Int64(void);
	extern char Random_Int8Between(char Min, char Max);
	extern short Random_Int16Between(short Min, short Max);
	extern int Random_Int32Between(int Min, int Max);
	extern long long Random_Int64Between(long long Min, long long Max);
	extern char unsigned Random_UInt8(void);
	extern short unsigned Random_UInt16(void);
	extern int unsigned Random_UInt32(void);
	extern long long unsigned Random_UInt64(void);
	extern char unsigned Random_UInt8Between(char unsigned Min, char unsigned Max);
	extern short unsigned Random_UInt16Between(short unsigned Min, short unsigned Max);
	extern int unsigned Random_UInt32Between(int unsigned Min, int unsigned Max);
	extern long long unsigned Random_UInt64Between(long long unsigned Min, long long unsigned Max);
	extern float Random_Real32(void);
	extern double Random_Real64(void);
	extern float Random_Real32Between(float Min, float Max);
	extern double Random_Real64Between(double Min, double Max);

	///////////////////////////////////////////////////////////////
	// Timer Definition
	///////////////////////////////////////////////////////////////

	typedef enum _TimerType
	{
		TIMER_TYPE_CPU,
		TIMER_TYPE_GPU,
	} TimerType;
	typedef struct _Timer
	{
		TimerType Type;
		int unsigned ComputeQuery;
		double Frequency;
		double StartNanoTime;
		double EndNanoTime;
		double ElapsedNanoTime;
	} Timer;

	extern void Timer_CpuAlloc(Timer* Timr);
	extern void Timer_GpuAlloc(Timer* Timr);
	extern void Timer_BeginMeasure(Timer* Timr);
	extern void Timer_EndMeasure(Timer* Timr);
	extern double Timer_ElapsedNanoSeconds(Timer* Timr);
	extern void Timer_Free(Timer* Timr);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedTimers = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Transform Definition
	///////////////////////////////////////////////////////////////

	typedef struct _Transform
	{
		struct _Transform* Parent;
		Vector3 LocalRight;
		Vector3 LocalUp;
		Vector3 LocalForward;
		Vector3 LocalLeft;
		Vector3 LocalDown;
		Vector3 LocalBack;
		Vector3 LocalPosition;
		Quaternion LocalRotation;
		Vector3 LocalScale;
		Vector3 WorldPosition;
		Quaternion WorldRotation;
		Vector3 WorldScale;
	} Transform;

	extern void Transform_Init(Transform* Trans);
	extern void Transform_GetWorldPosition(Transform* Trans, Vector3* Position);
	extern void Transform_GetWorldRotation(Transform* Trans, Quaternion* Rotation);
	extern void Transform_GetWorldEulerAngles(Transform* Trans, Vector3* Rotation);
	extern void Transform_GetWorldScale(Transform* Trans, Vector3* Scale);
	extern void Transform_GetLocalPosition(Transform* Trans, Vector3* Position);
	extern void Transform_GetLocalRotation(Transform* Trans, Quaternion* Rotation);
	extern void Transform_GetLocalEulerAngles(Transform* Trans, Vector3* Rotation);
	extern void Transform_GetLocalScale(Transform* Trans, Vector3* Scale);
	extern void Transform_SetPosition(Transform* Trans, Vector3 const* Position);
	extern void Transform_SetPositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ);
	extern void Transform_SetRelativePosition(Transform* Trans, Vector3 const* Position);
	extern void Transform_SetRelativePositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ);
	extern void Transform_SetRotation(Transform* Trans, Quaternion const* Rotation);
	extern void Transform_SetRotationSimple(Transform* Trans, float RotationX, float RotationY, float RotationZ, float RotationW);
	extern void Transform_SetRelativeRotation(Transform* Trans, Quaternion const* Rotation);
	extern void Transform_SetRelativeRotationSimple(Transform* Trans, float RotationX, float RotationY, float RotationZ, float RotationW);
	extern void Transform_SetEulerAngles(Transform* Trans, Vector3 const* Rotation);
	extern void Transform_SetEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll);
	extern void Transform_SetRelativeEulerAngles(Transform* Trans, Vector3 const* Rotation);
	extern void Transform_SetRelativeEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll);
	extern void Transform_SetScale(Transform* Trans, Vector3 const* Scale);
	extern void Transform_SetScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ);
	extern void Transform_SetRelativeScale(Transform* Trans, Vector3 const* Scale);
	extern void Transform_SetRelativeScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ);
	extern void Transform_ComputeModelMatrix(Transform* Trans, Matrix4x4* Model);

	extern void Transform_ComputeWorldPositionInternal(Transform* Trans);
	extern void Transform_ComputeWorldRotationInternal(Transform* Trans);
	extern void Transform_ComputeWorldScaleInternal(Transform* Trans);

#ifdef FAST_GL_IMPLEMENTATION
	static Vector3 sWorldRight = VECTOR3_RIGHT;
	static Vector3 sWorldUp = VECTOR3_UP;
	static Vector3 sWorldForward = VECTOR3_FORWARD;
	static Vector3 sWorldLeft = VECTOR3_LEFT;
	static Vector3 sWorldDown = VECTOR3_DOWN;
	static Vector3 sWorldBack = VECTOR3_BACK;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Controller Definition
	///////////////////////////////////////////////////////////////

	typedef struct _FirstPersonController
	{
		Transform Transform;
		float KeyboardMovementSpeed;
		float MouseMovementSpeed;
		float MouseRotationSpeed;
		float RollSpeed;
		float MouseDrag;
		Vector2 MousePositionStart;
		Vector2 MousePositionEnd;
	} FirstPersonController;
	typedef struct _OrbitController
	{
		Transform Transform;
		float KeyboardMovementSpeed;
		float MouseMovementSpeed;
		float MouseRotationSpeed;
		float MouseDrag;
		float Distance;
		Vector2 MousePositionStart;
		Vector2 MousePositionEnd;
	} OrbitController;

	extern void Controller_FirstPersonAlloc(FirstPersonController* Controller);
	extern void Controller_OrbitAlloc(OrbitController* Controller);
	extern void Controller_UpdateFirstPerson(FirstPersonController* Controller, float DeltaTime);
	extern void Controller_UpdateOrbit(OrbitController* Controller, float DeltaTime);
	extern void Controller_ComputeFirstPersonViewMatrix(FirstPersonController* Controller, Matrix4x4* View);
	extern void Controller_ComputeOrbitViewMatrix(OrbitController* Controller, Matrix4x4* View);

	///////////////////////////////////////////////////////////////
	// Shader Definition
	///////////////////////////////////////////////////////////////

	extern void Shader_VertexFragmentAlloc(int unsigned* Program, char const* VertexSource, char const* FragmentSource);
	extern void Shader_VertexGeometryFragmentAlloc(int unsigned* Program, char const* VertexSource, const char* GeometrySource, char const* FragmentSource);
	extern void Shader_ComputeAlloc(int unsigned* Program, char const* ComputeSource);
	extern void Shader_Bind(int unsigned Program);
	extern void Shader_SetUniformInt32(int unsigned Program, char const* UniformName, int Value);
	extern void Shader_SetUniformUInt32(int unsigned Program, char const* UniformName, int unsigned Value);
	extern void Shader_SetUniformReal32(int unsigned Program, char const* UniformName, float Value);
	extern void Shader_SetUniformVector2(int unsigned Program, char const* UniformName, Vector2 const* Value);
	extern void Shader_SetUniformVector3(int unsigned Program, char const* UniformName, Vector3 const* Value);
	extern void Shader_SetUniformVector4(int unsigned Program, char const* UniformName, Vector4 const* Value);
	extern void Shader_SetUniformMatrix4(int unsigned Program, char const* UniformName, Matrix4x4 const* Value);
	extern void Shader_ExecuteCompute(int unsigned NumGroupsX, int unsigned NumGroupsY, int unsigned NumGroupsZ);
	extern void Shader_CheckCompileStatus(int unsigned Shader);
	extern void Shader_CheckLinkStatus(int unsigned Program);
	extern void Shader_Free(int unsigned Program);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedPrograms = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// VertexArray Definition
	///////////////////////////////////////////////////////////////

	extern void VertexArray_Alloc(int unsigned* VertexArray);
	extern void VertexArray_Bind(int unsigned VertexArray);
	extern void VertexArray_DrawPoints(int unsigned Count);
	extern void VertexArray_DrawPointsInstanced(int unsigned Count, int unsigned NumInstances);
	extern void VertexArray_DrawLines(int unsigned Count);
	extern void VertexArray_DrawLinesInstanced(int unsigned Count, int unsigned NumInstances);
	extern void VertexArray_DrawLineStrip(int unsigned Count);
	extern void VertexArray_DrawLineStripInstanced(int unsigned Count, int unsigned NumInstances);
	extern void VertexArray_DrawTriangles(int unsigned Count);
	extern void VertexArray_DrawTrianglesInstanced(int unsigned Count, int unsigned NumInstances);
	extern void VertexArray_DrawTriangleStrip(int unsigned Count);
	extern void VertexArray_DrawTriangleStripInstanced(int unsigned Count, int unsigned NumInstances);
	extern void VertexArray_UnBind(void);
	extern void VertexArray_Free(int unsigned VertexArray);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedVertexArrays = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Buffer Definition
	///////////////////////////////////////////////////////////////

	extern void Buffer_VertexAlloc(int unsigned* Buffer);
	extern void Buffer_IndexAlloc(int unsigned* Buffer);
	extern void Buffer_UniformAlloc(int unsigned* Buffer);
	extern void Buffer_StorageAlloc(int unsigned* Buffer);
	extern void Buffer_VertexAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_IndexAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_UniformAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_StorageAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_VertexBind(int unsigned Buffer);
	extern void Buffer_IndexBind(int unsigned Buffer);
	extern void Buffer_UniformBind(int unsigned Buffer);
	extern void Buffer_StorageBind(int unsigned Buffer);
	extern void Buffer_VertexUnBind(void);
	extern void Buffer_IndexUnBind(void);
	extern void Buffer_UniformUnBind(void);
	extern void Buffer_StorageUnBind(void);
	extern void Buffer_VertexResize(long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_IndexResize(long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_UniformResize(long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_StorageResize(long long unsigned Size, void* Data, int unsigned Usage);
	extern void Buffer_VertexEnableAttrib(int unsigned Index);
	extern void Buffer_VertexAttribPointerReal32(int unsigned Index, int unsigned Size, long long unsigned Stride, long long unsigned Offset);
	extern void Buffer_VertexAttribPointerUInt32(int unsigned Index, int unsigned Size, long long unsigned Stride, long long unsigned Offset);
	extern void Buffer_VertexAttribDivisor(int unsigned Index, int unsigned Divisor);
	extern void Buffer_VertexSetData(void const* Data, long long unsigned Size);
	extern void Buffer_IndexSetData(void const* Data, long long unsigned Size);
	extern void Buffer_UniformSetData(void const* Data, long long unsigned Size);
	extern void Buffer_StorageSetData(void const* Data, long long unsigned Size);
	extern void Buffer_VertexGetData(void* Data, long long unsigned Size);
	extern void Buffer_IndexGetData(void* Data, long long unsigned Size);
	extern void Buffer_UniformGetData(void* Data, long long unsigned Size);
	extern void Buffer_StorageGetData(void* Data, long long unsigned Size);
	extern void Buffer_VertexSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_IndexSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_UniformSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_StorageSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_VertexGetSubData(void* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_IndexGetSubData(void* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_UniformGetSubData(void* Data, long long unsigned Offset, long long unsigned Size);
	extern void Buffer_StorageGetSubData(void* Data, long long unsigned Offset, long long unsigned Size);
	extern void* Buffer_VertexMap(int unsigned Access);
	extern void* Buffer_IndexMap(int unsigned Access);
	extern void* Buffer_UniformMap(int unsigned Access);
	extern void* Buffer_StorageMap(int unsigned Access);
	extern void Buffer_VertexUnMap(void);
	extern void Buffer_IndexUnMap(void);
	extern void Buffer_UniformUnMap(void);
	extern void Buffer_StorageUnMap(void);
	extern void Buffer_VertexBeginBarrier(void);
	extern void Buffer_IndexBeginBarrier(void);
	extern void Buffer_UniformBeginBarrier(void);
	extern void Buffer_StorageBeginBarrier(void);
	extern void Buffer_EndBarrier(void);
	extern void Buffer_UniformMount(int unsigned Buffer, int unsigned Index);
	extern void Buffer_StorageMount(int unsigned Buffer, int unsigned Index);
	extern void Buffer_Free(int unsigned Buffer);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedBuffers = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Batch Definition
	///////////////////////////////////////////////////////////////

	typedef struct _BatchWorldCircleVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} BatchWorldCircleVertex;
	typedef struct _BatchWorldLineVertex
	{
		Vector3 Position;
		Vector3 Rotation;
		float Thickness;
		Color4 Color;
	} BatchWorldLineVertex;
	typedef struct _BatchWorldRectVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} BatchWorldRectVertex;
	typedef struct _BatchScreenCircleVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} BatchScreenCircleVertex;
	typedef struct _BatchScreenLineVertex
	{
		Vector3 Position;
		float Rotation;
		float Thickness;
		Color4 Color;
	} BatchScreenLineVertex;
	typedef struct _BatchScreenRectVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} BatchScreenRectVertex;
	typedef struct _BatchWorldCircleInstanceEntry
	{
		Vector3 Position;
		Vector3 Rotation;
		float Radius;
		Color4 Color;
	} BatchWorldCircleInstanceEntry;
	typedef struct _BatchWorldRectInstanceEntry
	{
		Vector3 Position;
		Vector3 Rotation;
		Vector2 Size;
		Color4 Color;
	} BatchWorldRectInstanceEntry;
	typedef struct _BatchScreenCircleInstanceEntry
	{
		Vector3 Position;
		float Rotation;
		float Radius;
		Color4 Color;
	} BatchScreenCircleInstanceEntry;
	typedef struct _BatchScreenRectInstanceEntry
	{
		Vector3 Position;
		float Rotation;
		Vector2 Size;
		Color4 Color;
	} BatchScreenRectInstanceEntry;
	typedef struct _Batch
	{
		int unsigned NumWorldCircles;
		int unsigned NumWorldLines;
		int unsigned NumWorldRects;
		int unsigned NumScreenCircles;
		int unsigned NumScreenLines;
		int unsigned NumScreenRects;
		int unsigned WorldCircleVertexArray;
		int unsigned WorldCircleVertexBuffer;
		int unsigned WorldCircleInstanceBuffer;
		int unsigned WorldCircleInstanceOffset;
		int unsigned WorldCircleIndexBuffer;
		int unsigned ScreenCircleVertexArray;
		int unsigned ScreenCircleVertexBuffer;
		int unsigned ScreenCircleInstanceBuffer;
		int unsigned ScreenCircleInstanceOffset;
		int unsigned ScreenCircleIndexBuffer;
		int unsigned WorldLineVertexArray;
		int unsigned WorldLineVertexBuffer;
		int unsigned WorldLineVertexOffset;
		int unsigned WorldLineIndexBuffer;
		int unsigned WorldLineIndexOffset;
		int unsigned ScreenLineVertexArray;
		int unsigned ScreenLineVertexBuffer;
		int unsigned ScreenLineVertexOffset;
		int unsigned ScreenLineIndexBuffer;
		int unsigned ScreenLineIndexOffset;
		int unsigned WorldRectVertexArray;
		int unsigned WorldRectVertexBuffer;
		int unsigned WorldRectInstanceBuffer;
		int unsigned WorldRectInstanceOffset;
		int unsigned WorldRectIndexBuffer;
		int unsigned ScreenRectVertexArray;
		int unsigned ScreenRectVertexBuffer;
		int unsigned ScreenRectInstanceBuffer;
		int unsigned ScreenRectInstanceOffset;
		int unsigned ScreenRectIndexBuffer;
	} Batch;

	extern void Batch_Alloc(Batch* Bat);
	extern void Batch_Free(Batch* Bat);

	extern void Batch_BeginWorldCircles(Batch* Bat);
	extern void Batch_DrawWorldCircle(Vector3 const* Position, Vector3 const* Rotation, float Radius, Color4 const* Color);
	extern void Batch_DrawWorldCircleSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float Radius, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_DrawWorldCircleGrid(Vector3 const* Position, Vector3 const* Rotation, int unsigned Num, float Scale, float Radius, Color4 const* Color);
	extern void Batch_DrawWorldCircleGridSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, int unsigned Num, float Scale, float Radius, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_EndWorldCircles(Matrix4x4 const* Projection, Matrix4x4 const* View);

	extern void Batch_BeginScreenCircles(Batch* Bat);
	extern void Batch_DrawScreenCircle(Vector3 const* Position, float Rotation, float Radius, Color4 const* Color);
	extern void Batch_DrawScreenCircleSimple(float PositionX, float PositionY, float PositionZ, float Rotation, float Radius, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_DrawScreenCircleGrid(Vector3 const* Position, float Rotation, int unsigned Num, float Scale, float Radius, Color4 const* Color);
	extern void Batch_DrawScreenCircleGridSimple(float PositionX, float PositionY, float PositionZ, float Rotation, int unsigned Num, float Scale, float Radius, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_EndScreenCircles(void);

	extern void Batch_BeginWorldLines(Batch* Bat);
	extern void Batch_DrawWorldLine(Vector3 const* From, Vector3 const* To, Vector3 const* Rotation, float Thickness, Color4 const* Color);
	extern void Batch_DrawWorldLineSimple(float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Pitch, float Yaw, float Roll, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_DrawWorldLineGrid(Vector3 const* Position, Vector3 const* Rotation, int unsigned Num, float Scale, float Thickness, Color4 const* Color);
	extern void Batch_DrawWorldLineGridSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, int unsigned Num, float Scale, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_EndWorldLines(Matrix4x4 const* Projection, Matrix4x4 const* View);

	extern void Batch_BeginScreenLines(Batch* Bat);
	extern void Batch_DrawScreenLine(Vector3 const* From, Vector3 const* To, float Rotation, float Thickness, Color4 const* Color);
	extern void Batch_DrawScreenLineSimple(float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Rotation, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_DrawScreenLineGrid(Vector3 const* Position, float Rotation, int unsigned Num, float Scale, float Thickness, Color4 const* Color);
	extern void Batch_DrawScreenLineGridSimple(float PositionX, float PositionY, float PositionZ, float Rotation, int unsigned Num, float Scale, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_EndScreenLines(void);

	extern void Batch_BeginWorldRects(Batch* Bat);
	extern void Batch_DrawWorldRect(Vector3 const* Position, Vector3 const* Rotation, Vector2 const* Size, Color4 const* Color);
	extern void Batch_DrawWorldRectSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_EndWorldRects(Matrix4x4 const* Projection, Matrix4x4 const* View);

	extern void Batch_BeginScreenRects(Batch* Bat);
	extern void Batch_DrawScreenRect(Vector3 const* Position, float Rotation, Vector2 const* Size, Color4 const* Color);
	extern void Batch_DrawScreenRectSimple(float PositionX, float PositionY, float PositionZ, float Rotation, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Batch_EndScreenRects(void);

#ifdef FAST_GL_IMPLEMENTATION
	static int unsigned sWorldCircleProgram = 0;
	static int unsigned sWorldLineProgram = 0;
	static int unsigned sWorldRectProgram = 0;
	static int unsigned sScreenCircleProgram = 0;
	static int unsigned sScreenLineProgram = 0;
	static int unsigned sScreenRectProgram = 0;
	static Batch* sCurrBatch = 0;
	static BatchWorldCircleInstanceEntry* sMappedWorldCircleInstanceBuffer = 0;
	static BatchWorldLineVertex* sMappedWorldLineVertexBuffer = 0;
	static int unsigned* sMappedWorldLineIndexBuffer = 0;
	static BatchWorldRectInstanceEntry* sMappedWorldRectInstanceBuffer = 0;
	static BatchScreenCircleInstanceEntry* sMappedScreenCircleInstanceBuffer = 0;
	static BatchScreenLineVertex* sMappedScreenLineVertexBuffer = 0;
	static int unsigned* sMappedScreenLineIndexBuffer = 0;
	static BatchScreenRectInstanceEntry* sMappedScreenRectInstanceBuffer = 0;
	static char const sWorldCircleVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"layout (location = 2) in vec3 InstancePosition;"
		"layout (location = 3) in vec3 InstanceRotation;"
		"layout (location = 4) in float InstanceRadius;"
		"layout (location = 5) in vec4 InstanceColor;"
		"out VS_OUT {"
		"	vec3 Position;"
		"	vec2 TextureCoords;"
		"	float Radius;"
		"	vec4 Color;"
		"} VertexOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec3 EulerAngles = radians(InstanceRotation);"
		"	vec4 Rotation = EulerAnglesToQuaternion(EulerAngles.x, EulerAngles.y, EulerAngles.z);"
		"	vec3 LocalPosition = RotateVector3D(vec3(VertexPosition, 0.0) * InstanceRadius, Rotation);"
		"	vec3 WorldPosition = RotateVector3D(InstancePosition , Rotation);"
		"	vec4 ViewPosition = ViewMatrix * vec4(WorldPosition + LocalPosition, 1.0);"
		"	vec4 ClipPosition = ProjectionMatrix * ViewPosition;"
		"	gl_Position = ClipPosition;"
		"	VertexOutput.Position = LocalPosition;"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"	VertexOutput.Radius = InstanceRadius;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sWorldCircleFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec3 Position;"
		"	vec2 TextureCoords;"
		"	float Radius;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	if (dot(FragmentInput.Position, FragmentInput.Position) > (FragmentInput.Radius * FragmentInput.Radius)) discard;"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sWorldLineVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec3 VertexPosition;"
		"layout (location = 1) in vec3 VertexRotation;"
		"layout (location = 2) in float VertexThickness;"
		"layout (location = 3) in vec4 VertexColor;"
		"out VS_OUT {"
		"	vec3 Rotation;"
		"	float Thickness;"
		"	vec4 Color;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(VertexPosition, 1.0);"
		"	VertexOutput.Rotation = VertexRotation;"
		"	VertexOutput.Thickness = VertexThickness;"
		"	VertexOutput.Color = VertexColor;"
		"}";
	static char const sWorldLineGeometryShader[] =
		GLSL_GL_VERSION
		"layout (lines) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 4) out;"
		"in VS_OUT {"
		"	vec3 Rotation;"
		"	float Thickness;"
		"	vec4 Color;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec4 Color;"
		"} GeometryOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec3 PositionStart = gl_in[0].gl_Position.xyz;"
		"	vec3 PositionEnd = gl_in[1].gl_Position.xyz;"
		"	vec3 CurrDir = normalize(PositionEnd - PositionStart);"
		"	vec3 DirectionOffset = normalize(cross(CurrDir, vec3(0.0, 0.0, 1.0))) * GeometryInput[0].Thickness;"
		"	vec3 EulerAngles = radians(GeometryInput[0].Rotation);"
		"	vec4 Rotation = EulerAnglesToQuaternion(EulerAngles.x, EulerAngles.y, EulerAngles.z);"
		"	vec3 P0 = RotateVector3D((PositionStart - CurrDir * GeometryInput[0].Thickness) + DirectionOffset, Rotation);"
		"	vec3 P1 = RotateVector3D((PositionStart - CurrDir * GeometryInput[0].Thickness) - DirectionOffset, Rotation);"
		"	vec3 P2 = RotateVector3D((PositionEnd + CurrDir * GeometryInput[0].Thickness) + DirectionOffset, Rotation);"
		"	vec3 P3 = RotateVector3D((PositionEnd + CurrDir * GeometryInput[0].Thickness) - DirectionOffset, Rotation);"
		"	GeometryOutput.Color = GeometryInput[0].Color;"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P0, 1.0);"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P1, 1.0);"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P2, 1.0);"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P3, 1.0);"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sWorldLineFragmentShader[] =
		GLSL_GL_VERSION
		"in GS_OUT {"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sWorldRectVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"layout (location = 2) in vec3 InstancePosition;"
		"layout (location = 3) in vec3 InstanceRotation;"
		"layout (location = 4) in vec2 InstanceSize;"
		"layout (location = 5) in vec4 InstanceColor;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"	vec4 Color;"
		"} VertexOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec3 EulerAngles = radians(InstanceRotation);"
		"	vec4 Rotation = EulerAnglesToQuaternion(EulerAngles.x, EulerAngles.y, EulerAngles.z);"
		"	vec3 LocalPosition = RotateVector3D(vec3(VertexPosition * InstanceSize, 0.0), Rotation);"
		"	vec3 WorldPosition = RotateVector3D(InstancePosition , Rotation);"
		"	vec4 ViewPosition = ViewMatrix * vec4(WorldPosition + LocalPosition, 1.0);"
		"	vec4 ClipPosition = ProjectionMatrix * ViewPosition;"
		"	gl_Position = ClipPosition;"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sWorldRectFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sScreenCircleVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"layout (location = 2) in vec3 InstancePosition;"
		"layout (location = 3) in float InstanceRotation;"
		"layout (location = 4) in float InstanceRadius;"
		"layout (location = 5) in vec4 InstanceColor;"
		"out VS_OUT {"
		"	vec2 Position;"
		"	vec2 TextureCoords;"
		"	float Radius;"
		"	vec4 Color;"
		"} VertexOutput;"
		"uniform vec2 ScreenSize;"
		GLSL_SCREEN_SPACE_IMPLEMENTATION
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	float Roll = radians(InstanceRotation);"
		"	vec2 RotatedScreenPosition = RotateVector2D(VertexPosition * InstanceRadius, Roll);"
		"	vec3 ScreenPosition = InstancePosition + vec3(RotatedScreenPosition, 0.0);"
		"	gl_Position = ScreenToClipSpace(ScreenPosition, ScreenSize);"
		"	VertexOutput.Position = RotatedScreenPosition;"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"	VertexOutput.Radius = InstanceRadius;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sScreenCircleFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 Position;"
		"	vec2 TextureCoords;"
		"	float Radius;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	if (dot(FragmentInput.Position, FragmentInput.Position) > (FragmentInput.Radius * FragmentInput.Radius)) discard;"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sScreenLineVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec3 VertexPosition;"
		"layout (location = 1) in float VertexRotation;"
		"layout (location = 2) in float VertexThickness;"
		"layout (location = 3) in vec4 VertexColor;"
		"out VS_OUT {"
		"	float Rotation;"
		"	float Thickness;"
		"	vec4 Color;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(VertexPosition, 1.0);"
		"	VertexOutput.Rotation = VertexRotation;"
		"	VertexOutput.Thickness = VertexThickness;"
		"	VertexOutput.Color = VertexColor;"
		"}";
	static char const sScreenLineGeometryShader[] =
		GLSL_GL_VERSION
		"layout (lines) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 4) out;"
		"in VS_OUT {"
		"	float Rotation;"
		"	float Thickness;"
		"	vec4 Color;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec4 Color;"
		"} GeometryOutput;"
		"uniform vec2 ScreenSize;"
		GLSL_SCREEN_SPACE_IMPLEMENTATION
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec3 PositionStart = gl_in[0].gl_Position.xyz;"
		"	vec3 PositionEnd = gl_in[1].gl_Position.xyz;"
		"	vec3 CurrDir = normalize(PositionEnd - PositionStart);"
		"	vec2 DirectionOffset = vec2(normalize(cross(CurrDir, vec3(0.0, 0.0, 1.0))) * GeometryInput[0].Thickness);"
		"	float Roll = radians(GeometryInput[0].Rotation);"
		"	vec2 O0 = (PositionStart.xy - CurrDir.xy * GeometryInput[0].Thickness) + DirectionOffset;"
		"	vec2 O1 = (PositionStart.xy - CurrDir.xy * GeometryInput[0].Thickness) - DirectionOffset;"
		"	vec2 O2 = (PositionEnd.xy + CurrDir.xy * GeometryInput[0].Thickness) + DirectionOffset;"
		"	vec2 O3 = (PositionEnd.xy + CurrDir.xy * GeometryInput[0].Thickness) - DirectionOffset;"
		"	vec2 V0 = RotateVector2D(O0, Roll);"
		"	vec2 V1 = RotateVector2D(O1, Roll);"
		"	vec2 V2 = RotateVector2D(O2, Roll);"
		"	vec2 V3 = RotateVector2D(O3, Roll);"
		"	GeometryOutput.Color = GeometryInput[0].Color;"
		"	gl_Position = ScreenToClipSpace(vec3(V0 + O0, PositionStart.z), ScreenSize);"
		"	EmitVertex();"
		"	gl_Position = ScreenToClipSpace(vec3(V1 + O1, PositionStart.z), ScreenSize);"
		"	EmitVertex();"
		"	gl_Position = ScreenToClipSpace(vec3(V2 + O2, PositionEnd.z), ScreenSize);"
		"	EmitVertex();"
		"	gl_Position = ScreenToClipSpace(vec3(V3 + O3, PositionEnd.z), ScreenSize);"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sScreenLineFragmentShader[] =
		GLSL_GL_VERSION
		"in GS_OUT {"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sScreenRectVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"layout (location = 2) in vec3 InstancePosition;"
		"layout (location = 3) in float InstanceRotation;"
		"layout (location = 4) in vec2 InstanceSize;"
		"layout (location = 5) in vec4 InstanceColor;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"	vec4 Color;"
		"} VertexOutput;"
		"uniform vec2 ScreenSize;"
		GLSL_SCREEN_SPACE_IMPLEMENTATION
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	float Roll = radians(InstanceRotation);"
		"	vec2 RotatedScreenPosition = RotateVector2D(VertexPosition * InstanceSize, Roll);"
		"	vec3 ScreenPosition = InstancePosition + vec3(RotatedScreenPosition, 0.0);"
		"	gl_Position = ScreenToClipSpace(ScreenPosition, ScreenSize);"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sScreenRectFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	BaseColor = FragmentInput.Color;"
		"}";
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedBatches = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Font Definition
	///////////////////////////////////////////////////////////////

#define ON_CURVE_POINT_BIT (0ULL)
#define X_SHORT_VECTOR_BIT (1ULL)
#define Y_SHORT_VECTOR_BIT (2ULL)
#define REPEAT_FLAG_BIT (3ULL)
#define X_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT (4ULL)
#define Y_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT (5ULL)

	typedef struct _FontWorldGlyphVertex
	{
		Vector2 Position;
		int unsigned Index;
	} FontWorldGlyphVertex;
	typedef struct _FontScreenGlyphVertex
	{
		Vector2 Position;
		int unsigned Index;
	} FontScreenGlyphVertex;
	typedef struct _FontWorldGlyphInstanceEntry
	{
		Vector3 Pivot;
		Vector3 Position;
		Vector3 Rotation;
		Vector2 Scale;
		Vector2 Bearing;
		float UnitsPerEm;
		float FontSize;
		Vector2 GlyphSize;
		Color4 Color;
		int unsigned GlyphIndex;
		int unsigned LineHeight;
	} FontWorldGlyphInstanceEntry;
	typedef struct _FontScreenGlyphInstanceEntry
	{
		Vector3 Pivot;
		Vector2 Position;
		float Rotation;
		Vector2 Bearing;
		float UnitsPerEm;
		float FontSize;
		Vector2 GlyphSize;
		Color4 Color;
		int unsigned GlyphIndex;
		int unsigned LineHeight;
	} FontScreenGlyphInstanceEntry;
	typedef struct _FontGlyphPoint
	{
		short X;
		short Y;
		bool OnCurve;
	} FontGlyphPoint;
	typedef struct _FontGlyph
	{
		bool IsCompound;
		int unsigned GlyphIndex;
		short NumContours;
		short MinX;
		short MinY;
		short MaxX;
		short MaxY;
		short unsigned Width;
		short unsigned Height;
		short unsigned AdvanceWidth;
		short unsigned BearingX;
		short unsigned BearingY;
		short unsigned* ContourEndIndices;
		FontGlyphPoint* Points;
		short unsigned NumPoints;
		char unsigned* Flags;
		char unsigned* Instructions;
		short unsigned NumInstructions;
		Vector PointOffsets;
		Vector BezierPoints;
		Vector BezierOffsets;
		Vector BezierCurves;
	} FontGlyph;
	typedef struct _FontOffsetTable
	{
		int unsigned ScalerType;
		short unsigned NumTables;
		short unsigned SearchRange;
		short unsigned EntrySelector;
		short unsigned RangeShift;
	} FontOffsetTable;
	typedef struct _FontTableDirectory
	{
		char Tag[4];
		int unsigned CheckSum;
		int unsigned Offset;
		int unsigned Length;
	} FontTableDirectory;
	typedef struct _FontHeadTable
	{
		int unsigned Version;
		int unsigned FontRevision;
		int unsigned CheckSumAdjustment;
		int unsigned MagicNumber;
		short unsigned Flags;
		short unsigned UnitsPerEm;
		long long Created;
		long long Modified;
		short MinX;
		short MinY;
		short MaxX;
		short MaxY;
		short unsigned MacStyle;
		short unsigned LowestRecPPEM;
		short FontDirectionHint;
		short IndexToLocFormat;
		short GlyphDataFormat;
	} FontHeadTable;
	typedef struct _FontMaxpTable
	{
		int unsigned Version;
		short unsigned NumGlyphs;
		short unsigned MaxPoints;
		short unsigned MaxContours;
		short unsigned MaxComponentPoints;
		short unsigned MaxComponentContours;
		short unsigned MaxZones;
		short unsigned MaxTwilightPoints;
		short unsigned MaxStorage;
		short unsigned MaxFunctionDefs;
		short unsigned MaxInstructionDefs;
		short unsigned MaxStackElements;
		short unsigned MaxSizeOfInstructions;
		short unsigned MaxComponentElements;
		short unsigned MaxComponentDepth;
	} FontMaxpTable;
	typedef struct _FontCmapTable
	{
		short unsigned Version;
		short unsigned NumberSubTables;
	} FontCmapTable;
	typedef struct _FontCmapSubTable
	{
		short unsigned PlatformID;
		short unsigned PlatformSpecificID;
		int unsigned Offset;
	} FontCmapSubTable;
	typedef struct _FontHheaTable
	{
		int unsigned Version;
		short Ascent;
		short Descent;
		short LineGap;
		short unsigned AdvanceWidthMax;
		short MinLeftSideBearing;
		short MinRightSideBearing;
		short xMaxExtent;
		short CaretSlopeRise;
		short CaretSlopeRun;
		short CaretOffset;
		short Reserved0;
		short Reserved1;
		short Reserved2;
		short Reserved3;
		short MetricDataFormt;
		short unsigned NumOfLongHorMetrics;
	} FontHheaTable;
	typedef struct _FontOS2Table
	{
		short unsigned Version;
		short AvgCharWidth;
		short unsigned WeightClass;
		short unsigned WidthClass;
		short Type;
		short SubScriptXSize;
		short SubScriptYSize;
		short SubScriptXOffset;
		short SubScriptYOffset;
		short SuperScriptXSize;
		short SuperScriptYSize;
		short SuperScriptXOffset;
		short SuperScriptYOffset;
		short StrikeoutSize;
		short StrikeoutPosition;
		short FamilyClass;
		char unsigned Panose[10];
		int unsigned UnicodeRange[4];
		char VendorID[4];
		short unsigned Selection;
		short unsigned FirstCharIndex;
		short unsigned LastCharIndex;
		short TypoAscender;
		short TypoDescender;
		short TypoLineGap;
		short unsigned WinAscent;
		short unsigned WinDescent;
		int unsigned CodePageRange1;
		int unsigned CodePageRange2;
		short Height;
		short CapHeight;
		short unsigned DefaultChar;
		short unsigned BreakChar;
		short unsigned MaxContent;
		short unsigned LowerPointSize;
		short unsigned UpperPointSize;
	} FontOS2Table;
	typedef struct _Font
	{
		FontOffsetTable OffsetTable;
		FontTableDirectory HeadTableDir;
		FontTableDirectory GlyfTableDir;
		FontTableDirectory LocaTableDir;
		FontTableDirectory CmapTableDir;
		FontTableDirectory MaxpTableDir;
		FontTableDirectory HheaTableDir;
		FontTableDirectory HmtxTableDir;
		FontTableDirectory OS2TableDir;
		FontHeadTable HeadTable;
		FontMaxpTable MaxpTable;
		FontCmapTable CmapTable;
		FontHheaTable HheaTable;
		FontOS2Table OS2Table;
		short unsigned Width;
		short unsigned Height;
		short unsigned LineHeight;
		int unsigned* GlyphOffsets;
		HashMap GlyphMapping;
		FontGlyph* Glyphs;
		int unsigned WorldGlyphVertexArray;
		int unsigned WorldGlyphVertexBuffer;
		int unsigned WorldGlyphInstanceBuffer;
		int unsigned WorldGlyphIndexBuffer;
		int unsigned WorldGlyphInstanceOffset;
		int unsigned ScreenGlyphVertexArray;
		int unsigned ScreenGlyphVertexBuffer;
		int unsigned ScreenGlyphInstanceBuffer;
		int unsigned ScreenGlyphIndexBuffer;
		int unsigned ScreenGlyphInstanceOffset;
		int unsigned BezierOffsetBuffer;
		int unsigned BezierCurveBuffer;
		Vector BezierOffsets;
		Vector BezierCurves;
	} Font;
	typedef struct _FontIDRangeOffsetMap
	{
		int unsigned ReadLocation;
		short unsigned RangeOffset;
	} FontIDRangeOffsetMap;
	typedef struct _FontPointOffsetEntry
	{
		int unsigned Start;
		int unsigned Num;
	} FontPointOffsetEntry;
	typedef struct _FontBezierOffsetEntry
	{
		int unsigned Start;
		int unsigned Num;
	} FontBezierOffsetEntry;
	typedef struct _FontBezierCurveEntry
	{
		Vector2 P0;
		Vector2 P1;
		Vector2 P2;
	} FontBezierCurveEntry;

	extern void Font_AllocFromFile(Font* Fnt, int unsigned NumChars, char const* FilePath);
	extern void Font_AllocFromMemory(Font* Fnt, int unsigned NumChars, char unsigned* Buffer, int unsigned BufferSize);
	extern FontGlyph* Font_GlyphByGlyphIndex(Font* Fnt, short unsigned GlyphIndex);
	extern FontGlyph* Font_GlyphByUnicode(Font* Fnt, int unsigned Unicode);
	extern float Font_LineHeight(Font* Fnt);
	extern short unsigned Font_NumGlyphs(Font* Fnt);
	extern void Font_Free(Font* Fnt);

	extern Font* Font_GetDefault(void);

	extern void Font_AllocInternal(Font* Fnt, int unsigned NumChars, char unsigned* Buffer, int unsigned BufferSize);
	extern void Font_ReadGlyphInternal(Font* Fnt, FileReader* Reader, short unsigned GlyphIndex, FontGlyph* Result);
	extern void Font_ReadSimpleGlyphInternal(Font* Fnt, FileReader* Reader, FontGlyph* Result);
	extern void Font_ReadCompoundGlyphInternal(Font* Fnt, FileReader* Reader, short unsigned GlyphIndex, FontGlyph* Result);
	extern void Font_ApplyLayoutInfosInternal(Font* Fnt, FileReader* Reader);
	extern void Font_UnicodeToGlyphMappingsInternal(Font* Fnt, FileReader* Reader);
	extern void Font_CreateBezierInternal(Font* Fnt, FontGlyph* Glyph);

#ifdef FAST_GL_IMPLEMENTATION
	static Font sDefaultFont = { 0 };
	static FontWorldGlyphInstanceEntry* sMappedWorldGlyphInstanceBuffer = 0;
	static FontScreenGlyphInstanceEntry* sMappedScreenGlyphInstanceBuffer = 0;
	static char unsigned sDefaultFontBytes[] =
	{
		0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x80, 0x00, 0x03, 0x00, 0x50, 0x46, 0x46, 0x54, 0x4D, 0x86, 0x9F, 0xA7, 0x1D, 0x00, 0x00, 0x36, 0x98, 0x00, 0x00, 0x00, 0x1C, 0x47, 0x44, 0x45, 0x46,
		0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x36, 0x80, 0x00, 0x00, 0x00, 0x18, 0x4F, 0x53, 0x2F, 0x32, 0x68, 0x20, 0x8E, 0x0A, 0x00, 0x00, 0x01, 0x58, 0x00, 0x00, 0x00, 0x60, 0x63, 0x6D, 0x61, 0x70,
		0xE4, 0xDD, 0x33, 0xAD, 0x00, 0x00, 0x04, 0x2C, 0x00, 0x00, 0x02, 0x6C, 0x67, 0x61, 0x73, 0x70, 0xFF, 0xFF, 0x00, 0x03, 0x00, 0x00, 0x36, 0x78, 0x00, 0x00, 0x00, 0x08, 0x67, 0x6C, 0x79, 0x66,
		0xED, 0x88, 0x5A, 0x87, 0x00, 0x00, 0x07, 0xD8, 0x00, 0x00, 0x29, 0x38, 0x68, 0x65, 0x61, 0x64, 0x0E, 0x8B, 0x50, 0x05, 0x00, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, 0x36, 0x68, 0x68, 0x65, 0x61,
		0x07, 0x0A, 0x03, 0x58, 0x00, 0x00, 0x01, 0x14, 0x00, 0x00, 0x00, 0x24, 0x68, 0x6D, 0x74, 0x78, 0x50, 0x75, 0x00, 0x00, 0x00, 0x00, 0x01, 0xB8, 0x00, 0x00, 0x02, 0x74, 0x6C, 0x6F, 0x63, 0x61,
		0xFA, 0xD5, 0x04, 0xFC, 0x00, 0x00, 0x06, 0x98, 0x00, 0x00, 0x01, 0x40, 0x6D, 0x61, 0x78, 0x70, 0x00, 0xEB, 0x00, 0x3B, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x00, 0x20, 0x6E, 0x61, 0x6D, 0x65,
		0x9F, 0x0B, 0x3D, 0xF9, 0x00, 0x00, 0x31, 0x10, 0x00, 0x00, 0x03, 0xAE, 0x70, 0x6F, 0x73, 0x74, 0x7C, 0x29, 0xCE, 0xB0, 0x00, 0x00, 0x34, 0xC0, 0x00, 0x00, 0x01, 0xB6, 0x00, 0x01, 0x00, 0x00,
		0x00, 0x01, 0x00, 0x00, 0x34, 0x15, 0xF6, 0xBC, 0x5F, 0x0F, 0x3C, 0xF5, 0x00, 0x0B, 0x03, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x26, 0x06, 0x96, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x26, 0x06, 0x96,
		0x00, 0x00, 0xFF, 0x38, 0x03, 0x20, 0x02, 0xBC, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0xE8, 0xFF, 0x38, 0x00, 0x00, 0x03, 0x84,
		0x00, 0x00, 0x00, 0x00, 0x03, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x01, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x38,
		0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x39, 0x01, 0x90, 0x00, 0x05,
		0x00, 0x08, 0x02, 0x8A, 0x02, 0x58, 0x00, 0x00, 0x00, 0x4B, 0x02, 0x8A, 0x02, 0x58, 0x00, 0x00, 0x01, 0x5E, 0x00, 0x32, 0x01, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x4B, 0x57, 0x4E, 0x00, 0xC0, 0x00, 0x20, 0x26, 0x66, 0x03, 0x20, 0xFF, 0x38,
		0x00, 0xC8, 0x03, 0xE8, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x4D, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x01, 0x2C, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0xBC, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x01, 0x2C, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x02, 0xBC, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00,
		0x01, 0xF4, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x2C, 0x00, 0x00, 0x02, 0xBC, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0xBC, 0x00, 0x00, 0x01, 0x2C, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x2C, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x01, 0x2C, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x03, 0x84, 0x00, 0x00, 0x03, 0x20, 0x00, 0x00, 0x03, 0x20, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00, 0x03, 0x84, 0x00, 0x00, 0x03, 0x84, 0x00, 0x00, 0x03, 0x84, 0x00, 0x00, 0x02, 0x58, 0x00, 0x00,
		0x03, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x66,
		0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x04, 0x01, 0x4A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x20, 0x00, 0x04, 0x00, 0x08, 0x00, 0x5F, 0x00, 0x7E, 0x00, 0xB1, 0x00, 0xBF, 0x00, 0xC7,
		0x00, 0xD1, 0x00, 0xF4, 0x00, 0xFC, 0x00, 0xFF, 0x01, 0x92, 0x03, 0xA9, 0x20, 0x14, 0x20, 0x22, 0x22, 0x11, 0x22, 0x1E, 0x22, 0x48, 0x23, 0x02, 0x26, 0x42, 0x26, 0x66, 0xFF, 0xFF, 0x00, 0x00,
		0x00, 0x20, 0x00, 0x61, 0x00, 0xA1, 0x00, 0xB6, 0x00, 0xC4, 0x00, 0xD1, 0x00, 0xD8, 0x00, 0xF6, 0x00, 0xFF, 0x01, 0x92, 0x03, 0xA9, 0x20, 0x14, 0x20, 0x22, 0x22, 0x11, 0x22, 0x1A, 0x22, 0x48,
		0x23, 0x02, 0x26, 0x3A, 0x26, 0x60, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xE2, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xAC, 0xFF, 0xA3, 0x00, 0x00, 0xFF, 0x8F, 0xFF, 0x8D, 0xFE, 0xFB, 0xFC, 0xE5, 0xE0, 0x7B,
		0xE0, 0x6E, 0xDE, 0x80, 0x00, 0x00, 0xDE, 0x4C, 0xDD, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x90, 0x00, 0x00, 0x00, 0x61, 0x00, 0x62, 0x00, 0x63, 0x00, 0x64,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x67, 0x00, 0x68, 0x00, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x6B, 0x00, 0x6C, 0x00, 0x6D,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77,
		0x00, 0x78, 0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x7B, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7D, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x81, 0x00, 0x82, 0x00, 0x83, 0x00, 0x84, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0x00, 0x96, 0x00, 0x97, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99,
		0x00, 0x00, 0x00, 0x9A, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x9D, 0x00, 0x9E, 0x00, 0x00, 0x01, 0x06, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
		0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
		0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x00, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
		0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x00, 0x70, 0x71, 0x73, 0x00, 0x74, 0x00, 0x76, 0x78,
		0x77, 0x79, 0x00, 0x00, 0x7A, 0x7C, 0x00, 0x00, 0x7D, 0x7E, 0x7F, 0x00, 0x80, 0x00, 0x81, 0x83, 0x82, 0x84, 0x85, 0x00, 0x89, 0x88, 0x8A, 0x8B, 0x00, 0x00, 0x62, 0x63, 0x65, 0x90, 0x6B, 0x00,
		0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x75, 0x93, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x7B, 0x87, 0x6F, 0x61, 0x67, 0x92, 0x8D, 0x94, 0x00, 0x66,
		0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x86, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x12, 0x00, 0x2E, 0x00, 0x58, 0x00, 0x84, 0x00, 0xB2, 0x00, 0xEE, 0x01, 0x00, 0x01, 0x24, 0x01, 0x46, 0x01, 0x68, 0x01, 0x7E, 0x01, 0x8A, 0x01, 0x98, 0x01, 0xA4, 0x01, 0xC6,
		0x01, 0xF4, 0x02, 0x0A, 0x02, 0x38, 0x02, 0x68, 0x02, 0x8A, 0x02, 0xAE, 0x02, 0xD4, 0x02, 0xF2, 0x03, 0x20, 0x03, 0x4A, 0x03, 0x5C, 0x03, 0x6E, 0x03, 0x9A, 0x03, 0xAE, 0x03, 0xDA, 0x04, 0x04,
		0x04, 0x2A, 0x04, 0x46, 0x04, 0x6A, 0x04, 0x90, 0x04, 0xAA, 0x04, 0xC2, 0x04, 0xD6, 0x04, 0xFA, 0x05, 0x12, 0x05, 0x28, 0x05, 0x42, 0x05, 0x6A, 0x05, 0x7A, 0x05, 0x9C, 0x05, 0xBE, 0x05, 0xDE,
		0x05, 0xFA, 0x06, 0x24, 0x06, 0x46, 0x06, 0x70, 0x06, 0x82, 0x06, 0x9A, 0x06, 0xBC, 0x06, 0xDC, 0x07, 0x18, 0x07, 0x3A, 0x07, 0x64, 0x07, 0x76, 0x07, 0x98, 0x07, 0xAA, 0x07, 0xCC, 0x07, 0xD8,
		0x07, 0xFA, 0x08, 0x1A, 0x08, 0x40, 0x08, 0x60, 0x08, 0x80, 0x08, 0x9C, 0x08, 0xBE, 0x08, 0xDC, 0x08, 0xEE, 0x09, 0x0C, 0x09, 0x34, 0x09, 0x46, 0x09, 0x66, 0x09, 0x7E, 0x09, 0x9E, 0x09, 0xBE,
		0x09, 0xE0, 0x09, 0xFC, 0x0A, 0x20, 0x0A, 0x3A, 0x0A, 0x50, 0x0A, 0x72, 0x0A, 0x8C, 0x0A, 0xC4, 0x0A, 0xE2, 0x0B, 0x04, 0x0B, 0x28, 0x0B, 0x3A, 0x0B, 0x5C, 0x0B, 0x7A, 0x0B, 0x8C, 0x0B, 0xAC,
		0x0B, 0xD2, 0x0B, 0xF4, 0x0C, 0x2A, 0x0C, 0x66, 0x0C, 0x76, 0x0C, 0x82, 0x0C, 0xAC, 0x0C, 0xC8, 0x0C, 0xE6, 0x0C, 0xF2, 0x0D, 0x02, 0x0D, 0x3E, 0x0D, 0x66, 0x0D, 0x8E, 0x0D, 0xB0, 0x0D, 0xD2,
		0x0E, 0x04, 0x0E, 0x2C, 0x0E, 0x5A, 0x0E, 0x7E, 0x0E, 0xA6, 0x0E, 0xCC, 0x0E, 0xFE, 0x0F, 0x26, 0x0F, 0x56, 0x0F, 0x86, 0x0F, 0xB8, 0x0F, 0xE4, 0x0F, 0xF6, 0x10, 0x0E, 0x10, 0x2C, 0x10, 0x52,
		0x10, 0x78, 0x10, 0xA8, 0x10, 0xD2, 0x10, 0xEC, 0x11, 0x16, 0x11, 0x32, 0x11, 0x4E, 0x11, 0x78, 0x11, 0x9A, 0x11, 0xC4, 0x11, 0xF0, 0x12, 0x1A, 0x12, 0x28, 0x12, 0x34, 0x12, 0x60, 0x12, 0x7C,
		0x12, 0xAC, 0x12, 0xD8, 0x12, 0xFC, 0x13, 0x32, 0x13, 0x60, 0x13, 0xB0, 0x13, 0xDA, 0x14, 0x08, 0x14, 0x2E, 0x14, 0x54, 0x14, 0x76, 0x14, 0x9C, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x11, 0x33, 0x11, 0x23, 0x15, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0x02, 0xBC, 0xFE, 0x0C, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
		0x01, 0x90, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x3B, 0x01, 0x15, 0x23, 0x05, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15,
		0xC8, 0x64, 0xC8, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x02, 0xBC, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x1B,
		0x00, 0x1F, 0x00, 0x00, 0x01, 0x23, 0x15, 0x33, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x33,
		0x07, 0x35, 0x23, 0x15, 0x01, 0xF4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x01, 0x90, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0xC8, 0x64, 0x64,
		0x64, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x35,
		0x33, 0x35, 0x33, 0x15, 0x33, 0x15, 0x21, 0x33, 0x15, 0x23, 0x17, 0x35, 0x21, 0x15, 0x17, 0x23, 0x35, 0x33, 0x07, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x64, 0x64, 0x64, 0xC8, 0xFE, 0x0C,
		0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x01, 0xF4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00,
		0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x23, 0x35, 0x33, 0x21, 0x33,
		0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x23, 0x33, 0x15, 0x23, 0x25, 0x33, 0x15, 0x23, 0x21, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0xC8, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x01, 0xF4, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x27, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x07, 0x33, 0x15, 0x23,
		0x21, 0x23, 0x35, 0x33, 0x11, 0x15, 0x23, 0x35, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x15, 0x37, 0x15, 0x23, 0x35, 0x05, 0x15, 0x23, 0x35, 0x17, 0x33, 0x15, 0x23, 0x21, 0x23, 0x35, 0x33,
		0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xC8, 0xC8, 0x01, 0x90, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64,
		0x64, 0x64, 0xFE, 0xD4, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x90, 0x00, 0xC8, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x00, 0x13, 0x33, 0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x23, 0x35, 0x33, 0x07, 0x15, 0x23, 0x35, 0x11, 0x23, 0x11, 0x33, 0x13, 0x23, 0x35, 0x33, 0x15, 0x35,
		0x33, 0x15, 0x01, 0x90, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xFE, 0x70, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00,
		0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x17, 0x33, 0x15, 0x23, 0x3B, 0x01,
		0x11, 0x23, 0x07, 0x35, 0x33, 0x15, 0x21, 0x33, 0x15, 0x23, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0xC8, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4,
		0x64, 0x64, 0x64, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0xC8, 0x01, 0x90, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23, 0x25, 0x15,
		0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x07, 0x35, 0x33, 0x15, 0x21, 0x23, 0x35, 0x33, 0x64, 0x64, 0x01, 0x90, 0x64, 0xC8, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x64, 0x01, 0xF4, 0x02, 0x58, 0x00, 0x0B, 0x00, 0x00, 0x01, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35,
		0x33, 0x15, 0x01, 0xF4, 0xC8, 0x64, 0xC8, 0xC8, 0x64, 0x01, 0x90, 0x64, 0xC8, 0xC8, 0x64, 0xC8, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x9C, 0x00, 0x64, 0x00, 0xC8, 0x00, 0x03,
		0x00, 0x00, 0x35, 0x33, 0x11, 0x23, 0x64, 0x64, 0xC8, 0xFE, 0xD4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2C, 0x01, 0xF4, 0x01, 0x90, 0x00, 0x03, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x01, 0xF4,
		0xFE, 0x0C, 0x01, 0x90, 0x64, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0xC8, 0x00, 0x03, 0x00, 0x00, 0x35, 0x33, 0x15, 0x23, 0x64, 0x64, 0xC8, 0xC8, 0x00, 0x00,
		0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x33, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0x07, 0x35,
		0x33, 0x15, 0x23, 0x33, 0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8,
		0x64, 0x64, 0x64, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x0B, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x03, 0x23,
		0x15, 0x23, 0x11, 0x33, 0x11, 0x33, 0x13, 0x33, 0x11, 0x23, 0x11, 0x23, 0x35, 0x33, 0x07, 0x35, 0x33, 0x15, 0x17, 0x15, 0x21, 0x35, 0x64, 0x01, 0x2C, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64,
		0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x01, 0xF4, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x0C, 0x01, 0x2C, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64,
		0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x00, 0x25, 0x15, 0x21, 0x35, 0x33, 0x11, 0x23, 0x35, 0x33, 0x35, 0x33, 0x11, 0x01, 0xF4, 0xFE, 0x0C, 0xC8, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFD, 0xA8, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x1B, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x35, 0x33, 0x15, 0x25, 0x33, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x23, 0x33, 0x15, 0x21, 0x35, 0x33, 0x15, 0x21,
		0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x0C, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B,
		0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x35, 0x33, 0x15, 0x25, 0x33, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0x17, 0x35, 0x33, 0x15, 0x25, 0x33, 0x15, 0x23, 0x21, 0x15, 0x21, 0x35, 0x01, 0x90,
		0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0xC8, 0x64, 0xFE, 0x0C, 0x64, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8,
		0xC8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x11, 0x23, 0x35, 0x21, 0x35,
		0x33, 0x15, 0x21, 0x11, 0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x02, 0xBC, 0xFD, 0x44, 0xC8, 0xC8, 0x64,
		0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00,
		0x13, 0x15, 0x21, 0x15, 0x21, 0x11, 0x21, 0x15, 0x07, 0x33, 0x11, 0x23, 0x25, 0x33, 0x15, 0x23, 0x21, 0x15, 0x21, 0x35, 0x64, 0x01, 0x2C, 0xFE, 0x70, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0x70,
		0x64, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x01, 0x23, 0x35, 0x33, 0x07, 0x15, 0x23, 0x35, 0x11, 0x15, 0x23, 0x11, 0x33, 0x15, 0x21, 0x15, 0x31, 0x33, 0x15, 0x23, 0x31, 0x15,
		0x21, 0x35, 0x01, 0x90, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0x01, 0x90, 0x64, 0x64, 0xC8, 0x64, 0x64,
		0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x11, 0x23, 0x35, 0x21, 0x15, 0x23, 0x35, 0x01, 0x35, 0x33, 0x15, 0x23, 0x33,
		0x11, 0x23, 0x01, 0xF4, 0x64, 0xFE, 0xD4, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0x64, 0x64, 0x02, 0xBC, 0xFE, 0xD4, 0xC8, 0x64, 0xC8, 0xFE, 0x70, 0x64, 0x64, 0xFE, 0xD4, 0x00, 0x00, 0x07, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x21, 0x15, 0x23, 0x35, 0x21, 0x33,
		0x15, 0x23, 0x31, 0x15, 0x21, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x05, 0x35, 0x33, 0x15, 0x23, 0x15, 0x21, 0x35, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x01,
		0x90, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x21, 0x15, 0x23, 0x35, 0x21, 0x33, 0x11, 0x23, 0x35, 0x21, 0x35, 0x21, 0x03, 0x35,
		0x33, 0x15, 0x21, 0x33, 0x15, 0x23, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0xC8, 0x02, 0x58, 0x64, 0x64, 0xC8, 0xC8,
		0xFE, 0x70, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x02, 0x58, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23,
		0x15, 0x33, 0x15, 0x23, 0x64, 0x64, 0x64, 0x64, 0x02, 0x58, 0xC8, 0xC8, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0xFF, 0x9C, 0x00, 0x64, 0x02, 0x58, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00,
		0x11, 0x33, 0x15, 0x23, 0x15, 0x33, 0x11, 0x23, 0x64, 0x64, 0x64, 0x64, 0x02, 0x58, 0xC8, 0xC8, 0xFE, 0xD4, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x1D, 0x01, 0x35,
		0x33, 0x1D, 0x01, 0x35, 0x33, 0x1D, 0x01, 0x35, 0x33, 0x15, 0x01, 0x2C, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x02, 0x00, 0x00, 0x00, 0x64, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35,
		0x01, 0x15, 0x21, 0x35, 0x01, 0xF4, 0xFE, 0x0C, 0x01, 0xF4, 0xFE, 0x0C, 0x01, 0xF4, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x11, 0x35, 0x33, 0x1D, 0x01, 0x35, 0x33, 0x1D, 0x01, 0x35, 0x33, 0x1D, 0x01, 0x35, 0x33, 0x15, 0x07, 0x35,
		0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x17, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x35, 0x33, 0x15, 0x25, 0x33, 0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x01, 0x90, 0xFE, 0xD4,
		0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00,
		0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x33, 0x11, 0x23, 0x01, 0x33, 0x11, 0x21,
		0x11, 0x33, 0x15, 0x33, 0x01, 0x35, 0x21, 0x15, 0x01, 0xF4, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0xC8, 0x64, 0xFE, 0x70, 0x01, 0x90, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xFE,
		0x0C, 0x01, 0xF4, 0xFE, 0x70, 0x01, 0x2C, 0xC8, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x0F, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15,
		0x31, 0x33, 0x11, 0x23, 0x11, 0x21, 0x11, 0x23, 0x11, 0x33, 0x15, 0x21, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x02, 0x58, 0x64, 0x64, 0xFD, 0xA8, 0x01, 0x90, 0xFE,
		0x70, 0x02, 0x58, 0x64, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x15, 0x21, 0x11, 0x21, 0x15, 0x21, 0x11, 0x21, 0x15,
		0x21, 0x15, 0x21, 0x23, 0x35, 0x33, 0x07, 0x33, 0x11, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x70, 0x01, 0x90, 0xFE, 0xD4, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64,
		0xFE, 0xD4, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xC8, 0xFE, 0xD4, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x33, 0x11, 0x23, 0x01, 0x23, 0x35, 0x33, 0x11, 0x15, 0x23, 0x35, 0x05, 0x35, 0x21, 0x15, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64,
		0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x01, 0x90, 0x64, 0xFE, 0x70, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x25, 0x15, 0x21, 0x11, 0x21, 0x15, 0x21, 0x11, 0x01, 0x33, 0x11, 0x23, 0x01, 0x90, 0xFE, 0x70, 0x01, 0x90, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0x64,
		0x64, 0x64, 0x02, 0xBC, 0x64, 0xFE, 0x0C, 0x01, 0xF4, 0xFE, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x00, 0x13, 0x15, 0x33, 0x15, 0x23, 0x11,
		0x21, 0x15, 0x21, 0x11, 0x21, 0x15, 0x64, 0xC8, 0xC8, 0x01, 0x90, 0xFE, 0x0C, 0x01, 0xF4, 0x02, 0x58, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x02, 0xBC, 0x64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x09, 0x00, 0x00, 0x01, 0x15, 0x21, 0x15, 0x33, 0x15, 0x23, 0x11, 0x23, 0x11, 0x01, 0xF4, 0xFE, 0x70, 0xC8, 0xC8, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64,
		0xFE, 0x70, 0x02, 0xBC, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33,
		0x01, 0x23, 0x11, 0x23, 0x35, 0x33, 0x01, 0x35, 0x21, 0x15, 0x64, 0x01, 0x90, 0xFE, 0x70, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0xC8, 0xFE, 0x70, 0x01, 0x2C, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x0C,
		0x01, 0xF4, 0xFE, 0x0C, 0x01, 0x2C, 0x64, 0xFE, 0x0C, 0x64, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x00, 0x01, 0x33, 0x11, 0x23, 0x11, 0x21,
		0x11, 0x23, 0x11, 0x33, 0x15, 0x21, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x02, 0xBC, 0xFD, 0x44, 0x01, 0x90, 0xFE, 0x70, 0x02, 0xBC, 0xC8, 0x00, 0x00, 0x01, 0x00, 0x00,
		0x00, 0x00, 0x01, 0x2C, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x00, 0x37, 0x33, 0x15, 0x21, 0x35, 0x33, 0x11, 0x23, 0x35, 0x21, 0x15, 0x23, 0xC8, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64,
		0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x01, 0x33, 0x11, 0x23, 0x25, 0x33,
		0x15, 0x23, 0x21, 0x15, 0x21, 0x35, 0x01, 0x90, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x02, 0xBC, 0xFD, 0xA8, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x01, 0x15, 0x23, 0x11, 0x23, 0x11, 0x33, 0x15, 0x25, 0x15, 0x23, 0x35, 0x1D, 0x01,
		0x23, 0x35, 0x13, 0x23, 0x35, 0x33, 0x15, 0x33, 0x11, 0x23, 0x01, 0x2C, 0xC8, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x02, 0xBC, 0xC8,
		0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xFE, 0xD4, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x05, 0x00, 0x00, 0x25, 0x15, 0x21, 0x11, 0x33, 0x11,
		0x01, 0xF4, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x02, 0xBC, 0xFD, 0xA8, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x13, 0x33,
		0x15, 0x23, 0x11, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x11, 0x23, 0x35, 0x33, 0x07, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x02,
		0x58, 0x64, 0xFE, 0x0C, 0x02, 0xBC, 0xFD, 0x44, 0x01, 0xF4, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x13, 0x33, 0x15, 0x23, 0x11, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x11, 0x23, 0x35, 0x33, 0x27, 0x33, 0x15, 0x23, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64,
		0x64, 0xC8, 0x64, 0x64, 0x02, 0x58, 0x64, 0xFE, 0x0C, 0x02, 0xBC, 0xFD, 0x44, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x01,
		0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x0C, 0x01, 0xF4, 0xFE, 0x0C, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x09,
		0x00, 0x0D, 0x00, 0x00, 0x01, 0x15, 0x21, 0x11, 0x23, 0x11, 0x21, 0x15, 0x21, 0x15, 0x25, 0x33, 0x15, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0x64, 0x01,
		0xF4, 0x64, 0xFE, 0x70, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x17, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x07, 0x35, 0x33, 0x15, 0x21, 0x33, 0x15, 0x23, 0x21, 0x23, 0x35, 0x33, 0x64, 0x01, 0x2C, 0xFE,
		0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0xC8, 0x01, 0x90, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x0C, 0x01, 0xF4, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x09, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x01, 0x15, 0x21, 0x11, 0x23, 0x11, 0x21, 0x15, 0x21, 0x15, 0x21, 0x23, 0x35, 0x33,
		0x07, 0x33, 0x11, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xC8, 0xFE,
		0x70, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15,
		0x21, 0x33, 0x15, 0x23, 0x17, 0x35, 0x21, 0x15, 0x31, 0x33, 0x11, 0x23, 0x25, 0x33, 0x15, 0x23, 0x21, 0x15, 0x21, 0x35, 0x64, 0x01, 0x90, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64,
		0xFE, 0x70, 0x64, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x07, 0x00, 0x00, 0x01, 0x15, 0x23, 0x11, 0x23, 0x11, 0x23, 0x35, 0x01, 0xF4, 0xC8, 0x64, 0xC8, 0x02, 0xBC, 0x64, 0xFD, 0xA8, 0x02, 0x58, 0x64, 0x00, 0x00, 0x03, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x37, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64,
		0x64, 0xFE, 0xD4, 0x64, 0x02, 0x58, 0xFD, 0xA8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x13, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x2B, 0x01, 0x15, 0x23, 0x35, 0x3B, 0x01, 0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xC8, 0x64, 0xC8,
		0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x01, 0x90, 0xFE, 0x70, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x37, 0x33, 0x15, 0x23, 0x15, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x35, 0x23, 0x35, 0x33, 0x27, 0x33, 0x15, 0x23, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64,
		0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x02, 0xBC, 0xFD, 0x44, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23, 0x25, 0x15, 0x23, 0x35, 0x05, 0x33, 0x15, 0x23, 0x25, 0x15, 0x23, 0x35, 0x07, 0x33,
		0x15, 0x23, 0x07, 0x35, 0x33, 0x15, 0x33, 0x23, 0x35, 0x33, 0x05, 0x33, 0x11, 0x23, 0x01, 0x33, 0x11, 0x23, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0xD4, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x11, 0x33,
		0x15, 0x23, 0x25, 0x33, 0x15, 0x23, 0x21, 0x33, 0x15, 0x23, 0x33, 0x35, 0x33, 0x15, 0x23, 0x33, 0x11, 0x23, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64,
		0x64, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x05, 0x00, 0x09, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x17,
		0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x21, 0x35, 0x01, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x23, 0x33, 0x15, 0x21, 0x15, 0x21, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x01,
		0x2C, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x01, 0x90, 0xFE, 0x0C, 0x02, 0xBC, 0xC8, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00,
		0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2C, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x00, 0x37, 0x33, 0x15, 0x21, 0x11, 0x21, 0x15, 0x23, 0x64, 0xC8, 0xFE, 0xD4, 0x01, 0x2C, 0xC8, 0x64, 0x64, 0x02,
		0xBC, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23, 0x33, 0x15,
		0x23, 0x35, 0x17, 0x33, 0x15, 0x23, 0x33, 0x15, 0x23, 0x35, 0x17, 0x33, 0x15, 0x23, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0x64, 0xC8, 0xC8, 0xC8,
		0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2C, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x00, 0x01, 0x11, 0x21, 0x35, 0x33, 0x11, 0x23, 0x35, 0x01, 0x2C,
		0xFE, 0xD4, 0xC8, 0xC8, 0x02, 0xBC, 0xFD, 0x44, 0x64, 0x01, 0xF4, 0x64, 0x00, 0x05, 0x00, 0x00, 0x01, 0x90, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x13, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15, 0x21, 0x35, 0x33, 0x15, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x01,
		0x2C, 0x64, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x21, 0x15,
		0x21, 0x35, 0x01, 0xF4, 0xFE, 0x0C, 0x64, 0x64, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x05, 0x33,
		0x11, 0x21, 0x35, 0x21, 0x35, 0x21, 0x35, 0x21, 0x05, 0x33, 0x15, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x70, 0x64, 0x64, 0x01,
		0xF4, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x09, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x25, 0x15,
		0x21, 0x11, 0x33, 0x11, 0x33, 0x15, 0x23, 0x15, 0x01, 0x23, 0x35, 0x33, 0x15, 0x33, 0x11, 0x23, 0x01, 0x90, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x01, 0x2C, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x02,
		0xBC, 0xFE, 0xD4, 0x64, 0xC8, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x33, 0x11, 0x23, 0x25, 0x23, 0x35, 0x33, 0x1D, 0x01, 0x23, 0x35, 0x05, 0x35, 0x21, 0x15, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64,
		0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x09, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x01, 0x33, 0x11, 0x21, 0x35, 0x21, 0x35, 0x23, 0x35, 0x33, 0x2B, 0x01, 0x35, 0x33, 0x03, 0x23, 0x11, 0x33, 0x01, 0x90, 0x64, 0xFE,
		0x70, 0x01, 0x2C, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x02, 0xBC, 0xFD, 0x44, 0x64, 0xC8, 0x64, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x01, 0xF4, 0x00, 0x03, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x31, 0x33, 0x15, 0x21, 0x15, 0x23, 0x11, 0x33, 0x15, 0x21, 0x01, 0x35, 0x21, 0x15, 0x64, 0x01, 0x2C, 0x64,
		0xFE, 0x70, 0x64, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x01, 0x90, 0x01, 0x90, 0x64, 0x64, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x23, 0x35, 0x33, 0x05, 0x33, 0x15, 0x33, 0x15, 0x23, 0x11, 0x23, 0x11, 0x23, 0x35, 0x33, 0x01, 0x90, 0xC8, 0xC8, 0xFE, 0xD4, 0x64, 0xC8,
		0xC8, 0x64, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x01, 0x90, 0x64, 0x00, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x09, 0x00, 0x0D, 0x00, 0x11,
		0x00, 0x00, 0x01, 0x11, 0x23, 0x35, 0x21, 0x35, 0x21, 0x35, 0x21, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x01, 0x15, 0x21, 0x35, 0x01, 0xF4, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x01, 0x90,
		0xFE, 0x70, 0x01, 0xF4, 0xFE, 0x0C, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0xC8, 0xFE, 0x70, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07,
		0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x13, 0x33, 0x15, 0x23, 0x11, 0x23, 0x11, 0x33, 0x05, 0x15, 0x23, 0x35, 0x17, 0x33, 0x11, 0x23, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0xC8, 0xC8, 0x64,
		0x64, 0x01, 0x90, 0x64, 0xFE, 0xD4, 0x02, 0xBC, 0xC8, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00,
		0x11, 0x33, 0x15, 0x23, 0x15, 0x33, 0x11, 0x23, 0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0xFE, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x33, 0x15, 0x23, 0x15, 0x33, 0x11, 0x23, 0x25, 0x33, 0x15, 0x23, 0x21, 0x15, 0x21, 0x35, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70,
		0x64, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0x02, 0xBC, 0x64, 0x64, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F,
		0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x13, 0x33, 0x15, 0x23, 0x15, 0x23, 0x11, 0x33, 0x05, 0x15, 0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x13, 0x23, 0x35, 0x33, 0x17, 0x23, 0x35, 0x33, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0x02, 0xBC, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0xC8, 0x64, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x37, 0x23, 0x11, 0x33, 0x11, 0x33, 0x15, 0x23, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x02, 0x58,
		0xFD, 0xA8, 0x64, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x05, 0x00, 0x09, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x13, 0x15, 0x23, 0x11, 0x23, 0x11, 0x21, 0x33,
		0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0x37, 0x33, 0x11, 0x23, 0xC8, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x01, 0xF4, 0x64, 0xC8,
		0xC8, 0xFE, 0x70, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x01, 0x15, 0x21, 0x11, 0x23, 0x11, 0x05, 0x33, 0x11, 0x23, 0x01, 0x90,
		0xFE, 0xD4, 0x64, 0x01, 0x90, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x01,
		0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x25, 0x15, 0x21, 0x15, 0x23, 0x11, 0x33, 0x15, 0x33, 0x15, 0x23, 0x15, 0x25, 0x23, 0x35, 0x33, 0x15, 0x33, 0x15, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64,
		0x64, 0x64, 0x01, 0x2C, 0xC8, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x02, 0x58, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x33, 0x11, 0x23, 0x35, 0x21, 0x35, 0x21, 0x35, 0x23, 0x35, 0x33, 0x2B, 0x01, 0x35, 0x33, 0x07, 0x15, 0x23, 0x35, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4,
		0x01, 0x2C, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x01, 0xF4, 0xFD, 0xA8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x01, 0xF4, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x13, 0x15, 0x33, 0x15, 0x23, 0x11, 0x23, 0x11, 0x21, 0x15, 0x23, 0x35, 0x17, 0x33, 0x15, 0x23, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90,
		0xC8, 0xC8, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0xF4, 0x64, 0x64, 0x64, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x21, 0x33, 0x15, 0x23, 0x17, 0x35, 0x21, 0x15, 0x17, 0x23, 0x35, 0x33, 0x07, 0x15, 0x21, 0x35, 0x64, 0x01, 0x90, 0xFE, 0x0C, 0x64,
		0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2C,
		0x02, 0xBC, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x37, 0x23, 0x11, 0x23, 0x35, 0x33, 0x35, 0x33, 0x15, 0x33, 0x15, 0x23, 0x13, 0x23, 0x35, 0x33, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0xC8, 0x64, 0xFE, 0x70, 0x64, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x09, 0x00, 0x00, 0x37, 0x23, 0x11, 0x33,
		0x21, 0x33, 0x11, 0x21, 0x35, 0x21, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0x64, 0x01, 0x90, 0xFE, 0x0C, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x37, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x21, 0x33, 0x15, 0x23, 0x33, 0x35, 0x33, 0x15, 0x07, 0x35,
		0x33, 0x15, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0xC8, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x02, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x0D, 0x00, 0x00, 0x37, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x21, 0x35, 0x33, 0x35, 0x33, 0x15, 0x33, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64,
		0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90, 0xFE, 0x0C, 0x64, 0xC8, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x00, 0x11, 0x35, 0x33, 0x15, 0x21, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x07, 0x35,
		0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15, 0x21, 0x35, 0x33, 0x15, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64,
		0x64, 0xFE, 0x70, 0x64, 0x01, 0x2C, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00,
		0x00, 0x03, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00, 0x37, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x35, 0x21, 0x35, 0x21, 0x1D, 0x01,
		0x21, 0x35, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x70, 0xC8, 0x01, 0x2C, 0xFE, 0x0C, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x13, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x21, 0x35, 0x21, 0x15, 0x07, 0x15, 0x23, 0x35, 0x07, 0x33, 0x15, 0x21, 0x15, 0x21,
		0x35, 0x33, 0x01, 0x90, 0x64, 0xFE, 0xD4, 0x01, 0xF4, 0xC8, 0x64, 0x64, 0x64, 0x01, 0x2C, 0xFE, 0x0C, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00,
		0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x23, 0x35, 0x33, 0x03, 0x23, 0x35, 0x33, 0x07, 0x33,
		0x15, 0x23, 0x17, 0x35, 0x33, 0x1D, 0x01, 0x35, 0x33, 0x15, 0x01, 0x90, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x02, 0x58, 0x64, 0xFE, 0xD4, 0xC8, 0xC8, 0x64, 0xC8,
		0xC8, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x11, 0x33, 0x11, 0x23, 0x15, 0x33, 0x11, 0x23,
		0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0xFE, 0xD4, 0x64, 0xFE, 0xD4, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x05, 0x15, 0x23, 0x35, 0x17, 0x33, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0xC8, 0xC8, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0xC8, 0xC8, 0xC8, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0xC8, 0x64, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0xF4, 0x02, 0x58, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x21, 0x33, 0x15, 0x23, 0x05, 0x35, 0x33, 0x15, 0x37, 0x33, 0x15, 0x23, 0x01, 0x2C, 0xC8, 0x01, 0x90, 0x64, 0x64, 0xFE, 0x0C, 0x64, 0xC8, 0xC8,
		0xC8, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x02, 0x58, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23,
		0x15, 0x33, 0x11, 0x23, 0x64, 0x64, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x70, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x01, 0xF4, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x13,
		0x00, 0x00, 0x13, 0x35, 0x33, 0x35, 0x33, 0x15, 0x33, 0x15, 0x21, 0x33, 0x15, 0x23, 0x17, 0x23, 0x35, 0x21, 0x15, 0x23, 0x15, 0x23, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0xC8, 0x64,
		0x01, 0x2C, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x13, 0x00, 0x17,
		0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x07, 0x33, 0x15, 0x33, 0x15, 0x23, 0x15, 0x21, 0x15, 0x21, 0x35, 0x33, 0x35, 0x23, 0x35, 0x33, 0x25, 0x23, 0x35, 0x33, 0x01, 0x90, 0xC8, 0x64, 0x64, 0xC8,
		0xC8, 0x01, 0x2C, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
		0x00, 0xC8, 0x01, 0x2C, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x11, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x07, 0x35,
		0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00,
		0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15,
		0x21, 0x33, 0x15, 0x23, 0x17, 0x35, 0x21, 0x15, 0x21, 0x33, 0x15, 0x23, 0x21, 0x23, 0x35, 0x33, 0x07, 0x15, 0x21, 0x35, 0x05, 0x23, 0x35, 0x33, 0x07, 0x15, 0x21, 0x35, 0x64, 0x01, 0x90, 0xFE,
		0x0C, 0x64, 0x64, 0x64, 0x01, 0x2C, 0xFE, 0x70, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x90, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x27, 0x00, 0x00, 0x13, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15,
		0x33, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0xC8, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64,
		0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x00, 0x01, 0x00, 0x00, 0x00, 0x64, 0x01, 0xF4, 0x01, 0x2C, 0x00, 0x05, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x21, 0x35, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xC8,
		0x64, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2C, 0x00, 0xC8, 0x01, 0x90, 0x00, 0x03, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0xC8, 0xC8, 0x01, 0x90, 0x64, 0x64, 0x00, 0x03, 0x00, 0x00,
		0x00, 0x00, 0x02, 0x58, 0x01, 0xF4, 0x00, 0x09, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x23, 0x35, 0x21, 0x15, 0x23, 0x15, 0x23, 0x15, 0x23, 0x33, 0x15, 0x33, 0x15, 0x21, 0x35, 0x23, 0x11,
		0x33, 0x15, 0x33, 0x15, 0x33, 0x35, 0x37, 0x33, 0x11, 0x23, 0xC8, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0xC8, 0x64, 0x64, 0xC8, 0xFE, 0xD4, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x00,
		0x01, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x15, 0x13, 0x15, 0x21, 0x35, 0x01, 0xF4, 0xC8, 0x64, 0xC8, 0xC8, 0x64, 0xC8, 0xFE, 0x0C, 0x01, 0xF4, 0x64, 0xC8, 0xC8, 0x64,
		0xC8, 0xC8, 0xFE, 0x70, 0x64, 0x64, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x58, 0x02, 0xBC, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x00, 0x01, 0x11, 0x23, 0x11, 0x23, 0x11, 0x23, 0x11,
		0x23, 0x35, 0x33, 0x35, 0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x02, 0x58, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x02, 0xBC, 0xFD, 0x44, 0x02, 0x58, 0xFD, 0xA8, 0x01, 0x2C, 0x64, 0xC8, 0x64,
		0x64, 0xC8, 0xC8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC8, 0x00, 0xC8, 0x01, 0x90, 0x00, 0x03, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0xC8, 0xC8, 0x01, 0x90, 0xC8, 0xC8, 0x00, 0x02, 0x00, 0x00,
		0xFF, 0x38, 0x01, 0x2C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x3B, 0x01, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x23, 0xC8, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x00, 0x0A, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x27, 0x00, 0x00, 0x11, 0x35, 0x33, 0x15,
		0x33, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x07, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x15, 0x05, 0x35, 0x33, 0x15,
		0x33, 0x35, 0x33, 0x15, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x17, 0x15, 0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x1D, 0x01, 0x23, 0x35, 0x05, 0x33, 0x15, 0x23,
		0x31, 0x15, 0x21, 0x35, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0x64, 0x64,
		0x64, 0x64, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x17, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23, 0x25, 0x15, 0x23, 0x35,
		0x1D, 0x01, 0x21, 0x35, 0x05, 0x35, 0x33, 0x11, 0x23, 0x11, 0x21, 0x11, 0x23, 0x11, 0x33, 0x15, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x02,
		0xBC, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xFE, 0x0C, 0x01, 0x2C, 0xFE, 0xD4, 0x01, 0xF4, 0x64, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x13, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x03, 0x35, 0x21, 0x15, 0x31, 0x33, 0x11, 0x23, 0x35, 0x21, 0x15, 0x23, 0x11, 0x33, 0x15, 0x21, 0x01, 0x2C, 0x64, 0x64, 0x01, 0x2C,
		0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x02, 0xBC, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xFE, 0x70, 0xC8, 0xC8, 0x01, 0x90, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x15, 0x00, 0x00, 0x01, 0x15, 0x33, 0x15, 0x23, 0x11, 0x33, 0x15, 0x21, 0x11, 0x23, 0x11, 0x23, 0x11, 0x33, 0x15, 0x33, 0x35, 0x23, 0x35, 0x21, 0x15, 0x01, 0x2C, 0x64, 0x64,
		0xC8, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90, 0x02, 0x58, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x01, 0x90, 0xFE, 0x70, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x07, 0x00, 0x00,
		0xFF, 0x38, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x33, 0x11, 0x23, 0x01, 0x23,
		0x35, 0x33, 0x11, 0x15, 0x23, 0x35, 0x05, 0x35, 0x21, 0x15, 0x17, 0x23, 0x35, 0x33, 0x05, 0x33, 0x15, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4,
		0x01, 0x2C, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0xC8, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x01, 0x90, 0x64, 0xFE, 0x70, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00,
		0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x0B, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x13, 0x33, 0x15, 0x23, 0x11, 0x23, 0x11, 0x33,
		0x21, 0x33, 0x11, 0x23, 0x35, 0x23, 0x35, 0x33, 0x27, 0x33, 0x15, 0x23, 0x01, 0xF4, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x02, 0xBC,
		0x64, 0x64, 0xFE, 0xD4, 0x64, 0xFE, 0xD4, 0x01, 0xF4, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x0B, 0x00, 0x13,
		0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x03, 0x23, 0x15, 0x23, 0x11, 0x33, 0x11, 0x33, 0x13, 0x33, 0x11, 0x23, 0x11, 0x23, 0x35, 0x33, 0x07, 0x35, 0x33, 0x15, 0x17, 0x15,
		0x21, 0x35, 0x64, 0x01, 0x2C, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x01, 0xF4, 0xFE, 0xD4, 0x01,
		0x2C, 0xFE, 0x0C, 0x01, 0x2C, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13,
		0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x21, 0x33, 0x15, 0x23, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64,
		0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x01, 0x90, 0xFE, 0x70, 0x64, 0x64, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x11, 0x00, 0x15, 0x00, 0x00, 0x13, 0x23, 0x35, 0x33, 0x17, 0x15, 0x21, 0x35, 0x05, 0x33, 0x11, 0x21, 0x35, 0x21, 0x35, 0x21, 0x35, 0x21, 0x05, 0x33, 0x15, 0x23, 0xC8, 0xC8,
		0xC8, 0xC8, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x70, 0x64, 0x64, 0x02, 0x58, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x11, 0x00, 0x15, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x17, 0x15, 0x21, 0x35,
		0x05, 0x35, 0x33, 0x11, 0x21, 0x35, 0x21, 0x35, 0x21, 0x35, 0x07, 0x33, 0x15, 0x23, 0x01, 0xF4, 0xC8, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x64,
		0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x19, 0x00, 0x1D, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x21, 0x33, 0x15, 0x23, 0x21, 0x23, 0x35, 0x33, 0x07, 0x15, 0x21, 0x35, 0x05, 0x35, 0x33, 0x11, 0x21, 0x35, 0x21, 0x35,
		0x21, 0x35, 0x07, 0x33, 0x15, 0x23, 0x64, 0x01, 0x2C, 0xFE, 0x70, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x64,
		0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x11, 0x00, 0x15, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x17, 0x15, 0x21, 0x35, 0x05, 0x33, 0x11, 0x21, 0x35, 0x21, 0x35, 0x21, 0x35, 0x21, 0x05, 0x33, 0x15, 0x23, 0x01, 0x2C,
		0x64, 0xC8, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x70, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x00, 0x13, 0x33, 0x15, 0x23, 0x25, 0x15,
		0x23, 0x35, 0x13, 0x23, 0x15, 0x33, 0x15, 0x21, 0x35, 0x33, 0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x15, 0x3B, 0x01, 0x23, 0x35, 0x33, 0x05, 0x33, 0x15, 0x23, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64,
		0x64, 0x64, 0xC8, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0xC8, 0x64, 0x00, 0x00, 0x07, 0x00, 0x00, 0xFF, 0x38, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x15,
		0x21, 0x35, 0x07, 0x33, 0x11, 0x23, 0x25, 0x23, 0x35, 0x33, 0x1D, 0x01, 0x23, 0x35, 0x05, 0x35, 0x21, 0x15, 0x17, 0x23, 0x35, 0x33, 0x05, 0x33, 0x15, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64,
		0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0xC8, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0xC8, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x64, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x19, 0x00, 0x1D, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15,
		0x21, 0x33, 0x15, 0x23, 0x21, 0x23, 0x35, 0x33, 0x07, 0x15, 0x21, 0x35, 0x05, 0x35, 0x33, 0x15, 0x21, 0x15, 0x23, 0x11, 0x33, 0x15, 0x11, 0x35, 0x21, 0x15, 0x64, 0x01, 0x2C, 0xFE, 0x70, 0x64,
		0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x01, 0x90, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x01, 0x2C,
		0x64, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x15, 0x00, 0x19, 0x00, 0x00, 0x13, 0x15,
		0x23, 0x35, 0x21, 0x15, 0x23, 0x35, 0x03, 0x35, 0x21, 0x15, 0x31, 0x33, 0x15, 0x21, 0x15, 0x23, 0x11, 0x33, 0x15, 0x21, 0x01, 0x35, 0x21, 0x15, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0x01, 0x2C,
		0x64, 0xFE, 0x70, 0x64, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x01, 0x90, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x15, 0x33, 0x11, 0x23, 0xC8, 0xC8, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64,
		0xC8, 0xFE, 0x0C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2C, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x3B, 0x01, 0x15, 0x23, 0x07, 0x33,
		0x11, 0x23, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x09, 0x00, 0x0D, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x05, 0x15, 0x21, 0x11, 0x23, 0x11, 0x05, 0x33, 0x11, 0x23, 0x01, 0xF4, 0xFE, 0x0C, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x01, 0x90, 0x64,
		0x64, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0xFE, 0x70, 0x01, 0xF4, 0x64, 0xFE, 0x70, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x13, 0x23, 0x35, 0x33, 0x03, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0xC8, 0xC8, 0xC8, 0x64, 0x01, 0x2C,
		0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x03, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33,
		0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0x01, 0xF4, 0xC8, 0xC8, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0xBC, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xFE, 0xD4,
		0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B,
		0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x21, 0x33, 0x15, 0x23, 0x21, 0x23, 0x35, 0x33, 0x07, 0x15, 0x21, 0x35, 0x11, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0x64, 0x01,
		0x2C, 0xFE, 0x70, 0x64, 0x64, 0x01, 0xF4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70, 0x01,
		0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x00,
		0x13, 0x15, 0x23, 0x35, 0x21, 0x15, 0x23, 0x35, 0x03, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0x01, 0x2C,
		0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x03, 0x00, 0x00,
		0x00, 0x64, 0x01, 0xF4, 0x02, 0x58, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x05, 0x15, 0x21, 0x35, 0x13, 0x35, 0x33, 0x15, 0x01, 0x2C, 0x64, 0x01, 0x2C, 0xFE,
		0x0C, 0xC8, 0x64, 0x02, 0x58, 0x64, 0x64, 0xC8, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x09, 0x00, 0x17, 0x00, 0x1B,
		0x00, 0x00, 0x01, 0x33, 0x11, 0x23, 0x35, 0x23, 0x35, 0x23, 0x35, 0x21, 0x03, 0x33, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x23, 0x11, 0x33, 0x15, 0x33, 0x31, 0x35, 0x33, 0x15, 0x01, 0x90,
		0x64, 0x64, 0x64, 0xC8, 0x01, 0x2C, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90, 0xFE, 0xD4, 0xC8, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C, 0xC8, 0x64,
		0x64, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0D, 0x00, 0x00, 0x13, 0x23, 0x35, 0x33, 0x03, 0x23, 0x11, 0x33, 0x21, 0x33,
		0x11, 0x21, 0x35, 0x21, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0x02, 0x58, 0x64, 0xFD, 0xA8, 0x01, 0x90, 0xFE, 0x0C, 0x64, 0x00, 0x00, 0x03, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0D, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x03, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x21, 0x35, 0x21, 0x01, 0xF4, 0xC8, 0xC8,
		0x64, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0x02, 0xBC, 0x64, 0x64, 0xFD, 0xA8, 0x01, 0x90, 0xFE, 0x0C, 0x64, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03,
		0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x15, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x35, 0x33, 0x15, 0x25, 0x33, 0x15, 0x23, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x21, 0x35, 0x21,
		0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0x02, 0xBC, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70,
		0x01, 0x2C, 0xFE, 0x70, 0x64, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x11, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35,
		0x21, 0x15, 0x23, 0x35, 0x03, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x21, 0x35, 0x21, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0x64, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x70, 0x01, 0x2C, 0x02, 0xBC, 0x64,
		0x64, 0x64, 0x64, 0xFD, 0xA8, 0x01, 0x90, 0xFE, 0x0C, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x13, 0x00, 0x17,
		0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0x21, 0x15, 0x23, 0x35, 0x03, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x35, 0x21, 0x35, 0x21, 0x1D, 0x01, 0x21, 0x35, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xC8,
		0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xFE, 0x70, 0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x01, 0x2C, 0xFE, 0x0C, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x00, 0x00, 0x00,
		0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x33, 0x15, 0x2B, 0x01, 0x33, 0x15, 0x33, 0x15, 0x23,
		0x15, 0x23, 0x35, 0x23, 0x35, 0x33, 0x37, 0x33, 0x15, 0x23, 0x01, 0x33, 0x15, 0x23, 0x17, 0x35, 0x33, 0x15, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64,
		0xFE, 0x70, 0x64, 0x64, 0x64, 0x64, 0x02, 0xBC, 0x64, 0xC8, 0x64, 0xC8, 0xC8, 0x64, 0xC8, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x11, 0x00, 0x17, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x07, 0x33, 0x11, 0x23, 0x01, 0x33, 0x11, 0x23, 0x05, 0x33, 0x35, 0x33, 0x15, 0x23,
		0x25, 0x33, 0x15, 0x33, 0x15, 0x23, 0x01, 0x90, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x01, 0x90, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x64, 0xC8, 0x01, 0x2C, 0x64, 0x64, 0xC8, 0x02, 0xBC, 0x64, 0x64, 0x64,
		0xFE, 0x70, 0x01, 0x90, 0xFE, 0x70, 0x64, 0x64, 0xC8, 0xC8, 0x64, 0x64, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2C, 0x01, 0xF4, 0x01, 0x90, 0x00, 0x03, 0x00, 0x00, 0x01, 0x15, 0x21, 0x35, 0x01, 0xF4,
		0xFE, 0x0C, 0x01, 0x90, 0x64, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC8, 0x00, 0xC8, 0x01, 0x90, 0x00, 0x03, 0x00, 0x00, 0x13, 0x15, 0x23, 0x35, 0xC8, 0xC8, 0x01, 0x90, 0xC8, 0xC8,
		0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35, 0x21, 0x15, 0x23, 0x35, 0x13, 0x23,
		0x35, 0x33, 0x17, 0x23, 0x35, 0x33, 0x07, 0x35, 0x33, 0x15, 0x23, 0x33, 0x15, 0x21, 0x35, 0x33, 0x15, 0x21, 0x01, 0xF4, 0x64, 0xFE, 0xD4, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64,
		0xC8, 0x64, 0x01, 0x2C, 0x64, 0xFE, 0x0C, 0x02, 0xBC, 0xC8, 0x64, 0x64, 0xC8, 0xFE, 0xD4, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x20,
		0x02, 0xBC, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x15, 0x23, 0x11, 0x21, 0x35, 0x23, 0x35, 0x23, 0x35, 0x23, 0x35, 0x21, 0x15, 0x33, 0x11, 0x03, 0x20, 0xC8, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x01, 0x2C,
		0x64, 0x02, 0xBC, 0x64, 0xFD, 0xA8, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x64, 0x02, 0xBC, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x23, 0x35, 0x33, 0x05, 0x23, 0x35, 0x33, 0x05, 0x15, 0x23, 0x35, 0x21, 0x15, 0x23, 0x35, 0x21, 0x33, 0x15, 0x23, 0x21, 0x33,
		0x15, 0x23, 0x25, 0x33, 0x15, 0x23, 0x01, 0x2C, 0xC8, 0xC8, 0x01, 0x2C, 0xC8, 0xC8, 0xFE, 0x0C, 0x64, 0x01, 0x90, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0x0C, 0xC8, 0xC8, 0x01, 0x2C, 0xC8, 0xC8,
		0x01, 0x90, 0x64, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x64, 0x02, 0xBC, 0x02, 0x58, 0x00, 0x0F, 0x00, 0x1F, 0x00, 0x00,
		0x01, 0x15, 0x23, 0x15, 0x21, 0x35, 0x23, 0x15, 0x23, 0x35, 0x33, 0x35, 0x21, 0x15, 0x33, 0x35, 0x11, 0x33, 0x15, 0x23, 0x15, 0x21, 0x35, 0x23, 0x15, 0x23, 0x35, 0x33, 0x35, 0x21, 0x15, 0x33,
		0x02, 0xBC, 0x64, 0xFE, 0xD4, 0x64, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0xC8, 0x64, 0xFE, 0xD4, 0x64, 0xC8, 0x64, 0x01, 0x2C, 0x64, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE,
		0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x01, 0xF4, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x13, 0x00, 0x00, 0x01, 0x15, 0x23, 0x35,
		0x1D, 0x01, 0x23, 0x35, 0x05, 0x23, 0x35, 0x33, 0x15, 0x33, 0x11, 0x21, 0x11, 0x33, 0x15, 0x21, 0x01, 0x2C, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x64, 0x01, 0x2C, 0x01, 0xF4,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x01, 0x2C, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xFF, 0x9C, 0x03, 0x20, 0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B,
		0x00, 0x0F, 0x00, 0x13, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x01, 0x15, 0x23, 0x35, 0x05, 0x35, 0x33, 0x1D, 0x02, 0x23,
		0x15, 0x23, 0x35, 0x23, 0x35, 0x01, 0x15, 0x21, 0x35, 0x64, 0x02, 0x58, 0xFD, 0xA8, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0xFE, 0x70, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xC8, 0x64, 0x01, 0xF4, 0xFD,
		0xA8, 0x02, 0x58, 0x64, 0x64, 0xFD, 0xA8, 0x02, 0x58, 0xFD, 0xA8, 0x01, 0xF4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x04, 0x00, 0x00,
		0xFF, 0x9C, 0x03, 0x20, 0x02, 0xBC, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x33, 0x11, 0x23, 0x15, 0x21, 0x35, 0x23, 0x11, 0x33, 0x35, 0x21, 0x05, 0x15, 0x33, 0x35,
		0x05, 0x35, 0x23, 0x15, 0x17, 0x35, 0x21, 0x15, 0x33, 0x15, 0x33, 0x35, 0x02, 0xBC, 0x64, 0x64, 0xFD, 0xA8, 0x64, 0x64, 0x02, 0x58, 0xFE, 0x0C, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0x70, 0x64,
		0xC8, 0x02, 0x58, 0xFD, 0xA8, 0x64, 0x64, 0x02, 0x58, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0xFF, 0x9C, 0x03, 0x20,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x17, 0x00, 0x1B, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x27, 0x00, 0x2B, 0x00, 0x2F, 0x00, 0x33, 0x00, 0x37, 0x00, 0x00, 0x11, 0x33, 0x15, 0x23, 0x05, 0x33, 0x15, 0x33,
		0x15, 0x23, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x35, 0x33, 0x21, 0x15, 0x23, 0x35, 0x05, 0x33, 0x15, 0x23, 0x25, 0x15, 0x23, 0x35, 0x07, 0x23, 0x15, 0x33,
		0x05, 0x35, 0x33, 0x15, 0x21, 0x23, 0x35, 0x33, 0x05, 0x35, 0x33, 0x15, 0x21, 0x23, 0x35, 0x33, 0x64, 0x64, 0x01, 0xF4, 0x64, 0xC8, 0xC8, 0x64, 0xC8, 0x64, 0xC8, 0xC8, 0x64, 0xC8, 0x01, 0x2C,
		0x64, 0xFD, 0xA8, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0xC8, 0xC8, 0xFE, 0x70, 0x64, 0x01, 0xF4, 0x64, 0x64, 0xFD, 0x44, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x02, 0xBC, 0x64, 0x64, 0x64, 0xC8, 0x64,
		0xC8, 0xC8, 0x64, 0xC8, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0xC8, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x00, 0x00, 0x04, 0x00, 0x00, 0xFF, 0x9C, 0x01, 0xF4,
		0x02, 0xBC, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x1B, 0x00, 0x00, 0x13, 0x35, 0x21, 0x15, 0x01, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x23, 0x15, 0x33, 0x15, 0x23, 0x15,
		0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x23, 0x35, 0x64, 0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x02, 0x58, 0x64, 0x64, 0xFE, 0xD4,
		0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x06, 0x00, 0x00, 0xFF, 0x9C, 0x02, 0xBC, 0x02, 0xBC, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x17,
		0x00, 0x1B, 0x00, 0x00, 0x01, 0x11, 0x23, 0x35, 0x23, 0x35, 0x23, 0x35, 0x11, 0x35, 0x33, 0x15, 0x23, 0x15, 0x21, 0x35, 0x11, 0x23, 0x11, 0x33, 0x21, 0x33, 0x11, 0x23, 0x31, 0x15, 0x21, 0x35,
		0x02, 0xBC, 0x64, 0x64, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0xFE, 0xD4, 0x02, 0xBC, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x70,
		0x01, 0x2C, 0xFE, 0xD4, 0x64, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x9C, 0x02, 0xBC, 0x02, 0xBC, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x33, 0x15, 0x23, 0x15, 0x23, 0x15, 0x33, 0x15, 0x21,
		0x35, 0x33, 0x35, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x35, 0x33, 0x35, 0x33, 0x15, 0x33, 0x15, 0x33, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
		0x64, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0xC8, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x9C, 0x02, 0xBC, 0x02, 0xBC, 0x00, 0x1B,
		0x00, 0x00, 0x01, 0x15, 0x23, 0x15, 0x23, 0x15, 0x33, 0x15, 0x21, 0x35, 0x33, 0x35, 0x23, 0x35, 0x23, 0x35, 0x33, 0x35, 0x23, 0x35, 0x33, 0x35, 0x21, 0x15, 0x33, 0x15, 0x23, 0x15, 0x02, 0xBC,
		0x64, 0x64, 0x64, 0xFE, 0x0C, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x01, 0x2C, 0x64, 0x64, 0x01, 0x90, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00,
		0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0xBC, 0x02, 0xBC, 0x00, 0x17, 0x00, 0x00, 0x01, 0x33, 0x11, 0x23, 0x15, 0x23, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x23, 0x35, 0x23, 0x11, 0x33,
		0x35, 0x33, 0x15, 0x33, 0x35, 0x33, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0xC8, 0x64, 0xC8, 0x02, 0x58, 0xFE, 0xD4, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x2C,
		0x64, 0x64, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0xBC, 0x02, 0xBC, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x33, 0x15, 0x23, 0x15, 0x23, 0x15, 0x23, 0x15, 0x23, 0x35, 0x23, 0x35, 0x23,
		0x35, 0x23, 0x35, 0x33, 0x35, 0x33, 0x35, 0x33, 0x35, 0x33, 0x15, 0x33, 0x15, 0x33, 0x02, 0x58, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x01, 0x90,
		0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0xF6, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21,
		0x00, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x09, 0x00, 0x7A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x00, 0x94, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x03, 0x00, 0x1C, 0x00, 0xD6, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x11, 0x01, 0x17, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x3C, 0x01, 0xA3, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x11, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x02, 0x38, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x0C,
		0x02, 0x63, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x17, 0x02, 0xA0, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09,
		0x00, 0x01, 0x00, 0x12, 0x00, 0x66, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x02, 0x00, 0x0E, 0x00, 0x84, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x03, 0x00, 0x38, 0x00, 0x9C, 0x00, 0x03,
		0x00, 0x01, 0x04, 0x09, 0x00, 0x04, 0x00, 0x22, 0x00, 0xF3, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x05, 0x00, 0x78, 0x01, 0x29, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x06, 0x00, 0x22,
		0x01, 0xE0, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x08, 0x00, 0x20, 0x02, 0x16, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09, 0x00, 0x09, 0x00, 0x18, 0x02, 0x49, 0x00, 0x03, 0x00, 0x01, 0x04, 0x09,
		0x00, 0x0D, 0x00, 0x2E, 0x02, 0x70, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x70, 0x00, 0x79, 0x00, 0x72, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x20, 0x00, 0xA9, 0x00, 0x20, 0x00, 0x32,
		0x00, 0x30, 0x00, 0x31, 0x00, 0x37, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4A, 0x00, 0x61, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x62, 0x00, 0x20, 0x00, 0x44, 0x00, 0x65, 0x00, 0x62,
		0x00, 0x6F, 0x00, 0x6E, 0x00, 0x6F, 0x00, 0x2E, 0x00, 0x00, 0x43, 0x6F, 0x70, 0x79, 0x72, 0x69, 0x67, 0x68, 0x74, 0x20, 0xA9, 0x20, 0x32, 0x30, 0x31, 0x37, 0x20, 0x62, 0x79, 0x20, 0x4A, 0x61,
		0x63, 0x6F, 0x62, 0x20, 0x44, 0x65, 0x62, 0x6F, 0x6E, 0x6F, 0x2E, 0x00, 0x00, 0x4D, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x65, 0x00, 0x63, 0x00, 0x72, 0x00, 0x61, 0x00, 0x66, 0x00, 0x74, 0x00, 0x00,
		0x4D, 0x69, 0x6E, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x00, 0x00, 0x52, 0x00, 0x65, 0x00, 0x67, 0x00, 0x75, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x72, 0x00, 0x00, 0x52, 0x65, 0x67, 0x75, 0x6C, 0x61,
		0x72, 0x00, 0x00, 0x31, 0x00, 0x2E, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3B, 0x00, 0x55, 0x00, 0x4B, 0x00, 0x57, 0x00, 0x4E, 0x00, 0x3B, 0x00, 0x4D, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x65,
		0x00, 0x63, 0x00, 0x72, 0x00, 0x61, 0x00, 0x66, 0x00, 0x74, 0x00, 0x2D, 0x00, 0x52, 0x00, 0x65, 0x00, 0x67, 0x00, 0x75, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x72, 0x00, 0x00, 0x31, 0x2E, 0x30, 0x30,
		0x30, 0x3B, 0x55, 0x4B, 0x57, 0x4E, 0x3B, 0x4D, 0x69, 0x6E, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x2D, 0x52, 0x65, 0x67, 0x75, 0x6C, 0x61, 0x72, 0x00, 0x00, 0x4D, 0x00, 0x69, 0x00, 0x6E, 0x00,
		0x65, 0x00, 0x63, 0x00, 0x72, 0x00, 0x61, 0x00, 0x66, 0x00, 0x74, 0x00, 0x20, 0x00, 0x52, 0x00, 0x65, 0x00, 0x67, 0x00, 0x75, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x72, 0x00, 0x00, 0x4D, 0x69, 0x6E,
		0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x20, 0x52, 0x65, 0x67, 0x75, 0x6C, 0x61, 0x72, 0x00, 0x00, 0x56, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x20, 0x00,
		0x31, 0x00, 0x2E, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3B, 0x00, 0x50, 0x00, 0x53, 0x00, 0x20, 0x00, 0x30, 0x00, 0x30, 0x00, 0x31, 0x00, 0x2E, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00,
		0x3B, 0x00, 0x68, 0x00, 0x6F, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x76, 0x00, 0x20, 0x00, 0x31, 0x00, 0x2E, 0x00, 0x30, 0x00, 0x2E, 0x00, 0x38, 0x00, 0x38, 0x00, 0x3B, 0x00,
		0x6D, 0x00, 0x61, 0x00, 0x6B, 0x00, 0x65, 0x00, 0x6F, 0x00, 0x74, 0x00, 0x66, 0x00, 0x2E, 0x00, 0x6C, 0x00, 0x69, 0x00, 0x62, 0x00, 0x32, 0x00, 0x2E, 0x00, 0x35, 0x00, 0x2E, 0x00, 0x36, 0x00,
		0x34, 0x00, 0x37, 0x00, 0x37, 0x00, 0x35, 0x00, 0x00, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x31, 0x2E, 0x30, 0x30, 0x30, 0x3B, 0x50, 0x53, 0x20, 0x30, 0x30, 0x31, 0x2E, 0x30, 0x30,
		0x30, 0x3B, 0x68, 0x6F, 0x74, 0x63, 0x6F, 0x6E, 0x76, 0x20, 0x31, 0x2E, 0x30, 0x2E, 0x38, 0x38, 0x3B, 0x6D, 0x61, 0x6B, 0x65, 0x6F, 0x74, 0x66, 0x2E, 0x6C, 0x69, 0x62, 0x32, 0x2E, 0x35, 0x2E,
		0x36, 0x34, 0x37, 0x37, 0x35, 0x00, 0x00, 0x4D, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x65, 0x00, 0x63, 0x00, 0x72, 0x00, 0x61, 0x00, 0x66, 0x00, 0x74, 0x00, 0x2D, 0x00, 0x52, 0x00, 0x65, 0x00, 0x67,
		0x00, 0x75, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x72, 0x00, 0x00, 0x4D, 0x69, 0x6E, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x2D, 0x52, 0x65, 0x67, 0x75, 0x6C, 0x61, 0x72, 0x00, 0x00, 0x4A, 0x00, 0x44,
		0x00, 0x47, 0x00, 0x72, 0x00, 0x61, 0x00, 0x70, 0x00, 0x68, 0x00, 0x69, 0x00, 0x63, 0x00, 0x73, 0x00, 0x20, 0x00, 0x46, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x74, 0x00, 0x73, 0x00, 0x00, 0x4A, 0x44,
		0x47, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x73, 0x20, 0x46, 0x6F, 0x6E, 0x74, 0x73, 0x00, 0x00, 0x4A, 0x00, 0x61, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x62, 0x00, 0x20, 0x00, 0x44, 0x00, 0x65, 0x00,
		0x62, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x6F, 0x00, 0x00, 0x4A, 0x61, 0x63, 0x6F, 0x62, 0x20, 0x44, 0x65, 0x62, 0x6F, 0x6E, 0x6F, 0x00, 0x00, 0x46, 0x00, 0x72, 0x00, 0x65, 0x00, 0x65, 0x00, 0x20,
		0x00, 0x66, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x20, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x6D, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x72, 0x00, 0x63, 0x00, 0x69, 0x00, 0x61, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x55,
		0x00, 0x73, 0x00, 0x65, 0x00, 0x00, 0x46, 0x72, 0x65, 0x65, 0x20, 0x66, 0x6F, 0x72, 0x20, 0x43, 0x6F, 0x6D, 0x6D, 0x65, 0x72, 0x63, 0x69, 0x61, 0x6C, 0x20, 0x55, 0x73, 0x65, 0x00, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xB5, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x9F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08, 0x00, 0x09, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x0E,
		0x00, 0x0F, 0x00, 0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x13, 0x00, 0x14, 0x00, 0x15, 0x00, 0x16, 0x00, 0x17, 0x00, 0x18, 0x00, 0x19, 0x00, 0x1A, 0x00, 0x1B, 0x00, 0x1C, 0x00, 0x1D, 0x00, 0x1E,
		0x00, 0x1F, 0x00, 0x20, 0x00, 0x21, 0x00, 0x22, 0x00, 0x23, 0x00, 0x24, 0x00, 0x25, 0x00, 0x26, 0x00, 0x27, 0x00, 0x28, 0x00, 0x29, 0x00, 0x2A, 0x00, 0x2B, 0x00, 0x2C, 0x00, 0x2D, 0x00, 0x2E,
		0x00, 0x2F, 0x00, 0x30, 0x00, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0x34, 0x00, 0x35, 0x00, 0x36, 0x00, 0x37, 0x00, 0x38, 0x00, 0x39, 0x00, 0x3A, 0x00, 0x3B, 0x00, 0x3C, 0x00, 0x3D, 0x00, 0x3E,
		0x00, 0x3F, 0x00, 0x40, 0x00, 0x41, 0x00, 0x42, 0x00, 0x44, 0x00, 0x45, 0x00, 0x46, 0x00, 0x47, 0x00, 0x48, 0x00, 0x49, 0x00, 0x4A, 0x00, 0x4B, 0x00, 0x4C, 0x00, 0x4D, 0x00, 0x4E, 0x00, 0x4F,
		0x00, 0x50, 0x00, 0x51, 0x00, 0x52, 0x00, 0x53, 0x00, 0x54, 0x00, 0x55, 0x00, 0x56, 0x00, 0x57, 0x00, 0x58, 0x00, 0x59, 0x00, 0x5A, 0x00, 0x5B, 0x00, 0x5C, 0x00, 0x5D, 0x00, 0x5E, 0x00, 0x5F,
		0x00, 0x60, 0x00, 0x61, 0x00, 0xA3, 0x00, 0x84, 0x00, 0x85, 0x00, 0xBD, 0x00, 0x86, 0x00, 0xA9, 0x00, 0xA4, 0x01, 0x02, 0x00, 0x8A, 0x00, 0x93, 0x00, 0x88, 0x00, 0xC3, 0x00, 0xDE, 0x00, 0xAA,
		0x00, 0xA2, 0x00, 0x62, 0x00, 0x63, 0x00, 0x90, 0x00, 0x64, 0x00, 0x66, 0x00, 0x91, 0x00, 0x68, 0x00, 0x6A, 0x00, 0x69, 0x00, 0x6B, 0x00, 0x6E, 0x00, 0xA0, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x73,
		0x00, 0x74, 0x00, 0x76, 0x00, 0x78, 0x00, 0x7A, 0x00, 0x79, 0x00, 0x7B, 0x00, 0x7C, 0x00, 0xB8, 0x00, 0xA1, 0x00, 0x7F, 0x00, 0x7E, 0x00, 0x80, 0x00, 0x81, 0x00, 0xBA, 0x00, 0xA6, 0x01, 0x03,
		0x00, 0xB3, 0x00, 0x87, 0x00, 0x99, 0x00, 0xA5, 0x00, 0x92, 0x00, 0xA7, 0x01, 0x04, 0x01, 0x05, 0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0x01, 0x09, 0x01, 0x0A, 0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D,
		0x07, 0x75, 0x6E, 0x69, 0x30, 0x30, 0x41, 0x44, 0x07, 0x75, 0x6E, 0x69, 0x30, 0x33, 0x41, 0x39, 0x05, 0x68, 0x6F, 0x75, 0x73, 0x65, 0x09, 0x73, 0x6D, 0x69, 0x6C, 0x65, 0x66, 0x61, 0x63, 0x65,
		0x0C, 0x69, 0x6E, 0x76, 0x73, 0x6D, 0x69, 0x6C, 0x65, 0x66, 0x61, 0x63, 0x65, 0x03, 0x73, 0x75, 0x6E, 0x06, 0x66, 0x65, 0x6D, 0x61, 0x6C, 0x65, 0x04, 0x6D, 0x61, 0x6C, 0x65, 0x05, 0x73, 0x70,
		0x61, 0x64, 0x65, 0x04, 0x63, 0x6C, 0x75, 0x62, 0x05, 0x68, 0x65, 0x61, 0x72, 0x74, 0x07, 0x64, 0x69, 0x61, 0x6D, 0x6F, 0x6E, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x02,
		0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
		0xDA, 0x53, 0x99, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x26, 0x06, 0x96, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x26, 0x06, 0x96,
	};
	static int unsigned sWorldFontProgram = 0;
	static int unsigned sScreenFontProgram = 0;
	static char const sWorldFontVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in uint VertexIndex;"
		"layout (location = 2) in vec3 InstancePivot;"
		"layout (location = 3) in vec3 InstancePosition;"
		"layout (location = 4) in vec3 InstanceRotation;"
		"layout (location = 5) in vec2 InstanceScale;"
		"layout (location = 6) in vec2 InstanceBearing;"
		"layout (location = 7) in float InstanceUnitsPerEm;"
		"layout (location = 8) in float InstanceFontSize;"
		"layout (location = 9) in vec2 InstanceGlyphSize;"
		"layout (location = 10) in vec4 InstanceColor;"
		"layout (location = 11) in uint InstanceGlyphIndex;"
		"layout (location = 12) in uint InstanceLineHeight;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} VertexOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec2 BearingSize = InstanceBearing / InstanceUnitsPerEm;"
		"	vec2 GlyphSize = InstanceGlyphSize / InstanceUnitsPerEm;"
		"	float U0 = BearingSize.x;"
		"	float V0 = (BearingSize.y - GlyphSize.y);"
		"	float U1 = (BearingSize.x + GlyphSize.x);"
		"	float V1 = BearingSize.y;"
		"	vec4 Rotation = EulerAnglesToQuaternion(radians(InstanceRotation.x), radians(InstanceRotation.y), radians(InstanceRotation.z));"
		"	Rotation = normalize(Rotation);"
		"	vec3 Position = InstancePosition + vec3(VertexPosition * GlyphSize, 0.0);"
		"	Position = RotateVector3D(Position, Rotation);"
		"	Position *= vec3(InstanceScale, 1.0);"
		"	vec4 WorldPosition = vec4(Position, 1.0);"
		"	vec4 ViewPosition = ViewMatrix * WorldPosition;"
		"	vec4 ClipPosition = ProjectionMatrix * ViewPosition;"
		"	gl_Position = ClipPosition;"
		"	vec2 TextureCoords;"
		"	switch (VertexIndex) {"
		"		case 0: TextureCoords = vec2(U0, V0); break;"
		"		case 1: TextureCoords = vec2(U1, V0); break;"
		"		case 2: TextureCoords = vec2(U0, V1); break;"
		"		case 3: TextureCoords = vec2(U1, V1); break;"
		"	}"
		"	VertexOutput.TextureCoords = TextureCoords;"
		"	VertexOutput.GlyphIndex = InstanceGlyphIndex;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sWorldFontFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"struct BezierOffsetEntry {"
		"	uint Start;"
		"	uint Num;"
		"};"
		"struct BezierCurveEntry {"
		"	vec2 P0;"
		"	vec2 P1;"
		"	vec2 P2;"
		"};"
		"layout (std430, binding = 0) buffer BezierOffset {"
		"	BezierOffsetEntry Offsets[];"
		"} BezierOffsets;"
		"layout (std430, binding = 1) buffer BezierCurve {"
		"	BezierCurveEntry Curves[];"
		"} BezierCurves;"
		"uniform float AntiAliasingWindowSize = 1.0;"
		"uniform bool EnableSuperSamplingAntiAliasing = false;"
		"vec2 Rotate(vec2 V)"
		"{"
		"	return vec2(V.y, -V.x);"
		"}"
		"float ComputeCoverage(float InverseDiameter, vec2 P0, vec2 P1, vec2 P2)"
		"{"
		"	if (P0.y > 0.0 && P1.y > 0.0 && P2.y > 0.0) return 0.0;"
		"	if (P0.y < 0.0 && P1.y < 0.0 && P2.y < 0.0) return 0.0;"
		"	vec2 A = P0 - 2.0 * P1 + P2;"
		"	vec2 B = P0 - P1;"
		"	vec2 C = P0;"
		"	float T0 = 0.0;"
		"	float T1 = 0.0;"
		"	if (abs(A.y) >= 1e-5)"
		"	{"
		"		float Radicand = B.y * B.y - A.y * C.y;"
		"		if (Radicand <= 0.0) return 0.0;"
		"		float S = sqrt(Radicand);"
		"		T0 = (B.y - S) / A.y;"
		"		T1 = (B.y + S) / A.y;"
		"	}"
		"	else"
		"	{"
		"		float T = P0.y / (P0.y - P2.y);"
		"		if (P0.y < P2.y)"
		"		{"
		"			T0 = -1.0;"
		"			T1 = T;"
		"		}"
		"		else"
		"		{"
		"			T0 = T;"
		"			T1 = -1.0;"
		"		}"
		"	}"
		"	float Alpha = 0.0;"
		"	if (T0 >= 0.0 && T0 < 1.0)"
		"	{"
		"		float X = (A.x * T0 - 2.0 * B.x) * T0 + C.x;"
		"		Alpha += clamp(X * InverseDiameter + 0.5, 0.0, 1.0);"
		"	}"
		"	if (T1 >= 0.0 && T1 < 1.0)"
		"	{"
		"		float X = (A.x * T1 - 2.0 * B.x) * T1 + C.x;"
		"		Alpha -= clamp(X * InverseDiameter + 0.5, 0.0, 1.0);"
		"	}"
		"	return Alpha;"
		"}"
		"void main() {"
		"	float Alpha = 0.0;"
		"	vec2 InverseDiameter = 1.0 / (AntiAliasingWindowSize * fwidth(FragmentInput.TextureCoords));"
		"	BezierOffsetEntry BezierOffset = BezierOffsets.Offsets[FragmentInput.GlyphIndex];"
		"	for (uint CurveIndex = BezierOffset.Start; CurveIndex < (BezierOffset.Start + BezierOffset.Num); CurveIndex++)"
		"	{"
		"		BezierCurveEntry BezierCurve = BezierCurves.Curves[CurveIndex];"
		"		vec2 P0 = BezierCurve.P0 - FragmentInput.TextureCoords;"
		"		vec2 P1 = BezierCurve.P1 - FragmentInput.TextureCoords;"
		"		vec2 P2 = BezierCurve.P2 - FragmentInput.TextureCoords;"
		"		Alpha += ComputeCoverage(InverseDiameter.x, P0, P1, P2);"
		"		if (EnableSuperSamplingAntiAliasing)"
		"		{"
		"			Alpha += ComputeCoverage(InverseDiameter.y, Rotate(P0), Rotate(P1), Rotate(P2));"
		"		}"
		"	}"
		"	if (EnableSuperSamplingAntiAliasing)"
		"	{"
		"		Alpha *= 0.5;"
		"	}"
		"	Alpha = clamp(Alpha, 0.0, 1.0);"
		"	if (Alpha <= 0.0) discard;"
		"	BaseColor = FragmentInput.Color * Alpha;"
		"}";
	static char const sScreenFontVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in uint VertexIndex;"
		"layout (location = 2) in vec3 InstancePivot;"
		"layout (location = 3) in vec2 InstancePosition;"
		"layout (location = 4) in float InstanceRotation;"
		"layout (location = 5) in vec2 InstanceBearing;"
		"layout (location = 6) in float InstanceUnitsPerEm;"
		"layout (location = 7) in float InstanceFontSize;"
		"layout (location = 8) in vec2 InstanceGlyphSize;"
		"layout (location = 9) in vec4 InstanceColor;"
		"layout (location = 10) in uint InstanceGlyphIndex;"
		"layout (location = 11) in uint InstanceLineHeight;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} VertexOutput;"
		"uniform vec2 ScreenSize;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		GLSL_SCREEN_SPACE_IMPLEMENTATION
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec2 BearingSize = InstanceBearing / InstanceUnitsPerEm; "
		"	vec2 GlyphSize = InstanceGlyphSize / InstanceUnitsPerEm;"
		"	vec2 LineHeight = vec2(0.0, InstanceLineHeight) / InstanceUnitsPerEm;"
		"	float Roll = radians(InstanceRotation);"
		"	float U0 = BearingSize.x;"
		"	float V0 = (BearingSize.y + GlyphSize.y);"
		"	float U1 = (BearingSize.x + GlyphSize.x);"
		"	float V1 = BearingSize.y;"
		"	vec2 RotatedPosition = RotateVector2D(InstancePosition - InstancePivot.xy + (VertexPosition * GlyphSize * InstanceFontSize), Roll);"
		"	vec3 ScreenPosition = vec3(RotatedPosition + InstancePivot.xy, InstancePivot.z);"
		"	gl_Position = ScreenToClipSpace(ScreenPosition, ScreenSize);"
		"	vec2 TextureCoords;"
		"	switch (VertexIndex) {"
		"		case 0: TextureCoords = vec2(U0, V0); break;"
		"		case 1: TextureCoords = vec2(U1, V0); break;"
		"		case 2: TextureCoords = vec2(U0, V1); break;"
		"		case 3: TextureCoords = vec2(U1, V1); break;"
		"	}"
		"	VertexOutput.TextureCoords = TextureCoords;"
		"	VertexOutput.GlyphIndex = InstanceGlyphIndex;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sScreenFontFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"struct BezierOffsetEntry {"
		"	uint Start;"
		"	uint Num;"
		"};"
		"struct BezierCurveEntry {"
		"	vec2 P0;"
		"	vec2 P1;"
		"	vec2 P2;"
		"};"
		"layout (std430, binding = 0) buffer BezierOffset {"
		"	BezierOffsetEntry Offsets[];"
		"} BezierOffsets;"
		"layout (std430, binding = 1) buffer BezierCurve {"
		"	BezierCurveEntry Curves[];"
		"} BezierCurves;"
		"uniform float AntiAliasingWindowSize = 1.0;"
		"uniform bool EnableSuperSamplingAntiAliasing = false;"
		"vec2 Rotate(vec2 V)"
		"{"
		"	return vec2(V.y, -V.x);"
		"}"
		"float ComputeCoverage(float InverseDiameter, vec2 P0, vec2 P1, vec2 P2)"
		"{"
		"	if (P0.y > 0.0 && P1.y > 0.0 && P2.y > 0.0) return 0.0;"
		"	if (P0.y < 0.0 && P1.y < 0.0 && P2.y < 0.0) return 0.0;"
		"	vec2 A = P0 - 2.0 * P1 + P2;"
		"	vec2 B = P0 - P1;"
		"	vec2 C = P0;"
		"	float T0 = 0.0;"
		"	float T1 = 0.0;"
		"	if (abs(A.y) >= 1e-5)"
		"	{"
		"		float Radicand = B.y * B.y - A.y * C.y;"
		"		if (Radicand <= 0.0) return 0.0;"
		"		float S = sqrt(Radicand);"
		"		T0 = (B.y - S) / A.y;"
		"		T1 = (B.y + S) / A.y;"
		"	}"
		"	else"
		"	{"
		"		float T = P0.y / (P0.y - P2.y);"
		"		if (P0.y < P2.y)"
		"		{"
		"			T0 = -1.0;"
		"			T1 = T;"
		"		}"
		"		else"
		"		{"
		"			T0 = T;"
		"			T1 = -1.0;"
		"		}"
		"	}"
		"	float Alpha = 0.0;"
		"	if (T0 >= 0.0 && T0 < 1.0)"
		"	{"
		"		float X = (A.x * T0 - 2.0 * B.x) * T0 + C.x;"
		"		Alpha += clamp(X * InverseDiameter + 0.5, 0.0, 1.0);"
		"	}"
		"	if (T1 >= 0.0 && T1 < 1.0)"
		"	{"
		"		float X = (A.x * T1 - 2.0 * B.x) * T1 + C.x;"
		"		Alpha -= clamp(X * InverseDiameter + 0.5, 0.0, 1.0);"
		"	}"
		"	return Alpha;"
		"}"
		"void main() {"
		"	float Alpha = 0.0;"
		"	vec2 InverseDiameter = 1.0 / (AntiAliasingWindowSize * fwidth(FragmentInput.TextureCoords));"
		"	BezierOffsetEntry BezierOffset = BezierOffsets.Offsets[FragmentInput.GlyphIndex];"
		"	for (uint CurveIndex = BezierOffset.Start; CurveIndex < (BezierOffset.Start + BezierOffset.Num); CurveIndex++)"
		"	{"
		"		BezierCurveEntry BezierCurve = BezierCurves.Curves[CurveIndex];"
		"		vec2 P0 = BezierCurve.P0 - FragmentInput.TextureCoords;"
		"		vec2 P1 = BezierCurve.P1 - FragmentInput.TextureCoords;"
		"		vec2 P2 = BezierCurve.P2 - FragmentInput.TextureCoords;"
		"		Alpha += ComputeCoverage(InverseDiameter.x, P0, P1, P2);"
		"		if (EnableSuperSamplingAntiAliasing)"
		"		{"
		"			Alpha += ComputeCoverage(InverseDiameter.y, Rotate(P0), Rotate(P1), Rotate(P2));"
		"		}"
		"	}"
		"	if (EnableSuperSamplingAntiAliasing)"
		"	{"
		"		Alpha *= 0.5;"
		"	}"
		"	Alpha = clamp(Alpha, 0.0, 1.0);"
		"	if (Alpha <= 0.0) discard;"
		"	BaseColor = FragmentInput.Color * Alpha;"
		"}";
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedFonts = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Text Definition
	///////////////////////////////////////////////////////////////

#ifndef FAST_GL_TEXT_FMT_BUFFER_SIZE
#define FAST_GL_TEXT_FMT_BUFFER_SIZE (0x1000ULL)
#endif // FAST_GL_TEXT_FMT_BUFFER_SIZE

	typedef struct _TextWorldCache
	{
		int unsigned GlyphVertexArray;
		int unsigned GlyphVertexBuffer;
		int unsigned GlyphInstanceBuffer;
		int unsigned GlyphIndexBuffer;
		int unsigned GlyphInstanceOffset;
	} TextWorldCache;
	typedef struct _TextScreenCache
	{
		int unsigned GlyphVertexArray;
		int unsigned GlyphVertexBuffer;
		int unsigned GlyphInstanceBuffer;
		int unsigned GlyphIndexBuffer;
		int unsigned GlyphInstanceOffset;
	} TextScreenCache;

	extern void Text_BeginWorld(Font* Fnt);
	extern void Text_DrawWorld(Vector3 const* Position, Vector3 const* Rotation, Vector2 const* Size, Color4 const* Color, char const* Format, ...);
	extern void Text_DrawWorldSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...);
	extern void Text_EndWorld(Matrix4x4 const* Projection, Matrix4x4 const* View);

	extern void Text_BeginScreen(Font* Fnt);
	extern void Text_DrawScreen(Vector3 const* Position, float Rotation, float Size, Color4 const* Color, char const* Format, ...);
	extern void Text_DrawScreenSimple(float PositionX, float PositionY, float PositionZ, float Rotation, float Size, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...);
	extern void Text_EndScreen(void);

	extern void TextCache_WorldAlloc(TextWorldCache* Cache, int unsigned NumChars);
	extern void TextCache_DrawWorldCache(TextWorldCache* Cache, Matrix4x4 const* Projection, Matrix4x4 const* View);
	extern void TextCache_WorldFree(TextWorldCache* Cache);

	extern void TextCache_ScreenAlloc(TextScreenCache* Cache, int unsigned NumChars);
	extern void TextCache_DrawScreenCache(TextScreenCache* Cache);
	extern void TextCache_ScreenFree(TextScreenCache* Cache);

	extern void TextCache_BeginWorldCache(TextWorldCache* Cache, Font* Fnt);
	extern void TextCache_DrawWorld(TextWorldCache* Cache, Vector3 const* Position, Vector3 const* Rotation, Vector2 const* Size, Color4 const* Color, char const* Format, ...);
	extern void TextCache_DrawWorldSimple(TextWorldCache* Cache, float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...);
	extern void TextCache_EndWorldCache(TextWorldCache* Cache);

	extern void TextCache_BeginScreenCache(TextScreenCache* Cache, Font* Fnt);
	extern void TextCache_DrawScreen(TextScreenCache* Cache, Vector3 const* Position, float Rotation, float Size, Color4 const* Color, char const* Format, ...);
	extern void TextCache_DrawScreenSimple(TextScreenCache* Cache, float PositionX, float PositionY, float PositionZ, float Rotation, float Size, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...);
	extern void TextCache_EndScreenCache(TextScreenCache* Cache);

#ifdef FAST_GL_IMPLEMENTATION
	static Font* sCurrFont = 0;
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedTextCaches = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Texture Definition
	///////////////////////////////////////////////////////////////

	typedef enum _TextureWrap
	{
		TEXTURE_WRAP_REPEAT = GL_REPEAT,
		TEXTURE_WRAP_MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		TEXTURE_WRAP_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		TEXTURE_WRAP_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	} TextureWrap;
	typedef enum _TextureFilter
	{
		TEXTURE_FILTER_NEAREST = GL_NEAREST,
		TEXTURE_FILTER_LINEAR = GL_LINEAR,
		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
	} TextureFilter;
	typedef enum _TextureType
	{
		TEXTURE_TYPE_UINT8 = GL_UNSIGNED_BYTE,
		TEXTURE_TYPE_REAL32 = GL_FLOAT,
		TEXTURE_TYPE_UINT24_UINT8 = GL_UNSIGNED_INT_24_8,
	} TextureType;
	typedef enum _TextureFormat
	{
		TEXTURE_FORMAT_RGBA = GL_RGBA,
		TEXTURE_FORMAT_RGB = GL_RGB,
		TEXTURE_FORMAT_RG = GL_RG,
		TEXTURE_FORMAT_R = GL_RED,
		TEXTURE_FORMAT_DEPTH_STENCIL = GL_DEPTH_STENCIL,
	} TextureFormat;
	typedef enum _TextureInternalFormat
	{
		TEXTURE_INTERNAL_FORMAT_RGBA = GL_RGBA,
		TEXTURE_INTERNAL_FORMAT_RGB = GL_RGB,
		TEXTURE_INTERNAL_FORMAT_RG = GL_RG,
		TEXTURE_INTERNAL_FORMAT_R = GL_RED,
		TEXTURE_INTERNAL_FORMAT_R_UINT8 = GL_R8UI,
		TEXTURE_INTERNAL_FORMAT_R_REAL32 = GL_R32F,
		TEXTURE_INTERNAL_FORMAT_RGB_UINT8 = GL_RGB8UI,
		TEXTURE_INTERNAL_FORMAT_RGB_REAL32 = GL_RGB32F,
		TEXTURE_INTERNAL_FORMAT_RGBA_UINT8 = GL_RGBA8UI,
		TEXTURE_INTERNAL_FORMAT_RGBA_REAL32 = GL_RGBA32F,
		TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
	} TextureInternalFormat;
	typedef struct _Texture2D
	{
		int unsigned Texture;
		int unsigned Width;
		int unsigned Height;
		TextureWrap WrapS;
		TextureWrap WrapT;
		TextureFilter MinFilter;
		TextureFilter MagFilter;
		TextureType Type;
		TextureFormat Format;
		TextureInternalFormat InternalFormat;
	} Texture2D;

	extern void Texture2D_Alloc(Texture2D* Texture);
	extern int unsigned Texture2D_GetWidth(Texture2D* Texture);
	extern int unsigned Texture2D_GetHeight(Texture2D* Texture);
	extern int unsigned Texture2D_GetTexture(Texture2D* Texture);
	extern void Texture2D_SetWidth(Texture2D* Texture, int unsigned Width);
	extern void Texture2D_SetHeight(Texture2D* Texture, int unsigned Height);
	extern void Texture2D_SetWrapS(Texture2D* Texture, TextureWrap WrapS);
	extern void Texture2D_SetWrapT(Texture2D* Texture, TextureWrap WrapT);
	extern void Texture2D_SetMinFilter(Texture2D* Texture, TextureFilter MinFilter);
	extern void Texture2D_SetMagFilter(Texture2D* Texture, TextureFilter MagFilter);
	extern void Texture2D_SetType(Texture2D* Texture, TextureType Type);
	extern void Texture2D_SetFormat(Texture2D* Texture, TextureFormat Format);
	extern void Texture2D_SetInternalFormat(Texture2D* Texture, TextureInternalFormat InternalFormat);
	extern void Texture2D_Bind(Texture2D* Texture);
	extern void Texture2D_MountSampler(Texture2D* Texture, int unsigned Index);
	extern void Texture2D_MountImageRead(Texture2D* Texture, int unsigned Index, TextureInternalFormat InternalFormat);
	extern void Texture2D_MountImageWrite(Texture2D* Texture, int unsigned Index, TextureInternalFormat InternalFormat);
	extern void Texture2D_MountImageReadWrite(Texture2D* Texture, int unsigned Index, TextureInternalFormat InternalFormat);
	extern void Texture2D_Update(Texture2D* Texture, bool GenerateMipMaps);
	extern void Texture2D_UpdatePixels(Texture2D* Texture, char unsigned* Pixels, bool GenerateMipMaps);
	extern void* Texture2D_CopyPixels(Texture2D* Texture);
	extern void Texture2D_Free(Texture2D* Texture);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedTexture2Ds = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// FrameBuffer Definition
	///////////////////////////////////////////////////////////////

	typedef struct _FrameBuffer
	{
		int unsigned FrameBuffer;
		int unsigned Width;
		int unsigned Height;
		int unsigned NumColorAttachments;
		Texture2D** ColorAttachments;
		Texture2D* DepthStencilAttachment;
		int unsigned* BufferAttachments;
	} FrameBuffer;

	extern void FrameBuffer_Alloc(FrameBuffer* Buffer, int unsigned NumColorAttachments, int unsigned Width, int unsigned Height);
	extern int unsigned FrameBuffer_GetColorAttachmentNum(FrameBuffer* Buffer);
	extern void FrameBuffer_SetWidth(FrameBuffer* Buffer, int unsigned Width);
	extern void FrameBuffer_SetHeight(FrameBuffer* Buffer, int unsigned Height);
	extern void FrameBuffer_SetColorAttachment(FrameBuffer* Buffer, int unsigned Index, Texture2D* Attachment);
	extern void FrameBuffer_SetDepthStencilAttachment(FrameBuffer* Buffer, Texture2D* Attachment);
	extern Texture2D* FrameBuffer_GetColorAttachment(FrameBuffer* Buffer, int unsigned Index);
	extern Texture2D* FrameBuffer_GetDepthStencilAttachment(FrameBuffer* Buffer);
	extern void FrameBuffer_Update(FrameBuffer* Buffer);
	extern void FrameBuffer_BindRead(FrameBuffer* Buffer);
	extern void FrameBuffer_BindWrite(FrameBuffer* Buffer);
	extern void FrameBuffer_BindReadWrite(FrameBuffer* Buffer);
	extern void FrameBuffer_UnBindRead(FrameBuffer* Buffer);
	extern void FrameBuffer_UnBindWrite(FrameBuffer* Buffer);
	extern void FrameBuffer_UnBindReadWrite(FrameBuffer* Buffer);
	extern void FrameBuffer_Free(FrameBuffer* Buffer);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedFrameBuffers = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// BitMap Definition
	///////////////////////////////////////////////////////////////

#pragma pack(push, 1)
	typedef struct _BitMapHeader
	{
		short unsigned Type;
		int unsigned Size;
		short unsigned Reserved0;
		short unsigned Reserved1;
		int unsigned OffBits;
	} BitMapHeader;
	typedef struct _BitMapInfoHeader
	{
		int unsigned Size;
		int Width;
		int Height;
		short Planes;
		short BitCount;
		int unsigned Compression;
		int unsigned SizeImage;
		int XPelsPerMeter;
		int YPelsPerMeter;
		int unsigned ClrUsed;
		int unsigned ClrImportant;
	} BitMapInfoHeader;
#pragma pack(pop)

	extern void BitMap_Alloc(char unsigned** Pixels, char const* FilePath, int unsigned* Width, int unsigned* Height);
	extern void BitMap_Free(char unsigned* Pixels);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedBitMaps = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Primitive Definition
	///////////////////////////////////////////////////////////////

	typedef struct _SpriteVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} SpriteVertex;
	typedef struct _SpriteMesh
	{
		int unsigned VertexArray;
		int unsigned VertexBuffer;
		int unsigned IndexBuffer;
	} SpriteMesh;
	typedef struct _InstancedSprite
	{
		int unsigned NumInstances;
		int unsigned VertexArray;
		int unsigned VertexBuffer;
		int unsigned InstanceBuffer;
		int unsigned IndexBuffer;
	} InstancedSprite;
	typedef struct _SpriteInstanceEntry
	{
		Matrix4x4 TransformMatrix;
		int unsigned AtlasIndex;
	} SpriteInstanceEntry;
	typedef struct _PostProcessVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} PostProcessVertex;
	typedef struct _PostProcessMesh
	{
		int unsigned VertexArray;
		int unsigned VertexBuffer;
		int unsigned IndexBuffer;
	} PostProcessMesh;

	extern void Primitive_SpriteAlloc(SpriteMesh* Mesh);
	extern int unsigned Primitive_GetSpriteVertexArray(SpriteMesh* Mesh);
	extern void Primitive_SpriteFree(SpriteMesh* Mesh);

	extern void Primitive_PostProcessAlloc(PostProcessMesh* Mesh);
	extern int unsigned Primitive_GetPostProcessVertexArray(PostProcessMesh* Mesh);
	extern void Primitive_PostProcessFree(PostProcessMesh* Mesh);

	extern void Primitive_InstancedSpriteAlloc(InstancedSprite* Mesh, int unsigned NumInstances);
	extern int unsigned Primitive_GetInstancedSpriteNumInstances(InstancedSprite* Mesh);
	extern int unsigned Primitive_GetInstancedSpriteVertexArray(InstancedSprite* Mesh);
	extern SpriteInstanceEntry* Primitive_InstancedSpriteMapBuffer(InstancedSprite* Mesh);
	extern void Primitive_InstancedSpriteUnMapBuffer(InstancedSprite* Mesh);
	extern void Primitive_InstancedSpriteFree(InstancedSprite* Mesh);

#ifdef FAST_GL_IMPLEMENTATION
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedPrimitives = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// SpritePlayer Definition
	///////////////////////////////////////////////////////////////

	typedef struct _SpritePlayer
	{
		Texture2D* Atlas;
	} SpritePlayer;

	extern void SpritePlayer_Alloc(SpritePlayer* Player, Texture2D* Atlas, int unsigned OffsetX, int unsigned OffsetY, int unsigned NumCellsX, int unsigned NumCellsY, int unsigned CellSizeX, int unsigned CellSizeY);
	extern void SpritePlayer_AddAnimationFromRange(SpritePlayer* Player, char const* AnimationName, int unsigned AtlasIndexFrom, int unsigned AtlasIndexTo);
	extern void SpritePlayer_Play(SpritePlayer* Player);
	extern void SpritePlayer_Pause(SpritePlayer* Player);
	extern void SpritePlayer_Stop(SpritePlayer* Player);
	extern void SpritePlayer_Free(SpritePlayer* Player);

	///////////////////////////////////////////////////////////////
	// PostProcessEffect Definition
	///////////////////////////////////////////////////////////////

	typedef struct _PostProcessEffect
	{
		int unsigned Program;
		PostProcessMesh* Mesh;
	} PostProcessEffect;

	extern void PostProcessEffect_Alloc(PostProcessEffect* Effect, PostProcessMesh* Mesh, char const* FragmentSource);
	extern void PostProcessEffect_Begin(PostProcessEffect* Effect);
	extern void PostProcessEffect_SetColorAttachment(PostProcessEffect* Effect, Texture2D* ColorAttachment, int unsigned ColorAttachmentMountIndex);
	extern void PostProcessEffect_End(PostProcessEffect* Effect);
	extern void PostProcessEffect_Free(PostProcessEffect* Effect);

	extern char const* PostProcessEffect_GetColorBlendFragmentShader(void);
	extern char const* PostProcessEffect_GetWeightedBlendedOrderIndependentTransparencyPostProcessFragmentShader(void);

#ifdef FAST_GL_IMPLEMENTATION
	static char const sPostProcessVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(VertexPosition, 0.0, 1.0);"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"}";
	char const sColorBlendPostProcessFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 FinalColor;"
		"layout (binding = 0) uniform sampler2D BaseColorSampler0;"
		"layout (binding = 1) uniform sampler2D BaseColorSampler1;"
		"vec4 BlendColor(vec4 Source, vec4 Destination) {"
		"	float Alpha = Source.a + Destination.a * (1.0 - Source.a);"
		"	vec3 Color = (Source.rgb * Source.a + Destination.rgb * Destination.a * (1.0 - Source.a)) / Alpha;"
		"	if (Alpha == 0.0) {"
		"		Color = vec3(0.0, 0.0, 0.0);"
		"	}"
		"	return vec4(Color, Alpha);"
		"}"
		"void main() {"
		"	vec4 Color0 = texelFetch(BaseColorSampler0, ivec2(gl_FragCoord.xy), 0);"
		"	vec4 Color1 = texelFetch(BaseColorSampler1, ivec2(gl_FragCoord.xy), 0);"
		"	FinalColor = BlendColor(Color0, FinalColor);"
		"	FinalColor = BlendColor(Color1, FinalColor);"
		"}";
	char const sWeightedBlendedOrderIndependentTransparencyPostProcessFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 FinalColor;"
		"layout (binding = 0) uniform sampler2D AccumulatorSampler;"
		"layout (binding = 1) uniform sampler2D RevealageSampler;"
		"const float EPSILON_5 = 0.00001;"
		"bool IsApproximatelyEqual(float A, float B)"
		"{"
		"	return abs(A - B) <= (abs(A) < abs(B) ? abs(B) : abs(A)) * EPSILON_5;"
		"}"
		"float Max3(vec3 V)"
		"{"
		"	return max(max(V.x, V.y), V.z);"
		"}"
		"void main() {"
		"	float Revealage = texelFetch(RevealageSampler, ivec2(gl_FragCoord.xy), 0).r;"
		"	if (IsApproximatelyEqual(Revealage, 1.0)) discard;"
		"	vec4 Accumulator = texelFetch(AccumulatorSampler, ivec2(gl_FragCoord.xy), 0);"
		"	if (isinf(Max3(abs(Accumulator.rgb)))) Accumulator.rgb = vec3(Accumulator.a);"
		"	vec3 AverageColor = Accumulator.rgb / max(Accumulator.a, EPSILON_5);"
		"	FinalColor = vec4(AverageColor, 1.0 - Revealage);"
		"}";
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedPostProcessEffects = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Kek Definition
	///////////////////////////////////////////////////////////////

#ifndef KEK_DEPTH_INCREMENT
#define KEK_DEPTH_INCREMENT (-0.01F)
#endif // KEK_DEPTH_INCREMENT

#ifndef KEK_INITIAL_DEPTH
#define KEK_INITIAL_DEPTH (0.01F)
#endif // KEK_INITIAL_DEPTH

#ifndef KEK_DOCK_PANEL_TITLE_SIZE
#define KEK_DOCK_PANEL_TITLE_SIZE (0xFFULL)
#endif // KEK_DOCK_PANEL_TITLE_SIZE

	typedef struct _KekVertex
	{
		Vector3 Position;
		Vector2 TextureCoords;
	} KekVertex;
	typedef struct _KekStyle
	{
		float DockTabWidth;
		float DockTabHeight;
	} KekStyle;
	typedef enum _KekNodeClass
	{
		KEK_NODE_CLASS_DOCK_ROOT,
		KEK_NODE_CLASS_LIST_LAYOUT,
		KEK_NODE_CLASS_GRID_LAYOUT,
		KEK_NODE_CLASS_TOOL_BAR,
		KEK_NODE_CLASS_IMAGE,
		KEK_NODE_CLASS_BUTTON,
		KEK_NODE_CLASS_SLIDER,
		KEK_NODE_CLASS_VIEW_PORT,
		KEK_NODE_CLASS_TEST, // TODO
	} KekNodeClass;
	typedef struct _KekNode
	{
		ListEntry NodeEntry;
		KekNodeClass Class;
		Rect Rect;
	} KekNode;
	typedef enum _KekDockPanelType
	{
		KEK_DOCK_PANEL_TYPE_WINDOW,
		KEK_DOCK_PANEL_TYPE_HORIZONTAL,
		KEK_DOCK_PANEL_TYPE_VERTICAL,
	} KekDockPanelType;
	typedef struct _KekDockPanel
	{
		ListEntry PanelEntry;
		KekDockPanelType Type;
		Rect TabRect;
		Rect PanelRect;
		char Title[KEK_DOCK_PANEL_TITLE_SIZE];
		struct _KekDockLayout* DockLayout;
		struct _KekDockPanel* ParentPanel;
		struct _KekDockPanel* ActivePanel;
		ListEntry ChildPanels;
		KekNode* Node;
		Color4 BackgroundColor;
		Color4 TextColor;
	} KekDockPanel;
	typedef struct _KekDockLayout
	{
		KekNode Node;
		KekDockPanel* RootPanel;
		KekDockPanel* DragPanel;
		float DragOffsetX;
		float DragOffsetY;
	} KekDockLayout;
	typedef struct _KekListLayout
	{
		KekNode Node;
	} KekListLayout;
	typedef struct _KekGridLayout
	{
		KekNode Node;
	} KekGridLayout;
	typedef struct _KekToolBar
	{
		KekNode Node;
	} KekToolBar;
	typedef struct _KekImage
	{
		KekNode Node;
	} KekImage;
	typedef struct _KekButton
	{
		KekNode Node;
	} KekButton;
	typedef struct _KekSlider
	{
		KekNode Node;
	} KekSlider;
	typedef struct _KekViewPort
	{
		KekNode Node;
	} KekViewPort;
	typedef struct _KekTest
	{
		KekNode Node;
	} KekTest;
	typedef enum _KekBatchMode
	{
		KEK_BATCH_MODE_RECT,
		KEK_BATCH_MODE_TEXT,
	} KekBatchMode;

	extern void Kek_Alloc(void);
	extern void Kek_SetRootNode(void* Node);
	extern void Kek_Resize(void);
	extern void Kek_Update(void);
	extern void Kek_Draw(void);
	extern void Kek_Free(void);
	extern void Kek_PrintTree(void);

	extern void Kek_DrawRectInternal(KekBatchMode BatchMode, Rect const* Rect, float Rotation, float Depth, Color4 const* Color);
	extern void Kek_DrawTextInternal(KekBatchMode BatchMode, Rect const* Rect, float Rotation, float Depth, float Size, Color4 const* Color, char const* Text);

	extern void KekNode_Resize(KekNode* Node);
	extern void KekNode_Update(KekNode* Node);
	extern void KekNode_Draw(KekNode* Node, KekBatchMode BatchMode, float Depth);
	extern void KekNode_PrintTree(KekNode* Node, int unsigned NumIdentSteps);

	extern KekDockPanel* KekDockPanel_Alloc(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title, KekNode* Node);
	extern KekDockPanel* KekDockPanel_Insert(KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockPanel_InsertLeft(KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockPanel_InsertRight(KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockPanel_InsertTop(KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockPanel_InsertBottom(KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockPanel_FindChildInsideBounds(KekDockPanel* DockPanel);
	extern void KekDockPanel_UpdateRect(KekDockPanel* DockPanel, int unsigned ChildIndex);
	extern void KekDockPanel_Update(KekDockPanel* DockPanel);
	extern void KekDockPanel_Draw(KekDockPanel* DockPanel, KekBatchMode BatchMode, float Depth);
	extern void KekDockPanel_PrintTree(KekDockPanel* DockPanel, int unsigned NumIdentSteps);

	extern void KekDockLayout_Alloc(KekDockLayout* DockLayout, Rect const* Rect);
	extern KekDockPanel* KekDockLayout_Insert(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockLayout_InsertLeft(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockLayout_InsertRight(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockLayout_InsertTop(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title);
	extern KekDockPanel* KekDockLayout_InsertBottom(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title);
	extern void KekDockLayout_DragUpdate(KekDockLayout* DockLayout);
	extern void KekDockLayout_Resize(KekDockLayout* DockLayout);
	extern void KekDockLayout_Update(KekDockLayout* DockLayout);
	extern void KekDockLayout_Draw(KekDockLayout* DockLayout, KekBatchMode BatchMode, float Depth);
	extern void KekDockLayout_Free(KekDockLayout* DockLayout);
	extern void KekDockLayout_PrintTree(KekDockLayout* DockLayout, int unsigned NumIdentSteps);

	extern void KekListLayout_Alloc(KekListLayout* ListLayout, Rect const* Rect);
	extern void KekListLayout_Update(KekListLayout* ListLayout);
	extern void KekListLayout_Resize(KekListLayout* ListLayout);
	extern void KekListLayout_Draw(KekListLayout* ListLayout, KekBatchMode BatchMode, float Depth);
	extern void KekListLayout_Free(KekListLayout* ListLayout);
	extern void KekListLayout_PrintTree(KekListLayout* ListLayout, int unsigned NumIdentSteps);

	extern void KekGridLayout_Alloc(KekGridLayout* GridLayout, Rect const* Rect);
	extern void KekGridLayout_Resize(KekGridLayout* GridLayout);
	extern void KekGridLayout_Update(KekGridLayout* GridLayout);
	extern void KekGridLayout_Draw(KekGridLayout* GridLayout, KekBatchMode BatchMode, float Depth);
	extern void KekGridLayout_Free(KekGridLayout* GridLayout);
	extern void KekGridLayout_PrintTree(KekGridLayout* GridLayout, int unsigned NumIdentSteps);

	extern void KekToolBar_Alloc(KekToolBar* ToolBar, Rect const* Rect);
	extern void KekToolBar_Update(KekToolBar* ToolBar);
	extern void KekToolBar_Draw(KekToolBar* ToolBar, KekBatchMode BatchMode, float Depth);
	extern void KekToolBar_Free(KekToolBar* ToolBar);
	extern void KekToolBar_PrintTree(KekToolBar* ToolBar, int unsigned NumIdentSteps);

	extern void KekImage_Alloc(KekImage* Image, Rect const* Rect);
	extern void KekImage_Update(KekImage* Image);
	extern void KekImage_Draw(KekImage* Image, KekBatchMode BatchMode, float Depth);
	extern void KekImage_PrintTree(KekImage* Image, int unsigned NumIdentSteps);

	extern void KekButton_Alloc(KekButton* Button, Rect const* Rect);
	extern void KekButton_Update(KekButton* Button);
	extern void KekButton_Draw(KekButton* Button, KekBatchMode BatchMode, float Depth);
	extern void KekButton_PrintTree(KekButton* Button, int unsigned NumIdentSteps);

	extern void KekSlider_Alloc(KekSlider* Slider, Rect const* Rect);
	extern void KekSlider_Update(KekSlider* Slider);
	extern void KekSlider_Draw(KekSlider* Slider, KekBatchMode BatchMode, float Depth);
	extern void KekSlider_PrintTree(KekSlider* Slider, int unsigned NumIdentSteps);

	extern void KekViewPort_Alloc(KekViewPort* ViewPort, Rect const* Rect);
	extern void KekViewPort_Update(KekViewPort* ViewPort);
	extern void KekViewPort_Draw(KekViewPort* ViewPort, KekBatchMode BatchMode, float Depth);
	extern void KekViewPort_PrintTree(KekViewPort* ViewPort, int unsigned NumIdentSteps);

	extern void KekTest_Alloc(KekTest* Test, Rect const* Rect);
	extern void KekTest_Update(KekTest* Test);
	extern void KekTest_Draw(KekTest* Test, KekBatchMode BatchMode, float Depth);
	extern void KekTest_Free(KekTest* Test);
	extern void KekTest_PrintTree(KekTest* Test, int unsigned NumIdentSteps);

#ifdef FAST_GL_IMPLEMENTATION
	static Batch sKekBatch = { 0 };
	static KekStyle sKekStyle = { 0 };
	static void* sKekRootNode = 0;
	static char const sKekVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(VertexPosition, 0.0, 1.0);"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"}";
	char const gKekFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 FinalColor;"
		"void main() {"
		"	FinalColor = vec4(TextureCoords, 0.0, 1.0);"
		"}";
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Histogram Definition
	///////////////////////////////////////////////////////////////

	typedef enum _HistogramScaleType
	{
		HISTOGRAM_SCALE_NS,
		HISTOGRAM_SCALE_US,
		HISTOGRAM_SCALE_MS,
	} HistogramScaleType;
	typedef struct _HistogramVertex
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} HistogramVertex;
	typedef struct _Histogram
	{
		SpriteMesh* Mesh;
		float* Samples;
		char Name[0xFF];
		HistogramScaleType ScaleType;
		int unsigned NumSamples;
		int unsigned SampleBuffer;
		int unsigned SampleIndex;
		int unsigned Scale;
		int unsigned AvgDelta;
		float DisplayInterval;
		float DisplayIntervalAcc;
		float Accumulator;
	} Histogram;

	extern void Histogram_Alloc(Histogram* Histgrm, SpriteMesh* Mesh, char* Name, HistogramScaleType ScaleType, int unsigned NumSamples, int unsigned Scale, int unsigned DisplayInterval);
	extern void Histogram_PushSample(Histogram* Histgrm, double Sample);
	extern void Histogram_Draw(Histogram* Histgrm, Vector3 const* Position, float Rotation, Vector2 const* Size);
	extern void Histogram_DrawSimple(Histogram* Histgrm, float PositionX, float PositionY, float PositionZ, float Rotation, float Width, float Height);
	extern void Histogram_Free(Histogram* Histgrm);

#ifdef FAST_GL_IMPLEMENTATION
	static int unsigned sHistogramProgram = 0;
	static char const sHistogramVertexShader[] =
		GLSL_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"} VertexOutput;"
		"uniform vec2 ScreenSize;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"uniform vec3 Position;"
		"uniform float Rotation;"
		"uniform vec2 Size;"
		GLSL_SCREEN_SPACE_IMPLEMENTATION
		GLSL_ROTATION_IMPLEMENTATION
		"void main() {"
		"	vec2 RotatedPosition = RotateVector2D(Position.xy + (VertexPosition * Size), radians(Rotation));"
		"	vec3 ScreenPosition = vec3(RotatedPosition, Position.z);"
		"	gl_Position = ScreenToClipSpace(ScreenPosition, ScreenSize);"
		"	VertexOutput.TextureCoords = vec2(VertexTextureCoords.x, 1.0 - VertexTextureCoords.y);"
		"}";
	static char const sHistogramFragmentShader[] =
		GLSL_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"layout (std430, binding = 0) buffer HistogramSample {"
		"	float Samples[];"
		"} HistogramSamples;"
		"const vec3 SLOW_COLOR = vec3(1.0, 0.0, 0.0);"
		"const vec3 FAST_COLOR = vec3(0.0, 0.0, 1.0);"
		"uniform uint NumSamples;"
		"uniform uint CurrIndex;"
		"uniform uint Scale;"
		GLSL_MATH_UTILITY_IMPLEMENTATION
		"void main() {"
		"	float X = FragmentInput.TextureCoords.x;"
		"	float LineWidth = 1.0 / float(NumSamples);"
		"	uint SampleIndex = uint(X / LineWidth);"
		"	if (SampleIndex < NumSamples) {"
		"		float Sample = HistogramSamples.Samples[(SampleIndex + CurrIndex) % NumSamples];"
		"		float Y = FragmentInput.TextureCoords.y * float(Scale);"
		"		if (Y <= Sample) {"
		"			float SpeedColorFactor = mix(0.0, float(Scale), RemapTo01(Sample / 10, 0.0, Scale));"
		"			vec3 SpeedColor = mix(FAST_COLOR, SLOW_COLOR, SpeedColorFactor);"
		"			BaseColor = vec4(SpeedColor, 1.0);"
		"		}"
		"		else {"
		"			discard;"
		"		}"
		"	}"
		"	else {"
		"		discard;"
		"	}"
		"}";
#ifdef FAST_GL_REFERENCE_COUNT
	static long long unsigned sAllocatedHistograms = 0;
#endif // FAST_GL_REFERENCE_COUNT
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Window Definition
	///////////////////////////////////////////////////////////////

	typedef enum _KeyboardKey
	{
		KEYBOARD_KEY_BACK = VK_BACK,
		KEYBOARD_KEY_TAB = VK_TAB,
		KEYBOARD_KEY_RETURN = VK_RETURN,
		KEYBOARD_KEY_SHIFT = VK_SHIFT,
		KEYBOARD_KEY_CONTROL = VK_CONTROL,
		KEYBOARD_KEY_MENU = VK_MENU,
		KEYBOARD_KEY_PAUSE = VK_PAUSE,
		KEYBOARD_KEY_CAPITAL = VK_CAPITAL,
		KEYBOARD_KEY_ESCAPE = VK_ESCAPE,
		KEYBOARD_KEY_SPACE = VK_SPACE,
		KEYBOARD_KEY_PRIOR = VK_PRIOR,
		KEYBOARD_KEY_NEXT = VK_NEXT,
		KEYBOARD_KEY_END = VK_END,
		KEYBOARD_KEY_HOME = VK_HOME,
		KEYBOARD_KEY_LEFT = VK_LEFT,
		KEYBOARD_KEY_UP = VK_UP,
		KEYBOARD_KEY_RIGHT = VK_RIGHT,
		KEYBOARD_KEY_DOWN = VK_DOWN,
		KEYBOARD_KEY_SELECT = VK_SELECT,
		KEYBOARD_KEY_PRINT = VK_PRINT,
		KEYBOARD_KEY_EXE = VK_EXECUTE,
		KEYBOARD_KEY_SNAPSHOT = VK_SNAPSHOT,
		KEYBOARD_KEY_INSERT = VK_INSERT,
		KEYBOARD_KEY_DELETE = VK_DELETE,
		KEYBOARD_KEY_HELP = VK_HELP,
		KEYBOARD_KEY_0 = '0',
		KEYBOARD_KEY_1 = '1',
		KEYBOARD_KEY_2 = '2',
		KEYBOARD_KEY_3 = '3',
		KEYBOARD_KEY_4 = '4',
		KEYBOARD_KEY_5 = '5',
		KEYBOARD_KEY_6 = '6',
		KEYBOARD_KEY_7 = '7',
		KEYBOARD_KEY_8 = '8',
		KEYBOARD_KEY_9 = '9',
		KEYBOARD_KEY_A = 'A',
		KEYBOARD_KEY_B = 'B',
		KEYBOARD_KEY_C = 'C',
		KEYBOARD_KEY_D = 'D',
		KEYBOARD_KEY_E = 'E',
		KEYBOARD_KEY_F = 'F',
		KEYBOARD_KEY_G = 'G',
		KEYBOARD_KEY_H = 'H',
		KEYBOARD_KEY_I = 'I',
		KEYBOARD_KEY_J = 'J',
		KEYBOARD_KEY_K = 'K',
		KEYBOARD_KEY_L = 'L',
		KEYBOARD_KEY_M = 'M',
		KEYBOARD_KEY_N = 'N',
		KEYBOARD_KEY_O = 'O',
		KEYBOARD_KEY_P = 'P',
		KEYBOARD_KEY_Q = 'Q',
		KEYBOARD_KEY_R = 'R',
		KEYBOARD_KEY_S = 'S',
		KEYBOARD_KEY_T = 'T',
		KEYBOARD_KEY_U = 'U',
		KEYBOARD_KEY_V = 'V',
		KEYBOARD_KEY_W = 'W',
		KEYBOARD_KEY_X = 'X',
		KEYBOARD_KEY_Y = 'Y',
		KEYBOARD_KEY_Z = 'Z',
		KEYBOARD_KEY_NUMPAD0 = VK_NUMPAD0,
		KEYBOARD_KEY_NUMPAD1 = VK_NUMPAD1,
		KEYBOARD_KEY_NUMPAD2 = VK_NUMPAD2,
		KEYBOARD_KEY_NUMPAD3 = VK_NUMPAD3,
		KEYBOARD_KEY_NUMPAD4 = VK_NUMPAD4,
		KEYBOARD_KEY_NUMPAD5 = VK_NUMPAD5,
		KEYBOARD_KEY_NUMPAD6 = VK_NUMPAD6,
		KEYBOARD_KEY_NUMPAD7 = VK_NUMPAD7,
		KEYBOARD_KEY_NUMPAD8 = VK_NUMPAD8,
		KEYBOARD_KEY_NUMPAD9 = VK_NUMPAD9,
		KEYBOARD_KEY_MULTIPLY = VK_MULTIPLY,
		KEYBOARD_KEY_ADD = VK_ADD,
		KEYBOARD_KEY_SEPARATOR = VK_SEPARATOR,
		KEYBOARD_KEY_SUBTRACT = VK_SUBTRACT,
		KEYBOARD_KEY_DECIMAL = VK_DECIMAL,
		KEYBOARD_KEY_DIVIDE = VK_DIVIDE,
		KEYBOARD_KEY_F1 = VK_F1,
		KEYBOARD_KEY_F2 = VK_F2,
		KEYBOARD_KEY_F3 = VK_F3,
		KEYBOARD_KEY_F4 = VK_F4,
		KEYBOARD_KEY_F5 = VK_F5,
		KEYBOARD_KEY_F6 = VK_F6,
		KEYBOARD_KEY_F7 = VK_F7,
		KEYBOARD_KEY_F8 = VK_F8,
		KEYBOARD_KEY_F9 = VK_F9,
		KEYBOARD_KEY_F10 = VK_F10,
		KEYBOARD_KEY_F11 = VK_F11,
		KEYBOARD_KEY_F12 = VK_F12,
		KEYBOARD_KEY_F13 = VK_F13,
		KEYBOARD_KEY_F14 = VK_F14,
		KEYBOARD_KEY_F15 = VK_F15,
		KEYBOARD_KEY_F16 = VK_F16,
		KEYBOARD_KEY_F17 = VK_F17,
		KEYBOARD_KEY_F18 = VK_F18,
		KEYBOARD_KEY_F19 = VK_F19,
		KEYBOARD_KEY_F20 = VK_F20,
		KEYBOARD_KEY_F21 = VK_F21,
		KEYBOARD_KEY_F22 = VK_F22,
		KEYBOARD_KEY_F23 = VK_F23,
		KEYBOARD_KEY_F24 = VK_F24,
		KEYBOARD_KEY_LEFT_SHIFT = VK_LSHIFT,
		KEYBOARD_KEY_RIGHT_SHIFT = VK_RSHIFT,
		KEYBOARD_KEY_LEFT_CONTROL = VK_LCONTROL,
		KEYBOARD_KEY_RIGHT_CONTROL = VK_RCONTROL,
	} KeyboardKey;
	typedef enum _MouseKey
	{
		MOUSE_KEY_LEFT,
		MOUSE_KEY_MIDDLE,
		MOUSE_KEY_RIGHT,
	} MouseKey;
	typedef enum _KeyboardKeyState
	{
		KEYBOARD_KEY_STATE_UP,
		KEYBOARD_KEY_STATE_PRESSED,
		KEYBOARD_KEY_STATE_DOWN,
		KEYBOARD_KEY_STATE_RELEASED,
	} KeyboardKeyState;
	typedef enum _MouseKeyState
	{
		MOUSE_KEY_STATE_UP,
		MOUSE_KEY_STATE_PRESSED,
		MOUSE_KEY_STATE_DOWN,
		MOUSE_KEY_STATE_RELEASED,
	} MouseKeyState;

	extern void Window_Alloc(int unsigned Width, int unsigned Height, char const* WindowTitle);
	extern bool Window_ShouldClose(void);
	extern void Window_PollEvents(void);
	extern void Window_SwapBuffers(void);
	extern void Window_ToNDC(float* X, float* Y);
	extern int Window_GetWidth(void);
	extern int Window_GetHeight(void);
	extern int Window_GetMousePositionX(void);
	extern int Window_GetMousePositionY(void);
	extern bool Window_IsKeyboardKeyPressed(KeyboardKey Key);
	extern bool Window_IsKeyboardKeyHeld(KeyboardKey Key);
	extern bool Window_IsKeyboardKeyReleased(KeyboardKey Key);
	extern bool Window_IsMouseKeyPressed(MouseKey Key);
	extern bool Window_IsMouseKeyHeld(MouseKey Key);
	extern bool Window_IsMouseKeyReleased(MouseKey Key);
	extern void Window_Free(void);

	extern LRESULT Window_CallbackInternal(HWND hWnd, UINT Message, WPARAM WParam, LPARAM LParam);
	extern void Window_GLDebugCallbackInternal(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);

#ifdef FAST_GL_IMPLEMENTATION
	static char const sWindowClassName[] = "FastGLWindow";
	static HINSTANCE sModuleInstance = 0;
	static HWND sWindowHandle = 0;
	static HDC sDeviceContext = 0;
	static HGLRC sGraphicsContext = 0;
	static HMODULE sOpenGLInstance = 0;
	static MSG sWindowMessage = { 0 };
	static bool sWindowShouldClose = false;
	static bool sWindowReady = false;
	static int sWindowWidth = 0;
	static int sWindowHeight = 0;
	static int sMousePositionX = 0;
	static int sMousePositionY = 0;
	static int sWheelDelta = 0;
	static KeyboardKeyState sKeyboardKeyStates[0xFF] = { 0 };
	static MouseKeyState sMouseKeyStates[0x3] = { 0 };
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Memory Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void* Memory_Alloc(long long unsigned Size, void const* Reference)
	{
#ifdef FAST_GL_DEBUG
		long long unsigned NewSize = sizeof(long long unsigned) + Size;

		long long unsigned* NewBlock = (long long unsigned*)malloc(NewSize);

		sAllocatedBytes += NewSize;

		*NewBlock = NewSize;
		NewBlock += 1;

		if (Reference)
		{
			memcpy(NewBlock, Reference, Size);
		}

		return NewBlock;
#else
		void* NewBlock = malloc(Size);

		if (Reference)
		{
			memcpy(NewBlock, Reference, Size);
		}

		return NewBlock;
#endif // FAST_GL_DEBUG
	}
	void* Memory_Realloc(void* Block, long long unsigned Size)
	{
#ifdef FAST_GL_DEBUG
		if (Block)
		{
			long long unsigned* PrevBlock = (long long unsigned*)Block;

			PrevBlock -= 1;

			long long unsigned PrevSize = *PrevBlock;
			long long unsigned NewSize = sizeof(long long unsigned) + Size;

			sAllocatedBytes -= PrevSize;

			long long unsigned* NewBlock = (long long unsigned*)realloc(PrevBlock, NewSize);

			sAllocatedBytes += NewSize;

			*NewBlock = NewSize;
			NewBlock += 1;

			return NewBlock;
		}
		else
		{
			return Memory_Alloc(Size, 0);
		}
#else
		return realloc(Block, Size);
#endif // FAST_GL_DEBUG
	}
	void Memory_Free(void* Block)
	{
#ifdef FAST_GL_DEBUG
		long long unsigned* PrevBlock = (long long unsigned*)Block;

		PrevBlock -= 1;

		long long unsigned PrevSize = *PrevBlock;

		sAllocatedBytes -= PrevSize;

		free(PrevBlock);
#else
		free(Block);
#endif // FAST_GL_DEBUG
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Math Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Vector2_Zero(Vector2* Result)
	{
		Result->X = 0.0F;
		Result->Y = 0.0F;
	}
	void Vector2_Set(Vector2* const Value, Vector2* Result)
	{
		Result->X = Value->X;
		Result->Y = Value->Y;
	}
	void Vector2_SetSimple(float X, float Y, Vector2* Result)
	{
		Result->X = X;
		Result->Y = Y;
	}
	void Vector2_Add(Vector2* const A, Vector2* const B, Vector2* Result)
	{
		Result->X = A->X + B->X;
		Result->Y = A->Y + B->Y;
	}
	void Vector2_Sub(Vector2* const A, Vector2* const B, Vector2* Result)
	{
		Result->X = A->X - B->X;
		Result->Y = A->Y - B->Y;
	}
	void Vector2_Mul(Vector2* const A, Vector2* const B, Vector2* Result)
	{
		Result->X = A->X * B->X;
		Result->Y = A->Y * B->Y;
	}
	void Vector2_Div(Vector2* const A, Vector2* const B, Vector2* Result)
	{
		Result->X = A->X / B->X;
		Result->Y = A->Y / B->Y;
	}
	void Vector2_AddScalar(Vector2* const Value, float Scalar, Vector2* Result)
	{
		Result->X = Value->X + Scalar;
		Result->Y = Value->Y + Scalar;
	}
	void Vector2_SubScalar(Vector2* const Value, float Scalar, Vector2* Result)
	{
		Result->X = Value->X - Scalar;
		Result->Y = Value->Y - Scalar;
	}
	void Vector2_MulScalar(Vector2* const Value, float Scalar, Vector2* Result)
	{
		Result->X = Value->X * Scalar;
		Result->Y = Value->Y * Scalar;
	}
	void Vector2_DivScalar(Vector2* const Value, float Scalar, Vector2* Result)
	{
		Result->X = Value->X / Scalar;
		Result->Y = Value->Y / Scalar;
	}
	void Vector2_MulAdd(Vector2* const Value, float Scalar, Vector2* Result)
	{
		Result->X += Value->X * Scalar;
		Result->Y += Value->Y * Scalar;
	}
	float Vector2_Dot(Vector2* const A, Vector2* const B)
	{
		return (A->X * B->X) + (A->Y * B->Y);
	}
	float Vector2_Length(Vector2* const Value)
	{
		return sqrtf(Vector2_Dot(Value, Value));
	}
	float Vector2_Length2(Vector2* const Value)
	{
		return Vector2_Dot(Value, Value);
	}
	void Vector2_Print(Vector2* const Value)
	{
		printf("[%f, %f]\n", Value->X, Value->Y);
	}
	void Vector3_Zero(Vector3* Result)
	{
		Result->X = 0.0F;
		Result->Y = 0.0F;
		Result->Z = 0.0F;
	}
	void Vector3_Set(Vector3* const Value, Vector3* Result)
	{
		Result->X = Value->X;
		Result->Y = Value->Y;
		Result->Z = Value->Z;
	}
	void Vector3_SetSimple(float X, float Y, float Z, Vector3* Result)
	{
		Result->X = X;
		Result->Y = Y;
		Result->Z = Z;
	}
	void Vector3_Add(Vector3* const A, Vector3* const B, Vector3* Result)
	{
		Result->X = A->X + B->X;
		Result->Y = A->Y + B->Y;
		Result->Z = A->Z + B->Z;
	}
	void Vector3_Sub(Vector3* const A, Vector3* const B, Vector3* Result)
	{
		Result->X = A->X - B->X;
		Result->Y = A->Y - B->Y;
		Result->Z = A->Z - B->Z;
	}
	void Vector3_Mul(Vector3* const A, Vector3* const B, Vector3* Result)
	{
		Result->X = A->X * B->X;
		Result->Y = A->Y * B->Y;
		Result->Z = A->Z * B->Z;
	}
	void Vector3_Div(Vector3* const A, Vector3* const B, Vector3* Result)
	{
		Result->X = A->X / B->X;
		Result->Y = A->Y / B->Y;
		Result->Z = A->Z / B->Z;
	}
	void Vector3_AddScalar(Vector3* const Value, float Scalar, Vector3* Result)
	{
		Result->X = Value->X + Scalar;
		Result->Y = Value->Y + Scalar;
		Result->Z = Value->Z + Scalar;
	}
	void Vector3_SubScalar(Vector3* const Value, float Scalar, Vector3* Result)
	{
		Result->X = Value->X - Scalar;
		Result->Y = Value->Y - Scalar;
		Result->Z = Value->Z - Scalar;
	}
	void Vector3_MulScalar(Vector3* const Value, float Scalar, Vector3* Result)
	{
		Result->X = Value->X * Scalar;
		Result->Y = Value->Y * Scalar;
		Result->Z = Value->Z * Scalar;
	}
	void Vector3_DivScalar(Vector3* const Value, float Scalar, Vector3* Result)
	{
		Result->X = Value->X / Scalar;
		Result->Y = Value->Y / Scalar;
		Result->Z = Value->Z / Scalar;
	}
	void Vector3_MulAdd(Vector3* const Value, float Scalar, Vector3* Result)
	{
		Result->X += Value->X * Scalar;
		Result->Y += Value->Y * Scalar;
		Result->Z += Value->Z * Scalar;
	}
	void Vector3_Norm(Vector3* const Value, Vector3* Result)
	{
		float A = Vector3_Dot(Value, Value);
		float N = sqrtf(A);

		if (N == 0.0F)
		{
			Vector3_Zero(Result);
		}
		else
		{
			Vector3_MulScalar(Value, 1.0F / N, Result);
		}
	}
	float Vector3_Dot(Vector3* const A, Vector3* const B)
	{
		return (A->X * B->X) + (A->Y * B->Y) + (A->Z * B->Z);
	}
	float Vector3_Length(Vector3* const Value)
	{
		return sqrtf(Vector3_Dot(Value, Value));
	}
	float Vector3_Length2(Vector3* const Value)
	{
		return Vector3_Dot(Value, Value);
	}
	void Vector3_Cross(Vector3* const A, Vector3* const B, Vector3* Result)
	{
		Result->X = (A->Y * B->Z) - (A->Z * B->Y);
		Result->Y = (A->Z * B->X) - (A->X * B->Z);
		Result->Z = (A->X * B->Y) - (A->Y * B->X);
	}
	void Vector3_Rotate(Vector3* const Value, Quaternion* const Rotation, Vector3* Result)
	{
		float QX2 = Rotation->X * 2.0F;
		float QY2 = Rotation->Y * 2.0F;
		float QZ2 = Rotation->Z * 2.0F;

		float XX = Rotation->X * QX2;
		float YY = Rotation->Y * QY2;
		float ZZ = Rotation->Z * QZ2;
		float XY = Rotation->X * QY2;
		float XZ = Rotation->X * QZ2;
		float YZ = Rotation->Y * QZ2;
		float WX = Rotation->W * QX2;
		float WY = Rotation->W * QY2;
		float WZ = Rotation->W * QZ2;

		Result->X = (1.0F - (YY + ZZ)) * Value->X + (XY - WZ) * Value->Y + (XZ + WY) * Value->Z;
		Result->Y = (XY + WZ) * Value->X + (1.0F - (XX + ZZ)) * Value->Y + (YZ - WX) * Value->Z;
		Result->Z = (XZ - WY) * Value->X + (YZ + WX) * Value->Y + (1.0F - (XX + YY)) * Value->Z;
	}
	void Vector3_Print(Vector3* const Value)
	{
		printf("[%f, %f, %f]\n", Value->X, Value->Y, Value->Z);
	}
	void Vector4_Zero(Vector4* Result)
	{
		Result->X = 0.0F;
		Result->Y = 0.0F;
		Result->Z = 0.0F;
		Result->W = 0.0F;
	}
	void Vector4_Set(Vector4* const Value, Vector4* Result)
	{
		Result->X = Value->X;
		Result->Y = Value->Y;
		Result->Z = Value->Z;
		Result->W = Value->W;
	}
	void Vector4_SetSimple(float X, float Y, float Z, float W, Vector4* Result)
	{
		Result->X = X;
		Result->Y = Y;
		Result->Z = Z;
		Result->W = W;
	}
	void Vector4_Add(Vector4* const A, Vector4* const B, Vector4* Result)
	{
		Result->X = A->X + B->X;
		Result->Y = A->Y + B->Y;
		Result->Z = A->Z + B->Z;
		Result->W = A->W + B->W;
	}
	void Vector4_Sub(Vector4* const A, Vector4* const B, Vector4* Result)
	{
		Result->X = A->X - B->X;
		Result->Y = A->Y - B->Y;
		Result->Z = A->Z - B->Z;
		Result->W = A->W - B->W;
	}
	void Vector4_Mul(Vector4* const A, Vector4* const B, Vector4* Result)
	{
		Result->X = A->X * B->X;
		Result->Y = A->Y * B->Y;
		Result->Z = A->Z * B->Z;
		Result->W = A->W * B->W;
	}
	void Vector4_Div(Vector4* const A, Vector4* const B, Vector4* Result)
	{
		Result->X = A->X / B->X;
		Result->Y = A->Y / B->Y;
		Result->Z = A->Z / B->Z;
		Result->W = A->W / B->W;
	}
	void Vector4_AddScalar(Vector4* const Value, float Scalar, Vector4* Result)
	{
		Result->X = Value->X + Scalar;
		Result->Y = Value->Y + Scalar;
		Result->Z = Value->Z + Scalar;
		Result->W = Value->W + Scalar;
	}
	void Vector4_SubScalar(Vector4* const Value, float Scalar, Vector4* Result)
	{
		Result->X = Value->X - Scalar;
		Result->Y = Value->Y - Scalar;
		Result->Z = Value->Z - Scalar;
		Result->W = Value->W - Scalar;
	}
	void Vector4_MulScalar(Vector4* const Value, float Scalar, Vector4* Result)
	{
		Result->X = Value->X * Scalar;
		Result->Y = Value->Y * Scalar;
		Result->Z = Value->Z * Scalar;
		Result->W = Value->W * Scalar;
	}
	void Vector4_DivScalar(Vector4* const Value, float Scalar, Vector4* Result)
	{
		Result->X = Value->X / Scalar;
		Result->Y = Value->Y / Scalar;
		Result->Z = Value->Z / Scalar;
		Result->W = Value->W / Scalar;
	}
	void Vector4_MulAdd(Vector4* const Value, float Scalar, Vector4* Result)
	{
		Result->X += Value->X * Scalar;
		Result->Y += Value->Y * Scalar;
		Result->Z += Value->Z * Scalar;
		Result->W += Value->W * Scalar;
	}
	void Vector4_Print(Vector4* const Value)
	{
		printf("[%f, %f, %f, %f]\n", Value->X, Value->Y, Value->Z, Value->W);
	}
	void Quaternion_Zero(Quaternion* Result)
	{
		Result->X = 0.0F;
		Result->Y = 0.0F;
		Result->Z = 0.0F;
		Result->W = 0.0F;
	}
	void Quaternion_Identity(Quaternion* Result)
	{
		Result->X = 0.0F;
		Result->Y = 0.0F;
		Result->Z = 0.0F;
		Result->W = 1.0F;
	}
	void Quaternion_Set(Quaternion* const Value, Quaternion* Result)
	{
		Result->X = Value->X;
		Result->Y = Value->Y;
		Result->Z = Value->Z;
		Result->W = Value->W;
	}
	void Quaternion_SetSimple(float X, float Y, float Z, float W, Quaternion* Result)
	{
		Result->X = X;
		Result->Y = Y;
		Result->Z = Z;
		Result->W = W;
	}
	void Quaternion_Mul(Quaternion* const A, Quaternion* const B, Quaternion* Result)
	{
		Result->X = (A->W * B->X) + (A->X * B->W) + (A->Y * B->Z) - (A->Z * B->Y);
		Result->Y = (A->W * B->Y) - (A->X * B->Z) + (A->Y * B->W) + (A->Z * B->X);
		Result->Z = (A->W * B->Z) + (A->X * B->Y) - (A->Y * B->X) + (A->Z * B->W);
		Result->W = (A->W * B->W) - (A->X * B->X) - (A->Y * B->Y) - (A->Z * B->Z);
	}
	void Quaternion_MulScalar(Quaternion* const Value, float Scalar, Quaternion* Result)
	{
		Result->X = Value->X * Scalar;
		Result->Y = Value->Y * Scalar;
		Result->Z = Value->Z * Scalar;
		Result->W = Value->W * Scalar;
	}
	void Quaternion_Conjugate(Quaternion* const Value, Quaternion* Result)
	{
		Result->X = -Value->X;
		Result->Y = -Value->Y;
		Result->Z = -Value->Z;
		Result->W = Value->W;
	}
	void Quaternion_EulerAngles(Quaternion* const Value, Vector3* Result)
	{
		float SRCP = 2.0F * ((Value->W * Value->X) + (Value->Y * Value->Z));
		float CRCP = 1.0F - 2.0F * (Value->X * Value->X + Value->Y * Value->Y);
		float R = atan2f(SRCP, CRCP);

		float SP = 2.0F * ((Value->W * Value->Y) - (Value->Z * Value->X));
		float P = 0.0F;
		if (fabs(SP) >= 1.0F)
		{
			P = copysignf(PI / 2, SP);
		}
		else
		{
			P = asinf(SP);
		}

		float SYCP = 2.0F * ((Value->W * Value->Z) + (Value->X * Value->Y));
		float CYCP = 1.0F - 2.0F * (Value->Y * Value->Y + Value->Z * Value->Z);
		float Y = atan2f(SYCP, CYCP);

		Result->X = P;
		Result->Y = Y;
		Result->Z = R;
	}
	void Quaternion_AngleAxis(float Angle, Vector3* const Axis, Quaternion* Result)
	{
		Vector3 AN = VECTOR3_ZERO;

		Vector3_Norm(Axis, &AN);

		float HA = Angle / 2.0f;
		float S = sinf(HA);

		Result->X = AN.X * S;
		Result->Y = AN.Y * S;
		Result->Z = AN.Z * S;
		Result->W = cosf(HA);
	}
	void Quaternion_Norm(Quaternion* const Value, Quaternion* Result)
	{
		float A = (Value->X * Value->X) + (Value->Y * Value->Y) + (Value->Z * Value->Z) + (Value->W * Value->W);
		float N = sqrtf(A);

		if (N == 0.0f)
		{
			Quaternion_Identity(Result);
		}
		else
		{
			Quaternion_MulScalar(Value, 1.0F / N, Result);
		}
	}
	void Quaternion_Print(Quaternion* const Value)
	{
		printf("[%f, %f, %f, %f]\n", Value->X, Value->Y, Value->Z, Value->W);
	}
	void Rect_Zero(Rect* Result)
	{
		Result->Left = 0.0F;
		Result->Right = 0.0F;
		Result->Top = 0.0F;
		Result->Bottom = 0.0F;
	}
	void Rect_Set(Rect const* Value, Rect* Result)
	{
		Result->Left = Value->Left;
		Result->Right = Value->Right;
		Result->Top = Value->Top;
		Result->Bottom = Value->Bottom;
	}
	void Rect_SetSimple(float Left, float Right, float Top, float Bottom, Rect* Result)
	{
		Result->Left = Left;
		Result->Right = Right;
		Result->Top = Top;
		Result->Bottom = Bottom;
	}
	void Rect_SetPosition(float PositionX, float PositionY, Rect* Result)
	{
		float Width = Result->Right - Result->Left;
		float Height = Result->Bottom - Result->Top;
		Result->Left = PositionX;
		Result->Right = PositionX + Width;
		Result->Top = PositionY;
		Result->Bottom = PositionY + Height;
	}
	void Rect_SetSize(float SizeX, float SizeY, Rect* Result)
	{
		Result->Right = Result->Right + SizeX;
		Result->Bottom = Result->Bottom + SizeY;
	}
	float Rect_PositionX(Rect const* Value)
	{
		return Value->Left;
	}
	float Rect_PositionY(Rect const* Value)
	{
		return Value->Top;
	}
	float Rect_Width(Rect const* Value)
	{
		return Value->Right - Value->Left;
	}
	float Rect_Height(Rect const* Value)
	{
		return Value->Bottom - Value->Top;
	}
	bool Rect_Overlap(Rect const* Value, float PositionX, float PositionY)
	{
		return (PositionX >= Value->Left && PositionX < Value->Right &&
				PositionY >= Value->Top && PositionY < Value->Bottom);
	}
	void Rect_Print(Rect const* Value)
	{
		printf("[%f, %f, %f, %f]\n", Value->Left, Value->Right, Value->Top, Value->Bottom);
	}
	void Matrix4x4_Set(Matrix4x4* const Value, Matrix4x4* Result)
	{
		Result->M00 = Value->M00; Result->M01 = Value->M01; Result->M02 = Value->M02; Result->M03 = Value->M03;
		Result->M10 = Value->M10; Result->M11 = Value->M11; Result->M12 = Value->M12; Result->M13 = Value->M13;
		Result->M20 = Value->M20; Result->M21 = Value->M21; Result->M22 = Value->M22; Result->M23 = Value->M23;
		Result->M30 = Value->M30; Result->M31 = Value->M31; Result->M32 = Value->M32; Result->M33 = Value->M33;
	}
	void Matrix4x4_Zero(Matrix4x4* Result)
	{
		Result->M00 = Result->M01 = Result->M02 = Result->M03 = 0.0F;
		Result->M10 = Result->M11 = Result->M12 = Result->M13 = 0.0F;
		Result->M20 = Result->M21 = Result->M22 = Result->M23 = 0.0F;
		Result->M30 = Result->M31 = Result->M32 = Result->M33 = 0.0F;
	}
	void Matrix4x4_One(Matrix4x4* Result)
	{
		Result->M00 = Result->M01 = Result->M02 = Result->M03 = 1.0F;
		Result->M10 = Result->M11 = Result->M12 = Result->M13 = 1.0F;
		Result->M20 = Result->M21 = Result->M22 = Result->M23 = 1.0F;
		Result->M30 = Result->M31 = Result->M32 = Result->M33 = 1.0F;
	}
	void Matrix4x4_Identity(Matrix4x4* Result)
	{
		Result->M00 = 1.0F; Result->M01 = 0.0F; Result->M02 = 0.0F; Result->M03 = 0.0F;
		Result->M10 = 0.0F; Result->M11 = 1.0F; Result->M12 = 0.0F; Result->M13 = 0.0F;
		Result->M20 = 0.0F; Result->M21 = 0.0F; Result->M22 = 1.0F; Result->M23 = 0.0F;
		Result->M30 = 0.0F; Result->M31 = 0.0F; Result->M32 = 0.0F; Result->M33 = 1.0F;
	}
	void Matrix4x4_GetPosition(Matrix4x4* const Value, Vector3* Result)
	{
		Result->X = Value->M30;
		Result->Y = Value->M31;
		Result->Z = Value->M32;
	}
	void Matrix4x4_GetRotation(Matrix4x4* const Value, Quaternion* Result)
	{
		Vector3 C0 = { Value->M00, Value->M10, Value->M20 };
		Vector3 C1 = { Value->M01, Value->M11, Value->M21 };
		Vector3 C2 = { Value->M02, Value->M12, Value->M22 };

		Vector3 CN0 = VECTOR3_ZERO;
		Vector3 CN1 = VECTOR3_ZERO;
		Vector3 CN2 = VECTOR3_ZERO;

		Vector3_Norm(&C0, &CN0);
		Vector3_Norm(&C1, &CN1);
		Vector3_Norm(&C2, &CN2);

		float Trace = CN0.X + CN1.Y + CN2.Z;
		if (Trace > 0.0F)
		{
			float S = 0.5F / sqrtf(Trace + 1.0F);
			Result->X = (CN2.Y - CN1.Z) * S;
			Result->Y = (CN0.Z - CN2.X) * S;
			Result->Z = (CN1.X - CN0.Y) * S;
			Result->W = 0.25F / S;
		}
		else
		{
			if ((CN0.X > CN1.Y) && (CN0.X > CN2.Z))
			{
				float S = 2.0F * sqrtf(1.0F + CN0.X - CN1.Y - CN2.Z);
				Result->X = 0.25F * S;
				Result->Y = (CN0.Y + CN1.X) / S;
				Result->Z = (CN0.Z + CN2.Y) / S;
				Result->W = (CN2.Y - CN1.Z) / S;
			}
			else if (CN1.Y > CN2.Z)
			{
				float S = 2.0F * sqrtf(1.0F + CN1.Y - CN0.X - CN2.Z);
				Result->X = (CN0.Y + CN1.X) / S;
				Result->Y = 0.25F * S;
				Result->Z = (CN1.Z + CN2.Y) / S;
				Result->W = (CN0.Z - CN2.X) / S;
			}
			else
			{
				float S = 2.0F * sqrtf(1.0F + CN2.Z - CN0.X - CN1.Y);
				Result->X = (CN0.Z + CN2.X) / S;
				Result->Y = (CN1.Z + CN2.Y) / S;
				Result->Z = 0.25F * S;
				Result->W = (CN1.X - CN0.Y) / S;
			}
		}
	}
	void Matrix4x4_GetRotationEulerAngles(Matrix4x4* const Value, Vector3* Result)
	{
		if (fabsf(Value->M02) < 1.0F - EPSILON_6)
		{
			Result->X = atan2f(-Value->M12, Value->M22);
			Result->Y = asinf(Value->M02);
			Result->Z = atan2f(-Value->M01, Value->M00);
		}
		else
		{
			Result->X = atan2f(Value->M10, Value->M11);
			Result->Y = (Value->M02 > 0.0F) ? PI / 2.0F : -PI / 2.0F;
			Result->Z = 0.0F;
		}
	}
	void Matrix4x4_GetScale(Matrix4x4* const Value, Vector3* Result)
	{
		Result->X = Value->M00;
		Result->Y = Value->M11;
		Result->Z = Value->M22;
	}
	void Matrix4x4_SetPosition(Vector3* const Value, Matrix4x4* Result)
	{
		Result->M30 = Value->X;
		Result->M31 = Value->Y;
		Result->M32 = Value->Z;
	}
	void Matrix4x4_SetPositionSimple(float ValueX, float ValueY, float ValueZ, Matrix4x4* Result)
	{
		Result->M30 = ValueX;
		Result->M31 = ValueY;
		Result->M32 = ValueZ;
	}
	void Matrix4x4_SetRotation(Quaternion* const Value, Matrix4x4* Result)
	{
		float XX = Value->X * Value->X;
		float YY = Value->Y * Value->Y;
		float ZZ = Value->Z * Value->Z;
		float XY = Value->X * Value->Y;
		float XZ = Value->X * Value->Z;
		float YZ = Value->Y * Value->Z;
		float WX = Value->W * Value->X;
		float WY = Value->W * Value->Y;
		float WZ = Value->W * Value->Z;

		Result->M00 = 1.0F - 2.0F * (YY + ZZ);
		Result->M01 = 2.0F * (XY - WZ);
		Result->M02 = 2.0F * (XZ + WY);
		Result->M03 = 0.0F;
		Result->M10 = 2.0F * (XY + WZ);
		Result->M11 = 1.0F - 2.0F * (XX + ZZ);
		Result->M12 = 2.0F * (YZ - WX);
		Result->M13 = 0.0F;
		Result->M20 = 2.0F * (XZ - WY);
		Result->M21 = 2.0F * (YZ + WX);
		Result->M22 = 1.0F - 2.0F * (XX + YY);
		Result->M23 = 0.0F;
	}
	void Matrix4x4_SetRotationSimple(float ValueX, float ValueY, float ValueZ, float ValueW, Matrix4x4* Result)
	{
		float XX = ValueX * ValueX;
		float YY = ValueY * ValueY;
		float ZZ = ValueZ * ValueZ;
		float XY = ValueX * ValueY;
		float XZ = ValueX * ValueZ;
		float YZ = ValueY * ValueZ;
		float WX = ValueW * ValueX;
		float WY = ValueW * ValueY;
		float WZ = ValueW * ValueZ;

		Result->M00 = 1.0F - 2.0F * (YY + ZZ);
		Result->M01 = 2.0F * (XY - WZ);
		Result->M02 = 2.0F * (XZ + WY);
		Result->M03 = 0.0F;
		Result->M10 = 2.0F * (XY + WZ);
		Result->M11 = 1.0F - 2.0F * (XX + ZZ);
		Result->M12 = 2.0F * (YZ - WX);
		Result->M13 = 0.0F;
		Result->M20 = 2.0F * (XZ - WY);
		Result->M21 = 2.0F * (YZ + WX);
		Result->M22 = 1.0F - 2.0F * (XX + YY);
		Result->M23 = 0.0F;
	}
	void Matrix4x4_SetRotationEulerAngles(Vector3* const Value, Matrix4x4* Result)
	{
		float Pitch = DEG_TO_RAD(Value->X);
		float Yaw = DEG_TO_RAD(Value->Y);
		float Roll = DEG_TO_RAD(Value->Z);

		float CX = cosf(Pitch), SX = sinf(Pitch);
		float CY = cosf(Yaw), SY = sinf(Yaw);
		float CZ = cosf(Roll), SZ = sinf(Roll);

		Result->M00 = CY * CZ;
		Result->M01 = -CY * SZ;
		Result->M02 = SY;
		Result->M03 = 0.0F;
		Result->M10 = SX * SY * CZ + CX * SZ;
		Result->M11 = -SX * SY * SZ + CX * CZ;
		Result->M12 = -SX * CY;
		Result->M13 = 0.0F;
		Result->M20 = -CX * SY * CZ + SX * SZ;
		Result->M21 = CX * SY * SZ + SX * CZ;
		Result->M22 = CX * CY;
		Result->M23 = 0.0F;
	}
	void Matrix4x4_SetRotationEulerAnglesSimple(float Pitch, float Yaw, float Roll, Matrix4x4* Result)
	{
		Pitch = DEG_TO_RAD(Pitch);
		Yaw = DEG_TO_RAD(Yaw);
		Roll = DEG_TO_RAD(Roll);

		float CX = cosf(Pitch), SX = sinf(Pitch);
		float CY = cosf(Yaw), SY = sinf(Yaw);
		float CZ = cosf(Roll), SZ = sinf(Roll);

		Result->M00 = CY * CZ;
		Result->M01 = -CY * SZ;
		Result->M02 = SY;
		Result->M03 = 0.0F;
		Result->M10 = SX * SY * CZ + CX * SZ;
		Result->M11 = -SX * SY * SZ + CX * CZ;
		Result->M12 = -SX * CY;
		Result->M13 = 0.0F;
		Result->M20 = -CX * SY * CZ + SX * SZ;
		Result->M21 = CX * SY * SZ + SX * CZ;
		Result->M22 = CX * CY;
		Result->M23 = 0.0F;
	}
	void Matrix4x4_SetScale(Vector3* const Value, Matrix4x4* Result)
	{
		Result->M00 = Value->X;
		Result->M11 = Value->Y;
		Result->M22 = Value->Z;
	}
	void Matrix4x4_SetScaleSimple(float ValueX, float ValueY, float ValueZ, Matrix4x4* Result)
	{
		Result->M00 = ValueX;
		Result->M11 = ValueY;
		Result->M22 = ValueZ;
	}
	void Matrix4x4_Decompose(Matrix4x4* const Value, Vector3* Position, Quaternion* Rotation, Vector3* Scale)
	{
		Position->X = Value->M30;
		Position->Y = Value->M31;
		Position->Z = Value->M32;

		Vector3 C0 = { Value->M00, Value->M10, Value->M20 };
		Vector3 C1 = { Value->M01, Value->M11, Value->M21 };
		Vector3 C2 = { Value->M02, Value->M12, Value->M22 };

		Scale->X = Vector3_Length(&C0);
		Scale->Y = Vector3_Length(&C1);
		Scale->Z = Vector3_Length(&C2);

		Vector3 CN0 = VECTOR3_ZERO;
		Vector3 CN1 = VECTOR3_ZERO;
		Vector3 CN2 = VECTOR3_ZERO;

		Vector3_Norm(&C0, &CN0);
		Vector3_Norm(&C1, &CN1);
		Vector3_Norm(&C2, &CN2);

		float Trace = CN0.X + CN1.Y + CN2.Z;
		if (Trace > 0.0F)
		{
			float S = 0.5F / sqrtf(Trace + 1.0F);
			Rotation->X = (CN2.Y - CN1.Z) * S;
			Rotation->Y = (CN0.Z - CN2.X) * S;
			Rotation->Z = (CN1.X - CN0.Y) * S;
			Rotation->W = 0.25F / S;
		}
		else
		{
			if ((CN0.X > CN1.Y) && (CN0.X > CN2.Z))
			{
				float S = 2.0F * sqrtf(1.0F + CN0.X - CN1.Y - CN2.Z);
				Rotation->X = 0.25F * S;
				Rotation->Y = (CN0.Y + CN1.X) / S;
				Rotation->Z = (CN0.Z + CN2.Y) / S;
				Rotation->W = (CN2.Y - CN1.Z) / S;
			}
			else if (CN1.Y > CN2.Z)
			{
				float S = 2.0F * sqrtf(1.0F + CN1.Y - CN0.X - CN2.Z);
				Rotation->X = (CN0.Y + CN1.X) / S;
				Rotation->Y = 0.25F * S;
				Rotation->Z = (CN1.Z + CN2.Y) / S;
				Rotation->W = (CN0.Z - CN2.X) / S;
			}
			else
			{
				float S = 2.0F * sqrtf(1.0F + CN2.Z - CN0.X - CN1.Y);
				Rotation->X = (CN0.Z + CN2.X) / S;
				Rotation->Y = (CN1.Z + CN2.Y) / S;
				Rotation->Z = 0.25F * S;
				Rotation->W = (CN1.X - CN0.Y) / S;
			}
		}
	}
	void Matrix4x4_Mul(Matrix4x4* const A, Matrix4x4* const B, Matrix4x4* Result)
	{
		Result->M00 = (A->M00 * B->M00) + (A->M10 * B->M01) + (A->M20 * B->M02) + (A->M30 * B->M03);
		Result->M01 = (A->M01 * B->M00) + (A->M11 * B->M01) + (A->M21 * B->M02) + (A->M31 * B->M03);
		Result->M02 = (A->M02 * B->M00) + (A->M12 * B->M01) + (A->M22 * B->M02) + (A->M32 * B->M03);
		Result->M03 = (A->M03 * B->M00) + (A->M13 * B->M01) + (A->M23 * B->M02) + (A->M33 * B->M03);
		Result->M10 = (A->M00 * B->M10) + (A->M10 * B->M11) + (A->M20 * B->M12) + (A->M30 * B->M13);
		Result->M11 = (A->M01 * B->M10) + (A->M11 * B->M11) + (A->M21 * B->M12) + (A->M31 * B->M13);
		Result->M12 = (A->M02 * B->M10) + (A->M12 * B->M11) + (A->M22 * B->M12) + (A->M32 * B->M13);
		Result->M13 = (A->M03 * B->M10) + (A->M13 * B->M11) + (A->M23 * B->M12) + (A->M33 * B->M13);
		Result->M20 = (A->M00 * B->M20) + (A->M10 * B->M21) + (A->M20 * B->M22) + (A->M30 * B->M23);
		Result->M21 = (A->M01 * B->M20) + (A->M11 * B->M21) + (A->M21 * B->M22) + (A->M31 * B->M23);
		Result->M22 = (A->M02 * B->M20) + (A->M12 * B->M21) + (A->M22 * B->M22) + (A->M32 * B->M23);
		Result->M23 = (A->M03 * B->M20) + (A->M13 * B->M21) + (A->M23 * B->M22) + (A->M33 * B->M23);
		Result->M30 = (A->M00 * B->M30) + (A->M10 * B->M31) + (A->M20 * B->M32) + (A->M30 * B->M33);
		Result->M31 = (A->M01 * B->M30) + (A->M11 * B->M31) + (A->M21 * B->M32) + (A->M31 * B->M33);
		Result->M32 = (A->M02 * B->M30) + (A->M12 * B->M31) + (A->M22 * B->M32) + (A->M32 * B->M33);
		Result->M33 = (A->M03 * B->M30) + (A->M13 * B->M31) + (A->M23 * B->M32) + (A->M33 * B->M33);
	}
	void Matrix4x4_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, Matrix4x4* Result)
	{
		Matrix4x4_Zero(Result);

		Result->M00 = 2.0F / (Right - Left);
		Result->M11 = 2.0F / (Top - Bottom);
		Result->M22 = 1.0F / (FarZ - NearZ);
		Result->M30 = -(Right + Left) / (Right - Left);
		Result->M31 = -(Top + Bottom) / (Top - Bottom);
		Result->M32 = -NearZ / (FarZ - NearZ);
		Result->M33 = 1.0F;
	}
	void Matrix4x4_Perspective(float FieldOfView, float AspectRatio, float NearZ, float FarZ, Matrix4x4* Result)
	{
		Matrix4x4_Zero(Result);

		float TanHalfFovy = tanf(FieldOfView / 2.0F);

		Result->M00 = 1.0F / (AspectRatio * TanHalfFovy);
		Result->M11 = 1.0F / (TanHalfFovy);
		Result->M22 = FarZ / (FarZ - NearZ);
		Result->M23 = 1.0F;
		Result->M32 = -(FarZ * NearZ) / (FarZ - NearZ);
	}
	void Matrix4x4_LookAt(Vector3* const Eye, Vector3* const Center, Vector3* const Up, Matrix4x4* Result)
	{
		Vector3 F = VECTOR3_ZERO, U = VECTOR3_ZERO, S = VECTOR3_ZERO;
		Vector3 FN = VECTOR3_ZERO, SN = VECTOR3_ZERO;

		Vector3_Sub(Center, Eye, &F);
		Vector3_Norm(&F, &FN);
		Vector3_Cross(Up, &FN, &S);
		Vector3_Norm(&S, &SN);
		Vector3_Cross(&FN, &SN, &U);

		Result->M00 = S.X;
		Result->M01 = U.X;
		Result->M02 = FN.X;
		Result->M10 = S.Y;
		Result->M11 = U.Y;
		Result->M12 = FN.Y;
		Result->M20 = S.Z;
		Result->M21 = U.Z;
		Result->M22 = FN.Z;
		Result->M30 = -Vector3_Dot(&S, Eye);
		Result->M31 = -Vector3_Dot(&U, Eye);
		Result->M32 = -Vector3_Dot(&FN, Eye);
		Result->M03 = 0.0F;
		Result->M13 = 0.0F;
		Result->M23 = 0.0F;
		Result->M33 = 1.0F;
	}
	void Matrix4x4_Print(Matrix4x4* const Value)
	{
		printf("[%f, %f, %f, %f]\n", Value->M00, Value->M01, Value->M02, Value->M03);
		printf("[%f, %f, %f, %f]\n", Value->M10, Value->M11, Value->M12, Value->M13);
		printf("[%f, %f, %f, %f]\n", Value->M20, Value->M21, Value->M22, Value->M23);
		printf("[%f, %f, %f, %f]\n", Value->M30, Value->M31, Value->M32, Value->M33);
	}
	float Math_StepTowards(float Current, float Target, float Step)
	{
		float Delta = Target - Current;
		if (fabs(Delta) <= Step)
		{
			return Target;
		}
		return Current + (Delta > 0 ? Step : -Step);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// List Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void List_InitHead(ListEntry* List)
	{
		List->Next = List;
		List->Prev = List;
	}
	void List_InsertTail(ListEntry* List, ListEntry* Entry)
	{
		Entry->Next = List;
		Entry->Prev = List->Prev;

		List->Prev->Next = Entry;
		List->Prev = Entry;
	}
	void List_InsertAfter(ListEntry* Curr, ListEntry* Entry)
	{
		Entry->Next = Curr->Next;
		Entry->Prev = Curr;

		Curr->Next = Entry;
	}
	void List_InsertBefore(ListEntry* Curr, ListEntry* Entry)
	{
		Entry->Next = Curr;
		Entry->Prev = Curr->Prev;

		Curr->Prev = Curr;
	}
	void List_Remove(ListEntry* Entry)
	{
		Entry->Prev->Next = Entry->Next;
		Entry->Next->Prev = Entry->Prev;
	}
	ListEntry* List_RemoveHead(ListEntry* List)
	{
		ListEntry* Entry = 0;
		if (List_IsEmpty(List))
		{
			return 0;
		}

		Entry = List->Next;

		List->Next = Entry->Next;
		Entry->Next->Prev = List;

		Entry->Next = Entry->Prev = 0;

		return Entry;
	}
	bool List_IsEmpty(ListEntry* List)
	{
		return (List->Next == List) && (List->Prev == List);
	}
	long long unsigned List_Num(ListEntry* List)
	{
		long long unsigned NumEntries = 0;

		ListEntry* Entry = List->Next;
		while (Entry != List)
		{
			NumEntries++;
			Entry = Entry->Next;
		}

		return NumEntries;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Vector Implementation
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Vector_Alloc(Vector* Vtor, long long unsigned ValueSize)
	{
		memset(Vtor, 0, sizeof(Vector));
		Vtor->Buffer = (char unsigned*)Memory_Alloc(ValueSize * FAST_GL_VECTOR_INITIAL_CAPACITY, 0);
		Vtor->ValueSize = ValueSize;
		Vtor->BufferSize = ValueSize * FAST_GL_VECTOR_INITIAL_CAPACITY;
		Vtor->BufferNum = FAST_GL_VECTOR_INITIAL_CAPACITY;
		Vtor->BufferIndex = 0;
		Vtor->BufferOffset = 0;

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedVectors += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Vector_Push(Vector* Vtor, void* Item)
	{
		memcpy(Vtor->Buffer + Vtor->BufferOffset, Item, Vtor->ValueSize);
		Vtor->BufferIndex += 1;
		Vtor->BufferOffset += Vtor->ValueSize;
		if (Vtor->BufferIndex >= Vtor->BufferNum)
		{
			Vector_ExpandInternal(Vtor);
		}
	}
	void Vector_PushRange(Vector* Vtor, Vector* Source)
	{
		for (long long unsigned Index = 0; Index < Source->BufferIndex; Index++)
		{
			Vector_Push(Vtor, Source->Buffer + (Index * Source->ValueSize));
		}
	}
	void Vector_Pop(Vector* Vtor, void* Item)
	{
		Vtor->BufferIndex -= 1;
		Vtor->BufferOffset -= Vtor->ValueSize;
		if (Item)
		{
			memcpy(Item, Vtor->Buffer + Vtor->BufferOffset, Vtor->ValueSize);
		}
		memset(Vtor->Buffer + Vtor->BufferOffset, 0, Vtor->ValueSize);
	}
	void Vector_Resize(Vector* Vtor, long long unsigned Num)
	{
		if (Num > Vtor->BufferNum)
		{
			Vtor->Buffer = (char unsigned*)Memory_Realloc(Vtor->Buffer, Num * Vtor->ValueSize);
			Vtor->BufferNum = Num;
			Vtor->BufferSize = Num * Vtor->ValueSize;
		}
		else if (Num < Vtor->BufferNum)
		{
			Vtor->Buffer = (char unsigned*)Memory_Realloc(Vtor->Buffer, Num * Vtor->ValueSize);
			Vtor->BufferNum = Num;
			Vtor->BufferSize = Num * Vtor->ValueSize;
			Vtor->BufferIndex = MIN(Vtor->BufferIndex, Num);
			Vtor->BufferOffset = MIN(Vtor->BufferIndex, Num) * Vtor->ValueSize;
		}
	}
	void Vector_CopyFrom(Vector* Vtor, Vector* Source)
	{
		Vtor->Buffer = (char unsigned*)Memory_Realloc(Vtor->Buffer, Source->BufferSize);
		Vtor->ValueSize = Source->ValueSize;
		Vtor->BufferSize = Source->ValueSize;
		Vtor->BufferNum = Source->BufferNum;
		Vtor->BufferIndex = Source->BufferIndex;
		Vtor->BufferOffset = Source->BufferOffset;

		memcpy(Vtor->Buffer, Source->Buffer, Source->BufferOffset);
	}
	void Vector_Clear(Vector* Vtor)
	{
		Vtor->BufferIndex = 0;
		Vtor->BufferOffset = 0;
	}
	void* Vector_At(Vector* Vtor, long long unsigned Index)
	{
		assert(Index < Vtor->BufferIndex);
		return Vtor->Buffer + (Index * Vtor->ValueSize);
	}
	void* Vector_Buffer(Vector* Vtor)
	{
		return (void*)Vtor->Buffer;
	}
	bool Vector_Empty(Vector* Vtor)
	{
		return Vtor->BufferIndex == 0;
	}
	long long unsigned Vector_Num(Vector* Vtor)
	{
		return Vtor->BufferIndex;
	}
	long long unsigned Vector_Size(Vector* Vtor)
	{
		return Vtor->BufferIndex * Vtor->ValueSize;
	}
	void Vector_Free(Vector* Vtor)
	{
		Memory_Free(Vtor->Buffer);
		memset(Vtor, 0, sizeof(Vector));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedVectors -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Vector_ExpandInternal(Vector* Vtor)
	{
		long long unsigned NextBufferNum = Vtor->BufferNum * 2;
		long long unsigned NextBufferSize = Vtor->BufferSize * 2;
		Vtor->Buffer = (char unsigned*)Memory_Realloc(Vtor->Buffer, NextBufferSize);
		Vtor->BufferNum = NextBufferNum;
		Vtor->BufferSize = NextBufferSize;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// HashMap Definition
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void HashMap_Alloc(HashMap* Map)
	{
		memset(Map, 0, sizeof(HashMap));
		Map->Table = (HashMapPair**)Memory_Alloc(FAST_GL_HASH_MAP_INITIAL_CAPACITY * sizeof(HashMapPair*), 0);
		Map->TableSize = FAST_GL_HASH_MAP_INITIAL_CAPACITY;
		Map->TableCount = 0;
		for (long long unsigned TableIndex = 0; TableIndex < FAST_GL_HASH_MAP_INITIAL_CAPACITY; TableIndex++)
		{
			Map->Table[TableIndex] = 0;
		}

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedHashMaps += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void HashMap_Insert(HashMap* Map, void const* Key, long long unsigned KeySize, void const* Value, long long unsigned KeyValue)
	{
		if ((((float)(Map->TableCount + 1U)) / (float)Map->TableSize) > FAST_GL_HASH_MAP_LOAD_FACTOR)
		{
			HashMap_ResizeInternal(Map);
		}
		long long unsigned Hash = HashMap_ComputeHashInternal((char*)Key, Map->TableSize);
		HashMapPair* Pair = HashMap_PairAllocInternal(Key, KeySize, Value, KeyValue);
		Pair->Next = Map->Table[Hash];
		Map->Table[Hash] = Pair;
		Map->TableCount++;
	}
	void HashMap_InsertSimple(HashMap* Map, char const* Key, void const* Value, long long unsigned KeyValue)
	{
		if ((((float)(Map->TableCount + 1U)) / (float)Map->TableSize) > FAST_GL_HASH_MAP_LOAD_FACTOR)
		{
			HashMap_ResizeInternal(Map);
		}
		long long unsigned Hash = HashMap_ComputeHashInternal((char*)Key, Map->TableSize);
		HashMapPair* Pair = HashMap_PairAllocInternal(Key, strlen(Key), Value, KeyValue);
		Pair->Next = Map->Table[Hash];
		Map->Table[Hash] = Pair;
		Map->TableCount++;
	}
	void HashMap_Remove(HashMap* Map, void const* Key, long long unsigned KeySize)
	{
		long long unsigned Hash = HashMap_ComputeHashInternal((char*)Key, Map->TableSize);
		HashMapPair* Pair = Map->Table[Hash];
		HashMapPair* Prev = 0;
		while (Pair)
		{
			long long unsigned Size = MIN(Pair->KeySize, KeySize);
			if (strncmp((char const*)Pair->Key, (char const*)Key, Size) == 0)
			{
				if (Prev)
				{
					Prev->Next = Pair->Next;
				}
				else
				{
					Map->Table[Hash] = Pair->Next;
				}
				Memory_Free(Pair->Key);
				Memory_Free(Pair->Value);
				Memory_Free(Pair);
				Map->TableCount--;
				return;
			}
			Prev = Pair;
			Pair = Pair->Next;
		}
	}
	void HashMap_RemoveSimple(HashMap* Map, char const* Key)
	{
		long long unsigned Hash = HashMap_ComputeHashInternal((char*)Key, Map->TableSize);
		HashMapPair* Pair = Map->Table[Hash];
		HashMapPair* Prev = 0;
		while (Pair)
		{
			long long unsigned KeySize = strlen(Key);
			long long unsigned Size = MIN(Pair->KeySize, KeySize);
			if (strncmp((char const*)Pair->Key, (char const*)Key, Size) == 0)
			{
				if (Prev)
				{
					Prev->Next = Pair->Next;
				}
				else
				{
					Map->Table[Hash] = (HashMapPair*)Pair->Next;
				}
				Memory_Free(Pair->Key);
				Memory_Free(Pair->Value);
				Memory_Free(Pair);
				Map->TableCount--;
				return;
			}
			Prev = Pair;
			Pair = (HashMapPair*)Pair->Next;
		}
	}
	void* HashMap_At(HashMap* Map, void const* Key, long long unsigned KeySize)
	{
		long long unsigned Hash = HashMap_ComputeHashInternal((char*)Key, Map->TableSize);
		HashMapPair* Pair = Map->Table[Hash];
		while (Pair)
		{
			long long unsigned Size = MIN(Pair->KeySize, KeySize);
			if (strncmp((char const*)Pair->Key, (char const*)Key, Size) == 0)
			{
				return Pair->Value;
			}
			Pair = (HashMapPair*)Pair->Next;
		}
		return 0;
	}
	void* HashMap_AtSimple(HashMap* Map, char const* Key)
	{
		long long unsigned Hash = HashMap_ComputeHashInternal((char*)Key, Map->TableSize);
		HashMapPair* Pair = Map->Table[Hash];
		while (Pair)
		{
			long long unsigned KeySize = strlen(Key);
			long long unsigned Size = MIN(Pair->KeySize, KeySize);
			if (strncmp((char const*)Pair->Key, (char const*)Key, Size) == 0)
			{
				return Pair->Value;
			}
			Pair = (HashMapPair*)Pair->Next;
		}
		return 0;
	}
	void HashMap_Free(HashMap* Map)
	{
		for (long long unsigned TableIndex = 0; TableIndex < Map->TableSize; TableIndex++)
		{
			HashMapPair* Pair = Map->Table[TableIndex];
			while (Pair)
			{
				HashMapPair* Tmp = Pair;
				Pair = (HashMapPair*)Pair->Next;
				Memory_Free(Tmp->Key);
				Memory_Free(Tmp->Value);
				Memory_Free(Tmp);
			}
		}
		Memory_Free(Map->Table);
		memset(Map, 0, sizeof(HashMap));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedHashMaps -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	HashMapPair* HashMap_PairAllocInternal(void const* Key, long long unsigned KeySize, void const* Value, long long unsigned ValueSize)
	{
		HashMapPair* Pair = (HashMapPair*)Memory_Alloc(sizeof(HashMapPair), 0);
		Pair->Next = 0;
		Pair->Key = Memory_Alloc(KeySize, Key);
		Pair->Value = Memory_Alloc(ValueSize, Value);
		Pair->KeySize = KeySize;
		Pair->ValueSize = ValueSize;
		return Pair;
	}
	long long unsigned HashMap_ComputeHashInternal(char* Key, long long unsigned Modulus)
	{
		long long unsigned Hash = FAST_GL_HASH_MAP_INITIAL_HASH;
		while (*Key++) Hash = ((Hash << 5U) + Hash) + *Key;
		return Hash % Modulus;
	}
	void HashMap_ResizeInternal(HashMap* Map)
	{
		long long unsigned NextTableSize = Map->TableSize * 2;
		HashMapPair** NewTable = (HashMapPair**)Memory_Alloc(NextTableSize * sizeof(HashMapPair*), 0);
		for (long long unsigned TableIndex = 0; TableIndex < NextTableSize; TableIndex++)
		{
			NewTable[TableIndex] = 0;
		}
		for (long long unsigned TableIndex = 0; TableIndex < Map->TableSize; TableIndex++)
		{
			HashMapPair* Pair = Map->Table[TableIndex];
			while (Pair)
			{
				HashMapPair* NextPair = (HashMapPair*)Pair->Next;
				long long unsigned NewHash = HashMap_ComputeHashInternal((char*)Pair->Key, NextTableSize);
				Pair->Next = NewTable[NewHash];
				NewTable[NewHash] = Pair;
				Pair = NextPair;
			}
		}
		Memory_Free(Map->Table);
		Map->Table = NewTable;
		Map->TableSize = NextTableSize;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// FileSystem Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void FileSystem_ReadText(char** Buffer, int unsigned* BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "r");
		fseek(File, 0, SEEK_END);
		(*BufferSize) = (int unsigned)ftell(File);
		(*Buffer) = (char*)Memory_Alloc(((*BufferSize) + 1) * sizeof(char), 0);
		fseek(File, 0, SEEK_SET);
		fread((*Buffer), sizeof(char), (*BufferSize), File);
		fclose(File);
	}
	void FileSystem_ReadBinary(char unsigned** Buffer, int unsigned* BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "rb");
		fseek(File, 0, SEEK_END);
		(*BufferSize) = (int unsigned)ftell(File);
		(*Buffer) = (char unsigned*)Memory_Alloc((*BufferSize) * sizeof(char unsigned), 0);
		fseek(File, 0, SEEK_SET);
		fread((*Buffer), sizeof(char unsigned), (*BufferSize), File);
		fclose(File);
	}
	void FileSystem_WriteText(char const* Buffer, int unsigned BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "w");
		fseek(File, 0, SEEK_SET);
		fwrite(Buffer, sizeof(char), BufferSize, File);
		fclose(File);
	}
	void FileSystem_WriteBinary(char unsigned const* Buffer, int unsigned BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "wb");
		fseek(File, 0, SEEK_SET);
		fwrite(Buffer, sizeof(char unsigned), BufferSize, File);
		fclose(File);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// FileReader Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void FileReader_Alloc(FileReader* Reader, char unsigned const* Buffer, int unsigned BufferSize)
	{
		memset(Reader, 0, sizeof(FileReader));
		Reader->Buffer = Buffer;
		Reader->BufferSize = BufferSize;
		Reader->BufferOffset = 0;
	}
	void FileReader_SeekAbs(FileReader* Reader, int unsigned Offset)
	{
		Reader->BufferOffset = Offset;
	}
	void FileReader_SeekRel(FileReader* Reader, int Offset)
	{
		Reader->BufferOffset += Offset;
	}
	int unsigned FileReader_Offset(FileReader* Reader)
	{
		return Reader->BufferOffset;
	}
	char FileReader_ReadInt8(FileReader* Reader)
	{
		char Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(char));
		Reader->BufferOffset += sizeof(char);
		return Value;
	}
	char unsigned FileReader_ReadUInt8(FileReader* Reader)
	{
		char unsigned Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(char unsigned));
		Reader->BufferOffset += sizeof(char unsigned);
		return Value;
	}
	short FileReader_ReadInt16(FileReader* Reader, bool BigEndian)
	{
		short Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(short));
		Reader->BufferOffset += sizeof(short);
		return (BigEndian) ? B2L_ENDIAN_S16(Value) : Value;
	}
	short unsigned FileReader_ReadUInt16(FileReader* Reader, bool BigEndian)
	{
		short unsigned Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(short unsigned));
		Reader->BufferOffset += sizeof(short unsigned);
		return (BigEndian) ? B2L_ENDIAN_U16(Value) : Value;
	}
	int FileReader_ReadInt32(FileReader* Reader, bool BigEndian)
	{
		int Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(int));
		Reader->BufferOffset += sizeof(int);
		return (BigEndian) ? B2L_ENDIAN_S32(Value) : Value;
	}
	int unsigned FileReader_ReadUInt32(FileReader* Reader, bool BigEndian)
	{
		int unsigned Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(int unsigned));
		Reader->BufferOffset += sizeof(int unsigned);
		return (BigEndian) ? B2L_ENDIAN_U32(Value) : Value;
	}
	long long FileReader_ReadInt64(FileReader* Reader, bool BigEndian)
	{
		long long Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(long long));
		Reader->BufferOffset += sizeof(long long);
		return (BigEndian) ? B2L_ENDIAN_S64(Value) : Value;
	}
	long long unsigned FileReader_ReadUInt64(FileReader* Reader, bool BigEndian)
	{
		long long unsigned Value = 0;
		memcpy(&Value, Reader->Buffer + Reader->BufferOffset, sizeof(long long unsigned));
		Reader->BufferOffset += sizeof(long long unsigned);
		return (BigEndian) ? B2L_ENDIAN_U64(Value) : Value;
	}
	void FileReader_ReadInt8Array(FileReader* Reader, char* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(char));
		Reader->BufferOffset += NumValues * sizeof(char);
	}
	void FileReader_ReadUInt8Array(FileReader* Reader, char unsigned* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(char unsigned));
		Reader->BufferOffset += NumValues * sizeof(char unsigned);
	}
	void FileReader_ReadInt16Array(FileReader* Reader, bool BigEndian, short* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(short));
		Reader->BufferOffset += NumValues * sizeof(short);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_S16(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadUInt16Array(FileReader* Reader, bool BigEndian, short unsigned* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(short unsigned));
		Reader->BufferOffset += NumValues * sizeof(short unsigned);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_U16(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadInt32Array(FileReader* Reader, bool BigEndian, int* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(int));
		Reader->BufferOffset += NumValues * sizeof(int);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_S32(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadUInt32Array(FileReader* Reader, bool BigEndian, int unsigned* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(int unsigned));
		Reader->BufferOffset += NumValues * sizeof(int unsigned);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_U32(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadInt64Array(FileReader* Reader, bool BigEndian, long long* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(long long));
		Reader->BufferOffset += NumValues * sizeof(long long);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_S64(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadUInt64Array(FileReader* Reader, bool BigEndian, long long unsigned* Values, int unsigned NumValues)
	{
		memcpy(Values, Reader->Buffer + Reader->BufferOffset, NumValues * sizeof(long long unsigned));
		Reader->BufferOffset += NumValues * sizeof(long long unsigned);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_U64(Values[ValueIndex]);
			}
		}
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Random Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Random_Seed(char const* Seed)
	{
		if (Seed)
		{
			int unsigned Hash = 0;
			while (*Seed++)
			{
				Hash = Hash * 31 + (unsigned int)*Seed;
			}
			srand(Hash);
		}
		else
		{
			srand((int unsigned)time(0));
		}
	}
	char Random_Int8(void)
	{
		return (char)((rand() % 0x100U) - 0x7F);
	}
	short Random_Int16(void)
	{
		return (short)((rand() % 0x10000U) - 0x7FFF);
	}
	int Random_Int32(void)
	{
		return (int)(((rand() << 16) | rand()) - 0x7FFFFFFF);
	}
	long long Random_Int64(void)
	{
		return (long long)((((long long)((rand() << 16) | rand()) << 32) | (long long)((rand() << 16) | rand())) - 0x7FFFFFFFFFFFFFFF);
	}
	char Random_Int8Between(char Min, char Max)
	{
		return (char)(Min + rand() % (Max - Min + 1));
	}
	short Random_Int16Between(short Min, short Max)
	{
		return (short)(Min + rand() % (Max - Min + 1));
	}
	int Random_Int32Between(int Min, int Max)
	{
		return (int)(Min + (int)rand() * ((long long)(Max - Min + 1)) / (RAND_MAX + 1));
	}
	long long Random_Int64Between(long long Min, long long Max)
	{
		return (long long)(Min + (long long)rand() * ((long long)(Max - Min + 1)) / (RAND_MAX + 1));
	}
	char unsigned Random_UInt8(void)
	{
		return (char unsigned)(rand() % 0x100ULL);
	}
	short unsigned Random_UInt16(void)
	{
		return (short unsigned)((rand() % 0x10000ULL));
	}
	int unsigned Random_UInt32(void)
	{
		return ((int unsigned)rand() << 16) | (int unsigned)rand();
	}
	long long unsigned Random_UInt64(void)
	{
		return (long long unsigned)(((long long unsigned)(((int unsigned)rand() << 16) | (int unsigned)rand()) << 32) | (long long unsigned)(((int unsigned)rand() << 16) | (int unsigned)rand()));
	}
	char unsigned Random_UInt8Between(char unsigned Min, char unsigned Max)
	{
		return (char unsigned)(Min + rand() % (Max - Min + 1));
	}
	short unsigned Random_UInt16Between(short unsigned Min, short unsigned Max)
	{
		return (short unsigned)(Min + rand() % (Max - Min + 1));
	}
	int unsigned Random_UInt32Between(int unsigned Min, int unsigned Max)
	{
		return (int unsigned)(Min + (int unsigned)rand() * ((long long unsigned)(Max - Min + 1)) / (RAND_MAX + 1));
	}
	long long unsigned Random_UInt64Between(long long unsigned Min, long long unsigned Max)
	{
		return (long long unsigned)(Min + (long long unsigned)rand() * ((long long unsigned)(Max - Min + 1)) / (RAND_MAX + 1));
	}
	float Random_Real32(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}
	double Random_Real64(void)
	{
		return (double)rand() / (double)RAND_MAX;
	}
	float Random_Real32Between(float Min, float Max)
	{
		return Min + (Max - Min) * ((float)rand() / (float)RAND_MAX);
	}
	double Random_Real64Between(double Min, double Max)
	{
		return Min + (Max - Min) * ((double)rand() / (double)RAND_MAX);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Timer Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Timer_CpuAlloc(Timer* Timr)
	{
		memset(Timr, 0, sizeof(Timer));

		LARGE_INTEGER Frequency = { 0 };
		QueryPerformanceFrequency(&Frequency);

		Timr->Type = TIMER_TYPE_CPU;
		Timr->Frequency = (double)Frequency.QuadPart;

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTimers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Timer_GpuAlloc(Timer* Timr)
	{
		memset(Timr, 0, sizeof(Timer));

		Timr->Type = TIMER_TYPE_GPU;
		glGenQueries(1, &Timr->ComputeQuery);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTimers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Timer_BeginMeasure(Timer* Timr)
	{
		switch (Timr->Type)
		{
		case TIMER_TYPE_CPU:
		{
			LARGE_INTEGER Time = { 0 };
			QueryPerformanceCounter(&Time);

			Timr->StartNanoTime = (double)(Time.QuadPart * 1000000000ULL);

			break;
		}
		case TIMER_TYPE_GPU:
		{
			glBeginQuery(GL_TIME_ELAPSED, Timr->ComputeQuery);

			break;
		}
		}
	}
	void Timer_EndMeasure(Timer* Timr)
	{
		switch (Timr->Type)
		{
		case TIMER_TYPE_CPU:
		{
			LARGE_INTEGER Time = { 0 };
			QueryPerformanceCounter(&Time);

			Timr->EndNanoTime = (double)(Time.QuadPart * 1000000000ULL);
			Timr->ElapsedNanoTime = (Timr->EndNanoTime - Timr->StartNanoTime) / Timr->Frequency;

			break;
		}
		case TIMER_TYPE_GPU:
		{
			glEndQuery(GL_TIME_ELAPSED);
			long long unsigned Time = 0ULL;
			glGetQueryObjectui64v(Timr->ComputeQuery, GL_QUERY_RESULT, &Time);

			Timr->ElapsedNanoTime = (double)Time;

			break;
		}
		}
	}
	double Timer_ElapsedNanoSeconds(Timer* Timr)
	{
		return Timr->ElapsedNanoTime;
	}
	void Timer_Free(Timer* Timr)
	{
		switch (Timr->Type)
		{
		case TIMER_TYPE_CPU:
		{
			break;
		}
		case TIMER_TYPE_GPU:
		{
			glDeleteQueries(1, &Timr->ComputeQuery);

			break;
		}
		}

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTimers -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Transform Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Transform_Init(Transform* Trans)
	{
		memset(Trans, 0, sizeof(Transform));

		Trans->Parent = 0;

		Vector3_SetSimple(1.0F, 0.0F, 0.0F, &Trans->LocalRight);
		Vector3_SetSimple(0.0F, 1.0F, 0.0F, &Trans->LocalUp);
		Vector3_SetSimple(0.0F, 0.0F, 1.0F, &Trans->LocalForward);
		Vector3_SetSimple(-1.0F, 0.0F, 0.0F, &Trans->LocalLeft);
		Vector3_SetSimple(0.0F, -1.0F, 0.0F, &Trans->LocalDown);
		Vector3_SetSimple(0.0F, 0.0F, -1.0F, &Trans->LocalBack);
		Vector3_SetSimple(0.0F, 0.0F, 0.0F, &Trans->LocalPosition);
		Quaternion_Identity(&Trans->LocalRotation);
		Vector3_SetSimple(1.0F, 1.0F, 1.0F, &Trans->LocalScale);
		Vector3_SetSimple(0.0F, 0.0F, 0.0F, &Trans->WorldPosition);
		Quaternion_Identity(&Trans->WorldRotation);
		Vector3_SetSimple(1.0F, 1.0F, 1.0F, &Trans->WorldScale);
	}
	void Transform_GetWorldPosition(Transform* Trans, Vector3* Position)
	{
		Position->X = Trans->WorldPosition.X;
		Position->Y = Trans->WorldPosition.Y;
		Position->Z = Trans->WorldPosition.Z;
	}
	void Transform_GetWorldRotation(Transform* Trans, Quaternion* Rotation)
	{
		Rotation->X = Trans->WorldRotation.X;
		Rotation->Y = Trans->WorldRotation.Y;
		Rotation->Z = Trans->WorldRotation.Z;
		Rotation->W = Trans->WorldRotation.W;
	}
	void Transform_GetWorldEulerAngles(Transform* Trans, Vector3* Rotation)
	{
		Quaternion_EulerAngles(&Trans->WorldRotation, Rotation);

		Rotation->X = RAD_TO_DEG(Rotation->X);
		Rotation->Y = RAD_TO_DEG(Rotation->Y);
		Rotation->Z = RAD_TO_DEG(Rotation->Z);
	}
	void Transform_GetWorldScale(Transform* Trans, Vector3* Scale)
	{
		Scale->X = Trans->WorldScale.X;
		Scale->Y = Trans->WorldScale.Y;
		Scale->Z = Trans->WorldScale.Z;
	}
	void Transform_GetLocalPosition(Transform* Trans, Vector3* Position)
	{
		Position->X = Trans->LocalPosition.X;
		Position->Y = Trans->LocalPosition.Y;
		Position->Z = Trans->LocalPosition.Z;
	}
	void Transform_GetLocalRotation(Transform* Trans, Quaternion* Rotation)
	{
		Rotation->X = Trans->LocalRotation.X;
		Rotation->Y = Trans->LocalRotation.Y;
		Rotation->Z = Trans->LocalRotation.Z;
		Rotation->W = Trans->LocalRotation.W;
	}
	void Transform_GetLocalEulerAngles(Transform* Trans, Vector3* Rotation)
	{
		Quaternion_EulerAngles(&Trans->LocalRotation, Rotation);

		Rotation->X = RAD_TO_DEG(Rotation->X);
		Rotation->Y = RAD_TO_DEG(Rotation->Y);
		Rotation->Z = RAD_TO_DEG(Rotation->Z);
	}
	void Transform_GetLocalScale(Transform* Trans, Vector3* Scale)
	{
		Scale->X = Trans->LocalScale.X;
		Scale->Y = Trans->LocalScale.Y;
		Scale->Z = Trans->LocalScale.Z;
	}
	void Transform_SetPosition(Transform* Trans, Vector3 const* Position)
	{
		Trans->LocalPosition.X = Position->X;
		Trans->LocalPosition.Y = Position->Y;
		Trans->LocalPosition.Z = Position->Z;

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetPositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ)
	{
		Trans->LocalPosition.X = PositionX;
		Trans->LocalPosition.Y = PositionY;
		Trans->LocalPosition.Z = PositionZ;

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativePosition(Transform* Trans, Vector3 const* Position)
	{
		Trans->LocalPosition.X += Position->X;
		Trans->LocalPosition.Y += Position->Y;
		Trans->LocalPosition.Z += Position->Z;

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativePositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ)
	{
		Trans->LocalPosition.X += PositionX;
		Trans->LocalPosition.Y += PositionY;
		Trans->LocalPosition.Z += PositionZ;

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRotation(Transform* Trans, Quaternion const* Rotation)
	{
		UNREFERENCED_PARAMETER(Trans);
		UNREFERENCED_PARAMETER(Rotation);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Transform_SetRotationSimple(Transform* Trans, float RotationX, float RotationY, float RotationZ, float RotationW)
	{
		UNREFERENCED_PARAMETER(Trans);
		UNREFERENCED_PARAMETER(RotationX);
		UNREFERENCED_PARAMETER(RotationY);
		UNREFERENCED_PARAMETER(RotationZ);
		UNREFERENCED_PARAMETER(RotationW);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Transform_SetRelativeRotation(Transform* Trans, Quaternion const* Rotation)
	{
		UNREFERENCED_PARAMETER(Trans);
		UNREFERENCED_PARAMETER(Rotation);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Transform_SetRelativeRotationSimple(Transform* Trans, float RotationX, float RotationY, float RotationZ, float RotationW)
	{
		UNREFERENCED_PARAMETER(Trans);
		UNREFERENCED_PARAMETER(RotationX);
		UNREFERENCED_PARAMETER(RotationY);
		UNREFERENCED_PARAMETER(RotationZ);
		UNREFERENCED_PARAMETER(RotationW);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Transform_SetEulerAngles(Transform* Trans, Vector3 const* Rotation)
	{
		float Pitch = DEG_TO_RAD(Rotation->X);
		float Yaw = DEG_TO_RAD(Rotation->Y);
		float Roll = DEG_TO_RAD(Rotation->Z);

		Vector3 LocalLeft = VECTOR3_ZERO;
		Vector3 LocalDown = VECTOR3_ZERO;
		Vector3 LocalBack = VECTOR3_ZERO;

		Quaternion QX = QUATERNION_ZERO;
		Quaternion QY = QUATERNION_ZERO;
		Quaternion QZ = QUATERNION_ZERO;
		Quaternion QXZ = QUATERNION_ZERO;
		Quaternion QYXZ = QUATERNION_ZERO;
		Quaternion QNYXZ = QUATERNION_ZERO;

		Vector3 LR = VECTOR3_ZERO;
		Vector3 LU = VECTOR3_ZERO;
		Vector3 LF = VECTOR3_ZERO;
		Vector3 LRN = VECTOR3_ZERO;
		Vector3 LUN = VECTOR3_ZERO;
		Vector3 LFN = VECTOR3_ZERO;

		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Quaternion_AngleAxis(Pitch, &ParentTrans->LocalRight, &QX);
			Quaternion_AngleAxis(Yaw, &ParentTrans->LocalUp, &QY);
			Quaternion_AngleAxis(Roll, &ParentTrans->LocalForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Set(&QNYXZ, &Trans->LocalRotation);

			Vector3_Rotate(&ParentTrans->LocalRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&ParentTrans->LocalUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&ParentTrans->LocalForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, &sWorldRight, &QX);
			Quaternion_AngleAxis(Yaw, &sWorldUp, &QY);
			Quaternion_AngleAxis(Roll, &sWorldForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Set(&QNYXZ, &Trans->LocalRotation);

			Vector3_Rotate(&sWorldRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&sWorldUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&sWorldForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll)
	{
		Pitch = DEG_TO_RAD(Pitch);
		Yaw = DEG_TO_RAD(Yaw);
		Roll = DEG_TO_RAD(Roll);

		Vector3 LocalLeft = VECTOR3_ZERO;
		Vector3 LocalDown = VECTOR3_ZERO;
		Vector3 LocalBack = VECTOR3_ZERO;

		Quaternion QX = QUATERNION_ZERO;
		Quaternion QY = QUATERNION_ZERO;
		Quaternion QZ = QUATERNION_ZERO;
		Quaternion QXZ = QUATERNION_ZERO;
		Quaternion QYXZ = QUATERNION_ZERO;
		Quaternion QNYXZ = QUATERNION_ZERO;

		Vector3 LR = VECTOR3_ZERO;
		Vector3 LU = VECTOR3_ZERO;
		Vector3 LF = VECTOR3_ZERO;
		Vector3 LRN = VECTOR3_ZERO;
		Vector3 LUN = VECTOR3_ZERO;
		Vector3 LFN = VECTOR3_ZERO;

		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Quaternion_AngleAxis(Pitch, &ParentTrans->LocalRight, &QX);
			Quaternion_AngleAxis(Yaw, &ParentTrans->LocalUp, &QY);
			Quaternion_AngleAxis(Roll, &ParentTrans->LocalForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Set(&QNYXZ, &Trans->LocalRotation);

			Vector3_Rotate(&ParentTrans->LocalRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&ParentTrans->LocalUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&ParentTrans->LocalForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, &sWorldRight, &QX);
			Quaternion_AngleAxis(Yaw, &sWorldUp, &QY);
			Quaternion_AngleAxis(Roll, &sWorldForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Set(&QNYXZ, &Trans->LocalRotation);

			Vector3_Rotate(&sWorldRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&sWorldUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&sWorldForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativeEulerAngles(Transform* Trans, Vector3 const* Rotation)
	{
		float Pitch = DEG_TO_RAD(Rotation->X);
		float Yaw = DEG_TO_RAD(Rotation->Y);
		float Roll = DEG_TO_RAD(Rotation->Z);

		Vector3 LocalLeft = VECTOR3_ZERO;
		Vector3 LocalDown = VECTOR3_ZERO;
		Vector3 LocalBack = VECTOR3_ZERO;

		Quaternion QX = QUATERNION_ZERO;
		Quaternion QY = QUATERNION_ZERO;
		Quaternion QZ = QUATERNION_ZERO;
		Quaternion QXZ = QUATERNION_ZERO;
		Quaternion QYXZ = QUATERNION_ZERO;
		Quaternion QNYXZ = QUATERNION_ZERO;
		Quaternion QNYXZR = QUATERNION_ZERO;

		Vector3 LR = VECTOR3_ZERO;
		Vector3 LU = VECTOR3_ZERO;
		Vector3 LF = VECTOR3_ZERO;
		Vector3 LRN = VECTOR3_ZERO;
		Vector3 LUN = VECTOR3_ZERO;
		Vector3 LFN = VECTOR3_ZERO;

		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Quaternion_AngleAxis(Pitch, &ParentTrans->LocalRight, &QX);
			Quaternion_AngleAxis(Yaw, &ParentTrans->LocalUp, &QY);
			Quaternion_AngleAxis(Roll, &ParentTrans->LocalForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Mul(&Trans->LocalRotation, &QNYXZ, &QNYXZR);
			Quaternion_Set(&QNYXZR, &Trans->LocalRotation);

			Vector3_Rotate(&ParentTrans->LocalRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&ParentTrans->LocalUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&ParentTrans->LocalForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, &sWorldRight, &QX);
			Quaternion_AngleAxis(Yaw, &sWorldUp, &QY);
			Quaternion_AngleAxis(Roll, &sWorldForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Mul(&Trans->LocalRotation, &QNYXZ, &QNYXZR);
			Quaternion_Set(&QNYXZR, &Trans->LocalRotation);

			Vector3_Rotate(&sWorldRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&sWorldUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&sWorldForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativeEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll)
	{
		Pitch = DEG_TO_RAD(Pitch);
		Yaw = DEG_TO_RAD(Yaw);
		Roll = DEG_TO_RAD(Roll);

		Vector3 LocalLeft = VECTOR3_ZERO;
		Vector3 LocalDown = VECTOR3_ZERO;
		Vector3 LocalBack = VECTOR3_ZERO;

		Quaternion QX = QUATERNION_ZERO;
		Quaternion QY = QUATERNION_ZERO;
		Quaternion QZ = QUATERNION_ZERO;
		Quaternion QXZ = QUATERNION_ZERO;
		Quaternion QYXZ = QUATERNION_ZERO;
		Quaternion QNYXZ = QUATERNION_ZERO;
		Quaternion QNYXZR = QUATERNION_ZERO;

		Vector3 LR = VECTOR3_ZERO;
		Vector3 LU = VECTOR3_ZERO;
		Vector3 LF = VECTOR3_ZERO;
		Vector3 LRN = VECTOR3_ZERO;
		Vector3 LUN = VECTOR3_ZERO;
		Vector3 LFN = VECTOR3_ZERO;

		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Quaternion_AngleAxis(Pitch, &ParentTrans->LocalRight, &QX);
			Quaternion_AngleAxis(Yaw, &ParentTrans->LocalUp, &QY);
			Quaternion_AngleAxis(Roll, &ParentTrans->LocalForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Mul(&Trans->LocalRotation, &QNYXZ, &QNYXZR);
			Quaternion_Set(&QNYXZR, &Trans->LocalRotation);

			Vector3_Rotate(&ParentTrans->LocalRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&ParentTrans->LocalUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&ParentTrans->LocalForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, &sWorldRight, &QX);
			Quaternion_AngleAxis(Yaw, &sWorldUp, &QY);
			Quaternion_AngleAxis(Roll, &sWorldForward, &QZ);

			Quaternion_Mul(&QX, &QZ, &QXZ);
			Quaternion_Mul(&QY, &QXZ, &QYXZ);
			Quaternion_Norm(&QYXZ, &QNYXZ);
			Quaternion_Mul(&Trans->LocalRotation, &QNYXZ, &QNYXZR);
			Quaternion_Set(&QNYXZR, &Trans->LocalRotation);

			Vector3_Rotate(&sWorldRight, &Trans->LocalRotation, &LR);
			Vector3_Rotate(&sWorldUp, &Trans->LocalRotation, &LU);
			Vector3_Rotate(&sWorldForward, &Trans->LocalRotation, &LF);

			Vector3_Norm(&LR, &LRN);
			Vector3_Norm(&LU, &LUN);
			Vector3_Norm(&LF, &LFN);

			Vector3_Set(&LRN, &Trans->LocalRight);
			Vector3_Set(&LUN, &Trans->LocalUp);
			Vector3_Set(&LFN, &Trans->LocalForward);

			LocalLeft.X = -Trans->LocalRight.X;
			LocalLeft.Y = -Trans->LocalRight.Y;
			LocalLeft.Z = -Trans->LocalRight.Z;

			LocalDown.X = -Trans->LocalUp.X;
			LocalDown.Y = -Trans->LocalUp.Y;
			LocalDown.Z = -Trans->LocalUp.Z;

			LocalBack.X = -Trans->LocalForward.X;
			LocalBack.Y = -Trans->LocalForward.Y;
			LocalBack.Z = -Trans->LocalForward.Z;

			Vector3_Set(&LocalLeft, &Trans->LocalLeft);
			Vector3_Set(&LocalDown, &Trans->LocalDown);
			Vector3_Set(&LocalBack, &Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetScale(Transform* Trans, Vector3 const* Scale)
	{
		Trans->LocalScale.X = Scale->X;
		Trans->LocalScale.Y = Scale->Y;
		Trans->LocalScale.Z = Scale->Z;

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_SetScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ)
	{
		Trans->LocalScale.X = ScaleX;
		Trans->LocalScale.Y = ScaleY;
		Trans->LocalScale.Z = ScaleZ;

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_SetRelativeScale(Transform* Trans, Vector3 const* Scale)
	{
		Trans->LocalScale.X += Scale->X;
		Trans->LocalScale.Y += Scale->Y;
		Trans->LocalScale.Z += Scale->Z;

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_SetRelativeScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ)
	{
		Trans->LocalScale.X += ScaleX;
		Trans->LocalScale.Y += ScaleY;
		Trans->LocalScale.Z += ScaleZ;

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_ComputeModelMatrix(Transform* Trans, Matrix4x4* Model)
	{
		float X2 = Trans->WorldRotation.X + Trans->WorldRotation.X;
		float Y2 = Trans->WorldRotation.Y + Trans->WorldRotation.Y;
		float Z2 = Trans->WorldRotation.Z + Trans->WorldRotation.Z;

		float XX = Trans->WorldRotation.X * X2;
		float YY = Trans->WorldRotation.Y * Y2;
		float ZZ = Trans->WorldRotation.Z * Z2;
		float XY = Trans->WorldRotation.X * Y2;
		float XZ = Trans->WorldRotation.X * Z2;
		float YZ = Trans->WorldRotation.Y * Z2;
		float WX = Trans->WorldRotation.W * X2;
		float WY = Trans->WorldRotation.W * Y2;
		float WZ = Trans->WorldRotation.W * Z2;

		Model->M00 = (1.0F - (YY + ZZ)) * Trans->WorldScale.X;
		Model->M01 = (XY - WZ) * Trans->WorldScale.X;
		Model->M02 = (XZ + WY) * Trans->WorldScale.X;
		Model->M03 = 0.0F;
		Model->M10 = (XY + WZ) * Trans->WorldScale.Y;
		Model->M11 = (1.0F - (XX + ZZ)) * Trans->WorldScale.Y;
		Model->M12 = (YZ - WX) * Trans->WorldScale.Y;
		Model->M13 = 0.0F;
		Model->M20 = (XZ - WY) * Trans->WorldScale.Z;
		Model->M21 = (YZ + WX) * Trans->WorldScale.Z;
		Model->M22 = (1.0F - (XX + YY)) * Trans->WorldScale.Z;
		Model->M23 = 0.0F;
		Model->M30 = Trans->WorldPosition.X;
		Model->M31 = Trans->WorldPosition.Y;
		Model->M32 = Trans->WorldPosition.Z;
		Model->M33 = 1.0F;
	}
	void Transform_ComputeWorldPositionInternal(Transform* Trans)
	{
		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Vector3 RotatedLocalPosition = VECTOR3_ZERO;
			Vector3 WorldPosition = VECTOR3_ZERO;

			Vector3_Rotate(&Trans->LocalPosition, &ParentTrans->WorldRotation, &RotatedLocalPosition);
			Vector3_Add(&ParentTrans->WorldPosition, &RotatedLocalPosition, &WorldPosition);
			Vector3_Set(&WorldPosition, &Trans->WorldPosition);
		}
		else
		{
			Vector3_Set(&Trans->LocalPosition, &Trans->WorldPosition);
		}
	}
	void Transform_ComputeWorldRotationInternal(Transform* Trans)
	{
		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Quaternion WorldRotation = QUATERNION_ZERO;

			Quaternion_Mul(&Trans->LocalRotation, &ParentTrans->WorldRotation, &WorldRotation);
			Quaternion_Set(&WorldRotation, &Trans->WorldRotation);
		}
		else
		{
			Quaternion_Set(&Trans->LocalRotation, &Trans->WorldRotation);
		}
	}
	void Transform_ComputeWorldScaleInternal(Transform* Trans)
	{
		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Vector3 WorldScale = VECTOR3_ZERO;

			Vector3_Mul(&Trans->LocalScale, &ParentTrans->WorldScale, &WorldScale);
			Vector3_Set(&WorldScale, &Trans->WorldScale);
		}
		else
		{
			Vector3_Set(&Trans->LocalScale, &Trans->WorldScale);
		}
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Controller Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Controller_FirstPersonAlloc(FirstPersonController* Controller)
	{
		memset(Controller, 0, sizeof(FirstPersonController));

		Transform_Init(&Controller->Transform);
		Transform_SetPositionSimple(&Controller->Transform, 0.0F, 0.0F, -10.0F);
		Controller->KeyboardMovementSpeed = 5.0F;
		Controller->MouseMovementSpeed = 10.0F;
		Controller->MouseRotationSpeed = 10.0F;
		Controller->RollSpeed = 0.8F;
		Controller->MouseDrag = 50.0F;
		Vector2_Zero(&Controller->MousePositionStart);
		Vector2_Zero(&Controller->MousePositionEnd);
	}
	void Controller_OrbitAlloc(OrbitController* Controller)
	{
		memset(Controller, 0, sizeof(OrbitController));

		Transform_Init(&Controller->Transform);
		Transform_SetPositionSimple(&Controller->Transform, 0.0F, 0.0F, -10.0F);
		Controller->KeyboardMovementSpeed = 5.0F;
		Controller->MouseMovementSpeed = 10.0F;
		Controller->MouseRotationSpeed = 10.0F;
		Controller->MouseDrag = 50.0F;
		Controller->Distance = 20.0F;
		Vector2_Zero(&Controller->MousePositionStart);
		Vector2_Zero(&Controller->MousePositionEnd);
	}
	void Controller_UpdateFirstPerson(FirstPersonController* Controller, float DeltaTime)
	{
		float Speed = Controller->KeyboardMovementSpeed * DeltaTime;

		Transform* Trans = &Controller->Transform;

		Vector3 RightStep = VECTOR3_ZERO;
		Vector3 LeftStep = VECTOR3_ZERO;
		Vector3 ForwardStep = VECTOR3_ZERO;
		Vector3 BackStep = VECTOR3_ZERO;
		Vector3 RollLeftStep = { 0.0F, 0.0F, -Controller->RollSpeed };
		Vector3 RollRightStep = { 0.0F, 0.0F, Controller->RollSpeed };

		Vector3_MulScalar(&Trans->LocalRight, Speed, &RightStep);
		Vector3_MulScalar(&Trans->LocalLeft, Speed, &LeftStep);
		Vector3_MulScalar(&Trans->LocalForward, Speed, &ForwardStep);
		Vector3_MulScalar(&Trans->LocalBack, Speed, &BackStep);

		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_D)) Transform_SetRelativePosition(Trans, &RightStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_A)) Transform_SetRelativePosition(Trans, &LeftStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_W)) Transform_SetRelativePosition(Trans, &ForwardStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_S)) Transform_SetRelativePosition(Trans, &BackStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_E)) Transform_SetRelativeEulerAngles(Trans, &RollLeftStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_Q)) Transform_SetRelativeEulerAngles(Trans, &RollRightStep);

		if (Window_IsMouseKeyPressed(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionStart.X = (float)Window_GetMousePositionX();
			Controller->MousePositionStart.Y = (float)Window_GetMousePositionY();
		}

		if (Window_IsMouseKeyHeld(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionEnd.X = (float)Window_GetMousePositionX();
			Controller->MousePositionEnd.Y = (float)Window_GetMousePositionY();

			Vector2 MousePositionDelta = VECTOR2_ZERO;

			Vector2_Sub(&Controller->MousePositionStart, &Controller->MousePositionEnd, &MousePositionDelta);

			if (Vector2_Length2(&MousePositionDelta) > (EPSILON_2 * EPSILON_2))
			{
				Vector2 MousePositionDeltaDrag = VECTOR2_ZERO;

				Vector2_MulScalar(&MousePositionDelta, Controller->MouseDrag * DeltaTime, &MousePositionDeltaDrag);
				Vector2_Sub(&Controller->MousePositionStart, &MousePositionDelta, &Controller->MousePositionStart);
			}
			else
			{
				Vector2_Set(&Controller->MousePositionEnd, &Controller->MousePositionStart);
			}

			float Pitch = -MousePositionDelta.Y * Controller->MouseRotationSpeed * DeltaTime;
			float Yaw = -MousePositionDelta.X * Controller->MouseRotationSpeed * DeltaTime;

			Transform_SetRelativeEulerAnglesSimple(Trans, Pitch, Yaw, 0.0F);
		}
	}
	void Controller_UpdateOrbit(OrbitController* Controller, float DeltaTime)
	{
		float Speed = Controller->KeyboardMovementSpeed * DeltaTime;

		Transform* Trans = &Controller->Transform;

		Vector3 RightStep = VECTOR3_ZERO;
		Vector3 LeftStep = VECTOR3_ZERO;
		Vector3 ForwardStep = VECTOR3_ZERO;
		Vector3 BackStep = VECTOR3_ZERO;

		Vector3_MulScalar(&sWorldRight, Speed, &RightStep);
		Vector3_MulScalar(&sWorldLeft, Speed, &LeftStep);
		Vector3_MulScalar(&sWorldForward, Speed, &ForwardStep);
		Vector3_MulScalar(&sWorldBack, Speed, &BackStep);

		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_D)) Transform_SetRelativePosition(Trans, &RightStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_A)) Transform_SetRelativePosition(Trans, &LeftStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_W)) Transform_SetRelativePosition(Trans, &ForwardStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_S)) Transform_SetRelativePosition(Trans, &BackStep);

		if (Window_IsMouseKeyPressed(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionStart.X = (float)Window_GetMousePositionX();
			Controller->MousePositionStart.Y = (float)Window_GetMousePositionY();
		}

		if (Window_IsMouseKeyHeld(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionEnd.X = (float)Window_GetMousePositionX();
			Controller->MousePositionEnd.Y = (float)Window_GetMousePositionY();

			Vector2 MousePositionDelta = VECTOR2_ZERO;

			Vector2_Sub(&Controller->MousePositionStart, &Controller->MousePositionEnd, &MousePositionDelta);

			if (Vector2_Length2(&MousePositionDelta) > (EPSILON_2 * EPSILON_2))
			{
				Vector2 MousePositionDeltaDrag = VECTOR2_ZERO;

				Vector2_MulScalar(&MousePositionDelta, Controller->MouseDrag * DeltaTime, &MousePositionDeltaDrag);
				Vector2_Sub(&Controller->MousePositionStart, &MousePositionDelta, &Controller->MousePositionStart);
			}
			else
			{
				Vector2_Set(&Controller->MousePositionEnd, &Controller->MousePositionStart);
			}

			float Pitch = -MousePositionDelta.Y * Controller->MouseRotationSpeed * DeltaTime;
			float Yaw = -MousePositionDelta.X * Controller->MouseRotationSpeed * DeltaTime;

			Transform_SetRelativeEulerAnglesSimple(Trans, Pitch, Yaw, 0.0F);
		}
	}
	void Controller_ComputeFirstPersonViewMatrix(FirstPersonController* Controller, Matrix4x4* View)
	{
		Transform* Trans = &Controller->Transform;

		Vector3 Eye = { Trans->WorldPosition.X, Trans->WorldPosition.Y, Trans->WorldPosition.Z };
		Vector3 Center = { Trans->WorldPosition.X + Trans->LocalForward.X, Trans->WorldPosition.Y + Trans->LocalForward.Y, Trans->WorldPosition.Z + Trans->LocalForward.Z };
		Vector3 Up = { Trans->LocalUp.X, Trans->LocalUp.Y, Trans->LocalUp.Z };

		Matrix4x4_LookAt(&Eye, &Center, &Up, View);
	}
	void Controller_ComputeOrbitViewMatrix(OrbitController* Controller, Matrix4x4* View)
	{
		Transform* Trans = &Controller->Transform;

		Vector3 Eye = { Trans->WorldPosition.X + Trans->LocalBack.X * Controller->Distance, Trans->WorldPosition.Y + Trans->LocalBack.Y * Controller->Distance, Trans->WorldPosition.Z + Trans->LocalBack.Z * Controller->Distance };
		Vector3 Center = { Trans->WorldPosition.X, Trans->WorldPosition.Y, Trans->WorldPosition.Z };
		Vector3 Up = { Trans->LocalUp.X, Trans->LocalUp.Y, Trans->LocalUp.Z };

		Matrix4x4_LookAt(&Eye, &Center, &Up, View);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Shader Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Shader_VertexFragmentAlloc(int unsigned* Program, char const* VertexSource, char const* FragmentSource)
	{
		(*Program) = glCreateProgram();

		int unsigned VertexShader = glCreateShader(GL_VERTEX_SHADER);
		int unsigned FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(VertexShader, 1, &VertexSource, 0);
		glCompileShader(VertexShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(VertexShader);
#endif // FAST_GL_DEBUG
		glShaderSource(FragmentShader, 1, &FragmentSource, 0);
		glCompileShader(FragmentShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(FragmentShader);
#endif // FAST_GL_DEBUG
		glAttachShader((*Program), VertexShader);
		glAttachShader((*Program), FragmentShader);
		glLinkProgram((*Program));
#ifdef FAST_GL_DEBUG
		Shader_CheckLinkStatus((*Program));
#endif // FAST_GL_DEBUG
		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrograms += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Shader_VertexGeometryFragmentAlloc(int unsigned* Program, char const* VertexSource, const char* GeometrySource, char const* FragmentSource)
	{
		(*Program) = glCreateProgram();

		int unsigned VertexShader = glCreateShader(GL_VERTEX_SHADER);
		int unsigned GeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		int unsigned FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(VertexShader, 1, &VertexSource, 0);
		glCompileShader(VertexShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(VertexShader);
#endif // FAST_GL_DEBUG
		glShaderSource(GeometryShader, 1, &GeometrySource, 0);
		glCompileShader(GeometryShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(GeometryShader);
#endif // FAST_GL_DEBUG
		glShaderSource(FragmentShader, 1, &FragmentSource, 0);
		glCompileShader(FragmentShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(FragmentShader);
#endif // FAST_GL_DEBUG
		glAttachShader((*Program), VertexShader);
		glAttachShader((*Program), GeometryShader);
		glAttachShader((*Program), FragmentShader);
		glLinkProgram((*Program));
#ifdef FAST_GL_DEBUG
		Shader_CheckLinkStatus((*Program));
#endif // FAST_GL_DEBUG
		glDeleteShader(VertexShader);
		glDeleteShader(GeometryShader);
		glDeleteShader(FragmentShader);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrograms += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Shader_ComputeAlloc(int unsigned* Program, char const* ComputeSource)
	{
		(*Program) = glCreateProgram();

		int unsigned ComputeShader = glCreateShader(GL_COMPUTE_SHADER);

		glShaderSource(ComputeShader, 1, &ComputeSource, 0);
		glCompileShader(ComputeShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(ComputeShader);
#endif // FAST_GL_DEBUG
		glAttachShader((*Program), ComputeShader);
		glLinkProgram((*Program));
#ifdef FAST_GL_DEBUG
		Shader_CheckLinkStatus((*Program));
#endif // FAST_GL_DEBUG
		glDeleteShader(ComputeShader);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrograms += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Shader_Bind(int unsigned Program)
	{
		glUseProgram(Program);
	}
	void Shader_SetUniformInt32(int unsigned Program, char const* UniformName, int Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniform1i(Location, Value);
	}
	void Shader_SetUniformUInt32(int unsigned Program, char const* UniformName, int unsigned Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniform1ui(Location, Value);
	}
	void Shader_SetUniformReal32(int unsigned Program, char const* UniformName, float Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniform1f(Location, Value);
	}
	void Shader_SetUniformVector2(int unsigned Program, char const* UniformName, Vector2 const* Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniform2fv(Location, 1, &Value->Data[0]);
	}
	void Shader_SetUniformVector3(int unsigned Program, char const* UniformName, Vector3 const* Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniform3fv(Location, 1, &Value->Data[0]);
	}
	void Shader_SetUniformVector4(int unsigned Program, char const* UniformName, Vector4 const* Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniform4fv(Location, 1, &Value->Data[0]);
	}
	void Shader_SetUniformMatrix4(int unsigned Program, char const* UniformName, Matrix4x4 const* Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
#ifdef FAST_GL_DEBUG
		if (Location < 0)
		{
			printf("Shader %u cannot assign to uniform %s\n", Program, UniformName);
		}
#endif // FAST_GL_DEBUG
		glUniformMatrix4fv(Location, 1, 0, &Value->Data[0]);
	}
	void Shader_ExecuteCompute(int unsigned NumGroupsX, int unsigned NumGroupsY, int unsigned NumGroupsZ)
	{
		glDispatchCompute(NumGroupsX, NumGroupsY, NumGroupsZ);
	}
	void Shader_CheckCompileStatus(int unsigned Shader)
	{
#ifdef FAST_GL_DEBUG
		int CompileStatus = 0;
		int InfoLogLength = 0;
		char Log[0x400] = { 0 };
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompileStatus);
		if (CompileStatus == 0)
		{
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0)
			{
				InfoLogLength = MIN(InfoLogLength, (int)sizeof(Log));
				glGetShaderInfoLog(Shader, InfoLogLength, &InfoLogLength, Log);
				printf("%s\n", Log);
			}
		}
#else
		UNREFERENCED_PARAMETER(Shader);
#endif // FAST_GL_DEBUG
	}
	void Shader_CheckLinkStatus(int unsigned Program)
	{
#ifdef FAST_GL_DEBUG
		int CompileStatus = 0;
		int InfoLogLength = 0;
		char Log[0x400] = { 0 };
		glGetProgramiv(Program, GL_LINK_STATUS, &CompileStatus);
		if (CompileStatus == 0)
		{
			glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0)
			{
				InfoLogLength = MIN(InfoLogLength, (int)sizeof(Log));
				glGetProgramInfoLog(Program, InfoLogLength, &InfoLogLength, &Log[0]);
				printf("%s\n", Log);
			}
		}
#else
		UNREFERENCED_PARAMETER(Program);
#endif // FAST_GL_DEBUG
	}
	void Shader_Free(int unsigned Program)
	{
		glDeleteProgram(Program);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrograms -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// VertexArray Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void VertexArray_Alloc(int unsigned* VertexArray)
	{
		glGenVertexArrays(1, VertexArray);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedVertexArrays += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void VertexArray_Bind(int unsigned VertexArray)
	{
		glBindVertexArray(VertexArray);
	}
	void VertexArray_DrawPoints(int unsigned Count)
	{
		glDrawArrays(GL_LINES, 0, (int)Count);
	}
	void VertexArray_DrawPointsInstanced(int unsigned Count, int unsigned NumInstances)
	{
		glDrawArraysInstanced(GL_POINTS, 0, (int)Count, (int)NumInstances);
	}
	void VertexArray_DrawLines(int unsigned Count)
	{
		glDrawArrays(GL_LINES, 0, (int)Count);
	}
	void VertexArray_DrawLinesInstanced(int unsigned Count, int unsigned NumInstances)
	{
		glDrawArraysInstanced(GL_LINES, 0, (int)Count, (int)NumInstances);
	}
	void VertexArray_DrawLineStrip(int unsigned Count)
	{
		glDrawArrays(GL_LINE_STRIP, 0, (int)Count);
	}
	void VertexArray_DrawLineStripInstanced(int unsigned Count, int unsigned NumInstances)
	{
		glDrawArraysInstanced(GL_LINE_STRIP, 0, (int)Count, (int)NumInstances);
	}
	void VertexArray_DrawTriangles(int unsigned Count)
	{
		glDrawArrays(GL_TRIANGLES, 0, (int)Count);
	}
	void VertexArray_DrawTrianglesInstanced(int unsigned Count, int unsigned NumInstances)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, (int)Count, (int)NumInstances);
	}
	void VertexArray_DrawTriangleStrip(int unsigned Count)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, (int)Count);
	}
	void VertexArray_DrawTriangleStripInstanced(int unsigned Count, int unsigned NumInstances)
	{
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, (int)Count, (int)NumInstances);
	}
	void VertexArray_UnBind(void)
	{
		glBindVertexArray(0);
	}
	void VertexArray_Free(int unsigned VertexArray)
	{
		glDeleteVertexArrays(1, &VertexArray);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedVertexArrays -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Buffer Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Buffer_VertexAlloc(int unsigned* Buffer)
	{
		glGenBuffers(1, Buffer);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_IndexAlloc(int unsigned* Buffer)
	{
		glGenBuffers(1, Buffer);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_UniformAlloc(int unsigned* Buffer)
	{
		glGenBuffers(1, Buffer);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_StorageAlloc(int unsigned* Buffer)
	{
		glGenBuffers(1, Buffer);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_VertexAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);

		glBindBuffer(GL_ARRAY_BUFFER, (*Buffer));
		glBufferData(GL_ARRAY_BUFFER, (int unsigned)Size, Data, Usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_IndexAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*Buffer));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int unsigned)Size, Data, Usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_UniformAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);

		glBindBuffer(GL_UNIFORM_BUFFER, (*Buffer));
		glBufferData(GL_UNIFORM_BUFFER, (int unsigned)Size, Data, Usage);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_StorageAllocSimple(int unsigned* Buffer, long long unsigned Size, void* Data, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, (*Buffer));
		glBufferData(GL_SHADER_STORAGE_BUFFER, (int unsigned)Size, Data, Usage);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Buffer_VertexBind(int unsigned Buffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	}
	void Buffer_IndexBind(int unsigned Buffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer);
	}
	void Buffer_UniformBind(int unsigned Buffer)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, Buffer);
	}
	void Buffer_StorageBind(int unsigned Buffer)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer);
	}
	void Buffer_VertexUnBind(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Buffer_IndexUnBind(void)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Buffer_UniformUnBind(void)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	void Buffer_StorageUnBind(void)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	void Buffer_VertexResize(long long unsigned Size, void* Data, int unsigned Usage)
	{
		glBufferData(GL_ARRAY_BUFFER, (int unsigned)Size, Data, Usage);
	}
	void Buffer_IndexResize(long long unsigned Size, void* Data, int unsigned Usage)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int unsigned)Size, Data, Usage);
	}
	void Buffer_UniformResize(long long unsigned Size, void* Data, int unsigned Usage)
	{
		glBufferData(GL_UNIFORM_BUFFER, (int unsigned)Size, Data, Usage);
	}
	void Buffer_StorageResize(long long unsigned Size, void* Data, int unsigned Usage)
	{
		glBufferData(GL_SHADER_STORAGE_BUFFER, (int unsigned)Size, Data, Usage);
	}
	void Buffer_VertexEnableAttrib(int unsigned Index)
	{
		glEnableVertexAttribArray(Index);
	}
	void Buffer_VertexAttribPointerReal32(int unsigned Index, int unsigned Size, long long unsigned Stride, long long unsigned Offset)
	{
		glVertexAttribPointer(Index, (int)Size, GL_FLOAT, 0, (int unsigned)Stride, (void*)Offset);
	}
	void Buffer_VertexAttribPointerUInt32(int unsigned Index, int unsigned Size, long long unsigned Stride, long long unsigned Offset)
	{
		glVertexAttribIPointer(Index, (int)Size, GL_UNSIGNED_INT, (int unsigned)Stride, (void*)Offset);
	}
	void Buffer_VertexAttribDivisor(int unsigned Index, int unsigned Divisor)
	{
		glVertexAttribDivisor(Index, Divisor);
	}
	void Buffer_VertexSetData(void const* Data, long long unsigned Size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_IndexSetData(void const* Data, long long unsigned Size)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_UniformSetData(void const* Data, long long unsigned Size)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_StorageSetData(void const* Data, long long unsigned Size)
	{
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_VertexGetData(void* Data, long long unsigned Size)
	{
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_IndexGetData(void* Data, long long unsigned Size)
	{
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_UniformGetData(void* Data, long long unsigned Size)
	{
		glGetBufferSubData(GL_UNIFORM_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_StorageGetData(void* Data, long long unsigned Size)
	{
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, (int unsigned)Size, Data);
	}
	void Buffer_VertexSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_IndexSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_UniformSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_StorageSetSubData(void const* Data, long long unsigned Offset, long long unsigned Size)
	{
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_VertexGetSubData(void* Data, long long unsigned Offset, long long unsigned Size)
	{
		glGetBufferSubData(GL_ARRAY_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_IndexGetSubData(void* Data, long long unsigned Offset, long long unsigned Size)
	{
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_UniformGetSubData(void* Data, long long unsigned Offset, long long unsigned Size)
	{
		glGetBufferSubData(GL_UNIFORM_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void Buffer_StorageGetSubData(void* Data, long long unsigned Offset, long long unsigned Size)
	{
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, (int unsigned)Offset, (int unsigned)Size, Data);
	}
	void* Buffer_VertexMap(int unsigned Access)
	{
		return glMapBuffer(GL_ARRAY_BUFFER, Access);
	}
	void* Buffer_IndexMap(int unsigned Access)
	{
		return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, Access);
	}
	void* Buffer_UniformMap(int unsigned Access)
	{
		return glMapBuffer(GL_UNIFORM_BUFFER, Access);
	}
	void* Buffer_StorageMap(int unsigned Access)
	{
		return glMapBuffer(GL_SHADER_STORAGE_BUFFER, Access);
	}
	void Buffer_VertexUnMap(void)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	void Buffer_IndexUnMap(void)
	{
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}
	void Buffer_UniformUnMap(void)
	{
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}
	void Buffer_StorageUnMap(void)
	{
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}
	void Buffer_VertexBeginBarrier(void)
	{
		glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	}
	void Buffer_IndexBeginBarrier(void)
	{
		glMemoryBarrier(GL_ELEMENT_ARRAY_BARRIER_BIT);
	}
	void Buffer_UniformBeginBarrier(void)
	{
		glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
	}
	void Buffer_StorageBeginBarrier(void)
	{
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}
	void Buffer_EndBarrier(void)
	{
		glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
	}
	void Buffer_UniformMount(int unsigned Buffer, int unsigned Index)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, Index, Buffer);
	}
	void Buffer_StorageMount(int unsigned Buffer, int unsigned Index)
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Index, Buffer);
	}
	void Buffer_Free(int unsigned Buffer)
	{
		glDeleteBuffers(1, &Buffer);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBuffers -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Gizmo Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Batch_Alloc(Batch* Bat)
	{
		memset(Bat, 0, sizeof(Batch));

		Bat->NumWorldCircles = 1000;
		Bat->NumWorldLines = 1000;
		Bat->NumWorldRects = 1000;

		Bat->NumScreenCircles = 1000;
		Bat->NumScreenLines = 1000;
		Bat->NumScreenRects = 1000;

		static BatchWorldCircleVertex WorldCircleVertexBuffer[3] = { 0 };
		static int unsigned WorldCircleIndexBuffer[3] = { 0 };

		WorldCircleVertexBuffer[0].Position.X = -SQRT_3;
		WorldCircleVertexBuffer[0].Position.Y = -1.0F;
		WorldCircleVertexBuffer[0].TextureCoords.X = 0.0F;
		WorldCircleVertexBuffer[0].TextureCoords.Y = 0.0F;
		WorldCircleVertexBuffer[1].Position.X = SQRT_3;
		WorldCircleVertexBuffer[1].Position.Y = -1.0F;
		WorldCircleVertexBuffer[1].TextureCoords.X = 1.0F;
		WorldCircleVertexBuffer[1].TextureCoords.Y = 0.0F;
		WorldCircleVertexBuffer[2].Position.X = 0.0F;
		WorldCircleVertexBuffer[2].Position.Y = 2.0F;
		WorldCircleVertexBuffer[2].TextureCoords.X = 0.5F;
		WorldCircleVertexBuffer[2].TextureCoords.Y = 1.0F;

		WorldCircleIndexBuffer[0] = 0;
		WorldCircleIndexBuffer[1] = 1;
		WorldCircleIndexBuffer[2] = 2;

		static BatchScreenCircleVertex ScreenCircleVertexBuffer[3] = { 0 };
		static int unsigned ScreenCircleIndexBuffer[3] = { 0 };

		ScreenCircleVertexBuffer[0].Position.X = -SQRT_3;
		ScreenCircleVertexBuffer[0].Position.Y = -1.0F;
		ScreenCircleVertexBuffer[0].TextureCoords.X = 0.0F;
		ScreenCircleVertexBuffer[0].TextureCoords.Y = 0.0F;
		ScreenCircleVertexBuffer[1].Position.X = SQRT_3;
		ScreenCircleVertexBuffer[1].Position.Y = -1.0F;
		ScreenCircleVertexBuffer[1].TextureCoords.X = 1.0F;
		ScreenCircleVertexBuffer[1].TextureCoords.Y = 0.0F;
		ScreenCircleVertexBuffer[2].Position.X = 0.0F;
		ScreenCircleVertexBuffer[2].Position.Y = 2.0F;
		ScreenCircleVertexBuffer[2].TextureCoords.X = 0.5F;
		ScreenCircleVertexBuffer[2].TextureCoords.Y = 1.0F;

		ScreenCircleIndexBuffer[0] = 0;
		ScreenCircleIndexBuffer[1] = 1;
		ScreenCircleIndexBuffer[2] = 2;

		static BatchWorldRectVertex WorldRectVertexBuffer[4] = { 0 };
		static int unsigned WorldRectIndexBuffer[6] = { 0 };

		WorldRectVertexBuffer[0].Position.X = 0.0F;
		WorldRectVertexBuffer[0].Position.Y = 0.0F;
		WorldRectVertexBuffer[0].TextureCoords.X = 0.0F;
		WorldRectVertexBuffer[0].TextureCoords.Y = 0.0F;
		WorldRectVertexBuffer[1].Position.X = 1.0F;
		WorldRectVertexBuffer[1].Position.Y = 0.0F;
		WorldRectVertexBuffer[1].TextureCoords.X = 1.0F;
		WorldRectVertexBuffer[1].TextureCoords.Y = 0.0F;
		WorldRectVertexBuffer[2].Position.X = 0.0F;
		WorldRectVertexBuffer[2].Position.Y = 1.0F;
		WorldRectVertexBuffer[2].TextureCoords.X = 0.0F;
		WorldRectVertexBuffer[2].TextureCoords.Y = 1.0F;
		WorldRectVertexBuffer[3].Position.X = 1.0F;
		WorldRectVertexBuffer[3].Position.Y = 1.0F;
		WorldRectVertexBuffer[3].TextureCoords.X = 1.0F;
		WorldRectVertexBuffer[3].TextureCoords.Y = 1.0F;

		WorldRectIndexBuffer[0] = 0;
		WorldRectIndexBuffer[1] = 1;
		WorldRectIndexBuffer[2] = 2;
		WorldRectIndexBuffer[3] = 2;
		WorldRectIndexBuffer[4] = 3;
		WorldRectIndexBuffer[5] = 1;

		static BatchScreenRectVertex ScreenRectVertexBuffer[4] = { 0 };
		static int unsigned ScreenRectIndexBuffer[6] = { 0 };

		ScreenRectVertexBuffer[0].Position.X = 0.0F;
		ScreenRectVertexBuffer[0].Position.Y = 0.0F;
		ScreenRectVertexBuffer[0].TextureCoords.X = 0.0F;
		ScreenRectVertexBuffer[0].TextureCoords.Y = 0.0F;
		ScreenRectVertexBuffer[1].Position.X = 1.0F;
		ScreenRectVertexBuffer[1].Position.Y = 0.0F;
		ScreenRectVertexBuffer[1].TextureCoords.X = 1.0F;
		ScreenRectVertexBuffer[1].TextureCoords.Y = 0.0F;
		ScreenRectVertexBuffer[2].Position.X = 0.0F;
		ScreenRectVertexBuffer[2].Position.Y = 1.0F;
		ScreenRectVertexBuffer[2].TextureCoords.X = 0.0F;
		ScreenRectVertexBuffer[2].TextureCoords.Y = 1.0F;
		ScreenRectVertexBuffer[3].Position.X = 1.0F;
		ScreenRectVertexBuffer[3].Position.Y = 1.0F;
		ScreenRectVertexBuffer[3].TextureCoords.X = 1.0F;
		ScreenRectVertexBuffer[3].TextureCoords.Y = 1.0F;

		ScreenRectIndexBuffer[0] = 0;
		ScreenRectIndexBuffer[1] = 1;
		ScreenRectIndexBuffer[2] = 2;
		ScreenRectIndexBuffer[3] = 2;
		ScreenRectIndexBuffer[4] = 3;
		ScreenRectIndexBuffer[5] = 1;

		VertexArray_Alloc(&Bat->WorldCircleVertexArray);
		Buffer_VertexAlloc(&Bat->WorldCircleVertexBuffer);
		Buffer_VertexAlloc(&Bat->WorldCircleInstanceBuffer);
		Buffer_IndexAlloc(&Bat->WorldCircleIndexBuffer);

		VertexArray_Alloc(&Bat->ScreenCircleVertexArray);
		Buffer_VertexAlloc(&Bat->ScreenCircleVertexBuffer);
		Buffer_VertexAlloc(&Bat->ScreenCircleInstanceBuffer);
		Buffer_IndexAlloc(&Bat->ScreenCircleIndexBuffer);

		VertexArray_Alloc(&Bat->WorldLineVertexArray);
		Buffer_VertexAlloc(&Bat->WorldLineVertexBuffer);
		Buffer_IndexAlloc(&Bat->WorldLineIndexBuffer);

		VertexArray_Alloc(&Bat->ScreenLineVertexArray);
		Buffer_VertexAlloc(&Bat->ScreenLineVertexBuffer);
		Buffer_IndexAlloc(&Bat->ScreenLineIndexBuffer);

		VertexArray_Alloc(&Bat->WorldRectVertexArray);
		Buffer_VertexAlloc(&Bat->WorldRectVertexBuffer);
		Buffer_VertexAlloc(&Bat->WorldRectInstanceBuffer);
		Buffer_IndexAlloc(&Bat->WorldRectIndexBuffer);

		VertexArray_Alloc(&Bat->ScreenRectVertexArray);
		Buffer_VertexAlloc(&Bat->ScreenRectVertexBuffer);
		Buffer_VertexAlloc(&Bat->ScreenRectInstanceBuffer);
		Buffer_IndexAlloc(&Bat->ScreenRectIndexBuffer);

		VertexArray_Bind(Bat->WorldCircleVertexArray);
		Buffer_VertexBind(Bat->WorldCircleVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(BatchWorldCircleVertex), OFFSET_OF(BatchWorldCircleVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(BatchWorldCircleVertex), OFFSET_OF(BatchWorldCircleVertex, TextureCoords));
		Buffer_VertexResize(3 * sizeof(BatchWorldCircleVertex), WorldCircleVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Bat->WorldCircleInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexAttribPointerReal32(2, 3, sizeof(BatchWorldCircleInstanceEntry), OFFSET_OF(BatchWorldCircleInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(3, 3, sizeof(BatchWorldCircleInstanceEntry), OFFSET_OF(BatchWorldCircleInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(4, 1, sizeof(BatchWorldCircleInstanceEntry), OFFSET_OF(BatchWorldCircleInstanceEntry, Radius));
		Buffer_VertexAttribPointerReal32(5, 4, sizeof(BatchWorldCircleInstanceEntry), OFFSET_OF(BatchWorldCircleInstanceEntry, Color));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexResize(Bat->NumWorldCircles * sizeof(BatchWorldCircleInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Bat->WorldCircleIndexBuffer);
		Buffer_IndexResize(3 * sizeof(int unsigned), WorldCircleIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

		VertexArray_Bind(Bat->ScreenCircleVertexArray);
		Buffer_VertexBind(Bat->ScreenCircleVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(BatchScreenCircleVertex), OFFSET_OF(BatchScreenCircleVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(BatchScreenCircleVertex), OFFSET_OF(BatchScreenCircleVertex, TextureCoords));
		Buffer_VertexResize(3 * sizeof(BatchScreenCircleVertex), ScreenCircleVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Bat->ScreenCircleInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexAttribPointerReal32(2, 2, sizeof(BatchScreenCircleInstanceEntry), OFFSET_OF(BatchScreenCircleInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(3, 1, sizeof(BatchScreenCircleInstanceEntry), OFFSET_OF(BatchScreenCircleInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(4, 1, sizeof(BatchScreenCircleInstanceEntry), OFFSET_OF(BatchScreenCircleInstanceEntry, Radius));
		Buffer_VertexAttribPointerReal32(5, 4, sizeof(BatchScreenCircleInstanceEntry), OFFSET_OF(BatchScreenCircleInstanceEntry, Color));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexResize(Bat->NumScreenCircles * sizeof(BatchScreenCircleInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Bat->ScreenCircleIndexBuffer);
		Buffer_IndexResize(3 * sizeof(int unsigned), ScreenCircleIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

		VertexArray_Bind(Bat->WorldLineVertexArray);
		Buffer_VertexBind(Bat->WorldLineVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexAttribPointerReal32(0, 3, sizeof(BatchWorldLineVertex), OFFSET_OF(BatchWorldLineVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 3, sizeof(BatchWorldLineVertex), OFFSET_OF(BatchWorldLineVertex, Rotation));
		Buffer_VertexAttribPointerReal32(2, 1, sizeof(BatchWorldLineVertex), OFFSET_OF(BatchWorldLineVertex, Thickness));
		Buffer_VertexAttribPointerReal32(3, 4, sizeof(BatchWorldLineVertex), OFFSET_OF(BatchWorldLineVertex, Color));
		Buffer_VertexResize(Bat->NumWorldLines * 2 * sizeof(BatchWorldLineVertex), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Bat->WorldLineIndexBuffer);
		Buffer_IndexResize(Bat->NumWorldLines * 2 * sizeof(int unsigned), 0, GL_DYNAMIC_DRAW);
		VertexArray_UnBind();

		VertexArray_Bind(Bat->ScreenLineVertexArray);
		Buffer_VertexBind(Bat->ScreenLineVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(BatchScreenLineVertex), OFFSET_OF(BatchScreenLineVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 1, sizeof(BatchScreenLineVertex), OFFSET_OF(BatchScreenLineVertex, Rotation));
		Buffer_VertexAttribPointerReal32(2, 1, sizeof(BatchScreenLineVertex), OFFSET_OF(BatchScreenLineVertex, Thickness));
		Buffer_VertexAttribPointerReal32(3, 4, sizeof(BatchScreenLineVertex), OFFSET_OF(BatchScreenLineVertex, Color));
		Buffer_VertexResize(Bat->NumScreenLines * 2 * sizeof(BatchScreenLineVertex), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Bat->ScreenLineIndexBuffer);
		Buffer_IndexResize(Bat->NumScreenLines * 2 * sizeof(int unsigned), 0, GL_DYNAMIC_DRAW);
		VertexArray_UnBind();

		VertexArray_Bind(Bat->WorldRectVertexArray);
		Buffer_VertexBind(Bat->WorldRectVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(BatchWorldRectVertex), OFFSET_OF(BatchWorldRectVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(BatchWorldRectVertex), OFFSET_OF(BatchWorldRectVertex, TextureCoords));
		Buffer_VertexResize(4 * sizeof(BatchWorldRectVertex), WorldRectVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Bat->WorldRectInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexAttribPointerReal32(2, 3, sizeof(BatchWorldRectInstanceEntry), OFFSET_OF(BatchWorldRectInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(3, 3, sizeof(BatchWorldRectInstanceEntry), OFFSET_OF(BatchWorldRectInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(4, 2, sizeof(BatchWorldRectInstanceEntry), OFFSET_OF(BatchWorldRectInstanceEntry, Size));
		Buffer_VertexAttribPointerReal32(5, 4, sizeof(BatchWorldRectInstanceEntry), OFFSET_OF(BatchWorldRectInstanceEntry, Color));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexResize(Bat->NumWorldRects * sizeof(BatchWorldRectInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Bat->WorldRectIndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), WorldRectIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

		VertexArray_Bind(Bat->ScreenRectVertexArray);
		Buffer_VertexBind(Bat->ScreenRectVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(BatchScreenRectVertex), OFFSET_OF(BatchScreenRectVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(BatchScreenRectVertex), OFFSET_OF(BatchScreenRectVertex, TextureCoords));
		Buffer_VertexResize(4 * sizeof(BatchScreenRectVertex), ScreenRectVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Bat->ScreenRectInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexAttribPointerReal32(2, 2, sizeof(BatchScreenRectInstanceEntry), OFFSET_OF(BatchScreenRectInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(3, 1, sizeof(BatchScreenRectInstanceEntry), OFFSET_OF(BatchScreenRectInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(4, 2, sizeof(BatchScreenRectInstanceEntry), OFFSET_OF(BatchScreenRectInstanceEntry, Size));
		Buffer_VertexAttribPointerReal32(5, 4, sizeof(BatchScreenRectInstanceEntry), OFFSET_OF(BatchScreenRectInstanceEntry, Color));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexResize(Bat->NumScreenRects * sizeof(BatchScreenRectInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Bat->ScreenRectIndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), ScreenRectIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBatches += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Batch_Free(Batch* Bat)
	{
		VertexArray_Free(Bat->WorldCircleVertexArray);
		Buffer_Free(Bat->WorldCircleVertexBuffer);
		Buffer_Free(Bat->WorldCircleInstanceBuffer);
		Buffer_Free(Bat->WorldCircleIndexBuffer);

		VertexArray_Free(Bat->ScreenCircleVertexArray);
		Buffer_Free(Bat->ScreenCircleVertexBuffer);
		Buffer_Free(Bat->ScreenCircleInstanceBuffer);
		Buffer_Free(Bat->ScreenCircleIndexBuffer);

		VertexArray_Free(Bat->WorldLineVertexArray);
		Buffer_Free(Bat->WorldLineVertexBuffer);
		Buffer_Free(Bat->WorldLineIndexBuffer);

		VertexArray_Free(Bat->ScreenLineVertexArray);
		Buffer_Free(Bat->ScreenLineVertexBuffer);
		Buffer_Free(Bat->ScreenLineIndexBuffer);

		VertexArray_Free(Bat->WorldRectVertexArray);
		Buffer_Free(Bat->WorldRectVertexBuffer);
		Buffer_Free(Bat->WorldRectInstanceBuffer);
		Buffer_Free(Bat->WorldRectIndexBuffer);

		VertexArray_Free(Bat->ScreenRectVertexArray);
		Buffer_Free(Bat->ScreenRectVertexBuffer);
		Buffer_Free(Bat->ScreenRectInstanceBuffer);
		Buffer_Free(Bat->ScreenRectIndexBuffer);

		memset(Bat, 0, sizeof(Batch));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBatches -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Batch_BeginWorldCircles(Batch* Bat)
	{
		sCurrBatch = Bat;

		Buffer_VertexBind(sCurrBatch->WorldCircleInstanceBuffer);
		sCurrBatch->WorldCircleInstanceOffset = 0;

		sMappedWorldCircleInstanceBuffer = (BatchWorldCircleInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Batch_DrawWorldCircle(Vector3 const* Position, Vector3 const* Rotation, float Radius, Color4 const* Color)
	{
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.X = Position->X;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Y = Position->Y;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Z = Position->Z;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.X = Rotation->X;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Y = Rotation->Y;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Z = Rotation->Z;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Radius = Radius;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.R = Color->R;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.G = Color->G;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.B = Color->B;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.A = Color->A;

		sCurrBatch->WorldCircleInstanceOffset += 1;
	}
	void Batch_DrawWorldCircleSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float Radius, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.X = PositionX;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Y = PositionY;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Z = PositionZ;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.X = Pitch;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Y = Yaw;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Z = Roll;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Radius = Radius;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.R = ColorR;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.G = ColorG;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.B = ColorB;
		sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.A = ColorA;

		sCurrBatch->WorldCircleInstanceOffset += 1;
	}
	void Batch_DrawWorldCircleGrid(Vector3 const* Position, Vector3 const* Rotation, int unsigned Num, float Scale, float Radius, Color4 const* Color)
	{
		float SizeStep = ((float)Num * Scale) / (float)Num;

		for (int unsigned X = 0; X <= Num; X++)
		{
			for (int unsigned Y = 0; Y <= Num; Y++)
			{
				float StepX = (float)X * SizeStep;
				float StepY = (float)Y * SizeStep;

				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.X = Position->X + StepX;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Y = Position->Y + StepY;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Z = Position->Z;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.X = Rotation->X;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Y = Rotation->Y;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Z = Rotation->Z;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Radius = Radius;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.R = Color->R;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.G = Color->G;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.B = Color->B;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.A = Color->A;

				sCurrBatch->WorldCircleInstanceOffset += 1;
			}
		}
	}
	void Batch_DrawWorldCircleGridSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, int unsigned Num, float Scale, float Radius, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		float SizeStep = ((float)Num * Scale) / (float)Num;

		for (int unsigned X = 0; X <= Num; X++)
		{
			for (int unsigned Y = 0; Y <= Num; Y++)
			{
				float StepX = (float)X * SizeStep;
				float StepY = (float)Y * SizeStep;

				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.X = PositionX + StepX;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Y = PositionY + StepY;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Position.Z = PositionZ;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.X = Pitch;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Y = Yaw;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Rotation.Z = Roll;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Radius = Radius;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.R = ColorR;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.G = ColorG;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.B = ColorB;
				sMappedWorldCircleInstanceBuffer[sCurrBatch->WorldCircleInstanceOffset].Color.A = ColorA;

				sCurrBatch->WorldCircleInstanceOffset += 1;
			}
		}
	}
	void Batch_EndWorldCircles(Matrix4x4 const* Projection, Matrix4x4 const* View)
	{
		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
		Shader_Bind(sWorldCircleProgram);
		Shader_SetUniformMatrix4(sWorldCircleProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sWorldCircleProgram, "ViewMatrix", View);
		VertexArray_Bind(sCurrBatch->WorldCircleVertexArray);
		VertexArray_DrawTriangleStripInstanced(3, sCurrBatch->WorldCircleInstanceOffset);
		VertexArray_UnBind();

		sCurrBatch = 0;
		sMappedWorldCircleInstanceBuffer = 0;
	}
	void Batch_BeginScreenCircles(Batch* Bat)
	{
		sCurrBatch = Bat;

		Buffer_VertexBind(sCurrBatch->ScreenCircleInstanceBuffer);
		sCurrBatch->ScreenCircleInstanceOffset = 0;

		sMappedScreenCircleInstanceBuffer = (BatchScreenCircleInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Batch_DrawScreenCircle(Vector3 const* Position, float Rotation, float Radius, Color4 const* Color)
	{
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.X = Position->X;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Y = Position->Y;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Z = Position->Z;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Rotation = Rotation;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Radius = Radius;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.R = Color->R;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.G = Color->G;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.B = Color->B;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.A = Color->A;

		sCurrBatch->ScreenCircleInstanceOffset += 1;
	}
	void Batch_DrawScreenCircleSimple(float PositionX, float PositionY, float PositionZ, float Rotation, float Radius, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.X = PositionX;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Y = PositionY;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Z = PositionZ;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Rotation = Rotation;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Radius = Radius;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.R = ColorR;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.G = ColorG;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.B = ColorB;
		sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.A = ColorA;

		sCurrBatch->ScreenCircleInstanceOffset += 1;
	}
	void Batch_DrawScreenCircleGrid(Vector3 const* Position, float Rotation, int unsigned Num, float Scale, float Radius, Color4 const* Color)
	{
		float SizeStep = ((float)Num * Scale) / (float)Num;

		for (int unsigned X = 0; X <= Num; X++)
		{
			for (int unsigned Y = 0; Y <= Num; Y++)
			{
				float StepX = (float)X * SizeStep;
				float StepY = (float)Y * SizeStep;

				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.X = Position->X + StepX;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Y = Position->Y + StepY;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Z = Position->Z;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Rotation = Rotation;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Radius = Radius;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.R = Color->R;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.G = Color->G;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.B = Color->B;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.A = Color->A;

				sCurrBatch->ScreenCircleInstanceOffset += 1;
			}
		}
	}
	void Batch_DrawScreenCircleGridSimple(float PositionX, float PositionY, float PositionZ, float Rotation, int unsigned Num, float Scale, float Radius, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		float SizeStep = ((float)Num * Scale) / (float)Num;

		for (int unsigned X = 0; X <= Num; X++)
		{
			for (int unsigned Y = 0; Y <= Num; Y++)
			{
				float StepX = (float)X * SizeStep;
				float StepY = (float)Y * SizeStep;

				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.X = PositionX + StepX;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Y = PositionY + StepY;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Position.Z = PositionZ;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Rotation = Rotation;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Radius = Radius;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.R = ColorR;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.G = ColorG;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.B = ColorB;
				sMappedScreenCircleInstanceBuffer[sCurrBatch->ScreenCircleInstanceOffset].Color.A = ColorA;

				sCurrBatch->ScreenCircleInstanceOffset += 1;
			}
		}
	}
	void Batch_EndScreenCircles(void)
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };

		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
		Shader_Bind(sScreenCircleProgram);
		Shader_SetUniformVector2(sScreenCircleProgram, "ScreenSize", &ScreenSize);
		VertexArray_Bind(sCurrBatch->ScreenCircleVertexArray);
		VertexArray_DrawTriangleStripInstanced(3, sCurrBatch->ScreenCircleInstanceOffset);
		VertexArray_UnBind();

		sCurrBatch = 0;
		sMappedScreenCircleInstanceBuffer = 0;
	}
	void Batch_BeginWorldLines(Batch* Bat)
	{
		sCurrBatch = Bat;

		Buffer_VertexBind(sCurrBatch->WorldLineVertexBuffer);
		Buffer_IndexBind(sCurrBatch->WorldLineIndexBuffer);
		sCurrBatch->WorldLineVertexOffset = 0;
		sCurrBatch->WorldLineIndexOffset = 0;

		sMappedWorldLineVertexBuffer = (BatchWorldLineVertex*)Buffer_VertexMap(GL_WRITE_ONLY);
		sMappedWorldLineIndexBuffer = (int unsigned*)Buffer_IndexMap(GL_WRITE_ONLY);
	}
	void Batch_DrawWorldLine(Vector3 const* From, Vector3 const* To, Vector3 const* Rotation, float Thickness, Color4 const* Color)
	{
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Position.X = From->X;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Position.Y = From->Y;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Position.Z = From->Z;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Rotation.X = Rotation->X;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Rotation.Y = Rotation->Y;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Rotation.Z = Rotation->Z;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Thickness = Thickness;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.R = Color->R;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.G = Color->G;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.B = Color->B;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.A = Color->A;

		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Position.X = To->X;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Position.Y = To->Y;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Position.Z = To->Z;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Rotation.X = Rotation->X;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Rotation.Y = Rotation->Y;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Rotation.Z = Rotation->Z;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Thickness = Thickness;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.R = Color->R;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.G = Color->G;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.B = Color->B;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.A = Color->A;

		sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset] = sCurrBatch->WorldLineVertexOffset;
		sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + 1] = sCurrBatch->WorldLineVertexOffset + 1;

		sCurrBatch->WorldLineVertexOffset += 2;
		sCurrBatch->WorldLineIndexOffset += 2;
	}
	void Batch_DrawWorldLineSimple(float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Pitch, float Yaw, float Roll, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Position.X = FromX;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Position.Y = FromY;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Position.Z = FromZ;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Rotation.X = Pitch;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Rotation.Y = Yaw;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Rotation.Z = Roll;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Thickness = Thickness;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.R = ColorR;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.G = ColorG;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.B = ColorB;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset].Color.A = ColorA;

		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Position.X = ToX;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Position.Y = ToY;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Position.Z = ToZ;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Rotation.X = Pitch;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Rotation.Y = Yaw;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Rotation.Z = Roll;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Thickness = Thickness;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.R = ColorR;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.G = ColorG;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.B = ColorB;
		sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + 1].Color.A = ColorA;

		sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset] = sCurrBatch->WorldLineVertexOffset;
		sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + 1] = sCurrBatch->WorldLineVertexOffset + 1;

		sCurrBatch->WorldLineVertexOffset += 2;
		sCurrBatch->WorldLineIndexOffset += 2;
	}
	void Batch_DrawWorldLineGrid(Vector3 const* Position, Vector3 const* Rotation, int unsigned Num, float Scale, float Thickness, Color4 const* Color)
	{
		int unsigned Num4 = Num * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)Num * Scale) / (float)Num;
		float Size = (float)Num * Scale;

		for (int unsigned I = 0; I <= Num; I++)
		{
			float Step = (float)I * SizeStep;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Position.X = Position->X + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Position.Y = Position->Y;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Position.Z = Position->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Rotation.X = Rotation->X;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Rotation.Y = Rotation->Y;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Rotation.Z = Rotation->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.R = Color->R;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.G = Color->G;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.B = Color->B;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.A = Color->A;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Position.X = Position->X + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Position.Y = Position->Y + Size;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Position.Z = Position->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Rotation.X = Rotation->X;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Rotation.Y = Rotation->Y;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Rotation.Z = Rotation->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.R = Color->R;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.G = Color->G;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.B = Color->B;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.A = Color->A;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Position.X = Position->X;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Position.Y = Position->Y + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Position.Z = Position->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Rotation.X = Rotation->X;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Rotation.Y = Rotation->Y;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Rotation.Z = Rotation->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.R = Color->R;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.G = Color->G;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.B = Color->B;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.A = Color->A;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Position.X = Position->X + Size;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Position.Y = Position->Y + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Position.Z = Position->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Rotation.X = Rotation->X;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Rotation.Y = Rotation->Y;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Rotation.Z = Rotation->Z;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.R = Color->R;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.G = Color->G;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.B = Color->B;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.A = Color->A;

			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex] = sCurrBatch->WorldLineVertexOffset + SegmentIndex;
			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex + 1] = sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1;
			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex + 2] = sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2;
			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex + 3] = sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		sCurrBatch->WorldLineVertexOffset += Num4 + 4;
		sCurrBatch->WorldLineIndexOffset += Num4 + 4;
	}
	void Batch_DrawWorldLineGridSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, int unsigned Num, float Scale, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		int unsigned Num4 = Num * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)Num * Scale) / (float)Num;
		float Size = (float)Num * Scale;

		for (int unsigned I = 0; I <= Num; I++)
		{
			float Step = (float)I * SizeStep;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Position.X = PositionX + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Position.Y = PositionY;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Position.Z = PositionZ;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Rotation.X = Pitch;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Rotation.Y = Yaw;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Rotation.Z = Roll;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.R = ColorR;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.G = ColorG;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.B = ColorB;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex].Color.A = ColorA;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Position.X = PositionX + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Position.Y = PositionY + Size;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Position.Z = PositionZ;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Rotation.X = Pitch;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Rotation.Y = Yaw;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Rotation.Z = Roll;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.R = ColorR;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.G = ColorG;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.B = ColorB;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1].Color.A = ColorA;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Position.X = PositionX;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Position.Y = PositionY + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Position.Z = PositionZ;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Rotation.X = Pitch;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Rotation.Y = Yaw;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Rotation.Z = Roll;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.R = ColorR;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.G = ColorG;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.B = ColorB;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2].Color.A = ColorA;

			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Position.X = PositionX + Size;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Position.Y = PositionY + Step;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Position.Z = PositionZ;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Rotation.X = Pitch;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Rotation.Y = Yaw;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Rotation.Z = Roll;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Thickness = Thickness;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.R = ColorR;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.G = ColorG;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.B = ColorB;
			sMappedWorldLineVertexBuffer[sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3].Color.A = ColorA;

			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex] = sCurrBatch->WorldLineVertexOffset + SegmentIndex;
			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex + 1] = sCurrBatch->WorldLineVertexOffset + SegmentIndex + 1;
			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex + 2] = sCurrBatch->WorldLineVertexOffset + SegmentIndex + 2;
			sMappedWorldLineIndexBuffer[sCurrBatch->WorldLineIndexOffset + SegmentIndex + 3] = sCurrBatch->WorldLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		sCurrBatch->WorldLineVertexOffset += Num4 + 4;
		sCurrBatch->WorldLineIndexOffset += Num4 + 4;
	}
	void Batch_EndWorldLines(Matrix4x4 const* Projection, Matrix4x4 const* View)
	{
		Buffer_VertexUnMap();
		Buffer_IndexUnMap();
		Buffer_VertexUnBind();
		Buffer_IndexUnBind();
		Shader_Bind(sWorldLineProgram);
		Shader_SetUniformMatrix4(sWorldLineProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sWorldLineProgram, "ViewMatrix", View);
		VertexArray_Bind(sCurrBatch->WorldLineVertexArray);
		VertexArray_DrawLines(sCurrBatch->WorldLineIndexOffset);
		VertexArray_UnBind();

		sCurrBatch = 0;
		sMappedWorldLineVertexBuffer = 0;
		sMappedWorldLineIndexBuffer = 0;
	}
	void Batch_BeginScreenLines(Batch* Bat)
	{
		sCurrBatch = Bat;

		Buffer_VertexBind(sCurrBatch->ScreenLineVertexBuffer);
		Buffer_IndexBind(sCurrBatch->ScreenLineIndexBuffer);
		sCurrBatch->ScreenLineVertexOffset = 0;
		sCurrBatch->ScreenLineIndexOffset = 0;

		sMappedScreenLineVertexBuffer = (BatchScreenLineVertex*)Buffer_VertexMap(GL_WRITE_ONLY);
		sMappedScreenLineIndexBuffer = (int unsigned*)Buffer_IndexMap(GL_WRITE_ONLY);
	}
	void Batch_DrawScreenLine(Vector3 const* From, Vector3 const* To, float Rotation, float Thickness, Color4 const* Color)
	{
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Position.X = From->X;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Position.Y = From->Y;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Position.Z = From->Z;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Rotation = Rotation;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Thickness = Thickness;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.R = Color->R;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.G = Color->G;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.B = Color->B;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.A = Color->A;

		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Position.X = To->X;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Position.Y = To->Y;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Position.Z = To->Z;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Rotation = Rotation;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Thickness = Thickness;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.R = Color->R;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.G = Color->G;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.B = Color->B;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.A = Color->A;

		sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset] = sCurrBatch->ScreenLineVertexOffset;
		sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + 1] = sCurrBatch->ScreenLineVertexOffset + 1;

		sCurrBatch->ScreenLineVertexOffset += 2;
		sCurrBatch->ScreenLineIndexOffset += 2;
	}
	void Batch_DrawScreenLineSimple(float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Rotation, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Position.X = FromX;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Position.Y = FromY;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Position.Z = FromZ;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Rotation = Rotation;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Thickness = Thickness;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.R = ColorR;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.G = ColorG;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.B = ColorB;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset].Color.A = ColorA;

		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Position.X = ToX;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Position.Y = ToY;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Position.Z = ToZ;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Rotation = Rotation;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Thickness = Thickness;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.R = ColorR;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.G = ColorG;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.B = ColorB;
		sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + 1].Color.A = ColorA;

		sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset] = sCurrBatch->ScreenLineVertexOffset;
		sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + 1] = sCurrBatch->ScreenLineVertexOffset + 1;

		sCurrBatch->ScreenLineVertexOffset += 2;
		sCurrBatch->ScreenLineIndexOffset += 2;
	}
	void Batch_DrawScreenLineGrid(Vector3 const* Position, float Rotation, int unsigned Num, float Scale, float Thickness, Color4 const* Color)
	{
		int unsigned Num4 = Num * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)Num * Scale) / (float)Num;
		float Size = (float)Num * Scale;

		for (int unsigned I = 0; I <= Num; I++)
		{
			float Step = (float)I * SizeStep;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Position.X = Position->X + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Position.Y = Position->Y;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Position.Z = Position->Z;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.R = Color->R;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.G = Color->G;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.B = Color->B;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.A = Color->A;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Position.X = Position->X + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Position.Y = Position->Y + Size;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Position.Z = Position->Z;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.R = Color->R;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.G = Color->G;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.B = Color->B;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.A = Color->A;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Position.X = Position->X;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Position.Y = Position->Y + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Position.Z = Position->Z;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.R = Color->R;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.G = Color->G;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.B = Color->B;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.A = Color->A;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Position.X = Position->X + Size;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Position.Y = Position->Y + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Position.Z = Position->Z;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.R = Color->R;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.G = Color->G;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.B = Color->B;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.A = Color->A;

			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex;
			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex + 1] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1;
			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex + 2] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2;
			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex + 3] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		sCurrBatch->ScreenLineVertexOffset += Num4 + 4;
		sCurrBatch->ScreenLineIndexOffset += Num4 + 4;
	}
	void Batch_DrawScreenLineGridSimple(float PositionX, float PositionY, float PositionZ, float Rotation, int unsigned Num, float Scale, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		int unsigned Num4 = Num * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)Num * Scale) / (float)Num;
		float Size = (float)Num * Scale;

		for (int unsigned I = 0; I <= Num; I++)
		{
			float Step = (float)I * SizeStep;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Position.X = PositionX + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Position.Y = PositionY;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Position.Z = PositionZ;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.R = ColorR;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.G = ColorG;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.B = ColorB;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex].Color.A = ColorA;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Position.X = PositionX + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Position.Y = PositionY + Size;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Position.Z = PositionZ;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.R = ColorR;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.G = ColorG;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.B = ColorB;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1].Color.A = ColorA;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Position.X = PositionX;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Position.Y = PositionY + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Position.Z = PositionZ;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.R = ColorR;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.G = ColorG;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.B = ColorB;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2].Color.A = ColorA;

			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Position.X = PositionX + Size;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Position.Y = PositionY + Step;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Position.Z = PositionZ;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Rotation = Rotation;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Thickness = Thickness;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.R = ColorR;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.G = ColorG;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.B = ColorB;
			sMappedScreenLineVertexBuffer[sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3].Color.A = ColorA;

			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex;
			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex + 1] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 1;
			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex + 2] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 2;
			sMappedScreenLineIndexBuffer[sCurrBatch->ScreenLineIndexOffset + SegmentIndex + 3] = sCurrBatch->ScreenLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		sCurrBatch->ScreenLineVertexOffset += Num4 + 4;
		sCurrBatch->ScreenLineIndexOffset += Num4 + 4;
	}
	void Batch_EndScreenLines(void)
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };

		Buffer_VertexUnMap();
		Buffer_IndexUnMap();
		Buffer_VertexUnBind();
		Buffer_IndexUnBind();
		Shader_Bind(sScreenLineProgram);
		Shader_SetUniformVector2(sScreenLineProgram, "ScreenSize", &ScreenSize);
		VertexArray_Bind(sCurrBatch->ScreenLineVertexArray);
		VertexArray_DrawLines(sCurrBatch->ScreenLineIndexOffset);
		VertexArray_UnBind();

		sCurrBatch = 0;
		sMappedScreenLineVertexBuffer = 0;
		sMappedScreenLineIndexBuffer = 0;
	}
	void Batch_BeginWorldRects(Batch* Bat)
	{
		sCurrBatch = Bat;

		Buffer_VertexBind(sCurrBatch->WorldRectInstanceBuffer);
		sCurrBatch->WorldRectInstanceOffset = 0;

		sMappedWorldRectInstanceBuffer = (BatchWorldRectInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Batch_DrawWorldRect(Vector3 const* Position, Vector3 const* Rotation, Vector2 const* Size, Color4 const* Color)
	{
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Position.X = Position->X;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Position.Y = Position->Y;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Position.Z = Position->Z;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Rotation.X = Rotation->X;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Rotation.Y = Rotation->Y;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Rotation.Z = Rotation->Z;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Size.X = Size->X;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Size.Y = Size->Y;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.R = Color->R;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.G = Color->G;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.B = Color->B;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.A = Color->A;

		sCurrBatch->WorldRectInstanceOffset += 1;
	}
	void Batch_DrawWorldRectSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Position.X = PositionX;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Position.Y = PositionY;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Position.Z = PositionZ;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Rotation.X = Pitch;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Rotation.Y = Yaw;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Rotation.Z = Roll;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Size.X = SizeX;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Size.Y = SizeY;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.R = ColorR;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.G = ColorG;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.B = ColorB;
		sMappedWorldRectInstanceBuffer[sCurrBatch->WorldRectInstanceOffset].Color.A = ColorA;

		sCurrBatch->WorldRectInstanceOffset += 1;
	}
	void Batch_EndWorldRects(Matrix4x4 const* Projection, Matrix4x4 const* View)
	{
		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
		Shader_Bind(sWorldRectProgram);
		Shader_SetUniformMatrix4(sWorldRectProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sWorldRectProgram, "ViewMatrix", View);
		VertexArray_Bind(sCurrBatch->WorldRectVertexArray);
		VertexArray_DrawTriangleStripInstanced(4, sCurrBatch->WorldRectInstanceOffset);
		VertexArray_UnBind();

		sCurrBatch = 0;
		sMappedWorldRectInstanceBuffer = 0;
	}
	void Batch_BeginScreenRects(Batch* Bat)
	{
		sCurrBatch = Bat;

		Buffer_VertexBind(sCurrBatch->ScreenRectInstanceBuffer);
		sCurrBatch->ScreenRectInstanceOffset = 0;

		sMappedScreenRectInstanceBuffer = (BatchScreenRectInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Batch_DrawScreenRect(Vector3 const* Position, float Rotation, Vector2 const* Size, Color4 const* Color)
	{
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Position.X = Position->X;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Position.Y = Position->Y;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Position.Z = Position->Z;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Rotation = Rotation;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Size.X = Size->X;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Size.Y = Size->Y;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.R = Color->R;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.G = Color->G;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.B = Color->B;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.A = Color->A;

		sCurrBatch->ScreenRectInstanceOffset += 1;
	}
	void Batch_DrawScreenRectSimple(float PositionX, float PositionY, float PositionZ, float Rotation, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Position.X = PositionX;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Position.Y = PositionY;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Position.Z = PositionZ;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Rotation = Rotation;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Size.X = SizeX;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Size.Y = SizeY;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.R = ColorR;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.G = ColorG;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.B = ColorB;
		sMappedScreenRectInstanceBuffer[sCurrBatch->ScreenRectInstanceOffset].Color.A = ColorA;

		sCurrBatch->ScreenRectInstanceOffset += 1;
	}
	void Batch_EndScreenRects()
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };

		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
		Shader_Bind(sScreenRectProgram);
		Shader_SetUniformVector2(sScreenRectProgram, "ScreenSize", &ScreenSize);
		VertexArray_Bind(sCurrBatch->ScreenRectVertexArray);
		VertexArray_DrawTriangleStripInstanced(4, sCurrBatch->ScreenRectInstanceOffset);
		VertexArray_UnBind();

		sCurrBatch = 0;
		sMappedScreenRectInstanceBuffer = 0;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Font Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Font_AllocFromFile(Font* Fnt, int unsigned NumChars, char const* FilePath)
	{
		char unsigned* Buffer = 0;
		int unsigned BufferSize = 0;
		FileSystem_ReadBinary(&Buffer, &BufferSize, FilePath);
		Font_AllocInternal(Fnt, NumChars, Buffer, BufferSize);
		Memory_Free(Buffer);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedFonts += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Font_AllocFromMemory(Font* Fnt, int unsigned NumChars, char unsigned* Buffer, int unsigned BufferSize)
	{
		Font_AllocInternal(Fnt, NumChars, Buffer, BufferSize);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedFonts += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	FontGlyph* Font_GlyphByGlyphIndex(Font* Fnt, short unsigned GlyphIndex)
	{
		return &Fnt->Glyphs[GlyphIndex];
	}
	FontGlyph* Font_GlyphByUnicode(Font* Fnt, int unsigned Unicode)
	{
		return *(FontGlyph**)HashMap_At(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned));
	}
	float Font_LineHeight(Font* Fnt)
	{
		return (float)Fnt->LineHeight / (float)Fnt->HeadTable.UnitsPerEm;
	}
	short unsigned Font_NumGlyphs(Font* Fnt)
	{
		return Fnt->MaxpTable.NumGlyphs;
	}
	void Font_Free(Font* Fnt)
	{
		for (short unsigned GlyphIndex = 0; GlyphIndex < Fnt->MaxpTable.NumGlyphs; GlyphIndex++)
		{
			if (Fnt->Glyphs[GlyphIndex].ContourEndIndices) Memory_Free(Fnt->Glyphs[GlyphIndex].ContourEndIndices);
			if (Fnt->Glyphs[GlyphIndex].Points) Memory_Free(Fnt->Glyphs[GlyphIndex].Points);
			if (Fnt->Glyphs[GlyphIndex].Flags) Memory_Free(Fnt->Glyphs[GlyphIndex].Flags);
			if (Fnt->Glyphs[GlyphIndex].Instructions) Memory_Free(Fnt->Glyphs[GlyphIndex].Instructions);

			Vector_Free(&Fnt->Glyphs[GlyphIndex].PointOffsets);
			Vector_Free(&Fnt->Glyphs[GlyphIndex].BezierPoints);
			Vector_Free(&Fnt->Glyphs[GlyphIndex].BezierOffsets);
			Vector_Free(&Fnt->Glyphs[GlyphIndex].BezierCurves);
		}

		HashMap_Free(&Fnt->GlyphMapping);
		Vector_Free(&Fnt->BezierOffsets);
		Vector_Free(&Fnt->BezierCurves);

		VertexArray_Free(Fnt->WorldGlyphVertexArray);
		Buffer_Free(Fnt->WorldGlyphVertexBuffer);
		Buffer_Free(Fnt->WorldGlyphInstanceBuffer);
		Buffer_Free(Fnt->WorldGlyphIndexBuffer);

		VertexArray_Free(Fnt->ScreenGlyphVertexArray);
		Buffer_Free(Fnt->ScreenGlyphVertexBuffer);
		Buffer_Free(Fnt->ScreenGlyphInstanceBuffer);
		Buffer_Free(Fnt->ScreenGlyphIndexBuffer);

		Buffer_Free(Fnt->BezierOffsetBuffer);
		Buffer_Free(Fnt->BezierCurveBuffer);

		Memory_Free(Fnt->GlyphOffsets);
		Memory_Free(Fnt->Glyphs);

		memset(Fnt, 0, sizeof(Font));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedFonts -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	Font* Font_GetDefault(void)
	{
		return &sDefaultFont;
	}
	void Font_AllocInternal(Font* Fnt, int unsigned NumChars, char unsigned* Buffer, int unsigned BufferSize)
	{
		memset(Fnt, 0, sizeof(Font));

		FileReader Reader = { 0 };

		FileReader_Alloc(&Reader, Buffer, BufferSize);

		Fnt->OffsetTable.ScalerType = FileReader_ReadUInt32(&Reader, true);
		Fnt->OffsetTable.NumTables = FileReader_ReadUInt16(&Reader, true);
		Fnt->OffsetTable.SearchRange = FileReader_ReadUInt16(&Reader, true);
		Fnt->OffsetTable.EntrySelector = FileReader_ReadUInt16(&Reader, true);
		Fnt->OffsetTable.RangeShift = FileReader_ReadUInt16(&Reader, true);

		for (short unsigned TableIndex = 0; TableIndex < Fnt->OffsetTable.NumTables; TableIndex++)
		{
			FontTableDirectory TableDir = { 0 };
			FileReader_ReadInt8Array(&Reader, TableDir.Tag, 4);
			TableDir.CheckSum = FileReader_ReadUInt32(&Reader, true);
			TableDir.Offset = FileReader_ReadUInt32(&Reader, true);
			TableDir.Length = FileReader_ReadUInt32(&Reader, true);

			if (strncmp(TableDir.Tag, "head", 4) == 0)
			{
				memcpy(&Fnt->HeadTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "glyf", 4) == 0)
			{
				memcpy(&Fnt->GlyfTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "loca", 4) == 0)
			{
				memcpy(&Fnt->LocaTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "cmap", 4) == 0)
			{
				memcpy(&Fnt->CmapTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "maxp", 4) == 0)
			{
				memcpy(&Fnt->MaxpTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "hhea", 4) == 0)
			{
				memcpy(&Fnt->HheaTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "hmtx", 4) == 0)
			{
				memcpy(&Fnt->HmtxTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "OS/2", 4) == 0)
			{
				memcpy(&Fnt->OS2TableDir, &TableDir, sizeof(FontTableDirectory));
			}
		}

		assert(Fnt->HeadTableDir.Offset);
		assert(Fnt->GlyfTableDir.Offset);
		assert(Fnt->LocaTableDir.Offset);
		assert(Fnt->CmapTableDir.Offset);
		assert(Fnt->MaxpTableDir.Offset);
		assert(Fnt->HheaTableDir.Offset);
		assert(Fnt->HmtxTableDir.Offset);
		assert(Fnt->OS2TableDir.Offset);

		FileReader_SeekAbs(&Reader, Fnt->HeadTableDir.Offset);
		Fnt->HeadTable.Version = FileReader_ReadUInt32(&Reader, true);
		Fnt->HeadTable.FontRevision = FileReader_ReadUInt32(&Reader, true);
		Fnt->HeadTable.CheckSumAdjustment = FileReader_ReadUInt32(&Reader, true);
		Fnt->HeadTable.MagicNumber = FileReader_ReadUInt32(&Reader, true);
		Fnt->HeadTable.Flags = FileReader_ReadUInt16(&Reader, true);
		Fnt->HeadTable.UnitsPerEm = FileReader_ReadUInt16(&Reader, true);
		Fnt->HeadTable.Created = FileReader_ReadInt64(&Reader, true);
		Fnt->HeadTable.Modified = FileReader_ReadInt64(&Reader, true);
		Fnt->HeadTable.MinX = FileReader_ReadInt16(&Reader, true);
		Fnt->HeadTable.MinY = FileReader_ReadInt16(&Reader, true);
		Fnt->HeadTable.MaxX = FileReader_ReadInt16(&Reader, true);
		Fnt->HeadTable.MaxY = FileReader_ReadInt16(&Reader, true);
		Fnt->HeadTable.MacStyle = FileReader_ReadUInt16(&Reader, true);
		Fnt->HeadTable.LowestRecPPEM = FileReader_ReadUInt16(&Reader, true);
		Fnt->HeadTable.FontDirectionHint = FileReader_ReadInt16(&Reader, true);
		Fnt->HeadTable.IndexToLocFormat = FileReader_ReadInt16(&Reader, true);
		Fnt->HeadTable.GlyphDataFormat = FileReader_ReadInt16(&Reader, true);
		assert(Fnt->HeadTable.Version == 0x10000);
		assert(Fnt->HeadTable.MagicNumber == 0x5F0F3CF5);

		FileReader_SeekAbs(&Reader, Fnt->MaxpTableDir.Offset);
		Fnt->MaxpTable.Version = FileReader_ReadUInt32(&Reader, true);
		Fnt->MaxpTable.NumGlyphs = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxPoints = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxContours = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxComponentPoints = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxComponentContours = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxZones = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxTwilightPoints = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxStorage = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxFunctionDefs = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxInstructionDefs = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxStackElements = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxSizeOfInstructions = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxComponentElements = FileReader_ReadUInt16(&Reader, true);
		Fnt->MaxpTable.MaxComponentDepth = FileReader_ReadUInt16(&Reader, true);
		assert(Fnt->MaxpTable.Version == 0x10000);

		FileReader_SeekAbs(&Reader, Fnt->CmapTableDir.Offset);
		Fnt->CmapTable.Version = FileReader_ReadUInt16(&Reader, true);
		Fnt->CmapTable.NumberSubTables = FileReader_ReadUInt16(&Reader, true);
		assert(Fnt->CmapTable.Version == 0x0);

		FileReader_SeekAbs(&Reader, Fnt->HheaTableDir.Offset);
		Fnt->HheaTable.Version = FileReader_ReadUInt32(&Reader, true);
		Fnt->HheaTable.Ascent = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.Descent = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.LineGap = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.AdvanceWidthMax = FileReader_ReadUInt16(&Reader, true);
		Fnt->HheaTable.MinLeftSideBearing = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.MinRightSideBearing = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.xMaxExtent = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.CaretSlopeRise = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.CaretSlopeRun = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.CaretOffset = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.Reserved0 = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.Reserved1 = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.Reserved2 = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.Reserved3 = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.MetricDataFormt = FileReader_ReadInt16(&Reader, true);
		Fnt->HheaTable.NumOfLongHorMetrics = FileReader_ReadUInt16(&Reader, true);
		assert(Fnt->MaxpTable.Version == 0x10000);

		FileReader_SeekAbs(&Reader, Fnt->OS2TableDir.Offset);
		Fnt->OS2Table.Version = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.AvgCharWidth = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.WeightClass = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.WidthClass = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.Type = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SubScriptXSize = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SubScriptYSize = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SubScriptXOffset = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SubScriptYOffset = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SuperScriptXSize = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SuperScriptYSize = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SuperScriptXOffset = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.SuperScriptYOffset = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.StrikeoutSize = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.StrikeoutPosition = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.FamilyClass = FileReader_ReadInt16(&Reader, true);
		FileReader_ReadUInt8Array(&Reader, Fnt->OS2Table.Panose, 10);
		FileReader_ReadUInt32Array(&Reader, true, Fnt->OS2Table.UnicodeRange, 4);
		FileReader_ReadInt8Array(&Reader, Fnt->OS2Table.VendorID, 4);
		Fnt->OS2Table.Selection = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.FirstCharIndex = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.LastCharIndex = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.TypoAscender = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.TypoDescender = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.TypoLineGap = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.WinAscent = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.WinDescent = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.CodePageRange1 = FileReader_ReadUInt32(&Reader, true);
		Fnt->OS2Table.CodePageRange2 = FileReader_ReadUInt32(&Reader, true);
		Fnt->OS2Table.Height = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.CapHeight = FileReader_ReadInt16(&Reader, true);
		Fnt->OS2Table.DefaultChar = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.BreakChar = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.MaxContent = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.LowerPointSize = FileReader_ReadUInt16(&Reader, true);
		Fnt->OS2Table.UpperPointSize = FileReader_ReadUInt16(&Reader, true);

		short unsigned NumGlyphs = Fnt->MaxpTable.NumGlyphs;

		Fnt->Width = (int unsigned)(Fnt->HeadTable.MaxX - Fnt->HeadTable.MinX);
		Fnt->Height = (int unsigned)(Fnt->HeadTable.MaxY - Fnt->HeadTable.MinY);
		Fnt->Glyphs = (FontGlyph*)Memory_Alloc(NumGlyphs * sizeof(FontGlyph), 0);
		Fnt->GlyphOffsets = (int unsigned*)Memory_Alloc(NumGlyphs * sizeof(int unsigned), 0);

		Vector_Alloc(&Fnt->BezierOffsets, sizeof(FontBezierOffsetEntry));
		Vector_Alloc(&Fnt->BezierCurves, sizeof(FontBezierCurveEntry));

		for (short unsigned GlyphIndex = 0; GlyphIndex < NumGlyphs; GlyphIndex++)
		{
			if (Fnt->HeadTable.IndexToLocFormat)
			{
				FileReader_SeekAbs(&Reader, Fnt->LocaTableDir.Offset + (GlyphIndex * 4U));
				Fnt->GlyphOffsets[GlyphIndex] = Fnt->GlyfTableDir.Offset + FileReader_ReadUInt32(&Reader, true);
			}
			else
			{
				FileReader_SeekAbs(&Reader, Fnt->LocaTableDir.Offset + (GlyphIndex * 2U));
				Fnt->GlyphOffsets[GlyphIndex] = Fnt->GlyfTableDir.Offset + FileReader_ReadUInt16(&Reader, true) * 2U;
			}
		}

		FontBezierOffsetEntry CurrBezierOffset = { 0 };

		for (short unsigned GlyphIndex = 0; GlyphIndex < NumGlyphs; GlyphIndex++)
		{
			FontGlyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];

			memset(CurrGlyph, 0, sizeof(FontGlyph));

			Font_ReadGlyphInternal(Fnt, &Reader, GlyphIndex, CurrGlyph);
			Font_CreateBezierInternal(Fnt, CurrGlyph);

			CurrBezierOffset.Num = (int unsigned)Vector_Num(&CurrGlyph->BezierCurves);
			Vector_Push(&Fnt->BezierOffsets, &CurrBezierOffset);
			CurrBezierOffset.Start += CurrBezierOffset.Num;
			Vector_PushRange(&Fnt->BezierCurves, &CurrGlyph->BezierCurves);
		}

		Font_ApplyLayoutInfosInternal(Fnt, &Reader);

		Font_UnicodeToGlyphMappingsInternal(Fnt, &Reader);

		static FontWorldGlyphVertex WorldVertexBuffer[4] = { 0 };
		static int unsigned WorldIndexBuffer[6] = { 0 };

		WorldVertexBuffer[0].Position.X = 0.0F;
		WorldVertexBuffer[0].Position.Y = 0.0F;
		WorldVertexBuffer[0].Index = 0;
		WorldVertexBuffer[1].Position.X = 1.0F;
		WorldVertexBuffer[1].Position.Y = 0.0F;
		WorldVertexBuffer[1].Index = 1;
		WorldVertexBuffer[2].Position.X = 0.0F;
		WorldVertexBuffer[2].Position.Y = 1.0F;
		WorldVertexBuffer[2].Index = 2;
		WorldVertexBuffer[3].Position.X = 1.0F;
		WorldVertexBuffer[3].Position.Y = 1.0F;
		WorldVertexBuffer[3].Index = 3;

		WorldIndexBuffer[0] = 0;
		WorldIndexBuffer[1] = 1;
		WorldIndexBuffer[2] = 2;
		WorldIndexBuffer[3] = 2;
		WorldIndexBuffer[4] = 3;
		WorldIndexBuffer[5] = 1;

		static FontScreenGlyphVertex ScreenVertexBuffer[4] = { 0 };
		static int unsigned ScreenIndexBuffer[6] = { 0 };

		ScreenVertexBuffer[0].Position.X = 0.0F;
		ScreenVertexBuffer[0].Position.Y = 0.0F;
		ScreenVertexBuffer[0].Index = 0;
		ScreenVertexBuffer[1].Position.X = 1.0F;
		ScreenVertexBuffer[1].Position.Y = 0.0F;
		ScreenVertexBuffer[1].Index = 1;
		ScreenVertexBuffer[2].Position.X = 0.0F;
		ScreenVertexBuffer[2].Position.Y = 1.0F;
		ScreenVertexBuffer[2].Index = 2;
		ScreenVertexBuffer[3].Position.X = 1.0F;
		ScreenVertexBuffer[3].Position.Y = 1.0F;
		ScreenVertexBuffer[3].Index = 3;

		ScreenIndexBuffer[0] = 0;
		ScreenIndexBuffer[1] = 1;
		ScreenIndexBuffer[2] = 2;
		ScreenIndexBuffer[3] = 2;
		ScreenIndexBuffer[4] = 3;
		ScreenIndexBuffer[5] = 1;

		VertexArray_Alloc(&Fnt->WorldGlyphVertexArray);
		Buffer_VertexAlloc(&Fnt->WorldGlyphVertexBuffer);
		Buffer_VertexAlloc(&Fnt->WorldGlyphInstanceBuffer);
		Buffer_IndexAlloc(&Fnt->WorldGlyphIndexBuffer);

		VertexArray_Alloc(&Fnt->ScreenGlyphVertexArray);
		Buffer_VertexAlloc(&Fnt->ScreenGlyphVertexBuffer);
		Buffer_VertexAlloc(&Fnt->ScreenGlyphInstanceBuffer);
		Buffer_IndexAlloc(&Fnt->ScreenGlyphIndexBuffer);

		VertexArray_Bind(Fnt->WorldGlyphVertexArray);
		Buffer_VertexBind(Fnt->WorldGlyphVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(FontWorldGlyphVertex), OFFSET_OF(FontWorldGlyphVertex, Position));
		Buffer_VertexAttribPointerUInt32(1, 1, sizeof(FontWorldGlyphVertex), OFFSET_OF(FontWorldGlyphVertex, Index));
		Buffer_VertexResize(4 * sizeof(FontWorldGlyphVertex), WorldVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Fnt->WorldGlyphInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexEnableAttrib(6);
		Buffer_VertexEnableAttrib(7);
		Buffer_VertexEnableAttrib(8);
		Buffer_VertexEnableAttrib(9);
		Buffer_VertexEnableAttrib(10);
		Buffer_VertexEnableAttrib(11);
		Buffer_VertexEnableAttrib(12);
		Buffer_VertexAttribPointerReal32(2, 3, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Pivot));
		Buffer_VertexAttribPointerReal32(3, 3, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(4, 3, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(5, 2, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Scale));
		Buffer_VertexAttribPointerReal32(6, 2, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Bearing));
		Buffer_VertexAttribPointerReal32(7, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, UnitsPerEm));
		Buffer_VertexAttribPointerReal32(8, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, FontSize));
		Buffer_VertexAttribPointerReal32(9, 2, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, GlyphSize));
		Buffer_VertexAttribPointerReal32(10, 4, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Color));
		Buffer_VertexAttribPointerUInt32(11, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, GlyphIndex));
		Buffer_VertexAttribPointerUInt32(12, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, LineHeight));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexAttribDivisor(6, 1);
		Buffer_VertexAttribDivisor(7, 1);
		Buffer_VertexAttribDivisor(8, 1);
		Buffer_VertexAttribDivisor(9, 1);
		Buffer_VertexAttribDivisor(10, 1);
		Buffer_VertexAttribDivisor(11, 1);
		Buffer_VertexAttribDivisor(12, 1);
		Buffer_VertexResize(NumChars * sizeof(FontWorldGlyphInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Fnt->WorldGlyphIndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), WorldIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

		VertexArray_Bind(Fnt->ScreenGlyphVertexArray);
		Buffer_VertexBind(Fnt->ScreenGlyphVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(FontScreenGlyphVertex), OFFSET_OF(FontScreenGlyphVertex, Position));
		Buffer_VertexAttribPointerUInt32(1, 1, sizeof(FontScreenGlyphVertex), OFFSET_OF(FontScreenGlyphVertex, Index));
		Buffer_VertexResize(4 * sizeof(FontScreenGlyphVertex), ScreenVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Fnt->ScreenGlyphInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexEnableAttrib(6);
		Buffer_VertexEnableAttrib(7);
		Buffer_VertexEnableAttrib(8);
		Buffer_VertexEnableAttrib(9);
		Buffer_VertexEnableAttrib(10);
		Buffer_VertexEnableAttrib(11);
		Buffer_VertexAttribPointerReal32(2, 3, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Pivot));
		Buffer_VertexAttribPointerReal32(3, 2, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(4, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(5, 2, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Bearing));
		Buffer_VertexAttribPointerReal32(6, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, UnitsPerEm));
		Buffer_VertexAttribPointerReal32(7, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, FontSize));
		Buffer_VertexAttribPointerReal32(8, 2, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, GlyphSize));
		Buffer_VertexAttribPointerReal32(9, 4, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Color));
		Buffer_VertexAttribPointerUInt32(10, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, GlyphIndex));
		Buffer_VertexAttribPointerUInt32(11, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, LineHeight));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexAttribDivisor(6, 1);
		Buffer_VertexAttribDivisor(7, 1);
		Buffer_VertexAttribDivisor(8, 1);
		Buffer_VertexAttribDivisor(9, 1);
		Buffer_VertexAttribDivisor(10, 1);
		Buffer_VertexAttribDivisor(11, 1);
		Buffer_VertexResize(NumChars * sizeof(FontScreenGlyphInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Fnt->ScreenGlyphIndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), ScreenIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

		void* BezierOffsetBuffer = Vector_Buffer(&Fnt->BezierOffsets);
		void* BezierCurveBuffer = Vector_Buffer(&Fnt->BezierCurves);
		long long unsigned NumBezierOffsets = Vector_Num(&Fnt->BezierOffsets);
		long long unsigned NumBezierCurves = Vector_Num(&Fnt->BezierCurves);

		Buffer_StorageAllocSimple(&Fnt->BezierOffsetBuffer, NumBezierOffsets * sizeof(FontBezierOffsetEntry), BezierOffsetBuffer, GL_STATIC_DRAW);
		Buffer_StorageAllocSimple(&Fnt->BezierCurveBuffer, NumBezierCurves * sizeof(FontBezierCurveEntry), BezierCurveBuffer, GL_STATIC_DRAW);
	}
	void Font_ReadGlyphInternal(Font* Fnt, FileReader* Reader, short unsigned GlyphIndex, FontGlyph* Result)
	{
		FileReader_SeekAbs(Reader, Fnt->GlyphOffsets[GlyphIndex]);

		Result->NumContours = FileReader_ReadInt16(Reader, true);
		Result->MinX = FileReader_ReadInt16(Reader, true);
		Result->MinY = FileReader_ReadInt16(Reader, true);
		Result->MaxX = FileReader_ReadInt16(Reader, true);
		Result->MaxY = FileReader_ReadInt16(Reader, true);
		Result->IsCompound = Result->NumContours < 0;
		Result->GlyphIndex = GlyphIndex;

		if (Result->IsCompound)
		{
			Font_ReadCompoundGlyphInternal(Fnt, Reader, GlyphIndex, Result);
		}
		else
		{
			Font_ReadSimpleGlyphInternal(Fnt, Reader, Result);
		}
	}
	void Font_ReadSimpleGlyphInternal(Font* Fnt, FileReader* Reader, FontGlyph* Result)
	{
		UNREFERENCED_PARAMETER(Fnt);

		if (Result->NumContours == 0)
		{
			return;
		}

		Result->ContourEndIndices = (short unsigned*)Memory_Alloc(Result->NumContours * sizeof(short unsigned), 0);
		FileReader_ReadUInt16Array(Reader, true, Result->ContourEndIndices, (int unsigned)Result->NumContours);

		Result->NumPoints = Result->ContourEndIndices[Result->NumContours - 1U] + 1U;
		Result->Points = (FontGlyphPoint*)Memory_Alloc(Result->NumPoints * sizeof(FontGlyphPoint), 0);
		Result->Flags = (char unsigned*)Memory_Alloc(Result->NumPoints, 0);

		Result->NumInstructions = FileReader_ReadUInt16(Reader, true);
		Result->Instructions = (char unsigned*)Memory_Alloc(Result->NumInstructions, 0);
		FileReader_ReadUInt8Array(Reader, Result->Instructions, Result->NumInstructions);

		for (short unsigned PointIndex = 0; PointIndex < Result->NumPoints; PointIndex++)
		{
			char unsigned Flag = FileReader_ReadUInt8(Reader);
			Result->Flags[PointIndex] = Flag;
			if (IS_BIT_SET(Flag, REPEAT_FLAG_BIT))
			{
				char unsigned NumRepeats = FileReader_ReadUInt8(Reader);
				for (unsigned char RepeatIndex = 0; ((RepeatIndex < NumRepeats) && ((PointIndex + 1) < Result->NumPoints)); RepeatIndex++)
				{
					PointIndex++;
					Result->Flags[PointIndex] = Flag;
				}
			}
		}

		short CoordX = 0;
		short CoordY = 0;

		for (short unsigned PointIndex = 0; PointIndex < Result->NumPoints; PointIndex++)
		{
			char unsigned Flag = Result->Flags[PointIndex];

			if (IS_BIT_SET(Flag, X_SHORT_VECTOR_BIT))
			{
				char unsigned CoordOffset = FileReader_ReadUInt8(Reader);
				CoordX += IS_BIT_SET(Flag, X_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT) ? CoordOffset : -CoordOffset;
			}
			else if (IS_BIT_NOT_SET(Flag, X_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT))
			{
				CoordX += FileReader_ReadInt16(Reader, true);
			}

			Result->Points[PointIndex].X = CoordX;
			Result->Points[PointIndex].OnCurve = IS_BIT_SET(Flag, ON_CURVE_POINT_BIT);
		}

		for (short unsigned PointIndex = 0; PointIndex < Result->NumPoints; PointIndex++)
		{
			char unsigned Flag = Result->Flags[PointIndex];

			if (IS_BIT_SET(Flag, Y_SHORT_VECTOR_BIT))
			{
				char unsigned CoordOffset = FileReader_ReadUInt8(Reader);
				CoordY += IS_BIT_SET(Flag, Y_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT) ? CoordOffset : -CoordOffset;
			}
			else if (IS_BIT_NOT_SET(Flag, Y_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT))
			{
				CoordY += FileReader_ReadInt16(Reader, true);
			}

			Result->Points[PointIndex].Y = CoordY;
			Result->Points[PointIndex].OnCurve = IS_BIT_SET(Flag, ON_CURVE_POINT_BIT);
		}
	}
	void Font_ReadCompoundGlyphInternal(Font* Fnt, FileReader* Reader, short unsigned GlyphIndex, FontGlyph* Result)
	{
		UNREFERENCED_PARAMETER(GlyphIndex);

		while (true)
		{
			short unsigned Flags = FileReader_ReadUInt16(Reader, true);
			short unsigned NewGlyphIndex = FileReader_ReadUInt16(Reader, true);

			assert(Fnt->GlyphOffsets[GlyphIndex] != Fnt->GlyphOffsets[NewGlyphIndex]);

			bool ArgsAre2Bytes = IS_BIT_SET(Flags, 0);
			bool ArgsAreXYValues = IS_BIT_SET(Flags, 1);
			bool RoundXYToGrid = IS_BIT_SET(Flags, 2);
			bool IsSingleScaleValue = IS_BIT_SET(Flags, 3);
			bool IsMoreComponentsAfterThis = IS_BIT_SET(Flags, 5);
			bool IsXAndYScale = IS_BIT_SET(Flags, 6);
			bool Is2x2Matrix = IS_BIT_SET(Flags, 7);
			bool HasInstructions = IS_BIT_SET(Flags, 8);
			bool UseThisComponentMetrics = IS_BIT_SET(Flags, 9);
			bool ComponentsOverlap = IS_BIT_SET(Flags, 10);

			UNREFERENCED_PARAMETER(ArgsAreXYValues);
			UNREFERENCED_PARAMETER(RoundXYToGrid);
			UNREFERENCED_PARAMETER(HasInstructions);
			UNREFERENCED_PARAMETER(UseThisComponentMetrics);
			UNREFERENCED_PARAMETER(ComponentsOverlap);

			int Arg0 = 0;
			int Arg1 = 0;

			if (ArgsAre2Bytes)
			{
				Arg0 = FileReader_ReadInt16(Reader, true);
				Arg1 = FileReader_ReadInt16(Reader, true);
			}
			else
			{
				Arg0 = FileReader_ReadInt8(Reader);
				Arg1 = FileReader_ReadInt8(Reader);
			}

			assert(ArgsAreXYValues);

			double OffsetX = Arg0;
			double OffsetY = Arg1;
			double IHatX = 1.0;
			double IHatY = 0.0;
			double JHatX = 0.0;
			double JHatY = 1.0;

			if (IsSingleScaleValue)
			{
				short Value = FileReader_ReadInt16(Reader, true);

				IHatX = (double)Value / (double)(1 << 14);
				JHatY = (double)Value / (double)(1 << 14);
			}
			else if (IsXAndYScale)
			{
				short ValueIX = FileReader_ReadInt16(Reader, true);
				short ValueJY = FileReader_ReadInt16(Reader, true);

				IHatX = (double)ValueIX / (double)(1 << 14);
				JHatY = (double)ValueJY / (double)(1 << 14);
			}
			else if (Is2x2Matrix)
			{
				short ValueIX = FileReader_ReadInt16(Reader, true);
				short ValueIY = FileReader_ReadInt16(Reader, true);
				short ValueJX = FileReader_ReadInt16(Reader, true);
				short ValueJY = FileReader_ReadInt16(Reader, true);

				IHatX = (double)ValueIX / (double)(1 << 14);
				IHatY = (double)ValueIY / (double)(1 << 14);
				JHatX = (double)ValueJX / (double)(1 << 14);
				JHatY = (double)ValueJY / (double)(1 << 14);
			}

			int unsigned StoredLocation = FileReader_Offset(Reader);
			FontGlyph ResultGlyph = { 0 };
			Font_ReadGlyphInternal(Fnt, Reader, NewGlyphIndex, &ResultGlyph);
			FileReader_SeekAbs(Reader, StoredLocation);

			for (short unsigned PointIndex = 0; PointIndex < ResultGlyph.NumPoints; PointIndex++)
			{
				ResultGlyph.Points[PointIndex].X = (short)(IHatX * (double)ResultGlyph.Points[PointIndex].X + JHatX * (double)ResultGlyph.Points[PointIndex].Y + OffsetX);
				ResultGlyph.Points[PointIndex].Y = (short)(IHatY * (double)ResultGlyph.Points[PointIndex].X + JHatY * (double)ResultGlyph.Points[PointIndex].Y + OffsetY);
			}

			if (Result->NumContours == -1)
			{
				Result->NumContours = 0;
			}

			short unsigned NumContours = (short unsigned)(Result->NumContours + ResultGlyph.NumContours);
			short unsigned NumPoints = (short unsigned)(Result->NumPoints + ResultGlyph.NumPoints);

			Result->ContourEndIndices = (short unsigned*)Memory_Realloc(Result->ContourEndIndices, NumContours * sizeof(short unsigned));
			Result->Points = (FontGlyphPoint*)Memory_Realloc(Result->Points, NumPoints * sizeof(FontGlyphPoint));

			for (short unsigned ContourIndex = 0; ContourIndex < ResultGlyph.NumContours; ContourIndex++)
			{
				Result->ContourEndIndices[Result->NumContours + ContourIndex] = (short unsigned)(Result->NumPoints + ResultGlyph.ContourEndIndices[ContourIndex]);
			}

			memcpy(&Result->Points[Result->NumPoints], ResultGlyph.Points, ResultGlyph.NumPoints * sizeof(FontGlyphPoint));

			Result->NumContours = (short)NumContours;
			Result->NumPoints = NumPoints;

			if (ResultGlyph.ContourEndIndices) Memory_Free(ResultGlyph.ContourEndIndices);
			if (ResultGlyph.Points) Memory_Free(ResultGlyph.Points);
			if (ResultGlyph.Flags) Memory_Free(ResultGlyph.Flags);
			if (ResultGlyph.Instructions) Memory_Free(ResultGlyph.Instructions);

			if (IsMoreComponentsAfterThis == 0)
			{
				break;
			}
		}
	}
	void Font_ApplyLayoutInfosInternal(Font* Fnt, FileReader* Reader)
	{
		short Ascent = Fnt->HheaTable.Ascent;
		short Descent = Fnt->HheaTable.Descent;
		short LineGap = Fnt->HheaTable.LineGap;

		Fnt->LineHeight = (short unsigned)(Ascent - Descent + LineGap);

		FileReader_SeekAbs(Reader, Fnt->HmtxTableDir.Offset);

		short unsigned NumLongHorMetrics = Fnt->HheaTable.NumOfLongHorMetrics;
		short unsigned NumRem = (short unsigned)(Fnt->MaxpTable.NumGlyphs - NumLongHorMetrics);

		short unsigned LastAdvanceWidth = 0;
		for (short unsigned MetricIndex = 0; MetricIndex < NumLongHorMetrics; MetricIndex++)
		{
			short unsigned GlyphIndex = MetricIndex;

			FontGlyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];

			short unsigned AdvanceWidth = FileReader_ReadUInt16(Reader, true);
			short LeftSideBearing = FileReader_ReadInt16(Reader, true);
			short TopSideBearing = CurrGlyph->MinY + (CurrGlyph->MaxY - CurrGlyph->MinY);

			LastAdvanceWidth = AdvanceWidth;

			CurrGlyph->AdvanceWidth = AdvanceWidth;
			CurrGlyph->Width = (short unsigned)(CurrGlyph->MaxX - CurrGlyph->MinX);
			CurrGlyph->Height = (short unsigned)(CurrGlyph->MaxY - CurrGlyph->MinY);
			CurrGlyph->BearingX = (short unsigned)LeftSideBearing;
			CurrGlyph->BearingY = (short unsigned)(TopSideBearing);
		}

		for (short unsigned RemIndex = 0; RemIndex < NumRem; RemIndex++)
		{
			short unsigned GlyphIndex = (short unsigned)(NumLongHorMetrics + RemIndex);

			FontGlyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];

			short LeftSideBearing = FileReader_ReadInt16(Reader, true);
			short TopSideBearing = CurrGlyph->MinY + (CurrGlyph->MaxY - CurrGlyph->MinY);

			CurrGlyph->AdvanceWidth = LastAdvanceWidth;
			CurrGlyph->Width = (short unsigned)(CurrGlyph->MaxX - CurrGlyph->MinX);
			CurrGlyph->Height = (short unsigned)(CurrGlyph->MaxY - CurrGlyph->MinY);
			CurrGlyph->BearingX = (short unsigned)LeftSideBearing;
			CurrGlyph->BearingY = (short unsigned)(TopSideBearing);
		}
	}
	void Font_UnicodeToGlyphMappingsInternal(Font* Fnt, FileReader* Reader)
	{
		HashMap_Alloc(&Fnt->GlyphMapping);

		FileReader_SeekAbs(Reader, Fnt->CmapTableDir.Offset + sizeof(FontCmapTable));

		int SelectedUnicodeVersionID = -1;
		int unsigned CmapSubTableOffset = 0;
		for (int unsigned SubTableIndex = 0; SubTableIndex < Fnt->CmapTable.NumberSubTables; SubTableIndex++)
		{
			FontCmapSubTable CmapSubTable = { 0 };
			CmapSubTable.PlatformID = FileReader_ReadUInt16(Reader, true);
			CmapSubTable.PlatformSpecificID = FileReader_ReadUInt16(Reader, true);
			CmapSubTable.Offset = FileReader_ReadUInt32(Reader, true);

			if (CmapSubTable.PlatformID == 0)
			{
				if ((CmapSubTable.PlatformSpecificID == 0) ||
					(CmapSubTable.PlatformSpecificID == 1) ||
					(CmapSubTable.PlatformSpecificID == 3) ||
					(CmapSubTable.PlatformSpecificID == 4) &&
					(CmapSubTable.PlatformSpecificID > SelectedUnicodeVersionID))
				{
					CmapSubTableOffset = CmapSubTable.Offset;
					SelectedUnicodeVersionID = CmapSubTable.PlatformSpecificID;
				}
			}
			else if ((CmapSubTable.PlatformID == 3) && (SelectedUnicodeVersionID == -1))
			{
				if ((CmapSubTable.PlatformSpecificID == 1) ||
					(CmapSubTable.PlatformSpecificID == 10))
				{
					CmapSubTableOffset = CmapSubTable.Offset;
				}
			}
		}
		assert(CmapSubTableOffset);

		FileReader_SeekAbs(Reader, Fnt->CmapTableDir.Offset + CmapSubTableOffset);

		short unsigned Format = FileReader_ReadUInt16(Reader, true);
		assert((Format == 4) || (Format == 12));

		bool HasMissingGlyphs = false;

		switch (Format)
		{
		case 4:
		{
			short unsigned Length = FileReader_ReadUInt16(Reader, true);
			short unsigned Language = FileReader_ReadUInt16(Reader, true);
			short unsigned NumSegX2 = FileReader_ReadUInt16(Reader, true);
			short unsigned SearchRange = FileReader_ReadUInt16(Reader, true);
			short unsigned EntrySelector = FileReader_ReadUInt16(Reader, true);
			short unsigned RangeShift = FileReader_ReadUInt16(Reader, true);
			short unsigned NumSeg = NumSegX2 / 2U;

			UNREFERENCED_PARAMETER(Length);
			UNREFERENCED_PARAMETER(Language);
			UNREFERENCED_PARAMETER(SearchRange);
			UNREFERENCED_PARAMETER(EntrySelector);
			UNREFERENCED_PARAMETER(RangeShift);

			short unsigned* EndCodes = (short unsigned*)Memory_Alloc(NumSeg * sizeof(short unsigned), 0);
			FileReader_ReadUInt16Array(Reader, true, EndCodes, NumSeg);

			short unsigned Reserved = FileReader_ReadUInt16(Reader, true);
			UNREFERENCED_PARAMETER(Reserved);

			short unsigned* StartCodes = (short unsigned*)Memory_Alloc(NumSeg * sizeof(short unsigned), 0);
			FileReader_ReadUInt16Array(Reader, true, StartCodes, NumSeg);

			short unsigned* IDDeltas = (short unsigned*)Memory_Alloc(NumSeg * sizeof(short unsigned), 0);
			FileReader_ReadUInt16Array(Reader, true, IDDeltas, NumSeg);

			FontIDRangeOffsetMap* IDRangeOffsets = (FontIDRangeOffsetMap*)Memory_Alloc(NumSeg * sizeof(FontIDRangeOffsetMap), 0);

			for (short unsigned SegmentIndex = 0; SegmentIndex < NumSeg; SegmentIndex++)
			{
				IDRangeOffsets[SegmentIndex].ReadLocation = FileReader_Offset(Reader);
				IDRangeOffsets[SegmentIndex].RangeOffset = FileReader_ReadUInt16(Reader, true);
			}

			for (short unsigned SegmentIndex = 0; SegmentIndex < NumSeg; SegmentIndex++)
			{
				int unsigned EndCode = EndCodes[SegmentIndex];
				int unsigned CurrCode = StartCodes[SegmentIndex];

				if (CurrCode == 0xFFFFU)
				{
					break;
				}

				while (CurrCode <= EndCode)
				{
					short unsigned GlyphIndex = 0;
					int unsigned Unicode = CurrCode;

					if (IDRangeOffsets[SegmentIndex].RangeOffset == 0)
					{
						GlyphIndex = (CurrCode + IDDeltas[SegmentIndex]) % 0x10000U;
					}
					else
					{
						int unsigned StoredLocation = FileReader_Offset(Reader);
						int unsigned RangeOffsetLocation = IDRangeOffsets[SegmentIndex].ReadLocation + IDRangeOffsets[SegmentIndex].RangeOffset;
						int unsigned GlyphIndexArrayLocation = 2U * (CurrCode - StartCodes[SegmentIndex]) + RangeOffsetLocation;

						FileReader_SeekAbs(Reader, GlyphIndexArrayLocation);

						GlyphIndex = FileReader_ReadUInt16(Reader, true);

						if (GlyphIndex != 0)
						{
							GlyphIndex = (GlyphIndex + IDDeltas[SegmentIndex]) % 0x10000U;
						}

						FileReader_SeekAbs(Reader, StoredLocation);
					}

					FontGlyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];
					HashMap_Insert(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned), &CurrGlyph, sizeof(FontGlyph*));

					HasMissingGlyphs |= GlyphIndex == 0;
					CurrCode++;
				}
			}

			Memory_Free(EndCodes);
			Memory_Free(StartCodes);
			Memory_Free(IDDeltas);
			Memory_Free(IDRangeOffsets);

			break;
		}
		case 12:
		{
			short unsigned Reserved = FileReader_ReadUInt16(Reader, true);
			int unsigned Length = FileReader_ReadUInt32(Reader, true);
			int unsigned Language = FileReader_ReadUInt32(Reader, true);
			int unsigned NumGroups = FileReader_ReadUInt32(Reader, true);

			UNREFERENCED_PARAMETER(Reserved);
			UNREFERENCED_PARAMETER(Length);
			UNREFERENCED_PARAMETER(Language);

			for (int unsigned GroupIndex = 0; GroupIndex < NumGroups; GroupIndex++)
			{
				int unsigned StartCharCode = FileReader_ReadUInt32(Reader, true);
				int unsigned EndCharCode = FileReader_ReadUInt32(Reader, true);
				int unsigned StartGlyphCode = FileReader_ReadUInt32(Reader, true);
				int unsigned NumChars = EndCharCode - StartCharCode + 1;

				for (int unsigned CharIndex = 0; CharIndex < NumChars; CharIndex++)
				{
					short unsigned GlyphIndex = (short unsigned)(StartGlyphCode + CharIndex);
					int unsigned Unicode = StartCharCode + CharIndex;

					FontGlyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];
					HashMap_Insert(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned), &CurrGlyph, sizeof(FontGlyph*));

					HasMissingGlyphs |= GlyphIndex == 0;
				}
			}

			break;
		}
		}

		if (HasMissingGlyphs == 0)
		{
			short unsigned GlyphIndex = 0;
			int unsigned Unicode = 0xFFFF;

			FontGlyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];
			HashMap_Insert(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned), &CurrGlyph, sizeof(FontGlyph*));
		}
	}
	void Font_CreateBezierInternal(Font* Fnt, FontGlyph* Glyph)
	{
		Vector_Alloc(&Glyph->PointOffsets, sizeof(FontPointOffsetEntry));
		Vector_Alloc(&Glyph->BezierPoints, sizeof(Vector2));
		Vector_Alloc(&Glyph->BezierOffsets, sizeof(FontBezierOffsetEntry));
		Vector_Alloc(&Glyph->BezierCurves, sizeof(FontBezierCurveEntry));

		Vector CollectedPoints = { 0 };
		Vector_Alloc(&CollectedPoints, sizeof(Vector2));

		short unsigned UnitsPerEm = Fnt->HeadTable.UnitsPerEm;
		short unsigned ContourStartIndex = 0;

		FontPointOffsetEntry CurrPointOffset = { 0 };
		FontBezierOffsetEntry CurrBezierOffset = { 0 };

		for (short unsigned ContourIndex = 0; ContourIndex < Glyph->NumContours; ContourIndex++)
		{
			short unsigned ContourEndIndex = Glyph->ContourEndIndices[ContourIndex];
			short unsigned NumContourPoints = (short unsigned)(ContourEndIndex - ContourStartIndex);

			for (short unsigned PointIndex = ContourStartIndex; PointIndex <= (ContourStartIndex + NumContourPoints); PointIndex++)
			{
				short unsigned I0 = (short unsigned)(PointIndex % Glyph->NumPoints);
				short unsigned I1 = (short unsigned)((PointIndex + 1U) % Glyph->NumPoints);

				if (PointIndex == (ContourStartIndex + NumContourPoints))
				{
					I1 = ContourStartIndex;
				}

				FontGlyphPoint* CurrGlyphPoint = &Glyph->Points[I0];
				FontGlyphPoint* NextGlyphPoint = &Glyph->Points[I1];

				Vector2 Point = { (float)CurrGlyphPoint->X / UnitsPerEm, (float)CurrGlyphPoint->Y / UnitsPerEm };
				Vector_Push(&CollectedPoints, &Point);

				bool IsConsecutiveOffCurvePoints = !CurrGlyphPoint->OnCurve && !NextGlyphPoint->OnCurve;
				bool IsStraightLine = CurrGlyphPoint->OnCurve && NextGlyphPoint->OnCurve;

				if (IsConsecutiveOffCurvePoints || IsStraightLine)
				{
					Vector2 MidPoint = { (float)(CurrGlyphPoint->X + NextGlyphPoint->X) / 2.0F / UnitsPerEm, (float)(CurrGlyphPoint->Y + NextGlyphPoint->Y) / 2.0F / UnitsPerEm };
					Vector_Push(&CollectedPoints, &MidPoint);
				}
			}

			CurrPointOffset.Num = (int unsigned)Vector_Num(&CollectedPoints);
			Vector_Push(&Glyph->PointOffsets, &CurrPointOffset);
			CurrPointOffset.Start += CurrPointOffset.Num;

			Vector_PushRange(&Glyph->BezierPoints, &CollectedPoints);
			Vector_Clear(&CollectedPoints);

			ContourStartIndex = ContourEndIndex + 1U;
		}

		bool ContourComplete = false;
		long long unsigned NumBezierPoints = Vector_Num(&Glyph->BezierPoints);

		for (long long unsigned BezierPointIndex = 0; BezierPointIndex < NumBezierPoints; BezierPointIndex += 2)
		{
			int unsigned I0 = (int unsigned)BezierPointIndex;
			int unsigned I1 = (int unsigned)BezierPointIndex + 1;
			int unsigned I2 = (int unsigned)BezierPointIndex + 2;
			long long unsigned NumPointOffsets = Vector_Num(&Glyph->PointOffsets);

			for (long long unsigned PointOffsetIndex = 0; PointOffsetIndex < NumPointOffsets; PointOffsetIndex++)
			{
				FontPointOffsetEntry* PointOffset = (FontPointOffsetEntry*)Vector_At(&Glyph->PointOffsets, PointOffsetIndex);

				int unsigned StartOffset = PointOffset->Start;
				int unsigned EndOffset = PointOffset->Start + PointOffset->Num;
				int unsigned NumPoints = EndOffset - StartOffset;

				if ((I0 >= StartOffset) && (I0 < EndOffset))
				{
					if (I1 >= EndOffset)
					{
						I1 = StartOffset + ((I1 - StartOffset) % NumPoints);
						ContourComplete = true;
					}

					if (I2 >= EndOffset)
					{
						I2 = StartOffset + ((I2 - StartOffset) % NumPoints);
						ContourComplete = true;
					}

					break;
				}
			}

			Vector2* P0 = (Vector2*)Vector_At(&Glyph->BezierPoints, I0 % NumBezierPoints);
			Vector2* P1 = (Vector2*)Vector_At(&Glyph->BezierPoints, I1 % NumBezierPoints);
			Vector2* P2 = (Vector2*)Vector_At(&Glyph->BezierPoints, I2 % NumBezierPoints);

			FontBezierCurveEntry BezierCurve = { 0 };

			Vector2_Set(P0, &BezierCurve.P0);
			Vector2_Set(P1, &BezierCurve.P1);
			Vector2_Set(P2, &BezierCurve.P2);

			Vector_Push(&Glyph->BezierCurves, &BezierCurve);

			CurrBezierOffset.Num++;

			if (ContourComplete)
			{
				ContourComplete = false;

				Vector_Push(&Glyph->BezierOffsets, &CurrBezierOffset);
				CurrBezierOffset.Start += CurrBezierOffset.Num;
				CurrBezierOffset.Num = 0;
			}
		}

		Vector_Free(&CollectedPoints);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Text Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Text_BeginWorld(Font* Fnt)
	{
		sCurrFont = Fnt;

		Buffer_VertexBind(sCurrFont->WorldGlyphInstanceBuffer);
		sCurrFont->WorldGlyphInstanceOffset = 0;

		sMappedWorldGlyphInstanceBuffer = (FontWorldGlyphInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Text_DrawWorld(Vector3 const* Position, Vector3 const* Rotation, Vector2 const* Size, Color4 const* Color, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = Position->X;
		float Y = Position->Y;
		float Z = Position->Z;

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * Size->Y;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = Position->X;
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * Size->Y;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Pivot.X = Position->X;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Pivot.Y = Position->Y;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Pivot.Z = Position->Z;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Position.X = X;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Position.Y = Y;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Position.Z = Z;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Rotation.X = Rotation->X;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Rotation.Y = Rotation->Y;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Rotation.Z = Rotation->Z;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Scale.X = Size->X;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Scale.Y = Size->Y;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].FontSize = 0.0F;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Height;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.R = Color->R;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.G = Color->G;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.B = Color->B;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.A = Color->A;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					sCurrFont->WorldGlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Size->X;

				break;
			}
			}

			Char++;
		}
	}
	void Text_DrawWorldSimple(float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = PositionX;
		float Y = PositionY;
		float Z = PositionZ;

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * SizeY;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = PositionX;
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * SizeY;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Pivot.X = PositionX;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Pivot.Y = PositionY;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Pivot.Z = PositionZ;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Position.X = X;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Position.Y = Y;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Position.Z = Z;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Rotation.X = Pitch;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Rotation.Y = Yaw;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Rotation.Z = Roll;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Scale.X = SizeX;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Scale.Y = SizeY;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].FontSize = 0.0F;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Height;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.R = ColorR;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.G = ColorG;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.B = ColorB;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].Color.A = ColorA;
					sMappedWorldGlyphInstanceBuffer[sCurrFont->WorldGlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					sCurrFont->WorldGlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * SizeX;

				break;
			}
			}

			Char++;
		}
	}
	void Text_EndWorld(Matrix4x4 const* Projection, Matrix4x4 const* View)
	{
		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
		Shader_Bind(sWorldFontProgram);
		Shader_SetUniformMatrix4(sWorldFontProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sWorldFontProgram, "ViewMatrix", View);
		Buffer_StorageMount(sCurrFont->BezierOffsetBuffer, 0);
		Buffer_StorageMount(sCurrFont->BezierCurveBuffer, 1);
		VertexArray_Bind(sCurrFont->WorldGlyphVertexArray);
		VertexArray_DrawTriangleStripInstanced(4, sCurrFont->WorldGlyphInstanceOffset);
		VertexArray_UnBind();

		sCurrFont = 0;
		sMappedWorldGlyphInstanceBuffer = 0;
	}
	void Text_BeginScreen(Font* Fnt)
	{
		sCurrFont = Fnt;

		Buffer_VertexBind(sCurrFont->ScreenGlyphInstanceBuffer);
		sCurrFont->ScreenGlyphInstanceOffset = 0;

		sMappedScreenGlyphInstanceBuffer = (FontScreenGlyphInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Text_DrawScreen(Vector3 const* Position, float Rotation, float Size, Color4 const* Color, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = Position->X;
		float Y = Position->Y;

		Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = Position->X;
				Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Pivot.X = Position->X;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Pivot.Y = Position->Y;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Pivot.Z = Position->Z;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Position.X = X;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Position.Y = Y;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Rotation = Rotation;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].FontSize = Size;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : -(float)CurrGlyph->Height;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.R = Color->R;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.G = Color->G;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.B = Color->B;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.A = Color->A;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					sCurrFont->ScreenGlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Size;

				break;
			}
			}

			Char++;
		}
	}
	void Text_DrawScreenSimple(float PositionX, float PositionY, float PositionZ, float Rotation, float Size, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = PositionX;
		float Y = PositionY;

		Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = PositionX;
				Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Pivot.X = PositionX;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Pivot.Y = PositionY;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Pivot.Z = PositionZ;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Position.X = X;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Position.Y = Y;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Rotation = Rotation;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].FontSize = Size;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : -(float)CurrGlyph->Height;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.R = ColorR;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.G = ColorG;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.B = ColorB;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].Color.A = ColorA;
					sMappedScreenGlyphInstanceBuffer[sCurrFont->ScreenGlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					sCurrFont->ScreenGlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Size;

				break;
			}
			}

			Char++;
		}
	}
	void Text_EndScreen()
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };

		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
		Shader_Bind(sScreenFontProgram);
		Shader_SetUniformVector2(sScreenFontProgram, "ScreenSize", &ScreenSize);
		Buffer_StorageMount(sCurrFont->BezierOffsetBuffer, 0);
		Buffer_StorageMount(sCurrFont->BezierCurveBuffer, 1);
		VertexArray_Bind(sCurrFont->ScreenGlyphVertexArray);
		VertexArray_DrawTriangleStripInstanced(4, sCurrFont->ScreenGlyphInstanceOffset);
		VertexArray_UnBind();

		sCurrFont = 0;
		sMappedScreenGlyphInstanceBuffer = 0;
	}
	void TextCache_WorldAlloc(TextWorldCache* Cache, int unsigned NumChars)
	{
		memset(Cache, 0, sizeof(TextWorldCache));

		static FontWorldGlyphVertex WorldVertexBuffer[4] = { 0 };
		static int unsigned WorldIndexBuffer[6] = { 0 };

		WorldVertexBuffer[0].Position.X = 0.0F;
		WorldVertexBuffer[0].Position.Y = 0.0F;
		WorldVertexBuffer[0].Index = 0;
		WorldVertexBuffer[1].Position.X = 1.0F;
		WorldVertexBuffer[1].Position.Y = 0.0F;
		WorldVertexBuffer[1].Index = 1;
		WorldVertexBuffer[2].Position.X = 0.0F;
		WorldVertexBuffer[2].Position.Y = 1.0F;
		WorldVertexBuffer[2].Index = 2;
		WorldVertexBuffer[3].Position.X = 1.0F;
		WorldVertexBuffer[3].Position.Y = 1.0F;
		WorldVertexBuffer[3].Index = 3;

		WorldIndexBuffer[0] = 0;
		WorldIndexBuffer[1] = 1;
		WorldIndexBuffer[2] = 2;
		WorldIndexBuffer[3] = 2;
		WorldIndexBuffer[4] = 3;
		WorldIndexBuffer[5] = 1;

		VertexArray_Alloc(&Cache->GlyphVertexArray);
		Buffer_VertexAlloc(&Cache->GlyphVertexBuffer);
		Buffer_VertexAlloc(&Cache->GlyphInstanceBuffer);
		Buffer_IndexAlloc(&Cache->GlyphIndexBuffer);
		VertexArray_Bind(Cache->GlyphVertexArray);
		Buffer_VertexBind(Cache->GlyphVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(FontWorldGlyphVertex), OFFSET_OF(FontWorldGlyphVertex, Position));
		Buffer_VertexAttribPointerUInt32(1, 1, sizeof(FontWorldGlyphVertex), OFFSET_OF(FontWorldGlyphVertex, Index));
		Buffer_VertexResize(4 * sizeof(FontWorldGlyphVertex), WorldVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Cache->GlyphInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexEnableAttrib(6);
		Buffer_VertexEnableAttrib(7);
		Buffer_VertexEnableAttrib(8);
		Buffer_VertexEnableAttrib(9);
		Buffer_VertexEnableAttrib(10);
		Buffer_VertexEnableAttrib(11);
		Buffer_VertexEnableAttrib(12);
		Buffer_VertexAttribPointerReal32(2, 3, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Pivot));
		Buffer_VertexAttribPointerReal32(3, 3, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(4, 3, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(5, 2, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Scale));
		Buffer_VertexAttribPointerReal32(6, 2, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Bearing));
		Buffer_VertexAttribPointerReal32(7, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, UnitsPerEm));
		Buffer_VertexAttribPointerReal32(8, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, FontSize));
		Buffer_VertexAttribPointerReal32(9, 2, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, GlyphSize));
		Buffer_VertexAttribPointerReal32(10, 4, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, Color));
		Buffer_VertexAttribPointerUInt32(11, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, GlyphIndex));
		Buffer_VertexAttribPointerUInt32(12, 1, sizeof(FontWorldGlyphInstanceEntry), OFFSET_OF(FontWorldGlyphInstanceEntry, LineHeight));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexAttribDivisor(6, 1);
		Buffer_VertexAttribDivisor(7, 1);
		Buffer_VertexAttribDivisor(8, 1);
		Buffer_VertexAttribDivisor(9, 1);
		Buffer_VertexAttribDivisor(10, 1);
		Buffer_VertexAttribDivisor(11, 1);
		Buffer_VertexAttribDivisor(12, 1);
		Buffer_VertexResize(NumChars * sizeof(FontWorldGlyphInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Cache->GlyphIndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), WorldIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTextCaches += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void TextCache_DrawWorldCache(TextWorldCache* Cache, Matrix4x4 const* Projection, Matrix4x4 const* View)
	{
		Shader_Bind(sWorldFontProgram);
		Shader_SetUniformMatrix4(sWorldFontProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sWorldFontProgram, "ViewMatrix", View);
		Buffer_StorageMount(sCurrFont->BezierOffsetBuffer, 0);
		Buffer_StorageMount(sCurrFont->BezierCurveBuffer, 1);
		VertexArray_Bind(Cache->GlyphVertexArray);
		VertexArray_DrawTriangleStripInstanced(4, Cache->GlyphInstanceOffset);
		VertexArray_UnBind();
	}
	void TextCache_WorldFree(TextWorldCache* Cache)
	{
		VertexArray_Free(Cache->GlyphVertexArray);

		Buffer_Free(Cache->GlyphVertexBuffer);
		Buffer_Free(Cache->GlyphInstanceBuffer);
		Buffer_Free(Cache->GlyphIndexBuffer);

		memset(Cache, 0, sizeof(TextWorldCache));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTextCaches -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void TextCache_ScreenAlloc(TextScreenCache* Cache, int unsigned NumChars)
	{
		memset(Cache, 0, sizeof(TextScreenCache));

		static FontScreenGlyphVertex ScreenVertexBuffer[4] = { 0 };
		static int unsigned ScreenIndexBuffer[6] = { 0 };

		ScreenVertexBuffer[0].Position.X = 0.0F;
		ScreenVertexBuffer[0].Position.Y = 0.0F;
		ScreenVertexBuffer[0].Index = 0;
		ScreenVertexBuffer[1].Position.X = 1.0F;
		ScreenVertexBuffer[1].Position.Y = 0.0F;
		ScreenVertexBuffer[1].Index = 1;
		ScreenVertexBuffer[2].Position.X = 0.0F;
		ScreenVertexBuffer[2].Position.Y = 1.0F;
		ScreenVertexBuffer[2].Index = 2;
		ScreenVertexBuffer[3].Position.X = 1.0F;
		ScreenVertexBuffer[3].Position.Y = 1.0F;
		ScreenVertexBuffer[3].Index = 3;

		ScreenIndexBuffer[0] = 0;
		ScreenIndexBuffer[1] = 1;
		ScreenIndexBuffer[2] = 2;
		ScreenIndexBuffer[3] = 2;
		ScreenIndexBuffer[4] = 3;
		ScreenIndexBuffer[5] = 1;

		VertexArray_Alloc(&Cache->GlyphVertexArray);
		Buffer_VertexAlloc(&Cache->GlyphVertexBuffer);
		Buffer_VertexAlloc(&Cache->GlyphInstanceBuffer);
		Buffer_IndexAlloc(&Cache->GlyphIndexBuffer);
		VertexArray_Bind(Cache->GlyphVertexArray);
		Buffer_VertexBind(Cache->GlyphVertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(FontScreenGlyphVertex), OFFSET_OF(FontScreenGlyphVertex, Position));
		Buffer_VertexAttribPointerUInt32(1, 1, sizeof(FontScreenGlyphVertex), OFFSET_OF(FontScreenGlyphVertex, Index));
		Buffer_VertexResize(4 * sizeof(FontScreenGlyphVertex), ScreenVertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Cache->GlyphInstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexEnableAttrib(6);
		Buffer_VertexEnableAttrib(7);
		Buffer_VertexEnableAttrib(8);
		Buffer_VertexEnableAttrib(9);
		Buffer_VertexEnableAttrib(10);
		Buffer_VertexEnableAttrib(11);
		Buffer_VertexAttribPointerReal32(2, 3, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Pivot));
		Buffer_VertexAttribPointerReal32(3, 2, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Position));
		Buffer_VertexAttribPointerReal32(4, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Rotation));
		Buffer_VertexAttribPointerReal32(5, 2, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Bearing));
		Buffer_VertexAttribPointerReal32(6, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, UnitsPerEm));
		Buffer_VertexAttribPointerReal32(7, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, FontSize));
		Buffer_VertexAttribPointerReal32(8, 2, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, GlyphSize));
		Buffer_VertexAttribPointerReal32(9, 4, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, Color));
		Buffer_VertexAttribPointerUInt32(10, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, GlyphIndex));
		Buffer_VertexAttribPointerUInt32(11, 1, sizeof(FontScreenGlyphInstanceEntry), OFFSET_OF(FontScreenGlyphInstanceEntry, LineHeight));
		Buffer_VertexAttribDivisor(2, 1);
		Buffer_VertexAttribDivisor(3, 1);
		Buffer_VertexAttribDivisor(4, 1);
		Buffer_VertexAttribDivisor(5, 1);
		Buffer_VertexAttribDivisor(6, 1);
		Buffer_VertexAttribDivisor(7, 1);
		Buffer_VertexAttribDivisor(8, 1);
		Buffer_VertexAttribDivisor(9, 1);
		Buffer_VertexAttribDivisor(10, 1);
		Buffer_VertexAttribDivisor(11, 1);
		Buffer_VertexResize(NumChars * sizeof(FontScreenGlyphInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Cache->GlyphIndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), ScreenIndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTextCaches += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void TextCache_DrawScreenCache(TextScreenCache* Cache)
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };

		Shader_Bind(sScreenFontProgram);
		Shader_SetUniformVector2(sScreenFontProgram, "ScreenSize", &ScreenSize);
		Buffer_StorageMount(sCurrFont->BezierOffsetBuffer, 0);
		Buffer_StorageMount(sCurrFont->BezierCurveBuffer, 1);
		VertexArray_Bind(Cache->GlyphVertexArray);
		VertexArray_DrawTriangleStripInstanced(4, Cache->GlyphInstanceOffset);
		VertexArray_UnBind();
	}
	void TextCache_ScreenFree(TextScreenCache* Cache)
	{
		VertexArray_Free(Cache->GlyphVertexArray);

		Buffer_Free(Cache->GlyphVertexBuffer);
		Buffer_Free(Cache->GlyphInstanceBuffer);
		Buffer_Free(Cache->GlyphIndexBuffer);

		memset(Cache, 0, sizeof(TextScreenCache));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTextCaches -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void TextCache_BeginWorldCache(TextWorldCache* Cache, Font* Fnt)
	{
		sCurrFont = Fnt;

		Buffer_VertexBind(Cache->GlyphInstanceBuffer);
		Cache->GlyphInstanceOffset = 0;

		sMappedWorldGlyphInstanceBuffer = (FontWorldGlyphInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void TextCache_DrawWorld(TextWorldCache* Cache, Vector3 const* Position, Vector3 const* Rotation, Vector2 const* Size, Color4 const* Color, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = Position->X;
		float Y = Position->Y;
		float Z = Position->Z;

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * Size->Y;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = Position->X;
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * Size->Y;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.X = Position->X;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Y = Position->Y;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Z = Position->Z;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.X = X;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.Y = Y;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.Z = Z;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation.X = Rotation->X;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation.Y = Rotation->Y;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation.Z = Rotation->Z;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Scale.X = Size->X;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Scale.Y = Size->Y;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].FontSize = 0.0F;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Height;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.R = Color->R;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.G = Color->G;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.B = Color->B;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.A = Color->A;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					Cache->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Size->X;

				break;
			}
			}

			Char++;
		}
	}
	void TextCache_DrawWorldSimple(TextWorldCache* Cache, float PositionX, float PositionY, float PositionZ, float Pitch, float Yaw, float Roll, float SizeX, float SizeY, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = PositionX;
		float Y = PositionY;
		float Z = PositionZ;

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * SizeY;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = PositionX;
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * SizeY;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.X = PositionX;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Y = PositionY;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Z = PositionZ;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.X = X;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.Y = Y;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.Z = Z;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation.X = Pitch;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation.Y = Yaw;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation.Z = Roll;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Scale.X = SizeX;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Scale.Y = SizeY;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].FontSize = 0.0F;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Height;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.R = ColorR;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.G = ColorG;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.B = ColorB;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.A = ColorA;
					sMappedWorldGlyphInstanceBuffer[Cache->GlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					Cache->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * SizeX;

				break;
			}
			}

			Char++;
		}
	}
	void TextCache_EndWorldCache(TextWorldCache* Cache)
	{
		UNREFERENCED_PARAMETER(Cache);

		Buffer_VertexUnMap();
		Buffer_VertexUnBind();

		sCurrFont = 0;
		sMappedWorldGlyphInstanceBuffer = 0;
	}
	void TextCache_BeginScreenCache(TextScreenCache* Cache, Font* Fnt)
	{
		sCurrFont = Fnt;

		Buffer_VertexBind(Cache->GlyphInstanceBuffer);
		Cache->GlyphInstanceOffset = 0;

		sMappedScreenGlyphInstanceBuffer = (FontScreenGlyphInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void TextCache_DrawScreen(TextScreenCache* Cache, Vector3 const* Position, float Rotation, float Size, Color4 const* Color, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = Position->X;
		float Y = Position->Y;

		Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = Position->X;
				Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.X = Position->X;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Y = Position->Y;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Z = Position->Z;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.X = X;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.Y = Y;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation = Rotation;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].FontSize = Size;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : -(float)CurrGlyph->Height;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.R = Color->R;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.G = Color->G;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.B = Color->B;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.A = Color->A;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					Cache->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Size;

				break;
			}
			}

			Char++;
		}
	}
	void TextCache_DrawScreenSimple(TextScreenCache* Cache, float PositionX, float PositionY, float PositionZ, float Rotation, float Size, float ColorR, float ColorG, float ColorB, float ColorA, char const* Format, ...)
	{
		static char FormatBuffer[FAST_GL_TEXT_FMT_BUFFER_SIZE] = { 0 };

		va_list Arguments = { 0 };
		va_start(Arguments, Format);
		vsnprintf(FormatBuffer, sizeof(FormatBuffer), Format, Arguments);
		va_end(Arguments);

		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = PositionX;
		float Y = PositionY;

		Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

		char* Char = FormatBuffer;

		while (*Char)
		{
			switch (*Char)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = PositionX;
				Y += ((float)sCurrFont->Height / UnitsPerEm) * Size;

				break;
			}
			case '\0':
			{
				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*Char;
				FontGlyph* CurrGlyph = *(FontGlyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.X = PositionX;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Y = PositionY;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Pivot.Z = PositionZ;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.X = X;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position.Y = Y;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation = Rotation;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.X = (float)CurrGlyph->BearingX;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing.Y = (float)CurrGlyph->BearingY;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].FontSize = Size;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.X = (*Char == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphSize.Y = (*Char == ' ') ? 0.0F : -(float)CurrGlyph->Height;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.R = ColorR;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.G = ColorG;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.B = ColorB;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color.A = ColorA;
					sMappedScreenGlyphInstanceBuffer[Cache->GlyphInstanceOffset].LineHeight = sCurrFont->LineHeight;

					Cache->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Size;

				break;
			}
			}

			Char++;
		}
	}
	void TextCache_EndScreenCache(TextScreenCache* Cache)
	{
		UNREFERENCED_PARAMETER(Cache);

		Buffer_VertexUnMap();
		Buffer_VertexUnBind();

		sCurrFont = 0;
		sMappedScreenGlyphInstanceBuffer = 0;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Texture Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION 
	void Texture2D_Alloc(Texture2D* Texture)
	{
		memset(Texture, 0, sizeof(Texture2D));
		glGenTextures(1, &Texture->Texture);
		Texture->Width = 1;
		Texture->Height = 1;
		Texture->WrapS = TEXTURE_WRAP_CLAMP_TO_EDGE;
		Texture->WrapT = TEXTURE_WRAP_CLAMP_TO_EDGE;
		Texture->MinFilter = TEXTURE_FILTER_NEAREST;
		Texture->MagFilter = TEXTURE_FILTER_NEAREST;
		Texture->Type = TEXTURE_TYPE_UINT8;
		Texture->Format = TEXTURE_FORMAT_RGBA;
		Texture->InternalFormat = TEXTURE_INTERNAL_FORMAT_RGBA;

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTexture2Ds += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	int unsigned Texture2D_GetWidth(Texture2D* Texture)
	{
		return Texture->Width;
	}
	int unsigned Texture2D_GetHeight(Texture2D* Texture)
	{
		return Texture->Height;
	}
	int unsigned Texture2D_GetTexture(Texture2D* Texture)
	{
		return Texture->Texture;
	}
	void Texture2D_SetWidth(Texture2D* Texture, int unsigned Width)
	{
		Texture->Width = Width;
	}
	void Texture2D_SetHeight(Texture2D* Texture, int unsigned Height)
	{
		Texture->Height = Height;
	}
	void Texture2D_SetWrapS(Texture2D* Texture, TextureWrap WrapS)
	{
		Texture->WrapS = WrapS;
	}
	void Texture2D_SetWrapT(Texture2D* Texture, TextureWrap WrapT)
	{
		Texture->WrapT = WrapT;
	}
	void Texture2D_SetMinFilter(Texture2D* Texture, TextureFilter MinFilter)
	{
		Texture->MinFilter = MinFilter;
	}
	void Texture2D_SetMagFilter(Texture2D* Texture, TextureFilter MagFilter)
	{
		Texture->MagFilter = MagFilter;
	}
	void Texture2D_SetType(Texture2D* Texture, TextureType Type)
	{
		Texture->Type = Type;
	}
	void Texture2D_SetFormat(Texture2D* Texture, TextureFormat Format)
	{
		Texture->Format = Format;
	}
	void Texture2D_SetInternalFormat(Texture2D* Texture, TextureInternalFormat InternalFormat)
	{
		Texture->InternalFormat = InternalFormat;
	}
	void Texture2D_Bind(Texture2D* Texture)
	{
		glBindTexture(GL_TEXTURE_2D, Texture->Texture);
	}
	void Texture2D_MountSampler(Texture2D* Texture, int unsigned Index)
	{
		glBindTextureUnit(Index, Texture->Texture);
	}
	void Texture2D_MountImageRead(Texture2D* Texture, int unsigned Index, TextureInternalFormat InternalFormat)
	{
		glBindImageTexture(Index, Texture->Texture, 0, 0, 0, GL_READ_ONLY, InternalFormat);
	}
	void Texture2D_MountImageWrite(Texture2D* Texture, int unsigned Index, TextureInternalFormat InternalFormat)
	{
		glBindImageTexture(Index, Texture->Texture, 0, 0, 0, GL_WRITE_ONLY, InternalFormat);
	}
	void Texture2D_MountImageReadWrite(Texture2D* Texture, int unsigned Index, TextureInternalFormat InternalFormat)
	{
		glBindImageTexture(Index, Texture->Texture, 0, 0, 0, GL_READ_ONLY | GL_WRITE_ONLY, InternalFormat);
	}
	void Texture2D_Update(Texture2D* Texture, bool GenerateMipMaps)
	{
		glBindTexture(GL_TEXTURE_2D, Texture->Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Texture->WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Texture->WrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture->MinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texture->MagFilter);
		glTexImage2D(GL_TEXTURE_2D, 0, Texture->InternalFormat, (int)Texture->Width, (int)Texture->Height, 0, Texture->Format, Texture->Type, 0);
		if (GenerateMipMaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D_UpdatePixels(Texture2D* Texture, char unsigned* Pixels, bool GenerateMipMaps)
	{
		glBindTexture(GL_TEXTURE_2D, Texture->Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Texture->WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Texture->WrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture->MinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texture->MagFilter);
		glTexImage2D(GL_TEXTURE_2D, 0, Texture->InternalFormat, (int)Texture->Width, (int)Texture->Height, 0, Texture->Format, Texture->Type, Pixels);
		if (GenerateMipMaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void* Texture2D_CopyPixels(Texture2D* Texture)
	{
		void* Pixels = 0;

		switch (Texture->Type)
		{
		case TEXTURE_TYPE_UINT8:
		{
			switch (Texture->Format)
			{
			case TEXTURE_FORMAT_R: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(char unsigned), 0); break;
			case TEXTURE_FORMAT_RG: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(char unsigned) * 2, 0); break;
			case TEXTURE_FORMAT_RGB: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(char unsigned) * 3, 0); break;
			case TEXTURE_FORMAT_RGBA: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(char unsigned) * 4, 0); break;
			case TEXTURE_FORMAT_DEPTH_STENCIL: assert(0); break;
			}

			break;
		}
		case TEXTURE_TYPE_REAL32:
		{
			switch (Texture->Format)
			{
			case TEXTURE_FORMAT_R: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(float), 0); break;
			case TEXTURE_FORMAT_RG: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(float) * 2, 0); break;
			case TEXTURE_FORMAT_RGB: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(float) * 3, 0); break;
			case TEXTURE_FORMAT_RGBA: Pixels = Memory_Alloc(Texture->Width * Texture->Height * sizeof(float) * 4, 0); break;
			case TEXTURE_FORMAT_DEPTH_STENCIL: assert(0); break;
			}

			break;
		}
		case TEXTURE_TYPE_UINT24_UINT8:
		{
			assert(0);

			break;
		}
		}

		glBindTexture(GL_TEXTURE_2D, Texture->Texture);
		glGetTexImage(GL_TEXTURE_2D, 0, Texture->Format, Texture->Type, Pixels);
		glBindTexture(GL_TEXTURE_2D, 0);

		return Pixels;
	}
	void Texture2D_Free(Texture2D* Texture)
	{
		glDeleteTextures(1, &Texture->Texture);

		memset(Texture, 0, sizeof(Texture2D));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedTexture2Ds -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// FrameBuffer Definition
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void FrameBuffer_Alloc(FrameBuffer* Buffer, int unsigned NumColorAttachments, int unsigned Width, int unsigned Height)
	{
		memset(Buffer, 0, sizeof(FrameBuffer));

		glGenFramebuffers(1, &Buffer->FrameBuffer);

		Buffer->Width = Width;
		Buffer->Height = Height;
		Buffer->NumColorAttachments = NumColorAttachments;
		Buffer->ColorAttachments = (Texture2D**)Memory_Alloc(NumColorAttachments * sizeof(Texture2D*), 0);
		Buffer->DepthStencilAttachment = 0;
		Buffer->BufferAttachments = (int unsigned*)Memory_Alloc(NumColorAttachments * sizeof(int unsigned), 0);

		for (int unsigned ColorAttachmentIndex = 0; ColorAttachmentIndex < NumColorAttachments; ColorAttachmentIndex++)
		{
			Buffer->ColorAttachments[ColorAttachmentIndex] = 0;
			Buffer->BufferAttachments[ColorAttachmentIndex] = GL_COLOR_ATTACHMENT0 + ColorAttachmentIndex;
		}

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedFrameBuffers += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	int unsigned FrameBuffer_GetColorAttachmentNum(FrameBuffer* Buffer)
	{
		return Buffer->NumColorAttachments;
	}
	void FrameBuffer_SetWidth(FrameBuffer* Buffer, int unsigned Width)
	{
		Buffer->Width = Width;
	}
	void FrameBuffer_SetHeight(FrameBuffer* Buffer, int unsigned Height)
	{
		Buffer->Height = Height;
	}
	void FrameBuffer_SetColorAttachment(FrameBuffer* Buffer, int unsigned Index, Texture2D* Attachment)
	{
		Buffer->ColorAttachments[Index] = Attachment;
	}
	void FrameBuffer_SetDepthStencilAttachment(FrameBuffer* Buffer, Texture2D* Attachment)
	{
		Buffer->DepthStencilAttachment = Attachment;
	}
	Texture2D* FrameBuffer_GetColorAttachment(FrameBuffer* Buffer, int unsigned Index)
	{
		return Buffer->ColorAttachments[Index];
	}
	Texture2D* FrameBuffer_GetDepthStencilAttachment(FrameBuffer* Buffer)
	{
		return Buffer->DepthStencilAttachment;
	}
	void FrameBuffer_Update(FrameBuffer* Buffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, Buffer->FrameBuffer);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, (int)Buffer->Width);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, (int)Buffer->Height);

		for (int unsigned ColorAttachmentIndex = 0; ColorAttachmentIndex < Buffer->NumColorAttachments; ColorAttachmentIndex++)
		{
			Texture2D_SetWidth(Buffer->ColorAttachments[ColorAttachmentIndex], Buffer->Width);
			Texture2D_SetHeight(Buffer->ColorAttachments[ColorAttachmentIndex], Buffer->Height);
			Texture2D_Update(Buffer->ColorAttachments[ColorAttachmentIndex], false);
		}
		Texture2D_SetWidth(Buffer->DepthStencilAttachment, Buffer->Width);
		Texture2D_SetHeight(Buffer->DepthStencilAttachment, Buffer->Height);
		Texture2D_Update(Buffer->DepthStencilAttachment, false);

		for (int unsigned ColorAttachmentIndex = 0; ColorAttachmentIndex < Buffer->NumColorAttachments; ColorAttachmentIndex++)
		{
			int unsigned ColorTexture = Texture2D_GetTexture(Buffer->ColorAttachments[ColorAttachmentIndex]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ColorAttachmentIndex, GL_TEXTURE_2D, ColorTexture, 0);
		}
		int unsigned DepthStencilTexture = Texture2D_GetTexture(Buffer->DepthStencilAttachment);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthStencilTexture, 0);

		glDrawBuffers(Buffer->NumColorAttachments, Buffer->BufferAttachments);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void FrameBuffer_BindRead(FrameBuffer* Buffer)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, Buffer->FrameBuffer);
	}
	void FrameBuffer_BindWrite(FrameBuffer* Buffer)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Buffer->FrameBuffer);
	}
	void FrameBuffer_BindReadWrite(FrameBuffer* Buffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, Buffer->FrameBuffer);
	}
	void FrameBuffer_UnBindRead(FrameBuffer* Buffer)
	{
		UNREFERENCED_PARAMETER(Buffer);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}
	void FrameBuffer_UnBindWrite(FrameBuffer* Buffer)
	{
		UNREFERENCED_PARAMETER(Buffer);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
	void FrameBuffer_UnBindReadWrite(FrameBuffer* Buffer)
	{
		UNREFERENCED_PARAMETER(Buffer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void FrameBuffer_Free(FrameBuffer* Buffer)
	{
		glDeleteFramebuffers(1, &Buffer->FrameBuffer);

		Memory_Free(Buffer->BufferAttachments);
		Memory_Free(Buffer->ColorAttachments);

		memset(Buffer, 0, sizeof(FrameBuffer));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedFrameBuffers -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// BitMap Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void BitMap_Alloc(char unsigned** Pixels, char const* FilePath, int unsigned* Width, int unsigned* Height)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "rb");

		BitMapHeader Header = { 0 };
		BitMapInfoHeader InfoHeader = { 0 };

		fread(&Header, sizeof(BitMapHeader), 1, File);
		fread(&InfoHeader, sizeof(BitMapInfoHeader), 1, File);
		fseek(File, (long)Header.OffBits, SEEK_SET);

		assert(Header.Type == 0x4D42);

		(*Width) = (int unsigned)InfoHeader.Width;
		(*Height) = ((int unsigned)abs(InfoHeader.Height));

		char unsigned* PixelsOriginal = 0;

		switch (InfoHeader.BitCount)
		{
		case 24:
		{
			int unsigned RowSize = ((*Width) * 3U + 3U) & ~3U;
			PixelsOriginal = (char unsigned*)Memory_Alloc(RowSize * (*Height), 0);
			(*Pixels) = (char unsigned*)Memory_Alloc(RowSize * (*Height), 0);
			fread(PixelsOriginal, RowSize, (*Height), File);

			break;
		}
		case 32:
		{
			int unsigned RowSize = (*Width) * 4U;
			PixelsOriginal = (char unsigned*)Memory_Alloc(RowSize * (*Height), 0);
			(*Pixels) = (char unsigned*)Memory_Alloc(RowSize * (*Height), 0);
			fread(PixelsOriginal, RowSize, (*Height), File);

			break;
		}
		default:
		{
			assert(0);
		}
		}

		for (int unsigned Col = 0; Col < (*Height); Col++)
		{
			for (int unsigned Row = 0; Row < (*Width); Row++)
			{
				char unsigned* PixelOriginal = PixelsOriginal + (Col * (*Width) + Row) * 4U;
				char unsigned* PixelRemapped = (*Pixels) + (Col * (*Width) + Row) * 4U;
				PixelRemapped[2] = PixelOriginal[0];
				PixelRemapped[1] = PixelOriginal[1];
				PixelRemapped[0] = PixelOriginal[2];
				PixelRemapped[3] = PixelOriginal[3];
			}
		}

		Memory_Free(PixelsOriginal);

		fclose(File);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBitMaps += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void BitMap_Free(char unsigned* Pixels)
	{
		Memory_Free(Pixels);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedBitMaps -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Primitive Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Primitive_SpriteAlloc(SpriteMesh* Mesh)
	{
		memset(Mesh, 0, sizeof(SpriteMesh));

		static SpriteVertex VertexBuffer[4] = { 0 };
		static int unsigned IndexBuffer[6] = { 0 };

		VertexBuffer[0].Position.X = 0.0F;
		VertexBuffer[0].Position.Y = 0.0F;
		VertexBuffer[0].TextureCoords.X = 0.0F;
		VertexBuffer[0].TextureCoords.Y = 0.0F;
		VertexBuffer[1].Position.X = 1.0F;
		VertexBuffer[1].Position.Y = 0.0F;
		VertexBuffer[1].TextureCoords.X = 1.0F;
		VertexBuffer[1].TextureCoords.Y = 0.0F;
		VertexBuffer[2].Position.X = 0.0F;
		VertexBuffer[2].Position.Y = 1.0F;
		VertexBuffer[2].TextureCoords.X = 0.0F;
		VertexBuffer[2].TextureCoords.Y = 1.0F;
		VertexBuffer[3].Position.X = 1.0F;
		VertexBuffer[3].Position.Y = 1.0F;
		VertexBuffer[3].TextureCoords.X = 1.0F;
		VertexBuffer[3].TextureCoords.Y = 1.0F;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;
		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 1;

		VertexArray_Alloc(&Mesh->VertexArray);
		Buffer_VertexAlloc(&Mesh->VertexBuffer);
		Buffer_IndexAlloc(&Mesh->IndexBuffer);
		VertexArray_Bind(Mesh->VertexArray);
		Buffer_VertexBind(Mesh->VertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(SpriteVertex), OFFSET_OF(SpriteVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(SpriteVertex), OFFSET_OF(SpriteVertex, TextureCoords));
		Buffer_VertexResize(4 * sizeof(SpriteVertex), VertexBuffer, GL_STATIC_DRAW);
		Buffer_IndexBind(Mesh->IndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), IndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrimitives += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	int unsigned Primitive_GetSpriteVertexArray(SpriteMesh* Mesh)
	{
		return Mesh->VertexArray;
	}
	void Primitive_SpriteFree(SpriteMesh* Mesh)
	{
		Buffer_Free(Mesh->VertexBuffer);
		Buffer_Free(Mesh->IndexBuffer);
		VertexArray_Free(Mesh->VertexArray);

		memset(Mesh, 0, sizeof(SpriteMesh));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrimitives -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Primitive_PostProcessAlloc(PostProcessMesh* Mesh)
	{
		memset(Mesh, 0, sizeof(PostProcessMesh));

		static PostProcessVertex VertexBuffer[4] = { 0 };
		static int unsigned IndexBuffer[6] = { 0 };

		VertexBuffer[0].Position.X = -1.0F;
		VertexBuffer[0].Position.Y = -1.0F;
		VertexBuffer[0].TextureCoords.X = 0.0F;
		VertexBuffer[0].TextureCoords.Y = 0.0F;
		VertexBuffer[1].Position.X = 1.0F;
		VertexBuffer[1].Position.Y = -1.0F;
		VertexBuffer[1].TextureCoords.X = 1.0F;
		VertexBuffer[1].TextureCoords.Y = 0.0F;
		VertexBuffer[2].Position.X = -1.0F;
		VertexBuffer[2].Position.Y = 1.0F;
		VertexBuffer[2].TextureCoords.X = 0.0F;
		VertexBuffer[2].TextureCoords.Y = 1.0F;
		VertexBuffer[3].Position.X = 1.0F;
		VertexBuffer[3].Position.Y = 1.0F;
		VertexBuffer[3].TextureCoords.X = 1.0F;
		VertexBuffer[3].TextureCoords.Y = 1.0F;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;
		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 1;

		VertexArray_Alloc(&Mesh->VertexArray);
		Buffer_VertexAlloc(&Mesh->VertexBuffer);
		Buffer_IndexAlloc(&Mesh->IndexBuffer);
		VertexArray_Bind(Mesh->VertexArray);
		Buffer_VertexBind(Mesh->VertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(PostProcessVertex), OFFSET_OF(PostProcessVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(PostProcessVertex), OFFSET_OF(PostProcessVertex, TextureCoords));
		Buffer_VertexResize(4 * sizeof(PostProcessVertex), VertexBuffer, GL_STATIC_DRAW);
		Buffer_IndexBind(Mesh->IndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), IndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrimitives += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	int unsigned Primitive_GetPostProcessVertexArray(PostProcessMesh* Mesh)
	{
		return Mesh->VertexArray;
	}
	void Primitive_PostProcessFree(PostProcessMesh* Mesh)
	{
		Buffer_Free(Mesh->VertexBuffer);
		Buffer_Free(Mesh->IndexBuffer);
		VertexArray_Free(Mesh->VertexArray);

		memset(Mesh, 0, sizeof(PostProcessMesh));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrimitives -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Primitive_InstancedSpriteAlloc(InstancedSprite* Mesh, int unsigned NumInstances)
	{
		memset(Mesh, 0, sizeof(InstancedSprite));

		Mesh->NumInstances = NumInstances;

		static SpriteVertex VertexBuffer[4] = { 0 };
		static int unsigned IndexBuffer[6] = { 0 };

		VertexBuffer[0].Position.X = 0.0F;
		VertexBuffer[0].Position.Y = 0.0F;
		VertexBuffer[0].TextureCoords.X = 0.0F;
		VertexBuffer[0].TextureCoords.Y = 0.0F;
		VertexBuffer[1].Position.X = 1.0F;
		VertexBuffer[1].Position.Y = 0.0F;
		VertexBuffer[1].TextureCoords.X = 1.0F;
		VertexBuffer[1].TextureCoords.Y = 0.0F;
		VertexBuffer[2].Position.X = 0.0F;
		VertexBuffer[2].Position.Y = 1.0F;
		VertexBuffer[2].TextureCoords.X = 0.0F;
		VertexBuffer[2].TextureCoords.Y = 1.0F;
		VertexBuffer[3].Position.X = 1.0F;
		VertexBuffer[3].Position.Y = 1.0F;
		VertexBuffer[3].TextureCoords.X = 1.0F;
		VertexBuffer[3].TextureCoords.Y = 1.0F;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;
		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 1;

		VertexArray_Alloc(&Mesh->VertexArray);
		Buffer_VertexAlloc(&Mesh->VertexBuffer);
		Buffer_VertexAlloc(&Mesh->InstanceBuffer);
		Buffer_IndexAlloc(&Mesh->IndexBuffer);
		VertexArray_Bind(Mesh->VertexArray);
		Buffer_VertexBind(Mesh->VertexBuffer);
		Buffer_VertexEnableAttrib(0);
		Buffer_VertexEnableAttrib(1);
		Buffer_VertexAttribPointerReal32(0, 2, sizeof(SpriteVertex), OFFSET_OF(SpriteVertex, Position));
		Buffer_VertexAttribPointerReal32(1, 2, sizeof(SpriteVertex), OFFSET_OF(SpriteVertex, TextureCoords));
		Buffer_VertexResize(4 * sizeof(SpriteVertex), VertexBuffer, GL_STATIC_DRAW);
		Buffer_VertexBind(Mesh->InstanceBuffer);
		Buffer_VertexEnableAttrib(2);
		Buffer_VertexEnableAttrib(3);
		Buffer_VertexEnableAttrib(4);
		Buffer_VertexEnableAttrib(5);
		Buffer_VertexEnableAttrib(6);
		Buffer_VertexAttribPointerReal32(2, 4, sizeof(SpriteInstanceEntry), OFFSET_OF(SpriteInstanceEntry, TransformMatrix));
		Buffer_VertexAttribPointerReal32(3, 4, sizeof(SpriteInstanceEntry), OFFSET_OF(SpriteInstanceEntry, TransformMatrix) + sizeof(Vector4));
		Buffer_VertexAttribPointerReal32(4, 4, sizeof(SpriteInstanceEntry), OFFSET_OF(SpriteInstanceEntry, TransformMatrix) + sizeof(Vector4) * 2);
		Buffer_VertexAttribPointerReal32(5, 4, sizeof(SpriteInstanceEntry), OFFSET_OF(SpriteInstanceEntry, TransformMatrix) + sizeof(Vector4) * 3);
		Buffer_VertexAttribPointerUInt32(6, 1, sizeof(SpriteInstanceEntry), OFFSET_OF(SpriteInstanceEntry, AtlasIndex));
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		Buffer_VertexResize(NumInstances * sizeof(SpriteInstanceEntry), 0, GL_DYNAMIC_DRAW);
		Buffer_IndexBind(Mesh->IndexBuffer);
		Buffer_IndexResize(6 * sizeof(int unsigned), IndexBuffer, GL_STATIC_DRAW);
		VertexArray_UnBind();

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrimitives += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	int unsigned Primitive_GetInstancedSpriteNumInstances(InstancedSprite* Mesh)
	{
		return Mesh->NumInstances;
	}
	int unsigned Primitive_GetInstancedSpriteVertexArray(InstancedSprite* Mesh)
	{
		return Mesh->VertexArray;
	}
	SpriteInstanceEntry* Primitive_InstancedSpriteMapBuffer(InstancedSprite* Mesh)
	{
		Buffer_VertexBind(Mesh->InstanceBuffer);
		return (SpriteInstanceEntry*)Buffer_VertexMap(GL_WRITE_ONLY);
	}
	void Primitive_InstancedSpriteUnMapBuffer(InstancedSprite* Mesh)
	{
		UNREFERENCED_PARAMETER(Mesh);

		Buffer_VertexUnMap();
		Buffer_VertexUnBind();
	}
	void Primitive_InstancedSpriteFree(InstancedSprite* Mesh)
	{
		Buffer_Free(Mesh->VertexBuffer);
		Buffer_Free(Mesh->InstanceBuffer);
		Buffer_Free(Mesh->IndexBuffer);
		VertexArray_Free(Mesh->VertexArray);

		memset(Mesh, 0, sizeof(InstancedSprite));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPrimitives -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// PostProcessEffect Definition
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void PostProcessEffect_Alloc(PostProcessEffect* Effect, PostProcessMesh* Mesh, char const* FragmentSource)
	{
		memset(Effect, 0, sizeof(PostProcessEffect));
		Effect->Mesh = Mesh;
		Shader_VertexFragmentAlloc(&Effect->Program, sPostProcessVertexShader, FragmentSource);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPostProcessEffects += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void PostProcessEffect_Begin(PostProcessEffect* Effect)
	{
		Shader_Bind(Effect->Program);
	}
	void PostProcessEffect_SetColorAttachment(PostProcessEffect* Effect, Texture2D* ColorAttachment, int unsigned ColorAttachmentIndex)
	{
		UNREFERENCED_PARAMETER(Effect);
		Texture2D_MountSampler(ColorAttachment, ColorAttachmentIndex);
	}
	void PostProcessEffect_End(PostProcessEffect* Effect)
	{
		int unsigned VertexArray = Primitive_GetPostProcessVertexArray(Effect->Mesh);
		VertexArray_Bind(VertexArray);
		VertexArray_DrawTriangleStrip(4);
		VertexArray_UnBind();
	}
	void PostProcessEffect_Free(PostProcessEffect* Effect)
	{
		Shader_Free(Effect->Program);
		memset(Effect, 0, sizeof(PostProcessEffect));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedPostProcessEffects -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	char const* PostProcessEffect_GetColorBlendFragmentShader(void)
	{
		return sColorBlendPostProcessFragmentShader;
	}
	char const* PostProcessEffect_GetWeightedBlendedOrderIndependentTransparencyPostProcessFragmentShader(void)
	{
		return sWeightedBlendedOrderIndependentTransparencyPostProcessFragmentShader;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Kek Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Kek_Alloc(void)
	{
		Batch_Alloc(&sKekBatch);

		sKekStyle.DockTabWidth = 150.0F;
		sKekStyle.DockTabHeight = 30.0F;
	}
	void Kek_SetRootNode(void* Node)
	{
		sKekRootNode = Node;
	}
	void Kek_Resize(void)
	{
		if (sKekRootNode)
		{
			KekNode_Resize(sKekRootNode);
		}
	}
	void Kek_Update(void)
	{
		if (sKekRootNode)
		{
			KekNode_Update(sKekRootNode);
		}
	}
	void Kek_Draw(void)
	{
		float Depth = KEK_INITIAL_DEPTH;

		if (sKekRootNode)
		{
			Batch_BeginScreenRects(&sKekBatch);
			KekNode_Draw(sKekRootNode, KEK_BATCH_MODE_RECT, Depth);
			Batch_EndScreenRects();

			Text_BeginScreen(&sDefaultFont);
			KekNode_Draw(sKekRootNode, KEK_BATCH_MODE_TEXT, Depth);
			Text_EndScreen();
		}
	}
	void Kek_Free(void)
	{
		Batch_Free(&sKekBatch);
	}
	void Kek_PrintTree(void)
	{
		if (sKekRootNode)
		{
			KekNode_PrintTree(sKekRootNode, 0);
		}
	}
	void Kek_DrawRectInternal(KekBatchMode BatchMode, Rect const* Rect, float Rotation, float Depth, Color4 const* Color)
	{
		if (BatchMode == KEK_BATCH_MODE_RECT)
		{
			Vector3 Position = { Rect_PositionX(Rect), Rect_PositionY(Rect), Depth };
			Vector2 Size = { Rect_Width(Rect), Rect_Height(Rect) };

			Batch_DrawScreenRect(&Position, Rotation, &Size, Color);
		}
	}
	void Kek_DrawTextInternal(KekBatchMode BatchMode, Rect const* Rect, float Rotation, float Depth, float Size, Color4 const* Color, char const* Text)
	{
		if (BatchMode == KEK_BATCH_MODE_TEXT)
		{
			Vector3 Position = { Rect_PositionX(Rect), Rect_PositionY(Rect), Depth };

			Text_DrawScreen(&Position, Rotation, Size, Color, Text);
		}
	}
	void KekNode_Resize(KekNode* Node)
	{
		KekNodeClass* Class = MEMBER_OF(Node, KekNode, Class, KekNodeClass);

		switch (*Class)
		{
		case KEK_NODE_CLASS_DOCK_ROOT: KekDockLayout_Resize((KekDockLayout*)Node); break;
		case KEK_NODE_CLASS_LIST_LAYOUT: KekListLayout_Resize((KekListLayout*)Node); break;
		case KEK_NODE_CLASS_GRID_LAYOUT: KekGridLayout_Resize((KekGridLayout*)Node); break;
		case KEK_NODE_CLASS_TOOL_BAR: break;
		case KEK_NODE_CLASS_IMAGE: break;
		case KEK_NODE_CLASS_BUTTON: break;
		case KEK_NODE_CLASS_SLIDER: break;
		case KEK_NODE_CLASS_VIEW_PORT: break;
		case KEK_NODE_CLASS_TEST: break;
		}
	}
	void KekNode_Update(KekNode* Node)
	{
		KekNodeClass* Class = MEMBER_OF(Node, KekNode, Class, KekNodeClass);

		switch (*Class)
		{
		case KEK_NODE_CLASS_DOCK_ROOT: KekDockLayout_Update((KekDockLayout*)Node); break;
		case KEK_NODE_CLASS_LIST_LAYOUT: KekListLayout_Update((KekListLayout*)Node); break;
		case KEK_NODE_CLASS_GRID_LAYOUT: KekGridLayout_Update((KekGridLayout*)Node); break;
		case KEK_NODE_CLASS_TOOL_BAR: KekToolBar_Update((KekToolBar*)Node); break;
		case KEK_NODE_CLASS_IMAGE: KekImage_Update((KekImage*)Node); break;
		case KEK_NODE_CLASS_BUTTON: KekButton_Update((KekButton*)Node); break;
		case KEK_NODE_CLASS_SLIDER: KekSlider_Update((KekSlider*)Node); break;
		case KEK_NODE_CLASS_VIEW_PORT: KekViewPort_Update((KekViewPort*)Node); break;
		case KEK_NODE_CLASS_TEST: KekTest_Update((KekTest*)Node); break;
		}
	}
	void KekNode_Draw(KekNode* Node, KekBatchMode BatchMode, float Depth)
	{
		KekNodeClass* Class = MEMBER_OF(Node, KekNode, Class, KekNodeClass);

		switch (*Class)
		{
		case KEK_NODE_CLASS_DOCK_ROOT: KekDockLayout_Draw((KekDockLayout*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_LIST_LAYOUT: KekListLayout_Draw((KekListLayout*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_GRID_LAYOUT: KekGridLayout_Draw((KekGridLayout*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_TOOL_BAR: KekToolBar_Draw((KekToolBar*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_IMAGE: KekImage_Draw((KekImage*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_BUTTON: KekButton_Draw((KekButton*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_SLIDER: KekSlider_Draw((KekSlider*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_VIEW_PORT: KekViewPort_Draw((KekViewPort*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		case KEK_NODE_CLASS_TEST: KekTest_Draw((KekTest*)Node, BatchMode, Depth + KEK_DEPTH_INCREMENT); break;
		}
	}
	void KekNode_PrintTree(KekNode* Node, int unsigned NumIdentSteps)
	{
		for (int unsigned IdentStep = 0; IdentStep < NumIdentSteps; IdentStep++)
		{
			printf("\t");
		}

		if (Node)
		{
			KekNodeClass* Class = MEMBER_OF(Node, KekNode, Class, KekNodeClass);

			switch (*Class)
			{
			case KEK_NODE_CLASS_DOCK_ROOT: KekDockLayout_PrintTree((KekDockLayout*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_LIST_LAYOUT: KekListLayout_PrintTree((KekListLayout*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_GRID_LAYOUT: KekGridLayout_PrintTree((KekGridLayout*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_TOOL_BAR: KekToolBar_PrintTree((KekToolBar*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_IMAGE: KekImage_PrintTree((KekImage*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_BUTTON: KekButton_PrintTree((KekButton*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_SLIDER: KekSlider_PrintTree((KekSlider*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_VIEW_PORT: KekViewPort_PrintTree((KekViewPort*)Node, NumIdentSteps); break;
			case KEK_NODE_CLASS_TEST: KekTest_PrintTree((KekTest*)Node, NumIdentSteps); break;
			}
		}
	}
	KekDockPanel* KekDockPanel_Alloc(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title, KekNode* Node)
	{
		KekDockPanel* Panel = (KekDockPanel*)Memory_Alloc(sizeof(KekDockPanel), 0);

		memset(Panel, 0, sizeof(KekDockPanel));

		Panel->Type = KEK_DOCK_PANEL_TYPE_WINDOW;
		Panel->DockLayout = DockLayout;
		Panel->ParentPanel = DockPanel;
		Panel->Node = Node;
		Panel->BackgroundColor.R = Random_Real32Between(0.0F, 1.0F);
		Panel->BackgroundColor.G = Random_Real32Between(0.0F, 1.0F);
		Panel->BackgroundColor.B = Random_Real32Between(0.0F, 1.0F);
		Panel->BackgroundColor.A = 1.0F;
		Panel->TextColor.R = 1.0F;
		Panel->TextColor.G = 1.0F;
		Panel->TextColor.B = 1.0F;
		Panel->TextColor.A = 1.0F;

		long long unsigned TitleLength = strlen(Title);
		memcpy(Panel->Title, Title, MIN(KEK_DOCK_PANEL_TITLE_SIZE, TitleLength));

		List_InitHead(&Panel->ChildPanels);

		if (DockPanel)
		{
			Rect_Set(&DockPanel->PanelRect, &Panel->PanelRect);
		}
		else
		{
			Rect_Set(&DockLayout->Node.Rect, &Panel->PanelRect);
		}

		return Panel;
	}
	KekDockPanel* KekDockPanel_Insert(KekDockPanel* DockPanel, char const* Title)
	{
		KekDockPanel* ChildPanel = KekDockPanel_Alloc(DockPanel->DockLayout, DockPanel, Title, 0);

		Rect TabRect = { 0 };
		TabRect.Left = DockPanel->PanelRect.Left;
		TabRect.Right = DockPanel->PanelRect.Left + sKekStyle.DockTabWidth;
		TabRect.Top = DockPanel->PanelRect.Top;
		TabRect.Bottom = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;

		Rect PanelRect = { 0 };
		PanelRect.Left = DockPanel->PanelRect.Left;
		PanelRect.Right = DockPanel->PanelRect.Right;
		PanelRect.Top = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;
		PanelRect.Bottom = DockPanel->PanelRect.Bottom;

		Rect_Set(&TabRect, &ChildPanel->TabRect);
		Rect_Set(&PanelRect, &ChildPanel->PanelRect);

		return ChildPanel;
	}
	KekDockPanel* KekDockPanel_InsertLeft(KekDockPanel* DockPanel, char const* Title)
	{
		KekDockPanel* ChildPanel = KekDockPanel_Alloc(DockPanel->DockLayout, DockPanel, Title, 0);

		Rect TabRect = { 0 };
		TabRect.Left = DockPanel->PanelRect.Left;
		TabRect.Right = DockPanel->PanelRect.Left + sKekStyle.DockTabWidth;
		TabRect.Top = DockPanel->PanelRect.Top;
		TabRect.Bottom = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;

		Rect PanelRect = { 0 };
		PanelRect.Left = DockPanel->PanelRect.Left;
		PanelRect.Right = DockPanel->PanelRect.Right;
		PanelRect.Top = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;
		PanelRect.Bottom = DockPanel->PanelRect.Bottom;

		Rect_Set(&TabRect, &ChildPanel->TabRect);
		Rect_Set(&PanelRect, &ChildPanel->PanelRect);

		return ChildPanel;
	}
	KekDockPanel* KekDockPanel_InsertRight(KekDockPanel* DockPanel, char const* Title)
	{
		KekDockPanel* ChildPanel = KekDockPanel_Alloc(DockPanel->DockLayout, DockPanel, Title, 0);

		Rect TabRect = { 0 };
		TabRect.Left = DockPanel->PanelRect.Left;
		TabRect.Right = DockPanel->PanelRect.Left + sKekStyle.DockTabWidth;
		TabRect.Top = DockPanel->PanelRect.Top;
		TabRect.Bottom = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;

		Rect PanelRect = { 0 };
		PanelRect.Left = DockPanel->PanelRect.Left;
		PanelRect.Right = DockPanel->PanelRect.Right;
		PanelRect.Top = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;
		PanelRect.Bottom = DockPanel->PanelRect.Bottom;

		Rect_Set(&TabRect, &ChildPanel->TabRect);
		Rect_Set(&PanelRect, &ChildPanel->PanelRect);

		return ChildPanel;
	}
	KekDockPanel* KekDockPanel_InsertTop(KekDockPanel* DockPanel, char const* Title)
	{
		KekDockPanel* ChildPanel = KekDockPanel_Alloc(DockPanel->DockLayout, DockPanel, Title, 0);

		Rect TabRect = { 0 };
		TabRect.Left = DockPanel->PanelRect.Left;
		TabRect.Right = DockPanel->PanelRect.Left + sKekStyle.DockTabWidth;
		TabRect.Top = DockPanel->PanelRect.Top;
		TabRect.Bottom = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;

		Rect PanelRect = { 0 };
		PanelRect.Left = DockPanel->PanelRect.Left;
		PanelRect.Right = DockPanel->PanelRect.Right;
		PanelRect.Top = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;
		PanelRect.Bottom = DockPanel->PanelRect.Bottom;

		Rect_Set(&TabRect, &ChildPanel->TabRect);
		Rect_Set(&PanelRect, &ChildPanel->PanelRect);

		return ChildPanel;
	}
	KekDockPanel* KekDockPanel_InsertBottom(KekDockPanel* DockPanel, char const* Title)
	{
		KekDockPanel* ChildPanel = KekDockPanel_Alloc(DockPanel->DockLayout, DockPanel, Title, 0);

		Rect TabRect = { 0 };
		TabRect.Left = DockPanel->PanelRect.Left;
		TabRect.Right = DockPanel->PanelRect.Left + sKekStyle.DockTabWidth;
		TabRect.Top = DockPanel->PanelRect.Top;
		TabRect.Bottom = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;

		Rect PanelRect = { 0 };
		PanelRect.Left = DockPanel->PanelRect.Left;
		PanelRect.Right = DockPanel->PanelRect.Right;
		PanelRect.Top = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;
		PanelRect.Bottom = DockPanel->PanelRect.Bottom;

		Rect_Set(&TabRect, &ChildPanel->TabRect);
		Rect_Set(&PanelRect, &ChildPanel->PanelRect);

		return ChildPanel;
	}
	KekDockPanel* KekDockPanel_FindChildInsideBounds(KekDockPanel* DockPanel)
	{
		UNREFERENCED_PARAMETER(DockPanel);

		//ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
		//while (Entry != &DockPanel->ChildPanels)
		//{
		//	KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);
		//
		//	if (Rect_Overlap(&ChildPanel->Rect, (float)sMousePositionX, (float)sMousePositionY))
		//	{
		//		return KekDockPanel_FindChildInsideBounds(ChildPanel);
		//	}
		//
		//	Entry = Entry->Next;
		//}
		//
		//return DockPanel;

		return 0;
	}
	void KekDockPanel_UpdateRect(KekDockPanel* DockPanel, int unsigned ChildIndex)
	{
		switch (DockPanel->Type)
		{
		case KEK_DOCK_PANEL_TYPE_WINDOW:
		{
			Rect* ParentRect = (DockPanel->ParentPanel) ? &DockPanel->ParentPanel->PanelRect : &DockPanel->DockLayout->Node.Rect;

			float TabOffsetX = ParentRect->Left + ChildIndex * sKekStyle.DockTabWidth;

			Rect TabRect = { 0 };
			TabRect.Left = TabOffsetX;
			TabRect.Right = TabOffsetX + sKekStyle.DockTabWidth;
			TabRect.Top = ParentRect->Top;
			TabRect.Bottom = ParentRect->Top + sKekStyle.DockTabHeight;

			Rect PanelRect = { 0 };
			PanelRect.Left = ParentRect->Left;
			PanelRect.Right = ParentRect->Right;
			PanelRect.Top = ParentRect->Top + sKekStyle.DockTabHeight;
			PanelRect.Bottom = ParentRect->Bottom;

			Rect_Set(&TabRect, &DockPanel->TabRect);
			Rect_Set(&PanelRect, &DockPanel->PanelRect);

			ChildIndex = 0;
			ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
			while (Entry != &DockPanel->ChildPanels)
			{
				KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

				KekDockPanel_UpdateRect(ChildPanel, ChildIndex);

				ChildIndex += 1;
				Entry = Entry->Next;
			}

			break;
		}
		case KEK_DOCK_PANEL_TYPE_HORIZONTAL:
		{
			long long unsigned NumChildPanels = List_Num(&DockPanel->ChildPanels);
			float ChildWidth = Rect_Width(&DockPanel->PanelRect) / (float)NumChildPanels;
			float ChildOffsetX = DockPanel->PanelRect.Left;

			ChildIndex = 0;
			ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
			while (Entry != &DockPanel->ChildPanels)
			{
				KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

				Rect PanelRect = { 0 };
				PanelRect.Left = ChildOffsetX;
				PanelRect.Right = ChildOffsetX + ChildWidth;
				PanelRect.Top = DockPanel->PanelRect.Top + sKekStyle.DockTabHeight;
				PanelRect.Bottom = DockPanel->PanelRect.Bottom;

				Rect_Set(&PanelRect, &ChildPanel->PanelRect);

				KekDockPanel_UpdateRect(ChildPanel, ChildIndex);

				ChildOffsetX += ChildWidth;

				Entry = Entry->Next;
			}

			break;
		}
		case KEK_DOCK_PANEL_TYPE_VERTICAL:
		{
			long long unsigned NumChildPanels = List_Num(&DockPanel->ChildPanels);
			float ChildHeight = Rect_Height(&DockPanel->PanelRect) / (float)NumChildPanels;
			float ChildOffsetY = DockPanel->PanelRect.Top;

			ChildIndex = 0;
			ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
			while (Entry != &DockPanel->ChildPanels)
			{
				KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

				Rect PanelRect = { 0 };
				PanelRect.Left = DockPanel->PanelRect.Left;
				PanelRect.Right = DockPanel->PanelRect.Right;
				PanelRect.Top = ChildOffsetY;
				PanelRect.Bottom = ChildOffsetY + ChildHeight;

				Rect_Set(&PanelRect, &ChildPanel->PanelRect);

				KekDockPanel_UpdateRect(ChildPanel, ChildIndex);

				ChildOffsetY += ChildHeight;

				Entry = Entry->Next;
			}

			break;
		}
		}
	}
	void KekDockPanel_Update(KekDockPanel* DockPanel)
	{
		if (Window_IsMouseKeyPressed(MOUSE_KEY_LEFT))
		{
			if (!DockPanel->DockLayout->DragPanel)
			{
				if (Rect_Overlap(&DockPanel->TabRect, (float)sMousePositionX, (float)sMousePositionY))
				{
					DockPanel->DockLayout->DragPanel = DockPanel;
					DockPanel->DockLayout->DragOffsetX = (float)sMousePositionX - DockPanel->TabRect.Left;
					DockPanel->DockLayout->DragOffsetY = (float)sMousePositionY - DockPanel->TabRect.Top;

					if (DockPanel->ParentPanel)
					{
						List_Remove(&DockPanel->PanelEntry);
					}
					else
					{
						DockPanel->DockLayout->RootPanel = 0;
					}
				}

				ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
				while (Entry != &DockPanel->ChildPanels)
				{
					KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

					KekDockPanel_Update(ChildPanel);

					Entry = Entry->Next;
				}
			}
		}
	}
	void KekDockPanel_Draw(KekDockPanel* DockPanel, KekBatchMode BatchMode, float Depth)
	{
		Kek_DrawRectInternal(BatchMode, &DockPanel->TabRect, 0.0F, Depth, &DockPanel->BackgroundColor);
		Kek_DrawRectInternal(BatchMode, &DockPanel->PanelRect, 0.0F, Depth, &DockPanel->BackgroundColor);
		Depth += KEK_DEPTH_INCREMENT;

		Kek_DrawTextInternal(BatchMode, &DockPanel->TabRect, 0.0F, Depth, 20.0F, &DockPanel->TextColor, DockPanel->Title);
		Depth += KEK_DEPTH_INCREMENT;

		ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
		while (Entry != &DockPanel->ChildPanels)
		{
			KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

			KekDockPanel_Draw(ChildPanel, BatchMode, Depth + KEK_DEPTH_INCREMENT);

			Entry = Entry->Next;
		}
	}
	void KekDockPanel_PrintTree(KekDockPanel* DockPanel, int unsigned NumIdentSteps)
	{
		for (int unsigned IdentStep = 0; IdentStep < NumIdentSteps; IdentStep++)
		{
			printf("\t");
		}

		printf("DockPanel ");

		switch (DockPanel->Type)
		{
		case KEK_DOCK_PANEL_TYPE_WINDOW: printf("WINDOW"); break;
		case KEK_DOCK_PANEL_TYPE_HORIZONTAL: printf("HORIZONTAL"); break;
		case KEK_DOCK_PANEL_TYPE_VERTICAL: printf("VERTICAL"); break;
		}

		printf("\n");

		if (DockPanel->Node)
		{
			KekNode_PrintTree(DockPanel->Node, NumIdentSteps + 1);
		}

		ListEntry* Entry = LIST_FIRST_ENTRY(DockPanel->ChildPanels);
		while (Entry != &DockPanel->ChildPanels)
		{
			KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

			KekDockPanel_PrintTree(ChildPanel, NumIdentSteps + 1);

			Entry = Entry->Next;
		}
	}
	void KekDockLayout_Alloc(KekDockLayout* DockLayout, Rect const* Rect)
	{
		memset(DockLayout, 0, sizeof(KekDockLayout));

		DockLayout->Node.Class = KEK_NODE_CLASS_DOCK_ROOT;
		DockLayout->RootPanel = KekDockPanel_Alloc(DockLayout, 0, "Root", 0);

		Rect_Set(Rect, &DockLayout->Node.Rect);
	}
	KekDockPanel* KekDockLayout_Insert(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title)
	{
		if (!DockPanel)
		{
			DockPanel = DockLayout->RootPanel;
		}

		KekDockPanel* ChildPanel = KekDockPanel_Insert(DockPanel, Title);

		List_InsertTail(&DockPanel->ChildPanels, &ChildPanel->PanelEntry);

		KekDockPanel_UpdateRect(DockPanel, 0);

		DockPanel->ActivePanel = ChildPanel;

		return ChildPanel;
	}
	KekDockPanel* KekDockLayout_InsertLeft(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title)
	{
		if (!DockPanel)
		{
			DockPanel = DockLayout->RootPanel;
		}

		KekDockPanel* ChildPanel = KekDockPanel_InsertLeft(DockPanel, Title);

		List_InsertTail(&DockPanel->ChildPanels, &ChildPanel->PanelEntry);

		KekDockPanel_UpdateRect(DockPanel, 0);

		DockPanel->ActivePanel = ChildPanel;

		return ChildPanel;
	}
	KekDockPanel* KekDockLayout_InsertRight(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title)
	{
		if (!DockPanel)
		{
			DockPanel = DockLayout->RootPanel;
		}

		KekDockPanel* ChildPanel = KekDockPanel_InsertRight(DockPanel, Title);

		List_InsertTail(&DockPanel->ChildPanels, &ChildPanel->PanelEntry);

		KekDockPanel_UpdateRect(DockPanel, 0);

		DockPanel->ActivePanel = ChildPanel;

		return ChildPanel;
	}
	KekDockPanel* KekDockLayout_InsertTop(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title)
	{
		if (!DockPanel)
		{
			DockPanel = DockLayout->RootPanel;
		}

		KekDockPanel* ChildPanel = KekDockPanel_InsertTop(DockPanel, Title);

		List_InsertTail(&DockPanel->ChildPanels, &ChildPanel->PanelEntry);

		KekDockPanel_UpdateRect(DockPanel, 0);

		DockPanel->ActivePanel = ChildPanel;

		return ChildPanel;
	}
	KekDockPanel* KekDockLayout_InsertBottom(KekDockLayout* DockLayout, KekDockPanel* DockPanel, char const* Title)
	{
		if (!DockPanel)
		{
			DockPanel = DockLayout->RootPanel;
		}

		KekDockPanel* ChildPanel = KekDockPanel_InsertBottom(DockPanel, Title);

		List_InsertTail(&DockPanel->ChildPanels, &ChildPanel->PanelEntry);

		KekDockPanel_UpdateRect(DockPanel, 0);

		DockPanel->ActivePanel = ChildPanel;

		return ChildPanel;
	}
	void KekDockLayout_DragUpdate(KekDockLayout* DockLayout)
	{
		if (DockLayout->DragPanel)
		{
			if (Window_IsMouseKeyHeld(MOUSE_KEY_LEFT))
			{
				Rect* ParentRect = (DockLayout->DragPanel->ParentPanel) ? &DockLayout->DragPanel->ParentPanel->PanelRect : &DockLayout->DragPanel->DockLayout->Node.Rect;

				Rect TabRect = { 0 };
				TabRect.Left = (float)sMousePositionX - DockLayout->DragOffsetX;
				TabRect.Right = TabRect.Left + sKekStyle.DockTabWidth;
				TabRect.Top = (float)sMousePositionY - DockLayout->DragOffsetY;
				TabRect.Bottom = TabRect.Top + sKekStyle.DockTabHeight;

				Rect PanelRect = { 0 };
				PanelRect.Left = (float)sMousePositionX - DockLayout->DragOffsetX;
				PanelRect.Right = PanelRect.Left + Rect_Width(ParentRect);
				PanelRect.Top = (float)sMousePositionY - DockLayout->DragOffsetY + sKekStyle.DockTabHeight;
				PanelRect.Bottom = PanelRect.Top + Rect_Height(ParentRect) - sKekStyle.DockTabHeight;

				Rect_Set(&TabRect, &DockLayout->DragPanel->TabRect);
				Rect_Set(&PanelRect, &DockLayout->DragPanel->PanelRect);

				int unsigned ChildIndex = 0;
				ListEntry* Entry = LIST_FIRST_ENTRY(DockLayout->DragPanel->ChildPanels);
				while (Entry != &DockLayout->DragPanel->ChildPanels)
				{
					KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

					KekDockPanel_UpdateRect(ChildPanel, ChildIndex);

					ChildIndex += 1;
					Entry = Entry->Next;
				}
			}
			else if (Window_IsMouseKeyReleased(MOUSE_KEY_LEFT))
			{
				if (DockLayout->DragPanel->ParentPanel)
				{
					List_InsertTail(&DockLayout->DragPanel->ParentPanel->ChildPanels, &DockLayout->DragPanel->PanelEntry);

					int unsigned ChildIndex = 0;
					ListEntry* Entry = LIST_FIRST_ENTRY(DockLayout->DragPanel->ParentPanel->ChildPanels);
					while (Entry != &DockLayout->DragPanel->ParentPanel->ChildPanels)
					{
						KekDockPanel* ChildPanel = BASE_OF(Entry, KekDockPanel, PanelEntry);

						KekDockPanel_UpdateRect(ChildPanel, ChildIndex);

						ChildIndex += 1;
						Entry = Entry->Next;
					}
				}
				else
				{
					DockLayout->RootPanel = DockLayout->DragPanel;

					KekDockPanel_UpdateRect(DockLayout->DragPanel, 0);
				}

				DockLayout->DragPanel = 0;
			}
		}
	}
	void KekDockLayout_Resize(KekDockLayout* DockLayout)
	{
		UNREFERENCED_PARAMETER(DockLayout);
	}
	void KekDockLayout_Update(KekDockLayout* DockLayout)
	{
		if (DockLayout->RootPanel)
		{
			KekDockPanel_Update(DockLayout->RootPanel);
		}
		
		KekDockLayout_DragUpdate(DockLayout);
	}
	void KekDockLayout_Draw(KekDockLayout* DockLayout, KekBatchMode BatchMode, float Depth)
	{
		if (DockLayout->RootPanel)
		{
			KekDockPanel_Draw(DockLayout->RootPanel, BatchMode, Depth + KEK_DEPTH_INCREMENT);
		}

		if (DockLayout->DragPanel)
		{
			KekDockPanel_Draw(DockLayout->DragPanel, BatchMode, Depth);
		}
	}
	void KekDockLayout_Free(KekDockLayout* DockLayout)
	{
		UNREFERENCED_PARAMETER(DockLayout);
	}
	void KekDockLayout_PrintTree(KekDockLayout* DockLayout, int unsigned NumIdentSteps)
	{
		printf("DockLayout\n");

		KekDockPanel_PrintTree(DockLayout->RootPanel, NumIdentSteps + 1);
	}
	void KekListLayout_Alloc(KekListLayout* ListLayout, Rect const* Rect)
	{
		memset(ListLayout, 0, sizeof(KekListLayout));

		ListLayout->Node.Class = KEK_NODE_CLASS_LIST_LAYOUT;

		Rect_Set(Rect, &ListLayout->Node.Rect);
	}
	void KekListLayout_Update(KekListLayout* ListLayout)
	{
		UNREFERENCED_PARAMETER(ListLayout);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekListLayout_Resize(KekListLayout* ListLayout)
	{
		UNREFERENCED_PARAMETER(ListLayout);
	}
	void KekListLayout_Draw(KekListLayout* ListLayout, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(ListLayout);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekListLayout_Free(KekListLayout* ListLayout)
	{
		UNREFERENCED_PARAMETER(ListLayout);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekListLayout_PrintTree(KekListLayout* ListLayout, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(ListLayout);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("ListLayout\n");
	}
	void KekGridLayout_Alloc(KekGridLayout* GridLayout, Rect const* Rect)
	{
		memset(GridLayout, 0, sizeof(KekGridLayout));

		GridLayout->Node.Class = KEK_NODE_CLASS_GRID_LAYOUT;

		Rect_Set(Rect, &GridLayout->Node.Rect);
	}
	void KekGridLayout_Resize(KekGridLayout* GridLayout)
	{
		UNREFERENCED_PARAMETER(GridLayout);
	}
	void KekGridLayout_Update(KekGridLayout* GridLayout)
	{
		UNREFERENCED_PARAMETER(GridLayout);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekGridLayout_Draw(KekGridLayout* GridLayout, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(GridLayout);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekGridLayout_Free(KekGridLayout* GridLayout)
	{
		UNREFERENCED_PARAMETER(GridLayout);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekGridLayout_PrintTree(KekGridLayout* GridLayout, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(GridLayout);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("GridLayout\n");
	}
	void KekToolBar_Alloc(KekToolBar* ToolBar, Rect const* Rect)
	{
		memset(ToolBar, 0, sizeof(KekToolBar));

		ToolBar->Node.Class = KEK_NODE_CLASS_TOOL_BAR;

		Rect_Set(Rect, &ToolBar->Node.Rect);
	}
	void KekToolBar_Update(KekToolBar* ToolBar)
	{
		UNREFERENCED_PARAMETER(ToolBar);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekToolBar_Draw(KekToolBar* ToolBar, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(ToolBar);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekToolBar_Free(KekToolBar* ToolBar)
	{
		UNREFERENCED_PARAMETER(ToolBar);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekToolBar_PrintTree(KekToolBar* ToolBar, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(ToolBar);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("ToolBar\n");
	}
	void KekImage_Alloc(KekImage* Image, Rect const* Rect)
	{
		memset(Image, 0, sizeof(KekImage));

		Image->Node.Class = KEK_NODE_CLASS_IMAGE;

		Rect_Set(Rect, &Image->Node.Rect);
	}
	void KekImage_Update(KekImage* Image)
	{
		UNREFERENCED_PARAMETER(Image);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekImage_Draw(KekImage* Image, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(Image);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekImage_Free(KekImage* Image)
	{
		UNREFERENCED_PARAMETER(Image);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekImage_PrintTree(KekImage* Image, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(Image);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("Image\n");
	}
	void KekButton_Alloc(KekButton* Button, Rect const* Rect)
	{
		memset(Button, 0, sizeof(KekButton));

		Button->Node.Class = KEK_NODE_CLASS_BUTTON;

		Rect_Set(Rect, &Button->Node.Rect);
	}
	void KekButton_Update(KekButton* Button)
	{
		UNREFERENCED_PARAMETER(Button);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekButton_Draw(KekButton* Button, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(Button);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekButton_Free(KekButton* Button)
	{
		UNREFERENCED_PARAMETER(Button);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekButton_PrintTree(KekButton* Button, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(Button);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("Button\n");
	}
	void KekSlider_Alloc(KekSlider* Slider, Rect const* Rect)
	{
		memset(Slider, 0, sizeof(KekSlider));

		Slider->Node.Class = KEK_NODE_CLASS_SLIDER;

		Rect_Set(Rect, &Slider->Node.Rect);
	}
	void KekSlider_Update(KekSlider* Slider)
	{
		UNREFERENCED_PARAMETER(Slider);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekSlider_Draw(KekSlider* Slider, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(Slider);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekSlider_Free(KekSlider* Slider)
	{
		UNREFERENCED_PARAMETER(Slider);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekSlider_PrintTree(KekSlider* Slider, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(Slider);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("Slider\n");
	}
	void KekViewPort_Alloc(KekViewPort* ViewPort, Rect const* Rect)
	{
		memset(ViewPort, 0, sizeof(KekViewPort));

		ViewPort->Node.Class = KEK_NODE_CLASS_VIEW_PORT;

		Rect_Set(Rect, &ViewPort->Node.Rect);
	}
	void KekViewPort_Update(KekViewPort* ViewPort)
	{
		UNREFERENCED_PARAMETER(ViewPort);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekViewPort_Draw(KekViewPort* ViewPort, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(ViewPort);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekViewPort_Free(KekViewPort* ViewPort)
	{
		UNREFERENCED_PARAMETER(ViewPort);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekViewPort_PrintTree(KekViewPort* ViewPort, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(ViewPort);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("ViewPort\n");
	}
	void KekTest_Alloc(KekTest* Test, Rect const* Rect)
	{
		memset(Test, 0, sizeof(KekTest));

		Test->Node.Class = KEK_NODE_CLASS_TEST;

		Rect_Set(Rect, &Test->Node.Rect);
	}
	void KekTest_Update(KekTest* Test)
	{
		UNREFERENCED_PARAMETER(Test);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekTest_Draw(KekTest* Test, KekBatchMode BatchMode, float Depth)
	{
		UNREFERENCED_PARAMETER(Test);
		UNREFERENCED_PARAMETER(BatchMode);
		UNREFERENCED_PARAMETER(Depth);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekTest_Free(KekTest* Test)
	{
		UNREFERENCED_PARAMETER(Test);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void KekTest_PrintTree(KekTest* Test, int unsigned NumIdentSteps)
	{
		UNREFERENCED_PARAMETER(Test);
		UNREFERENCED_PARAMETER(NumIdentSteps);

		printf("Test\n");
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Histogram Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Histogram_Alloc(Histogram* Histgrm, SpriteMesh* Mesh, char* Name, HistogramScaleType ScaleType, int unsigned NumSamples, int unsigned Scale, int unsigned DisplayInterval)
	{
		memset(Histgrm, 0, sizeof(Histogram));

		Histgrm->Mesh = Mesh;
		Histgrm->Samples = (float*)Memory_Alloc(NumSamples * sizeof(float), 0);
		memcpy(Histgrm->Name, Name, 0xFF);
		Histgrm->ScaleType = ScaleType;
		Histgrm->NumSamples = NumSamples;
		Histgrm->Scale = Scale;
		Histgrm->DisplayInterval = 1.0F / (float)DisplayInterval;

		for (int unsigned SampleIndex = 0; SampleIndex < NumSamples; SampleIndex++)
		{
			Histgrm->Samples[SampleIndex] = 0.0F;
		}

		Buffer_StorageAllocSimple(&Histgrm->SampleBuffer, NumSamples * sizeof(float), Histgrm->Samples, GL_DYNAMIC_DRAW);

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedHistograms += 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
	void Histogram_PushSample(Histogram* Histgrm, double Sample)
	{
		float NextSample = 0.0F;

		switch (Histgrm->ScaleType)
		{
		case HISTOGRAM_SCALE_NS: NextSample = (float)(Sample / 1000000.0); break;
		case HISTOGRAM_SCALE_US: NextSample = (float)(Sample / 1000.0); break;
		case HISTOGRAM_SCALE_MS: NextSample = (float)(Sample); break;
		}
		Histgrm->Accumulator -= Histgrm->Samples[Histgrm->SampleIndex];
		Histgrm->Accumulator += NextSample;
		Histgrm->Samples[Histgrm->SampleIndex] = NextSample;
		Histgrm->SampleIndex += 1;

		if (Histgrm->SampleIndex >= Histgrm->NumSamples)
		{
			Histgrm->SampleIndex = 0;
		}

		Buffer_StorageBind(Histgrm->SampleBuffer);
		Buffer_StorageSetData(Histgrm->Samples, Histgrm->NumSamples * sizeof(float));
		Buffer_StorageUnBind();
	}
	void Histogram_Draw(Histogram* Histgrm, Vector3 const* Position, float Rotation, Vector2 const* Size)
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };

		Shader_Bind(sHistogramProgram);
		Shader_SetUniformVector2(sHistogramProgram, "ScreenSize", &ScreenSize);
		Shader_SetUniformVector3(sHistogramProgram, "Position", Position);
		Shader_SetUniformReal32(sHistogramProgram, "Rotation", Rotation);
		Shader_SetUniformVector2(sHistogramProgram, "Size", Size);
		Shader_SetUniformUInt32(sHistogramProgram, "NumSamples", Histgrm->NumSamples);
		Shader_SetUniformUInt32(sHistogramProgram, "CurrIndex", Histgrm->SampleIndex);
		Shader_SetUniformUInt32(sHistogramProgram, "Scale", Histgrm->Scale);

		Buffer_StorageMount(Histgrm->SampleBuffer, 0);

		int unsigned VertexArray = Primitive_GetSpriteVertexArray(Histgrm->Mesh);
		VertexArray_Bind(VertexArray);
		VertexArray_DrawTriangleStrip(4);
		VertexArray_UnBind();

		float LineHeight = Font_LineHeight(&sDefaultFont) * 10.0F;

		Text_BeginScreen(&sDefaultFont);
		Text_DrawScreenSimple(Position->X + Size->X + 10.0F, Position->Y, Position->Z, 0.0F, 10.0F, 1.0F, 1.0F, 1.0F, 1.0F, Histgrm->Name);
		Text_DrawScreenSimple(Position->X + Size->X + 10.0F, Position->Y + LineHeight, Position->Z, 0.0F, 10.0F, 1.0F, 1.0F, 1.0F, 1.0F, "Max %u", Histgrm->Scale);
		Text_DrawScreenSimple(Position->X + Size->X + 10.0F, Position->Y + LineHeight + LineHeight, Position->Z, 0.0F, 10.0F, 1.0F, 1.0F, 1.0F, 1.0F, "Avg %u", Histgrm->AvgDelta);
		Text_EndScreen();

		if (Histgrm->DisplayIntervalAcc > 1.0F)
		{
			Histgrm->DisplayIntervalAcc = 0.0F;
			Histgrm->AvgDelta = (int unsigned)(Histgrm->Accumulator / (float)Histgrm->NumSamples);
		}

		Histgrm->DisplayIntervalAcc += Histgrm->DisplayInterval;
	}
	void Histogram_DrawSimple(Histogram* Histgrm, float PositionX, float PositionY, float PositionZ, float Rotation, float Width, float Height)
	{
		Vector2 ScreenSize = { (float)sWindowWidth, (float)sWindowHeight };
		Vector3 Position = { PositionX, PositionY, PositionZ };
		Vector2 Size = { Width, Height };

		Shader_Bind(sHistogramProgram);
		Shader_SetUniformVector2(sHistogramProgram, "ScreenSize", &ScreenSize);
		Shader_SetUniformVector3(sHistogramProgram, "Position", &Position);
		Shader_SetUniformReal32(sHistogramProgram, "Rotation", Rotation);
		Shader_SetUniformVector2(sHistogramProgram, "Size", &Size);
		Shader_SetUniformUInt32(sHistogramProgram, "NumSamples", Histgrm->NumSamples);
		Shader_SetUniformUInt32(sHistogramProgram, "CurrIndex", Histgrm->SampleIndex);
		Shader_SetUniformUInt32(sHistogramProgram, "Scale", Histgrm->Scale);

		Buffer_StorageMount(Histgrm->SampleBuffer, 0);

		int unsigned VertexArray = Primitive_GetSpriteVertexArray(Histgrm->Mesh);
		VertexArray_Bind(VertexArray);
		VertexArray_DrawTriangleStrip(4);
		VertexArray_UnBind();

		float LineHeight = Font_LineHeight(&sDefaultFont) * 10.0F;

		Text_BeginScreen(&sDefaultFont);
		Text_DrawScreenSimple(PositionX + Width + 10.0F, PositionY, PositionZ, 0.0F, 10.0F, 1.0F, 1.0F, 1.0F, 1.0F, Histgrm->Name);
		Text_DrawScreenSimple(PositionX + Width + 10.0F, PositionY + LineHeight, PositionZ, 0.0F, 10.0F, 1.0F, 1.0F, 1.0F, 1.0F, "Max %u", Histgrm->Scale);
		Text_DrawScreenSimple(PositionX + Width + 10.0F, PositionY + LineHeight + LineHeight, PositionZ, 0.0F, 10.0F, 1.0F, 1.0F, 1.0F, 1.0F, "Avg %u", Histgrm->AvgDelta);
		Text_EndScreen();

		if (Histgrm->DisplayIntervalAcc > 1.0F)
		{
			Histgrm->DisplayIntervalAcc = 0.0F;
			Histgrm->AvgDelta = (int unsigned)(Histgrm->Accumulator / (float)Histgrm->NumSamples);
		}

		Histgrm->DisplayIntervalAcc += Histgrm->DisplayInterval;
	}
	void Histogram_Free(Histogram* Histgrm)
	{
		Buffer_Free(Histgrm->SampleBuffer);
		Memory_Free(Histgrm->Samples);

		memset(Histgrm, 0, sizeof(Histogram));

#ifdef FAST_GL_REFERENCE_COUNT
		sAllocatedHistograms -= 1;
#endif // FAST_GL_REFERENCE_COUNT
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Window Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Window_Alloc(int unsigned Width, int unsigned Height, char const* WindowTitle)
	{
		sModuleInstance = GetModuleHandle(0);

		WNDCLASS WindowClass = { 0 };
		WindowClass.lpfnWndProc = Window_CallbackInternal;
		WindowClass.hInstance = sModuleInstance;
		WindowClass.lpszClassName = sWindowClassName;
		RegisterClass(&WindowClass);

		sWindowHandle = CreateWindowEx(
			0,
			sWindowClassName,
			WindowTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			(int)Width,
			(int)Height,
			0,
			0,
			sModuleInstance,
			0);

		ShowWindow(sWindowHandle, SW_SHOW);

		sDeviceContext = GetDC(sWindowHandle);

		PIXELFORMATDESCRIPTOR PixelFormatDescriptor = { 0 };
		PixelFormatDescriptor.nSize = sizeof(PixelFormatDescriptor);
		PixelFormatDescriptor.nVersion = 1;
		PixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		PixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
		PixelFormatDescriptor.cColorBits = 32;
		PixelFormatDescriptor.cDepthBits = 24;
		PixelFormatDescriptor.cStencilBits = 8;
		PixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

		int PixelFormat = ChoosePixelFormat(sDeviceContext, &PixelFormatDescriptor);
		SetPixelFormat(sDeviceContext, PixelFormat, &PixelFormatDescriptor);

		sOpenGLInstance = LoadLibrary("opengl32.dll");

		glCreateContext = (glCreateContext_PROC)GetProcAddress(sOpenGLInstance, "wglCreateContext");
		glMakeCurrent = (glMakeCurrent_PROC)GetProcAddress(sOpenGLInstance, "wglMakeCurrent");
		glGetProcAddress = (glGetProcAddress_PROC)GetProcAddress(sOpenGLInstance, "wglGetProcAddress");
		glDeleteContext = (glDeleteContext_PROC)GetProcAddress(sOpenGLInstance, "wglDeleteContext");

		sGraphicsContext = glCreateContext(sDeviceContext);

		glMakeCurrent(sDeviceContext, sGraphicsContext);

		glDebugMessageCallback = (glDebugMessageCallback_PROC)glGetProcAddress("glDebugMessageCallback");
		glGetQueryObjectui64v = (glGetQueryObjectui64v_PROC)glGetProcAddress("glGetQueryObjectui64v");
		glGenQueries = (glGenQueries_PROC)glGetProcAddress("glGenQueries");
		glBeginQuery = (glBeginQuery_PROC)glGetProcAddress("glBeginQuery");
		glEndQuery = (glEndQuery_PROC)glGetProcAddress("glEndQuery");
		glDeleteQueries = (glDeleteQueries_PROC)glGetProcAddress("glDeleteQueries");
		glClearBufferfv = (glClearBufferfv_PROC)glGetProcAddress("glClearBufferfv");
		glClearBufferiv = (glClearBufferiv_PROC)glGetProcAddress("glClearBufferiv");
		glBlendFunci = (glBlendFunci_PROC)glGetProcAddress("glBlendFunci");
		glBlendEquation = (glBlendEquation_PROC)glGetProcAddress("glBlendEquation");
		glMemoryBarrier = (glMemoryBarrier_PROC)glGetProcAddress("glMemoryBarrier");
		glDrawElementsInstanced = (glDrawElementsInstanced_PROC)glGetProcAddress("glDrawElementsInstanced");
		glDrawArraysInstanced = (glDrawArraysInstanced_PROC)glGetProcAddress("glDrawArraysInstanced");
		glCreateProgram = (glCreateProgram_PROC)glGetProcAddress("glCreateProgram");
		glCreateShader = (glCreateShader_PROC)glGetProcAddress("glCreateShader");
		glShaderSource = (glShaderSource_PROC)glGetProcAddress("glShaderSource");
		glCompileShader = (glCompileShader_PROC)glGetProcAddress("glCompileShader");
		glAttachShader = (glAttachShader_PROC)glGetProcAddress("glAttachShader");
		glLinkProgram = (glLinkProgram_PROC)glGetProcAddress("glLinkProgram");
		glDeleteShader = (glDeleteShader_PROC)glGetProcAddress("glDeleteShader");
		glUseProgram = (glUseProgram_PROC)glGetProcAddress("glUseProgram");
		glDeleteProgram = (glDeleteProgram_PROC)glGetProcAddress("glDeleteProgram");
		glUniform1f = (glUniform1f_PROC)glGetProcAddress("glUniform1f");
		glUniform2fv = (glUniform2fv_PROC)glGetProcAddress("glUniform2fv");
		glUniform3fv = (glUniform3fv_PROC)glGetProcAddress("glUniform3fv");
		glUniform4fv = (glUniform4fv_PROC)glGetProcAddress("glUniform4fv");
		glGetUniformLocation = (glGetUniformLocation_PROC)glGetProcAddress("glGetUniformLocation");
		glUniform1i = (glUniform1i_PROC)glGetProcAddress("glUniform1i");
		glUniform1ui = (glUniform1ui_PROC)glGetProcAddress("glUniform1ui");
		glUniformMatrix4fv = (glUniformMatrix4fv_PROC)glGetProcAddress("glUniformMatrix4fv");
		glDispatchCompute = (glDispatchCompute_PROC)glGetProcAddress("glDispatchCompute");
		glGetShaderiv = (glGetShaderiv_PROC)glGetProcAddress("glGetShaderiv");
		glGetShaderInfoLog = (glGetShaderInfoLog_PROC)glGetProcAddress("glGetShaderInfoLog");
		glGetProgramiv = (glGetProgramiv_PROC)glGetProcAddress("glGetProgramiv");
		glGetProgramInfoLog = (glGetProgramInfoLog_PROC)glGetProcAddress("glGetProgramInfoLog");
		glGenVertexArrays = (glGenVertexArrays_PROC)glGetProcAddress("glGenVertexArrays");
		glDeleteVertexArrays = (glDeleteVertexArrays_PROC)glGetProcAddress("glDeleteVertexArrays");
		glBindVertexArray = (glBindVertexArray_PROC)glGetProcAddress("glBindVertexArray");
		glEnableVertexAttribArray = (glEnableVertexAttribArray_PROC)glGetProcAddress("glEnableVertexAttribArray");
		glVertexAttribDivisor = (glVertexAttribDivisor_PROC)glGetProcAddress("glVertexAttribDivisor");
		glVertexAttribPointer = (glVertexAttribPointer_PROC)glGetProcAddress("glVertexAttribPointer");
		glVertexAttribIPointer = (glVertexAttribIPointer_PROC)glGetProcAddress("glVertexAttribIPointer");
		glGenBuffers = (glGenBuffers_PROC)glGetProcAddress("glGenBuffers");
		glBindBuffer = (glBindBuffer_PROC)glGetProcAddress("glBindBuffer");
		glBufferData = (glBufferData_PROC)glGetProcAddress("glBufferData");
		glBufferStorage = (glBufferStorage_PROC)glGetProcAddress("glBufferStorage");
		glDeleteBuffers = (glDeleteBuffers_PROC)glGetProcAddress("glDeleteBuffers");
		glBufferSubData = (glBufferSubData_PROC)glGetProcAddress("glBufferSubData");
		glGetBufferSubData = (glGetBufferSubData_PROC)glGetProcAddress("glGetBufferSubData");
		glBindBufferBase = (glBindBufferBase_PROC)glGetProcAddress("glBindBufferBase");
		glMapBuffer = (glMapBuffer_PROC)glGetProcAddress("glMapBuffer");
		glMapBufferRange = (glMapBufferRange_PROC)glGetProcAddress("glMapBufferRange");
		glUnmapBuffer = (glUnmapBuffer_PROC)glGetProcAddress("glUnmapBuffer");
		glBindTextureUnit = (glBindTextureUnit_PROC)glGetProcAddress("glBindTextureUnit");
		glBindImageTexture = (glBindImageTexture_PROC)glGetProcAddress("glBindImageTexture");
		glGenerateMipmap = (glGenerateMipmap_PROC)glGetProcAddress("glGenerateMipmap");
		glGenFramebuffers = (glGenFramebuffers_PROC)glGetProcAddress("glGenFramebuffers");
		glBindFramebuffer = (glBindFramebuffer_PROC)glGetProcAddress("glBindFramebuffer");
		glFramebufferParameteri = (glFramebufferParameteri_PROC)glGetProcAddress("glFramebufferParameteri");
		glFramebufferTexture2D = (glFramebufferTexture2D_PROC)glGetProcAddress("glFramebufferTexture2D");
		glDrawBuffers = (glDrawBuffers_PROC)glGetProcAddress("glDrawBuffers");
		glDeleteFramebuffers = (glDeleteFramebuffers_PROC)glGetProcAddress("glDeleteFramebuffers");

#ifdef FAST_GL_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(Window_GLDebugCallbackInternal, 0);
#endif // FAST_GL_DEBUG

		Shader_VertexFragmentAlloc(&sWorldCircleProgram, sWorldCircleVertexShader, sWorldCircleFragmentShader);
		Shader_VertexGeometryFragmentAlloc(&sWorldLineProgram, sWorldLineVertexShader, sWorldLineGeometryShader, sWorldLineFragmentShader);
		Shader_VertexFragmentAlloc(&sWorldRectProgram, sWorldRectVertexShader, sWorldRectFragmentShader);

		Shader_VertexFragmentAlloc(&sScreenCircleProgram, sScreenCircleVertexShader, sScreenCircleFragmentShader);
		Shader_VertexGeometryFragmentAlloc(&sScreenLineProgram, sScreenLineVertexShader, sScreenLineGeometryShader, sScreenLineFragmentShader);
		Shader_VertexFragmentAlloc(&sScreenRectProgram, sScreenRectVertexShader, sScreenRectFragmentShader);

		Shader_VertexFragmentAlloc(&sWorldFontProgram, sWorldFontVertexShader, sWorldFontFragmentShader);
		Shader_VertexFragmentAlloc(&sScreenFontProgram, sScreenFontVertexShader, sScreenFontFragmentShader);

		Shader_VertexFragmentAlloc(&sHistogramProgram, sHistogramVertexShader, sHistogramFragmentShader);

		Font_AllocFromMemory(&sDefaultFont, 1000, sDefaultFontBytes, sizeof(sDefaultFontBytes));

		sWindowReady = true;
	}
	bool Window_ShouldClose(void)
	{
		return sWindowShouldClose;
	}
	void Window_PollEvents(void)
	{
		sWheelDelta = 0;

		for (char unsigned KeyIndex = 0; KeyIndex < 0xFF; KeyIndex++)
		{
			if (sKeyboardKeyStates[KeyIndex] == KEYBOARD_KEY_STATE_PRESSED)
			{
				sKeyboardKeyStates[KeyIndex] = KEYBOARD_KEY_STATE_DOWN;
			}
			else if (sKeyboardKeyStates[KeyIndex] == KEYBOARD_KEY_STATE_RELEASED)
			{
				sKeyboardKeyStates[KeyIndex] = KEYBOARD_KEY_STATE_UP;
			}
		}

		for (char unsigned KeyIndex = 0; KeyIndex < 0x3; KeyIndex++)
		{
			if (sMouseKeyStates[KeyIndex] == MOUSE_KEY_STATE_PRESSED)
			{
				sMouseKeyStates[KeyIndex] = MOUSE_KEY_STATE_DOWN;
			}
			else if (sMouseKeyStates[KeyIndex] == MOUSE_KEY_STATE_RELEASED)
			{
				sMouseKeyStates[KeyIndex] = MOUSE_KEY_STATE_UP;
			}
		}

		while (PeekMessage(&sWindowMessage, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&sWindowMessage);
			DispatchMessage(&sWindowMessage);
		}
	}
	void Window_SwapBuffers(void)
	{
		SwapBuffers(sDeviceContext);
	}
	void Window_ToNDC(float* X, float* Y)
	{
		*X = 2.0F * ((float)sMousePositionX / (float)sWindowWidth) - 1.0F;
		*Y = 1.0F - 2.0F * ((float)sMousePositionY / (float)sWindowHeight);
	}
	int Window_GetWidth(void)
	{
		return sWindowWidth;
	}
	int Window_GetHeight(void)
	{
		return sWindowHeight;
	}
	int Window_GetMousePositionX(void)
	{
		return sMousePositionX;
	}
	int Window_GetMousePositionY(void)
	{
		return sMousePositionY;
	}
	bool Window_IsKeyboardKeyPressed(KeyboardKey Key)
	{
		return sKeyboardKeyStates[Key] == KEYBOARD_KEY_STATE_PRESSED;
	}
	bool Window_IsKeyboardKeyHeld(KeyboardKey Key)
	{
		return (sKeyboardKeyStates[Key] == KEYBOARD_KEY_STATE_DOWN) || (sKeyboardKeyStates[Key] == KEYBOARD_KEY_STATE_PRESSED);
	}
	bool Window_IsKeyboardKeyReleased(KeyboardKey Key)
	{
		return sKeyboardKeyStates[Key] == KEYBOARD_KEY_STATE_RELEASED;
	}
	bool Window_IsMouseKeyPressed(MouseKey Key)
	{
		return sMouseKeyStates[Key] == MOUSE_KEY_STATE_PRESSED;
	}
	bool Window_IsMouseKeyHeld(MouseKey Key)
	{
		return (sMouseKeyStates[Key] == MOUSE_KEY_STATE_DOWN) || (sMouseKeyStates[Key] == MOUSE_KEY_STATE_PRESSED);
	}
	bool Window_IsMouseKeyReleased(MouseKey Key)
	{
		return sMouseKeyStates[Key] == MOUSE_KEY_STATE_RELEASED;
	}
	void Window_Free(void)
	{
		Font_Free(&sDefaultFont);

		Shader_Free(sWorldCircleProgram);
		Shader_Free(sWorldLineProgram);
		Shader_Free(sWorldRectProgram);

		Shader_Free(sScreenCircleProgram);
		Shader_Free(sScreenLineProgram);
		Shader_Free(sScreenRectProgram);

		Shader_Free(sWorldFontProgram);
		Shader_Free(sScreenFontProgram);

		Shader_Free(sHistogramProgram);

		glMakeCurrent(0, 0);
		glDeleteContext(sGraphicsContext);

		FreeLibrary(sOpenGLInstance);
		ReleaseDC(sWindowHandle, sDeviceContext);
		DestroyWindow(sWindowHandle);

#ifdef FAST_GL_REFERENCE_COUNT
		assert(sAllocatedBytes == 0);
		assert(sAllocatedVectors == 0);
		assert(sAllocatedHashMaps == 0);
		assert(sAllocatedTimers == 0);
		assert(sAllocatedPrograms == 0);
		assert(sAllocatedVertexArrays == 0);
		assert(sAllocatedBuffers == 0);
		assert(sAllocatedBatches == 0);
		assert(sAllocatedFonts == 0);
		assert(sAllocatedTextCaches == 0);
		assert(sAllocatedTexture2Ds == 0);
		assert(sAllocatedFrameBuffers == 0);
		assert(sAllocatedBitMaps == 0);
		assert(sAllocatedPrimitives == 0);
		assert(sAllocatedPostProcessEffects == 0);
		assert(sAllocatedHistograms == 0);
#endif FAST_GL_REFERENCE_COUNT
	}
	LRESULT Window_CallbackInternal(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		switch (Message)
		{
		case WM_DESTROY:
		{
			sWindowShouldClose = true;

			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
			RECT ClientRect = { 0 };
			GetClientRect(WindowHandle, &ClientRect);

			int Width = ClientRect.right - ClientRect.left;
			int Height = ClientRect.bottom - ClientRect.top;

			if ((Width > 0) && (Height > 0))
			{
				sWindowWidth = Width;
				sWindowHeight = Height;
			}

			break;
		}
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			sKeyboardKeyStates[WParam] = ((sKeyboardKeyStates[WParam] == KEYBOARD_KEY_STATE_UP) || (sKeyboardKeyStates[WParam] == KEYBOARD_KEY_STATE_RELEASED)) ? KEYBOARD_KEY_STATE_PRESSED : KEYBOARD_KEY_STATE_DOWN;

			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			sKeyboardKeyStates[WParam] = ((sKeyboardKeyStates[WParam] == KEYBOARD_KEY_STATE_DOWN) || (sKeyboardKeyStates[WParam] == KEYBOARD_KEY_STATE_PRESSED)) ? KEYBOARD_KEY_STATE_RELEASED : KEYBOARD_KEY_STATE_UP;

			break;
		}
		case WM_LBUTTONDOWN:
		{
			sMouseKeyStates[MOUSE_KEY_LEFT] = ((sMouseKeyStates[MOUSE_KEY_LEFT] == MOUSE_KEY_STATE_UP) || (sMouseKeyStates[MOUSE_KEY_LEFT] == MOUSE_KEY_STATE_RELEASED)) ? MOUSE_KEY_STATE_PRESSED : MOUSE_KEY_STATE_DOWN;

			break;
		}
		case WM_LBUTTONUP:
		{
			sMouseKeyStates[MOUSE_KEY_LEFT] = ((sMouseKeyStates[MOUSE_KEY_LEFT] == MOUSE_KEY_STATE_DOWN) || (sMouseKeyStates[MOUSE_KEY_LEFT] == MOUSE_KEY_STATE_PRESSED)) ? MOUSE_KEY_STATE_RELEASED : MOUSE_KEY_STATE_UP;

			break;
		}
		case WM_MBUTTONDOWN:
		{
			sMouseKeyStates[MOUSE_KEY_MIDDLE] = ((sMouseKeyStates[MOUSE_KEY_MIDDLE] == MOUSE_KEY_STATE_UP) || (sMouseKeyStates[MOUSE_KEY_MIDDLE] == MOUSE_KEY_STATE_RELEASED)) ? MOUSE_KEY_STATE_PRESSED : MOUSE_KEY_STATE_DOWN;

			break;
		}
		case WM_MBUTTONUP:
		{
			sMouseKeyStates[MOUSE_KEY_MIDDLE] = ((sMouseKeyStates[MOUSE_KEY_MIDDLE] == MOUSE_KEY_STATE_DOWN) || (sMouseKeyStates[MOUSE_KEY_MIDDLE] == MOUSE_KEY_STATE_PRESSED)) ? MOUSE_KEY_STATE_RELEASED : MOUSE_KEY_STATE_UP;

			break;
		}
		case WM_RBUTTONDOWN:
		{
			sMouseKeyStates[MOUSE_KEY_RIGHT] = ((sMouseKeyStates[MOUSE_KEY_RIGHT] == MOUSE_KEY_STATE_UP) || (sMouseKeyStates[MOUSE_KEY_RIGHT] == MOUSE_KEY_STATE_RELEASED)) ? MOUSE_KEY_STATE_PRESSED : MOUSE_KEY_STATE_DOWN;

			break;
		}
		case WM_RBUTTONUP:
		{
			sMouseKeyStates[MOUSE_KEY_RIGHT] = ((sMouseKeyStates[MOUSE_KEY_RIGHT] == MOUSE_KEY_STATE_DOWN) || (sMouseKeyStates[MOUSE_KEY_RIGHT] == MOUSE_KEY_STATE_PRESSED)) ? MOUSE_KEY_STATE_RELEASED : MOUSE_KEY_STATE_UP;

			break;
		}
		case WM_LBUTTONDBLCLK:
		{
			break;
		}
		case WM_MBUTTONDBLCLK:
		{
			break;
		}
		case WM_RBUTTONDBLCLK:
		{
			break;
		}
		case WM_MOUSEMOVE:
		{
			int PositionX = LOWORD(LParam);
			int PositionY = HIWORD(LParam);

			sMousePositionX = PositionX;
			sMousePositionY = PositionY;

			break;
		}
		case WM_MOUSEWHEEL:
		{
			sWheelDelta = GET_WHEEL_DELTA_WPARAM(WParam);

			break;
		}
		}

		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}
	void Window_GLDebugCallbackInternal(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam)
	{
		UNREFERENCED_PARAMETER(Source);
		UNREFERENCED_PARAMETER(ID);
		UNREFERENCED_PARAMETER(Length);
		UNREFERENCED_PARAMETER(UserParam);
#ifdef FAST_GL_DEBUG
		switch (Severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION: break;
		case GL_DEBUG_SEVERITY_LOW: printf("Severity:Low Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_MEDIUM: printf("Severity:Medium Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_HIGH: printf("Severity:High Type:0x%x Message:%s\n", Type, Message); break;
		}
#else
		UNREFERENCED_PARAMETER(Severity);
		UNREFERENCED_PARAMETER(Type);
		UNREFERENCED_PARAMETER(Message);
#endif // FAST_GL_DEBUG
	}
#endif // FAST_GL_IMPLEMENTATION

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FAST_GL_H
