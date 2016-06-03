#pragma once

#include <string>

class A {
public:
	A();
	~A();
	std::string getString();
	void setString(std::string s);
	static int getCount();
private:
	std::string s;
	static int count;
};
