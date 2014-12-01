#pragma once
#include <string>
#include <map>

class EntitySettings
{
public:

	struct Setting
	{
		std::string texture;
		std::string mesh;
		explicit operator bool() { return mesh != ""; }
	};

	EntitySettings();

	Setting Get(std::string name);

	~EntitySettings();

protected:
private:
	std::map<std::string, Setting> m_settings;

};