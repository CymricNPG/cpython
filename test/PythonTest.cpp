#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <wchar.h>

using namespace boost::python;

wchar_t *nstrws_convert(const char *raw) {
    wchar_t *rtn = (wchar_t *) calloc(1, (sizeof(wchar_t) * (strlen(raw) + 1)));
    setlocale(LC_ALL, "en_US.UTF-8");
    mbstowcs(rtn, raw, strlen(raw));
    return rtn;
}

/** Dispose of an array of wchar_t * */
void nstrws_dispose(int count, wchar_t ** values) {
    for (int i = 0; i < count; i++) {
        free(values[i]);
    }
    free(values);
}

/** Convert an array of strings to wchar_t * all at once. */
wchar_t **nstrws_array(int argc, const char *argv[]) {
    wchar_t **rtn = (wchar_t **) calloc(argc, sizeof(wchar_t *));
    for (int i = 0; i < argc; i++) {
        rtn[i] = nstrws_convert(argv[i]);
    }
    return rtn;
}

BOOST_AUTO_TEST_SUITE( PythonTest )

    BOOST_AUTO_TEST_CASE( execute_python_tests ) {

        try {

            Py_Initialize();
            boost::filesystem::path python_dir = boost::filesystem::absolute("python").normalize();
            boost::filesystem::path test_dir = boost::filesystem::absolute("test").normalize();
            boost::filesystem::path lib_dir = boost::filesystem::absolute("bin").normalize();
            PyObject* sys_path = PySys_GetObject(const_cast<char*>("path"));
            PyList_Insert(sys_path, 0, PyUnicode_FromString(python_dir.string().c_str()));
            PyList_Insert(sys_path, 0, PyUnicode_FromString(lib_dir.string().c_str()));
            PyList_Insert(sys_path, 0, PyUnicode_FromString(test_dir.string().c_str()));
            const char *argv[] = { "nosetests.py", "python", NULL };
            int argc = 1;
            wchar_t **_argv = nstrws_array(argc, argv);
            PySys_SetArgv(argc, _argv);

            boost::python::object main = boost::python::import("__main__");
            boost::python::object global(main.attr("__dict__"));
            boost::python::object result = boost::python::exec_file("python/nosetests.py", global, global);
            Py_Finalize();
        } catch (error_already_set &e ) {
            PyErr_Print();
            BOOST_FAIL(true);
        }
    }
    BOOST_AUTO_TEST_SUITE_END()

