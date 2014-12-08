#include "Game.h"
#include <glm.hpp>
#include <iostream>

Game::Game(Display *display)
{
	m_timer = glfwGetTime();
	m_entityManager = new EntityManager(&m_timer);
	m_display = display;
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, (float)display->getWidth() / (float)display->getHeight(), 0.1f, 100.0f);
	m_shader = new Shader("./res/shaders/basic.vertex", "./res/shaders/basic.fragment");
	
}

void Game::Update(){
	m_createTimer--;
	// get time diff
	m_deltaTime = glfwGetTime() - m_timer;

	// apply keys to camera view
	HandleKeys();
	
	// bind & update shader
	m_shader->Bind();

	m_entityManager->Render(m_shader, m_camera);

	// update timer
	m_timer = glfwGetTime();
}

/*
 * Handles a single key input
 */
void Game::HandleKey(int key, int scancode, int action, int mods){
	
	if (key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(m_display->getWindow(), 1);
		return;
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
		m_camera->MoveLeft(m_deltaTime * MOVE_SPEED);
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
		m_camera->MoveRight(m_deltaTime * MOVE_SPEED);
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
		m_camera->MoveForward(m_deltaTime * MOVE_SPEED);
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
		m_camera->MoveBack(m_deltaTime * MOVE_SPEED);
	}

	if ( glfwGetKey(m_display->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS ){
		if (m_createTimer > 0){
			std::cout << "cannot create: timer " << m_createTimer << std::endl;
			return;
		}
		glm::vec3 fwd = m_camera->GetForward();
		fwd.x = fwd.x * 20;
		m_entityManager->CreateEntity("monkey", fwd, true);
		m_createTimer = CREATE_TIMEOUT;
	}

}

/*
 * Gets called from the update method; 
 * we need that to update the keys every frame
 */
void Game::HandleKeys(){
	HandleKey(0, 0, 0, 0);
}

void Game::HandleMouse(int xpos, int ypos){

	double dx = (double) m_xpos - xpos;
	double dy = (double) m_ypos - ypos;

	m_camera->RotateY( dx * ROTATE_SPEED);
	m_camera->Pitch( dy * INVERT_Y_AXIS_MULTIPLIER * PITCH_SPEED);

	m_xpos = xpos;
	m_ypos = ypos;

}

Game::~Game()
{
	delete m_entityManager;delete m_camera;
	delete m_shader;
	
}
