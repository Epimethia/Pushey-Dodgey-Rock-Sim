#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__
//	Library includes.
#include <memory>
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>


//	Local includes.


class Sprite;


class C_HealthBar
{
public:
	C_HealthBar();
	~C_HealthBar();
	C_HealthBar(const char* _Filepath);
	void SetSprite(const char* _Filepath);
	void SetPosition(glm::vec3& _Position);
	void SetScale(glm::vec3& _Scale);
	void SetRotation(float& _Angle);
	void SetRotation(glm::vec3& _Axis);
	void SetRotation(float& _Angle, glm::vec3& _Axis);
	glm::vec3& GetScale();
	void Render();
	

private:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_vPosition{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 m_Scale{ glm::vec3(1.0f, 0.1f, 0.0f) };
	glm::vec3 m_RotationAxis{ glm::vec3(0.0f, 0.0f, 1.0f) };
	float m_fRotationAngle{ 0.0f };

	// Variables for Debug Drawing
	GLuint m_iVAO;	//	uint
	GLuint m_iVBO;	//	uint
	GLuint m_iProgram;	//	uint



protected:


};

#endif