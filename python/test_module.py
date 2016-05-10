import unittest
from libpy_module import getTestString, getOptionalString

class TestModule(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_get_string(self):
        self.assertEqual("Hello World!", getTestString())

    def test_optional_string(self):
        self.assertEqual("Test", getOptionalString())