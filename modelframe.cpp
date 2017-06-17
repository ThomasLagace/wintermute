#include "modelframe.h"

void ModelFrame::Init(CEngine* e) {
	engine = e;

	glfwSetInputMode(engine->wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

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
		cameraPos += cameraSpeed * cameraFront;
	if (keyboard[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keyboard[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keyboard[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	yaw += (float)((mxpos - lastX) * sensitivity);
	pitch += (float)((lastY - mypos) * sensitivity);
	lastX = mxpos;
	lastY = mypos;

	if (pitch < -89.0f)
		pitch = -89.0f;
	if (pitch > 89.0f)
		pitch = 89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void ModelFrame::Loop() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void ModelFrame::Render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shader->Use();
	shader->uMatrix4("model", model);
	shader->uMatrix4("view", view);
	shader->uMatrix4("proj", proj);
	shader->uVector3("viewPos", cameraPos);
	shader->uVector3("mcolor", 0.3f, 0.3f, 0.3f);
	shader->uVector3("lightPos", 12.1f, 3.3f, -4.4f);
	shader->uVector3("lightPos2", -11.9f, 1.6f, -2.2f);

	wintermute->Draw(shader);

	glfwSwapBuffers(engine->wnd);
}
