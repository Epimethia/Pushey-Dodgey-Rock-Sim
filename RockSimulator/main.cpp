//	Library includes.
#include <time.h>

//	Local includes.
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "SceneManager.h"
#include "Utilities.h"
#include "FrameBuffer.h"
#include <vld.h>

SceneManager* g_pSceneManager{ nullptr };
FrameBuffer* exampleFrameBuffer = new FrameBuffer();

void Update();
void Render();
void ExitFunction();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	glutCreateWindow("Pushy Dodgey Rock Simulator");
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	std::srand(static_cast<unsigned int>(time(NULL)));

	// Initialize the starting scene
	SceneManager::GetInstance()->InitializeScene(MENU_SCENE);
	// Set the starting scene
	SceneManager::GetInstance()->SetCurrentScene(MENU_SCENE);
	// Init frame buffer
	exampleFrameBuffer->Initialize();

	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();

	ExitFunction();

	return 0;
}

void Render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	exampleFrameBuffer->BindFrameBuffer(); // has clearing in here

	SceneManager::GetInstance()->RenderCurrentScene();

	exampleFrameBuffer->Render();
	glutSwapBuffers();
}

void Update()
{
	SceneManager::GetInstance()->UpdateCurrentScene();
	glutPostRedisplay();
}

void ExitFunction()
{
	delete exampleFrameBuffer;
	exampleFrameBuffer = nullptr;
	SceneManager::DestroyInstance();
	ShaderLoader::DestroyInstance();
}