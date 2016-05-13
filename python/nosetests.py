#!/usr/bin/env python
print("Starting nose tests")
import os
print(os.getcwd())

__requires__ = 'nose==1.3.7'
import nose

nose.main([])
print("Finished")