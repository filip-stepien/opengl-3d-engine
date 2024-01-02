#include "EngineObject.hpp"

EngineObject::EngineObject() {
	uid = generateID()++;
}

unsigned long& EngineObject::generateID() {
	static unsigned long counter = 0;
	return counter;
}

unsigned long EngineObject::getID() {
	return uid;
}