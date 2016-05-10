#pragma once

#include <string>
#include <boost/optional.hpp>

class Test {
public:
	static std::string getTestString();
	static boost::optional<std::string> getOptionalString() ;
};
