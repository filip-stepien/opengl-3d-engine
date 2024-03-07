#include "EngineObject.hpp"

EngineObject::EngineObject() {
	uid = getIDCounter()++;
}

unsigned long long& EngineObject::getIDCounter() {
	static unsigned long long counter = 0;
	return counter;
}

unsigned long long EngineObject::getID() {
	return uid;
}