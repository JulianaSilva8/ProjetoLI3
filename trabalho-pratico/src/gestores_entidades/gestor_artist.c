#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "../../include/gestor_artist.h"
#include "../../include/music.h"
#include "../../include/artist.h"

struct gestorArtist {
    GHashTable* hashTable;
};

bool gestorArtist_existeArtista(gestorArtist* a, const char *artisteId) {
    return g_hash_table_contains(a->hashTable, artisteId);
}

gestorArtist* criaGestorArtist() {
    gestorArtist* gestor = (gestorArtist*)malloc(sizeof(gestorArtist));
    gestor->hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)freeArtist);
    return gestor;
}

void freeGestorArtist(gestorArtist* gestor) {
    if (gestor) {
        g_hash_table_destroy(gestor->hashTable);
        free(gestor);
    }
}

void insereArtist(gestorArtist* gestor, Artist* artist) {
    char* artist_id = getArtistId(artist);
    g_hash_table_insert(gestor->hashTable, artist_id, artist);
}

Artist* procuraArtist(gestorArtist* gestor, const char* artist_id) {
    return (Artist*)g_hash_table_lookup(gestor->hashTable, artist_id);
}

void resetArtistDurations(gestorArtist* gestorArtist) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, gestorArtist->hashTable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist* artist = (Artist*)value;
        resetArtistDuration(artist);
    }
}

GList* filtraArtistasPorPais(gestorArtist* gestorArtist, const char* country) {
    GList* artistList = NULL;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestorArtist->hashTable); // Inicializa o iterador

    while (g_hash_table_iter_next(&iter, &key, &value)) { // Avança para o próximo elemento com o valor e chave supostos
        Artist* artist = (Artist*)value;
        char* artistC = getArtistCountry(artist);

        if (country == NULL || (country && strcmp(artistC, country) == 0)) {
            artistList = g_list_append(artistList, artist);
        }
        free (artistC);
    }
    return artistList;
}