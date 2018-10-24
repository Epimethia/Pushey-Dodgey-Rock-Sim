#ifndef __UTILITIES_H__
#define __UTILITIES_H__
//	Library includes.
#include <memory>
#include <vector>
#include <iostream>
#include <random>


//	Local includes.
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Dependencies\Box2D\Box2D.h"


//	Global variables.
const int ki_SCREENWIDTH = 1600;
const int ki_SCREENHEIGHT = 900;
const float kf_NORMALX = static_cast<float>(ki_SCREENHEIGHT) / static_cast<float>(ki_SCREENWIDTH);
const bool kb_UNITTESTS = true;

struct UnitTests
{
	static bool SizeIncreaseCheck(unsigned int _before, // The size of a container before adding
							      unsigned int _after)  // The size of a container after adding
	{
		if (_before == _after) return 0;
		if (_before > _after) return 0;
		if (_before < _after) return 1;
		else return 0;
	}

	static bool ValidCheck(void* _pointer)
	{
		if (_pointer == nullptr) return 0;
		if (_pointer != _pointer) return 0; // only true if _pointer is NaN		
		else return 1;
	}

	static bool ValidProgramCheck(GLuint _program)
	{
		if (_program < 0) return 0;
		if (_program > 10) return 0;
		else return 1;
	}
};

#endif