#!/bin/bash

FOLDER=$1

echo -e '\n\nDeleting previous compilations'
rm -rf $FOLDER
mkdir $FOLDER
cd $FOLDER

echo -e '\n\nGenerating MakeFiles'
cmake ..

echo -e '\n\nRecompiling'
make -j4

p="\n\nProject recompiled on the \"${FOLDER}\" folder."
echo -e "${p}"
