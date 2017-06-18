#include "modelframe.h"

void ModelFrame::Init(CEngine* e) {
	engine = e;

	glfwSetInputMode(engine->wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 

	//
	// Here be dragons
	//

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	int width;
	int height;
	int channels;
	unsigned char* data;
	constexpr const char* fileNames[6] = {
		"env/cwd_rt.JPG",
		"env/cwd_lf.JPG",
		"env/cwd_up.JPG",
		"env/cwd_dn.JPG",
		"env/cwd_bk.JPG",
		"env/cwd_ft.JPG",
	};

	for (GLuint i = 0; i < 6; i++) {
		data = SOIL_load_image(fileNames[i], 
			&width, &height, &channels, 
			SOIL_LOAD_RGB);
		if (data == nullptr) {
			printf("Failed to load texture %s\n", fileNames[i]);
			exit(1);
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB,
				width, height,
				0, GL_RGB, GL_UNSIGNED_BYTE,
				data);
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  		

	float verts[] = {
	    -1.0f,  1.0f, -1.0f,
	    -1.0f, -1.0f, -1.0f,
	     1.0f, -1.0f, -1.0f,
	     1.0f, -1.0f, -1.0f,
	     1.0f,  1.0f, -1.0f,
	    -1.0f,  1.0f, -1.0f,
	
	    -1.0f, -1.0f,  1.0f,
	    -1.0f, -1.0f, -1.0f,
	    -1.0f,  1.0f, -1.0f,
	    -1.0f,  1.0f, -1.0f,
	    -1.0f,  1.0f,  1.0f,
	    -1.0f, -1.0f,  1.0f,

	     1.0f, -1.0f, -1.0f,
	     1.0f, -1.0f,  1.0f,
	     1.0f,  1.0f,  1.0f,
	     1.0f,  1.0f,  1.0f,
	     1.0f,  1.0f, -1.0f,
	     1.0f, -1.0f, -1.0f,
	
	    -1.0f, -1.0f,  1.0f,
	    -1.0f,  1.0f,  1.0f,
	     1.0f,  1.0f,  1.0f,
	     1.0f,  1.0f,  1.0f,
	     1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

	    -1.0f,  1.0f, -1.0f,
	     1.0f,  1.0f, -1.0f,
	     1.0f,  1.0f,  1.0f,
	     1.0f,  1.0f,  1.0f,
	    -1.0f,  1.0f,  1.0f,
	    -1.0f,  1.0f, -1.0f,

	    -1.0f, -1.0f, -1.0f,
	    -1.0f, -1.0f,  1.0f,
	     1.0f, -1.0f, -1.0f,
	     1.0f, -1.0f, -1.0f,
	    -1.0f, -1.0f,  1.0f,
	     1.0f, -1.0f,  1.0f
	};
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
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

	glDepthMask(GL_FALSE);
	skybox.Use();
	skybox.uMatrix4("view", glm::mat4(glm::mat3(camera.GetView())));
	skybox.uMatrix4("proj", proj);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	
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
