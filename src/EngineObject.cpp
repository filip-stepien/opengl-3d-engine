#include "EngineObject.hpp"

EngineObject::EngineObject() {
	id = generateID()++;
}

unsigned long& EngineObject::generateID() {
	static unsigned long counter = 0;
	return counter;
}

unsigned long EngineObject::getID() {
	return id;
}