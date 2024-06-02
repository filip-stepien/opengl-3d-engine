#include "EngineObject.hpp"

engine::EngineObject::EngineObject() {
	uid = getIDCounter()++;
}

unsigned int& engine::EngineObject::getIDCounter() {
	static unsigned int counter = 0;
	return counter;
}

unsigned int engine::EngineObject::getID() {
	return uid;
}