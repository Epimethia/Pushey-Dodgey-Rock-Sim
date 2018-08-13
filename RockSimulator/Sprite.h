#pragma once
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
	GLuint m_program;	
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_ebo;
	GLuint m_texture;	
	ShaderLoader m_shaderLoader;
};

