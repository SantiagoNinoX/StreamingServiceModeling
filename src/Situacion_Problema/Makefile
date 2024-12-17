CXXFLAGS = -g -Wall --pedantic

main: main.o CSVLoader.o  Episodio.o Pelicula.o Video.o
	g++ $(CXXFLAGS) main.o CSVLoader.o Episodio.o Pelicula.o Video.o -o main

main.o: main.cpp
	g++ -c $(CXXFLAGS) main.cpp

CSVLoader.o: CSVLoader.cpp CSVLoader.h
	g++ -c $(CXXFLAGS) CSVLoader.cpp 

Episodio.o: Episodio.cpp Episodio.h
	g++ -c $(CXXFLAGS) Episodio.cpp 

Pelicula.o: Pelicula.cpp Pelicula.h
	g++ -c $(CXXFLAGS) Pelicula.cpp 

Video.o: Video.cpp Video.h
	g++ -c $(CXXFLAGS) Video.cpp

clean:
	rm *.o main