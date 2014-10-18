all: ironmandata

ironmandata:
	g++ ironman-data/ironman-data/main.cpp -o iman-data -F ./ironman-data/ironman-data/ -framework myo -rpath ./ironman-data/ironman-data

clean:
	rm iman-data
