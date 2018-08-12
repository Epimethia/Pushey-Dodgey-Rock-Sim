#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "SceneManager.h"
#include "Utilities.h"

void Update();
void Render();

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	glutCreateWindow("OpenGL First Window");
	glEnable(GL_MULTISAMPLE);
	glewInit();
		
	// Set the starting scene
	SceneManager::GetInstance()->SetCurrentScene(LEVEL1_SCENE);
	// Initialize the starting scene
	SceneManager::GetInstance()->InitializeScene(LEVEL1_SCENE);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}

void Render()
{	
	SceneManager::GetInstance()->RenderCurrentScene();
}

void Update()
{			
	SceneManager::GetInstance()->UpdateCurrentScene();

	glutPostRedisplay();
}