#include "Game.h"
#include <glm.hpp>
#include <iostream>

Game::Game(Display *display):
m_shader("./res/shaders/basic"),
m_entityManager()
{
	m_display = display;
	m_transform = new Transform();
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)display->getWidth() / (float)display->getHeight(), 0.1f, 100.0f);
	m_timer = glfwGetTime();
}

void Game::Update(){
	// get time diff
	m_deltaTime = glfwGetTime() - m_timer;

	// apply keys to camera view
	HandleKeys();
	
	// bind & update shader
	m_shader.Bind();
	m_shader.Update(m_transform, m_camera);

	//m_monkey.Draw();
	m_entityManager.Render();

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
	
}
