#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_artist.h"

struct Data_artist {
    char* artist_id;
    int time;
};

char* getData_ArtistId(const Data_artist* artist) {
    return artist->artist_id;
}

int getTime(const Data_artist* artist) {
    return artist->time;
}

void setData_ArtistId(Data_artist* artist, const char* new_id) {
    if (artist->artist_id) {
        free(artist->artist_id);
    }

    if (new_id) {
        artist->artist_id = strdup(new_id);
    } else {
        artist->artist_id = NULL;
    }
}

void setTime(Data_artist* artist, int new_time) {
    artist->time = new_time;
}

void addTime(Data_artist* artist, int add_time){
    artist->time += add_time;
}

Data_artist* createDataArtist() {
    Data_artist* artist = (Data_artist*)malloc(sizeof(struct Data_artist));
    if (artist == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
        exit(1);
    }
    artist->artist_id = strdup(""); // Inicializa com string vazia.
    artist->time = 0; // Inicializa tempo com 0.
    return artist;
}

void freeDataArtist(Data_artist* artist) {
    if (artist) {
        free(artist->artist_id);
        free(artist);
    }
}