#ifndef __CAMERA_H__
#define __CAMERA_H__
//	Library includes.


//	Local includes.
#include "Utilities.h"


class Camera
{
#pragma region Singleton
public:
	static std::shared_ptr<Camera> GetInstance();
	static void DestroyInstance();
	Camera();
	~Camera();

	//Getters
	const glm::mat4& GetView();
	const glm::mat4& GetProj();
	const glm::vec3& GetPos();
	//Setters	
	void SetProj(int _screenWidth, int _screenHeight);
	//Other functions
	void Update();
	void MoveLeft();
	void MoveRight();
	
private:
	static std::shared_ptr<Camera> s_pInstance;
	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;


	glm::mat4 m_mView;
	glm::mat4 m_mProj;
	glm::vec3 m_vCameraPos;
	glm::vec3 m_vCameraFront;
	glm::vec3 m_vUpVec;
	float m_fCameraSpeed;
};

#endif