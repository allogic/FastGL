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
	// Configuration
	///////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define FAST_GL_DEBUG
#endif //_DEBUG

	///////////////////////////////////////////////////////////////
	// Global Macros
	///////////////////////////////////////////////////////////////

#define STATIC_ASSERT(EXPRESSION, MESSAGE) typedef char static_assertion_##MESSAGE[(EXPRESSION) ? 1 : -1]

#define OFFSET_OF(TYPE, MEMBER) ((long long unsigned)&(((TYPE*)0)->MEMBER))

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

#define SHADER_GL_VERSION \
	"#version 460 core\n"

#define SHADER_CONSTANTS \
	"const float PI = 3.1415926;" \
	"const float TAU = 6.2831853;" \

#define SHADER_RANDOM_IMPLEMENTATION \
	"const vec4 RANDOM_SCALE = vec4(443.897, 441.423, .0973, .1099);" \
	"vec2 Random2(vec2 Position) {" \
	"	vec3 p3 = fract(Position.xyx * RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 19.19);" \
	"	return fract((p3.xx + p3.yz) * p3.zy);" \
	"}" \
	"vec2 Random2(vec3 Position) {" \
	"	vec3 p3 = fract(Position * RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yzx + 19.19);" \
	"	return fract((p3.xx + p3.yz) * p3.zy);" \
	"}" \
	"vec3 Random3(vec2 Position) {" \
	"	vec3 p3 = fract(vec3(Position.xyx) * RANDOM_SCALE.xyz);" \
	"	p3 += dot(p3, p3.yxz + 19.19);" \
	"	return fract((p3.xxy + p3.yzz) * p3.zyx);" \
	"}" \
	"vec3 Random3(vec3 Position) {" \
	"	Position = fract(Position * RANDOM_SCALE.xyz);" \
	"	Position += dot(Position, Position.yxz + 19.19);" \
	"	return fract((Position.xxy + Position.yzz) * Position.zyx);" \
	"}"

#define SHADER_VORONOI_IMPLEMENTATION \
	"float Voronoi2D(vec2 Position, float AngleOffset, float Radius, float Density) {" \
	"	vec2 n = floor(Position * Density);" \
	"	vec2 f = fract(Position * Density);" \
	"	float f1 = 8.0;" \
	"	for (int j = -1; j <= 1; j++) {" \
	"		for (int i = -1; i <= 1; i++) {" \
	"			vec2 g = vec2(i, j);" \
	"			vec2 o = Random2(n + g);" \
	"			o = 0.5 + 0.41 * sin(AngleOffset + TAU * o);" \
	"			vec2 r = (g - f + o) * Radius;" \
	"			float d = sqrt(dot(r,r));" \
	"			if (d < f1) {" \
	"				f1 = d;" \
	"			}" \
	"		}" \
	"	}" \
	"	return f1;" \
	"}"

#define SHADER_VORONOISE_IMPLEMENTATION \
	"float Voronoise2D(vec2 Position, float U, float V) {" \
	"	float k = 1.0 + 63.0 * pow(1.0 - V, 6.0);" \
	"	vec2 i = floor(Position);" \
	"	vec2 f = fract(Position);" \
	"	vec2 a = vec2(0.0, 0.0);" \
	"	vec2 g = vec2(-2.0);" \
	"	for (g.y = -2.0; g.y <= 2.0; g.y++) {" \
	"		for (g.x = -2.0; g.x <= 2.0; g.x++) {" \
	"			vec3 o = Random3(i + g) * vec3(U, U, 1.0);" \
	"			vec2 d = g - f + o.xy;" \
	"			float w = pow(1.0 - smoothstep(0.0, 1.414, length(d)), k);" \
	"			a += vec2(o.z * w, w);" \
	"		}" \
	"	}" \
	"	return a.x / a.y;" \
	"}" \
	"float Voronoise3D(vec3 Position, float U, float V) {" \
	"	float k = 1.0 + 63.0 * pow(1.0 - V, 6.0);" \
	"	vec3 i = floor(Position);" \
	"	vec3 f = fract(Position);" \
	"	float s = 1.0 + 31.0 * V;" \
	"	vec2 a = vec2(0.0, 0.0);" \
	"	vec3 g = vec3(-2.0);" \
	"	for (g.z = -2.0; g.z <= 2.0; g.z++) {" \
	"		for (g.y = -2.0; g.y <= 2.0; g.y++) {" \
	"			for (g.x = -2.0; g.x <= 2.0; g.x++) {" \
	"				vec3 o = Random3(i + g) * vec3(U, U, 1.);" \
	"				vec3 d = g - f + o + 0.5;" \
	"				float w = pow(1.0 - smoothstep(0.0, 1.414, length(d)), k);" \
	"				a += vec2(o.z * w, w);" \
	"			}" \
	"		}" \
	"	}" \
	"	return a.x / a.y;" \
	"}"

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

	typedef void(*glDebug_PROC)(int unsigned Source, int unsigned Type, int unsigned ID, int unsigned Severity, int Length, char const* Message, void const* UserParam);
	typedef void(*glDebugMessageCallback_PROC)(glDebug_PROC Callback, void const* UserParam);
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
	typedef void(*glUniform1i_PROC)(int unsigned Location, int Value);
	typedef void(*glUniform1ui_PROC)(int unsigned Location, int unsigned Value);
	typedef void(*glUniform1f_PROC)(int unsigned Location, float Value);
	typedef void(*glUniform2fv_PROC)(int unsigned Location, int Count, float const* Value);
	typedef void(*glUniform3fv_PROC)(int unsigned Location, int Count, float const* Value);
	typedef void(*glUniform4fv_PROC)(int unsigned Location, int Count, float const* Value);
	typedef void(*glUniformMatrix4fv_PROC)(int unsigned Location, int unsigned Count, char unsigned Transpose, float const* Value);
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
	typedef void*(*glMapBuffer_PROC)(int unsigned Target, int unsigned Access);
	typedef void*(*glMapBufferRange_PROC)(int unsigned Target, int unsigned Offset, int unsigned Length, int unsigned Access);
	typedef char unsigned(*glUnmapBuffer_PROC)(int unsigned Target);
	typedef void(*glBindTextureUnit_PROC)(int unsigned Unit, int unsigned Texture);
	typedef void(*glGenerateMipmap_PROC)(int unsigned Target);
	typedef void(*glGenFramebuffers_PROC)(int unsigned Num, int unsigned* FrameBuffers);
	typedef void(*glBindFramebuffer_PROC)(int unsigned Target, int unsigned FrameBuffer);
	typedef void(*glFramebufferParameteri_PROC)(int unsigned Target, int unsigned ParamName, int Param);
	typedef void(*glFramebufferTexture2D_PROC)(int unsigned Target, int unsigned Attachment, int unsigned TexureTarget, int unsigned Texture, int Level);
	typedef void(*glDrawBuffers_PROC)(int unsigned Num, int unsigned const* Buffers);
	typedef void(*glDeleteFramebuffers_PROC)(int unsigned Num, int unsigned const* FrameBuffers);

#ifdef FAST_GL_IMPLEMENTATION
	glDebugMessageCallback_PROC glDebugMessageCallback = 0;
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
	glGenerateMipmap_PROC glGenerateMipmap = 0;
	glGenFramebuffers_PROC glGenFramebuffers = 0;
	glBindFramebuffer_PROC glBindFramebuffer = 0;
	glFramebufferParameteri_PROC glFramebufferParameteri = 0;
	glFramebufferTexture2D_PROC glFramebufferTexture2D = 0;
	glDrawBuffers_PROC glDrawBuffers = 0;
	glDeleteFramebuffers_PROC glDeleteFramebuffers = 0;
#else
	extern glDebugMessageCallback_PROC glDebugMessageCallback;
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

	extern void Memory_CheckForLeaksInternal(void);

#ifdef FAST_GL_IMPLEMENTATION
	static long long unsigned sAllocatedBytes = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Math Definition
	///////////////////////////////////////////////////////////////

#define VECTOR2_ZERO { 0.0F, 0.0F }
#define VECTOR3_ZERO { 0.0F, 0.0F, 0.0F }
#define VECTOR4_ZERO { 0.0F, 0.0F, 0.0F, 0.0F }
#define VECTOR2_ONE { 1.0F, 1.0F }
#define VECTOR3_ONE { 1.0F, 1.0F, 1.0F }
#define VECTOR4_ONE { 1.0F, 1.0F, 1.0F, 1.0F }
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

	extern void Matrix4_Set(Matrix4 const Value, Matrix4 Result);
	extern void Matrix4_Zero(Matrix4 Result);
	extern void Matrix4_One(Matrix4 Result);
	extern void Matrix4_Copy(Matrix4 const Value, Matrix4 Result);
	extern void Matrix4_Identity(Matrix4 Result);
	extern void Matrix4_GetPosition(Matrix4 const Value, Vector3 Result);
	extern void Matrix4_GetRotation(Matrix4 const Value, Quaternion Result);
	extern void Matrix4_GetScale(Matrix4 const Value, Vector3 Result);
	extern void Matrix4_SetPosition(Vector3 const Value, Matrix4 Result);
	extern void Matrix4_SetPositionSimple(float ValueX, float ValueY, float ValueZ, Matrix4 Result);
	extern void Matrix4_SetRotation(Quaternion const Value, Matrix4 Result);
	extern void Matrix4_SetRotationSimple(float ValueX, float ValueY, float ValueZ, float ValueW, Matrix4 Result);
	extern void Matrix4_SetScale(Vector3 const Value, Matrix4 Result);
	extern void Matrix4_SetScaleSimple(float ValueX, float ValueY, float ValueZ, Matrix4 Result);
	extern void Matrix4_Decompose(Matrix4 const Value, Vector3 Position, Quaternion Rotation, Vector3 Scale);
	extern void Matrix4_Mul(Matrix4 const A, Matrix4 const B, Matrix4 Result);
	extern void Matrix4_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, Matrix4 Result);
	extern void Matrix4_Perspective(float FieldOfView, float AspectRatio, float NearZ, float FarZ, Matrix4 Result);
	extern void Matrix4_LookAt(Vector3 const Eye, Vector3 const Center, Vector3 const Up, Matrix4 Result);

	extern float Math_StepTowards(float Current, float Target, float Step);

	///////////////////////////////////////////////////////////////
	// Vector Definition
	///////////////////////////////////////////////////////////////

#define VECTOR_INITIAL_CAPACITY (16ULL)

	typedef struct
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

	///////////////////////////////////////////////////////////////
	// HashMap Definition
	///////////////////////////////////////////////////////////////

#define HASH_MAP_INITIAL_CAPACITY (128ULL)
#define HASH_MAP_INITIAL_HASH (5381ULL)
#define HASH_MAP_LOAD_FACTOR (0.75F)

	typedef struct
	{
		void* Next;
		void* Key;
		void* Value;
		long long unsigned KeySize;
		long long unsigned ValueSize;
	} HashMapPair;
	typedef struct
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

	typedef struct
	{
		double Frequency;
		double StartMicroSeconds;
		double EndMicroSeconds;
		double ElapsedMicroSeconds;
	} Timer;

	extern void Timer_Alloc(Timer* Timr);
	extern void Timer_BeginMeasure(Timer* Timr);
	extern void Timer_EndMeasure(Timer* Timr);
	extern double Timer_ElapsedNanoSeconds(Timer* Timr);
	extern double Timer_ElapsedMicroSeconds(Timer* Timr);
	extern double Timer_ElapsedMilliSeconds(Timer* Timr);

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

	extern void Transform_Alloc(Transform* Trans);
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

	extern void Controller_FirstPersonAlloc(FirstPersonController* Controller);
	extern void Controller_OrbitAlloc(OrbitController* Controller);
	extern void Controller_UpdateFirstPerson(FirstPersonController* Controller, float DeltaTime);
	extern void Controller_UpdateOrbit(OrbitController* Controller, float DeltaTime);
	extern void Controller_ComputeFirstPersonViewMatrix(FirstPersonController* Controller, Matrix4 View);
	extern void Controller_ComputeOrbitViewMatrix(OrbitController* Controller, Matrix4 View);

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
	extern void Shader_SetUniformVector2(int unsigned Program, char const* UniformName, Vector2 Value);
	extern void Shader_SetUniformVector3(int unsigned Program, char const* UniformName, Vector3 Value);
	extern void Shader_SetUniformVector4(int unsigned Program, char const* UniformName, Vector4 Value);
	extern void Shader_SetUniformMatrix4(int unsigned Program, char const* UniformName, Matrix4 Value);
	extern void Shader_ExecuteCompute(int unsigned NumGroupsX, int unsigned NumGroupsY, int unsigned NumGroupsZ);
	extern void Shader_Free(int unsigned Program);

	extern void Shader_CheckCompileStatus(int unsigned Shader);
	extern void Shader_CheckLinkStatus(int unsigned Program);

	///////////////////////////////////////////////////////////////
	// VertexArray Definition
	///////////////////////////////////////////////////////////////

	extern void VertexArray_Alloc(int unsigned* VertexArray);
	extern void VertexArray_Bind(int unsigned VertexArray);
	extern void VertexArray_UnBind(void);
	extern void VertexArray_Free(int unsigned VertexArray);

	///////////////////////////////////////////////////////////////
	// Buffer Definition
	///////////////////////////////////////////////////////////////

	extern void Buffer_VertexAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage);
	extern void Buffer_IndexAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage);
	extern void Buffer_UniformAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage);
	extern void Buffer_StorageAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage);
	extern void Buffer_VertexBind(int unsigned Buffer);
	extern void Buffer_IndexBind(int unsigned Buffer);
	extern void Buffer_UniformBind(int unsigned Buffer);
	extern void Buffer_StorageBind(int unsigned Buffer);
	extern void Buffer_VertexSetData(void const* Data, int unsigned Size);
	extern void Buffer_IndexSetData(void const* Data, int unsigned Size);
	extern void Buffer_UniformSetData(void const* Data, int unsigned Size);
	extern void Buffer_StorageSetData(void const* Data, int unsigned Size);
	extern void Buffer_VertexGetData(void* Data, int unsigned Size);
	extern void Buffer_IndexGetData(void* Data, int unsigned Size);
	extern void Buffer_UniformGetData(void* Data, int unsigned Size);
	extern void Buffer_StorageGetData(void* Data, int unsigned Size);
	extern void Buffer_VertexSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_IndexSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_UniformSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_StorageSetSubData(void const* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_VertexGetSubData(void* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_IndexGetSubData(void* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_UniformGetSubData(void* Data, int unsigned Offset, int unsigned Size);
	extern void Buffer_StorageGetSubData(void* Data, int unsigned Offset, int unsigned Size);
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
		Vector4 Color;
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
		Vector4 Color;
		int unsigned Direction;
	} PointInstanceEntry;
	typedef struct
	{
		Vector3 Position;
		Vector3 Size;
		Vector4 Color;
		int unsigned Direction;
	} QuadInstanceEntry;

	extern void Gizmo_Alloc(int unsigned NumPoints, int unsigned NumLines, int unsigned NumQuads);
	extern void Gizmo_BeginPoints(void);
	extern void Gizmo_DrawPoint(GizmoDir Direction, Vector3 Position, float Radius, Vector4 Color);
	extern void Gizmo_DrawPointSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float Radius, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_EndPoints(Matrix4 Projection, Matrix4 View);
	extern void Gizmo_BeginLines(void);
	extern void Gizmo_DrawLine(GizmoDir Direction, Vector3 From, Vector3 To, float Thickness, Vector4 Color);
	extern void Gizmo_DrawLineSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_DrawLineRect(GizmoDir Direction, Vector3 Position, Vector3 Size, float Thickness, Vector4 Color);
	extern void Gizmo_DrawLineRectSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_DrawLineCircle(GizmoDir Direction, Vector3 Position, int unsigned NumSegments, float Radius, float Thickness, Vector4 Color);
	extern void Gizmo_DrawLineCircleSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumSegments, float Radius, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_DrawLineGrid(GizmoDir Direction, Vector3 Position, int unsigned NumLines, float Scale, float Thickness, Vector4 Color);
	extern void Gizmo_DrawLineGridSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumLines, float Scale, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_DrawLineBezierQuadratic(GizmoDir Direction, Vector3 From, Vector3 Ctrl, Vector3 To, int unsigned NumSegments, float Thickness, Vector4 Color);
	extern void Gizmo_DrawLineBezierQuadraticSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlX, float CtrlY, float CtrlZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_DrawLineBezierCubic(GizmoDir Direction, Vector3 From, Vector3 CtrlA, Vector3 CtrlB, Vector3 To, int unsigned NumSegments, float Thickness, Vector4 Color);
	extern void Gizmo_DrawLineBezierCubicSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlAX, float CtrlAY, float CtrlAZ, float CtrlBX, float CtrlBY, float CtrlBZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_EndLines(Matrix4 Projection, Matrix4 View);
	extern void Gizmo_BeginQuads(void);
	extern void Gizmo_DrawQuad(GizmoDir Direction, Vector3 Position, Vector3 Size, Vector4 Color);
	extern void Gizmo_DrawQuadSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Gizmo_EndQuads(Matrix4 Projection, Matrix4 View);
	extern void Gizmo_Free(void);

#ifdef FAST_GL_IMPLEMENTATION
	static char const sPointVertexShader[] =
		SHADER_GL_VERSION
		"layout (location = 0) in vec3 InstancePosition;"
		"layout (location = 1) in float InstanceRadius;"
		"layout (location = 2) in vec4 InstanceColor;"
		"layout (location = 3) in uint InstanceDirection;"
		"out VS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	vec4 Color;"
		"	flat uint Direction;"
		"} VertexOutput;"
		"void main() {"
		"	VertexOutput.Position = InstancePosition;"
		"	VertexOutput.Radius = InstanceRadius;"
		"	VertexOutput.Color = InstanceColor;"
		"	VertexOutput.Direction = InstanceDirection;"
		"}";
	static char const sPointGeometryShader[] =
		SHADER_GL_VERSION
		"layout (points) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 3) out;"
		"in VS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	vec4 Color;"
		"	flat uint Direction;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	vec4 Color;"
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
		"	vec4 Color = GeometryInput[0].Color;"
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
	static char const sPointFragmentShader[] =
		SHADER_GL_VERSION
		"in GS_OUT {"
		"	vec3 Position;"
		"	float Radius;"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	if (dot(FragmentInput.Position, FragmentInput.Position) > (FragmentInput.Radius * FragmentInput.Radius)) discard;"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sLineVertexShader[] =
		SHADER_GL_VERSION
		"layout (location = 0) in vec3 InputPosition;"
		"layout (location = 1) in float InputThickness;"
		"layout (location = 2) in vec4 InputColor;"
		"layout (location = 3) in uint InputDirection;"
		"out VS_OUT {"
		"	float Thickness;"
		"	vec4 Color;"
		"	flat uint Direction;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(InputPosition, 1.0);"
		"	VertexOutput.Thickness = InputThickness;"
		"	VertexOutput.Color = InputColor;"
		"	VertexOutput.Direction = InputDirection;"
		"}";
	static char const sLineGeometryShader[] =
		SHADER_GL_VERSION
		"layout (lines) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 4) out;"
		"in VS_OUT {"
		"	float Thickness;"
		"	vec4 Color;"
		"	flat uint Direction;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec4 Color;"
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
		"	vec4 Color = GeometryInput[0].Color;"
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
		"	vec3 P0 = Start + OffsetDir;"
		"	vec3 P1 = Start - OffsetDir;"
		"	vec3 P2 = End + OffsetDir;"
		"	vec3 P3 = End - OffsetDir;"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P0, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P1, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P2, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P3, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sLineFragmentShader[] =
		SHADER_GL_VERSION
		"in GS_OUT {"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static char const sQuadVertexShader[] =
		SHADER_GL_VERSION
		"layout (location = 0) in vec3 InstancePosition;"
		"layout (location = 1) in vec3 InstanceSize;"
		"layout (location = 2) in vec4 InstanceColor;"
		"layout (location = 3) in uint InstanceDirection;"
		"out VS_OUT {"
		"	vec3 Position;"
		"	vec3 Size;"
		"	vec4 Color;"
		"	flat uint Direction;"
		"} VertexOutput;"
		"void main() {"
		"	VertexOutput.Position = InstancePosition;"
		"	VertexOutput.Size = InstanceSize;"
		"	VertexOutput.Color = InstanceColor;"
		"	VertexOutput.Direction = InstanceDirection;"
		"}";
	static char const sQuadGeometryShader[] =
		SHADER_GL_VERSION
		"layout (points) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 4) out;"
		"in VS_OUT {"
		"	vec3 Position;"
		"	vec3 Size;"
		"	vec4 Color;"
		"	flat uint Direction;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec4 Color;"
		"} GeometryOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"const uint GIZMO_DIR_XY = 0;"
		"const uint GIZMO_DIR_XZ = 1;"
		"const uint GIZMO_DIR_ZY = 2;"
		"void main() {"
		"	vec3 Position = GeometryInput[0].Position;"
		"	vec3 Size = GeometryInput[0].Size;"
		"	vec4 Color = GeometryInput[0].Color;"
		"	uint Direction = GeometryInput[0].Direction;"
		"	vec3 OffsetADir = vec3(0.0);"
		"	vec3 OffsetBDir = vec3(0.0);"
		"	switch (Direction) {"
		"		case GIZMO_DIR_XY: {"
		"			OffsetADir = vec3(Size.x, 0.0, 0.0);"
		"			OffsetBDir = vec3(0.0, Size.y, 0.0);"
		"			break;"
		"		}"
		"		case GIZMO_DIR_XZ: {"
		"			OffsetADir = vec3(Size.x, 0.0, 0.0);"
		"			OffsetBDir = vec3(0.0, 0.0, Size.z);"
		"			break;"
		"		}"
		"		case GIZMO_DIR_ZY: {"
		"			OffsetADir = vec3(0.0, Size.y, 0.0);"
		"			OffsetBDir = vec3(0.0, 0.0, Size.z);"
		"			break;"
		"		}"
		"	}"
		"	vec3 P0 = Position;"
		"	vec3 P1 = Position + OffsetADir;"
		"	vec3 P2 = Position + OffsetBDir;"
		"	vec3 P3 = Position + OffsetADir + OffsetBDir;"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P0, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P1, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P2, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P3, 1.0);"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sQuadFragmentShader[] =
		SHADER_GL_VERSION
		"in GS_OUT {"
		"	vec4 Color;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"void main() {"
		"	BaseColor = FragmentInput.Color;"
		"}";
	static int unsigned sNumPoints = 0;
	static int unsigned sNumLines = 0;
	static int unsigned sNumQuads = 0;
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
	static int unsigned sQuadInstanceBuffer = 0;
	static int unsigned sQuadInstanceOffset = 0;
	static PointInstanceEntry* sMappedPointInstanceBuffer = 0;
	static LineVertex* sMappedLineVertexBuffer = 0;
	static int unsigned* sMappedLineIndexBuffer = 0;
	static QuadInstanceEntry* sMappedQuadInstanceBuffer = 0;
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
		Vector PointOffsets;
		Vector BezierPoints;
		Vector BezierOffsets;
		Vector BezierCurves;
	} Glyph;
	typedef struct
	{
		Vector3 Position;
		Vector4 Rotation;
		Vector2 Size;
		Vector2 Bearing;
		float UnitsPerEm;
		float Scale;
		int unsigned GlyphIndex;
		Vector4 Color;
	} GlyphInstanceEntry;
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
		short unsigned Width;
		short unsigned Height;
		int unsigned* GlyphOffsets;
		HashMap GlyphMapping;
		Glyph* Glyphs;
		int unsigned GlyphVertexArray;
		int unsigned GlyphInstanceBuffer;
		int unsigned GlyphInstanceOffset;
		int unsigned BezierOffsetBuffer;
		int unsigned BezierCurveBuffer;
		GlyphInstanceEntry* MappedGlyphInstanceBuffer;
		Vector BezierOffsets;
		Vector BezierCurves;
	} Font;
	typedef struct
	{
		int unsigned ReadLocation;
		short unsigned RangeOffset;
	} IDRangeOffsetMap;
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

	extern void Font_Alloc(Font* Fnt, int unsigned NumChars, char const* FilePath);
	extern Glyph* Font_GlyphByGlyphIndex(Font* Fnt, short unsigned GlyphIndex);
	extern Glyph* Font_GlyphByUnicode(Font* Fnt, int unsigned Unicode);
	extern short unsigned Font_NumGlyphs(Font* Fnt);
	extern void Font_Free(Font* Fnt);

	extern void Font_ReadGlyphInternal(Font* Fnt, FILE* File, short unsigned GlyphIndex, Glyph* Result);
	extern void Font_ReadSimpleGlyphInternal(Font* Fnt, FILE* File, Glyph* Result);
	extern void Font_ReadCompoundGlyphInternal(Font* Fnt, FILE* File, short unsigned GlyphIndex, Glyph* Result);
	extern void Font_ApplyLayoutInfosInternal(Font* Fnt, FILE* File);
	extern void Font_UnicodeToGlyphMappingsInternal(Font* Fnt, FILE* File);
	extern void Font_CreateBezierInternal(Font* Fnt, Glyph* Glyph);
	extern void Font_DebugGlyphsInternal(Font* Fnt, int unsigned UnicodeFrom, int unsigned UnicodeTo, Matrix4 Projection, Matrix4 View);

#ifdef FAST_GL_IMPLEMENTATION
	static int unsigned sFontProgram = 0;
	static char const sFontVertexShader[] =
		SHADER_GL_VERSION
		"layout (location = 0) in vec3 InstancePosition;"
		"layout (location = 1) in vec4 InstanceRotation;"
		"layout (location = 2) in vec2 InstanceSize;"
		"layout (location = 3) in vec2 InstanceBearing;"
		"layout (location = 4) in float InstanceUnitsPerEm;"
		"layout (location = 5) in float InstanceScale;"
		"layout (location = 6) in uint InstanceGlyphIndex;"
		"layout (location = 7) in vec4 InstanceColor;"
		"out VS_OUT {"
		"	vec3 Position;"
		"	vec4 Rotation;"
		"	vec2 Size;"
		"	vec2 Bearing;"
		"	float UnitsPerEm;"
		"	float Scale;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} VertexOutput;"
		"void main() {"
		"	VertexOutput.Position = InstancePosition;"
		"	VertexOutput.Rotation = InstanceRotation;"
		"	VertexOutput.Size = InstanceSize;"
		"	VertexOutput.Bearing = InstanceBearing;"
		"	VertexOutput.UnitsPerEm = InstanceUnitsPerEm;"
		"	VertexOutput.Scale = InstanceScale;"
		"	VertexOutput.GlyphIndex = InstanceGlyphIndex;"
		"	VertexOutput.Color = InstanceColor;"
		"}";
	static char const sFontGeometryShader[] =
		SHADER_GL_VERSION
		"layout (points) in;"
		"layout (triangle_strip) out;"
		"layout (max_vertices = 4) out;"
		"in VS_OUT {"
		"	vec3 Position;"
		"	vec4 Rotation;"
		"	vec2 Size;"
		"	vec2 Bearing;"
		"	float UnitsPerEm;"
		"	float Scale;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} GeometryInput[];"
		"out GS_OUT {"
		"	vec2 TextureCoords;"
		"	flat uint GlyphIndex;"
		"	vec4 Color;"
		"} GeometryOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"void main() {"
		"	vec3 Position = GeometryInput[0].Position;"
		"	vec4 Rotation = GeometryInput[0].Rotation;"
		"	vec2 Size = GeometryInput[0].Size;"
		"	vec2 Bearing = GeometryInput[0].Bearing;"
		"	float UnitsPerEm = GeometryInput[0].UnitsPerEm;"
		"	float Scale = GeometryInput[0].Scale;"
		"	uint GlyphIndex = GeometryInput[0].GlyphIndex;"
		"	vec4 Color = GeometryInput[0].Color;"
		"	float U0 = Bearing.x / UnitsPerEm;"
		"	float V0 = (Bearing.y - Size.y) / UnitsPerEm;"
		"	float U1 = (Bearing.x + Size.x) / UnitsPerEm;"
		"	float V1 = Bearing.y / UnitsPerEm;"
		"	float X0 = Position.x + U0 * Scale;"
		"	float Y0 = Position.y + V0 * Scale;"
		"	float X1 = Position.x + U1 * Scale;"
		"	float Y1 = Position.y + V1 * Scale;"
		"	vec3 P0 = vec3(X0, Y0, Position.z);"
		"	vec3 P1 = vec3(X1, Y0, Position.z);"
		"	vec3 P2 = vec3(X0, Y1, Position.z);"
		"	vec3 P3 = vec3(X1, Y1, Position.z);"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P0, 1.0);"
		"	GeometryOutput.TextureCoords = vec2(U0, V0);"
		"	GeometryOutput.GlyphIndex = GlyphIndex;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P1, 1.0);"
		"	GeometryOutput.TextureCoords = vec2(U1, V0);"
		"	GeometryOutput.GlyphIndex = GlyphIndex;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P2, 1.0);"
		"	GeometryOutput.TextureCoords = vec2(U0, V1);"
		"	GeometryOutput.GlyphIndex = GlyphIndex;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	gl_Position = ProjectionMatrix * ViewMatrix * vec4(P3, 1.0);"
		"	GeometryOutput.TextureCoords = vec2(U1, V1);"
		"	GeometryOutput.GlyphIndex = GlyphIndex;"
		"	GeometryOutput.Color = Color;"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}";
	static char const sFontFragmentShader[] =
		SHADER_GL_VERSION
		"in GS_OUT {"
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
		"uniform bool EnableSuperSamplingAntiAliasing = true;"
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
		"	BaseColor = FragmentInput.Color * Alpha;"
		"}";
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Text Definition
	///////////////////////////////////////////////////////////////

	typedef struct
	{
		int unsigned GlyphVertexArray;
		int unsigned GlyphInstanceBuffer;
		int unsigned GlyphInstanceOffset;
		GlyphInstanceEntry* MappedGlyphInstanceBuffer;
	} TextCache;

	extern void Text_Begin(Font* Fnt);
	extern void Text_Draw(char const* Text, Vector3 Position, float Scale, Quaternion Rotation, Vector4 Color);
	extern void Text_DrawSimple(char const* Text, float PositionX, float PositionY, float PositionZ, float Scale, float RotationX, float RotationY, float RotationZ, float RotationW, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Text_End(Matrix4 Projection, Matrix4 View);

	extern void Text_CacheAlloc(TextCache* Cache, int unsigned NumChars);
	extern void Text_BeginCache(TextCache* Cache, Font* Fnt);
	extern void Text_PushCache(TextCache* Cache, char const* Text, Vector3 Position, Quaternion Rotation, float Scale, Vector4 Color);
	extern void Text_PushCacheSimple(TextCache* Cache, char const* Text, float PositionX, float PositionY, float PositionZ, float RotationX, float RotationY, float RotationZ, float RotationW, float Scale, float ColorR, float ColorG, float ColorB, float ColorA);
	extern void Text_EndCache(TextCache* Cache);
	extern void Text_DrawCache(TextCache* Cache, Matrix4 Projection, Matrix4 View);
	extern void Text_CacheFree(TextCache* Cache);

#ifdef FAST_GL_IMPLEMENTATION
	static Font* sCurrFont = 0;
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Texture Definition
	///////////////////////////////////////////////////////////////

	typedef enum
	{
		TEXTURE_WRAP_REPEAT = GL_REPEAT,
		TEXTURE_WRAP_MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		TEXTURE_WRAP_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		TEXTURE_WRAP_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	} TextureWrap;
	typedef enum
	{
		TEXTURE_FILTER_NEAREST = GL_NEAREST,
		TEXTURE_FILTER_LINEAR = GL_LINEAR,
		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
	} TextureFilter;
	typedef enum
	{
		TEXTURE_TYPE_UINT8 = GL_UNSIGNED_BYTE,
		TEXTURE_TYPE_REAL32 = GL_FLOAT,
		TEXTURE_TYPE_UINT24_UINT8 = GL_UNSIGNED_INT_24_8,
	} TextureType;
	typedef enum
	{
		TEXTURE_FORMAT_RGBA = GL_RGBA,
		TEXTURE_FORMAT_RGB = GL_RGB,
		TEXTURE_FORMAT_RG = GL_RG,
		TEXTURE_FORMAT_R = GL_RED,
		TEXTURE_FORMAT_DEPTH_STENCIL = GL_DEPTH_STENCIL,
	} TextureFormat;
	typedef enum
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
	typedef struct
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
	extern void Texture2D_Mount(Texture2D* Texture, int unsigned Index);
	extern void Texture2D_Update(Texture2D* Texture, bool GenerateMipMaps);
	extern void Texture2D_UpdatePixels(Texture2D* Texture, char unsigned* Pixels, bool GenerateMipMaps);
	extern char unsigned* Texture2D_CopyPixels(Texture2D* Texture);
	extern void Texture2D_Free(Texture2D* Texture);

	///////////////////////////////////////////////////////////////
	// FrameBuffer Definition
	///////////////////////////////////////////////////////////////

	typedef struct
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

	///////////////////////////////////////////////////////////////
	// BitMap Definition
	///////////////////////////////////////////////////////////////

#pragma pack(push, 1)
	typedef struct
	{
		short unsigned Type;
		int unsigned Size;
		short unsigned Reserved0;
		short unsigned Reserved1;
		int unsigned OffBits;
	} BitMapHeader;
	typedef struct
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

	///////////////////////////////////////////////////////////////
	// Primitive Definition
	///////////////////////////////////////////////////////////////

	typedef struct
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} SpriteVertex;
	typedef struct
	{
		int unsigned VertexArray;
		int unsigned VertexBuffer;
		int unsigned IndexBuffer;
	} SpriteMesh;
	typedef struct
	{
		int unsigned NumInstances;
		int unsigned VertexArray;
		int unsigned VertexBuffer;
		int unsigned InstanceBuffer;
		int unsigned IndexBuffer;
	} InstancedSprite;
	typedef struct
	{
		Matrix4 TransformMatrix;
		int unsigned AtlasIndex;
	} SpriteInstanceEntry;
	typedef struct
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} PostProcessVertex;
	typedef struct
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

	///////////////////////////////////////////////////////////////
	// SpritePlayer Definition
	///////////////////////////////////////////////////////////////

	typedef struct
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

	typedef struct
	{
		int unsigned Program;
		PostProcessMesh* Mesh;
	} PostProcessEffect;

	extern void PostProcessEffect_Alloc(PostProcessEffect* Effect, PostProcessMesh* Mesh, char const* FragmentSource);
	extern void PostProcessEffect_Begin(PostProcessEffect* Effect);
	extern void PostProcessEffect_SetColorAttachment(PostProcessEffect* Effect, Texture2D* ColorAttachment, int unsigned ColorAttachmentMountIndex);
	extern void PostProcessEffect_End(PostProcessEffect* Effect);
	extern void PostProcessEffect_Free(PostProcessEffect* Effect);

#ifdef FAST_GL_IMPLEMENTATION
	static char const sPassThroughPostProcessVertexShader[] =
		SHADER_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"} VertexOutput;"
		"void main() {"
		"	gl_Position = vec4(VertexPosition, 0.0, 1.0);"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"}";
	char const gPassThroughPostProcessFragmentShader[] =
		SHADER_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 FinalColor;"
		"layout (binding = 0) uniform sampler2D BaseColorSampler;"
		"void main() {"
		"	FinalColor = texelFetch(BaseColorSampler, ivec2(gl_FragCoord.xy), 0);"
		"}";
	char const gWeightedBlendedOrderIndependentTransparencyPostProcessFragmentShader[] =
		SHADER_GL_VERSION
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
#else
	extern char const gPassThroughPostProcessFragmentShader[];
	extern char const gWeightedBlendedOrderIndependentTransparencyPostProcessFragmentShader[];
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Histogram Definition
	///////////////////////////////////////////////////////////////

	typedef struct
	{
		Vector2 Position;
		Vector2 TextureCoords;
	} HistogramVertex;
	typedef struct
	{
		SpriteMesh* Mesh;
		float* Samples;
		int unsigned NumSamples;
		int unsigned SampleBuffer;
		int unsigned SampleIndex;
		float Scale;
		float ScaleAcc;
		float SlowValue;
		float FastValue;
		float StepSize;
	} Histogram;

	extern void Histogram_Alloc(Histogram* Histgrm, SpriteMesh* Mesh, int unsigned NumSamples, float FastValue, float SlowValue, float StepSize);
	extern void Histogram_PushSample(Histogram* Histgrm, float Sample);
	extern void Histogram_Draw(Histogram* Histgrm, Matrix4 Projection, Matrix4 View, Vector3 Position);
	extern void Histogram_DrawSimple(Histogram* Histgrm, Matrix4 Projection, Matrix4 View, float PositionX, float PositionY, float PositionZ);
	extern void Histogram_Free(Histogram* Histgrm);

#ifdef FAST_GL_IMPLEMENTATION
	static int unsigned sHistogramProgram = 0;
	static char const sHistogramVertexShader[] =
		SHADER_GL_VERSION
		"layout (location = 0) in vec2 VertexPosition;"
		"layout (location = 1) in vec2 VertexTextureCoords;"
		"out VS_OUT {"
		"	vec2 TextureCoords;"
		"} VertexOutput;"
		"uniform mat4 ProjectionMatrix;"
		"uniform mat4 ViewMatrix;"
		"uniform mat4 ModelMatrix;"
		"void main() {"
		"	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(VertexPosition, 0.0, 1.0);"
		"	VertexOutput.TextureCoords = VertexTextureCoords;"
		"}";
	static char const sHistogramFragmentShader[] =
		SHADER_GL_VERSION
		"in VS_OUT {"
		"	vec2 TextureCoords;"
		"} FragmentInput;"
		"layout (location = 0) out vec4 BaseColor;"
		"layout (std430, binding = 0) buffer HistogramSample {"
		"	float Samples[];"
		"} HistogramSamples;"
		"const vec3 SlowColor = vec3(1.0, 0.0, 0.0);"
		"const vec3 FastColor = vec3(0.0, 0.0, 1.0);"
		"uniform uint NumSamples;"
		"uniform uint CurrIndex;"
		"uniform float Scale;"
		"uniform float SlowValue;"
		"uniform float FastValue;"
		"void main() {"
		"	float X = FragmentInput.TextureCoords.x;"
		"	float LineWidth = 1.0 / float(NumSamples);"
		"	uint SampleIndex = uint(X / LineWidth);"
		"	if (SampleIndex < NumSamples) {"
		"		float Sample = HistogramSamples.Samples[(SampleIndex + CurrIndex) % NumSamples];"
		"		float Y = FragmentInput.TextureCoords.y * Scale;"
		"		if (Y <= Sample) {"
		"			float SpeedColorScale = mix(FastValue, SlowValue, Sample / Scale);"
		"			vec3 SpeedColor = mix(FastColor, SlowColor, SpeedColorScale);"
		"			BaseColor = vec4(SpeedColor, 1.0);"
		"		}"
		"		else {"
		"			BaseColor = vec4(0.0, 0.0, 0.0, 0.0);"
		"		}"
		"	}"
		"	else {"
		"		BaseColor = vec4(0.2, 0.0, 0.0, 0.0);"
		"	}"
		"}";
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
	void Memory_CheckForLeaksInternal(void)
	{
		assert(sAllocatedBytes == 0);
	}
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
	void Matrix4_Set(Matrix4 const Value, Matrix4 Result)
	{
		Result[0][0] = Value[0][0]; Result[0][1] = Value[0][1]; Result[0][2] = Value[0][2]; Result[0][3] = Value[0][3];
		Result[1][0] = Value[1][0]; Result[1][1] = Value[1][1]; Result[1][2] = Value[1][2]; Result[1][3] = Value[1][3];
		Result[2][0] = Value[2][0]; Result[2][1] = Value[2][1]; Result[2][2] = Value[2][2]; Result[2][3] = Value[2][3];
		Result[3][0] = Value[3][0]; Result[3][1] = Value[3][1]; Result[3][2] = Value[3][2]; Result[3][3] = Value[3][3];
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
	void Matrix4_GetPosition(Matrix4 const Value, Vector3 Result)
	{
		Result[0] = Value[3][0];
		Result[1] = Value[3][1];
		Result[2] = Value[3][2];
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
	void Matrix4_SetPositionSimple(float ValueX, float ValueY, float ValueZ, Matrix4 Result)
	{
		Result[3][0] = ValueX;
		Result[3][1] = ValueY;
		Result[3][2] = ValueZ;
	}
	void Matrix4_SetRotation(Quaternion const Value, Matrix4 Result)
	{
		float XX = Value[0] * Value[0];
		float YY = Value[1] * Value[1];
		float ZZ = Value[2] * Value[2];
		float XY = Value[0] * Value[1];
		float XZ = Value[0] * Value[2];
		float YZ = Value[1] * Value[2];
		float WX = Value[3] * Value[0];
		float WY = Value[3] * Value[1];
		float WZ = Value[3] * Value[2];

		Result[0][0] = 1.0F - 2.0F * (YY + ZZ);
		Result[0][1] = 2.0F * (XY - WZ);
		Result[0][2] = 2.0F * (XZ + WY);
		Result[0][3] = 0.0F;
		Result[1][0] = 2.0F * (XY + WZ);
		Result[1][1] = 1.0F - 2.0F * (XX + ZZ);
		Result[1][2] = 2.0F * (YZ - WX);
		Result[1][3] = 0.0F;
		Result[2][0] = 2.0F * (XZ - WY);
		Result[2][1] = 2.0F * (YZ + WX);
		Result[2][2] = 1.0F - 2.0F * (XX + YY);
		Result[2][3] = 0.0F;
	}
	void Matrix4_SetRotationSimple(float ValueX, float ValueY, float ValueZ, float ValueW, Matrix4 Result)
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

		Result[0][0] = 1.0F - 2.0F * (YY + ZZ);
		Result[0][1] = 2.0F * (XY - WZ);
		Result[0][2] = 2.0F * (XZ + WY);
		Result[0][3] = 0.0F;
		Result[1][0] = 2.0F * (XY + WZ);
		Result[1][1] = 1.0F - 2.0F * (XX + ZZ);
		Result[1][2] = 2.0F * (YZ - WX);
		Result[1][3] = 0.0F;
		Result[2][0] = 2.0F * (XZ - WY);
		Result[2][1] = 2.0F * (YZ + WX);
		Result[2][2] = 1.0F - 2.0F * (XX + YY);
		Result[2][3] = 0.0F;
	}
	void Matrix4_SetScale(Vector3 const Value, Matrix4 Result)
	{
		Result[0][0] = Value[0];
		Result[1][1] = Value[1];
		Result[2][2] = Value[2];
	}
	void Matrix4_SetScaleSimple(float ValueX, float ValueY, float ValueZ, Matrix4 Result)
	{
		Result[0][0] = ValueX;
		Result[1][1] = ValueY;
		Result[2][2] = ValueZ;
	}
	void Matrix4_Decompose(Matrix4 const Value, Vector3 Position, Quaternion Rotation, Vector3 Scale)
	{
		Position[0] = Value[3][0];
		Position[1] = Value[3][1];
		Position[2] = Value[3][2];

		Vector3 C0 = { Value[0][0], Value[1][0], Value[2][0] };
		Vector3 C1 = { Value[0][1], Value[1][1], Value[2][1] };
		Vector3 C2 = { Value[0][2], Value[1][2], Value[2][2] };

		Scale[0] = Vector3_Length(C0);
		Scale[1] = Vector3_Length(C1);
		Scale[2] = Vector3_Length(C2);

		Vector3 CN0 = VECTOR3_ZERO;
		Vector3 CN1 = VECTOR3_ZERO;
		Vector3 CN2 = VECTOR3_ZERO;

		Vector3_Norm(C0, CN0);
		Vector3_Norm(C1, CN1);
		Vector3_Norm(C2, CN2);

		float Trace = CN0[0] + CN1[1] + CN2[2];
		if (Trace > 0)
		{
			float S = 0.5F / sqrtf(Trace + 1.0F);
			Rotation[0] = (CN2[1] - CN1[2]) * S;
			Rotation[1] = (CN0[2] - CN2[0]) * S;
			Rotation[2] = (CN1[0] - CN0[1]) * S;
			Rotation[3] = 0.25F / S;
		}
		else
		{
			if ((CN0[0] > CN1[1]) && (CN0[0] > CN2[2]))
			{
				float S = 2.0F * sqrtf(1.0F + CN0[0] - CN1[1] - CN2[2]);
				Rotation[0] = 0.25F * S;
				Rotation[1] = (CN0[1] + CN1[0]) / S;
				Rotation[2] = (CN0[2] + CN2[1]) / S;
				Rotation[3] = (CN2[1] - CN1[2]) / S;
			}
			else if (CN1[1] > CN2[2])
			{
				float S = 2.0F * sqrtf(1.0F + CN1[1] - CN0[0] - CN2[2]);
				Rotation[0] = (CN0[1] + CN1[0]) / S;
				Rotation[1] = 0.25F * S;
				Rotation[2] = (CN1[2] + CN2[1]) / S;
				Rotation[3] = (CN0[2] - CN2[0]) / S;
			}
			else
			{
				float S = 2.0F * sqrtf(1.0F + CN2[2] - CN0[0] - CN1[1]);
				Rotation[0] = (CN0[2] + CN2[0]) / S;
				Rotation[1] = (CN1[2] + CN2[1]) / S;
				Rotation[2] = 0.25F * S;
				Rotation[3] = (CN1[0] - CN0[1]) / S;
			}
		}
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

		Result[0][0] = (A00 * B00) + (A10 * B01) + (A20 * B02) + (A30 * B03);
		Result[0][1] = (A01 * B00) + (A11 * B01) + (A21 * B02) + (A31 * B03);
		Result[0][2] = (A02 * B00) + (A12 * B01) + (A22 * B02) + (A32 * B03);
		Result[0][3] = (A03 * B00) + (A13 * B01) + (A23 * B02) + (A33 * B03);
		Result[1][0] = (A00 * B10) + (A10 * B11) + (A20 * B12) + (A30 * B13);
		Result[1][1] = (A01 * B10) + (A11 * B11) + (A21 * B12) + (A31 * B13);
		Result[1][2] = (A02 * B10) + (A12 * B11) + (A22 * B12) + (A32 * B13);
		Result[1][3] = (A03 * B10) + (A13 * B11) + (A23 * B12) + (A33 * B13);
		Result[2][0] = (A00 * B20) + (A10 * B21) + (A20 * B22) + (A30 * B23);
		Result[2][1] = (A01 * B20) + (A11 * B21) + (A21 * B22) + (A31 * B23);
		Result[2][2] = (A02 * B20) + (A12 * B21) + (A22 * B22) + (A32 * B23);
		Result[2][3] = (A03 * B20) + (A13 * B21) + (A23 * B22) + (A33 * B23);
		Result[3][0] = (A00 * B30) + (A10 * B31) + (A20 * B32) + (A30 * B33);
		Result[3][1] = (A01 * B30) + (A11 * B31) + (A21 * B32) + (A31 * B33);
		Result[3][2] = (A02 * B30) + (A12 * B31) + (A22 * B32) + (A32 * B33);
		Result[3][3] = (A03 * B30) + (A13 * B31) + (A23 * B32) + (A33 * B33);
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
	// Vector Definition
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Vector_Alloc(Vector* Vtor, long long unsigned ValueSize)
	{
		memset(Vtor, 0, sizeof(Vector));
		Vtor->Buffer = (char unsigned*)Memory_Alloc(ValueSize * VECTOR_INITIAL_CAPACITY, 0);
		Vtor->ValueSize = ValueSize;
		Vtor->BufferSize = ValueSize * VECTOR_INITIAL_CAPACITY;
		Vtor->BufferNum = VECTOR_INITIAL_CAPACITY;
		Vtor->BufferIndex = 0;
		Vtor->BufferOffset = 0;
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
		Map->Table = (HashMapPair**)Memory_Alloc(HASH_MAP_INITIAL_CAPACITY * sizeof(HashMapPair*), 0);
		Map->TableSize = HASH_MAP_INITIAL_CAPACITY;
		Map->TableCount = 0;
		for (long long unsigned TableIndex = 0; TableIndex < HASH_MAP_INITIAL_CAPACITY; TableIndex++)
		{
			Map->Table[TableIndex] = 0;
		}
	}
	void HashMap_Insert(HashMap* Map, void const* Key, long long unsigned KeySize, void const* Value, long long unsigned KeyValue)
	{
		if ((((float)(Map->TableCount + 1U)) / (float)Map->TableSize) > HASH_MAP_LOAD_FACTOR)
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
		if ((((float)(Map->TableCount + 1U)) / (float)Map->TableSize) > HASH_MAP_LOAD_FACTOR)
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
		long long unsigned Hash = HASH_MAP_INITIAL_HASH;
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
	void FileSystem_ReadBinary(char** Buffer, int unsigned* BufferSize, char const* FilePath)
	{
		FILE* File = 0;
		fopen_s(&File, FilePath, "rb");
		fseek(File, 0, SEEK_END);
		(*BufferSize) = (int unsigned)ftell(File);
		(*Buffer) = (char*)Memory_Alloc((*BufferSize) * sizeof(char), 0);
		fseek(File, 0, SEEK_SET);
		fread((*Buffer), sizeof(char), (*BufferSize), File);
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
		fread(&Value, sizeof(long long), 1, File);
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
	void Timer_Alloc(Timer* Timr)
	{
		memset(Timr, 0, sizeof(Timer));
		LARGE_INTEGER Frequency = { 0 };
		QueryPerformanceFrequency(&Frequency);
		Timr->Frequency = (double)Frequency.QuadPart;
		Timr->StartMicroSeconds = 0.0;
		Timr->EndMicroSeconds = 0.0;
		Timr->ElapsedMicroSeconds = 0.0;
	}
	void Timer_BeginMeasure(Timer* Timr)
	{
		LARGE_INTEGER StartMicroSeconds = { 0 };
		QueryPerformanceCounter(&StartMicroSeconds);
		Timr->StartMicroSeconds = (double)StartMicroSeconds.QuadPart;
	}
	void Timer_EndMeasure(Timer* Timr)
	{
		LARGE_INTEGER EndMicroSeconds = { 0 };
		QueryPerformanceCounter(&EndMicroSeconds);
		Timr->EndMicroSeconds = (double)EndMicroSeconds.QuadPart;
		Timr->ElapsedMicroSeconds = (Timr->EndMicroSeconds - Timr->StartMicroSeconds) / Timr->Frequency;
	}
	double Timer_ElapsedNanoSeconds(Timer* Timr)
	{
		return Timr->ElapsedMicroSeconds / 1000.0;
	}
	double Timer_ElapsedMicroSeconds(Timer* Timr)
	{
		return Timr->ElapsedMicroSeconds;
	}
	double Timer_ElapsedMilliSeconds(Timer* Timr)
	{
		return Timr->ElapsedMicroSeconds * 1000.0;
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Transform Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Transform_Alloc(Transform* Trans)
	{
		memset(Trans, 0, sizeof(Transform));

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

		Rotation[0] = RAD_TO_DEG(Rotation[0]);
		Rotation[1] = RAD_TO_DEG(Rotation[1]);
		Rotation[2] = RAD_TO_DEG(Rotation[2]);
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

		Rotation[0] = RAD_TO_DEG(Rotation[0]);
		Rotation[1] = RAD_TO_DEG(Rotation[1]);
		Rotation[2] = RAD_TO_DEG(Rotation[2]);
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
		float Pitch = DEG_TO_RAD(Rotation[0]);
		float Yaw = DEG_TO_RAD(Rotation[1]);
		float Roll = DEG_TO_RAD(Rotation[2]);

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
		float Pitch = DEG_TO_RAD(Rotation[0]);
		float Yaw = DEG_TO_RAD(Rotation[1]);
		float Roll = DEG_TO_RAD(Rotation[2]);

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
	void Controller_FirstPersonAlloc(FirstPersonController* Controller)
	{
		memset(Controller, 0, sizeof(FirstPersonController));

		Transform_Alloc(&Controller->Transform);
		Transform_SetPositionSimple(&Controller->Transform, 0.0F, 0.0F, -10.0F);
		Controller->KeyboardMovementSpeed = 5.0F;
		Controller->MouseMovementSpeed = 10.0F;
		Controller->MouseRotationSpeed = 10.0F;
		Controller->RollSpeed = 0.8F;
		Controller->MouseDrag = 50.0F;
		Vector2_Zero(Controller->MousePositionStart);
		Vector2_Zero(Controller->MousePositionEnd);
	}
	void Controller_OrbitAlloc(OrbitController* Controller)
	{
		memset(Controller, 0, sizeof(OrbitController));

		Transform_Alloc(&Controller->Transform);
		Transform_SetPositionSimple(&Controller->Transform, 0.0F, 0.0F, -10.0F);
		Controller->KeyboardMovementSpeed = 5.0F;
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
			Controller->MousePositionStart[0] = (float)Window_GetMousePositionX();
			Controller->MousePositionStart[1] = (float)Window_GetMousePositionY();
		}

		if (Window_IsMouseKeyHeld(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionEnd[0] = (float)Window_GetMousePositionX();
			Controller->MousePositionEnd[1] = (float)Window_GetMousePositionY();

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
			Controller->MousePositionStart[0] = (float)Window_GetMousePositionX();
			Controller->MousePositionStart[1] = (float)Window_GetMousePositionY();
		}

		if (Window_IsMouseKeyHeld(MOUSE_KEY_RIGHT))
		{
			Controller->MousePositionEnd[0] = (float)Window_GetMousePositionX();
			Controller->MousePositionEnd[1] = (float)Window_GetMousePositionY();

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
	void Controller_ComputeFirstPersonViewMatrix(FirstPersonController* Controller, Matrix4 View)
	{
		Transform* Trans = &Controller->Transform;

		Vector3 Eye = { Trans->WorldPosition[0], Trans->WorldPosition[1], Trans->WorldPosition[2] };
		Vector3 Center = { Trans->WorldPosition[0] + Trans->LocalForward[0], Trans->WorldPosition[1] + Trans->LocalForward[1], Trans->WorldPosition[2] + Trans->LocalForward[2] };
		Vector3 Up = { Trans->LocalUp[0], Trans->LocalUp[1], Trans->LocalUp[2] };

		Matrix4_LookAt(Eye, Center, Up, View);
	}
	void Controller_ComputeOrbitViewMatrix(OrbitController* Controller, Matrix4 View)
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
	}
	void Shader_Bind(int unsigned Program)
	{
		glUseProgram(Program);
	}
	void Shader_SetUniformInt32(int unsigned Program, char const* UniformName, int Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniform1i(Location, Value);
	}
	void Shader_SetUniformUInt32(int unsigned Program, char const* UniformName, int unsigned Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniform1ui(Location, Value);
	}
	void Shader_SetUniformReal32(int unsigned Program, char const* UniformName, float Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniform1f(Location, Value);
	}
	void Shader_SetUniformVector2(int unsigned Program, char const* UniformName, Vector2 Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniform2fv(Location, 1, &Value[0]);
	}
	void Shader_SetUniformVector3(int unsigned Program, char const* UniformName, Vector3 Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniform3fv(Location, 1, &Value[0]);
	}
	void Shader_SetUniformVector4(int unsigned Program, char const* UniformName, Vector4 Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniform4fv(Location, 1, &Value[0]);
	}
	void Shader_SetUniformMatrix4(int unsigned Program, char const* UniformName, Matrix4 Value)
	{
		int Location = glGetUniformLocation(Program, UniformName);
		assert(Location >= 0);
		glUniformMatrix4fv(Location, 1, 0, &Value[0][0]);
	}
	void Shader_ExecuteCompute(int unsigned NumGroupsX, int unsigned NumGroupsY, int unsigned NumGroupsZ)
	{
		glDispatchCompute(NumGroupsX, NumGroupsY, NumGroupsZ);
	}
	void Shader_Free(int unsigned Program)
	{
		glDeleteProgram(Program);
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
#endif // FAST_GL_DEBUG
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// VertexArray Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void VertexArray_Alloc(int unsigned* VertexArray)
	{
		glGenVertexArrays(1, VertexArray);
	}
	void VertexArray_Bind(int unsigned VertexArray)
	{
		glBindVertexArray(VertexArray);
	}
	void VertexArray_UnBind(void)
	{
		glBindVertexArray(0);
	}
	void VertexArray_Free(int unsigned VertexArray)
	{
		glDeleteVertexArrays(1, &VertexArray);
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Buffer Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Buffer_VertexAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, (*Buffer));
		glBufferData(GL_ARRAY_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Buffer_IndexAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*Buffer));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Buffer_UniformAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, (*Buffer));
		glBufferData(GL_UNIFORM_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	void Buffer_StorageAlloc(int unsigned* Buffer, int unsigned Size, int unsigned Usage)
	{
		glGenBuffers(1, Buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, (*Buffer));
		glBufferData(GL_SHADER_STORAGE_BUFFER, Size, 0, Usage);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
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
	void Buffer_VertexGetData(void* Data, int unsigned Size)
	{
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, Size, Data);
	}
	void Buffer_IndexGetData(void* Data, int unsigned Size)
	{
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Size, Data);
	}
	void Buffer_UniformGetData(void* Data, int unsigned Size)
	{
		glGetBufferSubData(GL_UNIFORM_BUFFER, 0, Size, Data);
	}
	void Buffer_StorageGetData(void* Data, int unsigned Size)
	{
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, Size, Data);
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
	void Buffer_VertexGetSubData(void* Data, int unsigned Offset, int unsigned Size)
	{
		glGetBufferSubData(GL_ARRAY_BUFFER, Offset, Size, Data);
	}
	void Buffer_IndexGetSubData(void* Data, int unsigned Offset, int unsigned Size)
	{
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, Offset, Size, Data);
	}
	void Buffer_UniformGetSubData(void* Data, int unsigned Offset, int unsigned Size)
	{
		glGetBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, Data);
	}
	void Buffer_StorageGetSubData(void* Data, int unsigned Offset, int unsigned Size)
	{
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, Offset, Size, Data);
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
		sNumPoints = NumPoints;
		sNumLines = NumLines;
		sNumQuads = NumQuads;

		Shader_VertexGeometryFragmentAlloc(&sPointProgram, sPointVertexShader, sPointGeometryShader, sPointFragmentShader);
		Shader_VertexGeometryFragmentAlloc(&sLineProgram, sLineVertexShader, sLineGeometryShader, sLineFragmentShader);
		Shader_VertexGeometryFragmentAlloc(&sQuadProgram, sQuadVertexShader, sQuadGeometryShader, sQuadFragmentShader);

		glGenVertexArrays(1, &sPointVertexArray);
		glGenBuffers(1, &sPointInstanceBuffer);
		glBindVertexArray(sPointVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(PointInstanceEntry), ((void*)(OFFSET_OF(PointInstanceEntry, Position))));
		glVertexAttribPointer(1, 1, GL_FLOAT, 0, sizeof(PointInstanceEntry), ((void*)(OFFSET_OF(PointInstanceEntry, Radius))));
		glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(PointInstanceEntry), ((void*)(OFFSET_OF(PointInstanceEntry, Color))));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(PointInstanceEntry), ((void*)(OFFSET_OF(PointInstanceEntry, Direction))));
		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(PointInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &sLineVertexArray);
		glGenBuffers(1, &sLineVertexBuffer);
		glGenBuffers(1, &sLineIndexBuffer);
		glBindVertexArray(sLineVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(LineVertex), ((void*)(OFFSET_OF(LineVertex, Position))));
		glVertexAttribPointer(1, 1, GL_FLOAT, 0, sizeof(LineVertex), ((void*)(OFFSET_OF(LineVertex, Thickness))));
		glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(LineVertex), ((void*)(OFFSET_OF(LineVertex, Color))));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(LineVertex), ((void*)(OFFSET_OF(LineVertex, Direction))));
		glBufferData(GL_ARRAY_BUFFER, NumLines * 2 * sizeof(LineVertex), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumLines * 2 * sizeof(int unsigned), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &sQuadVertexArray);
		glGenBuffers(1, &sQuadInstanceBuffer);
		glBindVertexArray(sQuadVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, sQuadInstanceBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(QuadInstanceEntry), ((void*)(OFFSET_OF(QuadInstanceEntry, Position))));
		glVertexAttribPointer(1, 3, GL_FLOAT, 0, sizeof(QuadInstanceEntry), ((void*)(OFFSET_OF(QuadInstanceEntry, Size))));
		glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(QuadInstanceEntry), ((void*)(OFFSET_OF(QuadInstanceEntry, Color))));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(QuadInstanceEntry), ((void*)(OFFSET_OF(QuadInstanceEntry, Direction))));
		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glBufferData(GL_ARRAY_BUFFER, NumQuads * sizeof(QuadInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Gizmo_BeginPoints(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sPointInstanceBuffer);
		sMappedPointInstanceBuffer = (PointInstanceEntry*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		sPointInstanceOffset = 0;
	}
	void Gizmo_DrawPoint(GizmoDir Direction, Vector3 Position, float Radius, Vector4 Color)
	{
		sMappedPointInstanceBuffer[sPointInstanceOffset].Position[0] = Position[0];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Position[1] = Position[1];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Position[2] = Position[2];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Radius = Radius;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[0] = Color[0];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[1] = Color[1];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[2] = Color[2];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[3] = Color[3];
		sMappedPointInstanceBuffer[sPointInstanceOffset].Direction = (int unsigned)Direction;

		sPointInstanceOffset += 1;
	}
	void Gizmo_DrawPointSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float Radius, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedPointInstanceBuffer[sPointInstanceOffset].Position[0] = PositionX;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Position[1] = PositionY;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Position[2] = PositionZ;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Radius = Radius;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[0] = ColorR;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[1] = ColorG;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[2] = ColorB;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Color[3] = ColorA;
		sMappedPointInstanceBuffer[sPointInstanceOffset].Direction = (int unsigned)Direction;

		sPointInstanceOffset += 1;
	}
	void Gizmo_EndPoints(Matrix4 Projection, Matrix4 View)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Shader_Bind(sPointProgram);
		Shader_SetUniformMatrix4(sPointProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sPointProgram, "ViewMatrix", View);
		glBindVertexArray(sPointVertexArray);
		glDrawArraysInstanced(GL_POINTS, 0, 1, (int)sPointInstanceOffset);
		glBindVertexArray(0);
	}
	void Gizmo_BeginLines(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sLineIndexBuffer);
		sMappedLineVertexBuffer = (LineVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		sMappedLineIndexBuffer = (int unsigned*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		sLineVertexOffset = 0;
		sLineIndexOffset = 0;
	}
	void Gizmo_DrawLine(GizmoDir Direction, Vector3 From, Vector3 To, float Thickness, Vector4 Color)
	{
		sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = From[0];
		sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = From[1];
		sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = From[2];
		sMappedLineVertexBuffer[sLineVertexOffset].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = To[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = To[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = To[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Direction = Direction;

		sMappedLineIndexBuffer[sLineIndexOffset] = sLineVertexOffset;
		sMappedLineIndexBuffer[sLineIndexOffset + 1] = sLineVertexOffset + 1;

		sLineVertexOffset += 2;
		sLineIndexOffset += 2;
	}
	void Gizmo_DrawLineSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = FromX;
		sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = FromY;
		sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = FromZ;
		sMappedLineVertexBuffer[sLineVertexOffset].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = ToX;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = ToY;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = ToZ;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Direction = Direction;

		sMappedLineIndexBuffer[sLineIndexOffset] = sLineVertexOffset;
		sMappedLineIndexBuffer[sLineIndexOffset + 1] = sLineVertexOffset + 1;

		sLineVertexOffset += 2;
		sLineIndexOffset += 2;
	}
	void Gizmo_DrawLineRect(GizmoDir Direction, Vector3 Position, Vector3 Size, float Thickness, Vector4 Color)
	{
		switch (Direction)
		{
		case GIZMO_DIR_XY:
		{
			sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[2] = Position[2];

			break;
		}
		case GIZMO_DIR_XZ:
		{
			sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[0] = Position[0] + Size[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[2] = Position[2];

			break;
		}
		case GIZMO_DIR_ZY:
		{
			sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[2] = Position[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[1] = Position[1] + Size[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[2] = Position[2] + Size[2];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[0] = Position[0];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[1] = Position[1];
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[2] = Position[2];

			break;
		}
		}

		sMappedLineVertexBuffer[sLineVertexOffset].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[0] = Color[0];
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[1] = Color[1];
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[2] = Color[2];
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[3] = Color[3];
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Direction = Direction;

		sMappedLineIndexBuffer[sLineIndexOffset] = sLineVertexOffset;
		sMappedLineIndexBuffer[sLineIndexOffset + 1] = sLineVertexOffset + 1;
		sMappedLineIndexBuffer[sLineIndexOffset + 2] = sLineVertexOffset + 2;
		sMappedLineIndexBuffer[sLineIndexOffset + 3] = sLineVertexOffset + 3;
		sMappedLineIndexBuffer[sLineIndexOffset + 4] = sLineVertexOffset + 4;
		sMappedLineIndexBuffer[sLineIndexOffset + 5] = sLineVertexOffset + 5;
		sMappedLineIndexBuffer[sLineIndexOffset + 6] = sLineVertexOffset + 6;
		sMappedLineIndexBuffer[sLineIndexOffset + 7] = sLineVertexOffset;

		sLineVertexOffset += 8;
		sLineIndexOffset += 8;
	}
	void Gizmo_DrawLineRectSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		switch (Direction)
		{
		case GIZMO_DIR_XY:
		{
			sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[2] = PositionZ;

			break;
		}
		case GIZMO_DIR_XZ:
		{
			sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[0] = PositionX + SizeX;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[2] = PositionZ;

			break;
		}
		case GIZMO_DIR_ZY:
		{
			sMappedLineVertexBuffer[sLineVertexOffset].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 1].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 2].Position[2] = PositionZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 3].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[1] = PositionY + SizeY;
			sMappedLineVertexBuffer[sLineVertexOffset + 4].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 5].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 6].Position[2] = PositionZ + SizeZ;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[0] = PositionX;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[1] = PositionY;
			sMappedLineVertexBuffer[sLineVertexOffset + 7].Position[2] = PositionZ;

			break;
		}
		}

		sMappedLineVertexBuffer[sLineVertexOffset].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 1].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 2].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 3].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 4].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 5].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 6].Direction = Direction;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Thickness = Thickness;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[0] = ColorR;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[1] = ColorG;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[2] = ColorB;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Color[3] = ColorA;
		sMappedLineVertexBuffer[sLineVertexOffset + 7].Direction = Direction;

		sMappedLineIndexBuffer[sLineIndexOffset] = sLineVertexOffset;
		sMappedLineIndexBuffer[sLineIndexOffset + 1] = sLineVertexOffset + 1;
		sMappedLineIndexBuffer[sLineIndexOffset + 2] = sLineVertexOffset + 2;
		sMappedLineIndexBuffer[sLineIndexOffset + 3] = sLineVertexOffset + 3;
		sMappedLineIndexBuffer[sLineIndexOffset + 4] = sLineVertexOffset + 4;
		sMappedLineIndexBuffer[sLineIndexOffset + 5] = sLineVertexOffset + 5;
		sMappedLineIndexBuffer[sLineIndexOffset + 6] = sLineVertexOffset + 6;
		sMappedLineIndexBuffer[sLineIndexOffset + 7] = sLineVertexOffset;

		sLineVertexOffset += 8;
		sLineIndexOffset += 8;
	}
	void Gizmo_DrawLineCircle(GizmoDir Direction, Vector3 Position, int unsigned NumSegments, float Radius, float Thickness, Vector4 Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned ElementIndex = 0;

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = 2.0F * PI * (float)SegmentIndex / (float)NumSegments;
			float T1 = 2.0F * PI * (float)(SegmentIndex + 1) / (float)NumSegments;

			float Theta0 = Radius * cosf(T0);
			float Phi0 = Radius * sinf(T0);

			float Theta1 = Radius * cosf(T1);
			float Phi1 = Radius * sinf(T1);

			switch (Direction)
			{
			case GIZMO_DIR_XY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[0] = Position[0] + Theta0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[1] = Position[1] + Phi0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[2] = Position[2];
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[0] = Position[0] + Theta1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[1] = Position[1] + Phi1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[2] = Position[2];

				break;
			}
			case GIZMO_DIR_XZ:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[0] = Position[0] + Theta0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[2] = Position[2] + Phi0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[0] = Position[0] + Theta1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[2] = Position[2] + Phi1;

				break;
			}
			case GIZMO_DIR_ZY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[1] = Position[1] + Phi0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[2] = Position[2] + Theta0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[1] = Position[1] + Phi1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[2] = Position[2] + Theta1;

				break;
			}
			}

			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex] = sLineVertexOffset + SegmentIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex + 1] = sLineVertexOffset + SegmentIndex + 1;

			ElementIndex += 2;
		}

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineCircleSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumSegments, float Radius, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned ElementIndex = 0;

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = 2.0F * PI * (float)SegmentIndex / (float)NumSegments;
			float T1 = 2.0F * PI * (float)(SegmentIndex + 1) / (float)NumSegments;

			float Theta0 = Radius * cosf(T0);
			float Phi0 = Radius * sinf(T0);

			float Theta1 = Radius * cosf(T1);
			float Phi1 = Radius * sinf(T1);

			switch (Direction)
			{
			case GIZMO_DIR_XY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[0] = PositionX + Theta0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[1] = PositionY + Phi0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[2] = PositionZ;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[0] = PositionX + Theta1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[1] = PositionY + Phi1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[2] = PositionZ;

				break;
			}
			case GIZMO_DIR_XZ:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[0] = PositionX + Theta0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[2] = PositionZ + Phi0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[0] = PositionX + Theta1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[2] = PositionZ + Phi1;

				break;
			}
			case GIZMO_DIR_ZY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[1] = PositionY + Phi0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Position[2] = PositionZ + Theta0;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[1] = PositionY + Phi1;
				sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Position[2] = PositionZ + Theta1;

				break;
			}
			}


			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + ElementIndex + 1].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex] = sLineVertexOffset + SegmentIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex + 1] = sLineVertexOffset + SegmentIndex + 1;

			ElementIndex += 2;
		}

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineGrid(GizmoDir Direction, Vector3 Position, int unsigned NumLines, float Scale, float Thickness, Vector4 Color)
	{
		int unsigned NumLines4 = NumLines * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)NumLines * Scale) / (float)NumLines;
		float Size = (float)(NumLines)*Scale;

		for (int unsigned LineIndex = 0; LineIndex <= NumLines; LineIndex++)
		{
			float GridOffset = (float)LineIndex * SizeStep;

			switch (Direction)
			{
			case GIZMO_DIR_XY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[0] = Position[0] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[2] = Position[2];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[0] = Position[0] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[1] = Position[1] + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[2] = Position[2];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[1] = Position[1] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[2] = Position[2];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[0] = Position[0] + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[1] = Position[1] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[2] = Position[2];

				break;
			}
			case GIZMO_DIR_XZ:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[0] = Position[0] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[2] = Position[2];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[0] = Position[0] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[2] = Position[2] + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[2] = Position[2] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[0] = Position[0] + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[2] = Position[2] + GridOffset;

				break;
			}
			case GIZMO_DIR_ZY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[1] = Position[1] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[2] = Position[2];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[1] = Position[1] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[2] = Position[2] + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[1] = Position[1];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[2] = Position[2] + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[0] = Position[0];
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[1] = Position[1] + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[2] = Position[2] + GridOffset;

				break;
			}
			}

			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex] = sLineVertexOffset + SegmentIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex + 1] = sLineVertexOffset + SegmentIndex + 1;
			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex + 2] = sLineVertexOffset + SegmentIndex + 2;
			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex + 3] = sLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		sLineVertexOffset += NumLines4 + 4;
		sLineIndexOffset += NumLines4 + 4;
	}
	void Gizmo_DrawLineGridSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, int unsigned NumLines, float Scale, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		int unsigned NumLines4 = NumLines * 4;
		int unsigned SegmentIndex = 0;
		float SizeStep = ((float)NumLines * Scale) / (float)NumLines;
		float Size = (float)(NumLines)*Scale;

		for (int unsigned LineIndex = 0; LineIndex <= NumLines; LineIndex++)
		{
			float GridOffset = (float)LineIndex * SizeStep;

			switch (Direction)
			{
			case GIZMO_DIR_XY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[0] = PositionX + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[2] = PositionZ;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[0] = PositionX + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[1] = PositionY + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[2] = PositionZ;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[1] = PositionY + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[2] = PositionZ;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[0] = PositionX + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[1] = PositionY + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[2] = PositionZ;

				break;
			}
			case GIZMO_DIR_XZ:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[0] = PositionX + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[2] = PositionZ;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[0] = PositionX + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[2] = PositionZ + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[2] = PositionZ + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[0] = PositionX + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[2] = PositionZ + GridOffset;

				break;
			}
			case GIZMO_DIR_ZY:
			{
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[1] = PositionY + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Position[2] = PositionZ;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[1] = PositionY + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Position[2] = PositionZ + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[1] = PositionY;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Position[2] = PositionZ + GridOffset;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[0] = PositionX;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[1] = PositionY + Size;
				sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Position[2] = PositionZ + GridOffset;

				break;
			}
			}

			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 1].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 2].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + SegmentIndex + 3].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex] = sLineVertexOffset + SegmentIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex + 1] = sLineVertexOffset + SegmentIndex + 1;
			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex + 2] = sLineVertexOffset + SegmentIndex + 2;
			sMappedLineIndexBuffer[sLineIndexOffset + SegmentIndex + 3] = sLineVertexOffset + SegmentIndex + 3;

			SegmentIndex += 4;
		}

		sLineVertexOffset += NumLines4 + 4;
		sLineIndexOffset += NumLines4 + 4;
	}
	void Gizmo_DrawLineBezierQuadratic(GizmoDir Direction, Vector3 From, Vector3 Ctrl, Vector3 To, int unsigned NumSegments, float Thickness, Vector4 Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float Theta0 = powf(1.0F - T0, 2.0F) * From[0] + 2.0F * (1.0F - T0) * T0 * Ctrl[0] + T0 * T0 * To[0];
			float Phi0 = powf(1.0F - T0, 2.0F) * From[1] + 2.0F * (1.0F - T0) * T0 * Ctrl[1] + T0 * T0 * To[1];
			float Chi0 = powf(1.0F - T0, 2.0F) * From[2] + 2.0F * (1.0F - T0) * T0 * Ctrl[2] + T0 * T0 * To[2];

			float Theta1 = powf(1.0F - T1, 2.0F) * From[0] + 2.0F * (1.0F - T1) * T1 * Ctrl[0] + T1 * T1 * To[0];
			float Phi1 = powf(1.0F - T1, 2.0F) * From[1] + 2.0F * (1.0F - T1) * T1 * Ctrl[1] + T1 * T1 * To[1];
			float Chi1 = powf(1.0F - T1, 2.0F) * From[2] + 2.0F * (1.0F - T1) * T1 * Ctrl[2] + T1 * T1 * To[2];

			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[0] = Theta0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[1] = Phi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[2] = Chi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[0] = Theta1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[1] = Phi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[2] = Chi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex] = sLineVertexOffset + VertexIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineBezierQuadraticSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlX, float CtrlY, float CtrlZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float Theta0 = powf(1.0F - T0, 2.0F) * FromX + 2.0F * (1.0F - T0) * T0 * CtrlX + T0 * T0 * ToX;
			float Phi0 = powf(1.0F - T0, 2.0F) * FromY + 2.0F * (1.0F - T0) * T0 * CtrlY + T0 * T0 * ToY;
			float Chi0 = powf(1.0F - T0, 2.0F) * FromZ + 2.0F * (1.0F - T0) * T0 * CtrlZ + T0 * T0 * ToZ;

			float Theta1 = powf(1.0F - T1, 2.0F) * FromX + 2.0F * (1.0F - T1) * T1 * CtrlX + T1 * T1 * ToX;
			float Phi1 = powf(1.0F - T1, 2.0F) * FromY + 2.0F * (1.0F - T1) * T1 * CtrlY + T1 * T1 * ToY;
			float Chi1 = powf(1.0F - T1, 2.0F) * FromZ + 2.0F * (1.0F - T1) * T1 * CtrlZ + T1 * T1 * ToZ;

			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[0] = Theta0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[1] = Phi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[2] = Chi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[0] = Theta1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[1] = Phi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[2] = Chi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex] = sLineVertexOffset + VertexIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineBezierCubic(GizmoDir Direction, Vector3 From, Vector3 CtrlA, Vector3 CtrlB, Vector3 To, int unsigned NumSegments, float Thickness, Vector4 Color)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float Theta0 = powf(1.0F - T0, 3.0F) * From[0] + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlA[0] + 3.0F * (1.0F - T0) * T0 * T0 * CtrlB[0] + T0 * T0 * T0 * To[0];
			float Phi0 = powf(1.0F - T0, 3.0F) * From[1] + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlA[1] + 3.0F * (1.0F - T0) * T0 * T0 * CtrlB[1] + T0 * T0 * T0 * To[1];
			float Chi0 = powf(1.0F - T0, 3.0F) * From[2] + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlA[2] + 3.0F * (1.0F - T0) * T0 * T0 * CtrlB[2] + T0 * T0 * T0 * To[2];

			float Theta1 = powf(1.0F - T1, 3.0F) * From[0] + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlA[0] + 3.0F * (1.0F - T1) * T1 * T1 * CtrlB[0] + T1 * T1 * T1 * To[0];
			float Phi1 = powf(1.0F - T1, 3.0F) * From[1] + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlA[1] + 3.0F * (1.0F - T1) * T1 * T1 * CtrlB[1] + T1 * T1 * T1 * To[1];
			float Chi1 = powf(1.0F - T1, 3.0F) * From[2] + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlA[2] + 3.0F * (1.0F - T1) * T1 * T1 * CtrlB[2] + T1 * T1 * T1 * To[2];

			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[0] = Theta0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[1] = Phi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[2] = Chi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[0] = Theta1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[1] = Phi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[2] = Chi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[0] = Color[0];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[1] = Color[1];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[2] = Color[2];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[3] = Color[3];
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex] = sLineVertexOffset + VertexIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_DrawLineBezierCubicSimple(GizmoDir Direction, float FromX, float FromY, float FromZ, float CtrlAX, float CtrlAY, float CtrlAZ, float CtrlBX, float CtrlBY, float CtrlBZ, float ToX, float ToY, float ToZ, int unsigned NumSegments, float Thickness, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		int unsigned NumSegments2 = NumSegments * 2;
		int unsigned VertexIndex = 0;
		int unsigned ElementIndex = 0;

		for (int unsigned SegmentIndex = 0; SegmentIndex < NumSegments; SegmentIndex++)
		{
			float T0 = (float)SegmentIndex / (float)NumSegments;
			float T1 = (float)(SegmentIndex + 1) / (float)NumSegments;

			float Theta0 = powf(1.0F - T0, 3.0F) * FromX + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlAX + 3.0F * (1.0F - T0) * T0 * T0 * CtrlBX + T0 * T0 * T0 * ToX;
			float Phi0 = powf(1.0F - T0, 3.0F) * FromY + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlAY + 3.0F * (1.0F - T0) * T0 * T0 * CtrlBY + T0 * T0 * T0 * ToY;
			float Chi0 = powf(1.0F - T0, 3.0F) * FromZ + 3.0F * powf(1.0F - T0, 2.0F) * T0 * CtrlAZ + 3.0F * (1.0F - T0) * T0 * T0 * CtrlBZ + T0 * T0 * T0 * ToZ;

			float Theta1 = powf(1.0F - T1, 3.0F) * FromX + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlAX + 3.0F * (1.0F - T1) * T1 * T1 * CtrlBX + T1 * T1 * T1 * ToX;
			float Phi1 = powf(1.0F - T1, 3.0F) * FromY + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlAY + 3.0F * (1.0F - T1) * T1 * T1 * CtrlBY + T1 * T1 * T1 * ToY;
			float Chi1 = powf(1.0F - T1, 3.0F) * FromZ + 3.0F * powf(1.0F - T1, 2.0F) * T1 * CtrlAZ + 3.0F * (1.0F - T1) * T1 * T1 * CtrlBZ + T1 * T1 * T1 * ToZ;

			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[0] = Theta0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[1] = Phi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Position[2] = Chi0;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex].Direction = Direction;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[0] = Theta1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[1] = Phi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Position[2] = Chi1;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Thickness = Thickness;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[0] = ColorR;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[1] = ColorG;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[2] = ColorB;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Color[3] = ColorA;
			sMappedLineVertexBuffer[sLineVertexOffset + VertexIndex + 1].Direction = Direction;

			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex] = sLineVertexOffset + VertexIndex;
			sMappedLineIndexBuffer[sLineIndexOffset + ElementIndex + 1] = sLineVertexOffset + VertexIndex + 1;

			VertexIndex += 2;
			ElementIndex += 2;
		}

		sLineVertexOffset += NumSegments2;
		sLineIndexOffset += NumSegments2;
	}
	void Gizmo_EndLines(Matrix4 Projection, Matrix4 View)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		Shader_Bind(sLineProgram);
		Shader_SetUniformMatrix4(sLineProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sLineProgram, "ViewMatrix", View);
		glBindVertexArray(sLineVertexArray);
		glDrawArrays(GL_LINES, 0, (int)sLineIndexOffset);
		glBindVertexArray(0);
	}
	void Gizmo_BeginQuads(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sQuadInstanceBuffer);
		sMappedQuadInstanceBuffer = (QuadInstanceEntry*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		sQuadInstanceOffset = 0;
	}
	void Gizmo_DrawQuad(GizmoDir Direction, Vector3 Position, Vector3 Size, Vector4 Color)
	{
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Position[0] = Position[0];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Position[1] = Position[1];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Position[2] = Position[2];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Size[0] = Size[0];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Size[1] = Size[1];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Size[2] = Size[2];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[0] = Color[0];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[1] = Color[1];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[2] = Color[2];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[3] = Color[3];
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Direction = Direction;

		sQuadInstanceOffset += 1;
	}
	void Gizmo_DrawQuadSimple(GizmoDir Direction, float PositionX, float PositionY, float PositionZ, float SizeX, float SizeY, float SizeZ, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Position[0] = PositionX;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Position[1] = PositionY;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Position[2] = PositionZ;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Size[0] = SizeX;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Size[1] = SizeY;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Size[2] = SizeZ;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[0] = ColorR;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[1] = ColorG;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[2] = ColorB;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Color[3] = ColorA;
		sMappedQuadInstanceBuffer[sQuadInstanceOffset].Direction = Direction;

		sQuadInstanceOffset += 1;
	}
	void Gizmo_EndQuads(Matrix4 Projection, Matrix4 View)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Shader_Bind(sQuadProgram);
		Shader_SetUniformMatrix4(sQuadProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sQuadProgram, "ViewMatrix", View);
		glBindVertexArray(sQuadVertexArray);
		glDrawArraysInstanced(GL_POINTS, 0, 1, (int)sQuadInstanceOffset);
		glBindVertexArray(0);
	}
	void Gizmo_Free(void)
	{
		glDeleteBuffers(1, &sPointInstanceBuffer);
		glDeleteBuffers(1, &sLineVertexBuffer);
		glDeleteBuffers(1, &sLineIndexBuffer);
		glDeleteBuffers(1, &sQuadInstanceBuffer);
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
	void Font_Alloc(Font* Fnt, int unsigned NumChars, char const* FilePath)
	{
		memset(Fnt, 0, sizeof(Font));

		FILE* File = 0;
		fopen_s(&File, FilePath, "rb");

		Fnt->OffsetTable.ScalerType = FileReader_ReadUInt32(File, true);
		Fnt->OffsetTable.NumTables = FileReader_ReadUInt16(File, true);
		Fnt->OffsetTable.SearchRange = FileReader_ReadUInt16(File, true);
		Fnt->OffsetTable.EntrySelector = FileReader_ReadUInt16(File, true);
		Fnt->OffsetTable.RangeShift = FileReader_ReadUInt16(File, true);

		for (short unsigned TableIndex = 0; TableIndex < Fnt->OffsetTable.NumTables; TableIndex++)
		{
			FontTableDirectory TableDir = { 0 };
			FileReader_ReadInt8Array(File, TableDir.Tag, 4);
			TableDir.CheckSum = FileReader_ReadUInt32(File, true);
			TableDir.Offset = FileReader_ReadUInt32(File, true);
			TableDir.Length = FileReader_ReadUInt32(File, true);

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
		}

		assert(Fnt->HeadTableDir.Offset);
		assert(Fnt->GlyfTableDir.Offset);
		assert(Fnt->LocaTableDir.Offset);
		assert(Fnt->CmapTableDir.Offset);
		assert(Fnt->MaxpTableDir.Offset);
		assert(Fnt->HheaTableDir.Offset);
		assert(Fnt->HmtxTableDir.Offset);

		fseek(File, (long)Fnt->HeadTableDir.Offset, SEEK_SET);
		Fnt->HeadTable.Version = FileReader_ReadUInt32(File, true);
		Fnt->HeadTable.FontRevision = FileReader_ReadUInt32(File, true);
		Fnt->HeadTable.CheckSumAdjustment = FileReader_ReadUInt32(File, true);
		Fnt->HeadTable.MagicNumber = FileReader_ReadUInt32(File, true);
		Fnt->HeadTable.Flags = FileReader_ReadUInt16(File, true);
		Fnt->HeadTable.UnitsPerEm = FileReader_ReadUInt16(File, true);
		Fnt->HeadTable.Created = FileReader_ReadInt64(File, true);
		Fnt->HeadTable.Modified = FileReader_ReadInt64(File, true);
		Fnt->HeadTable.MinX = FileReader_ReadInt16(File, true);
		Fnt->HeadTable.MinY = FileReader_ReadInt16(File, true);
		Fnt->HeadTable.MaxX = FileReader_ReadInt16(File, true);
		Fnt->HeadTable.MaxY = FileReader_ReadInt16(File, true);
		Fnt->HeadTable.MacStyle = FileReader_ReadUInt16(File, true);
		Fnt->HeadTable.LowestRecPPEM = FileReader_ReadUInt16(File, true);
		Fnt->HeadTable.FontDirectionHint = FileReader_ReadInt16(File, true);
		Fnt->HeadTable.IndexToLocFormat = FileReader_ReadInt16(File, true);
		Fnt->HeadTable.GlyphDataFormat = FileReader_ReadInt16(File, true);
		assert(Fnt->HeadTable.Version == 0x10000);
		assert(Fnt->HeadTable.MagicNumber == 0x5F0F3CF5);

		fseek(File, (long)Fnt->MaxpTableDir.Offset, SEEK_SET);
		Fnt->MaxpTable.Version = FileReader_ReadUInt32(File, true);
		Fnt->MaxpTable.NumGlyphs = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxPoints = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxContours = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxComponentPoints = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxComponentContours = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxZones = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxTwilightPoints = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxStorage = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxFunctionDefs = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxInstructionDefs = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxStackElements = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxSizeOfInstructions = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxComponentElements = FileReader_ReadUInt16(File, true);
		Fnt->MaxpTable.MaxComponentDepth = FileReader_ReadUInt16(File, true);
		assert(Fnt->MaxpTable.Version == 0x10000);

		fseek(File, (long)Fnt->CmapTableDir.Offset, SEEK_SET);
		Fnt->CmapTable.Version = FileReader_ReadUInt16(File, true);
		Fnt->CmapTable.NumberSubTables = FileReader_ReadUInt16(File, true);
		assert(Fnt->CmapTable.Version == 0x0);

		fseek(File, (long)Fnt->HheaTableDir.Offset, SEEK_SET);
		Fnt->HheaTable.Version = FileReader_ReadUInt32(File, true);
		Fnt->HheaTable.Ascent = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.Descent = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.LineGap = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.AdvanceWidthMax = FileReader_ReadUInt16(File, true);
		Fnt->HheaTable.MinLeftSideBearing = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.MinRightSideBearing = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.xMaxExtent = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.CaretSlopeRise = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.CaretSlopeRun = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.CaretOffset = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.Reserved0 = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.Reserved1 = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.Reserved2 = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.Reserved3 = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.MetricDataFormt = FileReader_ReadInt16(File, true);
		Fnt->HheaTable.NumOfLongHorMetrics = FileReader_ReadUInt16(File, true);
		assert(Fnt->MaxpTable.Version == 0x10000);

		short unsigned NumGlyphs = Fnt->MaxpTable.NumGlyphs;

		Fnt->Width = (int unsigned)(Fnt->HeadTable.MaxX - Fnt->HeadTable.MinX);
		Fnt->Height = (int unsigned)(Fnt->HeadTable.MaxY - Fnt->HeadTable.MinY);
		Fnt->Glyphs = (Glyph*)Memory_Alloc(NumGlyphs * sizeof(Glyph), 0);
		Fnt->GlyphOffsets = (int unsigned*)Memory_Alloc(NumGlyphs * sizeof(int unsigned), 0);

		Vector_Alloc(&Fnt->BezierOffsets, sizeof(BezierOffsetEntry));
		Vector_Alloc(&Fnt->BezierCurves, sizeof(BezierCurveEntry));

		for (short unsigned GlyphIndex = 0; GlyphIndex < NumGlyphs; GlyphIndex++)
		{
			if (Fnt->HeadTable.IndexToLocFormat)
			{
				fseek(File, (long)(Fnt->LocaTableDir.Offset + (GlyphIndex * 4U)), SEEK_SET);
				Fnt->GlyphOffsets[GlyphIndex] = Fnt->GlyfTableDir.Offset + FileReader_ReadUInt32(File, true);
			}
			else
			{
				fseek(File, (long)(Fnt->LocaTableDir.Offset + (GlyphIndex * 2U)), SEEK_SET);
				Fnt->GlyphOffsets[GlyphIndex] = Fnt->GlyfTableDir.Offset + FileReader_ReadUInt16(File, true) * 2U;
			}
		}

		BezierOffsetEntry CurrBezierOffset = { 0 };

		for (short unsigned GlyphIndex = 0; GlyphIndex < NumGlyphs; GlyphIndex++)
		{
			Glyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];

			memset(CurrGlyph, 0, sizeof(Glyph));

			Font_ReadGlyphInternal(Fnt, File, GlyphIndex, CurrGlyph);
			Font_CreateBezierInternal(Fnt, CurrGlyph);

			CurrBezierOffset.Num = (int unsigned)Vector_Num(&CurrGlyph->BezierCurves);
			Vector_Push(&Fnt->BezierOffsets, &CurrBezierOffset);
			CurrBezierOffset.Start += CurrBezierOffset.Num;
			Vector_PushRange(&Fnt->BezierCurves, &CurrGlyph->BezierCurves);
		}

		Font_ApplyLayoutInfosInternal(Fnt, File);

		Font_UnicodeToGlyphMappingsInternal(Fnt, File);

		glGenVertexArrays(1, &Fnt->GlyphVertexArray);
		glGenBuffers(1, &Fnt->GlyphInstanceBuffer);
		glBindVertexArray(Fnt->GlyphVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, Fnt->GlyphInstanceBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Position))));
		glVertexAttribPointer(1, 4, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Rotation))));
		glVertexAttribPointer(2, 2, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Size))));
		glVertexAttribPointer(3, 2, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Bearing))));
		glVertexAttribPointer(4, 1, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, UnitsPerEm))));
		glVertexAttribPointer(5, 1, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Scale))));
		glVertexAttribIPointer(6, 1, GL_UNSIGNED_INT, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, GlyphIndex))));
		glVertexAttribPointer(7, 4, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Color))));
		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);
		glBufferData(GL_ARRAY_BUFFER, NumChars * sizeof(GlyphInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		void* BezierOffsetBuffer = Vector_Buffer(&Fnt->BezierOffsets);
		long long unsigned NumBezierOffsets = Vector_Num(&Fnt->BezierOffsets);

		glGenBuffers(1, &Fnt->BezierOffsetBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Fnt->BezierOffsetBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, (int unsigned)(NumBezierOffsets * sizeof(BezierOffsetEntry)), BezierOffsetBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		void* BezierCurveBuffer = Vector_Buffer(&Fnt->BezierCurves);
		long long unsigned NumBezierCurves = Vector_Num(&Fnt->BezierCurves);

		glGenBuffers(1, &Fnt->BezierCurveBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Fnt->BezierCurveBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, (int unsigned)(NumBezierCurves * sizeof(BezierCurveEntry)), BezierCurveBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		fclose(File);
	}
	Glyph* Font_GlyphByGlyphIndex(Font* Fnt, short unsigned GlyphIndex)
	{
		return &Fnt->Glyphs[GlyphIndex];
	}
	Glyph* Font_GlyphByUnicode(Font* Fnt, int unsigned Unicode)
	{
		return *(Glyph**)HashMap_At(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned));
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

			glDeleteVertexArrays(1, &Fnt->GlyphVertexArray);
			glDeleteBuffers(1, &Fnt->GlyphInstanceBuffer);
			glDeleteBuffers(1, &Fnt->BezierOffsetBuffer);
			glDeleteBuffers(1, &Fnt->BezierCurveBuffer);
		}

		HashMap_Free(&Fnt->GlyphMapping);
		Vector_Free(&Fnt->BezierOffsets);
		Vector_Free(&Fnt->BezierCurves);

		Memory_Free(Fnt->GlyphOffsets);
		Memory_Free(Fnt->Glyphs);

		memset(Fnt, 0, sizeof(Font));
	}
	void Font_ReadGlyphInternal(Font* Fnt, FILE* File, short unsigned GlyphIndex, Glyph* Result)
	{
		fseek(File, (long)Fnt->GlyphOffsets[GlyphIndex], SEEK_SET);

		Result->NumContours = FileReader_ReadInt16(File, true);
		Result->MinX = FileReader_ReadInt16(File, true);
		Result->MinY = FileReader_ReadInt16(File, true);
		Result->MaxX = FileReader_ReadInt16(File, true);
		Result->MaxY = FileReader_ReadInt16(File, true);
		Result->IsCompound = Result->NumContours < 0;
		Result->GlyphIndex = GlyphIndex;

		if (Result->IsCompound)
		{
			Font_ReadCompoundGlyphInternal(Fnt, File, GlyphIndex, Result);
		}
		else
		{
			Font_ReadSimpleGlyphInternal(Fnt, File, Result);
		}
	}
	void Font_ReadSimpleGlyphInternal(Font* Fnt, FILE* File, Glyph* Result)
	{
		UNREFERENCED_PARAMETER(Fnt);

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
	void Font_ReadCompoundGlyphInternal(Font* Fnt, FILE* File, short unsigned GlyphIndex, Glyph* Result)
	{
		UNREFERENCED_PARAMETER(GlyphIndex);

		while (true)
		{
			short unsigned Flags = FileReader_ReadUInt16(File, true);
			short unsigned NewGlyphIndex = FileReader_ReadUInt16(File, true);

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
			Glyph ResultGlyph = { 0 };
			Font_ReadGlyphInternal(Fnt, File, NewGlyphIndex, &ResultGlyph);
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
	void Font_ApplyLayoutInfosInternal(Font* Fnt, FILE* File)
	{
		fseek(File, (long)Fnt->HmtxTableDir.Offset, SEEK_SET);

		short unsigned NumLongHorMetrics = Fnt->HheaTable.NumOfLongHorMetrics;
		short unsigned NumRem = (short unsigned)(Fnt->MaxpTable.NumGlyphs - NumLongHorMetrics);

		short unsigned LastAdvanceWidth = 0;
		for (short unsigned MetricIndex = 0; MetricIndex < NumLongHorMetrics; MetricIndex++)
		{
			short unsigned GlyphIndex = MetricIndex;

			Glyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];

			short unsigned AdvanceWidth = FileReader_ReadUInt16(File, true);
			short LeftSideBearing = FileReader_ReadInt16(File, true);
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

			Glyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];

			short LeftSideBearing = FileReader_ReadInt16(File, true);
			short TopSideBearing = CurrGlyph->MinY + (CurrGlyph->MaxY - CurrGlyph->MinY);

			CurrGlyph->AdvanceWidth = LastAdvanceWidth;
			CurrGlyph->Width = (short unsigned)(CurrGlyph->MaxX - CurrGlyph->MinX);
			CurrGlyph->Height = (short unsigned)(CurrGlyph->MaxY - CurrGlyph->MinY);
			CurrGlyph->BearingX = (short unsigned)LeftSideBearing;
			CurrGlyph->BearingY = (short unsigned)(TopSideBearing);
		}
	}
	void Font_UnicodeToGlyphMappingsInternal(Font* Fnt, FILE* File)
	{
		HashMap_Alloc(&Fnt->GlyphMapping);

		fseek(File, (long)Fnt->CmapTableDir.Offset + (long)sizeof(FontCmapTable), SEEK_SET);

		int SelectedUnicodeVersionID = -1;
		int unsigned CmapSubTableOffset = 0;
		for (int unsigned SubTableIndex = 0; SubTableIndex < Fnt->CmapTable.NumberSubTables; SubTableIndex++)
		{
			FontCmapSubTable CmapSubTable = { 0 };
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

		fseek(File, (long)Fnt->CmapTableDir.Offset + (long)CmapSubTableOffset, SEEK_SET);

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
					int unsigned Unicode = CurrCode;

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

					Glyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];
					HashMap_Insert(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned), &CurrGlyph, sizeof(Glyph*));

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
					int unsigned Unicode = StartCharCode + CharIndex;

					Glyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];
					HashMap_Insert(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned), &CurrGlyph, sizeof(Glyph*));

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

			Glyph* CurrGlyph = &Fnt->Glyphs[GlyphIndex];
			HashMap_Insert(&Fnt->GlyphMapping, &Unicode, sizeof(int unsigned), &CurrGlyph, sizeof(Glyph*));
		}
	}
	void Font_CreateBezierInternal(Font* Fnt, Glyph* Glyph)
	{
		Vector_Alloc(&Glyph->PointOffsets, sizeof(PointOffsetEntry));
		Vector_Alloc(&Glyph->BezierPoints, sizeof(Vector2));
		Vector_Alloc(&Glyph->BezierOffsets, sizeof(BezierOffsetEntry));
		Vector_Alloc(&Glyph->BezierCurves, sizeof(BezierCurveEntry));

		Vector CollectedPoints = { 0 };
		Vector_Alloc(&CollectedPoints, sizeof(Vector2));

		short unsigned UnitsPerEm = Fnt->HeadTable.UnitsPerEm;
		short unsigned ContourStartIndex = 0;

		PointOffsetEntry CurrPointOffset = { 0 };
		BezierOffsetEntry CurrBezierOffset = { 0 };

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

				GlyphPoint* CurrGlyphPoint = &Glyph->Points[I0];
				GlyphPoint* NextGlyphPoint = &Glyph->Points[I1];

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
				PointOffsetEntry* PointOffset = (PointOffsetEntry*)Vector_At(&Glyph->PointOffsets, PointOffsetIndex);

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

			BezierCurveEntry BezierCurve = { 0 };

			Vector2_Set(*P0, BezierCurve.P0);
			Vector2_Set(*P1, BezierCurve.P1);
			Vector2_Set(*P2, BezierCurve.P2);

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
	void Font_DebugGlyphsInternal(Font* Fnt, int unsigned UnicodeFrom, int unsigned UnicodeTo, Matrix4 Projection, Matrix4 View)
	{
		float OffsetX = 0.0F;
		float IncrementX = 10.0F;
		float Scale = 10.0F;

		for (int unsigned GlyphIndex = UnicodeFrom; GlyphIndex <= UnicodeTo; GlyphIndex++)
		{
			Glyph* Glyph = Font_GlyphByUnicode(Fnt, GlyphIndex);

			if (Glyph)
			{
				Gizmo_BeginLines();
				{
					long long unsigned NumBezierOffsets = Vector_Num(&Glyph->BezierOffsets);
					for (long long unsigned BezierOffsetIndex = 0; BezierOffsetIndex < NumBezierOffsets; BezierOffsetIndex++)
					{
						BezierOffsetEntry* BezierOffset = (BezierOffsetEntry*)Vector_At(&Glyph->BezierOffsets, BezierOffsetIndex);

						for (int unsigned BezierCurveIndex = BezierOffset->Start; BezierCurveIndex < (BezierOffset->Start + BezierOffset->Num); BezierCurveIndex++)
						{
							BezierCurveEntry* BezierCurve = (BezierCurveEntry*)Vector_At(&Glyph->BezierCurves, BezierCurveIndex);

							float X0 = OffsetX + BezierCurve->P0[0] * Scale;
							float Y0 = BezierCurve->P0[1] * Scale;

							float X1 = OffsetX + BezierCurve->P1[0] * Scale;
							float Y1 = BezierCurve->P1[1] * Scale;

							float X2 = OffsetX + BezierCurve->P2[0] * Scale;
							float Y2 = BezierCurve->P2[1] * Scale;

							Gizmo_DrawLineBezierQuadraticSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, X1, Y1, 0.0F, X2, Y2, 0.0F, 10, 0.05F, 1.0F, 0.0F, 0.0F, 1.0F);
						}
					}
				}
				Gizmo_EndLines(Projection, View);

				Gizmo_BeginPoints();
				{
					long long unsigned NumBezierOffsets = Vector_Num(&Glyph->BezierOffsets);
					for (long long unsigned BezierOffsetIndex = 0; BezierOffsetIndex < NumBezierOffsets; BezierOffsetIndex++)
					{
						BezierOffsetEntry* BezierOffset = (BezierOffsetEntry*)Vector_At(&Glyph->BezierOffsets, BezierOffsetIndex);

						for (int unsigned BezierCurveIndex = BezierOffset->Start; BezierCurveIndex < (BezierOffset->Start + BezierOffset->Num); BezierCurveIndex++)
						{
							BezierCurveEntry* BezierCurve = (BezierCurveEntry*)Vector_At(&Glyph->BezierCurves, BezierCurveIndex);

							float X0 = OffsetX + BezierCurve->P0[0] * Scale;
							float Y0 = BezierCurve->P0[1] * Scale;

							float X1 = OffsetX + BezierCurve->P1[0] * Scale;
							float Y1 = BezierCurve->P1[1] * Scale;

							float X2 = OffsetX + BezierCurve->P2[0] * Scale;
							float Y2 = BezierCurve->P2[1] * Scale;

							Gizmo_DrawPointSimple(GIZMO_DIR_XY, X0, Y0, 0.0F, 0.15F, 1.0F, 0.0F, 0.0F, 1.0F);
							Gizmo_DrawPointSimple(GIZMO_DIR_XY, X1, Y1, 0.0F, 0.15F, 1.0F, 0.0F, 0.0F, 1.0F);
							Gizmo_DrawPointSimple(GIZMO_DIR_XY, X2, Y2, 0.0F, 0.15F, 1.0F, 0.0F, 0.0F, 1.0F);
						}
					}
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
	void Text_Begin(Font* Fnt)
	{
		sCurrFont = Fnt;
		glBindBuffer(GL_ARRAY_BUFFER, sCurrFont->GlyphInstanceBuffer);
		sCurrFont->MappedGlyphInstanceBuffer = (GlyphInstanceEntry*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		sCurrFont->GlyphInstanceOffset = 0;
	}
	void Text_Draw(char const* Text, Vector3 Position, float Scale, Quaternion Rotation, Vector4 Color)
	{
		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = Position[0];
		float Y = Position[1];
		float Z = Position[2];

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

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
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*CharCode;
				Glyph* CurrGlyph = *(Glyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Position[0] = X;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Position[1] = Y;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Position[2] = Z;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[0] = Rotation[0];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[1] = Rotation[1];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[2] = Rotation[2];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[3] = Rotation[3];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Size[0] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Size[1] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Height;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Bearing[0] = (float)CurrGlyph->BearingX;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Bearing[1] = (float)CurrGlyph->BearingY;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Scale = Scale;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[0] = Color[0];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[1] = Color[1];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[2] = Color[2];
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[3] = Color[3];

					sCurrFont->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Scale;

				break;
			}
			}
		}
	}
	void Text_DrawSimple(char const* Text, float PositionX, float PositionY, float PositionZ, float Scale, float RotationX, float RotationY, float RotationZ, float RotationW, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = PositionX;
		float Y = PositionY;
		float Z = PositionZ;

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

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
				X = PositionX;
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*CharCode;
				Glyph* CurrGlyph = *(Glyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Position[0] = X;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Position[1] = Y;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Position[2] = Z;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[0] = RotationX;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[1] = RotationY;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[2] = RotationZ;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Rotation[3] = RotationW;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Size[0] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Width;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Size[1] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Height;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Bearing[0] = (float)CurrGlyph->BearingX;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Bearing[1] = (float)CurrGlyph->BearingY;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Scale = Scale;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[0] = ColorR;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[1] = ColorG;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[2] = ColorB;
					sCurrFont->MappedGlyphInstanceBuffer[sCurrFont->GlyphInstanceOffset].Color[3] = ColorA;

					sCurrFont->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Scale;

				break;
			}
			}
		}
	}
	void Text_End(Matrix4 Projection, Matrix4 View)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Shader_Bind(sFontProgram);
		Shader_SetUniformMatrix4(sFontProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sFontProgram, "ViewMatrix", View);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, sCurrFont->BezierOffsetBuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sCurrFont->BezierCurveBuffer);
		glBindVertexArray(sCurrFont->GlyphVertexArray);
		glDrawArraysInstanced(GL_POINTS, 0, 1, (int)sCurrFont->GlyphInstanceOffset);
		glBindVertexArray(0);
	}
	void Text_CacheAlloc(TextCache* Cache, int unsigned NumChars)
	{
		memset(Cache, 0, sizeof(TextCache));

		Cache->GlyphInstanceOffset = 0;
		Cache->MappedGlyphInstanceBuffer = 0;

		glGenVertexArrays(1, &Cache->GlyphVertexArray);
		glGenBuffers(1, &Cache->GlyphInstanceBuffer);
		glBindVertexArray(Cache->GlyphVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, Cache->GlyphInstanceBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Position))));
		glVertexAttribPointer(1, 4, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Rotation))));
		glVertexAttribPointer(2, 2, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Size))));
		glVertexAttribPointer(3, 2, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Bearing))));
		glVertexAttribPointer(4, 1, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, UnitsPerEm))));
		glVertexAttribPointer(5, 1, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Scale))));
		glVertexAttribIPointer(6, 1, GL_UNSIGNED_INT, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, GlyphIndex))));
		glVertexAttribPointer(7, 4, GL_FLOAT, 0, sizeof(GlyphInstanceEntry), ((void*)(OFFSET_OF(GlyphInstanceEntry, Color))));
		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);
		glBufferData(GL_ARRAY_BUFFER, NumChars * sizeof(GlyphInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Text_BeginCache(TextCache* Cache, Font* Fnt)
	{
		sCurrFont = Fnt;
		glBindBuffer(GL_ARRAY_BUFFER, Cache->GlyphInstanceBuffer);
		Cache->MappedGlyphInstanceBuffer = (GlyphInstanceEntry*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		Cache->GlyphInstanceOffset = 0;
	}
	void Text_PushCache(TextCache* Cache, char const* Text, Vector3 Position, Quaternion Rotation, float Scale, Vector4 Color)
	{
		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = Position[0];
		float Y = Position[1];
		float Z = Position[2];

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

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
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*CharCode;
				Glyph* CurrGlyph = *(Glyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position[0] = X;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position[1] = Y;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position[2] = Z;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[0] = Rotation[0];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[1] = Rotation[1];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[2] = Rotation[2];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[3] = Rotation[3];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Size[0] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Width;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Size[1] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Height;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing[0] = (float)CurrGlyph->BearingX;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing[1] = (float)CurrGlyph->BearingY;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Scale = Scale;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[0] = Color[0];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[1] = Color[1];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[2] = Color[2];
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[3] = Color[3];

					Cache->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Scale;

				break;
			}
			}
		}
	}
	void Text_PushCacheSimple(TextCache* Cache, char const* Text, float PositionX, float PositionY, float PositionZ, float RotationX, float RotationY, float RotationZ, float RotationW, float Scale, float ColorR, float ColorG, float ColorB, float ColorA)
	{
		short unsigned UnitsPerEm = sCurrFont->HeadTable.UnitsPerEm;

		float X = PositionX;
		float Y = PositionY;
		float Z = PositionZ;

		Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

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
				X = PositionX;
				Y -= ((float)sCurrFont->Height / UnitsPerEm) * Scale;

				break;
			}
			default:
			{
				int unsigned Unicode = (int unsigned)*CharCode;
				Glyph* CurrGlyph = *(Glyph**)HashMap_At(&sCurrFont->GlyphMapping, &Unicode, sizeof(int unsigned));

				if (CurrGlyph->NumPoints)
				{
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position[0] = X;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position[1] = Y;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Position[2] = Z;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[0] = RotationX;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[1] = RotationY;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[2] = RotationZ;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Rotation[3] = RotationW;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Size[0] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Width;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Size[1] = (*CharCode == ' ') ? 0.0F : (float)CurrGlyph->Height;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing[0] = (float)CurrGlyph->BearingX;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Bearing[1] = (float)CurrGlyph->BearingY;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].UnitsPerEm = (float)UnitsPerEm;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Scale = Scale;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].GlyphIndex = CurrGlyph->GlyphIndex;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[0] = ColorR;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[1] = ColorG;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[2] = ColorB;
					Cache->MappedGlyphInstanceBuffer[Cache->GlyphInstanceOffset].Color[3] = ColorA;

					Cache->GlyphInstanceOffset += 1;
				}

				X += ((float)CurrGlyph->AdvanceWidth / UnitsPerEm) * Scale;

				break;
			}
			}
		}
	}
	void Text_EndCache(TextCache* Cache)
	{
		UNREFERENCED_PARAMETER(Cache);

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Text_DrawCache(TextCache* Cache, Matrix4 Projection, Matrix4 View)
	{
		Shader_Bind(sFontProgram);
		Shader_SetUniformMatrix4(sFontProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sFontProgram, "ViewMatrix", View);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, sCurrFont->BezierOffsetBuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sCurrFont->BezierCurveBuffer);
		glBindVertexArray(Cache->GlyphVertexArray);
		glDrawArraysInstanced(GL_POINTS, 0, 1, (int)Cache->GlyphInstanceOffset);
		glBindVertexArray(0);
	}
	extern void Text_CacheFree(TextCache* Cache)
	{
		glDeleteBuffers(1, &Cache->GlyphInstanceBuffer);
		glDeleteBuffers(1, &Cache->GlyphInstanceOffset);
		glDeleteVertexArrays(1, &Cache->GlyphVertexArray);
		memset(Cache, 0, sizeof(TextCache));
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
	void Texture2D_Mount(Texture2D* Texture, int unsigned Index)
	{
		glBindTextureUnit(Index, Texture->Texture);
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
	char unsigned* Texture2D_CopyPixels(Texture2D* Texture)
	{
		int unsigned PixelSize = 0;
		switch (Texture->Type)
		{
		case TEXTURE_TYPE_UINT8: PixelSize = sizeof(char unsigned); break;
		case TEXTURE_TYPE_REAL32: PixelSize = sizeof(float); break;
		case TEXTURE_TYPE_UINT24_UINT8: PixelSize = sizeof(int unsigned); break;
		}
		char unsigned* Pixels = (char unsigned*)Memory_Alloc(Texture->Width * Texture->Height * PixelSize, 0);
		glBindTexture(GL_TEXTURE_2D, Texture->Texture);
		glGetTexImage(GL_TEXTURE_2D, 0, Texture->Format, Texture->Type, Pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
		return Pixels;
	}
	void Texture2D_Free(Texture2D* Texture)
	{
		glDeleteTextures(1, &Texture->Texture);
		memset(Texture, 0, sizeof(Texture2D));
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
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, Buffer->Width);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, Buffer->Height);
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
	}
	void BitMap_Free(char unsigned* Pixels)
	{
		Memory_Free(Pixels);
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

		VertexBuffer[0].Position[0] = 0.0F;
		VertexBuffer[0].Position[1] = 0.0F;
		VertexBuffer[0].TextureCoords[0] = 0.0F;
		VertexBuffer[0].TextureCoords[1] = 0.0F;
		VertexBuffer[1].Position[0] = 1.0F;
		VertexBuffer[1].Position[1] = 0.0F;
		VertexBuffer[1].TextureCoords[0] = 1.0F;
		VertexBuffer[1].TextureCoords[1] = 0.0F;
		VertexBuffer[2].Position[0] = 0.0F;
		VertexBuffer[2].Position[1] = 1.0F;
		VertexBuffer[2].TextureCoords[0] = 0.0F;
		VertexBuffer[2].TextureCoords[1] = 1.0F;
		VertexBuffer[3].Position[0] = 1.0F;
		VertexBuffer[3].Position[1] = 1.0F;
		VertexBuffer[3].TextureCoords[0] = 1.0F;
		VertexBuffer[3].TextureCoords[1] = 1.0F;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;
		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 1;

		glGenVertexArrays(1, &Mesh->VertexArray);
		glGenBuffers(1, &Mesh->VertexBuffer);
		glGenBuffers(1, &Mesh->IndexBuffer);
		glBindVertexArray(Mesh->VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh->VertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(SpriteVertex), ((void*)(OFFSET_OF(SpriteVertex, Position))));
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(SpriteVertex), ((void*)(OFFSET_OF(SpriteVertex, TextureCoords))));
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SpriteVertex), VertexBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh->IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int unsigned), IndexBuffer, GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	int unsigned Primitive_GetSpriteVertexArray(SpriteMesh* Mesh)
	{
		return Mesh->VertexArray;
	}
	void Primitive_SpriteFree(SpriteMesh* Mesh)
	{
		glDeleteBuffers(1, &Mesh->VertexBuffer);
		glDeleteBuffers(1, &Mesh->IndexBuffer);
		glDeleteVertexArrays(1, &Mesh->VertexArray);

		memset(Mesh, 0, sizeof(SpriteMesh));
	}
	void Primitive_PostProcessAlloc(PostProcessMesh* Mesh)
	{
		memset(Mesh, 0, sizeof(PostProcessMesh));

		static PostProcessVertex VertexBuffer[4] = { 0 };
		static int unsigned IndexBuffer[6] = { 0 };

		VertexBuffer[0].Position[0] = -1.0F;
		VertexBuffer[0].Position[1] = -1.0F;
		VertexBuffer[0].TextureCoords[0] = 0.0F;
		VertexBuffer[0].TextureCoords[1] = 0.0F;
		VertexBuffer[1].Position[0] = 1.0F;
		VertexBuffer[1].Position[1] = -1.0F;
		VertexBuffer[1].TextureCoords[0] = 1.0F;
		VertexBuffer[1].TextureCoords[1] = 0.0F;
		VertexBuffer[2].Position[0] = -1.0F;
		VertexBuffer[2].Position[1] = 1.0F;
		VertexBuffer[2].TextureCoords[0] = 0.0F;
		VertexBuffer[2].TextureCoords[1] = 1.0F;
		VertexBuffer[3].Position[0] = 1.0F;
		VertexBuffer[3].Position[1] = 1.0F;
		VertexBuffer[3].TextureCoords[0] = 1.0F;
		VertexBuffer[3].TextureCoords[1] = 1.0F;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;
		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 1;

		glGenVertexArrays(1, &Mesh->VertexArray);
		glGenBuffers(1, &Mesh->VertexBuffer);
		glGenBuffers(1, &Mesh->IndexBuffer);
		glBindVertexArray(Mesh->VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh->VertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(PostProcessVertex), ((void*)(OFFSET_OF(PostProcessVertex, Position))));
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(PostProcessVertex), ((void*)(OFFSET_OF(PostProcessVertex, TextureCoords))));
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(PostProcessVertex), VertexBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh->IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int unsigned), IndexBuffer, GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	int unsigned Primitive_GetPostProcessVertexArray(PostProcessMesh* Mesh)
	{
		return Mesh->VertexArray;
	}
	void Primitive_PostProcessFree(PostProcessMesh* Mesh)
	{
		glDeleteBuffers(1, &Mesh->VertexBuffer);
		glDeleteBuffers(1, &Mesh->IndexBuffer);
		glDeleteVertexArrays(1, &Mesh->VertexArray);
		memset(Mesh, 0, sizeof(PostProcessMesh));
	}
	void Primitive_InstancedSpriteAlloc(InstancedSprite* Mesh, int unsigned NumInstances)
	{
		memset(Mesh, 0, sizeof(InstancedSprite));

		Mesh->NumInstances = NumInstances;

		static SpriteVertex VertexBuffer[4] = { 0 };
		static int unsigned IndexBuffer[6] = { 0 };

		VertexBuffer[0].Position[0] = 0.0F;
		VertexBuffer[0].Position[1] = 0.0F;
		VertexBuffer[0].TextureCoords[0] = 0.0F;
		VertexBuffer[0].TextureCoords[1] = 0.0F;
		VertexBuffer[1].Position[0] = 1.0F;
		VertexBuffer[1].Position[1] = 0.0F;
		VertexBuffer[1].TextureCoords[0] = 1.0F;
		VertexBuffer[1].TextureCoords[1] = 0.0F;
		VertexBuffer[2].Position[0] = 0.0F;
		VertexBuffer[2].Position[1] = 1.0F;
		VertexBuffer[2].TextureCoords[0] = 0.0F;
		VertexBuffer[2].TextureCoords[1] = 1.0F;
		VertexBuffer[3].Position[0] = 1.0F;
		VertexBuffer[3].Position[1] = 1.0F;
		VertexBuffer[3].TextureCoords[0] = 1.0F;
		VertexBuffer[3].TextureCoords[1] = 1.0F;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;
		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 1;

		glGenVertexArrays(1, &Mesh->VertexArray);
		glGenBuffers(1, &Mesh->VertexBuffer);
		glGenBuffers(1, &Mesh->InstanceBuffer);
		glGenBuffers(1, &Mesh->IndexBuffer);
		glBindVertexArray(Mesh->VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh->VertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(SpriteVertex), ((void*)(OFFSET_OF(SpriteVertex, Position))));
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(SpriteVertex), ((void*)(OFFSET_OF(SpriteVertex, TextureCoords))));
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SpriteVertex), VertexBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh->InstanceBuffer);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(2, 4, GL_FLOAT, 0, sizeof(SpriteInstanceEntry), ((void*)(OFFSET_OF(SpriteInstanceEntry, TransformMatrix))));
		glVertexAttribPointer(3, 4, GL_FLOAT, 0, sizeof(SpriteInstanceEntry), ((void*)(OFFSET_OF(SpriteInstanceEntry, TransformMatrix) + sizeof(Vector4))));
		glVertexAttribPointer(4, 4, GL_FLOAT, 0, sizeof(SpriteInstanceEntry), ((void*)(OFFSET_OF(SpriteInstanceEntry, TransformMatrix) + sizeof(Vector4) * 2)));
		glVertexAttribPointer(5, 4, GL_FLOAT, 0, sizeof(SpriteInstanceEntry), ((void*)(OFFSET_OF(SpriteInstanceEntry, TransformMatrix) + sizeof(Vector4) * 3)));
		glVertexAttribIPointer(6, 1, GL_UNSIGNED_INT, sizeof(SpriteInstanceEntry), ((void*)(OFFSET_OF(SpriteInstanceEntry, AtlasIndex))));
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glBufferData(GL_ARRAY_BUFFER, NumInstances * sizeof(SpriteInstanceEntry), 0, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh->IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int unsigned), IndexBuffer, GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
		glBindBuffer(GL_ARRAY_BUFFER, Mesh->InstanceBuffer);
		return (SpriteInstanceEntry*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	void Primitive_InstancedSpriteUnMapBuffer(InstancedSprite* Mesh)
	{
		UNREFERENCED_PARAMETER(Mesh);

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Primitive_InstancedSpriteFree(InstancedSprite* Mesh)
	{
		glDeleteBuffers(1, &Mesh->VertexBuffer);
		glDeleteBuffers(1, &Mesh->InstanceBuffer);
		glDeleteBuffers(1, &Mesh->IndexBuffer);
		glDeleteVertexArrays(1, &Mesh->VertexArray);
		memset(Mesh, 0, sizeof(InstancedSprite));
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
		Shader_VertexFragmentAlloc(&Effect->Program, sPassThroughPostProcessVertexShader, FragmentSource);
	}
	void PostProcessEffect_Begin(PostProcessEffect* Effect)
	{
		Shader_Bind(Effect->Program);
	}
	void PostProcessEffect_SetColorAttachment(PostProcessEffect* Effect, Texture2D* ColorAttachment, int unsigned ColorAttachmentIndex)
	{
		UNREFERENCED_PARAMETER(Effect);
		Texture2D_Mount(ColorAttachment, ColorAttachmentIndex);
	}
	void PostProcessEffect_End(PostProcessEffect* Effect)
	{
		int unsigned VertexArray = Primitive_GetPostProcessVertexArray(Effect->Mesh);
		glBindVertexArray(VertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	void PostProcessEffect_Free(PostProcessEffect* Effect)
	{
		Shader_Free(Effect->Program);
		memset(Effect, 0, sizeof(PostProcessEffect));
	}
#endif // FAST_GL_IMPLEMENTATION

	///////////////////////////////////////////////////////////////
	// Histogram Declaration
	///////////////////////////////////////////////////////////////

#ifdef FAST_GL_IMPLEMENTATION
	void Histogram_Alloc(Histogram* Histgrm, SpriteMesh* Mesh, int unsigned NumSamples, float FastValue, float SlowValue, float StepSize)
	{
		memset(Histgrm, 0, sizeof(Histogram));

		Histgrm->Mesh = Mesh;
		Histgrm->Samples = (float*)Memory_Alloc(NumSamples * sizeof(float), 0);
		Histgrm->NumSamples = NumSamples;
		Histgrm->SlowValue = SlowValue;
		Histgrm->FastValue = FastValue;
		Histgrm->StepSize = StepSize;

		for (int unsigned SampleIndex = 0; SampleIndex < NumSamples; SampleIndex++)
		{
			Histgrm->Samples[SampleIndex] = 0.0F;
		}

		glGenBuffers(1, &Histgrm->SampleBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Histgrm->SampleBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, NumSamples * sizeof(float), Histgrm->Samples, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	void Histogram_PushSample(Histogram* Histgrm, float Sample)
	{
		Histgrm->ScaleAcc -= Histgrm->Samples[Histgrm->SampleIndex];
		Histgrm->ScaleAcc += Sample;
		Histgrm->Scale = Math_StepTowards(Histgrm->Scale, Histgrm->ScaleAcc / Histgrm->NumSamples, Histgrm->StepSize);
		Histgrm->Samples[Histgrm->SampleIndex] = Sample;
		Histgrm->SampleIndex += 1;

		if (Histgrm->SampleIndex >= Histgrm->NumSamples)
		{
			Histgrm->SampleIndex = 0;
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Histgrm->SampleBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, Histgrm->NumSamples * sizeof(float), Histgrm->Samples, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	void Histogram_Draw(Histogram* Histgrm, Matrix4 Projection, Matrix4 View, Vector3 Position)
	{
		static Matrix4 Model = MATRIX4_ZERO;

		Matrix4_Identity(Model);
		Matrix4_SetPosition(Position, Model);
		Matrix4_SetScaleSimple(5.0F, 0.5F, 1.0F, Model);

		Shader_Bind(sHistogramProgram);
		Shader_SetUniformMatrix4(sHistogramProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sHistogramProgram, "ViewMatrix", View);
		Shader_SetUniformMatrix4(sHistogramProgram, "ModelMatrix", Model);
		Shader_SetUniformUInt32(sHistogramProgram, "NumSamples", Histgrm->NumSamples);
		Shader_SetUniformUInt32(sHistogramProgram, "CurrIndex", Histgrm->SampleIndex);
		Shader_SetUniformReal32(sHistogramProgram, "Scale", Histgrm->Scale);
		Shader_SetUniformReal32(sHistogramProgram, "SlowValue", Histgrm->SlowValue);
		Shader_SetUniformReal32(sHistogramProgram, "FastValue", Histgrm->FastValue);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, Histgrm->SampleBuffer);

		glBindVertexArray(Histgrm->Mesh->VertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	void Histogram_DrawSimple(Histogram* Histgrm, Matrix4 Projection, Matrix4 View, float PositionX, float PositionY, float PositionZ)
	{
		static Matrix4 Model = MATRIX4_ZERO;

		Matrix4_Identity(Model);
		Matrix4_SetPositionSimple(PositionX, PositionY, PositionZ, Model);
		Matrix4_SetScaleSimple(5.0F, 0.5F, 1.0F, Model);

		Shader_Bind(sHistogramProgram);
		Shader_SetUniformMatrix4(sHistogramProgram, "ProjectionMatrix", Projection);
		Shader_SetUniformMatrix4(sHistogramProgram, "ViewMatrix", View);
		Shader_SetUniformMatrix4(sHistogramProgram, "ModelMatrix", Model);
		Shader_SetUniformUInt32(sHistogramProgram, "NumSamples", Histgrm->NumSamples);
		Shader_SetUniformUInt32(sHistogramProgram, "CurrIndex", Histgrm->SampleIndex);
		Shader_SetUniformReal32(sHistogramProgram, "Scale", Histgrm->Scale);
		Shader_SetUniformReal32(sHistogramProgram, "SlowValue", Histgrm->SlowValue);
		Shader_SetUniformReal32(sHistogramProgram, "FastValue", Histgrm->FastValue);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, Histgrm->SampleBuffer);

		glBindVertexArray(Histgrm->Mesh->VertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	void Histogram_Free(Histogram* Histgrm)
	{
		glDeleteBuffers(1, &Histgrm->SampleBuffer);
		Memory_Free(Histgrm->Samples);

		memset(Histgrm, 0, sizeof(Histogram));
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

		Shader_VertexGeometryFragmentAlloc(&sFontProgram, sFontVertexShader, sFontGeometryShader, sFontFragmentShader);
		Shader_VertexFragmentAlloc(&sHistogramProgram, sHistogramVertexShader, sHistogramFragmentShader);

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
		Shader_Free(sFontProgram);
		Shader_Free(sHistogramProgram);

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

			int Width = (int)WindowPos->cx;
			int Height = (int)WindowPos->cy;
			int TitleBarHeight = (int)GetSystemMetrics(SM_CYCAPTION);
			int BorderHeight = (int)GetSystemMetrics(SM_CYFRAME);

			if ((Width > 0) && (Height > 0))
			{
				sWindowWidth = Width;
				sWindowHeight = Height - TitleBarHeight + BorderHeight;
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
			int TitleBarHeight = (int unsigned)GetSystemMetrics(SM_CYCAPTION);
			int BorderHeight = (int unsigned)GetSystemMetrics(SM_CYFRAME);

			sMousePositionX = PositionX;
			sMousePositionY = PositionY + TitleBarHeight - BorderHeight;

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
		case GL_DEBUG_SEVERITY_LOW: printf("[GL] Severity:Low Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_MEDIUM: printf("[GL] Severity:Medium Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_HIGH: printf("[GL] Severity:High Type:0x%x Message:%s\n", Type, Message); break;
		}
#endif // FAST_GL_DEBUG
	}
#endif // FAST_GL_IMPLEMENTATION

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FAST_GL_H