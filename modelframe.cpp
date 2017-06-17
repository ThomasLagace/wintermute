#include "modelframe.h"

void ModelFrame::Init(CEngine* e) {
	engine = e;
}

void ModelFrame::Cleanup() {}

void ModelFrame::Pause() {}

void ModelFrame::Resume() {}

void ModelFrame::Loop() {
	// Do this every frame
}

void ModelFrame::ProcessInput(bool* keyboard, bool* mouse, double mxpos, double mypos) {
	//         ^
	// --------+
}

void ModelFrame::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(engine->wnd);
}
