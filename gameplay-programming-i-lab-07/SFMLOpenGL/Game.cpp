#include <Game.h>

bool updatable = false;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::RotationX(rotationAngle) * m_points[index];
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::RotationY(rotationAngle) * m_points[index];
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::RotationZ(-rotationAngle) * m_points[index];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::Translate(0, -1) * m_points[index];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::Translate(0, 1) * m_points[index];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::Translate(-1, 0) * m_points[index];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::Translate(1, 0) * m_points[index];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::Scale(99.0, 99.0) * m_points[index];
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		for (int index = 0; index < 8; index++)
		{
			m_points[index] = Matrix3::Scale(110.0, 110.0) * m_points[index];
		}
	}

	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0f, 0.5f, 1.0f);
		glVertex3f(m_points[0].m_x, m_points[0].m_y, m_points[0].m_z); // 1
		glVertex3f(m_points[1].m_x, m_points[1].m_y, m_points[1].m_z); // 2
		glVertex3f(m_points[2].m_x, m_points[2].m_y, m_points[2].m_z); // 3                

		glVertex3f(m_points[0].m_x, m_points[0].m_y, m_points[0].m_z); // 1
		glVertex3f(m_points[2].m_x, m_points[2].m_y, m_points[2].m_z); // 3 
		glVertex3f(m_points[3].m_x, m_points[3].m_y, m_points[3].m_z); // 4          

		glVertex3f(m_points[3].m_x, m_points[3].m_y, m_points[3].m_z); // 4
		glVertex3f(m_points[2].m_x, m_points[2].m_y, m_points[2].m_z); // 3           
		glVertex3f(m_points[6].m_x, m_points[6].m_y, m_points[6].m_z); // 7

		glVertex3f(m_points[6].m_x, m_points[6].m_y, m_points[6].m_z); // 7
		glVertex3f(m_points[7].m_x, m_points[7].m_y, m_points[7].m_z); // 8
		glVertex3f(m_points[3].m_x, m_points[3].m_y, m_points[3].m_z); // 4               

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(m_points[7].m_x, m_points[7].m_y, m_points[7].m_z); // 8
		glVertex3f(m_points[6].m_x, m_points[6].m_y, m_points[6].m_z); // 7
		glVertex3f(m_points[5].m_x, m_points[5].m_y, m_points[5].m_z); // 6

		glColor3f(0.0f, 0.0f, 0.5f);
		glVertex3f(m_points[5].m_x, m_points[5].m_y, m_points[5].m_z); // 6             
		glVertex3f(m_points[4].m_x, m_points[4].m_y, m_points[4].m_z); // 5
		glVertex3f(m_points[7].m_x, m_points[7].m_y, m_points[7].m_z); // 8

		glVertex3f(m_points[5].m_x, m_points[5].m_y, m_points[5].m_z); // 6
		glVertex3f(m_points[0].m_x, m_points[0].m_y, m_points[0].m_z); // 1          
		glVertex3f(m_points[4].m_x, m_points[4].m_y, m_points[4].m_z); // 5

		glColor3f(0.5f, 1.0f, 0.5f);
		glVertex3f(m_points[0].m_x, m_points[0].m_y, m_points[0].m_z); // 1 
		glVertex3f(m_points[5].m_x, m_points[5].m_y, m_points[5].m_z); // 6
		glVertex3f(m_points[1].m_x, m_points[1].m_y, m_points[1].m_z); // 2

		glVertex3f(m_points[6].m_x, m_points[6].m_y, m_points[6].m_z); // 7
		glVertex3f(m_points[1].m_x, m_points[1].m_y, m_points[1].m_z); // 2
		glVertex3f(m_points[5].m_x, m_points[5].m_y, m_points[5].m_z); // 6          

		glColor3f(0.5f, 1.0f, 0.0f);
		glVertex3f(m_points[6].m_x, m_points[6].m_y, m_points[6].m_z); // 7           
		glVertex3f(m_points[2].m_x, m_points[2].m_y, m_points[2].m_z); // 3 
		glVertex3f(m_points[1].m_x, m_points[1].m_y, m_points[1].m_z); // 2

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(m_points[4].m_x, m_points[4].m_y, m_points[4].m_z); // 5
		glVertex3f(m_points[0].m_x, m_points[0].m_y, m_points[0].m_z); // 1                 
		glVertex3f(m_points[3].m_x, m_points[3].m_y, m_points[3].m_z); // 4

		glVertex3f(m_points[7].m_x, m_points[7].m_y, m_points[7].m_z); // 8
		glVertex3f(m_points[4].m_x, m_points[4].m_y, m_points[4].m_z); // 5                
		glVertex3f(m_points[3].m_x, m_points[3].m_y, m_points[3].m_z); // 4
	}

	glEnd();
	glEndList();

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