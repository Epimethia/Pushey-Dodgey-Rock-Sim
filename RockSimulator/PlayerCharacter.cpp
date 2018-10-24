#include "PlayerCharacter.h"
#include "Sprite.h"
#include "Physics.h"
#include "Camera.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"

PlayerCharacter::PlayerCharacter()
{
	m_Sprite = std::make_shared<Sprite>();	
	m_Scale = glm::vec3(0.3f, 0.3f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fVibrationRate = 0.0f;
	m_fHealth = 100.0f;
	m_bPlayerDead = false;

	// Physics
	b2FixtureDef fixtureDef;	
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(8.0f, 4.5f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(0.2f, 0.25f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 3.0f;
	m_body->CreateFixture(&fixtureDef);

	Bullet = nullptr;
	m_bDebugDrawEnabled = false;
	m_bPlayerAccelerating = false;
}

void PlayerCharacter::InitializeDebugDraw()
{
	// Check that the shape has vertices
	if (1 > m_shape.m_count)
	{
		return;
	}

	m_iProgram = ShaderLoader::GetInstance().CreateProgram("Resources\\Shaders\\Vertex_DebugShader.vs",
		"Resources\\Shaders\\Fragment_DebugShader.fs");
	glm::vec3 Color = glm::vec3(1.0f, 0.0f, 0.0f);

	//translating the vertices supplied by Box2D into vertices usable by GLEW
	float verts[24];
	int CurrentIndex = 0;
	for (int i = 0; i < m_shape.m_count; i++)
	{
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
}

PlayerCharacter::~PlayerCharacter()
{
	//CLEAR UP ALL THE POINTERS
	delete Bullet;
	Bullet = nullptr;
}

void PlayerCharacter::Initialize()
{	
	if (nullptr == m_kcPlayerTexture)
	{
		m_Sprite->Initialize("Resources/Images/Player_Sprite.png");
	}
	else
	{
		m_Sprite->Initialize(m_kcPlayerTexture);
	}	
	InitializeDebugDraw();
}

void PlayerCharacter::TakeDamage()
{
	//SoundManager::GetInstance()->SoundTakeDamage();
	m_fHealth -= 50.0f;
	std::cout << m_fHealth << std::endl;	
}

b2Body * PlayerCharacter::GetBody() const
{
	return m_body;
}

void PlayerCharacter::Render()
{		
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) * 
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);

	//drawing the debug if enabled
	if (m_bDebugDrawEnabled) 
	{
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

	if (Bullet)
	{
		Bullet->Render();
	};
}

void PlayerCharacter::Update()
{
	if (0.0001f > m_fHealth)
	{
		m_bPlayerDead = true;
	}

	// Screen wrapping
	if (m_body->GetPosition().x < -0.4f) m_body->SetTransform(b2Vec2(16.5f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().x > 16.5f) m_body->SetTransform(b2Vec2(-0.4f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().y < -0.4f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, 9.4f), m_body->GetAngle());
	if (m_body->GetPosition().y > 9.5f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, -0.4f), m_body->GetAngle());

	m_fVibrationRate *= 0.90f;
	m_body->SetLinearVelocity(0.995f * m_body->GetLinearVelocity());
	m_body->SetAngularVelocity(0.975f * m_body->GetAngularVelocity());

	if (nullptr != Bullet)
	{
		if (Bullet->m_bValid)
		{
			Bullet->Update();
		}
		else
		{
			Bullet = nullptr;
		};
	};

}

//Update Overload
//Moves the player character by the input Translate
void PlayerCharacter::AddVelocity(const float& _Speed)
{
	m_body->ApplyForceToCenter(
	b2Vec2(m_body->GetWorldVector(b2Vec2(0, 1)).x * _Speed,
		   m_body->GetWorldVector(b2Vec2(0, 1)).y * _Speed),
		   true);

	// Limit/Clamp velocity
	b2Vec2 LinearVelocity = m_body->GetLinearVelocity();
	m_body->SetLinearVelocity(b2Vec2(glm::clamp(LinearVelocity.x, -4.1f, 4.1f), glm::clamp(LinearVelocity.y, -4.1f, 4.1f)));

	m_fVibrationRate = 3.0f;
}

//	Radians or Degrees?
void PlayerCharacter::AddRotation(const float& _Angle)
{	
	m_body->ApplyTorque(_Angle, true);
}

void PlayerCharacter::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

float PlayerCharacter::GetCurrentSpeed()
{
	b2Vec2 speed = m_body->GetLinearVelocity();
	return std::pow(speed.Normalize(), 2.0f);
}

void PlayerCharacter::Shoot()
{
	//getting the position of the bullet spawn
	if (nullptr == Bullet)
	{
		b2Vec2 Direction = m_body->GetWorldVector(b2Vec2(0, 1));
		Direction.Normalize();
		Direction *= 0.7f;
		b2Vec2 pos = m_body->GetPosition() + Direction;
		Bullet = new Projectile(pos, Direction, m_body->GetAngle());
		SoundManager::GetInstance()->SoundPew();
	}
}

void PlayerCharacter::LinkScore(short* _Deaths)
{
	m_pDeaths = _Deaths;
}

void PlayerCharacter::Respawn()
{		
	assert(m_body != nullptr);

	*m_pDeaths += 1;
	ResetPlayer();
}

void PlayerCharacter::ResetPlayer()
{
	m_bPlayerDead = false;
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	m_body->SetAngularVelocity(0.0f);
	m_body->SetTransform(b2Vec2(m_spawnPosition.x, m_spawnPosition.y), 0.0f);
	m_fHealth = 100.0f;
}

float PlayerCharacter::GetHealth()
{
	return m_fHealth;
}

void PlayerCharacter::SetPlayerTexture(const char * _texturePath)
{
	m_kcPlayerTexture = _texturePath;
}
