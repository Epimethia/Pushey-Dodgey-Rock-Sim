#pragma once
#include "Utilities.h"
#include "ShaderLoader.h"

class Sprite;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	// Pure Virtual Functions
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual glm::vec2 GetPosition() = 0;
	virtual void DrawDebug();

	// Entity Functions


protected:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationAxis;

	// Physics Variables
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;


private:
	// Member Variables

	// Variables for Debug Drawing
	GLuint m_iVAO;	//	uint
	GLuint m_iVBO;	//	uint
	GLuint m_iProgram;	//	uint
	ShaderLoader m_ShaderLoader;	//	ShaderLoader instance.
};

