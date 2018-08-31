#include "Utilities.h"

#pragma once
class Camera
{
#pragma region Singleton
public:
	static std::shared_ptr<Camera> GetInstance();
	static void DestroyInstance();
	~Camera();
	/*!!!!!!!!! YOU SHOULD NOT BE CALLING THIS DIRECTLY !!!!!!!*/
	Camera();
private:
	static std::shared_ptr<Camera> s_pCamera;
	Camera(Camera const&);
	void operator=(Camera const&);
	
#pragma endregion

public:	
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
	glm::mat4 m_mView;
	glm::mat4 m_mProj;
	glm::vec3 m_vCameraPos;
	glm::vec3 m_vCameraFront;
	glm::vec3 m_vUpVec;
	float m_fCameraSpeed;
};

