src = src/*.cpp
bin = bin/main

exec:
	- g++ $(src) -o $(bin)

run:
	- $(bin)
