#pragma once
#include <iostream>

using namespace std;

class Video {
protected: 
    string id;
    string nombre;
    int duracion;
    string genero;
    float calificacion;

public: 
    Video();
    Video(string id, string nombre, int duracion, string genero, float calificacion);

    virtual ~Video() = default; // implemente este destructor virtual, por un warning que me dio el compilador :)

    // ponemos la mayoria de los metodos que se usan en las clases, para no duplicar codigo en las clases derivadas. tambien, definimos algunos metodos virtuales, para darles usos diferentes en cada clase, aprovechando el polimorfismo
    string getId();
    string getNombre();
    int getDuracion();
    string getGenero();
    float getCalificacion();
    virtual string getTitulo(); // estos, si bien solo son para la clase episodio, los declare aqui como virtuales, para que se pudieran usar en el loadVideosFromCSV, ya que hace un arreglo de videos, y para subir series, se ocupan estos metodos
    virtual int getTemporada();

    void setId(string id);
    void setNombre(string nombre);
    void setDuracion(int duracion);
    void setGenero(string genero);
    void setCalificacion(float calificacion);
    
    virtual void mostrar() = 0; // Funcion virtual pura, ya que se implementa de diferente manera en cada una de las clases derivadas.
};