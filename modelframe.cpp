#include "modelframe.h"

void ModelFrame::Init(CEngine* e) {
	engine = e;

	glfwSetInputMode(engine->wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
    camera.SetSens(0.04);
}

void ModelFrame::Cleanup() {}
void ModelFrame::Pause() {}
void ModelFrame::Resume() {}

void ModelFrame::ProcessInput(bool* keyboard, bool* mouse, double mxpos, double mypos) {
	if (keyboard[GLFW_KEY_ESCAPE]) engine->Quit();

	if (keyboard[GLFW_KEY_W]) camera.MoveForward();
	
	if (keyboard[GLFW_KEY_S]) camera.MoveBack();
	
	if (keyboard[GLFW_KEY_D]) camera.StrafeRight();
	
	if (keyboard[GLFW_KEY_A]) camera.StrafeLeft();

	camera.Update((float)mxpos, (float)mypos);
}

void ModelFrame::Loop() {}

void ModelFrame::Render() {
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.Draw(proj, camera.GetView());
		
	shader.Use();
	shader.uMatrix4("model", model);
	shader.uMatrix4("view", camera.GetView());
	shader.uMatrix4("proj", proj);
	shader.uVector3("viewPos", camera.GetPos());
	shader.uVector3("mcolor", 0.3f, 0.3f, 0.3f);
	shader.uVector3("lightPos", 12.1f, 3.3f, -4.4f);
	shader.uVector3("lightPos2", -11.9f, 1.6f, -2.2f);

	wintermute.Draw(&shader);

	glfwSwapBuffers(engine->wnd);
}
