#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <vector>

const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 vPos = glm::vec3(0),glm::vec3 vLookAt = glm::vec3(0,0,-5), glm::vec3 vUp = glm::vec3(0,1,0))
		: m_vPos(vPos)
		, m_vLookAt(vLookAt)
		, m_vUp(vUp)
	{
	}
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(m_vPos, m_vLookAt, m_vUp);
	}
	glm::vec3 GetPos()const
	{
		return m_vPos;
	}

// 	void updateCameraVectors(float fYaw, float fPitch)
// 	{
// 		// calculate the new Front vector
// 		glm::vec3 front;
// 		front.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
// 		front.y = sin(glm::radians(fPitch));
// 		front.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));
// 		m_vFront = glm::normalize(front);
// 		// also re-calculate the Right and Up vector
// 		m_vRight = glm::normalize(glm::cross(m_vFront, m_vWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
// 		m_vUp = glm::normalize(glm::cross(m_vRight, m_vFront));
// 	}
private:
	glm::vec3 m_vPos;
	glm::vec3 m_vLookAt;
	glm::vec3 m_vUp;

};