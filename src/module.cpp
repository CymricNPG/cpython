#include <boost/python.hpp>
#include "Test.h"
#include "A.h"
#include <map>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <iostream>
#include "PyObjectCache.hpp"

using namespace boost::python;

std::map<A*, PyObject*> map_a;

template<typename CLASS> void addSharedVector(const char* vector_name) {
	boost::python::class_<std::vector<boost::shared_ptr<CLASS>>>(vector_name) //
	.def(boost::python::vector_indexing_suite<std::vector<boost::shared_ptr<CLASS>>, true>() );
}

PyObject* getObject(boost::shared_ptr<A> obj, PyObject *dst) {
	auto raw_ptr = obj.get();
	std::map<A*, PyObject*>::iterator it = map_a.find(raw_ptr);
	if (it == map_a.end()) {
		map_a[raw_ptr] = dst;
		Py_INCREF(dst); // Increment to store in map
		Py_INCREF(dst); // Inremented to return to python
		return dst;
	} else {
		Py_DECREF(dst); // Not needed anymore
		auto old_ptr = map_a[raw_ptr];
		Py_INCREF(old_ptr); // Inremented to return to python
		return old_ptr;
	}

}

typedef typename boost::python::pointee<boost::shared_ptr<A>>::type X;

struct A_ptr_to_python_A {
	static PyObject* convert(const boost::shared_ptr<A> &a) {
		std::cout << "Conversion started" << std::endl;
		auto result = objects::make_ptr_instance<X,
				objects::pointer_holder<boost::shared_ptr<A>, X>>::execute(a);
		return getObject(a, result); // get the cached object
	}
};

// Custom call policy to overwrite the postcall from C++ back to python //
template<typename BasePolicy = boost::python::default_call_policies>
struct existing_element_policy: BasePolicy {
	template<typename ArgumentPackage>
	PyObject* postcall(const ArgumentPackage& args, PyObject* result) {

		// Chain to base policy.
		result = BasePolicy::postcall(args, result);

		// Extract shared_ptr from result //
		boost::shared_ptr<A> xptr =
				boost::python::extract<boost::shared_ptr<A> >(result);

		if (!xptr) {
			return result;
		}
		return getObject(xptr, result);
//		auto raw_ptr = xptr.get();
//
//		std::map<A*, PyObject*>::iterator it = map_a.find(raw_ptr);
//		if (it == map_a.end()) {
//			map_a[raw_ptr] = result;
//			Py_INCREF(map_a[raw_ptr]); // Increment to store in map
//		} else {
//			Py_DECREF(result); // Not needed anymore
//		}
//
//		Py_INCREF(map_a[raw_ptr]); // Inremented to return to python
//		return map_a[raw_ptr];
	}
};

//struct A_to_python_A {
//	static PyObject* convert(A const& a) {
//		std::cout << "Conversion started" << std::endl;
//		return boost::python::incref(boost::python::object(a).ptr());
//	}
//};

//
//template <class P>
//void register_ptr_to_python()
//{
//    typedef typename boost::python::pointee<P>::type X;
//    objects::class_value_wrapper< P, objects::make_ptr_instance<X, objects::pointer_holder<P,X>>>();
//}
//
//}} // namespace boost::python
//
//#endif // REGISTER_PTR_TO_PYTHON_HPP
//
//
//template <class Src, class MakeInstance>
//struct class_value_wrapper
//    : to_python_converter<Src,class_value_wrapper<Src,MakeInstance> ,true>
//{
//    static PyObject* convert(Src x)
//    {
//        return MakeInstance::execute(x);
//    }
//#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
//    static PyTypeObject const *get_pytype() { return MakeInstance::get_pytype(); }
//#endif
//};
//
//

BOOST_PYTHON_MODULE(libpy_module)
{
	def("getTestString", &Test::getTestString);
	def("getTest", &Test::getTest);
	def("getCount", &A::getCount);

	class_<Test, boost::noncopyable>("Test", no_init) //
	.def("getA", &Test::getA) // , existing_element_policy<>()) //
	.def("resetA", &Test::resetA) //
	.def("getAs", &Test::getAs);

	register_ptr_to_python<boost::shared_ptr<Test> >();
	//boost::python::to_python_converter<A, A_to_python_A>();

	class_<A, boost::noncopyable>("A", no_init) //
	.def("getString", &A::getString) //
	.def("setString", &A::setString) //
			;
	boost::python::to_python_converter<boost::shared_ptr<A>,
			c_ptr_to_cached_python<A>>();
	//register_ptr_to_python<boost::shared_ptr<A> >();

	addSharedVector<A>("AVector");
}

