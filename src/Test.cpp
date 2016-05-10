#include "Test.h"

std::string Test::getTestString() {
	return "Hello World!";
}

boost::optional<std::string> Test::getOptionalString() {
	return std::string("Test");
}
