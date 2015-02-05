#ifndef HRTFVR_ENTITY_SETTINGS_H
#define HRTFVR_ENTITY_SETTINGS_H

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

	virtual ~EntitySettings();

protected:
private:
	std::map<std::string, Setting> m_settings;

};

#endif