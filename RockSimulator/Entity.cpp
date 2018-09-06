#include "Entity.h"
#include "Utilities.h"
#include "Camera.h"


Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::DrawDebug()
{
	// Check that the shape has vertices
	if (m_shape.m_count < 1)
	{
		return;
	}

	m_iProgram = ShaderLoader::GetInstance().CreateProgram("Resources\\Shaders\\Vertex_DebugShader.vs",
		"Resources\\Shaders\\Fragment_DebugShader.fs");
	glm::vec3 Color = glm::vec3(1.0f, 0.0f, 0.0f);

	//translating the vertices supplied by Box2D into vertices usable by GLEW
	float verts[24];
	int CurrentIndex = 0;
	for (int i = 0; i < m_shape.m_count; i++) {
		verts[CurrentIndex++] = (m_shape.m_vertices[i].x); //x
		verts[CurrentIndex++] = (m_shape.m_vertices[i].y); //y
		verts[CurrentIndex++] = 0.0f; //z

									  //color verts
		verts[CurrentIndex++] = Color.x;
		verts[CurrentIndex++] = Color.y;
		verts[CurrentIndex++] = Color.z;
	}

	//generating and binding the buffers
	glGenVertexArrays(1, &m_iVAO);
	glGenBuffers(1, &m_iVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * (6 * m_shape.m_count), verts, GL_STATIC_DRAW);
	glBindVertexArray(m_iVAO);

	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		6 * sizeof(GLfloat), // Stride of the single vertex(pos + color)
		(GLvoid*)(0 * sizeof(GLfloat))); // Offset from beginning of Vert
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		6 * sizeof(GLfloat), // Stride of the single vertex(pos + color)
		(GLvoid*)(3 * sizeof(GLfloat))); // Offset from beginning of Vert	
	glEnableVertexAttribArray(1);

	// RENDER
	// Set Culling and Use program
	glCullFace(GL_BACK); // Cull the Back faces
	glFrontFace(GL_CW); // Front face is Clockwise order
	glEnable(GL_CULL_FACE); // Turn on the back face culling	
	glUseProgram(m_iProgram);

	// Pass mvp to shader
	glm::mat4 Model =
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis);


	glm::mat4 MVP = Camera::GetInstance()->GetProj() * Camera::GetInstance()->GetView() * Model;
	GLint MVPloc = glGetUniformLocation(m_iProgram, "MVP");
	glUniformMatrix4fv(MVPloc, 1, GL_FALSE, value_ptr(MVP));

	//// Bind vao and draw object, unbind vao
	glBindVertexArray(m_iVAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);

}
