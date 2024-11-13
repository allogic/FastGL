# FastGL

## Basic Window
```c
#define FAST_GL_IMPLEMENTATION
#include "FastGL.h"

int main(void)
{
	Window_Alloc(800, 800, "FastGL");

	int Width = Window_GetWidth();
	int Height = Window_GetHeight();

	while (!Window_ShouldClose())
	{
		Window_PollEvents();

		Width = Window_GetWidth();
		Height = Window_GetHeight();

		glViewport(0, 0, Width, Height);
		glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		Text_BeginScreen(Font_GetDefault());
		Text_DrawScreenSimple(10.0F, 10.0F, 0.0F, 100.0F, 1.0F, 1.0F, 1.0F, 1.0F, "FastGL");
		Text_EndScreen();

		Window_SwapBuffers();
	}

	Window_Free();

	return 0;
}
```
