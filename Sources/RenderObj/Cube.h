#pragma once

#include "IRenderObj.h"
#include <glad/glad.h>
#include "Shader.h"

class Cube : public IRenderObj
{
public:
	Cube();
	~Cube();
	virtual void Init();
	virtual void Release();
	virtual void Tick(float fDetal);
	virtual void Render();

private:
	GLuint		m_nVAO;
};