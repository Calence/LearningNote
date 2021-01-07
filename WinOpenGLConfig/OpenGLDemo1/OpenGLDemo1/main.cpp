#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static const int WIDTH = 800;
static const int HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw 创建窗口
	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLDemo1", NULL, NULL);
	if (NULL == pWindow)
	{
		cout << "Failed to create GLFW Window." << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pWindow);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

	 // render loop
	while (!glfwWindowShouldClose(pWindow))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(1, 0, 0, 1);
		glfwSwapBuffers(pWindow); // 交换颜色缓冲
		glfwPollEvents();//检查有没有触发什么事件
	}

	//正确释放/删除之前的分配的所有资源
	glfwTerminate();

	system("pause");
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}