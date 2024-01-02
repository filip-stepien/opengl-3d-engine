#pragma once

class EngineObject {
protected:
	unsigned long id;
	static unsigned long& generateID();
public:
	EngineObject();
	unsigned long getID();
};