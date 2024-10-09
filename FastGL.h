#ifndef FAST_GL_H
#define FAST_GL_H

/*
#define FAST_GL_IMPLEMENTATION
#include "FastGL.h"

int main()
{
	WindowAlloc(800, 800, "FastGL");
	GizmoAlloc(66, 0);

	Vector3 Eye = { 0.0F, 0.0F, -10.0F };
	Vector3 Center = { 0.0F, 0.0F, 0.0F };
	Vector3 Up = { 0.0F, 1.0F, 0.0F };

	Matrix4 Projection = MATRIX4_IDENTITY;
	Matrix4 View = MATRIX4_IDENTITY;

	while (!WindowShouldClose())
	{
		WindowPollEvents();

		float Width = WindowWidth();
		float Height = WindowHeight();
		float MouseX = WindowMousePositionX();
		float MouseY = WindowMousePositionY();
		float FieldOfView = DEG2RAD(45.0F);
		float AspectRatio = Width / Height;

		WindowToNDC(&MouseX, &MouseY);

		WindowViewport((int unsigned)Width, (int unsigned)Height);
		WindowClear(0.0F, 0.0F, 0.0F, 0.0F, GL_COLOR_BUFFER_BIT);

		//Matrix4_Perspective(FieldOfView, AspectRatio, 0.001F, 1000.0F, Projection);
		Matrix4_Orthographic(-1.0F, 1.0F, -1.0F, 1.0F, 0.001F, 1000.0F, Projection);
		//Matrix4_LookAt(Eye, Center, Up, View);

		GizmoBeginLines();
		GizmoDrawLineSimple(0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0xFF0000FF);
		GizmoDrawLineSimple(0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0x00FF00FF);
		GizmoDrawLineCircleSimple(0.0F, 0.0F, 0.0F, 32, 0.4F, 0xFF00FFFF);
		GizmoDrawLineCircleSimple(MouseX, MouseY, 0.0F, 32, 0.4F, 0xFFFF00FF);
		GizmoDrawLines(Projection, View);

		WindowSwapBuffers();
	}

	GizmoFree();
	WindowFree();

	return 0;
}
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#include <Windows.h>

#include <gl/GL.h>

#pragma comment(lib, "Opengl32.lib")

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

///////////////////////////////////////////////////////////////
// Global Macros
///////////////////////////////////////////////////////////////

#ifndef MAX
	#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#endif // MAX

#ifndef MIN
	#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#endif // MIN

#ifndef PI
	#define PI (3.1415926F)
#endif // PI

#ifndef SQRT_3
	#define SQRT_3 (1.7320508F)
#endif // SQRT_3

#ifndef DEG2RAD
	#define DEG2RAD(DEGREES) (DEGREES * 0.0174532F)
#endif // DEG2RAD

#ifndef RAD2DEG
	#define RAD2DEG(RADIANS) (RADIANS * 57.2957795F)
#endif // RAD2DEG

#ifndef SHADER_CHECK_COMPILE_STATUS
	#ifdef FAST_GL_DEBUG
		#define SHADER_CHECK_COMPILE_STATUS(SHADER) \
			{ \
				int CompileStatus = 0, InfoLogLength = 0; \
				char Log[0x400] = { 0 }; \
				glGetShaderiv(SHADER, GL_COMPILE_STATUS, &CompileStatus); \
				if (CompileStatus == 0) \
				{ \
					glGetShaderiv(SHADER, GL_INFO_LOG_LENGTH, &InfoLogLength); \
					if (InfoLogLength > 0) \
					{ \
						InfoLogLength = MIN(InfoLogLength, (int)sizeof(Log)); \
						glGetShaderInfoLog(SHADER, InfoLogLength, &InfoLogLength, Log); \
						printf(Log); \
					} \
				} \
			}
	#else
		#define SHADER_CHECK_COMPILE_STATUS(SHADER)
	#endif // FAST_GL_DEBUG
#endif // SHADER_CHECK_COMPILE_STATUS

#ifndef PROGRAM_CHECK_LINK_STATUS
	#ifdef FAST_GL_DEBUG
		#define PROGRAM_CHECK_LINK_STATUS(PROGRAM) \
			{ \
				int CompileStatus = 0, InfoLogLength = 0; \
				char Log[0x400] = { 0 }; \
				glGetProgramiv(PROGRAM, GL_LINK_STATUS, &CompileStatus); \
				if (CompileStatus == 0) \
				{ \
					glGetProgramiv(PROGRAM, GL_INFO_LOG_LENGTH, &InfoLogLength); \
					if (InfoLogLength > 0) \
					{ \
						InfoLogLength = MIN(InfoLogLength, (int)sizeof(Log)); \
						glGetProgramInfoLog(PROGRAM, InfoLogLength, &InfoLogLength, &Log[0]); \
						printf(Log); \
					} \
				} \
			}
	#else
		#define PROGRAM_CHECK_LINK_STATUS(PROGRAM)
	#endif // FAST_GL_DEBUG
#endif // PROGRAM_CHECK_LINK_STATUS

#ifndef ALIGN_DOWN_BY
	#define ALIGN_DOWN_BY(VALUE, ALIGNMENT) (((long long unsigned)VALUE) & ~(((long long unsigned)ALIGNMENT) - 1))
#endif // ALIGN_DOWN_BY

#ifndef ALIGN_UP_BY
	#define ALIGN_UP_BY(VALUE, ALIGNMENT) ((((long long unsigned)VALUE) + (((long long unsigned)ALIGNMENT) - 1)) & ~(((long long unsigned)ALIGNMENT) - 1))
#endif // ALIGN_UP_BY

#ifndef L2B_ENDIAN_16
	#define L2B_ENDIAN_16(VALUE) \
		((((VALUE) & 0xFF) << 8) | \
		 (((VALUE) & 0xFF00) >> 8))
#endif // L2B_ENDIAN_16

#ifndef B2L_ENDIAN_16
	#define B2L_ENDIAN_16(VALUE) \
		((((VALUE) & 0xFF) << 8) | \
		 (((VALUE) & 0xFF00) >> 8))
#endif // B2L_ENDIAN_16

#ifndef L2B_ENDIAN_32
	#define L2B_ENDIAN_32(VALUE) \
		((((VALUE) & 0xFFUL) << 24) | \
		 (((VALUE) & 0xFF00UL) << 8) | \
		 (((VALUE) & 0xFF0000UL) >> 8) | \
		 (((VALUE) & 0xFF000000UL) >> 24))
#endif // L2B_ENDIAN_32

#ifndef B2L_ENDIAN_32
	#define B2L_ENDIAN_32(VALUE) \
		((((VALUE) & 0xFFUL) << 24) | \
		 (((VALUE) & 0xFF00UL) << 8) | \
		 (((VALUE) & 0xFF0000UL) >> 8) | \
		 (((VALUE) & 0xFF000000UL) >> 24))
#endif // B2L_ENDIAN_32

#ifndef L2B_ENDIAN_64
	#define L2B_ENDIAN_64(VALUE) \
		((((VALUE) & 0xFFULL) << 56) | \
		 (((VALUE) & 0xFF00ULL) << 40) | \
		 (((VALUE) & 0xFF0000ULL) << 24) | \
		 (((VALUE) & 0xFF000000ULL) << 8) | \
		 (((VALUE) & 0xFF00000000ULL) >> 8) | \
		 (((VALUE) & 0xFF0000000000ULL) >> 24) | \
		 (((VALUE) & 0xFF000000000000ULL) >> 40) | \
		 (((VALUE) & 0xFF00000000000000ULL) >> 56))
#endif // L2B_ENDIAN_64

#ifndef B2L_ENDIAN_64
	#define B2L_ENDIAN_64(VALUE) \
		((((VALUE) & 0xFFULL) << 56) | \
		 (((VALUE) & 0xFF00ULL) << 40) | \
		 (((VALUE) & 0xFF0000ULL) << 24) | \
		 (((VALUE) & 0xFF000000ULL) << 8) | \
		 (((VALUE) & 0xFF00000000ULL) >> 8) | \
		 (((VALUE) & 0xFF0000000000ULL) >> 24) | \
		 (((VALUE) & 0xFF000000000000ULL) >> 40) | \
		 (((VALUE) & 0xFF00000000000000ULL) >> 56))
#endif // B2L_ENDIAN_64

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

typedef void(*glDebug_PROC)(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);
typedef void(*glDebugMessageCallback_PROC)(glDebug_PROC Callback, void const* UserParam);
typedef void(*glMemoryBarrier_PROC)(int unsigned Barriers);
typedef void(*glDrawElementsInstanced_PROC)(int unsigned Mode, int Count, int unsigned Type, void const* Indices, int InstanceCount);

#ifdef FAST_GL_IMPLEMENTATION
static glDebugMessageCallback_PROC glDebugMessageCallback = 0;
static glMemoryBarrier_PROC glMemoryBarrier = 0;
static glDrawElementsInstanced_PROC glDrawElementsInstanced = 0;
#endif // FAST_GL_IMPLEMENTATION

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
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000

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
typedef void(*glGetShaderInfoLog_PROC)(int unsigned Shader, int unsigned BufferSize, int* Length, char* InfoLog);
typedef void(*glGetProgramiv_PROC)(int unsigned Program, int unsigned Name, int* Params);
typedef void(*glGetProgramInfoLog_PROC)(int unsigned Program, int unsigned BufferSize, int* Length, char* InfoLog);

#ifdef FAST_GL_IMPLEMENTATION
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
#endif // FAST_GL_IMPLEMENTATION

#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPUTE_SHADER 0x91B9
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84

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

///////////////////////////////////////////////////////////////
// Math Definition
///////////////////////////////////////////////////////////////

#define VECTOR2_ZERO { 0.0F, 0.0F }
#define VECTOR3_ZERO { 0.0F, 0.0F, 0.0F }
#define VECTOR4_ZERO { 0.0F, 0.0F, 0.0F, 0.0F }

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

typedef float Matrix2[2][2];
typedef float Matrix3[3][3];
typedef float Matrix4[4][4];

extern void Vector2_Zero(Vector2 Result);
extern void Vector3_Zero(Vector3 Result);
extern void Vector4_Zero(Vector4 Result);
extern void Vector2_Set(Vector2 Value, Vector2 Result);
extern void Vector3_Set(Vector3 Value, Vector3 Result);
extern void Vector4_Set(Vector4 Value, Vector4 Result);
extern void Vector2_SetSimple(float X, float Y, Vector2 Result);
extern void Vector3_SetSimple(float X, float Y, float Z, Vector3 Result);
extern void Vector4_SetSimple(float X, float Y, float Z, float W, Vector4 Result);
extern void Vector2_Add(Vector2 A, Vector2 B, Vector2 Result);
extern void Vector3_Add(Vector3 A, Vector3 B, Vector3 Result);
extern void Vector4_Add(Vector4 A, Vector4 B, Vector4 Result);
extern void Vector2_Sub(Vector2 A, Vector2 B, Vector2 Result);
extern void Vector3_Sub(Vector3 A, Vector3 B, Vector3 Result);
extern void Vector4_Sub(Vector4 A, Vector4 B, Vector4 Result);
extern void Vector2_Mul(Vector2 A, Vector2 B, Vector2 Result);
extern void Vector3_Mul(Vector3 A, Vector3 B, Vector3 Result);
extern void Vector4_Mul(Vector4 A, Vector4 B, Vector4 Result);
extern void Vector2_Div(Vector2 A, Vector2 B, Vector2 Result);
extern void Vector3_Div(Vector3 A, Vector3 B, Vector3 Result);
extern void Vector4_Div(Vector4 A, Vector4 B, Vector4 Result);
extern void Vector2_AddScalar(Vector2 Value, float Scalar, Vector2 Result);
extern void Vector3_AddScalar(Vector3 Value, float Scalar, Vector3 Result);
extern void Vector4_AddScalar(Vector4 Value, float Scalar, Vector4 Result);
extern void Vector2_SubScalar(Vector2 Value, float Scalar, Vector2 Result);
extern void Vector3_SubScalar(Vector3 Value, float Scalar, Vector3 Result);
extern void Vector4_SubScalar(Vector4 Value, float Scalar, Vector4 Result);
extern void Vector2_MulScalar(Vector2 Value, float Scalar, Vector2 Result);
extern void Vector3_MulScalar(Vector3 Value, float Scalar, Vector3 Result);
extern void Vector4_MulScalar(Vector4 Value, float Scalar, Vector4 Result);
extern void Vector2_DivScalar(Vector2 Value, float Scalar, Vector2 Result);
extern void Vector3_DivScalar(Vector3 Value, float Scalar, Vector3 Result);
extern void Vector4_DivScalar(Vector4 Value, float Scalar, Vector4 Result);
extern void Vector2_MulAdd(Vector2 Value, float Scalar, Vector2 Result);
extern void Vector3_MulAdd(Vector3 Value, float Scalar, Vector3 Result);
extern void Vector4_MulAdd(Vector4 Value, float Scalar, Vector4 Result);
extern void Vector3_Norm(Vector3 Result);
extern float Vector3_Dot(Vector3 A, Vector3 B);
extern void Vector3_Cross(Vector3 A, Vector3 B, Vector3 Result);
extern void Matrix4_GetPosition(Matrix4 Value, Vector3 Result);
extern void Matrix4_GetRotation(Matrix4 Value, Vector4 Result);
extern void Matrix4_GetScale(Matrix4 Value, Vector3 Result);
extern void Matrix4_SetPosition(Vector3 Value, Matrix4 Result);
extern void Matrix4_SetRotation(Vector4 Value, Matrix4 Result);
extern void Matrix4_SetScale(Vector3 Value, Matrix4 Result);
extern void Matrix4_Decompose(Matrix4 Value, Vector3 Position, Vector4 Rotation, Vector3 Scale);
extern void Matrix4_Zero(Matrix4 Result);
extern void Matrix4_One(Matrix4 Result);
extern void Matrix4_Copy(Matrix4 Value, Matrix4 Result);
extern void Matrix4_Identity(Matrix4 Result);
extern void Matrix4_Mul(Matrix4 A, Matrix4 B, Matrix4 Result);
extern void Matrix4_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, Matrix4 Result);
extern void Matrix4_Perspective(float FieldOfView, float AspectRatio, float NearZ, float FarZ, Matrix4 Result);
extern void Matrix4_LookAt(Vector3 Eye, Vector3 Center, Vector3 Up, Matrix4 Result);

///////////////////////////////////////////////////////////////
// FileSystem Definition
///////////////////////////////////////////////////////////////

extern void FileSystemReadText(char** Buffer, int unsigned* BufferSize, char const* FilePath);
extern void FileSystemReadBinary(char** Buffer, int unsigned* BufferSize, char const* FilePath);
extern void FileSystemWriteText(char const* Buffer, int unsigned BufferSize, char const* FilePath);
extern void FileSystemWriteBinary(char const* Buffer, int unsigned BufferSize, char const* FilePath);

///////////////////////////////////////////////////////////////
// Timer Definition
///////////////////////////////////////////////////////////////

typedef struct
{
	double StartMicroSeconds;
	double EndMicroSeconds;
	double ElapsedMicroSeconds;
} Timer;

extern void TimerAlloc(int unsigned NumOfTimers);
extern void TimerBeginMeasure(int unsigned Timer);
extern void TimerEndMeasure(int unsigned Timer);
extern double TimerElapsedNanoSeconds(int unsigned Timer);
extern double TimerElapsedMicroSeconds(int unsigned Timer);
extern double TimerElapsedMilliSeconds(int unsigned Timer);
extern void TimerFree();

#ifdef FAST_GL_IMPLEMENTATION
static int unsigned sNumOfTimers = 0;
static double sFrequency = 0.0;
static Timer* sTimers = 0;
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Window Definition
///////////////////////////////////////////////////////////////

extern void WindowAlloc(int unsigned Width, int unsigned Height, char const* WindowTitle);
extern bool WindowShouldClose(void);
extern void WindowViewport(int unsigned Width, int unsigned Height);
extern void WindowPollEvents(void);
extern void WindowSwapBuffers(void);
extern void WindowToNDC(float* X, float* Y);
extern float WindowWidth(void);
extern float WindowHeight(void);
extern float WindowMousePositionX(void);
extern float WindowMousePositionY(void);
extern void WindowFree(void);
extern LRESULT WindowCallback(HWND hWnd, UINT Message, WPARAM WParam, LPARAM LParam);
extern void WindowGLDebugCallback(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);

#ifdef FAST_GL_IMPLEMENTATION
static char const sWindowClassName[] = "FastGLWindow";
static HINSTANCE sModuleInstance = 0;
static HWND sWindowHandle = 0;
static HDC sDeviceContext = 0;
static HGLRC sGraphicsContext = 0;
static HMODULE sOpenGLInstance = 0;
static MSG sWindowMessage = {};
static bool sWindowShouldClose = false;
static float sWindowWidth = 0;
static float sWindowHeight = 0;
static float sMousePositionX = 0;
static float sMousePositionY = 0;
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Shader Definition
///////////////////////////////////////////////////////////////

extern int unsigned ShaderRenderAlloc(char const* VertexSource, char const* FragmentSource);
extern int unsigned ShaderComputeAlloc(char const* ComputeSource);
extern void ShaderBind(int unsigned Shader);
extern void ShaderFree(int unsigned Shader);

///////////////////////////////////////////////////////////////
// Buffer Definition
///////////////////////////////////////////////////////////////

extern int unsigned BufferVertexAlloc(int unsigned Size, int unsigned Usage);
extern int unsigned BufferIndexAlloc(int unsigned Size, int unsigned Usage);
extern int unsigned BufferUniformAlloc(int unsigned Size, int unsigned Usage);
extern int unsigned BufferStorageAlloc(int unsigned Size, int unsigned Usage);
extern void BufferVertexBind(int unsigned Buffer);
extern void BufferIndexBind(int unsigned Buffer);
extern void BufferUniformBind(int unsigned Buffer);
extern void BufferStorageBind(int unsigned Buffer);
extern void BufferVertexSetData(void const* Data, int unsigned Size);
extern void BufferIndexSetData(void const* Data, int unsigned Size);
extern void BufferUniformSetData(void const* Data, int unsigned Size);
extern void BufferStorageSetData(void const* Data, int unsigned Size);
extern void BufferVertexSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
extern void BufferIndexSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
extern void BufferUniformSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
extern void BufferStorageSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
extern void BufferVertexBeginBarrier(void);
extern void BufferIndexBeginBarrier(void);
extern void BufferUniformBeginBarrier(void);
extern void BufferStorageBeginBarrier(void);
extern void BufferEndBarrier(void);
extern void BufferUniformMount(int unsigned Buffer, int unsigned Index);
extern void BufferStorageMount(int unsigned Buffer, int unsigned Index);
extern void BufferFree(int unsigned Buffer);

///////////////////////////////////////////////////////////////
// Gizmo Definition
///////////////////////////////////////////////////////////////

typedef struct
{
	Vector3 Position;
} PointVertex;
typedef struct
{
	Vector3 Position;
	int unsigned Color;
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
} PointInstanceEntry;

typedef struct
{
	Vector3 Position;
	Vector3 Size;
	int unsigned Color;
} QuadInstanceEntry;

extern void GizmoAlloc(int unsigned NumPoints, int unsigned NumLines, int unsigned NumQuads);
extern void GizmoBeginPoints();
extern void GizmoDrawPoint(Vector3 Position, float Radius, int unsigned Color);
extern void GizmoDrawPointSimple(float PositionX, float PositionY, float PositionZ, float Radius, int unsigned Color);
extern void GizmoEndPoints(Matrix4 Projection, Matrix4 View);
extern void GizmoBeginLines(void);
extern void GizmoDrawLine(Vector3 From, Vector3 To, int unsigned Color);
extern void GizmoDrawLineSimple(float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int unsigned Color);
extern void GizmoDrawLineRect(Vector3 Position, Vector2 Size, int unsigned Color);
extern void GizmoDrawLineRectSimple(float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, int unsigned Color);
extern void GizmoDrawLineCircle(Vector3 Position, int unsigned NumSegments, float Radius, int unsigned Color);
extern void GizmoDrawLineCircleSimple(float PositionX, float PositionY, float PositionZ, int unsigned NumSegments, float Radius, int unsigned Color);
extern void GizmoDrawLineGrid(Vector3 Position, int unsigned NumOfLines, float Scale, int unsigned Color);
extern void GizmoEndLines(Matrix4 Projection, Matrix4 View);
extern void GizmoBeginQuads(void);
extern void GizmoDrawQuad(Vector3 Position, Vector3 Size, int unsigned Color);
extern void GizmoDrawQuadSimple(float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, int unsigned Color);
extern void GizmoEndQuads(Matrix4 Projection, Matrix4 View);
extern void GizmoFree(void);

#ifdef FAST_GL_IMPLEMENTATION
static char const sPointVertexShader[] = "#version 460 core\n"
"layout (location = 0) in vec3 InputPosition;\n"
"layout (location = 1) in vec3 InstancePosition;\n"
"layout (location = 2) in float InstanceRadius;\n"
"layout (location = 3) in uint InstanceColor;\n"
"layout (location = 0) out vec3 OutputPosition;\n"
"layout (location = 1) out float OutputRadius;\n"
"layout (location = 2) flat out uint OutputColor;\n"
"uniform mat4 ProjectionMatrix;\n"
"uniform mat4 ViewMatrix;\n"
"void main() {\n"
"	OutputPosition = InputPosition;\n"
"	OutputRadius = InstanceRadius;\n"
"	OutputColor = InstanceColor;\n"
"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(InstancePosition + InputPosition, 1.0);\n"
"}";
static char const sPointFragmentShader[] = "#version 460 core\n"
"layout (location = 0) in vec3 InputPosition;\n"
"layout (location = 1) in float InputRadius;\n"
"layout (location = 2) flat in uint InputColor;\n"
"layout (location = 0) out vec4 OutputColor;\n"
"void main() {\n"
"	if (dot(InputPosition, InputPosition) > InputRadius) discard;"
"	float R = ((InputColor >> 24) & 0xFF) / 255.0;\n"
"	float G = ((InputColor >> 16) & 0xFF) / 255.0;\n"
"	float B = ((InputColor >>  8) & 0xFF) / 255.0;\n"
"	float A = ((InputColor      ) & 0xFF) / 255.0;\n"
"	OutputColor = vec4(R, G, B, A);\n"
"}";
static char const sLineVertexShader[] = "#version 460 core\n"
"layout (location = 0) in vec3 InputPosition;\n"
"layout (location = 1) in uint InputColor;\n"
"layout (location = 0) flat out uint OutputColor;\n"
"uniform mat4 ProjectionMatrix;\n"
"uniform mat4 ViewMatrix;\n"
"void main() {\n"
"	OutputColor = InputColor;\n"
"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(InputPosition, 1.0);\n"
"}";
static char const sLineFragmentShader[] = "#version 460 core\n"
"layout (location = 0) flat in uint InputColor;\n"
"layout (location = 0) out vec4 OutputColor;\n"
"void main() {\n"
"	float R = ((InputColor >> 24) & 0xFF) / 255.0;\n"
"	float G = ((InputColor >> 16) & 0xFF) / 255.0;\n"
"	float B = ((InputColor >>  8) & 0xFF) / 255.0;\n"
"	float A = ((InputColor      ) & 0xFF) / 255.0;\n"
"	OutputColor = vec4(R, G, B, A);\n"
"}";
static char const sQuadVertexShader[] = "#version 460 core\n"
"layout (location = 0) in vec3 InputPosition;\n"
"layout (location = 1) in vec3 InstancePosition;\n"
"layout (location = 2) in vec3 InstanceSize;\n"
"layout (location = 3) in uint InstanceColor;\n"
"layout (location = 0) flat out uint OutputColor;\n"
"uniform mat4 ProjectionMatrix;\n"
"uniform mat4 ViewMatrix;\n"
"void main() {\n"
"	OutputColor = InstanceColor;\n"
"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(InstancePosition + (InputPosition * InstanceSize), 1.0);\n"
"}";
static char const sQuadFragmentShader[] = "#version 460 core\n"
"layout (location = 0) flat in uint InputColor;\n"
"layout (location = 0) out vec4 OutputColor;\n"
"void main() {\n"
"	float R = ((InputColor >> 24) & 0xFF) / 255.0;\n"
"	float G = ((InputColor >> 16) & 0xFF) / 255.0;\n"
"	float B = ((InputColor >>  8) & 0xFF) / 255.0;\n"
"	float A = ((InputColor      ) & 0xFF) / 255.0;\n"
"	OutputColor = vec4(R, G, B, A);\n"
"}";
static int unsigned sPointProgram = 0;
static int unsigned sLineProgram = 0;
static int unsigned sQuadProgram = 0;
static int unsigned sPointVertexArray = 0;
static int unsigned sPointVertexBuffer = 0;
static int unsigned sPointInstanceBuffer = 0;
static int unsigned sPointIndexBuffer = 0;
static int unsigned sLineVertexArray = 0;
static int unsigned sLineVertexBuffer = 0;
static int unsigned sLineIndexBuffer = 0;
static int unsigned sQuadVertexArray = 0;
static int unsigned sQuadVertexBuffer = 0;
static int unsigned sQuadInstanceBuffer = 0;
static int unsigned sQuadIndexBuffer = 0;
static int unsigned sPointInstanceOffset = 0;
static int unsigned sLineVertexOffset = 0;
static int unsigned sLineIndexOffset = 0;
static int unsigned sQuadInstanceOffset = 0;
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Text Definition
///////////////////////////////////////////////////////////////

struct GlyphPoint
{
	short X;
	short Y;
	bool OnCurve;
};

struct GlyphDescription
{
	short NumOfContours;
	short MinX;
	short MinY;
	short MaxX;
	short MaxY;
};

struct Glyph
{
	GlyphDescription Description;
	short unsigned* ContourEndIndices;
	short unsigned NumOfPoints;
	GlyphPoint* Points;
	char unsigned* Flags;
	short unsigned NumOfInstructions;
	char unsigned* Instructions;
};

extern void TextFontAlloc(char const* FilePath);
//extern void TextFontReadGlyph(FILE* File);
//extern void TextFontReadSimpleGlyph(FILE* File);
//extern void TextFontReadCompoundGlyph(FILE* File);
extern Glyph* TextFontGlyph(int unsigned Glyph);
extern void TextFontFree(void);

#ifdef FAST_GL_IMPLEMENTATION
static Glyph* sGlyphs = 0;
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
void Vector2_Set(Vector2 Value, Vector2 Result)
{
	Result[0] = Value[0];
	Result[1] = Value[1];
}
void Vector3_Set(Vector3 Value, Vector3 Result)
{
	Result[0] = Value[0];
	Result[1] = Value[1];
	Result[2] = Value[2];
}
void Vector4_Set(Vector4 Value, Vector4 Result)
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
void Vector2_Add(Vector2 A, Vector2 B, Vector2 Result)
{
	Result[0] = A[0] + B[0];
	Result[1] = A[1] + B[1];
}
void Vector3_Add(Vector3 A, Vector3 B, Vector3 Result)
{
	Result[0] = A[0] + B[0];
	Result[1] = A[1] + B[1];
	Result[2] = A[2] + B[2];
}
void Vector4_Add(Vector4 A, Vector4 B, Vector4 Result)
{
	Result[0] = A[0] + B[0];
	Result[1] = A[1] + B[1];
	Result[2] = A[2] + B[2];
	Result[3] = A[3] + B[3];
}
void Vector2_Sub(Vector2 A, Vector2 B, Vector2 Result)
{
	Result[0] = A[0] - B[0];
	Result[1] = A[1] - B[1];
}
void Vector3_Sub(Vector3 A, Vector3 B, Vector3 Result)
{
	Result[0] = A[0] - B[0];
	Result[1] = A[1] - B[1];
	Result[2] = A[2] - B[2];
}
void Vector4_Sub(Vector4 A, Vector4 B, Vector4 Result)
{
	Result[0] = A[0] - B[0];
	Result[1] = A[1] - B[1];
	Result[2] = A[2] - B[2];
	Result[3] = A[3] - B[3];
}
void Vector2_Mul(Vector2 A, Vector2 B, Vector2 Result)
{
	Result[0] = A[0] * B[0];
	Result[1] = A[1] * B[1];
}
void Vector3_Mul(Vector3 A, Vector3 B, Vector3 Result)
{
	Result[0] = A[0] * B[0];
	Result[1] = A[1] * B[1];
	Result[2] = A[2] * B[2];
}
void Vector4_Mul(Vector4 A, Vector4 B, Vector4 Result)
{
	Result[0] = A[0] * B[0];
	Result[1] = A[1] * B[1];
	Result[2] = A[2] * B[2];
	Result[3] = A[3] * B[3];
}
void Vector2_Div(Vector2 A, Vector2 B, Vector2 Result)
{
	Result[0] = A[0] / B[0];
	Result[1] = A[1] / B[1];
}
void Vector3_Div(Vector3 A, Vector3 B, Vector3 Result)
{
	Result[0] = A[0] / B[0];
	Result[1] = A[1] / B[1];
	Result[2] = A[2] / B[2];
}
void Vector4_Div(Vector4 A, Vector4 B, Vector4 Result)
{
	Result[0] = A[0] / B[0];
	Result[1] = A[1] / B[1];
	Result[2] = A[2] / B[2];
	Result[3] = A[3] / B[3];
}
void Vector2_AddScalar(Vector2 Value, float Scalar, Vector2 Result)
{
	Result[0] = Value[0] + Scalar;
	Result[1] = Value[1] + Scalar;
}
void Vector3_AddScalar(Vector3 Value, float Scalar, Vector3 Result)
{
	Result[0] = Value[0] + Scalar;
	Result[1] = Value[1] + Scalar;
	Result[2] = Value[2] + Scalar;
}
void Vector4_AddScalar(Vector4 Value, float Scalar, Vector4 Result)
{
	Result[0] = Value[0] + Scalar;
	Result[1] = Value[1] + Scalar;
	Result[2] = Value[2] + Scalar;
	Result[3] = Value[3] + Scalar;
}
void Vector2_SubScalar(Vector2 Value, float Scalar, Vector2 Result)
{
	Result[0] = Value[0] - Scalar;
	Result[1] = Value[1] - Scalar;
}
void Vector3_SubScalar(Vector3 Value, float Scalar, Vector3 Result)
{
	Result[0] = Value[0] - Scalar;
	Result[1] = Value[1] - Scalar;
	Result[2] = Value[2] - Scalar;
}
void Vector4_SubScalar(Vector4 Value, float Scalar, Vector4 Result)
{
	Result[0] = Value[0] - Scalar;
	Result[1] = Value[1] - Scalar;
	Result[2] = Value[2] - Scalar;
	Result[3] = Value[3] - Scalar;
}
void Vector2_MulScalar(Vector2 Value, float Scalar, Vector2 Result)
{
	Result[0] = Value[0] * Scalar;
	Result[1] = Value[1] * Scalar;
}
void Vector3_MulScalar(Vector3 Value, float Scalar, Vector3 Result)
{
	Result[0] = Value[0] * Scalar;
	Result[1] = Value[1] * Scalar;
	Result[2] = Value[2] * Scalar;
}
void Vector4_MulScalar(Vector4 Value, float Scalar, Vector4 Result)
{
	Result[0] = Value[0] * Scalar;
	Result[1] = Value[1] * Scalar;
	Result[2] = Value[2] * Scalar;
	Result[3] = Value[3] * Scalar;
}
void Vector2_DivScalar(Vector2 Value, float Scalar, Vector2 Result)
{
	Result[0] = Value[0] / Scalar;
	Result[1] = Value[1] / Scalar;
}
void Vector3_DivScalar(Vector3 Value, float Scalar, Vector3 Result)
{
	Result[0] = Value[0] / Scalar;
	Result[1] = Value[1] / Scalar;
	Result[2] = Value[2] / Scalar;
}
void Vector4_DivScalar(Vector4 Value, float Scalar, Vector4 Result)
{
	Result[0] = Value[0] / Scalar;
	Result[1] = Value[1] / Scalar;
	Result[2] = Value[2] / Scalar;
	Result[3] = Value[3] / Scalar;
}
void Vector2_MulAdd(Vector2 Value, float Scalar, Vector2 Result)
{
	Result[0] += Value[0] * Scalar;
	Result[1] += Value[1] * Scalar;
}
void Vector3_MulAdd(Vector3 Value, float Scalar, Vector3 Result)
{
	Result[0] += Value[0] * Scalar;
	Result[1] += Value[1] * Scalar;
	Result[2] += Value[2] * Scalar;
}
void Vector4_MulAdd(Vector4 Value, float Scalar, Vector4 Result)
{
	Result[0] += Value[0] * Scalar;
	Result[1] += Value[1] * Scalar;
	Result[2] += Value[2] * Scalar;
	Result[3] += Value[3] * Scalar;
}
void Vector3_Norm(Vector3 Result)
{
	float A = Vector3_Dot(Result, Result);
	float N = sqrtf(A);

	if (N == 0.0F)
	{
		Vector3_Zero(Result);
	}
	else
	{
		Vector3_MulScalar(Result, 1.0F / N, Result);
	}
}
float Vector3_Dot(Vector3 A, Vector3 B)
{
	return (A[0] * B[0]) + (A[1] * B[1]) + (A[2] * B[2]);
}
void Vector3_Cross(Vector3 A, Vector3 B, Vector3 Result)
{
	Result[0] = (A[1] * B[2]) - (A[2] * B[1]);
	Result[1] = (A[2] * B[0]) - (A[0] * B[2]);
	Result[2] = (A[0] * B[1]) - (A[1] * B[0]);
}
void Matrix4_GetPosition(Matrix4 Value, Vector3 Result)
{
	Result[0] = Value[0][0];
	Result[1] = Value[1][0];
	Result[2] = Value[2][0];
}
void Matrix4_GetRotation(Matrix4 Value, Vector4 Result)
{
#pragma message("FAST_GL_NO_IMPLEMENTATION")
}
void Matrix4_GetScale(Matrix4 Value, Vector3 Result)
{
	Result[0] = Value[0][0];
	Result[1] = Value[1][1];
	Result[2] = Value[2][2];
}
void Matrix4_SetPosition(Vector3 Value, Matrix4 Result)
{
	Result[3][0] = Value[0];
	Result[3][1] = Value[1];
	Result[3][2] = Value[2];
}
void Matrix4_SetRotation(Vector4 Value, Matrix4 Result)
{
#pragma message("FAST_GL_NO_IMPLEMENTATION")
}
void Matrix4_SetScale(Vector3 Value, Matrix4 Result)
{
	Result[0][0] = Value[0];
	Result[1][1] = Value[1];
	Result[2][2] = Value[2];
}
void Matrix4_Decompose(Matrix4 Value, Vector3 Position, Vector4 Rotation, Vector3 Scale)
{
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
void Matrix4_Copy(Matrix4 Value, Matrix4 Result)
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
void Matrix4_Mul(Matrix4 A, Matrix4 B, Matrix4 Result)
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
void Matrix4_LookAt(Vector3 Eye, Vector3 Center, Vector3 Up, Matrix4 Result)
{
	Vector3 F = VECTOR2_ZERO, U = VECTOR2_ZERO, S = VECTOR2_ZERO;

	Vector3_Sub(Center, Eye, F);
	Vector3_Norm(F);
	Vector3_Cross(Up, F, S);
	Vector3_Norm(S);
	Vector3_Cross(F, S, U);

	Result[0][0] = S[0];
	Result[0][1] = U[0];
	Result[0][2] = F[0];
	Result[1][0] = S[1];
	Result[1][1] = U[1];
	Result[1][2] = F[1];
	Result[2][0] = S[2];
	Result[2][1] = U[2];
	Result[2][2] = F[2];
	Result[3][0] = -Vector3_Dot(S, Eye);
	Result[3][1] = -Vector3_Dot(U, Eye);
	Result[3][2] = -Vector3_Dot(F, Eye);
	Result[0][3] = 0.0F;
	Result[1][3] = 0.0F;
	Result[2][3] = 0.0F;
	Result[3][3] = 1.0F;
}
#endif // #ifdef FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// FileSystem Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
void FileSystemReadText(char** Buffer, int unsigned* BufferSize, char const* FilePath)
{
	FILE* File = 0;
	fopen_s(&File, FilePath, "r");
	fseek(File, 0, SEEK_END);
	*BufferSize = ftell(File);
	*Buffer = (char*)calloc((*BufferSize) + 1, sizeof(char));
	fseek(File, 0, SEEK_SET);
	fread(*Buffer, sizeof(char), *BufferSize, File);
	fclose(File);
}
void FileSystemReadBinary(char** Buffer, int unsigned* BufferSize, char const* FilePath)
{
	FILE* File = 0;
	fopen_s(&File, FilePath, "rb");
	fseek(File, 0, SEEK_END);
	*BufferSize = ftell(File);
	*Buffer = (char*)calloc(*BufferSize, sizeof(char));
	fseek(File, 0, SEEK_SET);
	fread(*Buffer, sizeof(char), *BufferSize, File);
	fclose(File);
}
void FileSystemWriteText(char const* Buffer, int unsigned BufferSize, char const* FilePath)
{
	FILE* File = 0;
	fopen_s(&File, FilePath, "w");
	fseek(File, 0, SEEK_SET);
	fwrite(Buffer, sizeof(char), BufferSize, File);
	fclose(File);
}
void FileSystemWriteBinary(char const* Buffer, int unsigned BufferSize, char const* FilePath)
{
	FILE* File = 0;
	fopen_s(&File, FilePath, "wb");
	fseek(File, 0, SEEK_SET);
	fwrite(Buffer, sizeof(char), BufferSize, File);
	fclose(File);
}
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Timer Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
void TimerAlloc(int unsigned NumOfTimers)
{
	sTimers = (Timer*)calloc(NumOfTimers, sizeof(Timer));
	
	LARGE_INTEGER Frequency = {};

	QueryPerformanceFrequency(&Frequency);

	sFrequency = (double)Frequency.QuadPart;
}
void TimerBeginMeasure(int unsigned Timer)
{
	LARGE_INTEGER StartMicroSeconds = {};

	QueryPerformanceCounter(&StartMicroSeconds);

	sTimers[Timer].StartMicroSeconds = (double)StartMicroSeconds.QuadPart;
}
void TimerEndMeasure(int unsigned Timer)
{
	LARGE_INTEGER EndMicroSeconds = {};

	QueryPerformanceCounter(&EndMicroSeconds);

	sTimers[Timer].EndMicroSeconds = (double)EndMicroSeconds.QuadPart;
	sTimers[Timer].ElapsedMicroSeconds = (sTimers[Timer].EndMicroSeconds - sTimers[Timer].StartMicroSeconds) / sFrequency;
}
double TimerElapsedNanoSeconds(int unsigned Timer)
{
	return sTimers[Timer].ElapsedMicroSeconds / 1000.0;
}
double TimerElapsedMicroSeconds(int unsigned Timer)
{
	return sTimers[Timer].ElapsedMicroSeconds;
}
double TimerElapsedMilliSeconds(int unsigned Timer)
{
	return sTimers[Timer].ElapsedMicroSeconds * 1000.0;
}
void TimerFree()
{
	free(sTimers);
}
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Window Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
void WindowAlloc(int unsigned Width, int unsigned Height, char const* WindowTitle)
{
	sModuleInstance = GetModuleHandle(0);

	WNDCLASS WindowClass = {};
	WindowClass.lpfnWndProc = WindowCallback;
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
		Width,
		Height,
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
	glDebugMessageCallback(WindowGLDebugCallback, 0);
#endif // FAST_GL_DEBUG
}
bool WindowShouldClose(void)
{
	return sWindowShouldClose;
}
void WindowViewport(int unsigned Width, int unsigned Height)
{
	glViewport(0, 0, Width, Height);
}
void WindowClear(float R, float G, float B, float A, int unsigned Mask)
{
	glClearColor(R, G, B, A);
	glClear(Mask);
}
void WindowPollEvents(void)
{
	PeekMessage(&sWindowMessage, 0, 0, 0, PM_REMOVE);

	TranslateMessage(&sWindowMessage);

	DispatchMessage(&sWindowMessage);
}
void WindowSwapBuffers(void)
{
	SwapBuffers(sDeviceContext);
}
void WindowToNDC(float* X, float* Y)
{
	*X = 2.0F * (sMousePositionX / sWindowWidth) - 1.0F;
	*Y = 1.0F - 2.0F * (sMousePositionY / sWindowHeight);
}
float WindowWidth(void)
{
	return sWindowWidth;
}
float WindowHeight(void)
{
	return sWindowHeight;
}
float WindowMousePositionX(void)
{
	return sMousePositionX;
}
float WindowMousePositionY(void)
{
	return sMousePositionY;
}
void WindowFree(void)
{
	glMakeCurrent(0, 0);

	glDeleteContext(sGraphicsContext);

	FreeLibrary(sOpenGLInstance);

	ReleaseDC(sWindowHandle, sDeviceContext);

	DestroyWindow(sWindowHandle);
}
LRESULT WindowCallback(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
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
			int unsigned TitleBarHeight = GetSystemMetrics(SM_CYCAPTION);
			int unsigned BorderHeight = GetSystemMetrics(SM_CYFRAME);

			if ((Width > 0) && (Height > 0))
			{
				sWindowWidth = (float)Width;
				sWindowHeight = (float)(Height - TitleBarHeight + BorderHeight);
			}

			break;
		}
		case WM_MOUSEMOVE:
		{
			int unsigned PositionX = LOWORD(LParam);
			int unsigned PositionY = HIWORD(LParam);
			int unsigned TitleBarHeight = GetSystemMetrics(SM_CYCAPTION);
			int unsigned BorderHeight = GetSystemMetrics(SM_CYFRAME);

			sMousePositionX = (float)PositionX;
			sMousePositionY = (float)(PositionY + TitleBarHeight - BorderHeight);

			break;
		}
	}

	return DefWindowProc(WindowHandle, Message, WParam, LParam);
}
#ifdef FAST_GL_DEBUG
void WindowGLDebugCallback(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam)
{
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
// Shader Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
int unsigned ShaderRenderAlloc(char const* VertexSource, char const* FragmentSource)
{
	int unsigned Program = glCreateProgram();
	int unsigned VertexShader = glCreateShader(GL_VERTEX_SHADER);
	int unsigned FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VertexShader, 1, &VertexSource, 0);
	glCompileShader(VertexShader);
	SHADER_CHECK_COMPILE_STATUS(VertexShader);
	glShaderSource(FragmentShader, 1, &FragmentSource, 0);
	glCompileShader(FragmentShader);
	SHADER_CHECK_COMPILE_STATUS(FragmentShader);
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glLinkProgram(Program);
	PROGRAM_CHECK_LINK_STATUS(Program);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return Program;
}
int unsigned ShaderComputeAlloc(char const* ComputeSource)
{
	int unsigned Program = glCreateProgram();
	int unsigned ComputeShader = glCreateShader(GL_COMPUTE_SHADER);

	glShaderSource(ComputeShader, 1, &ComputeSource, 0);
	glCompileShader(ComputeShader);
	SHADER_CHECK_COMPILE_STATUS(ComputeShader);
	glAttachShader(Program, ComputeShader);
	glLinkProgram(Program);
	PROGRAM_CHECK_LINK_STATUS(Program);
	glDeleteShader(ComputeShader);

	return Program;
}
void ShaderBind(int unsigned Program)
{
	glUseProgram(Program);
}
void ShaderFree(int unsigned Program)
{
	glDeleteProgram(Program);
}
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Buffer Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
int unsigned BufferVertexAlloc(int unsigned Size, int unsigned Usage)
{
	int unsigned Buffer = 0;

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, Size, 0, Usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return Buffer;
}
int unsigned BufferIndexAlloc(int unsigned Size, int unsigned Usage)
{
	int unsigned Buffer = 0;

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, 0, Usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return Buffer;
}
int unsigned BufferUniformAlloc(int unsigned Size, int unsigned Usage)
{
	int unsigned Buffer = 0;

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, Buffer);
	glBufferData(GL_UNIFORM_BUFFER, Size, 0, Usage);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return Buffer;
}
int unsigned BufferStorageAlloc(int unsigned Size, int unsigned Usage)
{
	int unsigned Buffer = 0;

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, Size, 0, Usage);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	return Buffer;
}
void BufferVertexBind(int unsigned Buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
}
void BufferIndexBind(int unsigned Buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer);
}
void BufferUniformBind(int unsigned Buffer)
{
	glBindBuffer(GL_UNIFORM_BUFFER, Buffer);
}
void BufferStorageBind(int unsigned Buffer)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer);
}
void BufferVertexSetData(void const* Data, int unsigned Size)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Data);
}
void BufferIndexSetData(void const* Data, int unsigned Size)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Size, Data);
}
void BufferUniformSetData(void const* Data, int unsigned Size)
{
	glBufferSubData(GL_UNIFORM_BUFFER, 0, Size, Data);
}
void BufferStorageSetData(void const* Data, int unsigned Size)
{
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, Size, Data);
}
void BufferVertexSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
{
	glBufferSubData(GL_ARRAY_BUFFER, Offset, Size, Data);
}
void BufferIndexSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, Offset, Size, Data);
}
void BufferUniformSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
{
	glBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, Data);
}
void BufferStorageSetSubData(void const* Data, int unsigned Offset, int unsigned Size)
{
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, Offset, Size, Data);
}
void BufferVertexBeginBarrier(void)
{
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
}
void BufferIndexBeginBarrier(void)
{
	glMemoryBarrier(GL_ELEMENT_ARRAY_BARRIER_BIT);
}
void BufferUniformBeginBarrier(void)
{
	glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}
void BufferStorageBeginBarrier(void)
{
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}
void BufferEndBarrier(void)
{
	glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
}
void BufferUniformMount(int unsigned Buffer, int unsigned Index)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, Index, Buffer);
}
void BufferStorageMount(int unsigned Buffer, int unsigned Index)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Index, Buffer);
}
void BufferFree(int unsigned Buffer)
{
	glDeleteBuffers(1, &Buffer);
}
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Gizmo Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
void GizmoAlloc(int unsigned NumPoints, int unsigned NumLines, int unsigned NumQuads)
{
	int unsigned VertexShader = 0;
	int unsigned FragmentShader = 0;

	char const* PointVertexShaderPtr = sPointVertexShader;
	char const* PointFragmentShaderPtr = sPointFragmentShader;
	char const* LineVertexShaderPtr = sLineVertexShader;
	char const* LineFragmentShaderPtr = sLineFragmentShader;
	char const* QuadVertexShaderPtr = sQuadVertexShader;
	char const* QuadFragmentShaderPtr = sQuadFragmentShader;

	sPointProgram = glCreateProgram();
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(VertexShader, 1, &PointVertexShaderPtr, 0);
	glCompileShader(VertexShader);
	SHADER_CHECK_COMPILE_STATUS(VertexShader);
	glShaderSource(FragmentShader, 1, &PointFragmentShaderPtr, 0);
	glCompileShader(FragmentShader);
	SHADER_CHECK_COMPILE_STATUS(FragmentShader);
	glAttachShader(sPointProgram, VertexShader);
	glAttachShader(sPointProgram, FragmentShader);
	glLinkProgram(sPointProgram);
	PROGRAM_CHECK_LINK_STATUS(sPointProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	sLineProgram = glCreateProgram();
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(VertexShader, 1, &LineVertexShaderPtr, 0);
	glCompileShader(VertexShader);
	SHADER_CHECK_COMPILE_STATUS(VertexShader);
	glShaderSource(FragmentShader, 1, &LineFragmentShaderPtr, 0);
	glCompileShader(FragmentShader);
	SHADER_CHECK_COMPILE_STATUS(FragmentShader);
	glAttachShader(sLineProgram, VertexShader);
	glAttachShader(sLineProgram, FragmentShader);
	glLinkProgram(sLineProgram);
	PROGRAM_CHECK_LINK_STATUS(sLineProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	sQuadProgram = glCreateProgram();
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(VertexShader, 1, &QuadVertexShaderPtr, 0);
	glCompileShader(VertexShader);
	SHADER_CHECK_COMPILE_STATUS(VertexShader);
	glShaderSource(FragmentShader, 1, &QuadFragmentShaderPtr, 0);
	glCompileShader(FragmentShader);
	SHADER_CHECK_COMPILE_STATUS(FragmentShader);
	glAttachShader(sQuadProgram, VertexShader);
	glAttachShader(sQuadProgram, FragmentShader);
	glLinkProgram(sQuadProgram);
	PROGRAM_CHECK_LINK_STATUS(sQuadProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	PointVertex PointVertices[3] = {};
	PointVertices[0].Position[0] = 0.0F;
	PointVertices[0].Position[1] = 2.0F;
	PointVertices[0].Position[2] = 0.0F;
	PointVertices[1].Position[0] = -SQRT_3;
	PointVertices[1].Position[1] = -1.0F;
	PointVertices[1].Position[2] = 0.0F;
	PointVertices[2].Position[0] = SQRT_3;
	PointVertices[2].Position[1] = -1.0F;
	PointVertices[2].Position[2] = 0.0F;

	int unsigned PointIndices[3] = {};
	PointIndices[0] = 0;
	PointIndices[1] = 1;
	PointIndices[2] = 2;

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
	glGenBuffers(1, &sPointVertexBuffer);
	glGenBuffers(1, &sPointInstanceBuffer);
	glGenBuffers(1, &sPointIndexBuffer);
	glBindVertexArray(sPointVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, sPointVertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(PointVertex), (void*)(0));
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(PointVertex), PointVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(1, 3, GL_FLOAT, 0, sizeof(PointInstanceEntry), (void*)(0));
	glVertexAttribPointer(2, 1, GL_FLOAT, 0, sizeof(PointInstanceEntry), (void*)(sizeof(Vector3)));
	glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(PointInstanceEntry), (void*)(sizeof(Vector3) + sizeof(float)));
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(PointInstanceEntry), 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sPointIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(int unsigned), PointIndices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	glGenVertexArrays(1, &sLineVertexArray);
	glGenBuffers(1, &sLineVertexBuffer);
	glGenBuffers(1, &sLineIndexBuffer);
	glBindVertexArray(sLineVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(LineVertex), (void*)(0));
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(LineVertex), (void*)(sizeof(Vector3)));
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
void GizmoBeginPoints()
{
	sPointInstanceOffset = 0;
}
void GizmoDrawPoint(Vector3 Position, float Radius, int unsigned Color)
{
	glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);

	PointInstanceEntry* PointInstanceBuffer = (PointInstanceEntry*)glMapBufferRange(GL_ARRAY_BUFFER, sPointInstanceOffset * sizeof(PointInstanceEntry), sizeof(PointInstanceEntry), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	PointInstanceBuffer->Position[0] = Position[0];
	PointInstanceBuffer->Position[1] = Position[1];
	PointInstanceBuffer->Position[2] = Position[2];
	PointInstanceBuffer->Radius = Radius;
	PointInstanceBuffer->Color = Color;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	sPointInstanceOffset += 1;
}
void GizmoDrawPointSimple(float PositionX, float PositionY, float PositionZ, float Radius, int unsigned Color)
{
	glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);

	PointInstanceEntry* PointInstanceBuffer = (PointInstanceEntry*)glMapBufferRange(GL_ARRAY_BUFFER, sPointInstanceOffset * sizeof(PointInstanceEntry), sizeof(PointInstanceEntry), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	PointInstanceBuffer->Position[0] = PositionX;
	PointInstanceBuffer->Position[1] = PositionY;
	PointInstanceBuffer->Position[2] = PositionZ;
	PointInstanceBuffer->Radius = Radius;
	PointInstanceBuffer->Color = Color;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	sPointInstanceOffset += 1;
}
void GizmoEndPoints(Matrix4 Projection, Matrix4 View)
{
	glUseProgram(sPointProgram);
	int unsigned ProjectionMatrixLocation = glGetUniformLocation(sPointProgram, "ProjectionMatrix");
	int unsigned ViewMatrixLocation = glGetUniformLocation(sPointProgram, "ViewMatrix");
	glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
	glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
	glBindVertexArray(sPointVertexArray);
	glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, sPointInstanceOffset);
	glBindVertexArray(0);
}
void GizmoBeginLines(void)
{
	sLineVertexOffset = 0;
	sLineIndexOffset = 0;
}
void GizmoDrawLine(Vector3 From, Vector3 To, int unsigned Color)
{
	glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

	LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	VertexBuffer[0].Position[0] = From[0];
	VertexBuffer[0].Position[1] = From[1];
	VertexBuffer[0].Position[2] = From[2];
	VertexBuffer[0].Color = Color;
	VertexBuffer[1].Position[0] = To[0];
	VertexBuffer[1].Position[1] = To[1];
	VertexBuffer[1].Position[2] = To[2];
	VertexBuffer[1].Color = Color;

	IndexBuffer[0] = sLineVertexOffset + 0;
	IndexBuffer[1] = sLineVertexOffset + 1;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	sLineVertexOffset += 2;
	sLineIndexOffset += 2;
}
void GizmoDrawLineSimple(float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int unsigned Color)
{
	glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

	LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 2 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 2 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	VertexBuffer[0].Position[0] = FromX;
	VertexBuffer[0].Position[1] = FromY;
	VertexBuffer[0].Position[2] = FromZ;
	VertexBuffer[0].Color = Color;
	VertexBuffer[1].Position[0] = ToX;
	VertexBuffer[1].Position[1] = ToY;
	VertexBuffer[1].Position[2] = ToZ;
	VertexBuffer[1].Color = Color;

	IndexBuffer[0] = sLineVertexOffset + 0;
	IndexBuffer[1] = sLineVertexOffset + 1;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	sLineVertexOffset += 2;
	sLineIndexOffset += 2;
}
void GizmoDrawLineRect(Vector3 Position, Vector2 Size, int unsigned Color)
{
	glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

	LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 4 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 8 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	VertexBuffer[0].Position[0] = Position[0];
	VertexBuffer[0].Position[1] = Position[1];
	VertexBuffer[0].Position[2] = Position[2];
	VertexBuffer[0].Color = Color;
	VertexBuffer[1].Position[0] = Position[0] + Size[0];
	VertexBuffer[1].Position[1] = Position[1];
	VertexBuffer[1].Position[2] = Position[2];
	VertexBuffer[1].Color = Color;
	VertexBuffer[2].Position[0] = Position[0] + Size[0];
	VertexBuffer[2].Position[1] = Position[1] + Size[1];
	VertexBuffer[2].Position[2] = Position[2];
	VertexBuffer[2].Color = Color;
	VertexBuffer[3].Position[0] = Position[0];
	VertexBuffer[3].Position[1] = Position[1] + Size[1];
	VertexBuffer[3].Position[2] = Position[2];
	VertexBuffer[3].Color = Color;

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
void GizmoDrawLineRectSimple(float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, int unsigned Color)
{
	glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);

	LineVertex* VertexBuffer = (LineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, sLineVertexOffset * sizeof(LineVertex), 4 * sizeof(LineVertex), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	int unsigned* IndexBuffer = (int unsigned*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sLineIndexOffset * sizeof(int unsigned), 8 * sizeof(int unsigned), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	VertexBuffer[0].Position[0] = PositionX;
	VertexBuffer[0].Position[1] = PositionY;
	VertexBuffer[0].Position[2] = PositionZ;
	VertexBuffer[0].Color = Color;
	VertexBuffer[1].Position[0] = PositionX + SizeX;
	VertexBuffer[1].Position[1] = PositionY;
	VertexBuffer[1].Position[2] = PositionZ;
	VertexBuffer[1].Color = Color;
	VertexBuffer[2].Position[0] = PositionX + SizeX;
	VertexBuffer[2].Position[1] = PositionY + SizeY;
	VertexBuffer[2].Position[2] = PositionZ;
	VertexBuffer[2].Color = Color;
	VertexBuffer[3].Position[0] = PositionX;
	VertexBuffer[3].Position[1] = PositionY + SizeY;
	VertexBuffer[3].Position[2] = PositionZ;
	VertexBuffer[3].Color = Color;

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
void GizmoDrawLineCircle(Vector3 Position, int unsigned NumSegments, float Radius, int unsigned Color)
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
		VertexBuffer[SegmentIndex].Color = Color;

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
void GizmoDrawLineCircleSimple(float PositionX, float PositionY, float PositionZ, int unsigned NumSegments, float Radius, int unsigned Color)
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
		VertexBuffer[SegmentIndex].Color = Color;

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
void GizmoDrawLineGrid(Vector3 Position, int unsigned NumOfLines, float Scale, int unsigned Color)
{
#pragma message("FAST_GL_NO_IMPLEMENTATION")
}
void GizmoEndLines(Matrix4 Projection, Matrix4 View)
{
	glUseProgram(sLineProgram);
	int unsigned ProjectionMatrixLocation = glGetUniformLocation(sLineProgram, "ProjectionMatrix");
	int unsigned ViewMatrixLocation = glGetUniformLocation(sLineProgram, "ViewMatrix");
	glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
	glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
	glBindVertexArray(sLineVertexArray);
	glDrawElements(GL_LINES, sLineIndexOffset, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void GizmoBeginQuads(void)
{
	sQuadInstanceOffset = 0;
}
void GizmoDrawQuad(Vector3 Position, Vector3 Size, int unsigned Color)
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
void GizmoDrawQuadSimple(float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, int unsigned Color)
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
void GizmoEndQuads(Matrix4 Projection, Matrix4 View)
{
	glUseProgram(sQuadProgram);
	int unsigned ProjectionMatrixLocation = glGetUniformLocation(sQuadProgram, "ProjectionMatrix");
	int unsigned ViewMatrixLocation = glGetUniformLocation(sQuadProgram, "ViewMatrix");
	glUniformMatrix4fv(ProjectionMatrixLocation, 1, 0, &Projection[0][0]);
	glUniformMatrix4fv(ViewMatrixLocation, 1, 0, &View[0][0]);
	glBindVertexArray(sQuadVertexArray);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, sQuadInstanceOffset);
	glBindVertexArray(0);
}
void GizmoFree(void)
{
	glDeleteBuffers(1, &sPointVertexBuffer);
	glDeleteBuffers(1, &sPointInstanceBuffer);
	glDeleteBuffers(1, &sPointIndexBuffer);
	glDeleteBuffers(1, &sLineVertexBuffer);
	glDeleteBuffers(1, &sLineIndexBuffer);
	glDeleteBuffers(1, &sQuadVertexBuffer);
	glDeleteBuffers(1, &sQuadInstanceBuffer);
	glDeleteBuffers(1, &sQuadIndexBuffer);
	glDeleteVertexArrays(1, &sPointVertexArray);
	glDeleteVertexArrays(1, &sLineVertexArray);
	glDeleteVertexArrays(1, &sQuadVertexArray);
	glDeleteProgram(sPointProgram);
	glDeleteProgram(sLineProgram);
	glDeleteProgram(sQuadProgram);
}
#endif // FAST_GL_IMPLEMENTATION

///////////////////////////////////////////////////////////////
// Text Declaration
///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
void TextFontAlloc(char const* FilePath)
{
	FILE* File = 0;
	fopen_s(&File, FilePath, "rb");

	struct OffsetTable
	{
		int unsigned ScalerType;
		short unsigned NumTables;
		short unsigned SearchRange;
		short unsigned EntrySelector;
		short unsigned RangeShift;
	};

	OffsetTable OffsetTbl = {};

	fread(&OffsetTbl, sizeof(OffsetTable), 1, File);
	OffsetTbl.ScalerType = B2L_ENDIAN_32(OffsetTbl.ScalerType);
	OffsetTbl.NumTables = B2L_ENDIAN_16(OffsetTbl.NumTables);
	OffsetTbl.SearchRange = B2L_ENDIAN_16(OffsetTbl.SearchRange);
	OffsetTbl.EntrySelector = B2L_ENDIAN_16(OffsetTbl.EntrySelector);
	OffsetTbl.RangeShift = B2L_ENDIAN_16(OffsetTbl.RangeShift);

	struct TableDirectory
	{
		char Tag[4];
		int unsigned CheckSum;
		int unsigned Offset;
		int unsigned Length;
	};

	TableDirectory HeadTableDir = {};
	TableDirectory GlyfTableDir = {};
	TableDirectory LocaTableDir = {};
	TableDirectory CmapTableDir = {};
	TableDirectory MaxpTableDir = {};

	for (short unsigned TableIndex = 0; TableIndex < OffsetTbl.NumTables; TableIndex++)
	{
		TableDirectory TableDir = {};

		fread(&TableDir, sizeof(TableDirectory), 1, File);
		TableDir.CheckSum = B2L_ENDIAN_32(TableDir.CheckSum);
		TableDir.Offset = B2L_ENDIAN_32(TableDir.Offset);
		TableDir.Length = B2L_ENDIAN_32(TableDir.Length);

		if (strncmp(TableDir.Tag, "head", 4) == 0)
		{
			memcpy(&HeadTableDir, &TableDir, sizeof(TableDirectory));
		}
		else if (strncmp(TableDir.Tag, "glyf", 4) == 0)
		{
			memcpy(&GlyfTableDir, &TableDir, sizeof(TableDirectory));
		}
		else if (strncmp(TableDir.Tag, "loca", 4) == 0)
		{
			memcpy(&LocaTableDir, &TableDir, sizeof(TableDirectory));
		}
		else if (strncmp(TableDir.Tag, "cmap", 4) == 0)
		{
			memcpy(&CmapTableDir, &TableDir, sizeof(TableDirectory));
		}
		else if (strncmp(TableDir.Tag, "maxp", 4) == 0)
		{
			memcpy(&MaxpTableDir, &TableDir, sizeof(TableDirectory));
		}
	}

	struct HeadTable
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
	};

	HeadTable HeadTbl = {};

	fseek(File, HeadTableDir.Offset, SEEK_SET);
	fread(&HeadTbl, sizeof(HeadTable), 1, File);
	HeadTbl.Version = B2L_ENDIAN_32(HeadTbl.Version);
	HeadTbl.FontRevision = B2L_ENDIAN_32(HeadTbl.FontRevision);
	HeadTbl.CheckSumAdjustment = B2L_ENDIAN_32(HeadTbl.CheckSumAdjustment);
	HeadTbl.MagicNumber = B2L_ENDIAN_32(HeadTbl.MagicNumber);
	HeadTbl.Flags = B2L_ENDIAN_16(HeadTbl.Flags);
	HeadTbl.UnitsPerEm = B2L_ENDIAN_16(HeadTbl.UnitsPerEm);
	HeadTbl.Created = B2L_ENDIAN_64(HeadTbl.Created);
	HeadTbl.Modified = B2L_ENDIAN_64(HeadTbl.Modified);
	HeadTbl.MinX = B2L_ENDIAN_16(HeadTbl.MinX);
	HeadTbl.MinY = B2L_ENDIAN_16(HeadTbl.MinY);
	HeadTbl.MaxX = B2L_ENDIAN_16(HeadTbl.MaxX);
	HeadTbl.MaxY = B2L_ENDIAN_16(HeadTbl.MaxY);
	HeadTbl.MacStyle = B2L_ENDIAN_16(HeadTbl.MacStyle);
	HeadTbl.LowestRecPPEM = B2L_ENDIAN_16(HeadTbl.LowestRecPPEM);
	HeadTbl.FontDirectionHint = B2L_ENDIAN_16(HeadTbl.FontDirectionHint);
	HeadTbl.IndexToLocFormat = B2L_ENDIAN_16(HeadTbl.IndexToLocFormat);
	HeadTbl.GlyphDataFormat = B2L_ENDIAN_16(HeadTbl.GlyphDataFormat);
	assert(HeadTbl.Version == 0x10000);
	assert(HeadTbl.MagicNumber == 0x5F0F3CF5);

	struct MaxpTable
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
	};

	MaxpTable MaxpTbl = {};

	fseek(File, MaxpTableDir.Offset, SEEK_SET);
	fread(&MaxpTbl, sizeof(MaxpTable), 1, File);
	MaxpTbl.Version = B2L_ENDIAN_32(MaxpTbl.Version);
	MaxpTbl.NumGlyphs = B2L_ENDIAN_16(MaxpTbl.NumGlyphs);
	MaxpTbl.MaxPoints = B2L_ENDIAN_16(MaxpTbl.MaxPoints);
	MaxpTbl.MaxContours = B2L_ENDIAN_16(MaxpTbl.MaxContours);
	MaxpTbl.MaxComponentPoints = B2L_ENDIAN_16(MaxpTbl.MaxComponentPoints);
	MaxpTbl.MaxComponentContours = B2L_ENDIAN_16(MaxpTbl.MaxComponentContours);
	MaxpTbl.MaxZones = B2L_ENDIAN_16(MaxpTbl.MaxZones);
	MaxpTbl.MaxTwilightPoints = B2L_ENDIAN_16(MaxpTbl.MaxTwilightPoints);
	MaxpTbl.MaxStorage = B2L_ENDIAN_16(MaxpTbl.MaxStorage);
	MaxpTbl.MaxFunctionDefs = B2L_ENDIAN_16(MaxpTbl.MaxFunctionDefs);
	MaxpTbl.MaxInstructionDefs = B2L_ENDIAN_16(MaxpTbl.MaxInstructionDefs);
	MaxpTbl.MaxStackElements = B2L_ENDIAN_16(MaxpTbl.MaxStackElements);
	MaxpTbl.MaxSizeOfInstructions = B2L_ENDIAN_16(MaxpTbl.MaxSizeOfInstructions);
	MaxpTbl.MaxComponentElements = B2L_ENDIAN_16(MaxpTbl.MaxComponentElements);
	MaxpTbl.MaxComponentDepth = B2L_ENDIAN_16(MaxpTbl.MaxComponentDepth);
	assert(MaxpTbl.Version == 0x10000);

	int unsigned* GlyphOffsets = (int unsigned*)calloc(MaxpTbl.NumGlyphs, sizeof(int unsigned));
	char unsigned BytesPerEntry = (HeadTbl.IndexToLocFormat) ? 2 : 4;
	for (short unsigned GlyphIndex = 0; GlyphIndex < MaxpTbl.NumGlyphs; GlyphIndex++)
	{
		fseek(File, LocaTableDir.Offset + (GlyphIndex * BytesPerEntry), SEEK_SET);
		if (HeadTbl.IndexToLocFormat)
		{
			short unsigned GlyphOffset = 0;
			fread(&GlyphOffset, sizeof(short unsigned), 1, File);
			GlyphOffset = B2L_ENDIAN_16(GlyphOffset);
			GlyphOffset *= 2;
			GlyphOffsets[GlyphIndex] = GlyphOffset;
		}
		else
		{
			int unsigned GlyphOffset = 0;
			fread(&GlyphOffset, sizeof(int unsigned), 1, File);
			GlyphOffset = B2L_ENDIAN_32(GlyphOffset);
			GlyphOffsets[GlyphIndex] = GlyphOffset;
		}
	}

	sGlyphs = (Glyph*)calloc(MaxpTbl.NumGlyphs, sizeof(Glyph));

	for (short unsigned GlyphIndex = 0; GlyphIndex < MaxpTbl.NumGlyphs; GlyphIndex++)
	{
		//TextFontReadGlyph(); // TODO

		printf("Glyph %u:\n", GlyphIndex);
		for (short unsigned ContourIndex = 0; ContourIndex < sGlyphs[GlyphIndex].Description.NumOfContours; ContourIndex++)
		{
			printf("\tContour End Index %d: %d\n", ContourIndex, sGlyphs[GlyphIndex].ContourEndIndices[ContourIndex]);
		}
		for (short unsigned PointIndex = 0; PointIndex < sGlyphs[GlyphIndex].NumOfPoints; PointIndex++)
		{
			printf("\tPoint %d: (%d %d)\n", PointIndex, sGlyphs[GlyphIndex].Points[PointIndex].X, sGlyphs[GlyphIndex].Points[PointIndex].Y);
		}
		printf("\n");
	}

	free(GlyphOffsets);

	fclose(File);
}
/*
void TextFontReadGlyph(FILE* File, Glyph* Glyphs, short unsigned GlyphIndex)
{
	fseek(File, GlyfTableDir.Offset + GlyphOffsets[GlyphIndex], SEEK_SET);
	fread(&sGlyphs[GlyphIndex].Description, sizeof(GlyphDescription), 1, File);
	sGlyphs[GlyphIndex].Description.NumOfContours = B2L_ENDIAN_16(sGlyphs[GlyphIndex].Description.NumOfContours);
	sGlyphs[GlyphIndex].Description.MinX = B2L_ENDIAN_16(sGlyphs[GlyphIndex].Description.MinX);
	sGlyphs[GlyphIndex].Description.MinY = B2L_ENDIAN_16(sGlyphs[GlyphIndex].Description.MinY);
	sGlyphs[GlyphIndex].Description.MaxX = B2L_ENDIAN_16(sGlyphs[GlyphIndex].Description.MaxX);
	sGlyphs[GlyphIndex].Description.MaxY = B2L_ENDIAN_16(sGlyphs[GlyphIndex].Description.MaxY);

	if (sGlyphs[GlyphIndex].Description.NumOfContours >= 0)
	{
		TextFontReadSimpleGlyph(File, sGlyphs[GlyphIndex]);
	}
	else
	{
		TextFontReadCompoundGlyph(File, sGlyphs[GlyphIndex]);
	}
}
void TextFontReadSimpleGlyph(FILE* File, Glyph* Glyph)
{
	sGlyphs[GlyphIndex].ContourEndIndices = (short unsigned*)malloc(sGlyphs[GlyphIndex].Description.NumOfContours * sizeof(short unsigned));
	for (short unsigned ContourIndex = 0; ContourIndex < sGlyphs[GlyphIndex].Description.NumOfContours; ContourIndex++)
	{
		fread(&sGlyphs[GlyphIndex].ContourEndIndices[ContourIndex], sizeof(short unsigned), 1, File);
		sGlyphs[GlyphIndex].ContourEndIndices[ContourIndex] = B2L_ENDIAN_16(sGlyphs[GlyphIndex].ContourEndIndices[ContourIndex]);
		sGlyphs[GlyphIndex].NumOfPoints = MAX(sGlyphs[GlyphIndex].NumOfPoints, sGlyphs[GlyphIndex].ContourEndIndices[ContourIndex] + 1);
	}

	sGlyphs[GlyphIndex].Points = (GlyphPoint*)malloc(sGlyphs[GlyphIndex].NumOfPoints * sizeof(GlyphPoint));
	sGlyphs[GlyphIndex].Flags = (char unsigned*)malloc(sGlyphs[GlyphIndex].NumOfPoints);

	fread(&sGlyphs[GlyphIndex].NumOfInstructions, sizeof(short unsigned), 1, File);
	sGlyphs[GlyphIndex].NumOfInstructions = B2L_ENDIAN_16(sGlyphs[GlyphIndex].NumOfInstructions);
	sGlyphs[GlyphIndex].Instructions = (char unsigned*)malloc(sGlyphs[GlyphIndex].NumOfInstructions);
	fread(sGlyphs[GlyphIndex].Instructions, sizeof(char unsigned), sGlyphs[GlyphIndex].NumOfInstructions, File);

	for (short unsigned PointIndex = 0; PointIndex < sGlyphs[GlyphIndex].NumOfPoints; PointIndex++)
	{
		fread(&sGlyphs[GlyphIndex].Flags[PointIndex], sizeof(char unsigned), 1, File);

		if ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 3)) == (1 << 3))
		{
			char unsigned RepeatCount = 0;
			fread(&RepeatCount, sizeof(char unsigned), 1, File);

			for (char unsigned RepeatIndex = 0; RepeatIndex < RepeatCount; RepeatIndex++)
			{
				PointIndex++;
				sGlyphs[GlyphIndex].Flags[PointIndex] = sGlyphs[GlyphIndex].Flags[PointIndex - 1];
			}
		}
	}

	short CoordX = 0;
	short CoordY = 0;

	for (short unsigned PointIndex = 0; PointIndex < sGlyphs[GlyphIndex].NumOfPoints; PointIndex++)
	{
		if ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 1)) == (1 << 1))
		{
			char CoordOffset = 0;
			fread(&CoordOffset, sizeof(char), 1, File);
			CoordX += ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 4)) == (1 << 4)) ? CoordOffset : -CoordOffset;
		}
		else if ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 4)) != (1 << 4))
		{
			short CoordOffset = 0;
			fread(&CoordOffset, sizeof(short), 1, File);
			CoordOffset = B2L_ENDIAN_16(CoordOffset);
			CoordX += CoordOffset;
		}

		sGlyphs[GlyphIndex].Points[PointIndex].X = CoordX;
		sGlyphs[GlyphIndex].Points[PointIndex].OnCurve = sGlyphs[GlyphIndex].Flags[PointIndex] & 1;
	}

	for (short unsigned PointIndex = 0; PointIndex < sGlyphs[GlyphIndex].NumOfPoints; PointIndex++)
	{
		if ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 2)) == (1 << 2))
		{
			char CoordOffset = 0;
			fread(&CoordOffset, sizeof(char), 1, File);
			CoordY += ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 5)) == (1 << 5)) ? CoordOffset : -CoordOffset;
		}
		else if ((sGlyphs[GlyphIndex].Flags[PointIndex] & (1 << 5)) != (1 << 5))
		{
			short CoordOffset = 0;
			fread(&CoordOffset, sizeof(short), 1, File);
			CoordOffset = B2L_ENDIAN_16(CoordOffset);
			CoordY += CoordOffset;
		}

		sGlyphs[GlyphIndex].Points[PointIndex].Y = CoordY;
		sGlyphs[GlyphIndex].Points[PointIndex].OnCurve = sGlyphs[GlyphIndex].Flags[PointIndex] & 1;
	}
}
void TextFontReadCompoundGlyph(FILE* File)
{
	while (true)
	{
		short unsigned Flags = 0;
		fread(&Flags, sizeof(short unsigned), 1, File);
		Flags = B2L_ENDIAN_16(Flags);

		short unsigned NewGlyphIndex = 0;
		fread(&NewGlyphIndex, sizeof(short unsigned), 1, File);
		NewGlyphIndex = B2L_ENDIAN_16(NewGlyphIndex);

		if (GlyphOffsets[GlyphIndex] == GlyphOffsets[NewGlyphIndex])
		{
			assert(0);
		}

		bool ArgsAre2Bytes = (Flags & (1 << 0)) == (1 << 0);
		bool ArgsAreXYValues = (Flags & (1 << 1)) == (1 << 1);
		bool RoundXYToGrid = (Flags & (1 << 2)) == (1 << 2);
		bool IsSingleScaleValue = (Flags & (1 << 3)) == (1 << 3);
		bool IsMoreComponentsAfterThis = (Flags & (1 << 5)) == (1 << 5);
		bool IsXAndYScale = (Flags & (1 << 6)) == (1 << 6);
		bool Is2x2Matrix = (Flags & (1 << 7)) == (1 << 7);
		bool HasInstructions = (Flags & (1 << 8)) == (1 << 8);
		bool UseThisComponentMetrics = (Flags & (1 << 9)) == (1 << 9);
		bool ComponentsOverlap = (Flags & (1 << 10)) == (1 << 10);

		int Arg0 = 0;
		int Arg1 = 0;

		if (ArgsAre2Bytes)
		{
			fread(&Arg0, sizeof(short), 1, File);
			Arg0 = B2L_ENDIAN_16(Arg0);

			fread(&Arg1, sizeof(short), 1, File);
			Arg1 = B2L_ENDIAN_16(Arg1);
		}
		else
		{
			fread(&Arg0, sizeof(char), 1, File);
			fread(&Arg1, sizeof(char), 1, File);
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
			short Value = 0;
			fread(&Value, sizeof(short), 1, File);
			Value = B2L_ENDIAN_16(Value);

			IHatX = (double)Value / (double)(1 << 14);
			JHatY = (double)Value / (double)(1 << 14);
		}
		else if (IsXAndYScale)
		{
			short ValueIX = 0;
			fread(&ValueIX, sizeof(short), 1, File);
			ValueIX = B2L_ENDIAN_16(ValueIX);

			short ValueJY = 0;
			fread(&ValueJY, sizeof(short), 1, File);
			ValueJY = B2L_ENDIAN_16(ValueJY);

			IHatX = (double)ValueIX / (double)(1 << 14);
			JHatY = (double)ValueJY / (double)(1 << 14);
		}
		else if (Is2x2Matrix)
		{
			short ValueIX = 0;
			fread(&ValueIX, sizeof(short), 1, File);
			ValueIX = B2L_ENDIAN_16(ValueIX);

			short ValueIY = 0;
			fread(&ValueIY, sizeof(short), 1, File);
			ValueIY = B2L_ENDIAN_16(ValueIY);

			short ValueJX = 0;
			fread(&ValueJX, sizeof(short), 1, File);
			ValueJX = B2L_ENDIAN_16(ValueJX);

			short ValueJY = 0;
			fread(&ValueJY, sizeof(short), 1, File);
			ValueJY = B2L_ENDIAN_16(ValueJY);

			IHatX = (double)ValueIX / (double)(1 << 14);
			IHatY = (double)ValueIY / (double)(1 << 14);
			JHatX = (double)ValueJX / (double)(1 << 14);
			JHatY = (double)ValueJY / (double)(1 << 14);
		}

		int unsigned StoredLocation = ftell(File);

		TextFontReadGlyph(File);

		fseek(File, StoredLocation, SEEK_SET);

		for (short unsigned PointIndex = 0; PointIndex < SimpleGlyph.NumOfPoints; PointIndex++)
		{
			SimpleGlyph.Points[PointIndex].X = (short)(IHatX * (double)SimpleGlyph.Points[PointIndex].X + JHatX * (double)SimpleGlyph.Points[PointIndex].Y + OffsetX);
			SimpleGlyph.Points[PointIndex].Y = (short)(IHatY * (double)SimpleGlyph.Points[PointIndex].X + JHatY * (double)SimpleGlyph.Points[PointIndex].Y + OffsetY);
		}



		if (IsMoreComponentsAfterThis == 0)
		{
			break;
		}
	}
}
*/
Glyph* TextFontGlyph(int unsigned Glyph)
{
	return &sGlyphs[Glyph];
}
void TextFontFree(void)
{
	free(sGlyphs);
}
#endif // FAST_GL_IMPLEMENTATION

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FAST_GL_H
