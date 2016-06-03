#include "A.h"
#include <iostream>

int A::count = 0;

A::A() {
	A::count++;
	std::cout << "Created a" << std::endl;
}

A::~A() {
	A::count--;
	std::cout << "Deleted a" << std::endl;
}

std::string A::getString() {
	return s;
}

void A::setString(std::string s) {
	this->s = s;
}

int A::getCount() {
	return count;
}
