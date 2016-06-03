import unittest
from libpy_module import getTestString, getTest, getCount
import gc

class TestModule(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_get_string(self):
        self.assertEqual("Hello World!", getTestString())

    def test_get_A(self):
        test = getTest()
        a = test.getA()
        self.assertEqual(a.getString(), "0")

    def test_eq(self):
        test = getTest()
        a1 = test.getA()
        a2 = test.getA()
        self.assertEqual(a1, a1)
        self.assertEqual(a1, a2)

    def test_id(self):
        test = getTest()
        a1 = test.getA()
        a2 = test.getA()
        self.assertIs(a1, a1)
        self.assertIs(a1, a2)

    def test_eq_array(self):
        test = getTest()
        a1 = test.getA()
        a2 = test.getAs()[0]
        self.assertEqual(a1, a1)
        self.assertEqual(a1, a2)

    def test_id_array(self):
        test = getTest()
        a1 = test.getA()
        a2 = test.getAs()[0]
        self.assertIs(a1, a1)
        self.assertIs(a1, a2)

    def test_hash_array(self):
        test = getTest()
        a1 = test.getA()
        a2 = test.getAs()[0]
        self.assertEqual(hash(a1), hash(a2))

    def test_instance(self):
        test = getTest()
        a1 = test.getA()
        a1.new_var = "2"
        a2 = test.getAs()[0]
        self.assertEqual("2", a2.new_var)

    def test_instance_none(self):
        test = getTest()
        a1 = test.getA()
        a1.new_var = "2"
        a1 = None
        a2 = test.getAs()[0]
        self.assertEqual("2", a2.new_var)

    def test_instance_delete(self):
        test = getTest()
        a1 = test.getA()
        a1.new_var = "2"
        del(a1)
        a1 = None
        a2 = test.getAs()[0]
        self.assertEqual("2", a2.new_var)

    def test_reset(self):
        test = getTest()
        a1 = test.getA()
        test.resetA()
        a2 = test.getA()
        self.assertEqual(a1.getString(), "0")
        self.assertEqual(a2.getString(), "1")
        self.assertIsNot(a1, a2)

    def test_delete_object_is_freed(self):
        test = getTest()
        a1 = test.getA()
        self.assertEquals(1, getCount());
        test.resetA()
        a2 = test.getA()
        self.assertEquals(2, getCount());
        del(a1)
        a1 = None
        gc.collect()
        self.assertEquals(1, getCount());
