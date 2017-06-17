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
	float cameraSpeed = 0.05f;
	glm::vec3 cameraPos = glm::vec3(13.8f, 4.7f, -3.3f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float pitch = -7.5f;
	float yaw = 175.0f;
	double lastX, lastY;
	double sensitivity = 0.020;
	
	Model* wintermute;
	Shader* shader;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};
