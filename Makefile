build:
	g++-15 -std=c++17 src/*.cpp -I include -o snake

clean:
	rm snake