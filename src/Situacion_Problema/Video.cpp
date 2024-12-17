#include "Video.h"

using namespace std;

Video::Video() : id(""), nombre(""), duracion(0), genero(""), calificacion(0.0f) {}

Video::Video(string id, string nombre, int duracion, string genero, float calificacion) {
        this->id = id;
        this->nombre = nombre;
        this->duracion = duracion;
        this->genero = genero;
        this->calificacion = 0.0; 
}

string Video::getId() {
    return id;
}

string Video::getNombre() {
    return nombre;
}

int Video::getDuracion() {
    return duracion;
}

string Video::getGenero() {
    return genero;
}

float Video::getCalificacion() {
    return calificacion;
}

string Video::getTitulo()
{
    return "";
}

int Video::getTemporada()
{
    return 0;
}


void Video::setId(string id) {
    this->id = id;
}

void Video::setNombre(string nombre) {
    this->nombre = nombre;
}

void Video::setDuracion(int duracion) {
    this->duracion = duracion;
}

void Video::setGenero(string genero) {
    this->genero = genero;
}

void Video::setCalificacion(float calificacion) {
    this->calificacion = calificacion;
}

