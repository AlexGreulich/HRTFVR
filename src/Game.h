#ifndef HRTFVR_GAME_H
#define HRTFVR_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Display.h"
#include "Shader.h"
#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Loader.h"

class Game
{
public:
	Game(Display *display);
	void Update();
	void HandleKey(int key, int scancode, int action, int mods);
	void HandleKeys();
	void HandleMouse(double xpos, double ypos);
	virtual ~Game();
protected:
private:
	const double MOVE_SPEED = 2.0f;
	const double ROTATE_SPEED = 0.003f;
	const double PITCH_SPEED = 0.003f;
	const double INVERT_Y_AXIS_MULTIPLIER = -1; // 1  ||  -1
	const int CREATE_TIMEOUT = 40;

	Loader* m_loader;
	Display* m_display;
	Camera* m_camera;
	Shader* m_shader;
	EntityManager* m_entityManager;


	int m_xpos;
	int m_ypos;

	double m_timer;
	double m_createTimer;
	double m_deltaTime;
};



#endif