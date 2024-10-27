#pragma warning(disable : 4191)
#pragma warning(disable : 4668)
#pragma warning(disable : 4710)
#pragma warning(disable : 4711)
#pragma warning(disable : 4820)
#pragma warning(disable : 5039)
#pragma warning(disable : 5045)
#pragma warning(disable : 6011)
#pragma warning(disable : 6308)
#pragma warning(disable : 6387)
#pragma warning(disable : 28182)

#pragma comment(lib, "Opengl32.lib")

#ifndef FAST_GL_H
#define FAST_GL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#include <Windows.h>

#include <gl/GL.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	///////////////////////////////////////////////////////////////
	// Global Macros
	///////////////////////////////////////////////////////////////

#define STATIC_ASSERT(EXPRESSION, MESSAGE) typedef char static_assertion_##MESSAGE[(EXPRESSION) ? 1 : -1]

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

#define DEG2RAD(DEGREES) ((DEGREES) * 0.0174532F)
#define RAD2DEG(RADIANS) ((RADIANS) * 57.2957795F)

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
	// Platform Checks
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

	typedef HGLRC(__stdcall *glCreateContext_PROC)(HDC DeviceContext);
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

#define GL_DEBUG_OUTPUT 0x92E0
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_DEBUG_SEVERITY_LOW 0x9148
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT 0x00000002
#define GL_UNIFORM_BARRIER_BIT 0x00000004
#define GL_SHADER_STORAGE_BARRIER_BIT 0x00002000
#define GL_BUFFER_UPDATE_BARRIER_BIT 0x00000200
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_LINES_ADJACENCY 0x000A
#define GL_LINE_STRIP_ADJACENCY 0x000B
#define GL_TRIANGLES_ADJACENCY 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY 0x000D
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPUTE_SHADER 0x91B9
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_STREAM_DRAW 0x88E0
#define GL_STREAM_READ 0x88E1
#define GL_STREAM_COPY 0x88E2
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STATIC_COPY 0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_UNIFORM_BUFFER 0x8A11
#define GL_SHADER_STORAGE_BUFFER 0x90D2
#define GL_MAP_READ_BIT 0x0001
#define GL_MAP_WRITE_BIT 0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008

	typedef void(*glDebug_PROC)(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);
	typedef void(*glDebugMessageCallback_PROC)(glDebug_PROC Callback, void const* UserParam);
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
	typedef int unsigned(*glGetUniformLocation_PROC)(int unsigned Program, char const* Name);
	typedef void(*glUniform1f_PROC)(int unsigned Location, float Value);
	typedef void(*glUniformMatrix4fv_PROC)(int unsigned Location, int unsigned Count, char unsigned Transpose, float const* Value);
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
	typedef void(*glDeleteBuffers_PROC)(int unsigned Num, int unsigned const* Buffers);
	typedef void(*glBufferSubData_PROC)(int unsigned Target, int unsigned Offset, int unsigned Size, void const* Data);
	typedef void(*glBindBufferBase_PROC)(int unsigned Target, int unsigned Index, int unsigned Buffer);
	typedef void*(*glMapBuffer_PROC)(int unsigned Target, int unsigned Access);
	typedef void*(*glMapBufferRange_PROC)(int unsigned Target, int unsigned Offset, int unsigned Length, int unsigned Access);
	typedef char unsigned(*glUnmapBuffer_PROC)(int unsigned Target);

#ifdef FAST_GL_IMPLEMENTATION
	static glDebugMessageCallback_PROC glDebugMessageCallback = 0;
	static glMemoryBarrier_PROC glMemoryBarrier = 0;
	static glDrawElementsInstanced_PROC glDrawElementsInstanced = 0;
	static glDrawArraysInstanced_PROC glDrawArraysInstanced = 0;
	static glCreateProgram_PROC glCreateProgram = 0;
	static glCreateShader_PROC glCreateShader = 0;
	static glShaderSource_PROC glShaderSource = 0;
	static glCompileShader_PROC glCompileShader = 0;
	static glAttachShader_PROC glAttachShader = 0;
	static glLinkProgram_PROC glLinkProgram = 0;
	static glDeleteShader_PROC glDeleteShader = 0;
	static glUseProgram_PROC glUseProgram = 0;
	static glDeleteProgram_PROC glDeleteProgram = 0;
	static glGetUniformLocation_PROC glGetUniformLocation = 0;
	static glUniform1f_PROC glUniform1f = 0;
	static glUniformMatrix4fv_PROC glUniformMatrix4fv = 0;
	static glGetShaderiv_PROC glGetShaderiv = 0;
	static glGetShaderInfoLog_PROC glGetShaderInfoLog = 0;
	static glGetProgramiv_PROC glGetProgramiv = 0;
	static glGetProgramInfoLog_PROC glGetProgramInfoLog = 0;
	static glGenVertexArrays_PROC glGenVertexArrays = 0;
	static glDeleteVertexArrays_PROC glDeleteVertexArrays = 0;
	static glBindVertexArray_PROC glBindVertexArray = 0;
	static glEnableVertexAttribArray_PROC glEnableVertexAttribArray = 0;
	static glVertexAttribDivisor_PROC glVertexAttribDivisor = 0;
	static glVertexAttribPointer_PROC glVertexAttribPointer = 0;
	static glVertexAttribIPointer_PROC glVertexAttribIPointer = 0;
	static glGenBuffers_PROC glGenBuffers = 0;
	static glBindBuffer_PROC glBindBuffer = 0;
	static glBufferData_PROC glBufferData = 0;
	static glDeleteBuffers_PROC glDeleteBuffers = 0;
	static glBufferSubData_PROC glBufferSubData = 0;
	static glBindBufferBase_PROC glBindBufferBase = 0;
	static glMapBuffer_PROC glMapBuffer = 0;
	static glMapBufferRange_PROC glMapBufferRange = 0;
	static glUnmapBuffer_PROC glUnmapBuffer = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Memory Definition
	///////////////////////////////////////////////////////////////

	extern void* Memory_Alloc(long long unsigned Size, void const* Reference);
	extern void* Memory_Realloc(void* Block, long long unsigned Size);
	extern void Memory_Free(void* Block);

#ifdef FAST_GL_DEBUG
	extern void Memory_CheckForLeaksInternal();
#endif // FAST_GL_DEBUG

#ifdef FAST_GL_IMPLEMENTATION
	static long long unsigned sAllocatedBytes = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Math Definition
	///////////////////////////////////////////////////////////////

#define VECTOR2_ZERO { 0.0F, 0.0F }
#define VECTOR3_ZERO { 0.0F, 0.0F, 0.0F }
#define VECTOR4_ZERO { 0.0F, 0.0F, 0.0F, 0.0F }
#define VECTOR3_RIGHT { 1.0F, 0.0F, 0.0F }
#define VECTOR3_UP { 0.0F, 1.0F, 0.0F }
#define VECTOR3_FORWARD { 0.0F, 0.0F, 1.0F }
#define VECTOR3_LEFT { -1.0F, 0.0F, 0.0F }
#define VECTOR3_DOWN { 0.0F, -1.0F, 0.0F }
#define VECTOR3_BACK { 0.0F, 0.0F, -1.0F }
#define QUATERNION_ZERO { 0.0F, 0.0F, 0.0F, 0.0F }
#define QUATERNION_IDENTITY { 0.0F, 0.0F, 0.0F, 1.0F }
#define MATRIX2_ZERO \
{ \
	{ 0.0F, 0.0F }, \
	{ 0.0F, 0.0F }, \
}
#define MATRIX3_ZERO \
{ \
	{ 0.0F, 0.0F, 0.0F }, \
	{ 0.0F, 0.0F, 0.0F }, \
	{ 0.0F, 0.0F, 0.0F }, \
}
#define MATRIX4_ZERO \
{ \
	{ 0.0F, 0.0F, 0.0F, 0.0F }, \
	{ 0.0F, 0.0F, 0.0F, 0.0F }, \
	{ 0.0F, 0.0F, 0.0F, 0.0F }, \
	{ 0.0F, 0.0F, 0.0F, 0.0F }, \
}
#define MATRIX2_IDENTITY \
{ \
	{ 1.0F, 0.0F }, \
	{ 0.0F, 1.0F }, \
}
#define MATRIX3_IDENTITY \
{ \
	{ 1.0F, 0.0F, 0.0F }, \
	{ 0.0F, 1.0F, 0.0F }, \
	{ 0.0F, 0.0F, 1.0F }, \
}
#define MATRIX4_IDENTITY \
{ \
	{ 1.0F, 0.0F, 0.0F, 0.0F }, \
	{ 0.0F, 1.0F, 0.0F, 0.0F }, \
	{ 0.0F, 0.0F, 1.0F, 0.0F }, \
	{ 0.0F, 0.0F, 0.0F, 1.0F }, \
}

	typedef float Vector2[2];
	typedef float Vector3[3];
	typedef float Vector4[4];

	typedef float Quaternion[4];

	typedef float Matrix2[2][2];
	typedef float Matrix3[3][3];
	typedef float Matrix4[4][4];

	extern void Vector2_Zero(Vector2 Result);
	extern void Vector3_Zero(Vector3 Result);
	extern void Vector4_Zero(Vector4 Result);
	extern void Vector2_Set(Vector2 const Value, Vector2 Result);
	extern void Vector3_Set(Vector3 const Value, Vector3 Result);
	extern void Vector4_Set(Vector4 const Value, Vector4 Result);
	extern void Vector2_SetSimple(float X, float Y, Vector2 Result);
	extern void Vector3_SetSimple(float X, float Y, float Z, Vector3 Result);
	extern void Vector4_SetSimple(float X, float Y, float Z, float W, Vector4 Result);
	extern void Vector2_Add(Vector2 const A, Vector2 const B, Vector2 Result);
	extern void Vector3_Add(Vector3 const A, Vector3 const B, Vector3 Result);
	extern void Vector4_Add(Vector4 const A, Vector4 const B, Vector4 Result);
	extern void Vector2_Sub(Vector2 const A, Vector2 const B, Vector2 Result);
	extern void Vector3_Sub(Vector3 const A, Vector3 const B, Vector3 Result);
	extern void Vector4_Sub(Vector4 const A, Vector4 const B, Vector4 Result);
	extern void Vector2_Mul(Vector2 const A, Vector2 const B, Vector2 Result);
	extern void Vector3_Mul(Vector3 const A, Vector3 const B, Vector3 Result);
	extern void Vector4_Mul(Vector4 const A, Vector4 const B, Vector4 Result);
	extern void Vector2_Div(Vector2 const A, Vector2 const B, Vector2 Result);
	extern void Vector3_Div(Vector3 const A, Vector3 const B, Vector3 Result);
	extern void Vector4_Div(Vector4 const A, Vector4 const B, Vector4 Result);
	extern void Vector2_AddScalar(Vector2 const Value, float Scalar, Vector2 Result);
	extern void Vector3_AddScalar(Vector3 const Value, float Scalar, Vector3 Result);
	extern void Vector4_AddScalar(Vector4 const Value, float Scalar, Vector4 Result);
	extern void Vector2_SubScalar(Vector2 const Value, float Scalar, Vector2 Result);
	extern void Vector3_SubScalar(Vector3 const Value, float Scalar, Vector3 Result);
	extern void Vector4_SubScalar(Vector4 const Value, float Scalar, Vector4 Result);
	extern void Vector2_MulScalar(Vector2 const Value, float Scalar, Vector2 Result);
	extern void Vector3_MulScalar(Vector3 const Value, float Scalar, Vector3 Result);
	extern void Vector4_MulScalar(Vector4 const Value, float Scalar, Vector4 Result);
	extern void Vector2_DivScalar(Vector2 const Value, float Scalar, Vector2 Result);
	extern void Vector3_DivScalar(Vector3 const Value, float Scalar, Vector3 Result);
	extern void Vector4_DivScalar(Vector4 const Value, float Scalar, Vector4 Result);
	extern void Vector2_MulAdd(Vector2 const Value, float Scalar, Vector2 Result);
	extern void Vector3_MulAdd(Vector3 const Value, float Scalar, Vector3 Result);
	extern void Vector4_MulAdd(Vector4 const Value, float Scalar, Vector4 Result);
	extern void Vector3_Norm(Vector3 const Value, Vector3 Result);
	extern float Vector2_Dot(Vector2 const A, Vector2 const B);
	extern float Vector3_Dot(Vector3 const A, Vector3 const B);
	extern float Vector2_Length(Vector2 const Value);
	extern float Vector3_Length(Vector3 const Value);
	extern float Vector2_Length2(Vector2 const Value);
	extern float Vector3_Length2(Vector3 const Value);
	extern void Vector3_Cross(Vector3 const A, Vector3 const B, Vector3 Result);
	extern void Vector3_Rotate(Vector3 const Value, Quaternion const Rotation, Vector3 Result);

	extern void Quaternion_Zero(Quaternion Result);
	extern void Quaternion_Identity(Quaternion Result);
	extern void Quaternion_Set(Quaternion const Value, Quaternion Result);
	extern void Quaternion_SetSimple(float X, float Y, float Z, float W, Quaternion Result);
	extern void Quaternion_Mul(Quaternion const A, Quaternion const B, Quaternion Result);
	extern void Quaternion_MulScalar(Quaternion const Value, float Scalar, Quaternion Result);
	extern void Quaternion_Conjugate(Quaternion const Value, Quaternion Result);
	extern void Quaternion_EulerAngles(Quaternion const Value, Vector3 Result);
	extern void Quaternion_AngleAxis(float Angle, Vector3 const Axis, Quaternion Result);
	extern void Quaternion_Norm(Quaternion const Value, Quaternion Result);

	extern void Matrix4_GetPosition(Matrix4 const Value, Vector3 Result);
	extern void Matrix4_GetRotation(Matrix4 const Value, Quaternion Result);
	extern void Matrix4_GetScale(Matrix4 const Value, Vector3 Result);
	extern void Matrix4_SetPosition(Vector3 const Value, Matrix4 Result);
	extern void Matrix4_SetRotation(Quaternion const Value, Matrix4 Result);
	extern void Matrix4_SetScale(Vector3 const Value, Matrix4 Result);
	extern void Matrix4_Decompose(Matrix4 const Value, Vector3 Position, Quaternion Rotation, Vector3 Scale);
	extern void Matrix4_Zero(Matrix4 Result);
	extern void Matrix4_One(Matrix4 Result);
	extern void Matrix4_Copy(Matrix4 const Value, Matrix4 Result);
	extern void Matrix4_Identity(Matrix4 Result);
	extern void Matrix4_Mul(Matrix4 const A, Matrix4 const B, Matrix4 Result);
	extern void Matrix4_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, Matrix4 Result);
	extern void Matrix4_Perspective(float FieldOfView, float AspectRatio, float NearZ, float FarZ, Matrix4 Result);
	extern void Matrix4_LookAt(Vector3 const Eye, Vector3 const Center, Vector3 const Up, Matrix4 Result);

	///////////////////////////////////////////////////////////////
	// Vector Definition
	///////////////////////////////////////////////////////////////

#define VECTOR_INITIAL_CAPACITY 16

	typedef struct
	{
		char unsigned* Buffer;
		long long unsigned ValueSize;
		long long unsigned BufferSize;
		long long unsigned BufferNum;
		long long unsigned BufferIndex;
		long long unsigned BufferOffset;
	} Vector;

	extern Vector* Vector_Alloc(long long unsigned ValueSize);
	extern void Vector_Push(Vector* V, void* Item);
	extern void Vector_Pop(Vector* V, void* Item);
	extern void Vector_Resize(Vector* V, long long unsigned Num);
	extern void Vector_Clear(Vector* V);
	extern void* Vector_At(Vector* V, long long unsigned Index);
	extern void* Vector_Buffer(Vector* V);
	extern bool Vector_Empty(Vector* V);
	extern long long unsigned Vector_Num(Vector* V);
	extern long long unsigned Vector_Size(Vector* V);
	extern void Vector_Free(Vector* V);

	extern void Vector_ExpandInternal(Vector* V);

	///////////////////////////////////////////////////////////////
	// FileSystem Definition
	///////////////////////////////////////////////////////////////

	extern void FileSystem_ReadText(char** Buffer, int unsigned* BufferSize, char const* FilePath);
	extern void FileSystem_ReadBinary(char** Buffer, int unsigned* BufferSize, char const* FilePath);
	extern void FileSystem_WriteText(char const* Buffer, int unsigned BufferSize, char const* FilePath);
	extern void FileSystem_WriteBinary(char const* Buffer, int unsigned BufferSize, char const* FilePath);

	///////////////////////////////////////////////////////////////
	// FileReader Definition
	///////////////////////////////////////////////////////////////

	extern char FileReader_ReadInt8(FILE* File);
	extern char unsigned FileReader_ReadUInt8(FILE* File);
	extern short FileReader_ReadInt16(FILE* File, bool BigEndian);
	extern short unsigned FileReader_ReadUInt16(FILE* File, bool BigEndian);
	extern int FileReader_ReadInt32(FILE* File, bool BigEndian);
	extern int unsigned FileReader_ReadUInt32(FILE* File, bool BigEndian);
	extern long long FileReader_ReadInt64(FILE* File, bool BigEndian);
	extern long long unsigned FileReader_ReadUInt64(FILE* File, bool BigEndian);
	extern void FileReader_ReadInt8Array(FILE* File, char* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt8Array(FILE* File, char unsigned* Values, int unsigned NumValues);
	extern void FileReader_ReadInt16Array(FILE* File, bool BigEndian, short* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt16Array(FILE* File, bool BigEndian, short unsigned* Values, int unsigned NumValues);
	extern void FileReader_ReadInt32Array(FILE* File, bool BigEndian, int* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt32Array(FILE* File, bool BigEndian, int unsigned* Values, int unsigned NumValues);
	extern void FileReader_ReadInt64Array(FILE* File, bool BigEndian, long long* Values, int unsigned NumValues);
	extern void FileReader_ReadUInt64Array(FILE* File, bool BigEndian, long long unsigned* Values, int unsigned NumValues);

	///////////////////////////////////////////////////////////////
	// Random Definition
	///////////////////////////////////////////////////////////////

	extern void Random_Seed(char const* Seed);
	extern char Random_Int8(void);
	extern short Random_Int16(void);
	extern int Random_Int32(void);
	extern long long Random_Int64(void);
	extern char unsigned Random_UInt8(void);
	extern short unsigned Random_UInt16(void);
	extern int unsigned Random_UInt32(void);
	extern long long unsigned Random_UInt64(void);
	extern float Random_Float(float Min, float Max);
	extern double Random_Double(double Min, double Max);

	///////////////////////////////////////////////////////////////
	// Timer Definition
	///////////////////////////////////////////////////////////////

	typedef struct
	{
		double StartMicroSeconds;
		double EndMicroSeconds;
		double ElapsedMicroSeconds;
	} Timer;

	extern void Timer_Alloc(int unsigned NumTimers);
	extern void Timer_BeginMeasure(int unsigned TimerIndex);
	extern void Timer_EndMeasure(int unsigned TimerIndex);
	extern double Timer_ElapsedNanoSeconds(int unsigned TimerIndex);
	extern double Timer_ElapsedMicroSeconds(int unsigned TimerIndex);
	extern double Timer_ElapsedMilliSeconds(int unsigned TimerIndex);
	extern void Timer_Free();

#ifdef FAST_GL_IMPLEMENTATION
	static Timer* sTimers = 0;
	static int unsigned sNumTimers = 0;
	static double sFrequency = 0.0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Window Definition
	///////////////////////////////////////////////////////////////

	typedef enum
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
	typedef enum
	{
		MOUSE_KEY_LEFT,
		MOUSE_KEY_MIDDLE,
		MOUSE_KEY_RIGHT,
	} MouseKey;
	typedef enum
	{
		KEYBOARD_KEY_STATE_UP,
		KEYBOARD_KEY_STATE_PRESSED,
		KEYBOARD_KEY_STATE_DOWN,
		KEYBOARD_KEY_STATE_RELEASED,
	} KeyboardKeyState;
	typedef enum
	{
		MOUSE_KEY_STATE_UP,
		MOUSE_KEY_STATE_PRESSED,
		MOUSE_KEY_STATE_DOWN,
		MOUSE_KEY_STATE_RELEASED,
	} MouseKeyState;

	extern void Window_Alloc(int unsigned Width, int unsigned Height, char const* WindowTitle);
	extern bool Window_ShouldClose(void);
	extern void Window_Viewport(int unsigned Width, int unsigned Height);
	extern void Window_PollEvents(void);
	extern void Window_SwapBuffers(void);
	extern void Window_ToNDC(float* X, float* Y);
	extern float Window_GetWidth(void);
	extern float Window_GetHeight(void);
	extern float Window_GetMousePositionX(void);
	extern float Window_GetMousePositionY(void);
	extern bool Window_IsKeyboardKeyPressed(KeyboardKey Key);
	extern bool Window_IsKeyboardKeyHeld(KeyboardKey Key);
	extern bool Window_IsKeyboardKeyReleased(KeyboardKey Key);
	extern bool Window_IsMouseKeyPressed(MouseKey Key);
	extern bool Window_IsMouseKeyHeld(MouseKey Key);
	extern bool Window_IsMouseKeyReleased(MouseKey Key);
	extern void Window_Free(void);

	extern LRESULT Window_CallbackInternal(HWND hWnd, UINT Message, WPARAM WParam, LPARAM LParam);
#ifdef FAST_GL_DEBUG
	extern void Window_GLDebugCallbackInternal(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);
#endif // FAST_GL_DEBUG

#ifdef FAST_GL_IMPLEMENTATION
	static char const sWindowClassName[] = "FastGLWindow";
	static HINSTANCE sModuleInstance = 0;
	static HWND sWindowHandle = 0;
	static HDC sDeviceContext = 0;
	static HGLRC sGraphicsContext = 0;
	static HMODULE sOpenGLInstance = 0;
	static MSG sWindowMessage = {};
	static bool sWindowShouldClose = false;
	static float sWindowWidth = 0.0F;
	static float sWindowHeight = 0.0F;
	static float sMousePositionX = 0.0F;
	static float sMousePositionY = 0.0F;
	static float sWheelDelta = 0.0F;
	static KeyboardKeyState sKeyboardKeyStates[0xFF] = {};
	static MouseKeyState sMouseKeyStates[0x3] = {};
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Transform Definition
	///////////////////////////////////////////////////////////////

	typedef struct
	{
		void* Parent;
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
	extern void Transform_GetWorldPosition(Transform* Trans, Vector3 Position);
	extern void Transform_GetWorldRotation(Transform* Trans, Quaternion Rotation);
	extern void Transform_GetWorldEulerAngles(Transform* Trans, Vector3 Rotation);
	extern void Transform_GetWorldScale(Transform* Trans, Vector3 Scale);
	extern void Transform_GetLocalPosition(Transform* Trans, Vector3 Position);
	extern void Transform_GetLocalRotation(Transform* Trans, Quaternion Rotation);
	extern void Transform_GetLocalEulerAngles(Transform* Trans, Vector3 Rotation);
	extern void Transform_GetLocalScale(Transform* Trans, Vector3 Scale);
	extern void Transform_SetPosition(Transform* Trans, Vector3 Position);
	extern void Transform_SetPositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ);
	extern void Transform_SetRelativePosition(Transform* Trans, Vector3 Position);
	extern void Transform_SetRelativePositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ);
	extern void Transform_SetRotation(Transform* Trans, Quaternion Rotation);
	extern void Transform_SetRotationSimple(Transform* Trans, float RotationX, float RotationY, float RotationZ, float RotationW);
	extern void Transform_SetRelativeRotation(Transform* Trans, Quaternion Rotation);
	extern void Transform_SetRelativeRotationSimple(Transform* Trans, float RotationX, float RotationY, float RotationZ, float RotationW);
	extern void Transform_SetEulerAngles(Transform* Trans, Vector3 Rotation);
	extern void Transform_SetEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll);
	extern void Transform_SetRelativeEulerAngles(Transform* Trans, Vector3 Rotation);
	extern void Transform_SetRelativeEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll);
	extern void Transform_SetScale(Transform* Trans, Vector3 Scale);
	extern void Transform_SetScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ);
	extern void Transform_SetRelativeScale(Transform* Trans, Vector3 Scale);
	extern void Transform_SetRelativeScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ);

	extern void Transform_ComputeWorldPositionInternal(Transform* Trans);
	extern void Transform_ComputeWorldRotationInternal(Transform* Trans);
	extern void Transform_ComputeWorldScaleInternal(Transform* Trans);

#ifdef FAST_GL_IMPLEMENTATION
	static Vector3 const sWorldRight = VECTOR3_RIGHT;
	static Vector3 const sWorldUp = VECTOR3_UP;
	static Vector3 const sWorldForward = VECTOR3_FORWARD;
	static Vector3 const sWorldLeft = VECTOR3_LEFT;
	static Vector3 const sWorldDown = VECTOR3_DOWN;
	static Vector3 const sWorldBack = VECTOR3_BACK;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Controller Definition
	///////////////////////////////////////////////////////////////

	typedef struct
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
	typedef struct
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

	extern void Controller_InitFirstPerson(FirstPersonController* Controller);
	extern void Controller_InitOrbit(OrbitController* Controller);
	extern void Controller_UpdateFirstPerson(FirstPersonController* Controller, float DeltaTime);
	extern void Controller_UpdateOrbit(OrbitController* Controller, float DeltaTime);
	extern void Controller_GetFirstPersonViewMatrix(FirstPersonController* Controller, Matrix4 View);
	extern void Controller_GetOrbitViewMatrix(OrbitController* Controller, Matrix4 View);

	///////////////////////////////////////////////////////////////
	// Shader Definition
	///////////////////////////////////////////////////////////////

	extern int unsigned Shader_VertexFragmentAlloc(char const* VertexSource, char const* FragmentSource);
	extern int unsigned Shader_VertexGeometryFragmentAlloc(const char* GeometrySource, char const* VertexSource, char const* FragmentSource);
	extern int unsigned Shader_ComputeAlloc(char const* ComputeSource);
	extern void Shader_Bind(int unsigned Shader);
	extern void Shader_Free(int unsigned Shader);

#ifdef FAST_GL_DEBUG
	extern void Shader_CheckCompileStatus(int unsigned Shader);
	extern void Shader_CheckLinkStatus(int unsigned Program);
#endif // FAST_GL_DEBUG

	///////////////////////////////////////////////////////////////
	// Buffer Definition
	///////////////////////////////////////////////////////////////

	extern int unsigned Buffer_VertexAlloc(int unsigned Size, int unsigned Usage);
	extern int unsigned Buffer_IndexAlloc(int unsigned Size, int unsigned Usage);
	extern int unsigned Buffer_UniformAlloc(int unsigned Size, int unsigned Usage);
	extern int unsigned Buffer_StorageAlloc(int unsigned Size, int unsigned Usage);
	extern void Buffer_VertexBind(int unsigned Buffer);
	extern void Buffer_IndexBind(int unsigned Buffer);
	extern void Buffer_UniformBind(int unsigned Buffer);
	extern void Buffer_StorageBind(int unsigned Buffer);
	extern void Buffer_VertexSetData(void const* Data, int unsigned Size);
	extern void Buffer_IndexSetData(void const* Data, int unsigned Size);
	extern void Buffer_UniformSetData(void const* Data, int unsigned Size);
	extern void Buffer_StorageSetData(void const* Data, int unsigned Size);
	extern void Buffer_VertexSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_IndexSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_UniformSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_StorageSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_VertexBeginBarrier(void);
	extern void Buffer_IndexBeginBarrier(void);
	extern void Buffer_UniformBeginBarrier(void);
	extern void Buffer_StorageBeginBarrier(void);
	extern void Buffer_EndBarrier(void);
	extern void Buffer_UniformMount(int unsigned Buffer, int unsigned Index);
	extern void Buffer_StorageMount(int unsigned Buffer, int unsigned Index);
	extern void Buffer_Free(int unsigned Buffer);

	///////////////////////////////////////////////////////////////
	// Gizmo Definition
	///////////////////////////////////////////////////////////////

	typedef enum
	{
		GIZMO_DIR_XY,
		GIZMO_DIR_XZ,
		GIZMO_DIR_ZY,
	} GizmoDir;
	typedef struct
	{
		Vector3 Position;
		float Thickness;
		int unsigned Color;
		int unsigned Direction;
	} LineVertex;
	typedef struct
	{
		Vector3 Position;
	} QuadVertex;
	typedef struct
	{
		Vector3 Position;
		float Radius;
		int unsigned Color;
		int unsigned Direction;
	} PointInstanceEntry;
	typedef struct
	{
		Vector3 Position;
		Vector3 Size;
		int unsigned Color;
	} QuadInstanceEntry;

	extern void Gizmo_Alloc(int unsigned NumPoints, int unsigned NumLines, int unsigned NumQuads);
	extern void Gizmo_BeginPoints();
	extern void Gizmo_DrawPoint(GizmoDir Direction, Vector3 Position, float Radius, int unsigned Color);
	extern void Gizmo_DrawPointSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float Radius, int unsigned Color);
	extern void Gizmo_EndPoints(Matrix4 Projection, Matrix4 View);
	extern void Gizmo_BeginLines();
	extern void Gizmo_DrawLine(GizmoDir Direction, Vector3 From, Vector3 To, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineRect(GizmoDir Direction, Vector3 Position, Vector2 Size, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineRectSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineCircle(GizmoDir Direction, Vector3 Position, int unsigned NumSegments, float Radius, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineCircleSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumSegments, float Radius, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineGrid(GizmoDir Direction, Vector3 Position, int unsigned NumLines, float Scale, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineGridSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumLines, float Scale, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineBezierQuadratic(GizmoDir Direction, Vector3 From, Vector3 Ctrl, Vector3 To, int unsigned NumSegments, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineBezierQuadraticSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlX, float CtrlY, float CtrlZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineBezierCubic(GizmoDir Direction, Vector3 From, Vector3 CtrlA, Vector3 CtrlB, Vector3 To, int unsigned NumSegments, float Thickness, int unsigned Color);
	extern void Gizmo_DrawLineBezierCubicSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlAX, float CtrlAY, float CtrlAZ, float CtrlBX, float CtrlBY, float CtrlBZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, int unsigned Color);
	extern void Gizmo_EndLines(Matrix4 Projection, Matrix4 View);
	extern void Gizmo_BeginQuads(void);
	extern void Gizmo_DrawQuad(Vector3 Position, Vector3 Size, int unsigned Color);
	extern void Gizmo_DrawQuadSimple(float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, int unsigned Color);
	extern void Gizmo_EndQuads(Matrix4 Projection, Matrix4 View);
	extern void Gizmo_Free(void);

#ifdef FAST_GL_IMPLEMENTATION
	static char const sPointVertexShader[] = "#version 460 core\n"
		"layout (location = 0) in vec3 InstancePosition;"
		"layout (location = 1) in float InstanceRadius;"
		"layout (location = 2) in uint InstanceColor;"
		"layout (location = 3) in uint InstanceDirection;"
		"out VS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	flat uint Color;"
		"	flat uint Direction;"
		"} VertexOutput;"
		"void main() {"
		"	VertexOutput.Position = InstancePosition;"
		"	VertexOutput.Radius = InstanceRadius;"
		"	VertexOutput.Color = InstanceColor;"
		"	VertexOutput.Direction = InstanceDirection;"
		"}";
	static char const sPointGeometryShader[] = "#version 460 core\n"
		"layout (points) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 3) out;"
		"in VS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	flat uint Color;"
		"	flat uint Direction;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	flat uint Color;"
		"} GeometryOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"const float SQRT_3 = 1.7320508;"
		"const uint GIZMO_DIR_XY = 0;"
		"const uint GIZMO_DIR_XZ = 1;"
		"const uint GIZMO_DIR_ZY = 2;"
		"void main() {"
		"	vec3 Position = GeometryInput[0].Position;"
		"	float Radius = GeometryInput[0].Radius;"
		"	uint Color = GeometryInput[0].Color;"
		"	uint Direction = GeometryInput[0].Direction;"
		"	vec3 O0 = vec3(0.0);"
		"	vec3 O1 = vec3(0.0);"
		"	vec3 O2 = vec3(0.0);"
		"	switch (Direction) {"
		"		case GIZMO_DIR_XY: {"
		"			O0 = vec3(-SQRT_3, -1.0, 0.0);"
		"			O1 = vec3(SQRT_3, -1.0, 0.0);"
		"			O2 = vec3(0.0, 2.0, 0.0);"
		"			break;"
		"		}"
		"		case GIZMO_DIR_XZ: {"
		"			O0 = vec3(-SQRT_3, 0.0, -1.0);"
		"			O1 = vec3(SQRT_3, 0.0, -1.0);"
		"			O2 = vec3(0.0, 0.0, 2.0);"
		"			break;"
		"		}"
		"		case GIZMO_DIR_ZY: {"
		"			O0 = vec3(0.0, -1.0, -SQRT_3);"
		"			O1 = vec3(0.0, -1.0, SQRT_3);"
		"			O2 = vec3(0.0, 2.0, 0.0);"
		"			break;"
		"		}"
		"	}"
		"	O0 *= Radius;"
		"	O1 *= Radius;"
		"	O2 *= Radius;"
		"	vec3 P0 = Position + O0;"
		"	vec3 P1 = Position + O1;"
		"	vec3 P2 = Position + O2;"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P0, 1.0);"
		"	GeometryOutput.Position = O0;"
		"	GeometryOutput.Radius = Radius;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P1, 1.0);"
		"	GeometryOutput.Position = O1;"
		"	GeometryOutput.Radius = Radius;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P2, 1.0);"
		"	GeometryOutput.Position = O2;"
		"	GeometryOutput.Radius = Radius;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sPointFragmentShader[] = "#version 460 core\n"
		"in GS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	flat uint Color;"
		"} FragmentInput;"
		"out vec4 Color;"
		"void main() {"
		"	if (dot(FragmentInput.Position, FragmentInput.Position) > (FragmentInput.Radius * FragmentInput.Radius)) discard;"
		"	float R = ((FragmentInput.Color >> 24) & 0xFF) / 255.0;"
		"	float G = ((FragmentInput.Color >> 16) & 0xFF) / 255.0;"
		"	float B = ((FragmentInput.Color >>  8) & 0xFF) / 255.0;"
		"	float A = ((FragmentInput.Color      ) & 0xFF) / 255.0;"
		"	Color = vec4(R, G, B, A);"
		"}";
	static char const sLineVertexShader[] = "#version 460 core\n"
		"layout (location = 0) in vec3 InputPosition;"
		"layout (location = 1) in float InputThickness;"
		"layout (location = 2) in uint InputColor;"
		"layout (location = 3) in uint InputDirection;"
		"out VS_OUT {"
		"	float Thickness;"
		"	flat uint Color;"
		"	flat uint Direction;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(InputPosition, 1.0);"
		"	VertexOutput.Thickness = InputThickness;"
		"	VertexOutput.Color = InputColor;"
		"	VertexOutput.Direction = InputDirection;"
		"}";
	static char const sLineGeometryShader[] = "#version 460 core\n"
		"layout (lines) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 4) out;"
		"in VS_OUT {"
		"	float Thickness;"
		"	flat uint Color;"
		"	flat uint Direction;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	flat uint Color;"
		"} GeometryOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"const uint GIZMO_DIR_XY = 0;"
		"const uint GIZMO_DIR_XZ = 1;"
		"const uint GIZMO_DIR_ZY = 2;"
		"void main() {"
		"	vec3 Start = gl_in[0].gl_Position.xyz;"
		"	vec3 End = gl_in[1].gl_Position.xyz;"
		"	float Thickness = GeometryInput[0].Thickness;"
		"	uint Color = GeometryInput[0].Color;"
		"	uint Direction = GeometryInput[0].Direction;"
		"	vec3 CurrDir = normalize(End - Start);"
		"	vec3 OffsetDir = vec3(0.0);"
		"	switch (Direction) {"
		"		case GIZMO_DIR_XY: {"
		"			OffsetDir = normalize(cross(CurrDir, vec3(0.0, 0.0, 1.0))) * Thickness;"
		"			break;"
		"		}"
		"		case GIZMO_DIR_XZ: {"
		"			OffsetDir = normalize(cross(CurrDir, vec3(0.0, 1.0, 0.0))) * Thickness;"
		"			break;"
		"		}"
		"		case GIZMO_DIR_ZY: {"
		"			OffsetDir = normalize(cross(CurrDir, vec3(1.0, 0.0, 0.0))) * Thickness;"
		"			break;"
		"		}"
		"	}"
		"	vec3 O0 = Start + OffsetDir;"
		"	vec3 O1 = Start - OffsetDir;"
		"	vec3 O2 = End + OffsetDir;"
		"	vec3 O3 = End - OffsetDir;"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(O0, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(O1, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(O2, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(O3, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sLineFragmentShader[] = "#version 460 core\n"
		"in GS_OUT {"
		"	flat uint Color;"
		"} FragmentInput;"
		"out vec4 Color;"
		"void main() {"
		"	float R = ((FragmentInput.Color >> 24) & 0xFF) / 255.0;"
		"	float G = ((FragmentInput.Color >> 16) & 0xFF) / 255.0;"
		"	float B = ((FragmentInput.Color >>  8) & 0xFF) / 255.0;"
		"	float A = ((FragmentInput.Color      ) & 0xFF) / 255.0;"
		"	Color = vec4(R, G, B, A);"
		"}";
	static char const sQuadVertexShader[] = "#version 460 core\n"
		"layout (location = 0) in vec3 InputPosition;"
		"layout (location = 1) in vec3 InstancePosition;"
		"layout (location = 2) in vec3 InstanceSize;"
		"layout (location = 3) in uint InstanceColor;"
		"out VS_OUT {"
		"	flat uint Color;"
		"} VertexOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"void main() {"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(InstancePosition + (InputPosition * InstanceSize), 1.0);"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sQuadFragmentShader[] = "#version 460 core\n"
		"in VS_OUT {"
		"	flat uint Color;"
		"} FragmentInput;"
		"out vec4 Color;"
		"void main() {"
		"	float R = ((FragmentInput.Color >> 24) & 0xFF) / 255.0;"
		"	float G = ((FragmentInput.Color >> 16) & 0xFF) / 255.0;"
		"	float B = ((FragmentInput.Color >>  8) & 0xFF) / 255.0;"
		"	float A = ((FragmentInput.Color      ) & 0xFF) / 255.0;"
		"	Color = vec4(R, G, B, A);"
		"}";
	static int unsigned sPointProgram = 0;
	static int unsigned sLineProgram = 0;
	static int unsigned sQuadProgram = 0;
	static int unsigned sPointVertexArray = 0;
	static int unsigned sPointInstanceBuffer = 0;
	static int unsigned sPointInstanceOffset = 0;
	static int unsigned sLineVertexArray = 0;
	static int unsigned sLineVertexBuffer = 0;
	static int unsigned sLineIndexBuffer = 0;
	static int unsigned sLineVertexOffset = 0;
	static int unsigned sLineIndexOffset = 0;
	static int unsigned sQuadVertexArray = 0;
	static int unsigned sQuadVertexBuffer = 0;
	static int unsigned sQuadInstanceBuffer = 0;
	static int unsigned sQuadIndexBuffer = 0;
	static int unsigned sQuadInstanceOffset = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Font Definition
	///////////////////////////////////////////////////////////////

#define ON_CURVE_POINT_BIT 0ULL
#define X_SHORT_VECTOR_BIT 1ULL
#define Y_SHORT_VECTOR_BIT 2ULL
#define REPEAT_FLAG_BIT 3ULL
#define X_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT 4ULL
#define Y_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT 5ULL

	typedef struct
	{
		Vector3 Position;
		Vector2 TextureCoords;
		int unsigned GlyphIndex;
		int unsigned Color;
	} GlyphVertex;
	typedef struct
	{
		short X;
		short Y;
		bool OnCurve;
	} GlyphPoint;
	typedef struct
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
		GlyphPoint* Points;
		short unsigned NumPoints;
		char unsigned* Flags;
		char unsigned* Instructions;
		short unsigned NumInstructions;
		Vector* PointOffsets;
		Vector* BezierPoints;
		Vector* BezierOffsets;
		Vector* BezierCurves;
	} Glyph;
	typedef struct
	{
		short unsigned GlyphIndex;
		int unsigned Unicode;
	} GlyphMap;
	typedef struct
	{
		int unsigned ScalerType;
		short unsigned NumTables;
		short unsigned SearchRange;
		short unsigned EntrySelector;
		short unsigned RangeShift;
	} FontOffsetTable;
	typedef struct
	{
		char Tag[4];
		int unsigned CheckSum;
		int unsigned Offset;
		int unsigned Length;
	} FontTableDirectory;
	typedef struct
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
	typedef struct
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
	typedef struct
	{
		short unsigned Version;
		short unsigned NumberSubTables;
	} FontCmapTable;
	typedef struct
	{
		short unsigned PlatformID;
		short unsigned PlatformSpecificID;
		int unsigned Offset;
	} FontCmapSubTable;
	typedef struct
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
	typedef struct
	{
		FontOffsetTable OffsetTable;
		FontTableDirectory HeadTableDir;
		FontTableDirectory GlyfTableDir;
		FontTableDirectory LocaTableDir;
		FontTableDirectory CmapTableDir;
		FontTableDirectory MaxpTableDir;
		FontTableDirectory HheaTableDir;
		FontTableDirectory HmtxTableDir;
		FontHeadTable HeadTable;
		FontMaxpTable MaxpTable;
		FontCmapTable CmapTable;
		FontHheaTable HheaTable;
		float Dilation;
		short unsigned Width;
		short unsigned Height;
		int unsigned* GlyphOffsets;
		Vector* GlyphMapping;
		Glyph* Glyphs;
		int unsigned GlyphVertexArray;
		int unsigned GlyphVertexBuffer;
		int unsigned GlyphIndexBuffer;
		int unsigned BezierOffsetBuffer;
		int unsigned BezierCurveBuffer;
		int unsigned CharVertexOffset;
		int unsigned CharIndexOffset;
		Vector* BezierOffsets;
		Vector* BezierCurves;
	} Font;
	typedef struct
	{
		int unsigned Start;
		int unsigned Num;
	} PointOffsetEntry;
	typedef struct
	{
		int unsigned Start;
		int unsigned Num;
	} BezierOffsetEntry;
	typedef struct
	{
		Vector2 P0;
		Vector2 P1;
		Vector2 P2;
	} BezierCurveEntry;

	extern void Font_Alloc(int unsigned NumFonts);
	extern void Font_Parse(int unsigned FontIndex, int unsigned NumChars, char const* FilePath);
	extern Glyph* Font_GlyphByGlyphIndex(int unsigned FontIndex, short unsigned GlyphIndex);
	extern Glyph* Font_GlyphByUnicode(int unsigned FontIndex, int unsigned Unicode);
	extern short unsigned Font_NumGlyphs(int unsigned FontIndex);
	extern void Font_Free(void);

	extern void Font_ReadGlyphInternal(FILE* File, int unsigned FontIndex, short unsigned GlyphIndex, Glyph* Result);
	extern void Font_ReadSimpleGlyphInternal(FILE* File, Glyph* Result);
	extern void Font_ReadCompoundGlyphInternal(FILE* File, int unsigned FontIndex, short unsigned GlyphIndex, Glyph* Result);
	extern void Font_ApplyLayoutInfosInternal(FILE* File, int unsigned FontIndex);
	extern Vector* Font_UnicodeToGlyphMappingsInternal(FILE* File, int unsigned FontIndex);
	extern void Font_CreateBezierInternal(int unsigned FontIndex, Glyph* Glyph);
	extern void Font_DebugGlyphsInternal(int unsigned FontIndex, Matrix4 Projection, Matrix4 View);

#ifdef FAST_GL_IMPLEMENTATION
	static char const sFontVertexShader[] = "#version 460 core\n"
		"layout (location = 0) in vec3 InputPosition;\n"
		"layout (location = 1) in vec2 InputTextureCoords;\n"
		"layout (location = 2) in uint InputGlyphIndex;\n"
		"layout (location = 3) in uint InputColor;\n"
		"out VS_OUT {\n"
		"	vec2 TextureCoords;\n"
		"	flat uint GlyphIndex;\n"
		"	flat uint Color;\n"
		"} VertexOutput;\n"
		"uniform mat4 ProjectionMatrix;\n"
		"uniform mat4 ViewMatrix;\n"
		"void main() {\n"
		"	VertexOutput.TextureCoords = InputTextureCoords;\n"
		"	VertexOutput.GlyphIndex = InputGlyphIndex;\n"
		"	VertexOutput.Color = InputColor;\n"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(InputPosition, 1.0);\n"
		"}";
	static char const sFontFragmentShader[] = "#version 460 core\n"
		"struct BezierOffsetEntry {\n"
		"	uint Start;\n"
		"	uint Num;\n"
		"};\n"
		"struct BezierCurveEntry {\n"
		"	vec2 P0;\n"
		"	vec2 P1;\n"
		"	vec2 P2;\n"
		"};\n"
		"vec2 Rotate(vec2 V)\n"
		"{\n"
		"	return vec2(V.y, -V.x);\n"
		"}\n"
		"float ComputeCoverage(float InverseDiameter, vec2 P0, vec2 P1, vec2 P2)\n"
		"{\n"
		"	if (P0.y > 0.0 && P1.y > 0.0 && P2.y > 0.0) return 0.0;\n"
		"	if (P0.y < 0.0 && P1.y < 0.0 && P2.y < 0.0) return 0.0;\n"
		"	vec2 A = P0 - 2.0 * P1 + P2;\n"
		"	vec2 B = P0 - P1;\n"
		"	vec2 C = P0;\n"
		"	float T0 = 0.0;\n"
		"	float T1 = 0.0;\n"
		"	if (abs(A.y) >= 1e-5)\n"
		"	{\n"
		"		float Radicand = B.y * B.y - A.y * C.y;\n"
		"		if (Radicand <= 0.0) return 0.0;\n"
		"		float S = sqrt(Radicand);\n"
		"		T0 = (B.y - S) / A.y;\n"
		"		T1 = (B.y + S) / A.y;\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		float T = P0.y / (P0.y - P2.y);\n"
		"		if (P0.y < P2.y)\n"
		"		{\n"
		"			T0 = -1.0;\n"
		"			T1 = T;\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			T0 = T;\n"
		"			T1 = -1.0;\n"
		"		}\n"
		"	}\n"
		"	float Alpha = 0.0;\n"
		"	if (T0 >= 0.0 && T0 < 1.0)\n"
		"	{\n"
		"		float X = (A.x * T0 - 2.0 * B.x) * T0 + C.x;\n"
		"		Alpha += clamp(X * InverseDiameter + 0.5, 0.0, 1.0);\n"
		"	}\n"
		"	if (T1 >= 0.0 && T1 < 1.0)\n"
		"	{\n"
		"		float X = (A.x * T1 - 2.0 * B.x) * T1 + C.x;\n"
		"		Alpha -= clamp(X * InverseDiameter + 0.5, 0.0, 1.0);\n"
		"	}\n"
		"	return Alpha;\n"
		"}\n"
		"layout (location = 0) buffer BezierOffset {\n"
		"	BezierOffsetEntry Offsets[];\n"
		"} BezierOffsets;\n"
		"layout (location = 1) buffer BezierCurve {\n"
		"	BezierCurveEntry Curves[];\n"
		"} BezierCurves;\n"
		"in VS_OUT {\n"
		"	vec2 TextureCoords;\n"
		"	flat uint GlyphIndex;\n"
		"	flat uint Color;\n"
		"} FragmentInput;\n"
		"out vec4 Color;\n"
		"uniform float AntiAliasingWindowSize = 1.0;\n"
		"uniform bool EnableSuperSamplingAntiAliasing = false;\n"
		"uniform bool EnableControlPointsVisualization = true;\n"
		"void main() {\n"
		"	float Alpha = 0.0;\n"
		"	vec2 InverseDiameter = 1.0 / (AntiAliasingWindowSize * fwidth(FragmentInput.TextureCoords));\n"
		"	BezierOffsetEntry Offset = BezierOffsets.Offsets[FragmentInput.GlyphIndex];\n"
		"	for (uint CurveIndex = Offset.Start; CurveIndex < (Offset.Start + Offset.Num); CurveIndex++)\n"
		"	{\n"
		"		BezierCurveEntry Curve = BezierCurves.Curves[CurveIndex];\n"
		"		vec2 P0 = Curve.P0 - FragmentInput.TextureCoords;\n"
		"		vec2 P1 = Curve.P1 - FragmentInput.TextureCoords;\n"
		"		vec2 P2 = Curve.P2 - FragmentInput.TextureCoords;\n"
		"		Alpha += ComputeCoverage(InverseDiameter.x, P0, P1, P2);\n"
		"		if (EnableSuperSamplingAntiAliasing)\n"
		"		{\n"
		"			Alpha += ComputeCoverage(InverseDiameter.y, Rotate(P0), Rotate(P1), Rotate(P2));\n"
		"		}\n"
		"	}\n"
		"	if (EnableSuperSamplingAntiAliasing)\n"
		"	{\n"
		"		Alpha *= 0.5;\n"
		"	}\n"
		"	Alpha = clamp(Alpha, 0.0, 1.0);\n"
		"	float R = ((FragmentInput.Color >> 24) & 0xFF) / 255.0;\n"
		"	float G = ((FragmentInput.Color >> 16) & 0xFF) / 255.0;\n"
		"	float B = ((FragmentInput.Color >>  8) & 0xFF) / 255.0;\n"
		"	float A = ((FragmentInput.Color      ) & 0xFF) / 255.0;\n"
		"	Color = vec4(FragmentInput.TextureCoords, 0.0, A);\n"
		"	if (EnableControlPointsVisualization)\n"
		"	{\n"
		"		vec2 FW = fwidth(FragmentInput.TextureCoords);\n"
		"		float R = 3.0 * (FW.x + FW.y);\n"
		"		for (uint CurveIndex = Offset.Start; CurveIndex < (Offset.Start + Offset.Num); CurveIndex++)\n"
		"		{\n"
		"			BezierCurveEntry Curve = BezierCurves.Curves[CurveIndex];\n"
		"			vec2 P0 = Curve.P0 - FragmentInput.TextureCoords;\n"
		"			vec2 P1 = Curve.P1 - FragmentInput.TextureCoords;\n"
		"			vec2 P2 = Curve.P2 - FragmentInput.TextureCoords;\n"
		"			if ((dot(P0, P0) < R * R) || (dot(P2, P2) < R * R))\n"
		"			{\n"
		"				Color = vec4(0.0, 1.0, 0.0, 1.0);\n"
		"			}\n"
		"			if (dot(P1, P1) < R * R)\n"
		"			{\n"
		"				Color = vec4(1.0, 0.0, 1.0, 1.0);\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"}";
	static Font* sFonts = 0;
	static int unsigned sNumFonts = 0;
	static int unsigned sFontProgram = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Text Definition
	///////////////////////////////////////////////////////////////

	extern void Text_Begin(int unsigned FontIndex);
	extern void Text_Draw(char const* Text, Vector3 Position, float Scale, int unsigned Color);
	extern void Text_End(Matrix4 Projection, Matrix4 View);

#ifdef FAST_GL_IMPLEMENTATION
	static int unsigned sCurrFontIndex = 0;
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
		void* NewBlock = calloc(1, Size);

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
#ifdef FAST_GL_DEBUG
	void Memory_CheckForLeaksInternal()
	{
		assert(sAllocatedBytes == 0);
	}
#endif // FAST_GL_DEBUG
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Math Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Vector2_Zero(Vector2 Result)
	{
		Result[0] = 0.0F;
		Result[1] = 0.0F;
	}
	void Vector3_Zero(Vector3 Result)
	{
		Result[0] = 0.0F;
		Result[1] = 0.0F;
		Result[2] = 0.0F;
	}
	void Vector4_Zero(Vector4 Result)
	{
		Result[0] = 0.0F;
		Result[1] = 0.0F;
		Result[2] = 0.0F;
		Result[3] = 0.0F;
	}
	void Vector2_Set(Vector2 const Value, Vector2 Result)
	{
		Result[0] = Value[0];
		Result[1] = Value[1];
	}
	void Vector3_Set(Vector3 const Value, Vector3 Result)
	{
		Result[0] = Value[0];
		Result[1] = Value[1];
		Result[2] = Value[2];
	}
	void Vector4_Set(Vector4 const Value, Vector4 Result)
	{
		Result[0] = Value[0];
		Result[1] = Value[1];
		Result[2] = Value[2];
		Result[3] = Value[3];
	}
	void Vector2_SetSimple(float X, float Y, Vector2 Result)
	{
		Result[0] = X;
		Result[1] = Y;
	}
	void Vector3_SetSimple(float X, float Y, float Z, Vector3 Result)
	{
		Result[0] = X;
		Result[1] = Y;
		Result[2] = Z;
	}
	void Vector4_SetSimple(float X, float Y, float Z, float W, Vector4 Result)
	{
		Result[0] = X;
		Result[1] = Y;
		Result[2] = Z;
		Result[3] = W;
	}
	void Vector2_Add(Vector2 const A, Vector2 const B, Vector2 Result)
	{
		Result[0] = A[0] + B[0];
		Result[1] = A[1] + B[1];
	}
	void Vector3_Add(Vector3 const A, Vector3 const B, Vector3 Result)
	{
		Result[0] = A[0] + B[0];
		Result[1] = A[1] + B[1];
		Result[2] = A[2] + B[2];
	}
	void Vector4_Add(Vector4 const A, Vector4 const B, Vector4 Result)
	{
		Result[0] = A[0] + B[0];
		Result[1] = A[1] + B[1];
		Result[2] = A[2] + B[2];
		Result[3] = A[3] + B[3];
	}
	void Vector2_Sub(Vector2 const A, Vector2 const B, Vector2 Result)
	{
		Result[0] = A[0] - B[0];
		Result[1] = A[1] - B[1];
	}
	void Vector3_Sub(Vector3 const A, Vector3 const B, Vector3 Result)
	{
		Result[0] = A[0] - B[0];
		Result[1] = A[1] - B[1];
		Result[2] = A[2] - B[2];
	}
	void Vector4_Sub(Vector4 const A, Vector4 const B, Vector4 Result)
	{
		Result[0] = A[0] - B[0];
		Result[1] = A[1] - B[1];
		Result[2] = A[2] - B[2];
		Result[3] = A[3] - B[3];
	}
	void Vector2_Mul(Vector2 const A, Vector2 const B, Vector2 Result)
	{
		Result[0] = A[0] * B[0];
		Result[1] = A[1] * B[1];
	}
	void Vector3_Mul(Vector3 const A, Vector3 const B, Vector3 Result)
	{
		Result[0] = A[0] * B[0];
		Result[1] = A[1] * B[1];
		Result[2] = A[2] * B[2];
	}
	void Vector4_Mul(Vector4 const A, Vector4 const B, Vector4 Result)
	{
		Result[0] = A[0] * B[0];
		Result[1] = A[1] * B[1];
		Result[2] = A[2] * B[2];
		Result[3] = A[3] * B[3];
	}
	void Vector2_Div(Vector2 const A, Vector2 const B, Vector2 Result)
	{
		Result[0] = A[0] / B[0];
		Result[1] = A[1] / B[1];
	}
	void Vector3_Div(Vector3 const A, Vector3 const B, Vector3 Result)
	{
		Result[0] = A[0] / B[0];
		Result[1] = A[1] / B[1];
		Result[2] = A[2] / B[2];
	}
	void Vector4_Div(Vector4 const A, Vector4 const B, Vector4 Result)
	{
		Result[0] = A[0] / B[0];
		Result[1] = A[1] / B[1];
		Result[2] = A[2] / B[2];
		Result[3] = A[3] / B[3];
	}
	void Vector2_AddScalar(Vector2 const Value, float Scalar, Vector2 Result)
	{
		Result[0] = Value[0] + Scalar;
		Result[1] = Value[1] + Scalar;
	}
	void Vector3_AddScalar(Vector3 const Value, float Scalar, Vector3 Result)
	{
		Result[0] = Value[0] + Scalar;
		Result[1] = Value[1] + Scalar;
		Result[2] = Value[2] + Scalar;
	}
	void Vector4_AddScalar(Vector4 const Value, float Scalar, Vector4 Result)
	{
		Result[0] = Value[0] + Scalar;
		Result[1] = Value[1] + Scalar;
		Result[2] = Value[2] + Scalar;
		Result[3] = Value[3] + Scalar;
	}
	void Vector2_SubScalar(Vector2 const Value, float Scalar, Vector2 Result)
	{
		Result[0] = Value[0] - Scalar;
		Result[1] = Value[1] - Scalar;
	}
	void Vector3_SubScalar(Vector3 const Value, float Scalar, Vector3 Result)
	{
		Result[0] = Value[0] - Scalar;
		Result[1] = Value[1] - Scalar;
		Result[2] = Value[2] - Scalar;
	}
	void Vector4_SubScalar(Vector4 const Value, float Scalar, Vector4 Result)
	{
		Result[0] = Value[0] - Scalar;
		Result[1] = Value[1] - Scalar;
		Result[2] = Value[2] - Scalar;
		Result[3] = Value[3] - Scalar;
	}
	void Vector2_MulScalar(Vector2 const Value, float Scalar, Vector2 Result)
	{
		Result[0] = Value[0] * Scalar;
		Result[1] = Value[1] * Scalar;
	}
	void Vector3_MulScalar(Vector3 const Value, float Scalar, Vector3 Result)
	{
		Result[0] = Value[0] * Scalar;
		Result[1] = Value[1] * Scalar;
		Result[2] = Value[2] * Scalar;
	}
	void Vector4_MulScalar(Vector4 const Value, float Scalar, Vector4 Result)
	{
		Result[0] = Value[0] * Scalar;
		Result[1] = Value[1] * Scalar;
		Result[2] = Value[2] * Scalar;
		Result[3] = Value[3] * Scalar;
	}
	void Vector2_DivScalar(Vector2 const Value, float Scalar, Vector2 Result)
	{
		Result[0] = Value[0] / Scalar;
		Result[1] = Value[1] / Scalar;
	}
	void Vector3_DivScalar(Vector3 const Value, float Scalar, Vector3 Result)
	{
		Result[0] = Value[0] / Scalar;
		Result[1] = Value[1] / Scalar;
		Result[2] = Value[2] / Scalar;
	}
	void Vector4_DivScalar(Vector4 const Value, float Scalar, Vector4 Result)
	{
		Result[0] = Value[0] / Scalar;
		Result[1] = Value[1] / Scalar;
		Result[2] = Value[2] / Scalar;
		Result[3] = Value[3] / Scalar;
	}
	void Vector2_MulAdd(Vector2 const Value, float Scalar, Vector2 Result)
	{
		Result[0] += Value[0] * Scalar;
		Result[1] += Value[1] * Scalar;
	}
	void Vector3_MulAdd(Vector3 const Value, float Scalar, Vector3 Result)
	{
		Result[0] += Value[0] * Scalar;
		Result[1] += Value[1] * Scalar;
		Result[2] += Value[2] * Scalar;
	}
	void Vector4_MulAdd(Vector4 const Value, float Scalar, Vector4 Result)
	{
		Result[0] += Value[0] * Scalar;
		Result[1] += Value[1] * Scalar;
		Result[2] += Value[2] * Scalar;
		Result[3] += Value[3] * Scalar;
	}
	void Vector3_Norm(Vector3 const Value, Vector3 Result)
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
	float Vector2_Dot(Vector2 const A, Vector2 const B)
	{
		return (A[0] * B[0]) + (A[1] * B[1]);
	}
	float Vector3_Dot(Vector3 const A, Vector3 const B)
	{
		return (A[0] * B[0]) + (A[1] * B[1]) + (A[2] * B[2]);
	}
	float Vector2_Length(Vector2 const Value)
	{
		return sqrtf(Vector2_Dot(Value, Value));
	}
	float Vector3_Length(Vector3 const Value)
	{
		return sqrtf(Vector3_Dot(Value, Value));
	}
	float Vector2_Length2(Vector2 const Value)
	{
		return Vector2_Dot(Value, Value);
	}
	float Vector3_Length2(Vector3 const Value)
	{
		return Vector3_Dot(Value, Value);
	}
	void Vector3_Cross(Vector3 const A, Vector3 const B, Vector3 Result)
	{
		Result[0] = (A[1] * B[2]) - (A[2] * B[1]);
		Result[1] = (A[2] * B[0]) - (A[0] * B[2]);
		Result[2] = (A[0] * B[1]) - (A[1] * B[0]);
	}
	void Vector3_Rotate(Vector3 const Value, Quaternion const Rotation, Vector3 Result)
	{
		float QX2 = Rotation[0] * 2.0F;
		float QY2 = Rotation[1] * 2.0F;
		float QZ2 = Rotation[2] * 2.0F;

		float XX = Rotation[0] * QX2;
		float YY = Rotation[1] * QY2;
		float ZZ = Rotation[2] * QZ2;
		float XY = Rotation[0] * QY2;
		float XZ = Rotation[0] * QZ2;
		float YZ = Rotation[1] * QZ2;
		float WX = Rotation[3] * QX2;
		float WY = Rotation[3] * QY2;
		float WZ = Rotation[3] * QZ2;

		Result[0] = (1.0F - (YY + ZZ)) * Value[0] + (XY - WZ) * Value[1] + (XZ + WY) * Value[2];
		Result[1] = (XY + WZ) * Value[0] + (1.0F - (XX + ZZ)) * Value[1] + (YZ - WX) * Value[2];
		Result[2] = (XZ - WY) * Value[0] + (YZ + WX) * Value[1] + (1.0F - (XX + YY)) * Value[2];
	}
	void Quaternion_Zero(Quaternion Result)
	{
		Result[0] = 0.0F;
		Result[1] = 0.0F;
		Result[2] = 0.0F;
		Result[3] = 0.0F;
	}
	void Quaternion_Identity(Quaternion Result)
	{
		Result[0] = 0.0F;
		Result[1] = 0.0F;
		Result[2] = 0.0F;
		Result[3] = 1.0F;
	}
	void Quaternion_Set(Quaternion const Value, Quaternion Result)
	{
		Result[0] = Value[0];
		Result[1] = Value[1];
		Result[2] = Value[2];
		Result[3] = Value[3];
	}
	void Quaternion_SetSimple(float X, float Y, float Z, float W, Quaternion Result)
	{
		Result[0] = X;
		Result[1] = Y;
		Result[2] = Z;
		Result[3] = W;
	}
	void Quaternion_Mul(Quaternion const A, Quaternion const B, Quaternion Result)
	{
		Result[0] = (A[3] * B[0]) + (A[0] * B[3]) + (A[1] * B[2]) - (A[2] * B[1]);
		Result[1] = (A[3] * B[1]) - (A[0] * B[2]) + (A[1] * B[3]) + (A[2] * B[0]);
		Result[2] = (A[3] * B[2]) + (A[0] * B[1]) - (A[1] * B[0]) + (A[2] * B[3]);
		Result[3] = (A[3] * B[3]) - (A[0] * B[0]) - (A[1] * B[1]) - (A[2] * B[2]);
	}
	void Quaternion_MulScalar(Quaternion const Value, float Scalar, Quaternion Result)
	{
		Result[0] = Value[0] * Scalar;
		Result[1] = Value[1] * Scalar;
		Result[2] = Value[2] * Scalar;
		Result[3] = Value[3] * Scalar;
	}
	void Quaternion_Conjugate(Quaternion const Value, Quaternion Result)
	{
		Result[0] = -Value[0];
		Result[1] = -Value[1];
		Result[2] = -Value[2];
		Result[3] = Value[3];
	}
	void Quaternion_EulerAngles(Quaternion const Value, Vector3 Result)
	{
		float SRCP = 2.0F * ((Value[3] * Value[0]) + (Value[1] * Value[2]));
		float CRCP = 1.0F - 2.0F * (Value[0] * Value[0] + Value[1] * Value[1]);
		float R = atan2f(SRCP, CRCP);

		float SP = 2.0F * ((Value[4] * Value[1]) - (Value[2] * Value[0]));
		float P = 0.0F;
		if (fabs(SP) >= 1.0F)
		{
			P = copysignf(PI / 2, SP);
		}
		else
		{
			P = asinf(SP);
		}

		float SYCP = 2.0F * ((Value[3] * Value[2]) + (Value[0] * Value[1]));
		float CYCP = 1.0F - 2.0F * (Value[1] * Value[1] + Value[2] * Value[2]);
		float Y = atan2f(SYCP, CYCP);

		Result[0] = P;
		Result[1] = Y;
		Result[2] = R;
	}
	void Quaternion_AngleAxis(float Angle, Vector3 const Axis, Quaternion Result)
	{
		Vector3 AN = VECTOR3_ZERO;

		Vector3_Norm(Axis, AN);

		float HA = Angle / 2.0f;
		float S = sinf(HA);

		Result[0] = AN[0] * S;
		Result[1] = AN[1] * S;
		Result[2] = AN[2] * S;
		Result[3] = cosf(HA);
	}
	void Quaternion_Norm(Quaternion const Value, Quaternion Result)
	{
		float A = (Value[0] * Value[0]) + (Value[1] * Value[1]) + (Value[2] * Value[2]) + (Value[3] * Value[3]);
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
	void Matrix4_GetPosition(Matrix4 const Value, Vector3 Result)
	{
		Result[0] = Value[0][0];
		Result[1] = Value[1][0];
		Result[2] = Value[2][0];
	}
	void Matrix4_GetRotation(Matrix4 const Value, Quaternion Result)
	{
		UNREFERENCED_PARAMETER(Value);
		UNREFERENCED_PARAMETER(Result);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Matrix4_GetScale(Matrix4 const Value, Vector3 Result)
	{
		Result[0] = Value[0][0];
		Result[1] = Value[1][1];
		Result[2] = Value[2][2];
	}
	void Matrix4_SetPosition(Vector3 const Value, Matrix4 Result)
	{
		Result[3][0] = Value[0];
		Result[3][1] = Value[1];
		Result[3][2] = Value[2];
	}
	void Matrix4_SetRotation(Quaternion const Value, Matrix4 Result)
	{
		UNREFERENCED_PARAMETER(Value);
		UNREFERENCED_PARAMETER(Result);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Matrix4_SetScale(Vector3 const Value, Matrix4 Result)
	{
		Result[0][0] = Value[0];
		Result[1][1] = Value[1];
		Result[2][2] = Value[2];
	}
	void Matrix4_Decompose(Matrix4 const Value, Vector3 Position, Quaternion Rotation, Vector3 Scale)
	{
		UNREFERENCED_PARAMETER(Value);
		UNREFERENCED_PARAMETER(Position);
		UNREFERENCED_PARAMETER(Rotation);
		UNREFERENCED_PARAMETER(Scale);

#pragma message("FAST_GL_NO_IMPLEMENTATION")
	}
	void Matrix4_Zero(Matrix4 Result)
	{
		Result[0][0] = Result[0][1] = Result[0][2] = Result[0][3] = 0.0F;
		Result[1][0] = Result[1][1] = Result[1][2] = Result[1][3] = 0.0F;
		Result[2][0] = Result[2][1] = Result[2][2] = Result[2][3] = 0.0F;
		Result[3][0] = Result[3][1] = Result[3][2] = Result[3][3] = 0.0F;
	}
	void Matrix4_One(Matrix4 Result)
	{
		Result[0][0] = Result[0][1] = Result[0][2] = Result[0][3] = 1.0F;
		Result[1][0] = Result[1][1] = Result[1][2] = Result[1][3] = 1.0F;
		Result[2][0] = Result[2][1] = Result[2][2] = Result[2][3] = 1.0F;
		Result[3][0] = Result[3][1] = Result[3][2] = Result[3][3] = 1.0F;
	}
	void Matrix4_Copy(Matrix4 const Value, Matrix4 Result)
	{
		Result[0][0] = Value[0][0]; Result[1][0] = Value[1][0];
		Result[0][1] = Value[0][1]; Result[1][1] = Value[1][1];
		Result[0][2] = Value[0][2]; Result[1][2] = Value[1][2];
		Result[0][3] = Value[0][3]; Result[1][3] = Value[1][3];
		Result[2][0] = Value[2][0]; Result[3][0] = Value[3][0];
		Result[2][1] = Value[2][1]; Result[3][1] = Value[3][1];
		Result[2][2] = Value[2][2]; Result[3][2] = Value[3][2];
		Result[2][3] = Value[2][3]; Result[3][3] = Value[3][3];
	}
	void Matrix4_Identity(Matrix4 Result)
	{
		Result[0][0] = 1.0F; Result[0][1] = 0.0F; Result[0][2] = 0.0F; Result[0][3] = 0.0F;
		Result[1][0] = 0.0F; Result[1][1] = 1.0F; Result[1][2] = 0.0F; Result[1][3] = 0.0F;
		Result[2][0] = 0.0F; Result[2][1] = 0.0F; Result[2][2] = 1.0F; Result[2][3] = 0.0F;
		Result[3][0] = 0.0F; Result[3][1] = 0.0F; Result[3][2] = 0.0F; Result[3][3] = 1.0F;
	}
	void Matrix4_Mul(Matrix4 const A, Matrix4 const B, Matrix4 Result)
	{
		float A00 = A[0][0], A01 = A[0][1], A02 = A[0][2], A03 = A[0][3];
		float A10 = A[1][0], A11 = A[1][1], A12 = A[1][2], A13 = A[1][3];
		float A20 = A[2][0], A21 = A[2][1], A22 = A[2][2], A23 = A[2][3];
		float A30 = A[3][0], A31 = A[3][1], A32 = A[3][2], A33 = A[3][3];
		float B00 = B[0][0], B01 = B[0][1], B02 = B[0][2], B03 = B[0][3];
		float B10 = B[1][0], B11 = B[1][1], B12 = B[1][2], B13 = B[1][3];
		float B20 = B[2][0], B21 = B[2][1], B22 = B[2][2], B23 = B[2][3];
		float B30 = B[3][0], B31 = B[3][1], B32 = B[3][2], B33 = B[3][3];

		Result[0][0] = A00 * B00 + A10 * B01 + A20 * B02 + A30 * B03;
		Result[0][1] = A01 * B00 + A11 * B01 + A21 * B02 + A31 * B03;
		Result[0][2] = A02 * B00 + A12 * B01 + A22 * B02 + A32 * B03;
		Result[0][3] = A03 * B00 + A13 * B01 + A23 * B02 + A33 * B03;
		Result[1][0] = A00 * B10 + A10 * B11 + A20 * B12 + A30 * B13;
		Result[1][1] = A01 * B10 + A11 * B11 + A21 * B12 + A31 * B13;
		Result[1][2] = A02 * B10 + A12 * B11 + A22 * B12 + A32 * B13;
		Result[1][3] = A03 * B10 + A13 * B11 + A23 * B12 + A33 * B13;
		Result[2][0] = A00 * B20 + A10 * B21 + A20 * B22 + A30 * B23;
		Result[2][1] = A01 * B20 + A11 * B21 + A21 * B22 + A31 * B23;
		Result[2][2] = A02 * B20 + A12 * B21 + A22 * B22 + A32 * B23;
		Result[2][3] = A03 * B20 + A13 * B21 + A23 * B22 + A33 * B23;
		Result[3][0] = A00 * B30 + A10 * B31 + A20 * B32 + A30 * B33;
		Result[3][1] = A01 * B30 + A11 * B31 + A21 * B32 + A31 * B33;
		Result[3][2] = A02 * B30 + A12 * B31 + A22 * B32 + A32 * B33;
		Result[3][3] = A03 * B30 + A13 * B31 + A23 * B32 + A33 * B33;
	}
	void Matrix4_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, Matrix4 Result)
	{
		Matrix4_Zero(Result);

		Result[0][0] = 2.0F / (Right - Left);
		Result[1][1] = 2.0F / (Top - Bottom);
		Result[2][2] = 1.0F / (FarZ - NearZ);
		Result[3][0] = -(Right + Left) / (Right - Left);
		Result[3][1] = -(Top + Bottom) / (Top - Bottom);
		Result[3][2] = -NearZ / (FarZ - NearZ);
		Result[3][3] = 1.0F;
	}
	void Matrix4_Perspective(float FieldOfView, float AspectRatio, float NearZ, float FarZ, Matrix4 Result)
	{
		Matrix4_Zero(Result);

		float TanHalfFovy = tanf(FieldOfView / 2.0F);

		Result[0][0] = 1.0F / (AspectRatio * TanHalfFovy);
		Result[1][1] = 1.0F / (TanHalfFovy);
		Result[2][2] = FarZ / (FarZ - NearZ);
		Result[2][3] = 1.0F;
		Result[3][2] = -(FarZ * NearZ) / (FarZ - NearZ);
	}
	void Matrix4_LookAt(Vector3 const Eye, Vector3 const Center, Vector3 const Up, Matrix4 Result)
	{
		Vector3 F = VECTOR3_ZERO, U = VECTOR3_ZERO, S = VECTOR3_ZERO;
		Vector3 FN = VECTOR3_ZERO, SN = VECTOR3_ZERO;

		Vector3_Sub(Center, Eye, F);
		Vector3_Norm(F, FN);
		Vector3_Cross(Up, FN, S);
		Vector3_Norm(S, SN);
		Vector3_Cross(FN, SN, U);

		Result[0][0] = S[0];
		Result[0][1] = U[0];
		Result[0][2] = FN[0];
		Result[1][0] = S[1];
		Result[1][1] = U[1];
		Result[1][2] = FN[1];
		Result[2][0] = S[2];
		Result[2][1] = U[2];
		Result[2][2] = FN[2];
		Result[3][0] = -Vector3_Dot(S, Eye);
		Result[3][1] = -Vector3_Dot(U, Eye);
		Result[3][2] = -Vector3_Dot(FN, Eye);
		Result[0][3] = 0.0F;
		Result[1][3] = 0.0F;
		Result[2][3] = 0.0F;
		Result[3][3] = 1.0F;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Vector Definition
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	Vector* Vector_Alloc(long long unsigned ValueSize)
	{
		Vector* V = (Vector*)Memory_Alloc(sizeof(Vector), 0);

		V->Buffer = (char unsigned*)Memory_Alloc(ValueSize * VECTOR_INITIAL_CAPACITY, 0);
		V->ValueSize = ValueSize;
		V->BufferSize = ValueSize * VECTOR_INITIAL_CAPACITY;
		V->BufferNum = VECTOR_INITIAL_CAPACITY;
		V->BufferIndex = 0;
		V->BufferOffset = 0;

		return V;
	}
	void Vector_Push(Vector* V, void* Item)
	{
		memcpy(V->Buffer + V->BufferOffset, Item, V->ValueSize);

		V->BufferIndex += 1;
		V->BufferOffset += V->ValueSize;

		if (V->BufferIndex >= V->BufferNum)
		{
			Vector_ExpandInternal(V);
		}
	}
	void Vector_PushRange(Vector* V, Vector* Source)
	{
		for (long long unsigned Index = 0; Index < Source->BufferIndex; Index++)
		{
			Vector_Push(V, Source->Buffer + (Index * Source->ValueSize));
		}
	}
	void Vector_Pop(Vector* V, void* Item)
	{
		V->BufferIndex -= 1;
		V->BufferOffset -= V->ValueSize;

		if (Item)
		{
			memcpy(Item, V->Buffer + V->BufferOffset, V->ValueSize);
		}

		memset(V->Buffer + V->BufferOffset, 0, V->ValueSize);
	}
	void Vector_Resize(Vector* V, long long unsigned Num)
	{
		if (Num > V->BufferNum)
		{
			V->Buffer = (char unsigned*)Memory_Realloc(V->Buffer, Num * V->ValueSize);
			V->BufferNum = Num;
			V->BufferSize = Num * V->ValueSize;
		}
		else if (Num < V->BufferNum)
		{
			V->Buffer = (char unsigned*)Memory_Realloc(V->Buffer, Num * V->ValueSize);
			V->BufferNum = Num;
			V->BufferSize = Num * V->ValueSize;
			V->BufferIndex = MIN(V->BufferIndex, Num);
			V->BufferOffset = MIN(V->BufferIndex, Num) * V->ValueSize;
		}
	}
	void Vector_CopyFrom(Vector* V, Vector* Source)
	{
		V->Buffer = (char unsigned*)Memory_Realloc(V->Buffer, Source->BufferSize);
		V->ValueSize = Source->ValueSize;
		V->BufferSize = Source->ValueSize;
		V->BufferNum = Source->BufferNum;
		V->BufferIndex = Source->BufferIndex;
		V->BufferOffset = Source->BufferOffset;

		memcpy(V->Buffer, Source->Buffer, Source->BufferOffset);
	}
	void Vector_Clear(Vector* V)
	{
		V->BufferIndex = 0;
		V->BufferOffset = 0;
	}
	void* Vector_At(Vector* V, long long unsigned Index)
	{
		assert(Index < V->BufferIndex);
		return V->Buffer + (Index * V->ValueSize);
	}
	void* Vector_Buffer(Vector* V)
	{
		return (void*)V->Buffer;
	}
	bool Vector_Empty(Vector* V)
	{
		return V->BufferIndex == 0;
	}
	long long unsigned Vector_Num(Vector* V)
	{
		return V->BufferIndex;
	}
	long long unsigned Vector_Size(Vector* V)
	{
		return V->BufferIndex * V->ValueSize;
	}
	void Vector_Free(Vector* V)
	{
		Memory_Free(V->Buffer);
		Memory_Free(V);
	}
	void Vector_ExpandInternal(Vector* V)
	{
		long long unsigned NextBufferNum = V->BufferNum * 2;
		long long unsigned NextBufferSize = V->BufferSize * 2;

		V->Buffer = (char unsigned*)Memory_Realloc(V->Buffer, NextBufferSize);
		V->BufferNum = NextBufferNum;
		V->BufferSize = NextBufferSize;
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
		*BufferSize = (int unsigned)ftell(File);
		*Buffer = (char*)Memory_Alloc(((*BufferSize) + 1) * sizeof(char), 0);
		fseek(File, 0, SEEK_SET);
		fread(*Buffer, sizeof(char), *BufferSize, File);
		fclose(File);
	}
	void FileSystem_ReadBinary(char** Buffer, int unsigned* BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "rb");
		fseek(File, 0, SEEK_END);
		*BufferSize = (int unsigned)ftell(File);
		*Buffer = (char*)Memory_Alloc(*BufferSize * sizeof(char), 0);
		fseek(File, 0, SEEK_SET);
		fread(*Buffer, sizeof(char), *BufferSize, File);
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
	void FileSystem_WriteBinary(char const* Buffer, int unsigned BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "wb");
		fseek(File, 0, SEEK_SET);
		fwrite(Buffer, sizeof(char), BufferSize, File);
		fclose(File);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// FileReader Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	char FileReader_ReadInt8(FILE* File)
	{
		char Value = 0;
		fread(&Value, sizeof(char), 1, File);
		return Value;
	}
	char unsigned FileReader_ReadUInt8(FILE* File)
	{
		char unsigned Value = 0;
		fread(&Value, sizeof(char unsigned), 1, File);
		return Value;
	}
	short FileReader_ReadInt16(FILE* File, bool BigEndian)
	{
		short Value = 0;
		fread(&Value, sizeof(short), 1, File);
		return (BigEndian) ? B2L_ENDIAN_S16(Value) : Value;
	}
	short unsigned FileReader_ReadUInt16(FILE* File, bool BigEndian)
	{
		short unsigned Value = 0;
		fread(&Value, sizeof(short unsigned), 1, File);
		return (BigEndian) ? B2L_ENDIAN_U16(Value) : Value;
	}
	int FileReader_ReadInt32(FILE* File, bool BigEndian)
	{
		int Value = 0;
		fread(&Value, sizeof(int), 1, File);
		return (BigEndian) ? B2L_ENDIAN_S32(Value) : Value;
	}
	int unsigned FileReader_ReadUInt32(FILE* File, bool BigEndian)
	{
		int unsigned Value = 0;
		fread(&Value, sizeof(int unsigned), 1, File);
		return (BigEndian) ? B2L_ENDIAN_U32(Value) : Value;
	}
	long long FileReader_ReadInt64(FILE* File, bool BigEndian)
	{
		long long Value = 0;
		fread(&Value, sizeof(long long ), 1, File);
		return (BigEndian) ? B2L_ENDIAN_S64(Value) : Value;
	}
	long long unsigned FileReader_ReadUInt64(FILE* File, bool BigEndian)
	{
		long long unsigned Value = 0;
		fread(&Value, sizeof(long long unsigned), 1, File);
		return (BigEndian) ? B2L_ENDIAN_U64(Value) : Value;
	}
	void FileReader_ReadInt8Array(FILE* File, char* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(char), NumValues, File);
	}
	void FileReader_ReadUInt8Array(FILE* File, char unsigned* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(char unsigned), NumValues, File);
	}
	void FileReader_ReadInt16Array(FILE* File, bool BigEndian, short* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(short), NumValues, File);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_S16(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadUInt16Array(FILE* File, bool BigEndian, short unsigned* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(short unsigned), NumValues, File);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_U16(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadInt32Array(FILE* File, bool BigEndian, int* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(int), NumValues, File);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_S32(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadUInt32Array(FILE* File, bool BigEndian, int unsigned* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(int unsigned), NumValues, File);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_U32(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadInt64Array(FILE* File, bool BigEndian, long long* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(long long), NumValues, File);
		if (BigEndian)
		{
			for (int unsigned ValueIndex = 0; ValueIndex < NumValues; ValueIndex++)
			{
				Values[ValueIndex] = B2L_ENDIAN_S64(Values[ValueIndex]);
			}
		}
	}
	void FileReader_ReadUInt64Array(FILE* File, bool BigEndian, long long unsigned* Values, int unsigned NumValues)
	{
		fread(Values, sizeof(long long unsigned), NumValues, File);
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
	float Random_Float(float Min, float Max)
	{
		return Min + (Max - Min) * ((float)rand() / (float)RAND_MAX);
	}
	double Random_Double(double Min, double Max)
	{
		return Min + (Max - Min) * ((double)rand() / (double)RAND_MAX);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Timer Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Timer_Alloc(int unsigned NumTimers)
	{
		sTimers = (Timer*)Memory_Alloc(NumTimers * sizeof(Timer), 0);
		sNumTimers = NumTimers;

		LARGE_INTEGER Frequency = {};
		QueryPerformanceFrequency(&Frequency);
		sFrequency = (double)Frequency.QuadPart;
	}
	void Timer_BeginMeasure(int unsigned TimerIndex)
	{
		LARGE_INTEGER StartMicroSeconds = {};

		QueryPerformanceCounter(&StartMicroSeconds);

		sTimers[TimerIndex].StartMicroSeconds = (double)StartMicroSeconds.QuadPart;
	}
	void Timer_EndMeasure(int unsigned TimerIndex)
	{
		LARGE_INTEGER EndMicroSeconds = {};

		QueryPerformanceCounter(&EndMicroSeconds);

		sTimers[TimerIndex].EndMicroSeconds = (double)EndMicroSeconds.QuadPart;
		sTimers[TimerIndex].ElapsedMicroSeconds = (sTimers[TimerIndex].EndMicroSeconds - sTimers[TimerIndex].StartMicroSeconds) / sFrequency;
	}
	double Timer_ElapsedNanoSeconds(int unsigned TimerIndex)
	{
		return sTimers[TimerIndex].ElapsedMicroSeconds / 1000.0;
	}
	double Timer_ElapsedMicroSeconds(int unsigned TimerIndex)
	{
		return sTimers[TimerIndex].ElapsedMicroSeconds;
	}
	double Timer_ElapsedMilliSeconds(int unsigned TimerIndex)
	{
		return sTimers[TimerIndex].ElapsedMicroSeconds * 1000.0;
	}
	void Timer_Free()
	{
		Memory_Free(sTimers);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Window Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Window_Alloc(int unsigned Width, int unsigned Height, char const* WindowTitle)
	{
		sModuleInstance = GetModuleHandle(0);

		WNDCLASS WindowClass = {};
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

		PIXELFORMATDESCRIPTOR PixelFormatDescriptor = {};
		PixelFormatDescriptor.nSize = sizeof(PixelFormatDescriptor);
		PixelFormatDescriptor.nVersion = 1;
		PixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		PixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
		PixelFormatDescriptor.cColorBits = 32;
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
		glGetUniformLocation = (glGetUniformLocation_PROC)glGetProcAddress("glGetUniformLocation");
		glUniformMatrix4fv = (glUniformMatrix4fv_PROC)glGetProcAddress("glUniformMatrix4fv");
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
		glDeleteBuffers = (glDeleteBuffers_PROC)glGetProcAddress("glDeleteBuffers");
		glBufferSubData = (glBufferSubData_PROC)glGetProcAddress("glBufferSubData");
		glBindBufferBase = (glBindBufferBase_PROC)glGetProcAddress("glBindBufferBase");
		glMapBuffer = (glMapBuffer_PROC)glGetProcAddress("glMapBuffer");
		glMapBufferRange = (glMapBufferRange_PROC)glGetProcAddress("glMapBufferRange");
		glUnmapBuffer = (glUnmapBuffer_PROC)glGetProcAddress("glUnmapBuffer");

#ifdef FAST_GL_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(Window_GLDebugCallbackInternal, 0);
#endif // FAST_GL_DEBUG
	}
	bool Window_ShouldClose(void)
	{
		return sWindowShouldClose;
	}
	void Window_Viewport(int unsigned Width, int unsigned Height)
	{
		glViewport(0, 0, (int)Width, (int)Height);
	}
	void Window_Clear(float R, float G, float B, float A, int unsigned Mask)
	{
		glClearColor(R, G, B, A);
		glClear(Mask);
	}
	void Window_PollEvents(void)
	{
		sWheelDelta = 0.0F;

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
		*X = 2.0F * (sMousePositionX / sWindowWidth) - 1.0F;
		*Y = 1.0F - 2.0F * (sMousePositionY / sWindowHeight);
	}
	float Window_GetWidth(void)
	{
		return sWindowWidth;
	}
	float Window_GetHeight(void)
	{
		return sWindowHeight;
	}
	float Window_GetMousePositionX(void)
	{
		return sMousePositionX;
	}
	float Window_GetMousePositionY(void)
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
		glMakeCurrent(0, 0);
		glDeleteContext(sGraphicsContext);

		FreeLibrary(sOpenGLInstance);
		ReleaseDC(sWindowHandle, sDeviceContext);
		DestroyWindow(sWindowHandle);

#ifdef FAST_GL_DEBUG
		Memory_CheckForLeaksInternal();
#endif // FAST_GL_DEBUG
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
			WINDOWPOS* WindowPos = (WINDOWPOS*)LParam;

			int unsigned Width = (int unsigned)WindowPos->cx;
			int unsigned Height = (int unsigned)WindowPos->cy;
			int unsigned TitleBarHeight = (int unsigned)GetSystemMetrics(SM_CYCAPTION);
			int unsigned BorderHeight = (int unsigned)GetSystemMetrics(SM_CYFRAME);

			if ((Width > 0) && (Height > 0))
			{
				sWindowWidth = (float)Width;
				sWindowHeight = (float)(Height - TitleBarHeight + BorderHeight);
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
			int unsigned PositionX = LOWORD(LParam);
			int unsigned PositionY = HIWORD(LParam);
			int unsigned TitleBarHeight = (int unsigned)GetSystemMetrics(SM_CYCAPTION);
			int unsigned BorderHeight = (int unsigned)GetSystemMetrics(SM_CYFRAME);

			sMousePositionX = (float)PositionX;
			sMousePositionY = (float)(PositionY + TitleBarHeight - BorderHeight);

			break;
		}
		case WM_MOUSEWHEEL:
		{
			sWheelDelta = (float)GET_WHEEL_DELTA_WPARAM(WParam);

			break;
		}
		}

		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}
#ifdef FAST_GL_DEBUG
	void Window_GLDebugCallbackInternal(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam)
	{
		UNREFERENCED_PARAMETER(Source);
		UNREFERENCED_PARAMETER(ID);
		UNREFERENCED_PARAMETER(Length);
		UNREFERENCED_PARAMETER(UserParam);

		switch (Severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION: break;
		case GL_DEBUG_SEVERITY_LOW: printf("[GL] Severity:Low Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_MEDIUM: printf("[GL] Severity:Medium Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_HIGH: printf("[GL] Severity:High Type:0x%x Message:%s\n", Type, Message); break;
		}
	}
#endif // FAST_GL_DEBUG
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Transform Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Transform_Init(Transform* Trans)
	{
		Trans->Parent = 0;

		Vector3_SetSimple(1.0F, 0.0F, 0.0F, Trans->LocalRight);
		Vector3_SetSimple(0.0F, 1.0F, 0.0F, Trans->LocalUp);
		Vector3_SetSimple(0.0F, 0.0F, 1.0F, Trans->LocalForward);
		Vector3_SetSimple(-1.0F, 0.0F, 0.0F, Trans->LocalLeft);
		Vector3_SetSimple(0.0F, -1.0F, 0.0F, Trans->LocalDown);
		Vector3_SetSimple(0.0F, 0.0F, -1.0F, Trans->LocalBack);
		Vector3_SetSimple(0.0F, 0.0F, 0.0F, Trans->LocalPosition);
		Quaternion_Identity(Trans->LocalRotation);
		Vector3_SetSimple(1.0F, 1.0F, 1.0F, Trans->LocalScale);
		Vector3_SetSimple(0.0F, 0.0F, 0.0F, Trans->WorldPosition);
		Quaternion_Identity(Trans->WorldRotation);
		Vector3_SetSimple(1.0F, 1.0F, 1.0F, Trans->WorldScale);
	}
	void Transform_GetWorldPosition(Transform* Trans, Vector3 Position)
	{
		Position[0] = Trans->WorldPosition[0];
		Position[1] = Trans->WorldPosition[1];
		Position[2] = Trans->WorldPosition[2];
	}
	void Transform_GetWorldRotation(Transform* Trans, Quaternion Rotation)
	{
		Rotation[0] = Trans->WorldRotation[0];
		Rotation[1] = Trans->WorldRotation[1];
		Rotation[2] = Trans->WorldRotation[2];
		Rotation[3] = Trans->WorldRotation[3];
	}
	void Transform_GetWorldEulerAngles(Transform* Trans, Vector3 Rotation)
	{
		Quaternion_EulerAngles(Trans->WorldRotation, Rotation);

		Rotation[0] = RAD2DEG(Rotation[0]);
		Rotation[1] = RAD2DEG(Rotation[1]);
		Rotation[2] = RAD2DEG(Rotation[2]);
	}
	void Transform_GetWorldScale(Transform* Trans, Vector3 Scale)
	{
		Scale[0] = Trans->WorldScale[0];
		Scale[1] = Trans->WorldScale[1];
		Scale[2] = Trans->WorldScale[2];
	}
	void Transform_GetLocalPosition(Transform* Trans, Vector3 Position)
	{
		Position[0] = Trans->LocalPosition[0];
		Position[1] = Trans->LocalPosition[1];
		Position[2] = Trans->LocalPosition[2];
	}
	void Transform_GetLocalRotation(Transform* Trans, Quaternion Rotation)
	{
		Rotation[0] = Trans->LocalRotation[0];
		Rotation[1] = Trans->LocalRotation[1];
		Rotation[2] = Trans->LocalRotation[2];
		Rotation[3] = Trans->LocalRotation[3];
	}
	void Transform_GetLocalEulerAngles(Transform* Trans, Vector3 Rotation)
	{
		Quaternion_EulerAngles(Trans->LocalRotation, Rotation);
		
		Rotation[0] = RAD2DEG(Rotation[0]);
		Rotation[1] = RAD2DEG(Rotation[1]);
		Rotation[2] = RAD2DEG(Rotation[2]);
	}
	void Transform_GetLocalScale(Transform* Trans, Vector3 Scale)
	{
		Scale[0] = Trans->LocalScale[0];
		Scale[1] = Trans->LocalScale[1];
		Scale[2] = Trans->LocalScale[2];
	}
	void Transform_SetPosition(Transform* Trans, Vector3 Position)
	{
		Trans->LocalPosition[0] = Position[0];
		Trans->LocalPosition[1] = Position[1];
		Trans->LocalPosition[2] = Position[2];

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetPositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ)
	{
		Trans->LocalPosition[0] = PositionX;
		Trans->LocalPosition[1] = PositionY;
		Trans->LocalPosition[2] = PositionZ;

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativePosition(Transform* Trans, Vector3 Position)
	{
		Trans->LocalPosition[0] += Position[0];
		Trans->LocalPosition[1] += Position[1];
		Trans->LocalPosition[2] += Position[2];

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativePositionSimple(Transform* Trans, float PositionX, float PositionY, float PositionZ)
	{
		Trans->LocalPosition[0] += PositionX;
		Trans->LocalPosition[1] += PositionY;
		Trans->LocalPosition[2] += PositionZ;

		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRotation(Transform* Trans, Quaternion Rotation)
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
	void Transform_SetRelativeRotation(Transform* Trans, Quaternion Rotation)
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
	void Transform_SetEulerAngles(Transform* Trans, Vector3 Rotation)
	{
		float Pitch = DEG2RAD(Rotation[0]);
		float Yaw = DEG2RAD(Rotation[1]);
		float Roll = DEG2RAD(Rotation[2]);

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
			Quaternion_AngleAxis(Pitch, ParentTrans->LocalRight, QX);
			Quaternion_AngleAxis(Yaw, ParentTrans->LocalUp, QY);
			Quaternion_AngleAxis(Roll, ParentTrans->LocalForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Set(QNYXZ, Trans->LocalRotation);

			Vector3_Rotate(ParentTrans->LocalRight, Trans->LocalRotation, LR);
			Vector3_Rotate(ParentTrans->LocalUp, Trans->LocalRotation, LU);
			Vector3_Rotate(ParentTrans->LocalForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, sWorldRight, QX);
			Quaternion_AngleAxis(Yaw, sWorldUp, QY);
			Quaternion_AngleAxis(Roll, sWorldForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Set(QNYXZ, Trans->LocalRotation);

			Vector3_Rotate(sWorldRight, Trans->LocalRotation, LR);
			Vector3_Rotate(sWorldUp, Trans->LocalRotation, LU);
			Vector3_Rotate(sWorldForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll)
	{
		Pitch = DEG2RAD(Pitch);
		Yaw = DEG2RAD(Yaw);
		Roll = DEG2RAD(Roll);

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
			Quaternion_AngleAxis(Pitch, ParentTrans->LocalRight, QX);
			Quaternion_AngleAxis(Yaw, ParentTrans->LocalUp, QY);
			Quaternion_AngleAxis(Roll, ParentTrans->LocalForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Set(QNYXZ, Trans->LocalRotation);

			Vector3_Rotate(ParentTrans->LocalRight, Trans->LocalRotation, LR);
			Vector3_Rotate(ParentTrans->LocalUp, Trans->LocalRotation, LU);
			Vector3_Rotate(ParentTrans->LocalForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, sWorldRight, QX);
			Quaternion_AngleAxis(Yaw, sWorldUp, QY);
			Quaternion_AngleAxis(Roll, sWorldForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Set(QNYXZ, Trans->LocalRotation);

			Vector3_Rotate(sWorldRight, Trans->LocalRotation, LR);
			Vector3_Rotate(sWorldUp, Trans->LocalRotation, LU);
			Vector3_Rotate(sWorldForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativeEulerAngles(Transform* Trans, Vector3 Rotation)
	{
		float Pitch = DEG2RAD(Rotation[0]);
		float Yaw = DEG2RAD(Rotation[1]);
		float Roll = DEG2RAD(Rotation[2]);

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
			Quaternion_AngleAxis(Pitch, ParentTrans->LocalRight, QX);
			Quaternion_AngleAxis(Yaw, ParentTrans->LocalUp, QY);
			Quaternion_AngleAxis(Roll, ParentTrans->LocalForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Mul(Trans->LocalRotation, QNYXZ, QNYXZR);
			Quaternion_Set(QNYXZR, Trans->LocalRotation);

			Vector3_Rotate(ParentTrans->LocalRight, Trans->LocalRotation, LR);
			Vector3_Rotate(ParentTrans->LocalUp, Trans->LocalRotation, LU);
			Vector3_Rotate(ParentTrans->LocalForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, sWorldRight, QX);
			Quaternion_AngleAxis(Yaw, sWorldUp, QY);
			Quaternion_AngleAxis(Roll, sWorldForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Mul(Trans->LocalRotation, QNYXZ, QNYXZR);
			Quaternion_Set(QNYXZR, Trans->LocalRotation);

			Vector3_Rotate(sWorldRight, Trans->LocalRotation, LR);
			Vector3_Rotate(sWorldUp, Trans->LocalRotation, LU);
			Vector3_Rotate(sWorldForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetRelativeEulerAnglesSimple(Transform* Trans, float Pitch, float Yaw, float Roll)
	{
		Pitch = DEG2RAD(Pitch);
		Yaw = DEG2RAD(Yaw);
		Roll = DEG2RAD(Roll);

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
			Quaternion_AngleAxis(Pitch, ParentTrans->LocalRight, QX);
			Quaternion_AngleAxis(Yaw, ParentTrans->LocalUp, QY);
			Quaternion_AngleAxis(Roll, ParentTrans->LocalForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Mul(Trans->LocalRotation, QNYXZ, QNYXZR);
			Quaternion_Set(QNYXZR, Trans->LocalRotation);

			Vector3_Rotate(ParentTrans->LocalRight, Trans->LocalRotation, LR);
			Vector3_Rotate(ParentTrans->LocalUp, Trans->LocalRotation, LU);
			Vector3_Rotate(ParentTrans->LocalForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}
		else
		{
			Quaternion_AngleAxis(Pitch, sWorldRight, QX);
			Quaternion_AngleAxis(Yaw, sWorldUp, QY);
			Quaternion_AngleAxis(Roll, sWorldForward, QZ);

			Quaternion_Mul(QX, QZ, QXZ);
			Quaternion_Mul(QY, QXZ, QYXZ);
			Quaternion_Norm(QYXZ, QNYXZ);
			Quaternion_Mul(Trans->LocalRotation, QNYXZ, QNYXZR);
			Quaternion_Set(QNYXZR, Trans->LocalRotation);

			Vector3_Rotate(sWorldRight, Trans->LocalRotation, LR);
			Vector3_Rotate(sWorldUp, Trans->LocalRotation, LU);
			Vector3_Rotate(sWorldForward, Trans->LocalRotation, LF);

			Vector3_Norm(LR, LRN);
			Vector3_Norm(LU, LUN);
			Vector3_Norm(LF, LFN);

			Vector3_Set(LRN, Trans->LocalRight);
			Vector3_Set(LUN, Trans->LocalUp);
			Vector3_Set(LFN, Trans->LocalForward);

			LocalLeft[0] = -Trans->LocalRight[0];
			LocalLeft[1] = -Trans->LocalRight[1];
			LocalLeft[2] = -Trans->LocalRight[2];

			LocalDown[0] = -Trans->LocalUp[0];
			LocalDown[1] = -Trans->LocalUp[1];
			LocalDown[2] = -Trans->LocalUp[2];

			LocalBack[0] = -Trans->LocalForward[0];
			LocalBack[1] = -Trans->LocalForward[1];
			LocalBack[2] = -Trans->LocalForward[2];

			Vector3_Set(LocalLeft, Trans->LocalLeft);
			Vector3_Set(LocalDown, Trans->LocalDown);
			Vector3_Set(LocalBack, Trans->LocalBack);
		}

		Transform_ComputeWorldRotationInternal(Trans);
		Transform_ComputeWorldPositionInternal(Trans);
	}
	void Transform_SetScale(Transform* Trans, Vector3 Scale)
	{
		Trans->LocalScale[0] = Scale[0];
		Trans->LocalScale[1] = Scale[1];
		Trans->LocalScale[2] = Scale[2];

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_SetScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ)
	{
		Trans->LocalScale[0] = ScaleX;
		Trans->LocalScale[1] = ScaleY;
		Trans->LocalScale[2] = ScaleZ;

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_SetRelativeScale(Transform* Trans, Vector3 Scale)
	{
		Trans->LocalScale[0] += Scale[0];
		Trans->LocalScale[1] += Scale[1];
		Trans->LocalScale[2] += Scale[2];

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_SetRelativeScaleSimple(Transform* Trans, float ScaleX, float ScaleY, float ScaleZ)
	{
		Trans->LocalScale[0] += ScaleX;
		Trans->LocalScale[1] += ScaleY;
		Trans->LocalScale[2] += ScaleZ;

		Transform_ComputeWorldScaleInternal(Trans);
	}
	void Transform_ComputeWorldPositionInternal(Transform* Trans)
	{
		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Vector3 RotatedLocalPosition = VECTOR3_ZERO;
			Vector3 WorldPosition = VECTOR3_ZERO;

			Vector3_Rotate(Trans->LocalPosition, ParentTrans->WorldRotation, RotatedLocalPosition);
			Vector3_Add(ParentTrans->WorldPosition, RotatedLocalPosition, WorldPosition);
			Vector3_Set(WorldPosition, Trans->WorldPosition);
		}
		else
		{
			Vector3_Set(Trans->LocalPosition, Trans->WorldPosition);
		}
	}
	void Transform_ComputeWorldRotationInternal(Transform* Trans)
	{
		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Quaternion WorldRotation = QUATERNION_ZERO;

			Quaternion_Mul(Trans->LocalRotation, ParentTrans->WorldRotation, WorldRotation);
			Quaternion_Set(WorldRotation, Trans->WorldRotation);
		}
		else
		{
			Quaternion_Set(Trans->LocalRotation, Trans->WorldRotation);
		}
	}
	void Transform_ComputeWorldScaleInternal(Transform* Trans)
	{
		Transform* ParentTrans = (Transform*)Trans->Parent;

		if (ParentTrans)
		{
			Vector3 WorldScale = VECTOR3_ZERO;

			Vector3_Mul(Trans->LocalScale, ParentTrans->WorldScale, WorldScale);
			Vector3_Set(WorldScale, Trans->WorldScale);
		}
		else
		{
			Vector3_Set(Trans->LocalScale, Trans->WorldScale);
		}
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Controller Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Controller_InitFirstPerson(FirstPersonController* Controller)
	{
		Transform_Init(&Controller->Transform);
		Transform_SetPositionSimple(&Controller->Transform, 0.0F, 0.0F, -10.0F);
		Controller->KeyboardMovementSpeed = 10.0F;
		Controller->MouseMovementSpeed = 10.0F;
		Controller->MouseRotationSpeed = 10.0F;
		Controller->RollSpeed = 0.8F;
		Controller->MouseDrag = 50.0F;
		Vector2_Zero(Controller->MousePositionStart);
		Vector2_Zero(Controller->MousePositionEnd);
	}
	void Controller_InitOrbit(OrbitController* Controller)
	{
		Transform_Init(&Controller->Transform);
		Transform_SetPositionSimple(&Controller->Transform, 0.0F, 0.0F, -10.0F);
		Controller->KeyboardMovementSpeed = 10.0F;
		Controller->MouseMovementSpeed = 10.0F;
		Controller->MouseRotationSpeed = 10.0F;
		Controller->MouseDrag = 50.0F;
		Controller->Distance = 20.0F;
		Vector2_Zero(Controller->MousePositionStart);
		Vector2_Zero(Controller->MousePositionEnd);
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

		Vector3_MulScalar(Trans->LocalRight, Speed, RightStep);
		Vector3_MulScalar(Trans->LocalLeft, Speed, LeftStep);
		Vector3_MulScalar(Trans->LocalForward, Speed, ForwardStep);
		Vector3_MulScalar(Trans->LocalBack, Speed, BackStep);

		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_D)) Transform_SetRelativePosition(Trans, RightStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_A)) Transform_SetRelativePosition(Trans, LeftStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_W)) Transform_SetRelativePosition(Trans, ForwardStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_S)) Transform_SetRelativePosition(Trans, BackStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_E)) Transform_SetRelativeEulerAngles(Trans, RollLeftStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_Q)) Transform_SetRelativeEulerAngles(Trans, RollRightStep);

		if (Window_IsMouseKeyPressed(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionStart[0] = Window_GetMousePositionX();
			Controller->MousePositionStart[1] = Window_GetMousePositionY();
		}
		
		if (Window_IsMouseKeyHeld(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionEnd[0] = Window_GetMousePositionX();
			Controller->MousePositionEnd[1] = Window_GetMousePositionY();

			Vector2 MousePositionDelta = VECTOR2_ZERO;

			Vector2_Sub(Controller->MousePositionStart, Controller->MousePositionEnd, MousePositionDelta);
		
			if (Vector2_Length2(MousePositionDelta) > (EPSILON_2 * EPSILON_2))
			{
				Vector2 MousePositionDeltaDrag = VECTOR2_ZERO;

				Vector2_MulScalar(MousePositionDelta, Controller->MouseDrag * DeltaTime, MousePositionDeltaDrag);
				Vector2_Sub(Controller->MousePositionStart, MousePositionDelta, Controller->MousePositionStart);
			}
			else
			{
				Vector2_Set(Controller->MousePositionEnd, Controller->MousePositionStart);
			}
		
			float Pitch = -MousePositionDelta[1] * Controller->MouseRotationSpeed * DeltaTime;
			float Yaw = -MousePositionDelta[0] * Controller->MouseRotationSpeed * DeltaTime;
		
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

		Vector3_MulScalar(sWorldRight, Speed, RightStep);
		Vector3_MulScalar(sWorldLeft, Speed, LeftStep);
		Vector3_MulScalar(sWorldForward, Speed, ForwardStep);
		Vector3_MulScalar(sWorldBack, Speed, BackStep);

		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_D)) Transform_SetRelativePosition(Trans, RightStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_A)) Transform_SetRelativePosition(Trans, LeftStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_W)) Transform_SetRelativePosition(Trans, ForwardStep);
		if (Window_IsKeyboardKeyHeld(KEYBOARD_KEY_S)) Transform_SetRelativePosition(Trans, BackStep);

		if (Window_IsMouseKeyPressed(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionStart[0] = Window_GetMousePositionX();
			Controller->MousePositionStart[1] = Window_GetMousePositionY();
		}

		if (Window_IsMouseKeyHeld(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionEnd[0] = Window_GetMousePositionX();
			Controller->MousePositionEnd[1] = Window_GetMousePositionY();

			Vector2 MousePositionDelta = VECTOR2_ZERO;

			Vector2_Sub(Controller->MousePositionStart, Controller->MousePositionEnd, MousePositionDelta);

			if (Vector2_Length2(MousePositionDelta) > (EPSILON_2 * EPSILON_2))
			{
				Vector2 MousePositionDeltaDrag = VECTOR2_ZERO;

				Vector2_MulScalar(MousePositionDelta, Controller->MouseDrag * DeltaTime, MousePositionDeltaDrag);
				Vector2_Sub(Controller->MousePositionStart, MousePositionDelta, Controller->MousePositionStart);
			}
			else
			{
				Vector2_Set(Controller->MousePositionEnd, Controller->MousePositionStart);
			}

			float Pitch = -MousePositionDelta[1] * Controller->MouseRotationSpeed * DeltaTime;
			float Yaw = -MousePositionDelta[0] * Controller->MouseRotationSpeed * DeltaTime;

			Transform_SetRelativeEulerAnglesSimple(Trans, Pitch, Yaw, 0.0F);
		}
	}
	void Controller_GetFirstPersonViewMatrix(FirstPersonController* Controller, Matrix4 View)
	{
		Transform* Trans = &Controller->Transform;

		Vector3 Eye = { Trans->WorldPosition[0], Trans->WorldPosition[1], Trans->WorldPosition[2] };
		Vector3 Center = { Trans->WorldPosition[0] + Trans->LocalForward[0], Trans->WorldPosition[1] + Trans->LocalForward[1], Trans->WorldPosition[2] + Trans->LocalForward[2] };
		Vector3 Up = { Trans->LocalUp[0], Trans->LocalUp[1], Trans->LocalUp[2] };

		Matrix4_LookAt(Eye, Center, Up, View);
	}
	void Controller_GetOrbitViewMatrix(OrbitController* Controller, Matrix4 View)
	{
		Transform* Trans = &Controller->Transform;

		Vector3 Eye = { Trans->WorldPosition[0] + Trans->LocalBack[0] * Controller->Distance, Trans->WorldPosition[1] + Trans->LocalBack[1] * Controller->Distance, Trans->WorldPosition[2] + Trans->LocalBack[2] * Controller->Distance };
		Vector3 Center = { Trans->WorldPosition[0], Trans->WorldPosition[1], Trans->WorldPosition[2] };
		Vector3 Up = { Trans->LocalUp[0], Trans->LocalUp[1], Trans->LocalUp[2] };

		Matrix4_LookAt(Eye, Center, Up, View);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Shader Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	int unsigned Shader_VertexFragmentAlloc(char const* VertexSource, char const* FragmentSource)
	{
		int unsigned Program = glCreateProgram();
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
		glAttachShader(Program, VertexShader);
		glAttachShader(Program, FragmentShader);
		glLinkProgram(Program);
#ifdef FAST_GL_DEBUG
		Shader_CheckLinkStatus(Program);
#endif // FAST_GL_DEBUG
		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);

		return Program;
	}
	int unsigned Shader_VertexGeometryFragmentAlloc(char const* VertexSource, const char* GeometrySource, char const* FragmentSource)
	{
		int unsigned Program = glCreateProgram();
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
		glAttachShader(Program, VertexShader);
		glAttachShader(Program, GeometryShader);
		glAttachShader(Program, FragmentShader);
		glLinkProgram(Program);
#ifdef FAST_GL_DEBUG
		Shader_CheckLinkStatus(Program);
#endif // FAST_GL_DEBUG
		glDeleteShader(VertexShader);
		glDeleteShader(GeometryShader);
		glDeleteShader(FragmentShader);

		return Program;
	}
	int unsigned Shader_ComputeAlloc(char const* ComputeSource)
	{
		int unsigned Program = glCreateProgram();
		int unsigned ComputeShader = glCreateShader(GL_COMPUTE_SHADER);

		glShaderSource(ComputeShader, 1, &ComputeSource, 0);
		glCompileShader(ComputeShader);
#ifdef FAST_GL_DEBUG
		Shader_CheckCompileStatus(ComputeShader);
#endif // FAST_GL_DEBUG
		glAttachShader(Program, ComputeShader);
		glLinkProgram(Program);
#ifdef FAST_GL_DEBUG
		Shader_CheckLinkStatus(Program);
#endif // FAST_GL_DEBUG
		glDeleteShader(ComputeShader);

		return Program;
	}
	void Shader_Bind(int unsigned Program)
	{
		glUseProgram(Program);
	}
	void Shader_Free(int unsigned Program)
	{
		glDeleteProgram(Program);
	}
#ifdef FAST_GL_DEBUG
	void Shader_CheckCompileStatus(int unsigned Shader)
	{
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
	}
	void Shader_CheckLinkStatus(int unsigned Program)
	{
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
	}
#endif // FAST_GL_DEBUG
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Buffer Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	int unsigned Buffer_VertexAlloc(int unsigned Size, int unsigned Usage)
	{
		int unsigned Buffer = 0;

		glGenBuffers(1, &Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer);
		glBufferData(GL_ARRAY_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return Buffer;
	}
	int unsigned Buffer_IndexAlloc(int unsigned Size, int unsigned Usage)
	{
		int unsigned Buffer = 0;

		glGenBuffers(1, &Buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return Buffer;
	}
	int unsigned Buffer_UniformAlloc(int unsigned Size, int unsigned Usage)
	{
		int unsigned Buffer = 0;

		glGenBuffers(1, &Buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, Buffer);
		glBufferData(GL_UNIFORM_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		return Buffer;
	}
	int unsigned Buffer_StorageAlloc(int unsigned Size, int unsigned Usage)
	{
		int unsigned Buffer = 0;

		glGenBuffers(1, &Buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		return Buffer;
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
	void Buffer_VertexSetData(void const* Data, int unsigned Size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Data);
	}
	void Buffer_IndexSetData(void const* Data, int unsigned Size)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Size, Data);
	}
	void Buffer_UniformSetData(void const* Data, int unsigned Size)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, Size, Data);
	}
	void Buffer_StorageSetData(void const* Data, int unsigned Size)
	{
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, Size, Data);
	}
	void Buffer_VertexSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, Offset, Size, Data);
	}
	void Buffer_IndexSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, Offset, Size, Data);
	}
	void Buffer_UniformSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, Data);
	}
	void Buffer_StorageSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
	{
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, Offset, Size, Data);
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
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Gizmo Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Gizmo_Alloc(int unsigned NumPoints, int unsigned NumLines, int unsigned NumQuads)
	{
		sPointProgram = Shader_VertexGeometryFragmentAlloc(sPointVertexShader, sPointGeometryShader, sPointFragmentShader);
		sLineProgram = Shader_VertexGeometryFragmentAlloc(sLineVertexShader, sLineGeometryShader, sLineFragmentShader);
		sQuadProgram = Shader_VertexFragmentAlloc(sQuadVertexShader, sQuadFragmentShader);

		QuadVertex QuadVertices[4] = {};
		QuadVertices[0].Position[0] = -1.0F;
		QuadVertices[0].Position[1] = -1.0F;
		QuadVertices[0].Position[2] = -1.0F;
		QuadVertices[1].Position[0] = 1.0F;
		QuadVertices[1].Position[1] = -1.0F;
		QuadVertices[1].Position[2] = -1.0F;
		QuadVertices[2].Position[0] = -1.0F;
		QuadVertices[2].Position[1] = 1.0F;
		QuadVertices[2].Position[2] = -1.0F;
		QuadVertices[3].Position[0] = 1.0F;
		QuadVertices[3].Position[1] = 1.0F;
		QuadVertices[3].Position[2] = -1.0F;

		int unsigned QuadIndices[6] = {};
		QuadIndices[0] = 0;
		QuadIndices[1] = 2;
		QuadIndices[2] = 1;
		QuadIndices[3] = 3;
		QuadIndices[4] = 2;
		QuadIndices[5] = 1;

		glGenVertexArrays(1, &sPointVertexArray);
		glGenBuffers(1, &sPointInstanceBuffer);
		glBindVertexArray(sPointVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(PointInstanceEntry), (void*)(0));
		glVertexAttribPointer(1, 1, GL_FLOAT, 0, sizeof(PointInstanceEntry), (void*)(sizeof(Vector3)));
		glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(PointInstanceEntry), (void*)(sizeof(Vector3) + sizeof(float)));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(PointInstanceEntry), (void*)(sizeof(Vector3) + sizeof(float) + sizeof(int unsigned)));
		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(PointInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);

		glGenVertexArrays(1, &sLineVertexArray);
		glGenBuffers(1, &sLineVertexBuffer);
		glGenBuffers(1, &sLineIndexBuffer);
		glBindVertexArray(sLineVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(LineVertex), (void*)(0));
		glVertexAttribPointer(1, 1, GL_FLOAT, 0, sizeof(LineVertex), (void*)(sizeof(Vector3)));
		glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(LineVertex), (void*)(sizeof(Vector3) + sizeof(float)));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(LineVertex), (void*)(sizeof(Vector3) + sizeof(float) + sizeof(int unsigned)));
		glBufferData(GL_ARRAY_BUFFER, NumLines * 2 * sizeof(LineVertex), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumLines * 2 * sizeof(int unsigned), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);

		glGenVertexArrays(1, &sQuadVertexArray);
		glGenBuffers(1, &sQuadVertexBuffer);
		glGenBuffers(1, &sQuadInstanceBuffer);
		glGenBuffers(1, &sQuadIndexBuffer);
		glBindVertexArray(sQuadVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sQuadVertexBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(QuadVertex), (void*)(0));
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(QuadVertex), QuadVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, sQuadInstanceBuffer);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(1, 3, GL_FLOAT, 0, sizeof(QuadInstanceEntry), (void*)(0));
		glVertexAttribPointer(2, 3, GL_FLOAT, 0, sizeof(QuadInstanceEntry), (void*)(sizeof(Vector3)));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(QuadInstanceEntry), (void*)(sizeof(Vector3) + sizeof(Vector3)));
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glBufferData(GL_ARRAY_BUFFER, NumQuads * sizeof(QuadInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sQuadIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int unsigned), QuadIndices, GL_STATIC_DRAW);
		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Gizmo_BeginPoints()
	{
		sPointInstanceOffset = 0;
	}
	void Gizmo_DrawPoint(GizmoDir Direction, Vector3 Position, float Radius, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);

		PointInstanceEntry* PointInstanceBuffer = (PointInstanceEntry*)glMapBufferRange(GL_ARRAY_BUFFER, sPointInstanceOffset * sizeof(PointInstanceEntry), sizeof(PointInstanceEntry), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		PointInstanceBuffer->Position[0] = Position[0];
		PointInstanceBuffer->Position[1] = Position[1];
		PointInstanceBuffer->Position[2] = Position[2];
		PointInstanceBuffer->Radius = Radius;
		PointInstanceBuffer->Color = Color;
		PointInstanceBuffer->Direction = (int unsigned)Direction;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		sPointInstanceOffset += 1;
	}
	void Gizmo_DrawPointSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float Radius, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);

		PointInstanceEntry* PointInstanceBuffer = (PointInstanceEntry*)glMapBufferRange(GL_ARRAY_BUFFER, sPointInstanceOffset * sizeof(PointInstanceEntry), sizeof(PointInstanceEntry), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		PointInstanceBuffer->Position[0] = PositionX;
		PointInstanceBuffer->Position[1] = PositionY;
		PointInstanceBuffer->Position[2] = PositionZ;
		PointInstanceBuffer->Radius = Radius;
		PointInstanceBuffer->Color = Color;
		PointInstanceBuffer->Direction = (int unsigned)Direction;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		sPointInstanceOffset += 1;
	}
	void Gizmo_EndPoints(Matrix4 Projection, Matrix4 View)
	{
		glUseProgram(sPointProgram);
		int unsigned ProjectionMatrixLocation = glGetUniformLocation(sPointProgram, "ProjectionMatrix");
		int unsigned ViewMatrixLocation = glGetUniformLocation(sPointProgram, "ViewMatrix");
		glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
		glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
		glBindVertexArray(sPointVertexArray);
		glDrawArraysInstanced(GL_POINTS, 0, 1, (int)sPointInstanceOffset);
		glBindVertexArray(0);
	}
	void Gizmo_BeginLines()
	{
		sLineVertexOffset = 0;
		sLineIndexOffset = 0;
	}
	void Gizmo_DrawLine(GizmoDir Direction, Vector3 From, Vector3 To, float Thickness, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		VertexBuffer[0].Position[0] = From[0];
		VertexBuffer[0].Position[1] = From[1];
		VertexBuffer[0].Position[2] = From[2];
		VertexBuffer[0].Thickness = Thickness;
		VertexBuffer[0].Color = Color;
		VertexBuffer[0].Direction = Direction;
		VertexBuffer[1].Position[0] = To[0];
		VertexBuffer[1].Position[1] = To[1];
		VertexBuffer[1].Position[2] = To[2];
		VertexBuffer[1].Thickness = Thickness;
		VertexBuffer[1].Color = Color;
		VertexBuffer[1].Direction = Direction;

		IndexBuffer[0] = sLineVertexOffset + 0;
		IndexBuffer[1] = sLineVertexOffset + 1;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += 2;
		sLineIndexOffset += 2;
	}
	void Gizmo_DrawLineSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Thickness, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		VertexBuffer[0].Position[0] = FromX;
		VertexBuffer[0].Position[1] = FromY;
		VertexBuffer[0].Position[2] = FromZ;
		VertexBuffer[0].Thickness = Thickness;
		VertexBuffer[0].Color = Color;
		VertexBuffer[0].Direction = Direction;
		VertexBuffer[1].Position[0] = ToX;
		VertexBuffer[1].Position[1] = ToY;
		VertexBuffer[1].Position[2] = ToZ;
		VertexBuffer[1].Thickness = Thickness;
		VertexBuffer[1].Color = Color;
		VertexBuffer[1].Direction = Direction;

		IndexBuffer[0] = sLineVertexOffset + 0;
		IndexBuffer[1] = sLineVertexOffset + 1;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += 2;
		sLineIndexOffset += 2;
	}
	void Gizmo_DrawLineRect(GizmoDir Direction, Vector3 Position, Vector2 Size, float Thickness, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 4 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 8 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		VertexBuffer[0].Position[0] = Position[0];
		VertexBuffer[0].Position[1] = Position[1];
		VertexBuffer[0].Position[2] = Position[2];
		VertexBuffer[0].Thickness = Thickness;
		VertexBuffer[0].Color = Color;
		VertexBuffer[0].Direction = Direction;
		VertexBuffer[1].Position[0] = Position[0] + Size[0];
		VertexBuffer[1].Position[1] = Position[1];
		VertexBuffer[1].Position[2] = Position[2];
		VertexBuffer[1].Thickness = Thickness;
		VertexBuffer[1].Color = Color;
		VertexBuffer[1].Direction = Direction;
		VertexBuffer[2].Position[0] = Position[0] + Size[0];
		VertexBuffer[2].Position[1] = Position[1] + Size[1];
		VertexBuffer[2].Position[2] = Position[2];
		VertexBuffer[2].Thickness = Thickness;
		VertexBuffer[2].Color = Color;
		VertexBuffer[2].Direction = Direction;
		VertexBuffer[3].Position[0] = Position[0];
		VertexBuffer[3].Position[1] = Position[1] + Size[1];
		VertexBuffer[3].Position[2] = Position[2];
		VertexBuffer[3].Thickness = Thickness;
		VertexBuffer[3].Color = Color;
		VertexBuffer[3].Direction = Direction;

		IndexBuffer[0] = sLineVertexOffset + 0;
		IndexBuffer[1] = sLineVertexOffset + 1;
		IndexBuffer[2] = sLineVertexOffset + 1;
		IndexBuffer[3] = sLineVertexOffset + 2;
		IndexBuffer[4] = sLineVertexOffset + 2;
		IndexBuffer[5] = sLineVertexOffset + 3;
		IndexBuffer[6] = sLineVertexOffset + 3;
		IndexBuffer[7] = sLineVertexOffset + 0;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += 4;
		sLineIndexOffset += 8;
	}
	void Gizmo_DrawLineRectSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float Thickness, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 4 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 8 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		VertexBuffer[0].Position[0] = PositionX;
		VertexBuffer[0].Position[1] = PositionY;
		VertexBuffer[0].Position[2] = PositionZ;
		VertexBuffer[0].Thickness = Thickness;
		VertexBuffer[0].Color = Color;
		VertexBuffer[0].Direction = Direction;
		VertexBuffer[1].Position[0] = PositionX + SizeX;
		VertexBuffer[1].Position[1] = PositionY;
		VertexBuffer[1].Position[2] = PositionZ;
		VertexBuffer[1].Thickness = Thickness;
		VertexBuffer[1].Color = Color;
		VertexBuffer[1].Direction = Direction;
		VertexBuffer[2].Position[0] = PositionX + SizeX;
		VertexBuffer[2].Position[1] = PositionY + SizeY;
		VertexBuffer[2].Position[2] = PositionZ;
		VertexBuffer[2].Thickness = Thickness;
		VertexBuffer[2].Color = Color;
		VertexBuffer[2].Direction = Direction;
		VertexBuffer[3].Position[0] = PositionX;
		VertexBuffer[3].Position[1] = PositionY + SizeY;
		VertexBuffer[3].Position[2] = PositionZ;
		VertexBuffer[3].Thickness = Thickness;
		VertexBuffer[3].Color = Color;
		VertexBuffer[3].Direction = Direction;

		IndexBuffer[0] = sLineVertexOffset + 0;
		IndexBuffer[1] = sLineVertexOffset + 1;
		IndexBuffer[2] = sLineVertexOffset + 1;
		IndexBuffer[3] = sLineVertexOffset + 2;
		IndexBuffer[4] = sLineVertexOffset + 2;
		IndexBuffer[5] = sLineVertexOffset + 3;
		IndexBuffer[6] = sLineVertexOffset + 3;
		IndexBuffer[7] = sLineVertexOffset + 0;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += 4;
		sLineIndexOffset += 8;
	}
	void Gizmo_DrawLineCircle(GizmoDir Direction, Vector3 Position, int unsigned NumSegments, float Radius, float Thickness, int unsigned Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned ElementIndex = 0;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), NumSegments * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), NumSegments2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float Theta = 2.0F * PI * (float)SegmentIndex / (float)NumSegments;
			float X = Radius * cosf(Theta);
			float Y = Radius * sinf(Theta);

			VertexBuffer[SegmentIndex].Position[0] = Position[0] + X;
			VertexBuffer[SegmentIndex].Position[1] = Position[1] + Y;
			VertexBuffer[SegmentIndex].Position[2] = Position[2];
			VertexBuffer[SegmentIndex].Thickness = Thickness;
			VertexBuffer[SegmentIndex].Color = Color;
			VertexBuffer[SegmentIndex].Direction = Direction;

			if (SegmentIndex > 0)
			{
				IndexBuffer[ElementIndex + 0] = sLineVertexOffset + SegmentIndex - 1;
				IndexBuffer[ElementIndex + 1] = sLineVertexOffset + SegmentIndex;
				ElementIndex += 2;
			}
		}

		IndexBuffer[ElementIndex + 0] = sLineVertexOffset + NumSegments - 1;
		IndexBuffer[ElementIndex + 1] = sLineVertexOffset + 0;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumSegments;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineCircleSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumSegments, float Radius, float Thickness, int unsigned Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned ElementIndex = 0;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), NumSegments * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), NumSegments2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float Theta = 2.0F * PI * (float)SegmentIndex / (float)NumSegments;
			float X = Radius * cosf(Theta);
			float Y = Radius * sinf(Theta);

			VertexBuffer[SegmentIndex].Position[0] = PositionX + X;
			VertexBuffer[SegmentIndex].Position[1] = PositionY + Y;
			VertexBuffer[SegmentIndex].Position[2] = PositionZ;
			VertexBuffer[SegmentIndex].Thickness = Thickness;
			VertexBuffer[SegmentIndex].Color = Color;
			VertexBuffer[SegmentIndex].Direction = Direction;

			if (SegmentIndex > 0)
			{
				IndexBuffer[ElementIndex + 0] = sLineVertexOffset + SegmentIndex - 1;
				IndexBuffer[ElementIndex + 1] = sLineVertexOffset + SegmentIndex;
				ElementIndex += 2;
			}
		}

		IndexBuffer[ElementIndex + 0] = sLineVertexOffset + NumSegments - 1;
		IndexBuffer[ElementIndex + 1] = sLineVertexOffset + 0;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumSegments;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineGrid(GizmoDir Direction, Vector3 Position, int unsigned NumLines, float Scale, float Thickness, int unsigned Color)
	{
		int unsigned NumLines4 = NumLines * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)NumLines * Scale) / (float)NumLines;
		float HalfSize = ((float)NumLines * Scale) / 2.0F;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), (NumLines4 + 4) * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), (NumLines4 + 4) * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned LineIndex = 0; LineIndex <= NumLines; LineIndex++)
		{
			float GridOffset = (float)LineIndex * SizeStep - HalfSize;

			switch (Direction)
			{
			case GIZMO_DIR_XY:
			{
				VertexBuffer[SegmentIndex + 0].Position[0] = Position[0] + GridOffset;
				VertexBuffer[SegmentIndex + 0].Position[1] = Position[1] - HalfSize;
				VertexBuffer[SegmentIndex + 0].Position[2] = Position[2];
				VertexBuffer[SegmentIndex + 1].Position[0] = Position[0] + GridOffset;
				VertexBuffer[SegmentIndex + 1].Position[1] = Position[1] + HalfSize;
				VertexBuffer[SegmentIndex + 1].Position[2] = Position[2];
				VertexBuffer[SegmentIndex + 2].Position[0] = Position[0] - HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[1] = Position[1] + GridOffset;
				VertexBuffer[SegmentIndex + 2].Position[2] = Position[2];
				VertexBuffer[SegmentIndex + 3].Position[0] = Position[0] + HalfSize;
				VertexBuffer[SegmentIndex + 3].Position[1] = Position[1] + GridOffset;
				VertexBuffer[SegmentIndex + 3].Position[2] = Position[2];

				break;
			}
			case GIZMO_DIR_XZ:
			{
				VertexBuffer[SegmentIndex + 0].Position[0] = Position[0] + GridOffset;
				VertexBuffer[SegmentIndex + 0].Position[1] = Position[1];
				VertexBuffer[SegmentIndex + 0].Position[2] = Position[2] - HalfSize;
				VertexBuffer[SegmentIndex + 1].Position[0] = Position[0] + GridOffset;
				VertexBuffer[SegmentIndex + 1].Position[1] = Position[1];
				VertexBuffer[SegmentIndex + 1].Position[2] = Position[2] + HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[0] = Position[0] - HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[1] = Position[1];
				VertexBuffer[SegmentIndex + 2].Position[2] = Position[2] + GridOffset;
				VertexBuffer[SegmentIndex + 3].Position[0] = Position[0] + HalfSize;
				VertexBuffer[SegmentIndex + 3].Position[1] = Position[1];
				VertexBuffer[SegmentIndex + 3].Position[2] = Position[2] + GridOffset;

				break;
			}
			case GIZMO_DIR_ZY:
			{
				VertexBuffer[SegmentIndex + 0].Position[0] = Position[0];
				VertexBuffer[SegmentIndex + 0].Position[1] = Position[1] + GridOffset;
				VertexBuffer[SegmentIndex + 0].Position[2] = Position[2] - HalfSize;
				VertexBuffer[SegmentIndex + 1].Position[0] = Position[0];
				VertexBuffer[SegmentIndex + 1].Position[1] = Position[1] + GridOffset;
				VertexBuffer[SegmentIndex + 1].Position[2] = Position[2] + HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[0] = Position[0];
				VertexBuffer[SegmentIndex + 2].Position[1] = Position[1] - HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[2] = Position[2] + GridOffset;
				VertexBuffer[SegmentIndex + 3].Position[0] = Position[0];
				VertexBuffer[SegmentIndex + 3].Position[1] = Position[1] + HalfSize;
				VertexBuffer[SegmentIndex + 3].Position[2] = Position[2] + GridOffset;

				break;
			}
			}
			VertexBuffer[SegmentIndex + 0].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 0].Color = Color;
			VertexBuffer[SegmentIndex + 0].Direction = Direction;
			VertexBuffer[SegmentIndex + 1].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 1].Color = Color;
			VertexBuffer[SegmentIndex + 1].Direction = Direction;
			VertexBuffer[SegmentIndex + 2].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 2].Color = Color;
			VertexBuffer[SegmentIndex + 2].Direction = Direction;
			VertexBuffer[SegmentIndex + 3].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 3].Color = Color;
			VertexBuffer[SegmentIndex + 3].Direction = Direction;

			IndexBuffer[SegmentIndex + 0] = sLineVertexOffset + SegmentIndex + 0;
			IndexBuffer[SegmentIndex + 1] = sLineVertexOffset + SegmentIndex + 1;
			IndexBuffer[SegmentIndex + 2] = sLineVertexOffset + SegmentIndex + 2;
			IndexBuffer[SegmentIndex + 3] = sLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumLines4 + 4;
		sLineIndexOffset += NumLines4 + 4;
	}
	void Gizmo_DrawLineGridSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumLines, float Scale, float Thickness, int unsigned Color)
	{
		int unsigned NumLines4 = NumLines * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)NumLines * Scale) / (float)NumLines;
		float HalfSize = ((float)NumLines * Scale) / 2.0F;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), (NumLines4 + 4) * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), (NumLines4 + 4) * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned LineIndex = 0; LineIndex <= NumLines; LineIndex++)
		{
			float GridOffset = (float)LineIndex * SizeStep - HalfSize;

			switch (Direction)
			{
			case GIZMO_DIR_XY:
			{
				VertexBuffer[SegmentIndex + 0].Position[0] = PositionX + GridOffset;
				VertexBuffer[SegmentIndex + 0].Position[1] = PositionY - HalfSize;
				VertexBuffer[SegmentIndex + 0].Position[2] = PositionZ;
				VertexBuffer[SegmentIndex + 1].Position[0] = PositionX + GridOffset;
				VertexBuffer[SegmentIndex + 1].Position[1] = PositionY + HalfSize;
				VertexBuffer[SegmentIndex + 1].Position[2] = PositionZ;
				VertexBuffer[SegmentIndex + 2].Position[0] = PositionX - HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[1] = PositionY + GridOffset;
				VertexBuffer[SegmentIndex + 2].Position[2] = PositionZ;
				VertexBuffer[SegmentIndex + 3].Position[0] = PositionX + HalfSize;
				VertexBuffer[SegmentIndex + 3].Position[1] = PositionY + GridOffset;
				VertexBuffer[SegmentIndex + 3].Position[2] = PositionZ;

				break;
			}
			case GIZMO_DIR_XZ:
			{
				VertexBuffer[SegmentIndex + 0].Position[0] = PositionX + GridOffset;
				VertexBuffer[SegmentIndex + 0].Position[1] = PositionY;
				VertexBuffer[SegmentIndex + 0].Position[2] = PositionZ - HalfSize;
				VertexBuffer[SegmentIndex + 1].Position[0] = PositionX + GridOffset;
				VertexBuffer[SegmentIndex + 1].Position[1] = PositionY;
				VertexBuffer[SegmentIndex + 1].Position[2] = PositionZ + HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[0] = PositionX - HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[1] = PositionY;
				VertexBuffer[SegmentIndex + 2].Position[2] = PositionZ + GridOffset;
				VertexBuffer[SegmentIndex + 3].Position[0] = PositionX + HalfSize;
				VertexBuffer[SegmentIndex + 3].Position[1] = PositionY;
				VertexBuffer[SegmentIndex + 3].Position[2] = PositionZ + GridOffset;

				break;
			}
			case GIZMO_DIR_ZY:
			{
				VertexBuffer[SegmentIndex + 0].Position[0] = PositionX;
				VertexBuffer[SegmentIndex + 0].Position[1] = PositionY + GridOffset;
				VertexBuffer[SegmentIndex + 0].Position[2] = PositionZ - HalfSize;
				VertexBuffer[SegmentIndex + 1].Position[0] = PositionX;
				VertexBuffer[SegmentIndex + 1].Position[1] = PositionY + GridOffset;
				VertexBuffer[SegmentIndex + 1].Position[2] = PositionZ + HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[0] = PositionX;
				VertexBuffer[SegmentIndex + 2].Position[1] = PositionY - HalfSize;
				VertexBuffer[SegmentIndex + 2].Position[2] = PositionZ + GridOffset;
				VertexBuffer[SegmentIndex + 3].Position[0] = PositionX;
				VertexBuffer[SegmentIndex + 3].Position[1] = PositionY + HalfSize;
				VertexBuffer[SegmentIndex + 3].Position[2] = PositionZ + GridOffset;

				break;
			}
			}
			VertexBuffer[SegmentIndex + 0].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 0].Color = Color;
			VertexBuffer[SegmentIndex + 0].Direction = Direction;
			VertexBuffer[SegmentIndex + 1].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 1].Color = Color;
			VertexBuffer[SegmentIndex + 1].Direction = Direction;
			VertexBuffer[SegmentIndex + 2].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 2].Color = Color;
			VertexBuffer[SegmentIndex + 2].Direction = Direction;
			VertexBuffer[SegmentIndex + 3].Thickness = Thickness;
			VertexBuffer[SegmentIndex + 3].Color = Color;
			VertexBuffer[SegmentIndex + 3].Direction = Direction;

			IndexBuffer[SegmentIndex + 0] = sLineVertexOffset + SegmentIndex + 0;
			IndexBuffer[SegmentIndex + 1] = sLineVertexOffset + SegmentIndex + 1;
			IndexBuffer[SegmentIndex + 2] = sLineVertexOffset + SegmentIndex + 2;
			IndexBuffer[SegmentIndex + 3] = sLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumLines4 + 4;
		sLineIndexOffset += NumLines4 + 4;
	}
	void Gizmo_DrawLineBezierQuadratic(GizmoDir Direction, Vector3 From, Vector3 Ctrl, Vector3 To, int unsigned NumSegments, float Thickness, int unsigned Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), NumSegments2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), NumSegments2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float X0 = powf(1.0F - T0, 2.0F) * From[0] + 2.0F * (1.0F - T0) * T0 * Ctrl[0] + T0 * T0 * To[0];
			float Y0 = powf(1.0F - T0, 2.0F) * From[1] + 2.0F * (1.0F - T0) * T0 * Ctrl[1] + T0 * T0 * To[1];
			float Z0 = powf(1.0F - T0, 2.0F) * From[2] + 2.0F * (1.0F - T0) * T0 * Ctrl[2] + T0 * T0 * To[2];

			float X1 = powf(1.0F - T1, 2.0F) * From[0] + 2.0F * (1.0F - T1) * T1 * Ctrl[0] + T1 * T1 * To[0];
			float Y1 = powf(1.0F - T1, 2.0F) * From[1] + 2.0F * (1.0F - T1) * T1 * Ctrl[1] + T1 * T1 * To[1];
			float Z1 = powf(1.0F - T1, 2.0F) * From[2] + 2.0F * (1.0F - T1) * T1 * Ctrl[2] + T1 * T1 * To[2];

			VertexBuffer[VertexIndex + 0].Position[0] = X0;
			VertexBuffer[VertexIndex + 0].Position[1] = Y0;
			VertexBuffer[VertexIndex + 0].Position[2] = Z0;
			VertexBuffer[VertexIndex + 0].Thickness = Thickness;
			VertexBuffer[VertexIndex + 0].Color = Color;
			VertexBuffer[VertexIndex + 0].Direction = Direction;
			VertexBuffer[VertexIndex + 1].Position[0] = X1;
			VertexBuffer[VertexIndex + 1].Position[1] = Y1;
			VertexBuffer[VertexIndex + 1].Position[2] = Z1;
			VertexBuffer[VertexIndex + 1].Thickness = Thickness;
			VertexBuffer[VertexIndex + 1].Color = Color;
			VertexBuffer[VertexIndex + 1].Direction = Direction;

			IndexBuffer[ElementIndex + 0] = sLineVertexOffset + VertexIndex;
			IndexBuffer[ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineBezierQuadraticSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlX, float CtrlY, float CtrlZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, int unsigned Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), NumSegments2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), NumSegments2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float X0 = powf(1.0F - T0, 2.0F) * FromX + 2.0F * (1.0F - T0) * T0 * CtrlX + T0 * T0 * ToX;
			float Y0 = powf(1.0F - T0, 2.0F) * FromY + 2.0F * (1.0F - T0) * T0 * CtrlY + T0 * T0 * ToY;
			float Z0 = powf(1.0F - T0, 2.0F) * FromZ + 2.0F * (1.0F - T0) * T0 * CtrlZ + T0 * T0 * ToZ;

			float X1 = powf(1.0F - T1, 2.0F) * FromX + 2.0F * (1.0F - T1) * T1 * CtrlX + T1 * T1 * ToX;
			float Y1 = powf(1.0F - T1, 2.0F) * FromY + 2.0F * (1.0F - T1) * T1 * CtrlY + T1 * T1 * ToY;
			float Z1 = powf(1.0F - T1, 2.0F) * FromZ + 2.0F * (1.0F - T1) * T1 * CtrlZ + T1 * T1 * ToZ;

			VertexBuffer[VertexIndex + 0].Position[0] = X0;
			VertexBuffer[VertexIndex + 0].Position[1] = Y0;
			VertexBuffer[VertexIndex + 0].Position[2] = Z0;
			VertexBuffer[VertexIndex + 0].Thickness = Thickness;
			VertexBuffer[VertexIndex + 0].Color = Color;
			VertexBuffer[VertexIndex + 0].Direction = Direction;
			VertexBuffer[VertexIndex + 1].Position[0] = X1;
			VertexBuffer[VertexIndex + 1].Position[1] = Y1;
			VertexBuffer[VertexIndex + 1].Position[2] = Z1;
			VertexBuffer[VertexIndex + 1].Thickness = Thickness;
			VertexBuffer[VertexIndex + 1].Color = Color;
			VertexBuffer[VertexIndex + 1].Direction = Direction;

			IndexBuffer[ElementIndex + 0] = sLineVertexOffset + VertexIndex;
			IndexBuffer[ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineBezierCubic(GizmoDir Direction, Vector3 From, Vector3 CtrlA, Vector3 CtrlB, Vector3 To, int unsigned NumSegments, float Thickness, int unsigned Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), NumSegments2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), NumSegments2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float X0 = powf(1.0F - T0, 3.0F) * From[0] + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlA[0] + 3.0F * (1.0F - T0) * T0 * T0 * CtrlB[0] + T0 * T0 * T0 * To[0];
			float Y0 = powf(1.0F - T0, 3.0F) * From[1] + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlA[1] + 3.0F * (1.0F - T0) * T0 * T0 * CtrlB[1] + T0 * T0 * T0 * To[1];
			float Z0 = powf(1.0F - T0, 3.0F) * From[2] + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlA[2] + 3.0F * (1.0F - T0) * T0 * T0 * CtrlB[2] + T0 * T0 * T0 * To[2];

			float X1 = powf(1.0F - T1, 3.0F) * From[0] + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlA[0] + 3.0F * (1.0F - T1) * T1 * T1 * CtrlB[0] + T1 * T1 * T1 * To[0];
			float Y1 = powf(1.0F - T1, 3.0F) * From[1] + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlA[1] + 3.0F * (1.0F - T1) * T1 * T1 * CtrlB[1] + T1 * T1 * T1 * To[1];
			float Z1 = powf(1.0F - T1, 3.0F) * From[2] + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlA[2] + 3.0F * (1.0F - T1) * T1 * T1 * CtrlB[2] + T1 * T1 * T1 * To[2];

			VertexBuffer[VertexIndex + 0].Position[0] = X0;
			VertexBuffer[VertexIndex + 0].Position[1] = Y0;
			VertexBuffer[VertexIndex + 0].Position[2] = Z0;
			VertexBuffer[VertexIndex + 0].Thickness = Thickness;
			VertexBuffer[VertexIndex + 0].Color = Color;
			VertexBuffer[VertexIndex + 0].Direction = Direction;
			VertexBuffer[VertexIndex + 1].Position[0] = X1;
			VertexBuffer[VertexIndex + 1].Position[1] = Y1;
			VertexBuffer[VertexIndex + 1].Position[2] = Z1;
			VertexBuffer[VertexIndex + 1].Thickness = Thickness;
			VertexBuffer[VertexIndex + 1].Color = Color;
			VertexBuffer[VertexIndex + 1].Direction = Direction;

			IndexBuffer[ElementIndex + 0] = sLineVertexOffset + VertexIndex;
			IndexBuffer[ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineBezierCubicSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlAX, float CtrlAY, float CtrlAZ, float CtrlBX, float CtrlBY, float CtrlBZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, int unsigned Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

		LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), NumSegments2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), NumSegments2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float X0 = powf(1.0F - T0, 3.0F) * FromX + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlAX + 3.0F * (1.0F - T0) * T0 * T0 * CtrlBX + T0 * T0 * T0 * ToX;
			float Y0 = powf(1.0F - T0, 3.0F) * FromY + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlAY + 3.0F * (1.0F - T0) * T0 * T0 * CtrlBY + T0 * T0 * T0 * ToY;
			float Z0 = powf(1.0F - T0, 3.0F) * FromZ + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlAZ + 3.0F * (1.0F - T0) * T0 * T0 * CtrlBZ + T0 * T0 * T0 * ToZ;

			float X1 = powf(1.0F - T1, 3.0F) * FromX + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlAX + 3.0F * (1.0F - T1) * T1 * T1 * CtrlBX + T1 * T1 * T1 * ToX;
			float Y1 = powf(1.0F - T1, 3.0F) * FromY + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlAY + 3.0F * (1.0F - T1) * T1 * T1 * CtrlBY + T1 * T1 * T1 * ToY;
			float Z1 = powf(1.0F - T1, 3.0F) * FromZ + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlAZ + 3.0F * (1.0F - T1) * T1 * T1 * CtrlBZ + T1 * T1 * T1 * ToZ;

			VertexBuffer[VertexIndex + 0].Position[0] = X0;
			VertexBuffer[VertexIndex + 0].Position[1] = Y0;
			VertexBuffer[VertexIndex + 0].Position[2] = Z0;
			VertexBuffer[VertexIndex + 0].Thickness = Thickness;
			VertexBuffer[VertexIndex + 0].Color = Color;
			VertexBuffer[VertexIndex + 0].Direction = Direction;
			VertexBuffer[VertexIndex + 1].Position[0] = X1;
			VertexBuffer[VertexIndex + 1].Position[1] = Y1;
			VertexBuffer[VertexIndex + 1].Position[2] = Z1;
			VertexBuffer[VertexIndex + 1].Thickness = Thickness;
			VertexBuffer[VertexIndex + 1].Color = Color;
			VertexBuffer[VertexIndex + 1].Direction = Direction;

			IndexBuffer[ElementIndex + 0] = sLineVertexOffset + VertexIndex;
			IndexBuffer[ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_EndLines(Matrix4 Projection, Matrix4 View)
	{
		glUseProgram(sLineProgram);
		int unsigned ProjectionMatrixLocation = glGetUniformLocation(sLineProgram, "ProjectionMatrix");
		int unsigned ViewMatrixLocation = glGetUniformLocation(sLineProgram, "ViewMatrix");
		glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
		glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
		glBindVertexArray(sLineVertexArray);
		glDrawArrays(GL_LINES, 0, (int)sLineIndexOffset);
		glBindVertexArray(0);
	}
	void Gizmo_BeginQuads(void)
	{
		sQuadInstanceOffset = 0;
	}
	void Gizmo_DrawQuad(Vector3 Position, Vector3 Size, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sQuadInstanceBuffer);

		QuadInstanceEntry* QuadInstanceBuffer = (QuadInstanceEntry*)glMapBufferRange(GL_ARRAY_BUFFER, sQuadInstanceOffset * sizeof(QuadInstanceEntry), sizeof(QuadInstanceEntry), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		QuadInstanceBuffer->Position[0] = Position[0];
		QuadInstanceBuffer->Position[1] = Position[1];
		QuadInstanceBuffer->Position[2] = Position[2];
		QuadInstanceBuffer->Size[0] = Size[0];
		QuadInstanceBuffer->Size[1] = Size[1];
		QuadInstanceBuffer->Size[2] = Size[2];
		QuadInstanceBuffer->Color = Color;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		sQuadInstanceOffset += 1;
	}
	void Gizmo_DrawQuadSimple(float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, int unsigned Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sQuadInstanceBuffer);

		QuadInstanceEntry* QuadInstanceBuffer = (QuadInstanceEntry*)glMapBufferRange(GL_ARRAY_BUFFER, sQuadInstanceOffset * sizeof(QuadInstanceEntry), sizeof(QuadInstanceEntry), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		QuadInstanceBuffer->Position[0] = PositionX;
		QuadInstanceBuffer->Position[1] = PositionY;
		QuadInstanceBuffer->Position[2] = PositionZ;
		QuadInstanceBuffer->Size[0] = SizeX;
		QuadInstanceBuffer->Size[1] = SizeY;
		QuadInstanceBuffer->Size[2] = SizeZ;
		QuadInstanceBuffer->Color = Color;

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		sQuadInstanceOffset += 1;
	}
	void Gizmo_EndQuads(Matrix4 Projection, Matrix4 View)
	{
		glUseProgram(sQuadProgram);
		int unsigned ProjectionMatrixLocation = glGetUniformLocation(sQuadProgram, "ProjectionMatrix");
		int unsigned ViewMatrixLocation = glGetUniformLocation(sQuadProgram, "ViewMatrix");
		glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
		glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
		glBindVertexArray(sQuadVertexArray);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 1, (int)sQuadInstanceOffset);
		glBindVertexArray(0);
	}
	void Gizmo_Free(void)
	{
		glDeleteBuffers(1, &sPointInstanceBuffer);
		glDeleteBuffers(1, &sLineVertexBuffer);
		glDeleteBuffers(1, &sLineIndexBuffer);
		glDeleteBuffers(1, &sQuadVertexBuffer);
		glDeleteBuffers(1, &sQuadInstanceBuffer);
		glDeleteBuffers(1, &sQuadIndexBuffer);
		glDeleteVertexArrays(1, &sPointVertexArray);
		glDeleteVertexArrays(1, &sLineVertexArray);
		glDeleteVertexArrays(1, &sQuadVertexArray);
		
		Shader_Free(sPointProgram);
		Shader_Free(sLineProgram);
		Shader_Free(sQuadProgram);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Font Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Font_Alloc(int unsigned NumFonts)
	{
		sFonts = (Font*)Memory_Alloc(NumFonts * sizeof(Font), 0);
		sNumFonts = NumFonts;
		sFontProgram = Shader_VertexFragmentAlloc(sFontVertexShader, sFontFragmentShader);
	}
	void Font_Parse(int unsigned FontIndex, int unsigned NumChars, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "rb");

		memset(&sFonts[FontIndex], 0, sizeof(Font));

		sFonts[FontIndex].OffsetTable.ScalerType = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].OffsetTable.NumTables = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].OffsetTable.SearchRange = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].OffsetTable.EntrySelector = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].OffsetTable.RangeShift = FileReader_ReadUInt16(File, true);

		for (short unsigned TableIndex = 0; TableIndex < sFonts[FontIndex].OffsetTable.NumTables; TableIndex++)
		{
			FontTableDirectory TableDir = {};
			FileReader_ReadInt8Array(File, TableDir.Tag, 4);
			TableDir.CheckSum = FileReader_ReadUInt32(File, true);
			TableDir.Offset = FileReader_ReadUInt32(File, true);
			TableDir.Length = FileReader_ReadUInt32(File, true);

			if (strncmp(TableDir.Tag, "head", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].HeadTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "glyf", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].GlyfTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "loca", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].LocaTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "cmap", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].CmapTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "maxp", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].MaxpTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "hhea", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].HheaTableDir, &TableDir, sizeof(FontTableDirectory));
			}
			else if (strncmp(TableDir.Tag, "hmtx", 4) == 0)
			{
				memcpy(&sFonts[FontIndex].HmtxTableDir, &TableDir, sizeof(FontTableDirectory));
			}
		}

		assert(sFonts[FontIndex].HeadTableDir.Offset);
		assert(sFonts[FontIndex].GlyfTableDir.Offset);
		assert(sFonts[FontIndex].LocaTableDir.Offset);
		assert(sFonts[FontIndex].CmapTableDir.Offset);
		assert(sFonts[FontIndex].MaxpTableDir.Offset);
		assert(sFonts[FontIndex].HheaTableDir.Offset);
		assert(sFonts[FontIndex].HmtxTableDir.Offset);

		fseek(File, (long)sFonts[FontIndex].HeadTableDir.Offset, SEEK_SET);
		sFonts[FontIndex].HeadTable.Version = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].HeadTable.FontRevision = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].HeadTable.CheckSumAdjustment = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].HeadTable.MagicNumber = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].HeadTable.Flags = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].HeadTable.UnitsPerEm = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].HeadTable.Created = FileReader_ReadInt64(File, true);
		sFonts[FontIndex].HeadTable.Modified = FileReader_ReadInt64(File, true);
		sFonts[FontIndex].HeadTable.MinX = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HeadTable.MinY = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HeadTable.MaxX = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HeadTable.MaxY = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HeadTable.MacStyle = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].HeadTable.LowestRecPPEM = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].HeadTable.FontDirectionHint = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HeadTable.IndexToLocFormat = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HeadTable.GlyphDataFormat = FileReader_ReadInt16(File, true);
		assert(sFonts[FontIndex].HeadTable.Version == 0x10000);
		assert(sFonts[FontIndex].HeadTable.MagicNumber == 0x5F0F3CF5);

		fseek(File, (long)sFonts[FontIndex].MaxpTableDir.Offset, SEEK_SET);
		sFonts[FontIndex].MaxpTable.Version = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].MaxpTable.NumGlyphs = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxPoints = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxContours = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxComponentPoints = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxComponentContours = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxZones = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxTwilightPoints = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxStorage = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxFunctionDefs = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxInstructionDefs = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxStackElements = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxSizeOfInstructions = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxComponentElements = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].MaxpTable.MaxComponentDepth = FileReader_ReadUInt16(File, true);
		assert(sFonts[FontIndex].MaxpTable.Version == 0x10000);

		fseek(File, (long)sFonts[FontIndex].CmapTableDir.Offset, SEEK_SET);
		sFonts[FontIndex].CmapTable.Version = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].CmapTable.NumberSubTables = FileReader_ReadUInt16(File, true);
		assert(sFonts[FontIndex].CmapTable.Version == 0x0);

		fseek(File, (long)sFonts[FontIndex].HheaTableDir.Offset, SEEK_SET);
		sFonts[FontIndex].HheaTable.Version = FileReader_ReadUInt32(File, true);
		sFonts[FontIndex].HheaTable.Ascent = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.Descent = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.LineGap = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.AdvanceWidthMax = FileReader_ReadUInt16(File, true);
		sFonts[FontIndex].HheaTable.MinLeftSideBearing = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.MinRightSideBearing = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.xMaxExtent = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.CaretSlopeRise = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.CaretSlopeRun = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.CaretOffset = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.Reserved0 = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.Reserved1 = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.Reserved2 = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.Reserved3 = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.MetricDataFormt = FileReader_ReadInt16(File, true);
		sFonts[FontIndex].HheaTable.NumOfLongHorMetrics = FileReader_ReadUInt16(File, true);
		assert(sFonts[FontIndex].MaxpTable.Version == 0x10000);

		short unsigned NumGlyphs = sFonts[FontIndex].MaxpTable.NumGlyphs;

		sFonts[FontIndex].Dilation = 0.0F;
		sFonts[FontIndex].Width = (int unsigned)(sFonts[FontIndex].HeadTable.MaxX - sFonts[FontIndex].HeadTable.MinX);
		sFonts[FontIndex].Height = (int unsigned)(sFonts[FontIndex].HeadTable.MaxY - sFonts[FontIndex].HeadTable.MinY);
		sFonts[FontIndex].Glyphs = (Glyph*)Memory_Alloc(NumGlyphs * sizeof(Glyph), 0);
		sFonts[FontIndex].GlyphOffsets = (int unsigned*)Memory_Alloc(NumGlyphs * sizeof(int unsigned), 0);
		sFonts[FontIndex].BezierOffsets = Vector_Alloc(sizeof(BezierOffsetEntry));
		sFonts[FontIndex].BezierCurves = Vector_Alloc(sizeof(BezierCurveEntry));

		for (short unsigned GlyphIndex = 0; GlyphIndex < NumGlyphs; GlyphIndex++)
		{
			if (sFonts[FontIndex].HeadTable.IndexToLocFormat)
			{
				fseek(File, (long)(sFonts[FontIndex].LocaTableDir.Offset + (GlyphIndex * 4U)), SEEK_SET);
				sFonts[FontIndex].GlyphOffsets[GlyphIndex] = sFonts[FontIndex].GlyfTableDir.Offset + FileReader_ReadUInt32(File, true);
			}
			else
			{
				fseek(File, (long)(sFonts[FontIndex].LocaTableDir.Offset + (GlyphIndex * 2U)), SEEK_SET);
				sFonts[FontIndex].GlyphOffsets[GlyphIndex] = sFonts[FontIndex].GlyfTableDir.Offset + FileReader_ReadUInt16(File, true) * 2U;
			}
		}

		sFonts[FontIndex].GlyphMapping = Font_UnicodeToGlyphMappingsInternal(File, FontIndex);

		BezierOffsetEntry CurrBezierOffset = {};

		for (short unsigned GlyphIndex = 0; GlyphIndex < NumGlyphs; GlyphIndex++)
		{
			Glyph* CurrGlyph = &sFonts[FontIndex].Glyphs[GlyphIndex];

			memset(CurrGlyph, 0, sizeof(Glyph));

			Font_ReadGlyphInternal(File, FontIndex, GlyphIndex, CurrGlyph);
			Font_CreateBezierInternal(FontIndex, CurrGlyph);

			CurrBezierOffset.Num = (int unsigned)Vector_Num(CurrGlyph->BezierCurves);
			Vector_Push(sFonts[FontIndex].BezierOffsets, &CurrBezierOffset);
			CurrBezierOffset.Start += CurrBezierOffset.Num;
			Vector_PushRange(sFonts[FontIndex].BezierCurves, CurrGlyph->BezierCurves);
		}

		Font_ApplyLayoutInfosInternal(File, FontIndex);

		glGenVertexArrays(1, &sFonts[FontIndex].GlyphVertexArray);
		glGenBuffers(1, &sFonts[FontIndex].GlyphVertexBuffer);
		glGenBuffers(1, &sFonts[FontIndex].GlyphIndexBuffer);
		glBindVertexArray(sFonts[FontIndex].GlyphVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sFonts[FontIndex].GlyphVertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(GlyphVertex), (void*)(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(GlyphVertex), (void*)(sizeof(Vector3)));
		glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(GlyphVertex), (void*)(sizeof(Vector3) + sizeof(Vector2)));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(GlyphVertex), (void*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(int unsigned)));
		glBufferData(GL_ARRAY_BUFFER, NumChars * 4 * sizeof(LineVertex), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sFonts[FontIndex].GlyphIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumChars * 6 * sizeof(int unsigned), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		void* BezierOffsetBuffer = Vector_Buffer(sFonts[FontIndex].BezierOffsets);
		long long unsigned NumBezierOffsets = Vector_Num(sFonts[FontIndex].BezierOffsets);

		//for (long long unsigned i = 0; i < NumBezierOffsets; i++)
		//{
		//	BezierOffsetEntry* Entry = (BezierOffsetEntry*)Vector_At(BezierOffsets, i);
		//
		//	printf("%llu %u %u\n", i, Entry->Start, Entry->Num);
		//}

		glGenBuffers(1, &sFonts[FontIndex].BezierOffsetBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, sFonts[FontIndex].BezierOffsetBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, (int unsigned)(NumBezierOffsets * sizeof(BezierOffsetEntry)), BezierOffsetBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		void* BezierCurveBuffer = Vector_Buffer(sFonts[FontIndex].BezierCurves);
		long long unsigned NumBezierCurves = Vector_Num(sFonts[FontIndex].BezierCurves);

		//for (long long unsigned i = 3408; i < (3408 + 20); i++)
		//{
		//	BezierCurveEntry* Entry = (BezierCurveEntry*)Vector_At(BezierCurves, i);
		//
		//	printf("(%f, %f) (%f, %f) (%f, %f)\n", Entry->P0[0], Entry->P0[1], Entry->P1[0], Entry->P1[1], Entry->P2[0], Entry->P2[1]);
		//}

		glGenBuffers(1, &sFonts[FontIndex].BezierCurveBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, sFonts[FontIndex].BezierCurveBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, (int unsigned)(NumBezierCurves * sizeof(BezierCurveEntry)), BezierCurveBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		fclose(File);
	}
	Glyph* Font_GlyphByGlyphIndex(int unsigned FontIndex, short unsigned GlyphIndex)
	{
		return &sFonts[FontIndex].Glyphs[GlyphIndex];
	}
	Glyph* Font_GlyphByUnicode(int unsigned FontIndex, int unsigned Unicode)
	{
		long long unsigned NumGlyphMaps = Vector_Num(sFonts[FontIndex].GlyphMapping);

		for (long long unsigned GlyphMapIndex = 0; GlyphMapIndex < NumGlyphMaps; GlyphMapIndex++)
		{
			GlyphMap* GlyphMapping = (GlyphMap*)Vector_At(sFonts[FontIndex].GlyphMapping, GlyphMapIndex);

			if (GlyphMapping->Unicode == Unicode)
			{
				return &sFonts[FontIndex].Glyphs[GlyphMapping->GlyphIndex];
			}
		}

		return 0;
	}
	short unsigned Font_NumGlyphs(int unsigned FontIndex)
	{
		return sFonts[FontIndex].MaxpTable.NumGlyphs;
	}
	void Font_Free(void)
	{
		for (int unsigned FontIndex = 0; FontIndex < sNumFonts; FontIndex++)
		{
			for (short unsigned GlyphIndex = 0; GlyphIndex < sFonts[FontIndex].MaxpTable.NumGlyphs; GlyphIndex++)
			{
				if (sFonts[FontIndex].Glyphs[GlyphIndex].ContourEndIndices) Memory_Free(sFonts[FontIndex].Glyphs[GlyphIndex].ContourEndIndices);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].Points) Memory_Free(sFonts[FontIndex].Glyphs[GlyphIndex].Points);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].Flags) Memory_Free(sFonts[FontIndex].Glyphs[GlyphIndex].Flags);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].Instructions) Memory_Free(sFonts[FontIndex].Glyphs[GlyphIndex].Instructions);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].PointOffsets) Vector_Free(sFonts[FontIndex].Glyphs[GlyphIndex].PointOffsets);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].BezierPoints) Vector_Free(sFonts[FontIndex].Glyphs[GlyphIndex].BezierPoints);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].BezierOffsets) Vector_Free(sFonts[FontIndex].Glyphs[GlyphIndex].BezierOffsets);
				if (sFonts[FontIndex].Glyphs[GlyphIndex].BezierCurves) Vector_Free(sFonts[FontIndex].Glyphs[GlyphIndex].BezierCurves);

				glDeleteVertexArrays(1, &sFonts[FontIndex].GlyphVertexArray);
				glDeleteBuffers(1, &sFonts[FontIndex].GlyphVertexBuffer);
				glDeleteBuffers(1, &sFonts[FontIndex].GlyphIndexBuffer);
				glDeleteBuffers(1, &sFonts[FontIndex].BezierOffsetBuffer);
				glDeleteBuffers(1, &sFonts[FontIndex].BezierCurveBuffer);
			}

			Vector_Free(sFonts[FontIndex].GlyphMapping);
			Vector_Free(sFonts[FontIndex].BezierOffsets);
			Vector_Free(sFonts[FontIndex].BezierCurves);
			Memory_Free(sFonts[FontIndex].GlyphOffsets);
			Memory_Free(sFonts[FontIndex].Glyphs);
		}

		Memory_Free(sFonts);
		Shader_Free(sFontProgram);
	}
	void Font_ReadGlyphInternal(FILE* File, int unsigned FontIndex, short unsigned GlyphIndex, Glyph* Result)
	{
		fseek(File, (long)sFonts[FontIndex].GlyphOffsets[GlyphIndex], SEEK_SET);

		Result->NumContours = FileReader_ReadInt16(File, true);
		Result->MinX = FileReader_ReadInt16(File, true);
		Result->MinY = FileReader_ReadInt16(File, true);
		Result->MaxX = FileReader_ReadInt16(File, true);
		Result->MaxY = FileReader_ReadInt16(File, true);
		Result->IsCompound = Result->NumContours < 0;
		Result->GlyphIndex = GlyphIndex;

		if (Result->IsCompound)
		{
			Font_ReadCompoundGlyphInternal(File, FontIndex, GlyphIndex, Result);
		}
		else
		{
			Font_ReadSimpleGlyphInternal(File, Result);
		}
	}
	void Font_ReadSimpleGlyphInternal(FILE* File, Glyph* Result)
	{
		if (Result->NumContours == 0)
		{
			return;
		}

		Result->ContourEndIndices = (short unsigned*)Memory_Alloc(Result->NumContours * sizeof(short unsigned), 0);
		FileReader_ReadUInt16Array(File, true, Result->ContourEndIndices, (int unsigned)Result->NumContours);

		Result->NumPoints = Result->ContourEndIndices[Result->NumContours - 1U] + 1U;
		Result->Points = (GlyphPoint*)Memory_Alloc(Result->NumPoints * sizeof(GlyphPoint), 0);
		Result->Flags = (char unsigned*)Memory_Alloc(Result->NumPoints, 0);

		Result->NumInstructions = FileReader_ReadUInt16(File, true);
		Result->Instructions = (char unsigned*)Memory_Alloc(Result->NumInstructions, 0);
		FileReader_ReadUInt8Array(File, Result->Instructions, Result->NumInstructions);

		for (short unsigned PointIndex = 0; PointIndex < Result->NumPoints; PointIndex++)
		{
			char unsigned Flag = FileReader_ReadUInt8(File);
			Result->Flags[PointIndex] = Flag;
			if (IS_BIT_SET(Flag, REPEAT_FLAG_BIT))
			{
				char unsigned NumRepeats = FileReader_ReadUInt8(File);
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
				char unsigned CoordOffset = FileReader_ReadUInt8(File);
				CoordX += IS_BIT_SET(Flag, X_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT) ? CoordOffset : -CoordOffset;
			}
			else if (IS_BIT_NOT_SET(Flag, X_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT))
			{
				CoordX += FileReader_ReadInt16(File, true);
			}

			Result->Points[PointIndex].X = CoordX;
			Result->Points[PointIndex].OnCurve = IS_BIT_SET(Flag, ON_CURVE_POINT_BIT);
		}

		for (short unsigned PointIndex = 0; PointIndex < Result->NumPoints; PointIndex++)
		{
			char unsigned Flag = Result->Flags[PointIndex];

			if (IS_BIT_SET(Flag, Y_SHORT_VECTOR_BIT))
			{
				char unsigned CoordOffset = FileReader_ReadUInt8(File);
				CoordY += IS_BIT_SET(Flag, Y_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT) ? CoordOffset : -CoordOffset;
			}
			else if (IS_BIT_NOT_SET(Flag, Y_IS_SAME_OR_POSITIVE_SHORT_VECTOR_BIT))
			{
				CoordY += FileReader_ReadInt16(File, true);
			}

			Result->Points[PointIndex].Y = CoordY;
			Result->Points[PointIndex].OnCurve = IS_BIT_SET(Flag, ON_CURVE_POINT_BIT);
		}
	}
	void Font_ReadCompoundGlyphInternal(FILE* File, int unsigned FontIndex, short unsigned GlyphIndex, Glyph* Result)
	{
		UNREFERENCED_PARAMETER(GlyphIndex);

		while (true)
		{
			short unsigned Flags = FileReader_ReadUInt16(File, true);
			short unsigned NewGlyphIndex = FileReader_ReadUInt16(File, true);

			assert(sFonts[FontIndex].GlyphOffsets[GlyphIndex] != sFonts[FontIndex].GlyphOffsets[NewGlyphIndex]);

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
				Arg0 = FileReader_ReadInt16(File, true);
				Arg1 = FileReader_ReadInt16(File, true);
			}
			else
			{
				Arg0 = FileReader_ReadInt8(File);
				Arg1 = FileReader_ReadInt8(File);
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
				short Value = FileReader_ReadInt16(File, true);

				IHatX = (double)Value / (double)(1 << 14);
				JHatY = (double)Value / (double)(1 << 14);
			}
			else if (IsXAndYScale)
			{
				short ValueIX = FileReader_ReadInt16(File, true);
				short ValueJY = FileReader_ReadInt16(File, true);

				IHatX = (double)ValueIX / (double)(1 << 14);
				JHatY = (double)ValueJY / (double)(1 << 14);
			}
			else if (Is2x2Matrix)
			{
				short ValueIX = FileReader_ReadInt16(File, true);
				short ValueIY = FileReader_ReadInt16(File, true);
				short ValueJX = FileReader_ReadInt16(File, true);
				short ValueJY = FileReader_ReadInt16(File, true);

				IHatX = (double)ValueIX / (double)(1 << 14);
				IHatY = (double)ValueIY / (double)(1 << 14);
				JHatX = (double)ValueJX / (double)(1 << 14);
				JHatY = (double)ValueJY / (double)(1 << 14);
			}

			int unsigned StoredLocation = (int unsigned)ftell(File);
			Glyph ResultGlyph = {};
			Font_ReadGlyphInternal(File, FontIndex, NewGlyphIndex, &ResultGlyph);
			fseek(File, (long)StoredLocation, SEEK_SET);

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
			Result->Points = (GlyphPoint*)Memory_Realloc(Result->Points, NumPoints * sizeof(GlyphPoint));

			for (short unsigned ContourIndex = 0; ContourIndex < ResultGlyph.NumContours; ContourIndex++)
			{
				Result->ContourEndIndices[Result->NumContours + ContourIndex] = (short unsigned)(Result->NumPoints + ResultGlyph.ContourEndIndices[ContourIndex]);
			}

			memcpy(&Result->Points[Result->NumPoints], ResultGlyph.Points, ResultGlyph.NumPoints * sizeof(GlyphPoint));

			Result->NumContours = (short)NumContours;
			Result->NumPoints = NumPoints;

			Memory_Free(ResultGlyph.ContourEndIndices);
			Memory_Free(ResultGlyph.Points);
			Memory_Free(ResultGlyph.Flags);
			Memory_Free(ResultGlyph.Instructions);

			if (IsMoreComponentsAfterThis == 0)
			{
				break;
			}
		}
	}
	void Font_ApplyLayoutInfosInternal(FILE* File, int unsigned FontIndex)
	{
		fseek(File, (long)sFonts[FontIndex].HmtxTableDir.Offset, SEEK_SET);

		short unsigned NumLongHorMetrics = sFonts[FontIndex].HheaTable.NumOfLongHorMetrics;
		short unsigned NumRem = (short unsigned)(sFonts[FontIndex].MaxpTable.NumGlyphs - NumLongHorMetrics);
		short Ascent = sFonts[FontIndex].HheaTable.Ascent;

		short unsigned LastAdvanceWidth = 0;
		for (short unsigned MetricIndex = 0; MetricIndex < NumLongHorMetrics; MetricIndex++)
		{
			short unsigned GlyphIndex = MetricIndex;
			short unsigned AdvanceWidth = FileReader_ReadUInt16(File, true);
			short LeftSideBearing = FileReader_ReadInt16(File, true);
			short TopSideBearing = sFonts[FontIndex].Glyphs[GlyphIndex].MaxY;

			LastAdvanceWidth = AdvanceWidth;

			Glyph* CurrGlyph = &sFonts[FontIndex].Glyphs[GlyphIndex];

			CurrGlyph->AdvanceWidth = AdvanceWidth;
			CurrGlyph->Width = (short unsigned)(CurrGlyph->MaxX - CurrGlyph->MinX);
			CurrGlyph->Height = (short unsigned)(CurrGlyph->MaxY - CurrGlyph->MinY);
			CurrGlyph->BearingX = (short unsigned)LeftSideBearing;
			CurrGlyph->BearingY = (short unsigned)(Ascent - TopSideBearing);
		}

		for (short unsigned RemIndex = 0; RemIndex < NumRem; RemIndex++)
		{
			short unsigned GlyphIndex = (short unsigned)(NumLongHorMetrics + RemIndex);
			short LeftSideBearing = FileReader_ReadInt16(File, true);
			short TopSideBearing = sFonts[FontIndex].Glyphs[GlyphIndex].MaxY;

			Glyph* CurrGlyph = &sFonts[FontIndex].Glyphs[GlyphIndex];

			CurrGlyph->AdvanceWidth = LastAdvanceWidth;
			CurrGlyph->Width = (short unsigned)(CurrGlyph->MaxX - CurrGlyph->MinX);
			CurrGlyph->Height = (short unsigned)(CurrGlyph->MaxY - CurrGlyph->MinY);
			CurrGlyph->BearingX = (short unsigned)LeftSideBearing;
			CurrGlyph->BearingY = (short unsigned)(Ascent - TopSideBearing);
		}
	}
	Vector* Font_UnicodeToGlyphMappingsInternal(FILE* File, int unsigned FontIndex)
	{
		Vector* GlyphMapping = Vector_Alloc(sizeof(GlyphMap));

		fseek(File, (long)sFonts[FontIndex].CmapTableDir.Offset + (long)sizeof(FontCmapTable), SEEK_SET);

		int SelectedUnicodeVersionID = -1;
		int unsigned CmapSubTableOffset = 0;
		for (int unsigned SubTableIndex = 0; SubTableIndex < sFonts[FontIndex].CmapTable.NumberSubTables; SubTableIndex++)
		{
			FontCmapSubTable CmapSubTable = {};
			CmapSubTable.PlatformID = FileReader_ReadUInt16(File, true);
			CmapSubTable.PlatformSpecificID = FileReader_ReadUInt16(File, true);
			CmapSubTable.Offset = FileReader_ReadUInt32(File, true);

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

		fseek(File, (long)sFonts[FontIndex].CmapTableDir.Offset + (long)CmapSubTableOffset, SEEK_SET);

		short unsigned Format = FileReader_ReadUInt16(File, true);
		assert((Format == 4) || (Format == 12));

		bool HasMissingGlyphs = false;

		switch (Format)
		{
		case 4:
		{
			short unsigned Length = FileReader_ReadUInt16(File, true);
			short unsigned Language = FileReader_ReadUInt16(File, true);
			short unsigned NumSegX2 = FileReader_ReadUInt16(File, true);
			short unsigned SearchRange = FileReader_ReadUInt16(File, true);
			short unsigned EntrySelector = FileReader_ReadUInt16(File, true);
			short unsigned RangeShift = FileReader_ReadUInt16(File, true);
			short unsigned NumSeg = NumSegX2 / 2U;

			UNREFERENCED_PARAMETER(Length);
			UNREFERENCED_PARAMETER(Language);
			UNREFERENCED_PARAMETER(SearchRange);
			UNREFERENCED_PARAMETER(EntrySelector);
			UNREFERENCED_PARAMETER(RangeShift);

			short unsigned* EndCodes = (short unsigned*)Memory_Alloc(NumSeg * sizeof(short unsigned), 0);
			FileReader_ReadUInt16Array(File, true, EndCodes, NumSeg);

			short unsigned Reserved = FileReader_ReadUInt16(File, true);
			UNREFERENCED_PARAMETER(Reserved);

			short unsigned* StartCodes = (short unsigned*)Memory_Alloc(NumSeg * sizeof(short unsigned), 0);
			FileReader_ReadUInt16Array(File, true, StartCodes, NumSeg);

			short unsigned* IDDeltas = (short unsigned*)Memory_Alloc(NumSeg * sizeof(short unsigned), 0);
			FileReader_ReadUInt16Array(File, true, IDDeltas, NumSeg);

			struct IDRangeOffsetMap
			{
				int unsigned ReadLocation;
				short unsigned RangeOffset;
			};
			IDRangeOffsetMap* IDRangeOffsets = (IDRangeOffsetMap*)Memory_Alloc(NumSeg * sizeof(IDRangeOffsetMap), 0);

			for (short unsigned SegmentIndex = 0; SegmentIndex < NumSeg; SegmentIndex++)
			{
				IDRangeOffsets[SegmentIndex].ReadLocation = (int unsigned)ftell(File);
				IDRangeOffsets[SegmentIndex].RangeOffset = FileReader_ReadUInt16(File, true);
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

					if (IDRangeOffsets[SegmentIndex].RangeOffset == 0)
					{
						GlyphIndex = (CurrCode + IDDeltas[SegmentIndex]) % 0x10000U;
					}
					else
					{
						int unsigned StoredLocation = (int unsigned)ftell(File);
						int unsigned RangeOffsetLocation = IDRangeOffsets[SegmentIndex].ReadLocation + IDRangeOffsets[SegmentIndex].RangeOffset;
						int unsigned GlyphIndexArrayLocation = 2U * (CurrCode - StartCodes[SegmentIndex]) + RangeOffsetLocation;

						fseek(File, (long)GlyphIndexArrayLocation, SEEK_SET);

						GlyphIndex = FileReader_ReadUInt16(File, true);

						if (GlyphIndex != 0)
						{
							GlyphIndex = (GlyphIndex + IDDeltas[SegmentIndex]) % 0x10000U;
						}

						fseek(File, (long)StoredLocation, SEEK_SET);
					}

					GlyphMap Mapping = { GlyphIndex, CurrCode };
					Vector_Push(GlyphMapping, &Mapping);

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
			short unsigned Reserved = FileReader_ReadUInt16(File, true);
			int unsigned Length = FileReader_ReadUInt32(File, true);
			int unsigned Language = FileReader_ReadUInt32(File, true);
			int unsigned NumGroups = FileReader_ReadUInt32(File, true);

			UNREFERENCED_PARAMETER(Reserved);
			UNREFERENCED_PARAMETER(Length);
			UNREFERENCED_PARAMETER(Language);

			for (int unsigned GroupIndex = 0; GroupIndex < NumGroups; GroupIndex++)
			{
				int unsigned StartCharCode = FileReader_ReadUInt32(File, true);
				int unsigned EndCharCode = FileReader_ReadUInt32(File, true);
				int unsigned StartGlyphCode = FileReader_ReadUInt32(File, true);
				int unsigned NumChars = EndCharCode - StartCharCode + 1;

				for (int unsigned CharIndex = 0; CharIndex < NumChars; CharIndex++)
				{
					short unsigned GlyphIndex = (short unsigned)(StartGlyphCode + CharIndex);
					int unsigned CharCode = StartCharCode + CharIndex;

					GlyphMap Mapping = { GlyphIndex, CharCode };
					Vector_Push(GlyphMapping, &Mapping);

					HasMissingGlyphs |= GlyphIndex == 0;
				}
			}

			break;
		}
		}

		if (HasMissingGlyphs == 0)
		{
			GlyphMap Mapping = { 0, 0xFFFF };
			Vector_Push(GlyphMapping, &Mapping);
		}

		return GlyphMapping;
	}
	void Font_CreateBezierInternal(int unsigned FontIndex, Glyph* Glyph)
	{
		Glyph->PointOffsets = Vector_Alloc(sizeof(PointOffsetEntry));
		Glyph->BezierPoints = Vector_Alloc(sizeof(Vector2));
		Glyph->BezierOffsets = Vector_Alloc(sizeof(BezierOffsetEntry));
		Glyph->BezierCurves = Vector_Alloc(sizeof(BezierCurveEntry));

		Vector* CollectedPoints = Vector_Alloc(sizeof(Vector2));

		short unsigned UnitsPerEm = sFonts[FontIndex].HeadTable.UnitsPerEm;
		short unsigned ContourStartIndex = 0;

		PointOffsetEntry CurrPointOffset = {};
		BezierOffsetEntry CurrBezierOffset = {};

		for (short unsigned ContourIndex = 0; ContourIndex < Glyph->NumContours; ContourIndex++)
		{
			short unsigned ContourEndIndex = Glyph->ContourEndIndices[ContourIndex];
			short unsigned NumContourPoints = (short unsigned)(ContourEndIndex - ContourStartIndex);

			for (short unsigned PointIndex = ContourStartIndex; PointIndex < (ContourStartIndex + NumContourPoints); PointIndex++)
			{
				GlyphPoint* CurrGlyphPoint = &Glyph->Points[(PointIndex + 0) % Glyph->NumPoints];
				GlyphPoint* NextGlyphPoint = &Glyph->Points[(PointIndex + 1) % Glyph->NumPoints];

				Vector2 Point = { (float)CurrGlyphPoint->X / UnitsPerEm, (float)CurrGlyphPoint->Y / UnitsPerEm };
				Vector_Push(CollectedPoints, &Point);

				bool IsConsecutiveOffCurvePoints = !CurrGlyphPoint->OnCurve && !NextGlyphPoint->OnCurve;
				bool IsStraightLine = CurrGlyphPoint->OnCurve && NextGlyphPoint->OnCurve;

				if (IsConsecutiveOffCurvePoints || IsStraightLine)
				{
					Vector2 MidPoint = { (float)(CurrGlyphPoint->X + NextGlyphPoint->X) / 2.0F / UnitsPerEm, (float)(CurrGlyphPoint->Y + NextGlyphPoint->Y) / 2.0F / UnitsPerEm };
					Vector_Push(CollectedPoints, &MidPoint);
				}
			}

			GlyphPoint* LastGlyphPoint = &Glyph->Points[ContourStartIndex + NumContourPoints];
			GlyphPoint* FirstGlyphPoint = &Glyph->Points[ContourStartIndex];
			
			Vector2 LastPoint = { (float)LastGlyphPoint->X / UnitsPerEm, (float)LastGlyphPoint->Y / UnitsPerEm };
			Vector_Push(CollectedPoints, &LastPoint);
			
			bool IsConsecutiveOffCurvePoints = !LastGlyphPoint->OnCurve && !FirstGlyphPoint->OnCurve;
			bool IsStraightLine = LastGlyphPoint->OnCurve && FirstGlyphPoint->OnCurve;
			
			if (IsConsecutiveOffCurvePoints || IsStraightLine)
			{
				Vector2 MidPoint = { (float)(LastGlyphPoint->X + FirstGlyphPoint->X) / 2.0F / UnitsPerEm, (float)(LastGlyphPoint->Y + FirstGlyphPoint->Y) / 2.0F / UnitsPerEm };
				Vector_Push(CollectedPoints, &MidPoint);
			}

			Vector2 FirstPoint = { (float)FirstGlyphPoint->X / UnitsPerEm, (float)FirstGlyphPoint->Y / UnitsPerEm };
			Vector_Push(CollectedPoints, &FirstPoint);

			CurrPointOffset.Num = (int unsigned)Vector_Num(CollectedPoints);
			Vector_Push(Glyph->PointOffsets, &CurrPointOffset);
			CurrPointOffset.Start += CurrPointOffset.Num;

			Vector_PushRange(Glyph->BezierPoints, CollectedPoints);
			Vector_Clear(CollectedPoints);

			ContourStartIndex = ContourEndIndex + 1U;
		}

		bool ContourComplete = false;
		long long unsigned NumBezierPoints = Vector_Num(Glyph->BezierPoints);

		for (long long unsigned BezierPointIndex = 0; BezierPointIndex < NumBezierPoints; BezierPointIndex += 2)
		{
			int unsigned I0 = (int unsigned)BezierPointIndex + 0;
			int unsigned I1 = (int unsigned)BezierPointIndex + 1;
			int unsigned I2 = (int unsigned)BezierPointIndex + 2;
			long long unsigned NumPointOffsets = Vector_Num(Glyph->PointOffsets);

			for (long long unsigned PointOffsetIndex = 0; PointOffsetIndex < NumPointOffsets; PointOffsetIndex++)
			{
				PointOffsetEntry* PointOffset = (PointOffsetEntry*)Vector_At(Glyph->PointOffsets, PointOffsetIndex);

				int unsigned StartOffset = PointOffset->Start;
				int unsigned EndOffset = PointOffset->Start + PointOffset->Num;
				//int unsigned NumPoints = EndOffset - StartOffset;

				if (I0 >= StartOffset && I0 < EndOffset)
				{
					if (I1 >= EndOffset || I2 >= EndOffset)
					{
						I1 = I0; // StartOffset + (I1 % NumPoints);
						I2 = I0; // StartOffset + (I2 % NumPoints);

						ContourComplete = true;
					}

					break;
				}
			}

			Vector2* P0 = (Vector2*)Vector_At(Glyph->BezierPoints, I0);
			Vector2* P1 = (Vector2*)Vector_At(Glyph->BezierPoints, I1);
			Vector2* P2 = (Vector2*)Vector_At(Glyph->BezierPoints, I2);

			BezierCurveEntry BezierCurve = {};

			Vector2_Set(*P0, BezierCurve.P0);
			Vector2_Set(*P1, BezierCurve.P1);
			Vector2_Set(*P2, BezierCurve.P2);

			Vector_Push(Glyph->BezierCurves, &BezierCurve);

			CurrBezierOffset.Num++;

			if (ContourComplete)
			{
				ContourComplete = false;

				Vector_Push(Glyph->BezierOffsets, &CurrBezierOffset);
				CurrBezierOffset.Start += CurrBezierOffset.Num;
				CurrBezierOffset.Num = 0;
			}
		}

		// Remove me!
		//long long unsigned NumBezierOffsets = Vector_Num(Glyph->BezierOffsets);
		//for (long long unsigned i = 0; i < NumBezierOffsets; i++)
		//{
		//	BezierOffsetEntry* Entry = (BezierOffsetEntry*)Vector_At(Glyph->BezierOffsets, i);
		//
		//	printf("%llu %u %u\n", i, Entry->Start, Entry->Num);
		//}
		//
		//long long unsigned NumBezierCurves = Vector_Num(Glyph->BezierCurves);
		//for (long long unsigned i = 0; i < NumBezierCurves; i++)
		//{
		//	BezierCurveEntry* Entry = (BezierCurveEntry*)Vector_At(Glyph->BezierCurves, i);
		//
		//	printf("(%f, %f) (%f, %f) (%f, %f)\n", Entry->P0[0], Entry->P0[1], Entry->P1[0], Entry->P1[1], Entry->P2[0], Entry->P2[1]);
		//}

		Vector_Free(CollectedPoints);
	}
	void Font_DebugGlyphsInternal(int unsigned FontIndex, Matrix4 Projection, Matrix4 View)
	{
		short unsigned UnitsPerEm = sFonts[FontIndex].HeadTable.UnitsPerEm;

		float OffsetX = 0.0F;
		float IncrementX = 10.0F;
		float Scale = 10.0F;

		for (short unsigned GlyphIndex = 0; GlyphIndex < 10; GlyphIndex++)
		{
			Glyph* Glyph = Font_GlyphByGlyphIndex(FontIndex, GlyphIndex);

			if (Glyph)
			{
				Gizmo_BeginLines();
				{
					short unsigned ContourStartIndex = 0;
					for (short unsigned ContourIndex = 0; ContourIndex < Glyph->NumContours; ContourIndex++)
					{
						short unsigned ContourEndIndex = Glyph->ContourEndIndices[ContourIndex];
						short unsigned NumContourPoints = (short unsigned)(ContourEndIndex - ContourStartIndex);
				
						for (short unsigned PointIndex = ContourStartIndex; PointIndex < (ContourStartIndex + NumContourPoints); PointIndex++)
						{
							float FromX = (float)Glyph->Points[PointIndex].X / UnitsPerEm * Scale;
							float FromY = (float)Glyph->Points[PointIndex].Y / UnitsPerEm * Scale;
							float ToX = (float)Glyph->Points[(PointIndex + 1) % Glyph->NumPoints].X / UnitsPerEm * Scale;
							float ToY = (float)Glyph->Points[(PointIndex + 1) % Glyph->NumPoints].Y / UnitsPerEm * Scale;
				
							Gizmo_DrawLineSimple(GIZMO_DIR_XY, OffsetX + FromX, FromY, 0.0F, OffsetX + ToX, ToY, 0.0F, 0.05F, 0x888888FF);
						}
				
						float FromX = (float)Glyph->Points[ContourEndIndex].X / UnitsPerEm * Scale;
						float FromY = (float)Glyph->Points[ContourEndIndex].Y / UnitsPerEm * Scale;
						float ToX = (float)Glyph->Points[ContourStartIndex].X / UnitsPerEm * Scale;
						float ToY = (float)Glyph->Points[ContourStartIndex].Y / UnitsPerEm * Scale;
				
						Gizmo_DrawLineSimple(GIZMO_DIR_XY, OffsetX + FromX, FromY, 0.0F, OffsetX + ToX, ToY, 0.0F, 0.05F, 0x888888FF);
				
						ContourStartIndex = ContourEndIndex + 1U;
					}
				}
				Gizmo_EndLines(Projection, View);

				Gizmo_BeginLines();
				{
					long long unsigned NumBezierOffsets = Vector_Num(Glyph->BezierOffsets);
					for (long long unsigned BezierOffsetIndex = 0; BezierOffsetIndex < NumBezierOffsets; BezierOffsetIndex++)
					{
						BezierOffsetEntry* BezierOffset = (BezierOffsetEntry*)Vector_At(Glyph->BezierOffsets, BezierOffsetIndex);

						for (int unsigned BezierCurveIndex = BezierOffset->Start; BezierCurveIndex < (BezierOffset->Start + BezierOffset->Num); BezierCurveIndex++)
						{
							BezierCurveEntry* BezierCurve = (BezierCurveEntry*)Vector_At(Glyph->BezierCurves, BezierCurveIndex);
							
							float X0 = OffsetX + BezierCurve->P0[0] * Scale;
							float Y0 = BezierCurve->P0[1] * Scale;
							
							float X1 = OffsetX + BezierCurve->P1[0] * Scale;
							float Y1 = BezierCurve->P1[1] * Scale;
							
							float X2 = OffsetX + BezierCurve->P2[0] * Scale;
							float Y2 = BezierCurve->P2[1] * Scale;
							
							Gizmo_DrawLineBezierQuadraticSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, X1, Y1, 0.0F, X2, Y2, 0.0F, 10, 0.05F, 0x880000FF);
						}
					}

					//long long unsigned NumBezierCurves = Vector_Num(Glyph->BezierCurves);
					//for (long long unsigned BezierCurveIndex = 0; BezierCurveIndex < NumBezierCurves; BezierCurveIndex++)
					//{
					//	BezierCurveEntry* BezierCurve = (BezierCurveEntry*)Vector_At(Glyph->BezierCurves, BezierCurveIndex);
					//
					//	float X0 = OffsetX + BezierCurve->P0[0] * Scale;
					//	float Y0 = BezierCurve->P0[1] * Scale;
					//
					//	float X1 = OffsetX + BezierCurve->P1[0] * Scale;
					//	float Y1 = BezierCurve->P1[1] * Scale;
					//
					//	float X2 = OffsetX + BezierCurve->P2[0] * Scale;
					//	float Y2 = BezierCurve->P2[1] * Scale;
					//
					//	Gizmo_DrawLineBezierQuadraticSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, X1, Y1, 0.0F, X2, Y2, 0.0F, 10, 0x880000FF);
					//}
				}
				Gizmo_EndLines(Projection, View);

				Gizmo_BeginPoints();
				{
					long long unsigned NumBezierCurves = Vector_Num(Glyph->BezierCurves);
					for (long long unsigned BezierCurveIndex = 0; BezierCurveIndex < NumBezierCurves; BezierCurveIndex++)
					{
						BezierCurveEntry* BezierCurve = (BezierCurveEntry*)Vector_At(Glyph->BezierCurves, BezierCurveIndex);
					
						float X0 = OffsetX + BezierCurve->P0[0] * Scale;
						float Y0 = BezierCurve->P0[1] * Scale;

						float X1 = OffsetX + BezierCurve->P1[0] * Scale;
						float Y1 = BezierCurve->P1[1] * Scale;

						float X2 = OffsetX + BezierCurve->P2[0] * Scale;
						float Y2 = BezierCurve->P2[1] * Scale;
					
						Gizmo_DrawPointSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, 0.15F, 0xFF0000FF);
						Gizmo_DrawPointSimple(GIZMO_DIR_XY, X1, Y1, 0.0F, 0.15F, 0xFF0000FF);
						Gizmo_DrawPointSimple(GIZMO_DIR_XY, X2, Y2, 0.0F, 0.15F, 0xFF0000FF);
					}
					// TODO
					BezierCurveEntry* BezierCurve = (BezierCurveEntry*)Vector_At(Glyph->BezierCurves, 0);

					float X0 = OffsetX + BezierCurve->P0[0] * Scale;
					float Y0 = BezierCurve->P0[1] * Scale;

					float X1 = OffsetX + BezierCurve->P1[0] * Scale;
					float Y1 = BezierCurve->P1[1] * Scale;

					float X2 = OffsetX + BezierCurve->P2[0] * Scale;
					float Y2 = BezierCurve->P2[1] * Scale;

					Gizmo_DrawPointSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, 0.15F, 0x00FF00FF);
					Gizmo_DrawPointSimple(GIZMO_DIR_XY, X1, Y1, 0.0F, 0.15F, 0x00FF00FF);
					Gizmo_DrawPointSimple(GIZMO_DIR_XY, X2, Y2, 0.0F, 0.15F, 0x00FF00FF);
					// TODO
					BezierCurveEntry* BezierCurve2 = (BezierCurveEntry*)Vector_At(Glyph->BezierCurves, 1);

					X0 = OffsetX + BezierCurve2->P0[0] * Scale;
					Y0 = BezierCurve2->P0[1] * Scale;

					X1 = OffsetX + BezierCurve2->P1[0] * Scale;
					Y1 = BezierCurve2->P1[1] * Scale;

					X2 = OffsetX + BezierCurve2->P2[0] * Scale;
					Y2 = BezierCurve2->P2[1] * Scale;

					Gizmo_DrawPointSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, 0.15F, 0x0000FFFF);
					Gizmo_DrawPointSimple(GIZMO_DIR_XY, X1, Y1, 0.0F, 0.15F, 0x0000FFFF);
					Gizmo_DrawPointSimple(GIZMO_DIR_XY, X2, Y2, 0.0F, 0.15F, 0x0000FFFF);
				}
				Gizmo_EndPoints(Projection, View);
			}

			OffsetX += IncrementX;
		}
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Text Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Text_Begin(int unsigned FontIndex)
	{
		sCurrFontIndex = FontIndex;

		Font* CurrFont = &sFonts[sCurrFontIndex];

		CurrFont->CharVertexOffset = 0;
		CurrFont->CharIndexOffset = 0;
	}
	void Text_Draw(char const* Text, Vector3 Position, float Scale, int unsigned Color)
	{
		Font* CurrFont = &sFonts[sCurrFontIndex];

		int unsigned VertexBufferOffset = 0;
		int unsigned IndexBufferOffset = 0;
		int unsigned TextLength = (int unsigned)strlen(Text);
		short unsigned UnitsPerEm = CurrFont->HeadTable.UnitsPerEm;

		glBindBuffer(GL_ARRAY_BUFFER, CurrFont->GlyphVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurrFont->GlyphIndexBuffer);

		GlyphVertex* VertexBuffer = (GlyphVertex*)glMapBufferRange(GL_ARRAY_BUFFER, CurrFont->CharVertexOffset * sizeof(GlyphVertex), TextLength * 4 * sizeof(GlyphVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, CurrFont->CharIndexOffset * sizeof(int unsigned), TextLength * 6 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

		float X = Position[0];
		float Y = Position[1];

		Y -= ((float)CurrFont->Height / UnitsPerEm) * Scale;

		for (char const* CharCode = Text; *CharCode != 0; CharCode++)
		{
			switch (*CharCode)
			{
			case '\r':
			{
				break;
			}
			case '\n':
			{
				X = Position[0];
				Y -= ((float)CurrFont->Height / UnitsPerEm) * Scale;

				break;
			}
			default:
			{
				Glyph* CurrGlyph = Font_GlyphByUnicode(sCurrFontIndex, (int unsigned)*CharCode);

				if (CurrGlyph->NumPoints)
				{
					float D = UnitsPerEm * CurrFont->Dilation;

					float U0 = ((float)CurrGlyph->BearingX - D) / UnitsPerEm;
					float V0 = ((float)CurrGlyph->BearingY - D) / UnitsPerEm;
					float U1 = ((float)CurrGlyph->BearingX - (float)CurrGlyph->Width - D) / UnitsPerEm;
					float V1 = ((float)CurrGlyph->BearingY - (float)CurrGlyph->Height - D) / UnitsPerEm;

					float X0 = X + U0 * Scale;
					float Y0 = Y + V0 * Scale;
					float X1 = X + U1 * Scale;
					float Y1 = Y + V1 * Scale;

					VertexBuffer[VertexBufferOffset + 0].Position[0] = X0;
					VertexBuffer[VertexBufferOffset + 0].Position[1] = Y0;
					VertexBuffer[VertexBufferOffset + 0].Position[2] = Position[2];
					VertexBuffer[VertexBufferOffset + 0].TextureCoords[0] = U0;
					VertexBuffer[VertexBufferOffset + 0].TextureCoords[1] = V0;
					VertexBuffer[VertexBufferOffset + 0].GlyphIndex = CurrGlyph->GlyphIndex;
					VertexBuffer[VertexBufferOffset + 0].Color = Color;

					VertexBuffer[VertexBufferOffset + 1].Position[0] = X1;
					VertexBuffer[VertexBufferOffset + 1].Position[1] = Y0;
					VertexBuffer[VertexBufferOffset + 1].Position[2] = Position[2];
					VertexBuffer[VertexBufferOffset + 1].TextureCoords[0] = U1;
					VertexBuffer[VertexBufferOffset + 1].TextureCoords[1] = V0;
					VertexBuffer[VertexBufferOffset + 1].GlyphIndex = CurrGlyph->GlyphIndex;
					VertexBuffer[VertexBufferOffset + 1].Color = Color;

					VertexBuffer[VertexBufferOffset + 2].Position[0] = X1;
					VertexBuffer[VertexBufferOffset + 2].Position[1] = Y1;
					VertexBuffer[VertexBufferOffset + 2].Position[2] = Position[2];
					VertexBuffer[VertexBufferOffset + 2].TextureCoords[0] = U1;
					VertexBuffer[VertexBufferOffset + 2].TextureCoords[1] = V1;
					VertexBuffer[VertexBufferOffset + 2].GlyphIndex = CurrGlyph->GlyphIndex;
					VertexBuffer[VertexBufferOffset + 2].Color = Color;

					VertexBuffer[VertexBufferOffset + 3].Position[0] = X0;
					VertexBuffer[VertexBufferOffset + 3].Position[1] = Y1;
					VertexBuffer[VertexBufferOffset + 3].Position[2] = Position[2];
					VertexBuffer[VertexBufferOffset + 3].TextureCoords[0] = U0;
					VertexBuffer[VertexBufferOffset + 3].TextureCoords[1] = V1;
					VertexBuffer[VertexBufferOffset + 3].GlyphIndex = CurrGlyph->GlyphIndex;
					VertexBuffer[VertexBufferOffset + 3].Color = Color;

					IndexBuffer[IndexBufferOffset + 0] = VertexBufferOffset + 0;
					IndexBuffer[IndexBufferOffset + 1] = VertexBufferOffset + 1;
					IndexBuffer[IndexBufferOffset + 2] = VertexBufferOffset + 2;

					IndexBuffer[IndexBufferOffset + 3] = VertexBufferOffset + 2;
					IndexBuffer[IndexBufferOffset + 4] = VertexBufferOffset + 3;
					IndexBuffer[IndexBufferOffset + 5] = VertexBufferOffset + 0;

					VertexBufferOffset += 4;
					IndexBufferOffset += 6;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Scale;

				break;
			}
			}
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		CurrFont->CharVertexOffset += VertexBufferOffset;
		CurrFont->CharIndexOffset += IndexBufferOffset;
	}
	void Text_End(Matrix4 Projection, Matrix4 View)
	{
		Font* CurrFont = &sFonts[sCurrFontIndex];

		glUseProgram(sFontProgram);
		int unsigned ProjectionMatrixLocation = glGetUniformLocation(sFontProgram, "ProjectionMatrix");
		int unsigned ViewMatrixLocation = glGetUniformLocation(sFontProgram, "ViewMatrix");
		glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
		glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, CurrFont->BezierOffsetBuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, CurrFont->BezierCurveBuffer);
		glBindVertexArray(CurrFont->GlyphVertexArray);
		glDrawElements(GL_TRIANGLES, (int)CurrFont->CharIndexOffset, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
#endif // FAST_GL_IMPLEMENTATION

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FAST_GL_H
