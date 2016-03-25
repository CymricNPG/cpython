import unittest
from libpy_module import getTestString

class TestModule(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_get_string(self):
        self.assertEqual("Hello World!", getTestString())
