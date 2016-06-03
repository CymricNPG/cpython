#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include "A.h"
#include <vector>

class Test {
public:
	Test();
	~Test();
	static std::string getTestString();
	static boost::shared_ptr<Test> getTest();
	boost::shared_ptr<A> getA();
	std::vector<boost::shared_ptr<A>> getAs();
	void resetA();
private:
	boost::shared_ptr<A> a;
	int count = 0;

};
