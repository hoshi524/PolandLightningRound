set -e

cd `dirname $0`

javac src/KnightsAttacksVis.java -d out

g++ --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3 -o out/a.out src/KnightsAttacks.cpp
g++ --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3 -o out/b.out src/Test.cpp

java -cp out/ KnightsAttacksVis out/a.out out/b.out