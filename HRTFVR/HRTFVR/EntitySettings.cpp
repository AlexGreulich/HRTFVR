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
	teapot.mesh = "./res/meshes/tpt.obj";
	teapot.texture = "./res/textures/bricks.jpg";

	struct Setting octahedron;
	octahedron.mesh = "./res/meshes/octahedron.obj";
	octahedron.texture = "./res/textures/bricks.jpg";

	struct Setting skyscraper;
	skyscraper.mesh = "./res/meshes/skscr.obj";
	skyscraper.texture = "./res/textures/bricks.jpg";

	m_settings["cube"] = cube;
	m_settings["monkey"] = monkey;
	m_settings["teapot"] = teapot;
	m_settings["octahedron"] = octahedron;
	m_settings["skyscraper"] = skyscraper;

}

EntitySettings::~EntitySettings(){

}

EntitySettings::Setting EntitySettings::Get(std::string name){
	return m_settings[name];
}