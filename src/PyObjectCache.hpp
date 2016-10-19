#pragma once
#include <boost/python.hpp>
#include <map>
#include <iostream>

template<typename C_CLASS>
using storage_map = std::map<C_CLASS*, PyObject*>;

// does not work with inheritance
template<typename C_CLASS>
storage_map<C_CLASS>* getCachedObjects() {
	static storage_map<C_CLASS> *storage = new storage_map<C_CLASS>();
	return storage;
}

template<typename C_CLASS> using c_sptr = boost::shared_ptr<C_CLASS>;

template<typename T> using py_ptr = T;

template<typename T>
PyObject * createObject(const c_sptr<T>& obj) {
	using namespace boost::python::objects;
	return make_ptr_instance<T, pointer_holder<c_sptr<T>, T>>::execute(obj);
}

template<typename C_CLASS>
void cleanMap() {
	auto map = getCachedObjects<C_CLASS>();
	for (auto it = map->begin(); it != map->end();) {
		auto py_obj = it->second;
		Py_DECREF(py_obj);
		map->erase(it++);
	}
}

template<typename C_CLASS>
void removeObject(const c_sptr<C_CLASS>& obj) {
	auto map = getCachedObjects<C_CLASS>();
	auto raw_ptr = obj.get();
	auto it = map->find(raw_ptr);
	if (it == map->end()) {
		throw std::logic_error("Object was already removed.");
	}
	auto py_obj = it->second;
	Py_DECREF(py_obj);
	map->erase(it);
}

template<typename C_CLASS>
struct c_ptr_to_cached_python {
	static PyObject* convert(const c_sptr<C_CLASS> &obj) {
		auto raw_ptr = obj.get();
		auto map = getCachedObjects<C_CLASS>();
		auto it = map->find(raw_ptr);
		if (it == map->end()) {
			auto py_obj = createObject<C_CLASS>(obj);
			(*map)[raw_ptr] = py_obj;
			Py_INCREF(py_obj); // Increment to store in map
			return py_obj;
		} else {
			auto old_py_obj = it->second;
			Py_INCREF(old_py_obj);
			return old_py_obj;
		}
	}
};
