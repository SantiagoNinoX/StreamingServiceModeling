#include "Pelicula.h"

using namespace std;

Pelicula::Pelicula() : Video("", "", 0, "", 0.0) {}

Pelicula::Pelicula(string id, string nombre, int duracion, string genero, float calificacion) : Video(id, nombre, duracion, genero, calificacion)
{
}

void Pelicula::mostrar() {
    cout << "ID Pelicula: " << id << " | "
         << "Nombre Pelicula: " << nombre << " | "
         << "Duracion Pelicula: " << duracion << " | "
         << "Genero Pelicula: " << genero << " | "
         << "Calificacion Pelicula: " << calificacion << endl;
}

