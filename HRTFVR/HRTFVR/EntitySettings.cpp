#pragma once
#include "EntitySettings.h"

EntitySettings::EntitySettings(){

	struct Setting monkey;
	monkey.mesh = "./res/meshes/monkey.obj";
	monkey.texture = "./res/textures/bricks.jpg";
	
	struct Setting cube;
	cube.mesh = "./res/meshes/cube.obj";
	cube.texture = "./res/textures/cube-texture.jpg";

	struct Setting teapot;
	teapot.mesh = "./res/meshes/cube.obj";
	teapot.texture = "./res/textures/cube-texture.bmp";

	m_settings["cube"] = cube;
	m_settings["monkey"] = monkey;
	m_settings["teapot"] = teapot;

}

EntitySettings::~EntitySettings(){

}

EntitySettings::Setting EntitySettings::Get(std::string name){
	return m_settings[name];
}