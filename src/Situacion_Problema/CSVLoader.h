#pragma once

#include <string>
#include "Pelicula.h"
#include "Episodio.h"

#define PELICULA_ATTRIB_SIZE 5
#define SERIE_ATTRIB_SIZE 7

// Despues de cambiar a solo un arreglo me daba problemas de segmentation fault, despues de debuggearlo, me di cuenta que era porque cargaba primero las peliculas,
// y luego, para cargar las series, inicializaba el arreglo en 0, asi que se perdian las peliculas, y como buscaba 60 elementos, y solo tenia 50, 
// causaba segmentation faults, y en algunos casos mataba el programa, o simplemente no encontraba uno u otro tipo de video. por eso, 
// modifique la funcion para que regresara en lugar de un valor booleano, un valor que representara la posicion actual del arreglo, y al momento de que
// se volviera a llamar la funcion para cargar las series, pudiera empezar a cargar, despues de las peliculas, y no desde 0. con eso se arreglo! :)

unsigned int loadVideosFromCSV(const std::string& fileName, Video **&videoArray, unsigned int &arraySize,  unsigned int currentPos); // modificamos la implementacion, para solo hacer un array de videos, y no uno de cada tipo

int countDataLinesInCSV(const std::string& fileName);

