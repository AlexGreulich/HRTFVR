#ifndef HRTFVR_GAME_CPP
#define HRTFVR_GAME_CPP

#define GLM_FORCE_RADIANS
#include "Game.h"
#include "Logger.h"
#include <glm/glm.hpp>
#include <iostream>

Game::Game(Display *display):
m_display(display),
m_timer(glfwGetTime()),
m_camera(new Camera(
	glm::vec3(0.0, 0.0, 0.0),
	70.0f,
	display->getAspectRatio(),
	0.1f,
	1000.0f
)),
m_loader(new Loader()),
m_scene(new Scene(m_loader, m_camera, &m_timer))
{
}

void Game::Update(){
	// get time diff
	m_deltaTime = glfwGetTime() - m_timer;

	m_wireframeTimer -= m_deltaTime;
	m_fogToggleTimer -= m_deltaTime;
	
	// apply keys to camera view
	HandleKeys();
	
	m_scene->Render();

	// update timer
	m_timer = glfwGetTime();
}

/*
 * Handles a single key input
 */
void Game::HandleKey(int key, int scancode, int action, int mods){
	
	double speed = MOVE_SPEED;

	if (key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(m_display->getWindow(), 1);
		return;
	}

	if( m_fogToggleTimer <= 0 && glfwGetKey(m_display->getWindow(), GLFW_KEY_F) == GLFW_PRESS ){
		Shader* basicShader = ShaderFactory::GetInstance().GetShader("basic");
		basicShader->ToggleFog();
		m_fogToggleTimer = 0.5;

	}

	if( m_wireframeTimer <= 0 && glfwGetKey(m_display->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS ){
		m_display->ToggleWireframeMode();
		m_wireframeTimer = 0.5;
	}

	if( glfwGetKey(m_display->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ){
		speed = MOVE_SPEED * 4;
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_A) == GLFW_PRESS){

		m_camera->MoveLeft(m_deltaTime * speed);
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
		m_camera->MoveRight(m_deltaTime * speed);
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
		m_camera->MoveForward(m_deltaTime * speed);
	}

	if (glfwGetKey(m_display->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
		m_camera->MoveBack(m_deltaTime * speed);
	}

	if ( glfwGetKey(m_display->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS ){
	}

}

/*
 * Gets called from the update method; 
 * we need that to update the keys every frame
 */
void Game::HandleKeys(){
	HandleKey(0, 0, 0, glfwGetKey(m_display->getWindow(), GLFW_MOD_SHIFT));
}

void Game::HandleMouse(double xpos, double ypos){

	double dx = (double) m_xpos - xpos;
	double dy = (double) m_ypos - ypos;

	m_camera->RotateY( dx * ROTATE_SPEED);
	m_camera->Pitch( dy * INVERT_Y_AXIS_MULTIPLIER * PITCH_SPEED);

	m_xpos = xpos;
	m_ypos = ypos;

}

Game::~Game()
{
	delete m_camera;
	delete m_loader;
	delete m_scene;
}


#endif
