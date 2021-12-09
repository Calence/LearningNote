#pragma once

#include "IRenderObj.h"
#include <glad/glad.h>
#include "Shader.h"

class Rect : public IRenderObj
{
public:
	Rect();
	~Rect();
	virtual void Init();
	virtual void Release();
	virtual void Tick(float fDetal);
	virtual void Render();

private:
	GLuint		m_nVAO;
};