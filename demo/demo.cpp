// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <common/config.h>
#include <common/renderer.h>
#include <common/camera.h>
#include <common/scene.h>
#include <common/sprite.h>

int main( void )
{
	Renderer renderer;

	Scene* scene = new Scene();

	double xpos, ypos;

	Sprite* pencils = new Sprite("assets/pencils.tga");
	pencils->position = glm::vec3(900.0f, 300.0f, 0.0f);


	scene->addSprite(pencils);

	do {
		// get deltaTime and update camera
		float dt = renderer.updateDeltaTime();
		scene->camera()->computeViewMatrixFromInput(renderer.window(), dt);

		// Update the scene
		scene->update(dt); // TODO make subclass for Scene (and make Scene abstract?)
		glfwGetCursorPos(renderer.window(), &xpos, &ypos);
		if (glfwGetKey(renderer.window(), GLFW_KEY_P))
		{
			pencils->position.x = xpos;
			pencils->position.y = ypos;
		}


		// Render the scene
		renderer.renderScene(scene);
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(renderer.window()) == 0 );

	fstream MyFile;
	MyFile.open("test.txt", fstream::app);
	if (MyFile.is_open())
	{
		MyFile << pencils;
		MyFile.close();
	}

	delete scene;

	return 0;
}
