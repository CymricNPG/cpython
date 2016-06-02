#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include "A.h"
#include <vector>

class Test {
public:
	Test();
	static std::string getTestString();
	static boost::shared_ptr<Test> getTest();
	boost::shared_ptr<A> getA();
	std::vector<boost::shared_ptr<A>> getAs();

private:
	boost::shared_ptr<A> a;

};
