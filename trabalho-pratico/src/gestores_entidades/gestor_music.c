#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include "../../include/gestor_music.h"
#include "../../include/validacoes_musicas.h"
#include "../../include/gestor_artist.h"

struct gestorMusic {
    GHashTable* hashTable;
};

gestorMusic* criaGestorMusic() {
    gestorMusic* gestor = (gestorMusic*)malloc(sizeof(gestorMusic));
    gestor->hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)freeMusic);
    return gestor;
}

void freeGestorMusic(gestorMusic* gestor) {
    if (gestor) {
        g_hash_table_destroy(gestor->hashTable);
        free(gestor);
    }
}

void insereMusic(gestorMusic* gestor, Music* music) {
    char* music_id = getMusicId(music);
    g_hash_table_insert(gestor->hashTable, music_id, music);
}

Music* procuraMusic(gestorMusic* gestor, const char* music) {
    return (Music*)g_hash_table_lookup(gestor->hashTable, music);
}

Music* gestorMusic_lookup(gestorMusic* gestor, const char* key) {

    return (Music*)g_hash_table_lookup(gestor->hashTable, key);
}



void initMusicIterator(MusicIterator* musicIterator, gestorMusic* musicTable) {
    g_hash_table_iter_init(&musicIterator->iter, musicTable->hashTable);
    musicIterator->initialized = TRUE;
}

Music* getNextMusic(MusicIterator* musicIterator) {
    gpointer key;
    gpointer value;

    if (g_hash_table_iter_next(&musicIterator->iter, &key, &value)) {
        return (Music*)value;
    } else {
        musicIterator->initialized = FALSE;
        return NULL;
    }
}