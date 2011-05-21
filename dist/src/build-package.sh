#!/bin/sh

name="fcms-fdebug-proxy";
file="$name.tar.gz";
base=`pwd`;

mkdir /tmp/$name
cp -r ../../* /tmp/$name

cd /tmp
tar -czf $file $name

mv ./$file $base

rm -rf ./$name
