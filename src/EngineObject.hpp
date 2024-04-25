#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

class EngineObject {
protected:
	unsigned int uid;
	static unsigned int& getIDCounter();
public:
	EngineObject();
	unsigned int getID();
};

#endif