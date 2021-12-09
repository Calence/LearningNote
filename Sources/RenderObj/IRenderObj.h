#pragma once

class IRenderObj
{
public:
	IRenderObj(){}
	virtual ~IRenderObj(){}
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Tick(float fDetal) = 0;
	virtual void Render() = 0;
protected:
	int			m_nVertexNum;
};