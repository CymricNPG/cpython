#!/bin/sh
DIR=$( cd "$( dirname "$0" )" && pwd )
export PYTHONPATH=$DIR/bin/
cd $DIR/python
python nosetests.py $@
