//	Library includes.


//	Local includes.
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "SceneManager.h"
#include "Utilities.h"


SceneManager* g_pSceneManager{ nullptr };


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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();
	g_pSceneManager = &(*SceneManager::GetInstance());
	// Set the starting scene
	g_pSceneManager->SetCurrentScene(LEVEL1_SCENE);
	// Initialize the starting scene
	g_pSceneManager->InitializeScene(LEVEL1_SCENE);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();
	return 0;
}

void Render()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_pSceneManager->RenderCurrentScene();
	glutSwapBuffers();
}

void Update()
{			
	g_pSceneManager->UpdateCurrentScene();
	glutPostRedisplay();
}