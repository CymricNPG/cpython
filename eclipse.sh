#!/bin/sh

cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D_ECLIPSE_VERSION=4.5  -DCMAKE_ECLIPSE_GENERATE_LINKED_RESOURCES=off $@ .
sed -i "s/<\/natures>/<nature>org.python.pydev.pythonNature<\/nature><\/natures>/g" .project
sed -i "s/<storageModule moduleId=\"org.eclipse.cdt.core.pathentry\">/<storageModule moduleId=\"org.eclipse.cdt.core.pathentry\"> <pathentry include=\"\/usr\/include\/linux\" kind=\"inc\" path=\"\" system=\"true\"\/>  <pathentry include=\"\/usr\/include\" kind=\"inc\" path=\"\" system=\"true\"\/><pathentry include=\"\/usr\/include\/c++\/4.8.5\" kind=\"inc\" path=\"\" system=\"true\"\/><pathentry excluding=\"build\" kind=\"src\" path=\"\"\/>/g" .cproject
sed -i "s/<pathentry kind=\"mac\" name=\"__cplusplus\" path=\"\" value=\".*\"\/>/<pathentry kind=\"mac\" name=\"__cplusplus\" path=\"\" value=\"201103L\"\/>/g" .cproject


