#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();

	// Pure Virtual Functions
	virtual void Render() = 0;
	virtual void Update() = 0; 
	virtual void Initialize() = 0;

	// Entity Functions

private:
	// Member Variables
};

