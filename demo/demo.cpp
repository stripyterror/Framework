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
	float pPositionXS;
	float pPositionYS;
	float pPositionXL;
	float pPositionYL;

	fstream MyFile;
	std::string filename;
	cout << "What do you want your save file to be called? (In case one already exits input file name.)" << endl;
	std::cin >> filename;

	Renderer renderer;

	Scene* scene = new Scene();

	double xpos, ypos;

	Sprite* pencils = new Sprite("assets/pencils.tga");
	pencils->position = glm::vec3(900.0f, 300.0f, 0.0f);


	scene->addSprite(pencils);

	std::ifstream file(filename);

	std::vector<int> pos ;

	int input;
	while (file >> input)
	{
		pos.push_back(input);
	}

	MyFile.open(filename.c_str());
	if (MyFile.is_open())
	{
		pPositionXL = pos[0];
		pPositionYL = pos[1];
		pencils->position = glm::vec3(pPositionXL, pPositionYL, 0.0f);
		MyFile.close();
	}

	for (int test : pos)
	{
		std::cout << test << std::endl;
	}

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

	MyFile.open(filename.c_str(), fstream::out | fstream::trunc);
	if (MyFile.is_open())
	{
		pPositionXS = pencils->position.x;
		pPositionYS = pencils->position.y;

		MyFile << pPositionXS << endl;
		MyFile << pPositionYS << endl;
		MyFile.close();
	}
	else
		cout << "Error! Something went wrong.\n";



	delete scene;

	return 0;
}
