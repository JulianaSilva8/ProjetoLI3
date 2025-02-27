#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <glib.h>
#include "../../include/gestor_user.h"
#include "../../include/gestor_music.h"

struct gestorUser {
    GHashTable* hashTable;
};

struct UserIterator {
    GHashTableIter iter;
    gboolean initialized;
};

gestorUser* criaGestorUser() {
    gestorUser* gestor = (gestorUser*)malloc(sizeof(gestorUser));
    gestor->hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)freeUser);
    return gestor;
}

void freeGestorUser(gestorUser* gestor) {
    if (gestor) {
        g_hash_table_destroy(gestor->hashTable);
        free(gestor);
    }
}

void insereUser(gestorUser* gestor, User* user) {
    char* username = getUsername(user); // n preciso de dar free porque como estou a inserir na hashtable
    // e de acordo com o copilot, estou a transferir a ownership desta string duplicada para a hashtable.
    //ao destruir a hashtable vai tudo de vela e a memoria é libertada
    g_hash_table_insert(gestor->hashTable, username, user);
}

User* procuraUser(gestorUser* gestor, const char* username) {
    return (User*)g_hash_table_lookup(gestor->hashTable, username);
}

void initUserIterator(UserIterator* userIterator, gestorUser* userTable) {
    g_hash_table_iter_init(&userIterator->iter, userTable->hashTable);
    userIterator->initialized = 1;
}

User* getNextUser(UserIterator* userIterator) {
    gpointer key;
    gpointer value;

    if (g_hash_table_iter_next(&userIterator->iter, &key, &value)) {
        return (User*)value;
    } else {
        userIterator->initialized = FALSE;
        return NULL;
    }
}

unsigned long int getNumberUser(gestorUser* hashtable){
        return g_hash_table_size(hashtable->hashTable);
}