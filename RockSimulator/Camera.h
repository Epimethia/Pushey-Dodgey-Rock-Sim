#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#pragma once
class Camera
{
public:
	Camera();
	~Camera();
	//Getters
	glm::mat4 GetView();
	glm::mat4 GetProj();
	//Setters	
	void SetProj(int _screenWidth, int _screenHeight);
	//Other functions
	void Update();
	void MoveLeft();
	void MoveRight();
	
private:
	glm::mat4 m_view;
	glm::mat4 m_proj;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_upVec;
	float m_fCameraSpeed;
};

