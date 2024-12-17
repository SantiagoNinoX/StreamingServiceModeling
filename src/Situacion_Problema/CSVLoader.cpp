#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int loadVideosFromCSV(const std::string& fileName, Video **&videoArray, unsigned int &arraySize, unsigned int currentPos) {
    std::ifstream file(fileName);
    std::string line;
    unsigned int size = currentPos;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << fileName << std::endl;
        return 0;
    }

    // skip header
    if(!std::getline(file, line)) {
        std::cerr << "El archivo no tiene header" << std::endl;
        file.close();
        return 0;
    }

    std::cout << "Cargando archivo: " << fileName << std::endl;

    while (std::getline(file, line)) {
        Pelicula        nPelicula;
        std::stringstream    ss(line);
        std::string          cell;
        int             campo = 0, errores = 0;


        if(fileName == "movies.csv") {
            Pelicula nPelicula;

            while (std::getline(ss, cell, ',')) {
                if(!cell.length())
                    errores ++;

                switch(campo) {
                    case 0:
                        nPelicula.setId(cell);
                        break;
                    case 1:
                        nPelicula.setNombre(cell);
                        break;
                    case 2:
                        nPelicula.setDuracion(std::stoi(cell));
                        break;
                    case 3:
                        nPelicula.setGenero(cell);
                        break;
                    case 4:
                        nPelicula.setCalificacion(std::stof(cell));
                        break;

                    default:
                        errores ++;
                        break;
                }
                campo ++;
            }

            if(errores || campo != PELICULA_ATTRIB_SIZE) {
                std::cerr << "Error en la linea: " << std::endl << line << std::endl;
                file.close();
                return 0;
            }

            if(size < arraySize) {
                videoArray[size] = new Pelicula(nPelicula);
                size ++;
                currentPos++;
            }
            else {
                std::cerr << "Error, el arreglo es muy pequeño" << std::endl;
                file.close();
                return 0;
            }
        }

        else if(fileName == "series.csv") {
            Episodio nEpisodio;

            while (std::getline(ss, cell, ',')) {
                if(!cell.length())
                    errores ++;

                switch(campo) {
                    case 0: 
                        nEpisodio.setId(cell); 
                        break;
                    case 1: 
                        nEpisodio.setNombre(cell); 
                        break;
                    case 2: 
                        nEpisodio.setDuracion(std::stof(cell)); 
                        break;
                    case 3: 
                        nEpisodio.setGenero(cell); 
                        break;
                    case 4: 
                        nEpisodio.setEpisodioTitulo(cell); 
                        break;
                    case 5: 
                        nEpisodio.setTemporada(std::stoi(cell)); 
                        break;
                    case 6: 
                        nEpisodio.setCalificacion(std::stof(cell));
                        break;
                    default: errores++; break;
                }
                campo++;
            }

            if(errores || campo != SERIE_ATTRIB_SIZE) {
                std::cerr << "Error en la linea: " << std::endl << line << std::endl;
                file.close();
                return 0;
            }

            if(size < arraySize) {
                videoArray[size] = new Episodio(nEpisodio);
                size ++;
            }
            else {
                std::cerr << "Error, el arreglo es muy pequeño" << std::endl;
                file.close();
                return 0;
            }
        }
        else {
            std::cerr << "Tipo de video desconocido: " << std::endl;
            file.close();
            return 0;
        }
    }

    file.close();
    return currentPos;
}

int countDataLinesInCSV(const string& fileName) {
    ifstream    file(fileName);
    int         lineCount = 0;
    string      line;

    // Contar la cantidad de líneas en el archivo csv
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return -1;
    }

    // skip header
    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return -1;
    }

    // Contar lineas 
    while(getline(file, line)) {
        lineCount++;    
    }

    file.close();
    return(lineCount);
}