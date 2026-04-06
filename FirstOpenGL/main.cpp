#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "utils.h"


float orangeTriangle[] = {
	-0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.0f,  0.0f, 0.0f,
};

float purpleTriangle[] = {
	 0.0f,  0.0f, 0.0f,
	 0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window,  GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Checks if window was created
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (window == NULL) {
		std::cout << "Window Fail";
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	// Checks if GLAD was initialized
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Loading shaders

	std::string vertSrc = loadShader("vertex.glsl");
	std::string fragSrc1 = loadShader("orange.frag");
	std::string fragSrc2 = loadShader("purple.frag");
	
	const char* vertexShaderSource = vertSrc.c_str();
	const char* fragmentShaderSources[] = { fragSrc1.c_str(), fragSrc2.c_str() };

	// Buffer objects

	unsigned int VAOs[2];
	unsigned int VBOs[2];

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// Setup orangle triangle

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(orangeTriangle), orangeTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Setup purple triangle

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(purpleTriangle), purpleTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex shader

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment shaders

	unsigned int fragmentShaderOrange;
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSources[0], NULL);
	glCompileShader(fragmentShaderOrange);

	unsigned int fragmentShaderPurple;
	fragmentShaderPurple = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderPurple, 1, &fragmentShaderSources[1], NULL);
	glCompileShader(fragmentShaderPurple);

	// Shader programs

	unsigned int shaderProgramOrange;
	shaderProgramOrange = glCreateProgram();
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);

	unsigned int shaderProgramPurple;
	shaderProgramPurple = glCreateProgram();
	glAttachShader(shaderProgramPurple, vertexShader);
	glAttachShader(shaderProgramPurple, fragmentShaderPurple);
	glLinkProgram(shaderProgramPurple);

	// Deleting

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderPurple);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Input Processing
		processInput(window);

		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Display orange triangle
		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Display purple triangle
		glUseProgram(shaderProgramPurple);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// GLFW Commands
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
