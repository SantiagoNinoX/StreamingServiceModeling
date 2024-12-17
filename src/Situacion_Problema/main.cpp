#include <iostream>
#include "Video.h"
#include "Pelicula.h"
#include "CSVLoader.h"

#define SERIES_FILE "series.csv"
#define MOVIES_FILE "movies.csv"

using namespace std;


int main() {

    Video **videoArray = nullptr; // se colocan aqui para no usar variables globales
    unsigned int dataSize = 0; // se colocan aqui para no usar variables globales
    bool isDataLoaded = false; // Variable para verificar si los datos ya fueron cargados
    unsigned int currentPos = 0; // variable para la posicion actual del arreglo.
    unsigned int ultimoElemento = 0; // variable que nos ayudara a sobreescribir la posicion actual despues de cargar las peliculas, y antes de los episodios

    int opcion = 0;
    while (opcion != 6) {
        cout << "\n";
        cout << "1. Cargar archivo de datos\n";
        cout << "2. Mostrar videos con cierta calificacion o genero\n";
        cout << "3. Mostrar episodios de una serie con cierta calificacion\n";
        cout << "4. Mostrar peliculas con cierta calificacion\n";
        cout << "5. Calificar un video\n";
        cout << "6. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                {
                    if (isDataLoaded) { // Verificar si los datos ya fueron cargados
                        cout << "Los datos ya fueron cargados. No se pueden cargar de nuevo.\n";
                        break;
                    }

                    dataSize = countDataLinesInCSV(MOVIES_FILE) + countDataLinesInCSV(SERIES_FILE);
                    if(dataSize == -1) {
                        cerr << "No se pudo cargar el data set de " << MOVIES_FILE << " o " << SERIES_FILE << "\n";
                        return 0;
                    }

                    cout << "movies.csv y series.csv tienen: " << dataSize << " entradas en total\n";
                    videoArray = new(nothrow) Video*[dataSize];
                    if(videoArray == nullptr) {
                        cerr << "No hubo memoria para el arreglo de videos\n";
                        return 0;
                    }
                    // aqui cambie el orden logico para checar errores, primero cargando las peliculas, y luego, checando si habia regresado un elemento vacio, marcar error
                    ultimoElemento = loadVideosFromCSV(MOVIES_FILE, videoArray, dataSize, currentPos);
                    if(ultimoElemento == 0) {
                        cerr << "Error al cargar el data set de " << MOVIES_FILE << "\n";
                        
                        delete [] videoArray;
                        return 0;
                    } 
                    
                    // aqui hago el cambio de la variable currentPos, para que cuando se intenten cargar las series y lo tome como argumento, pueda empezar despues del contenido ya cargado
                    currentPos = ultimoElemento;
                    
                    ultimoElemento = loadVideosFromCSV(SERIES_FILE, videoArray, dataSize, currentPos);
                    if(ultimoElemento == 0) {
                        cerr << "Error al cargar el data set de " << SERIES_FILE << "\n";
                        
                        delete [] videoArray;
                        return 0;
                    }
                    

                    isDataLoaded = true; // Establecer que los datos ya fueron cargados
                    
                    
                    break;
                }

            case 2:
                {
                    if (videoArray == nullptr) {
                        cout << "\nNo se han cargado los archivos, por favor cargue archivos para poder usar esta opcion" << endl;
                        break;
                    }
                    
                    cout <<  "\nQuiere ver los videos en base a al genero a en base a la calificacion?" << endl << "a) Genero" << endl << "b) Calificacion" << endl;
                    char seleccion;
                    cout << "\nIngresa tu eleccion (la letra correspondiente): ";     
                    cin >> seleccion;         

                    if (tolower(seleccion) == 'a') {
                        cout << "\nOpciones de genero: " << endl << " 1. Drama\n 2. Accion\n 3. Misterio" << endl;
                        int seleccion_genero;  
                        cout << "\nSelecciona el genero (Ingresa el numero correspondiente): ";
                        cin >> seleccion_genero; 

                        string genero;
                        switch (seleccion_genero) {
                            case 1:
                                genero = "Drama";
                                break;
                            case 2:
                                genero = "Accion";
                                break;
                            case 3:
                                genero = "Misterio";
                                break;
                            default:
                                cout << "Opcion no valida." << endl;
                                break;
                        }

                        for (unsigned int i = 0; i < dataSize; i++) {
                            if (videoArray[i]->getGenero() == genero) {
                                videoArray[i]->mostrar(); // llamamos metodos en tiempo de ejecucion
                            }
                        }


                    }

                    else if (tolower(seleccion) == 'b') {
                        cout << "\nIngresa la calificacion que deseas encontrar: " << endl;
                        float seleccion_calificacion;
                        cin >> seleccion_calificacion;

                        bool found = false;
                        for (unsigned int i = 0; i < dataSize; i++) {
                            if (videoArray[i]->getCalificacion() == seleccion_calificacion) {
                                videoArray[i]->mostrar();
                                found = true;
                            }
                        }

                        for (unsigned int i = 0; i < dataSize; i++) {
                            if (videoArray[i]->getCalificacion() == seleccion_calificacion) {
                                videoArray[i]->mostrar();
                                found = true;
                            }
                        }
                        if (!found) {
                            cout << "\nNo se encontraron videos con esa calificacion" << endl;
                        }
                    }
                    break;
                }

            case 3:
                {
                    if (videoArray == nullptr) {
                        cout << "\nNo se han cargado los archivos, por favor cargue archivos para poder usar esta opcion" << endl;
                        break;
                    }

                    cout << "\nDe que serie le interesa conocer los episodios con cierta calificacion?" << endl;
                    cin.ignore(); // Ignora el carácter de nueva línea que queda en el búfer de entrada después de usar cin. ya que puede causar problemas en la continuacion del codigo el no borrarlo. (Esto lo tuve que investigar por un error, y asi llegue a la solucion. Fuente: https://stackoverflow.com/questions/25475384/when-and-why-do-i-need-to-use-cin-ignore-in-c)
                    string seleccion_serie;
                    getline(cin, seleccion_serie); // Lee una linea entera de entrada del usuario, ya que "cin" solo lee una palabra, por lo que, al estar el nombre de la serie conformado por dos palabras, causaba problemas usar cin.

                    cout << "\nIngresa la calificacion que deseas encontrar: " << endl;
                    float seleccion_calificacion;
                    cin >> seleccion_calificacion;
                    cin.ignore();// Ignora el carácter de nueva línea que queda en el búfer de entrada después de usar cin. ya que puede causar problemas en la continuacion del codigo el no borrarlo 

                    bool found = false;
                    for (unsigned int i = 0; i < dataSize; i++) {
                        if (videoArray[i]->getNombre() == seleccion_serie && videoArray[i]->getCalificacion() == seleccion_calificacion) {
                            videoArray[i]->mostrar();
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "\nNo se encontraron episodios con esa calificacion" << endl;
                    }

                    break;
                }
                
            case 4:
                {
                    if (videoArray == nullptr) {
                        cout << "\nNo se han cargado los archivos, por favor cargue archivos para poder usar esta opcion" << endl;
                        break;
                    }
                    
                    cout << "\nCon que calificacion te gustaria que te mostrara peliculas? " << endl;
                    float seleccion_calificacion;
                    cin >> seleccion_calificacion;

                    bool found = false;
                    for (unsigned int i = 0; i < dataSize; i++) {
                        // aqui aprovechamos el typeid, para que dentro del arreglo que tiene los dos tipos de video, solo escoga peliculas
                        if (typeid(*videoArray[i]) == typeid(Pelicula) && videoArray[i]->getCalificacion() == seleccion_calificacion) {
                            videoArray[i]->mostrar();
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "\nNo se encontraron peliculas con esa calificacion" << endl;
                    }

                    break;
                }
                
            case 5:
                {
                    if (videoArray == nullptr) {
                        cout << "\nNo se han cargado los archivos, por favor cargue archivos para poder usar esta opcion" << endl;
                        break;
                    }
                    
                    cout << "\nDeseas calificar una pelicula o un episodio? (p/e)" << endl;
                    char tipo_video;
                    cin >> tipo_video;
                    cin.ignore();

                    string nombre_video;
                    string titulo_episodio;

                    if (tipo_video == 'p') {
                        cout << "\nIngresa el nombre de la pelicula que deseas calificar: " << endl;
                        getline(cin, nombre_video);
                    } 
                    else if (tipo_video == 'e') {
                        cout << "\nIngresa el nombre de la serie de la cual deseas calificar un episodio: " << endl;
                        getline(cin, nombre_video);

                        cout << "Ingresa el titulo del episodio que deseas calificar: " << endl;
                        getline(cin, titulo_episodio);
                    } 
                    else {
                        cout << "\nTipo de video no valido. Por favor, intenta de nuevo." << endl;
                        break;
                    }

                    cout << "\nIngresa la nueva calificacion: " << endl;
                    float nueva_calificacion;
                    cin >> nueva_calificacion;
                    cin.ignore();

                    if (tipo_video == 'p') {
                        bool found = false;
                        for (unsigned int i = 0; i < dataSize; i++) {
                            if (videoArray[i]->getNombre() == nombre_video) {
                                videoArray[i]->setCalificacion(nueva_calificacion);
                                cout << "\nCalificacion actualizada con exito!" << endl;
                                videoArray[i]->mostrar();
                                found = true;
                                break;
                            }  
                        }
                        if (!found) {
                            cout << "\nNo se encontro la pelicula con el nombre proporcionado." << endl;
                        }
                    }
                    else if (tipo_video == 'e') {
                        bool found = false;
                        for (unsigned int i = 0; i < dataSize; i++) {
                            if (videoArray[i]->getNombre() == nombre_video && videoArray[i]->getTitulo() == titulo_episodio) {
                                videoArray[i]->setCalificacion(nueva_calificacion);
                                cout << "\nCalificacion actualizada con exito!" << endl;
                                videoArray[i]->mostrar();
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            cout << "\nNo se encontro el episodio con el nombre y titulo proporcionados." << endl;
                        }
                    }
                    break;
                }
                
            case 6:
                {
                    cout << "\nSaliendo...\n";
                    break;
                }
                
            default:
                {
                    cout << "\nOpcion no valida. Por favor, intenta de nuevo.\n";
                    break;
                }
        }
    }
    // Liberar la memoria al final del programa
    if (videoArray != nullptr) {
        for (unsigned int i = 0; i < dataSize; i++) {
            delete videoArray[i];
        }
        delete [] videoArray;
    }

    return 0;

}