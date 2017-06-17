#include "modelframe.h"

void ModelFrame::Init(CEngine* e) {
	engine = e;
    wintermute = new Model("models/wintermute.obj");
    shader = new Shader("shaders/wintermute.vs","shaders/wintermute.frag");
    wintermute->Draw(shader);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 3.0f));
    proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f); 
    cameraFront = glm::vec3 (1.0f, 0.0f, 0.0f);
}

void ModelFrame::Cleanup() {}

void ModelFrame::Pause() {}

void ModelFrame::Resume() {}

void ModelFrame::Loop() {
	// Do this every frame
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void ModelFrame::ProcessInput(bool* keyboard, bool* mouse, double mxpos, double mypos) {
    if (keyboard[GLFW_KEY_ESCAPE]) engine->Quit();
}

void ModelFrame::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(engine->wnd);
    shader->Use();
    shader->uMatrix4("model", model);
    shader->uMatrix4("view", view);
    shader->uVector3("viewPos", cameraPos);
    shader->uVector3("lightPos", 0.0f, 0.0f, 3.0f);
    wintermute->Draw(shader);
}
