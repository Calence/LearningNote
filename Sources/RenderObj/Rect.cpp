#include "Rect.h"
#include <GLFW/glfw3.h>


Rect::Rect()
	:IRenderObj()
{
	m_nVertexNum = 0;
}

Rect::~Rect()
{

}

void Rect::Init()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	const int NUM_COL = 5;
	m_nVertexNum = sizeof(quadVertices) / sizeof(float) / NUM_COL;

	//生成VAO数组
	glGenVertexArrays(1, &m_nVAO);
	//绑定VAO
	glBindVertexArray(m_nVAO);

	GLuint nVBO;
	//生成顶点缓冲对象
	glGenBuffers(1, &nVBO);
	glBindBuffer(GL_ARRAY_BUFFER,nVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, NUM_COL * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, NUM_COL * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);

}

void Rect::Release()
{

}

void Rect::Tick(float fDetal)
{

}

void Rect::Render()
{
	glBindVertexArray(m_nVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nVertexNum);
	glBindVertexArray(0);
}
