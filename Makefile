all: ironmandata

ironmandata:
	g++ ironman-data/ironman-data/main.cpp -o iman-data -F ./ironman-data/ironman-data/ -framework myo -rpath ./ironman-data/ironman-data

state:
	g++ -c ironman-data/ironman-data/state.cpp -o state.o

clean:
	rm iman-data
