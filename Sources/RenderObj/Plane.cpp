#include "Plane.h"
#include <GLFW/glfw3.h>


Plane::Plane(Shader	shader)
	:IRenderObj()
	, m_Shader(shader)
{
	m_nVertexNum = 0;
}

Plane::~Plane()
{

}

void Plane::Init()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float planeVertices[] = {
		// positions            // normals         // texcoords
		25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
		-25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,

		25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
		-25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
		25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 10.0f
	};
	m_nVertexNum = sizeof(planeVertices) /sizeof(float)/ 8;

	//生成VAO数组
	glGenVertexArrays(1, &m_nVAO);
	//绑定VAO
	glBindVertexArray(m_nVAO);

	GLuint nVBO;
	//生成顶点缓冲对象
	glGenBuffers(1, &nVBO);
	glBindBuffer(GL_ARRAY_BUFFER,nVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	glBindVertexArray(0);

}

void Plane::Release()
{

}

void Plane::Tick(float fDetal)
{

}

void Plane::Render()
{
	glBindVertexArray(m_nVAO);
	glDrawArrays(GL_TRIANGLES, 0, m_nVertexNum);
	glBindVertexArray(0);
}
