#include "Test.h"
#include <boost/make_shared.hpp>

std::string Test::getTestString() {
	return "Hello World!";
}

boost::shared_ptr<Test> Test::getTest() {
	return boost::make_shared<Test>();
}

std::vector<boost::shared_ptr<A>> Test::getAs() {
	std::vector<boost::shared_ptr<A>> as { getA() };
	return as;
}
Test::Test() :
		a(boost::make_shared<A>()) {
	this->a->setString("1");
}

boost::shared_ptr<A> Test::getA() {
	return a;
}
