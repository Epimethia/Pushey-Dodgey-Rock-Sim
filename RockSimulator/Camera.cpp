#include "Camera.h"


Camera::Camera()
{
	// Default camera position
	m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_upVec = glm::vec3(0.0, 1.0f, 0.0f);
	m_fCameraSpeed = 0.25f;
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetView()
{
	return m_view;
}

glm::mat4 Camera::GetProj()
{
	return m_proj;
}

void Camera::SetProj(int _screenWidth, int _screenHeight)
{
	m_proj = glm::ortho(
		0.0f,					// Left
		(float)_screenWidth,	// Right
		0.0f,					// Top
		(float)_screenHeight,   // Bottom
		0.1f,					// Near
		100.0f);				// Far
}

void Camera::Update()
{
	m_view = glm::lookAt(m_cameraPos,
						 m_cameraPos + m_cameraFront,
						 m_upVec);
}

void Camera::MoveLeft()
{
	m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_upVec)) * m_fCameraSpeed;
}

void Camera::MoveRight()
{
	m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_upVec)) * m_fCameraSpeed;
}

