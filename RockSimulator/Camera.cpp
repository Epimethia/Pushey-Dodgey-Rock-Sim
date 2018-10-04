//	This include.
#include "Camera.h"


//	Library includes.


//	Local includes.


//	Static variables.
std::shared_ptr<Camera> Camera::s_pInstance;


//	Singleton getter method.
std::shared_ptr<Camera> Camera::GetInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = std::shared_ptr<Camera>(new Camera());
	}
	return s_pInstance;
}

//	Singleton destruction method.
void Camera::DestroyInstance()
{
	//	Calls delete on the pointer.
	s_pInstance.reset();
	//s_pSceneManager = nullptr;
}

//	Default constructor.
Camera::Camera()
{
	// Default camera position
	m_vCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_vCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vUpVec = glm::vec3(0.0, 1.0f, 0.0f);
	m_fCameraSpeed = 0.25f;
}

//	Default destructor.
Camera::~Camera()
{
	//	No pointers to call delete on.
}

//	Return view matrics.
const glm::mat4& Camera::GetView()
{
	return m_mView;
}

const glm::mat4& Camera::GetProj()
{
	return m_mProj;
}

const glm::vec3& Camera::GetPos()
{
	return m_vCameraPos;
}

void Camera::SetProj(int _ScreenWidth, int _ScreenHeight)
{
	m_mProj = glm::ortho(
		0.0f,		// Left
		(float)_ScreenWidth / 100,		// Right
		0.0f,		// Bottom
		(float)_ScreenHeight / 100,		// Top		
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
	m_mView = glm::lookAt(m_vCameraPos,
						 m_vCameraPos + m_vCameraFront,
						 m_vUpVec);
}

void Camera::MoveLeft()
{
	m_vCameraPos -= glm::normalize(glm::cross(m_vCameraFront, m_vUpVec)) * m_fCameraSpeed;
}

void Camera::MoveRight()
{
	m_vCameraPos += glm::normalize(glm::cross(m_vCameraFront, m_vUpVec)) * m_fCameraSpeed;
}

