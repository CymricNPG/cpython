#pragma once

#include <string>

class A {
public:
	std::string getString();
	void setString(std::string s);
private:
	std::string s;
};
