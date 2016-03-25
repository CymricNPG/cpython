from enum import Enum
import unittest
import libpy_module

class Color(Enum):
    red = 1
    green = 2
    blue = 3

class BasicTestEnum(object):

    def test_to_string(self):
        self.assertIn(self.first_enum_expected_str, str(self.first_enum))

    def test_to_repr(self):
        self.assertIn(self.first_enum_expected_str, repr(self.first_enum))

    def test_hashable(self):
        colors = {}
        colors[self.first_enum] = 'red delicious'
        colors[self.second_enum] = 'granny smith'
        expected = {self.first_enum: 'red delicious', self.second_enum: 'granny smith'}
        self.assertEqual(colors, expected)

    def test_access_by_name(self):
        self.assertEqual(self.enum_by_name(self.first_enum_str), self.first_enum)

    def test_get_name(self):
        self.assertEqual(self.first_enum_str, self.first_enum.name)

    def test_is_comparison(self):
        self.assertTrue(self.first_enum is self.first_enum_duplicate)
        self.assertFalse(self.first_enum is self.second_enum)
        self.assertTrue(self.first_enum is not self.second_enum)

    def test_equal_comparison(self):
        self.assertTrue(self.first_enum == self.first_enum_duplicate)
        self.assertTrue(self.first_enum != self.second_enum)

# Basic test for enum34
class Enum34TestEnum(BasicTestEnum, unittest.TestCase):
    first_enum = Color.red
    first_enum_duplicate = Color.red
    second_enum = Color.blue
    first_enum_expected_str = "Color.red"
    first_enum_str = "red"

    def enum_by_name(self, name):
        return Color[name]

# Basic test for enum34
class BoostEnumTestEnum(BasicTestEnum, unittest.TestCase):
    first_enum = libpy_module.red
    first_enum_duplicate = libpy_module.red
    second_enum = libpy_module.blue
    first_enum_expected_str = "red"
    first_enum_str = "red"

    def enum_by_name(self, name):
        return libpy_module.Color[name]  
    
    def test_blue(self):
        self.assertEqual(libpy_module.Color["blue"] , libpy_module.blue)
    
    def test_green(self):
        self.assertEqual(libpy_module.Color["green"] , libpy_module.green)

