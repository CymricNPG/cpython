#include <boost/python.hpp>
#include "Test.h"
#include "optional_convert.hpp"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/ndarrayobject.h>

int export_numpy() {
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    import_array();
    return 0;
}

using namespace boost::python;

BOOST_PYTHON_MODULE(libpy_module)
{
	export_numpy();
	def("getTestString", &Test::getTestString);
	def("getOptionalString", &Test::getOptionalString);
	optional_<std::string>();

}


