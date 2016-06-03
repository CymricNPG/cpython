#include "Test.h"
#include <boost/make_shared.hpp>
#include "PyObjectCache.hpp"
#include <iostream>

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
	this->a->setString(std::to_string(count++));
}

Test::~Test() {
	cleanMap<A>();
}

boost::shared_ptr<A> Test::getA() {
	return a;
}

void Test::resetA() {
	std::cerr << "a count:" << this->a.use_count() << std::endl;
	removeObject<A>(this->a);
	this->a = nullptr;
	this->a = boost::make_shared<A>();
	this->a->setString(std::to_string(count++));
	std::cerr << "NEW a count:" << this->a.use_count() << std::endl;

}
