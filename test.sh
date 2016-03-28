#!/bin/sh
DIR=$( cd "$( dirname "$0" )" && pwd )
export PYTHONPATH=$DIR/lib/
cd $DIR/python
find .|grep ".pyc$"|xargs rm
nosetests $@
