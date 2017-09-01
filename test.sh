set -u

cd `dirname $0`

mkdir out

javac src/KnightsAttacksVis.java -d out

g++ --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3 -o out/a.out src/KnightsAttacks.cpp

java -cp out/ KnightsAttacksVis out/a.out