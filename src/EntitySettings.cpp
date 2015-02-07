#ifndef HRTFVR_ENTITY_SETTINGS_CPP
#define HRTFVR_ENTITY_SETTINGS_CPP

#include "EntitySettings.h"

EntitySettings::EntitySettings(){

	struct Setting monkey;
	monkey.mesh = "resources/meshes/monkey.obj";
	monkey.texture = "resources/textures/bricks.jpg";
	
	struct Setting cube;
	cube.mesh = "resources/meshes/cube.obj";
	cube.texture = "resources/textures/cube-texture.jpg";

	struct Setting teapot;
	teapot.mesh = "resources/meshes/tpt.obj";
	teapot.texture = "resources/textures/bricks.jpg";

	struct Setting octahedron;
	octahedron.mesh = "resources/meshes/octahedron.obj";
	octahedron.texture = "resources/textures/bricks.jpg";

	struct Setting skyscraper;
	skyscraper.mesh = "resources/meshes/skscr.obj";
	skyscraper.texture = "resources/textures/bricks.jpg";

	struct Setting terrain_mud;
	terrain_mud.mesh = "resources/meshes/terrain_mud.obj";
	terrain_mud.texture = "resources/textures/SoilMud0091_5_S.jpg";

	m_settings["cube"] = cube;
	m_settings["monkey"] = monkey;
	m_settings["teapot"] = teapot;
	m_settings["octahedron"] = octahedron;
	m_settings["skyscraper"] = skyscraper;
	m_settings["terrain_mud"] = terrain_mud;

}

EntitySettings::~EntitySettings(){

}

EntitySettings::Setting EntitySettings::Get(std::string name){
	return m_settings[name];
}

#endif