#include "modelframe.h"

void ModelFrame::Init(CEngine* e) {
	engine = e;

	glfwSetInputMode(engine->wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	camera = new Camera(glm::vec3(13.8f, 4.7f, -3.3f), 
			    glm::vec2(-7.5f, 175.0f),
			    0.1f, 0.020f);

	shader = new Shader("shaders/wintermute.vs", "shaders/wintermute.frag");

	wintermute = new Model("models/wintermute.obj");

	proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
}

void ModelFrame::Cleanup() {}
void ModelFrame::Pause() {}
void ModelFrame::Resume() {}

void ModelFrame::ProcessInput(bool* keyboard, bool* mouse, double mxpos, double mypos) {
	if (keyboard[GLFW_KEY_ESCAPE])
		engine->Quit();

	if (keyboard[GLFW_KEY_W])
		camera->MoveForward();
	if (keyboard[GLFW_KEY_S])
		camera->MoveBack();
	if (keyboard[GLFW_KEY_D])
		camera->StrafeRight();
	if (keyboard[GLFW_KEY_A])
		camera->StrafeLeft();

	camera->Update((float)mxpos, (float)mypos);
}

void ModelFrame::Loop() {}

void ModelFrame::Render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shader->Use();
	shader->uMatrix4("model", model);
	shader->uMatrix4("view", camera->GetView());
	shader->uMatrix4("proj", proj);
	shader->uVector3("viewPos", cameraPos);
	shader->uVector3("mcolor", 0.3f, 0.3f, 0.3f);
	shader->uVector3("lightPos", 12.1f, 3.3f, -4.4f);
	shader->uVector3("lightPos2", -11.9f, 1.6f, -2.2f);

	wintermute->Draw(shader);

	glfwSwapBuffers(engine->wnd);
}
