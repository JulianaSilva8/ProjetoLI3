#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/albuns.h"

struct Album {
    char* id;
    char* title;
    char* artist_id;
    char* year;
    char* producers;
};

const char* getAlbumId(Album* album) {
    return strdup(album->id);
}

const char* getAlbumTitle(Album* album) {
    return strdup(album->title);
}

const char* getAlbumArtistId(Album* album) {
    return strdup(album->artist_id);
}

const char* getAlbumYear(Album* album) {
    return strdup(album->year);
}

const char* getAlbumProducers(Album* album) {
    return strdup(album->producers);
}

Album* criaAlbum() {
    Album* album = (Album*)malloc(sizeof(Album));

    album->id = NULL;
    album->title = NULL;
    album->artist_id = NULL;
    album->year = NULL;
    album->producers = NULL;
    return album;
}

void freeAlbum(Album* album) {
    free(album->id);
    free(album->title);
    free(album->artist_id);
    free(album->year);
    free(album->producers);
    free(album);
}

void albumField(Album* album, int index, const char* value) {
    char* trim = strdup(value);
    // Verificar as aspas
    if (trim[0] == '"' && trim[strlen(trim) - 1] == '"') {
        trim[strlen(trim) - 1] = '\0'; // Remover as últimas aspas
        memmove(trim, trim + 1, strlen(trim)); // Shift para a esquerda para remover as primeiras aspas
    }

    switch (index) {
        case 0:
            album->id = strdup(trim);
            break;
        case 1:
            album->title = strdup(trim);
            break;
        case 2:
            album->artist_id = strdup(trim);
            break;
        case 3:
            album->year = strdup(trim);
            break;
        case 4:
            album->producers = strdup(trim);
            break;
        default:
            break;
    }
    free(trim);
}