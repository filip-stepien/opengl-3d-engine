#pragma once

class EngineObject {
protected:
	unsigned long uid;
	static unsigned long& generateID();
public:
	EngineObject();
	unsigned long getID();
};