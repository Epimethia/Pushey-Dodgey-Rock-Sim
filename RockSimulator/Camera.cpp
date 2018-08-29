#include "Camera.h"

std::shared_ptr<Camera> Camera::s_pCamera;

std::shared_ptr<Camera> Camera::GetInstance()
{
	if (!s_pCamera)
	{
		s_pCamera = std::shared_ptr<Camera>(new Camera());
	}
	return s_pCamera;
}

void Camera::DestroyInstance()
{
	s_pCamera.reset();
	//s_pSceneManager = nullptr;
}


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

glm::vec3 Camera::GetPos()
{
	return m_cameraPos;
}

void Camera::SetProj(int _screenWidth, int _screenHeight)
{
	m_proj = glm::ortho(
		0.0f,		// Left
		(float)_screenWidth / 100,		// Right
		0.0f,		// Bottom
		(float)_screenHeight / 100,		// Top		
		0.1f,								// Near
		100.0f);							// Far

	//m_proj = glm::ortho(
	//	-(float)_screenWidth / 156.25f,		// Left
	//	(float)_screenWidth / 156.25f,		// Right
	//	-(float)_screenHeight / 100.0f,		// Bottom
	//	(float)_screenHeight / 100.0f,		// Top		
	//	0.1f,								// Near
	//	100.0f);							// Far
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

