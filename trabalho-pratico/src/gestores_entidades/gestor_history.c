#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "../../include/gestor_history.h"
#include "../../include/history.h"

struct gestorHistory {
    GHashTable* hashTable;
};

gestorHistory* criaGestorHistory() {
    gestorHistory* gestor = (gestorHistory*)malloc(sizeof(gestorHistory));
    gestor->hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)freeHistory);
    return gestor;
}

void freeGestorHistory(gestorHistory* gestor) {
    if (gestor) {
        g_hash_table_destroy(gestor->hashTable);
        free(gestor);
    }
}

void insereHistory(gestorHistory* gestor, History* history) {
    char* historyId = getHistoryId(history);
    g_hash_table_insert(gestor->hashTable, historyId, history);
}

History* procuraHistory(gestorHistory* gestor, const char* historyId) {
    return (History*)g_hash_table_lookup(gestor->hashTable, historyId);
}