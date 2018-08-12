#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "ShaderLoader.h"
#include <memory>

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
	void Render();


private:	
	bool m_SpriteInitialized = false;	
	GLuint m_program;	
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_ebo;
	GLuint m_texture;
	GLfloat m_vertices[32] = {
		// Positions		// Colors				// Tex Coords
		-0.5f, 0.5f,	  0.0f, 0.0f, 1.0f, 0.0f,		0.0f, 0.0f, // Top Left
		0.5f, 0.5f,		  0.0f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f, // Top Right
		0.5f, -0.5f,	  0.0f, 1.0f, 1.0f, 0.0f,		1.0f, 1.0f, // Bottom Right
		-0.5f, -0.5f,	  0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Bottom Left
	};
	ShaderLoader m_shaderLoader;
};

