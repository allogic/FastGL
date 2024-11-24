# FastGL

## Basic Window
```c
#define FGL_IMPLEMENTATION
#include "FastGL.h"

int main()
{
	int Width = 800;
	int Height = 800;

	Window_Alloc(Width, Height, "FastGL");

	while (!Window_ShouldClose())
	{
		Window_PollEvents();

		Width = Window_GetWidth();
		Height = Window_GetHeight();

		glViewport(0, 0, Width, Height);
		glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		Text_BeginScreen(Font_GetDefault());
		Text_DrawScreenSimple(10.0F, 10.0F, 0.0F, 0.0F, 100.0F, 1.0F, 1.0F, 1.0F, 1.0F, "FastGL");
		Text_EndScreen();

		Window_SwapBuffers();
	}

	Window_Free();

	return 0;
}
```
