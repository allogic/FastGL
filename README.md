# FastGL

## Basic Window
```c
#define FAST_GL_IMPLEMENTATION
#include "FastGL.h"

int main(void)
{
	Window_Alloc(800, 800, "FastGL");
	Gizmo_Alloc(3, 3, 0);

	Matrix4 Projection = MATRIX4_IDENTITY;
	Matrix4 View = MATRIX4_IDENTITY;

	Vector3 Eye = { 0.0F, 0.0F, -10.0F };
	Vector3 Center = VECTOR3_ZERO;
	Vector3 Up = VECTOR3_UP;

	int Width = 0;
	int Height = 0;

	while (!Window_ShouldClose())
	{
		Window_PollEvents();

		Width = Window_GetWidth();
		Height = Window_GetHeight();

		glViewport(0, 0, Width, Height);
		glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		Matrix4_Perspective(DEG_TO_RAD(45.0F), (float)Width / (float)Height, 0.01F, 1000.0F, Projection);
		Matrix4_LookAt(Eye, Center, Up, View);

		Gizmo_BeginLines();
		Gizmo_DrawLineSimple(GIZMO_DIR_XY, -SQRT_3, -1.0F, 0.0F, 0.0F, 2.0F, 0.0F, 0.05F, 0.4F, 0.4F, 0.4F, 1.0F);
		Gizmo_DrawLineSimple(GIZMO_DIR_XY, SQRT_3, -1.0F, 0.0F, 0.0F, 2.0F, 0.0F, 0.05F, 0.4F, 0.4F, 0.4F, 1.0F);
		Gizmo_DrawLineSimple(GIZMO_DIR_XY, -SQRT_3, -1.0F, 0.0F, SQRT_3, -1.0F, 0.0F, 0.05F, 0.4F, 0.4F, 0.4F, 1.0F);
		Gizmo_EndLines(Projection, View);

		Gizmo_BeginPoints();
		Gizmo_DrawPointSimple(GIZMO_DIR_XY, -SQRT_3, -1.0F, 0.0F, 0.2F, 1.0F, 1.0F, 1.0F, 1.0F);
		Gizmo_DrawPointSimple(GIZMO_DIR_XY, 0.0F, 2.0F, 0.0F, 0.2F, 1.0F, 1.0F, 1.0F, 1.0F);
		Gizmo_DrawPointSimple(GIZMO_DIR_XY, SQRT_3, -1.0F, 0.0F, 0.2F, 1.0F, 1.0F, 1.0F, 1.0F);
		Gizmo_EndPoints(Projection, View);

		Text_Begin(&gDefaultFont);
		Text_DrawScreenSimple(15.0F, 0.0F, 0.0F, 100.0F, 1.0F, 1.0F, 1.0F, 1.0F, "Fast");
		Text_DrawScreenSimple(250.0F, 0.0F, 0.0F, 100.0F, 1.0F, 0.0F, 0.0F, 1.0F, "GL");
		Text_End(Projection, View);

		Window_SwapBuffers();
	}

	Gizmo_Free();
	Window_Free();

	return 0;
}
```
