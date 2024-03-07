#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

class EngineObject {
protected:
	unsigned long long uid;
	static unsigned long long& getIDCounter();
public:
	EngineObject();
	unsigned long long getID();
};

#endif