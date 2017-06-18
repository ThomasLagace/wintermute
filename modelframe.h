#pragma once
#include <k5/k5.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ModelFrame : public IFrame {
public:
	virtual void Init(CEngine* e) override;
	virtual void Cleanup() override;

	virtual void Pause() override;
	virtual void Resume() override;

	virtual void ProcessInput(bool* keyboard, bool* mouse, double mxpos, double mypos) override;
	virtual void Loop() override;
	virtual void Render() override;

	static ModelFrame& Instance() {
		static ModelFrame instance;
		return instance;
	}

protected:
	ModelFrame() = default;
	ModelFrame(const ModelFrame&) = delete;
	ModelFrame(ModelFrame&&) = delete;
	void operator=(const ModelFrame&) = delete;
	void operator=(ModelFrame&&) = delete;

private:	
	Model wintermute = Model("models/wintermute.obj");

	Shader shader = Shader("shaders/wintermute.vs",
				"shaders/wintermute.frag");

	Camera camera = Camera(glm::vec3(13.8f, 4.7f, -3.3f), 
			    glm::vec2(175.0f, -7.5f),
			    0.1f, 0.020f);

	glm::mat4 model;
	glm::mat4 proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	
	GLuint texID;
	GLuint vao;
	GLuint vbo;
	Shader skybox = Shader("shaders/cubemap.vs", "shaders/cubemap.frag");
};
