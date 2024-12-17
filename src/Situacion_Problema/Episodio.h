#pragma once
#include "Video.h"

class Episodio : public Video {
private: 
    string titulo;
    int temporada; 

public: 
    Episodio(string titulo = "", int temporada = 0, string id = "", string nombre = "", string genero = "", int duracion = 0, float calificacion = 0.0);

    string getTitulo() override;
    virtual int getTemporada() override;
    
    void mostrar() override; // Esta funcion va a sobreescribir la funcion virtual pura declarada en la clase base.

    void setEpisodioTitulo(string titulo);
    void setTemporada(int temporada);
};