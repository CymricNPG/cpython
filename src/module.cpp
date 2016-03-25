#include <boost/python.hpp>
#include "Test.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(libpy_module)
{
	def("getTestString", &Test::getTestString);
}

