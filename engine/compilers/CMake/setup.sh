#! /bin/sh
ln -fs ../../source
ln -fs ../../lib
if [ "$1" != "-nobuilddir" ]; then
	mkdir -p build
	cd build
	cmake $* ..
else
	cmake $* .
fi
