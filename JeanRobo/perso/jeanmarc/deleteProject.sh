#!/bin/sh

projectToDelete=$1

rm -r prj/$projectToDelete
rm src/ext/${projectToDelete}ConfigurationLoader.cpp
rm src/ext/${projectToDelete}ConfigurationLoader.o
rm include/ext/Config/${projectToDelete}ConfigurationLoader.h

echo "Hey human ! Now you have to remove your project from src/coreConfigurationLoader.cpp"
echo "If you want to keep things clean, think about removing the config files which use this project"
