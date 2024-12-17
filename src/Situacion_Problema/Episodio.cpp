#include "Episodio.h"

Episodio::Episodio(string titulo, int temporada, string id, string nombre, string genero, int duracion, float calificacion)
    : Video(id, nombre, duracion, genero, calificacion), titulo(titulo), temporada(temporada) {}

string Episodio::getTitulo() {
    return titulo; 
}

int Episodio::getTemporada() {
    return temporada; 
}

void Episodio::mostrar() {
    cout << "ID Serie: " << id << " | "
         << "Nombre Serie: " << nombre << " | "
         << "Duracion Episodio: " << duracion << " | "
         << "Genero Episodio: " << genero << " | "
         << "Titulo Episodio: " << titulo << " | "
         << "Temporada: " << temporada << " | "
         << "Calificacion Episodio: " << calificacion << endl;
}

void Episodio::setEpisodioTitulo(string titulo)  {
    this->titulo = titulo;
}

void Episodio::setTemporada(int temporada) {
    this->temporada = temporada;
}