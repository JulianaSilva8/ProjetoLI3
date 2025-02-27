#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "../../include/albuns.h"
#include "../../include/gestor_albuns.h"

struct gestorAlbuns {
    GHashTable* hashTable;
};

/**
 * @brief Verifica se um álbum existe no gestor de álbuns.
 *
 * @param a Gestor de álbuns.
 * @param id Id do álbum.
 */
bool gestorAlbum_existeAlbum(gestorAlbuns* a, const char *id) {
    return g_hash_table_contains(a->hashTable, id);
}

gestorAlbuns* criaGestorAlbuns() {
    gestorAlbuns* gestor = (gestorAlbuns*)malloc(sizeof(gestorAlbuns));
    gestor->hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)freeAlbum);
    return gestor;
}

void freeGestorAlbuns(gestorAlbuns* gestor) {
    if (gestor) {
        g_hash_table_destroy(gestor->hashTable);
        free(gestor);
    }
}

void insereAlbum(gestorAlbuns* gestor, Album* album) {
    char* album_id = getAlbumId(album);
    g_hash_table_insert(gestor->hashTable, album_id, album);
}

Album* procuraAlbum(gestorAlbuns* gestor, const char* album_id) {
    return (Album*)g_hash_table_lookup(gestor->hashTable, album_id);
}