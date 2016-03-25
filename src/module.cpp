#include "Test.h"
#include <boost/python.hpp>
#include <cstring>
#include <boost/algorithm/string/predicate.hpp>
#include "Color.h"

using namespace boost::python;



Color enumfromString(std::string input) {
	if (boost::iequals(input, "red")) {
		return Color::red;
	}
	if (boost::iequals(input, "blue")) {
		return Color::blue;
	}
	if (boost::iequals(input, "green")) {
		return Color::green;
	}
	throw std::logic_error("Unknown enum:" + input);
}

static PyObject* convertEnum(PyObject *self, PyObject *args) {
	auto resultEnum = enumfromString(PyString_AsString(args));
	return incref(object(resultEnum).ptr());
}


BOOST_PYTHON_MODULE(libpy_module)
{
	def("getTestString", &Test::getTestString);

	enum_<Color> testEnum("Color");

	testEnum.value("red", Color::red).value("blue", Color::blue).value("green",
			Color::green).export_values();

	PyObject *enum_type = reinterpret_cast<PyObject *>(testEnum.ptr());

	// get the metatype and make a copy
	PyTypeObject *pto = reinterpret_cast<PyTypeObject *>(enum_type->ob_type);
	PyTypeObject *new_pto = new PyTypeObject();
	memcpy(new_pto, pto, sizeof(PyTypeObject)); // do we need borrow? see enum..cpp in boost type_handle base(borrowed(&enum_type_object));

	// define a new mapping method
	PyMappingMethods *mapping = new PyMappingMethods();
	mapping->mp_subscript = convertEnum,

	// replace the old mapping method and overwrite the meta type in the enum
	new_pto->tp_as_mapping = mapping;
	enum_type->ob_type = new_pto;

}

