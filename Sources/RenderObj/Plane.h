#pragma once

#include "IRenderObj.h"
#include <glad/glad.h>
#include "Shader.h"

class Plane : public IRenderObj
{
public:
	Plane(Shader	shader);
	~Plane();
	virtual void Init();
	virtual void Release();
	virtual void Tick(float fDetal);
	virtual void Render();

private:
	GLuint		m_nVAO;
	Shader		m_Shader;
};