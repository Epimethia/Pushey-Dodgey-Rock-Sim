#ifndef __SPRITE_H__
#define __SPRITE_H__
//	Library includes.


//	Local includes.
#include "ShaderLoader.h"
#include "Utilities.h"


class Sprite
{
public:
	Sprite();
	~Sprite();
	// Setters

	// Getters	

	// Other functions
	void Initialize(const char * _TextureFilepath);
	void Update();
	void Render(glm::mat4 _ModelMatrix);


private:
	GLuint m_iProgram;	//	uint
	GLuint m_iVBO;	//	uint
	GLuint m_iVAO;	//	uint
	GLuint m_iEBO;	//	uint
	GLuint m_iTexture;	//	uint
};

#endif