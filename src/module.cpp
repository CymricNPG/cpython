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

static PyObject* Foo_doSomething(PyObject *self, PyObject *args) {
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
	PyTypeObject *pto = reinterpret_cast<PyTypeObject *>(enum_type->ob_type);
	PyTypeObject *new_pto = new PyTypeObject();
	memcpy(new_pto, pto, sizeof(PyTypeObject)); // do we need borrow?
	//see enum..cpp in boost type_handle base(borrowed(&enum_type_object));

	PyMappingMethods *counter_as_mapping = new PyMappingMethods();
	counter_as_mapping->mp_subscript = Foo_doSomething,

	new_pto->tp_as_mapping = counter_as_mapping;
	enum_type->ob_type = new_pto;

}

