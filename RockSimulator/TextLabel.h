// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	TextLabel.h
// Description	:	Header file defining the TextLabel class

#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "ShaderLoader.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <map>
#include <string>
#include <iostream>

struct Character
{
	GLuint        TextureID;	// Texture ID 
	glm::ivec2    Size;			// Size of glyph
	glm::ivec2    Bearing;		// Positon of glyph 
	GLuint        Advance;		// How far to move for the next character
};

class TextLabel {
public:
	TextLabel(std::string text, std::string font, glm::vec2 pos);
	~TextLabel();

	void Render();
	void SetText(std::string newText) { text = newText; };
	void SetColor(glm::vec3 newColor) { color = newColor; };
	void SetScale(GLfloat newScale) { scale = newScale; };
	void SetPosition(glm::vec2 newPosition) { position = newPosition; };
	glm::vec2 GetPosition();
	std::string GetText();
	GLfloat GetScale();

private:
	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;

	GLuint VAO, VBO, program;
	std::map<GLchar, Character> Characters;
	ShaderLoader shaderLoader;
};
