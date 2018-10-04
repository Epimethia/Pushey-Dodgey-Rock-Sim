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

#endif