#include "EngineObject.hpp"

EngineObject::EngineObject() {
	uid = getIDCounter()++;
}

unsigned int& EngineObject::getIDCounter() {
	static unsigned int counter = 0;
	return counter;
}

unsigned int EngineObject::getID() {
	return uid;
}