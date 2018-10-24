#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__
//	Library includes.
#include <memory>
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>


//	Local includes.
enum HEALTH{
	FULL,
	HALF
};

class Sprite;


class C_HealthBar
{
public:
	C_HealthBar();
	~C_HealthBar();
	C_HealthBar(const char * _Filepath_Full, const char*  _Filepath_Half);
	void SetHealth(HEALTH _HealthVal);
	void SetPosition(glm::vec3& _Position);
	void SetScale(glm::vec3& _Scale);
	void Render();
	

private:
	std::shared_ptr<Sprite> m_Sprite;
	
	std::shared_ptr<Sprite> m_HealthBarFull;
	std::shared_ptr<Sprite> m_HealthBarHalf;

	glm::vec3 m_vPosition{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 m_vScale{ glm::vec3(1.0f, 0.1f, 0.0f) };

	// Variables for Debug Drawing
	GLuint m_iVAO;	//	uint
	GLuint m_iVBO;	//	uint
	GLuint m_iProgram;	//	uint

protected:


};

#endif