#include <Game.h>

bool updatable = false;

gpp::Vector3 v3;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,0,-8);
	glEnable(GL_CULL_FACE);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0f, 0.5f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f); //1
		glVertex3f(1.0f, -1.0f, 1.0f); //2
		glVertex3f(1.0f, 1.0f, 1.0f); //3                 2

		glVertex3f(-1.0f, -1.0f, 1.0f); //1
		glVertex3f(1.0f, 1.0f, 1.0f); //3 
		glVertex3f(-1.0f, 1.0f, 1.0f); //4           1

		glVertex3f(-1.0f, 1.0f, 1.0f); //4
		glVertex3f(1.0f, 1.0f, 1.0f); //3            5
		glVertex3f(1.0f, 1.0f, -1.0f); //7

		glVertex3f(1.0f, 1.0f, -1.0f); //7
		glVertex3f(-1.0f, 1.0f, -1.0f); //8
		glVertex3f(-1.0f, 1.0f, 1.0f); //4               11

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f); //8
		glVertex3f(1.0f, 1.0f, -1.0f); //7
		glVertex3f(1.0f, -1.0f, -1.0f); //6

		glColor3f(0.0f, 0.0f, 0.5f);
		glVertex3f(1.0f, -1.0f, -1.0f); //6              7
		glVertex3f(-1.0f, -1.0f, -1.0f); //5
		glVertex3f(-1.0f, 1.0f, -1.0f); //8

		glVertex3f(1.0f, -1.0f, -1.0f); //6
		glVertex3f(-1.0f, -1.0f, 1.0f); //1            9
		glVertex3f(-1.0f, -1.0f, -1.0f); //5

		glColor3f(0.5f, 1.0f, 0.5f);
		glVertex3f(-1.0f, -1.0f, 1.0f);//1 
		glVertex3f(1.0f, -1.0f, -1.0f); //6
		glVertex3f(1.0f, -1.0f, 1.0f); //2

		glVertex3f(1.0f, 1.0f, -1.0f); //7
		glVertex3f(1.0f, -1.0f, 1.0f); //2
		glVertex3f(1.0f, -1.0f, -1.0f); //6           3

		glColor3f(0.5f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f); //7            4
		glVertex3f(1.0f, 1.0f, 1.0f); //3 
		glVertex3f(1.0f, -1.0f, 1.0f); //2

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f); //5
		glVertex3f(-1.0f, -1.0f, 1.0f); //1                   12
		glVertex3f(-1.0f, 1.0f, 1.0f); //4

		glVertex3f(-1.0f, 1.0f, -1.0f); //8
		glVertex3f(-1.0f, -1.0f, -1.0f); //5                6
		glVertex3f(-1.0f, 1.0f, 1.0f); //4
	}

	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		//glLoadIdentity();
		glRotatef(rotationAngle += 0.1f, 0.0f, 0.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		//glLoadIdentity();
		glRotatef(rotationAngle += 0.1f, 0.0f, 1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		//glLoadIdentity();
		glRotatef(rotationAngle += 0.1f, 1.0f, 0.0f, 0.0f);
	}

	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	//glLoadIdentity();
	//glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Y Axis

	glCallList(1);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}