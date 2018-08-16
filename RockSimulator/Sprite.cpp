#include "Sprite.h"
#include "Camera.h"
#include <assert.h>


Sprite::Sprite()
{
	
}


Sprite::~Sprite()
{
}

void Sprite::Initialize(const char * _TextureFilepath)
{	
	
	GLfloat m_vertices[32] = {
		// Positions					    // Colors					// Tex Coords
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, // Top Left
		1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f, // Top Right
		1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Bottom Left
	};

	//GLfloat m_vertices[32] = {
	//	// Positions					    // Colors					// Tex Coords
	//	-1.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, // Top Left
	//	1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f, // Top Right
	//	1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f, // Bottom Right
	//	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Bottom Left
	//};

	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};
	
	m_program = m_shaderLoader.CreateProgram("Resources\\Shaders\\VertexShader.vs",
		"Resources\\Shaders\\FragmentShader.fs");

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	int width, height;
	unsigned char* image = SOIL_load_image(
		_TextureFilepath, // File path/name 
		&width, // Output for the image width
		&height, // Output for the image height
		0, // Output for number of channels
		SOIL_LOAD_RGBA); // Load RGBA values only
	glTexImage2D(
		GL_TEXTURE_2D, // Type of texture
		0, // Mipmap level, 0 for base
		GL_RGBA, // Number of color components in texture
		width, // Width of the texture
		height, // Height of the texture
		0, // This value must be 0
		GL_RGBA, // Format for the pixel data
		GL_UNSIGNED_BYTE, // Data type of the pixel data
		image); // Pointer to image data in memory
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(m_vertices),
		m_vertices,
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		8 * sizeof(GLfloat), // Stride of the single vertex(pos + color)
		(GLvoid*)(0 * sizeof(GLfloat))); // Offset from beginning of Vert
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		8 * sizeof(GLfloat), // Stride of the single vertex(pos + color)
		(GLvoid*)(3 * sizeof(GLfloat))); // Offset from beginning of Vert	
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2, // Layout location on vertex shader
		2, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		8 * sizeof(GLfloat), // Stride of the single vertex(pos + color)
		(GLvoid*)(6 * sizeof(GLfloat))); // Offset from beginning of Vert	
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);
}

void Sprite::Update()
{
	
}

void Sprite::Render(glm::mat4 _ModelMatrix)
{
	// Set Culling and Use program
	glCullFace(GL_BACK); // Cull the Back faces
	glFrontFace(GL_CW); // Front face is Clockwise order
	glEnable(GL_CULL_FACE); // Turn on the back face culling	
	glUseProgram(m_program);

	// Pass mvp to shader
	glm::mat4 MVP = Camera::GetInstance()->GetProj() * Camera::GetInstance()->GetView() * _ModelMatrix;
	GLint MVPloc = glGetUniformLocation(m_program, "MVP");
	glUniformMatrix4fv(MVPloc, 1, GL_FALSE, value_ptr(MVP));

	// Pass texture to shader
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glUniform1i(glGetUniformLocation(m_program, "tex"), 0);

	// Bind vao and draw object, unbind vao
	glBindVertexArray(m_vao);		
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
	glBindVertexArray(0);
}


