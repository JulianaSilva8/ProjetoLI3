#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_artist.h"
#include "../../include/tree_data_history.h"
#include "../../include/artist.h"
#include "../../include/utils.h"

Node* createHistoryNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, freeDataArtist);

    return node;
}

void freeHistoryNode(Node* node) {
    if (node) {
        if (node->hashTable) {
            g_hash_table_destroy(node->hashTable);
        }
        free(node);
    }
}

void insertInHistoryHash(Node* node, const char* key, Data_artist* data_artist) {
    if (node && node->hashTable) {
        g_hash_table_insert(node->hashTable, key, data_artist);
    }
}

Data_artist* lookupInHistoryHash(Node* node, const char* key) {
    if (node && node->hashTable) {

        return g_hash_table_lookup(node->hashTable, key);
    }
    return NULL;
}

Node* findHistoryNode(GTree* tree, int value) {
    int* key = &value;
    return (Node*)g_tree_lookup(tree, key);
}

gint compareHistoryInts(gconstpointer a, gconstpointer b) {
    return *(int*)a - *(int*)b;
}

GTree* init_history_tree() {
    GTree* tree = g_tree_new_full((GCompareDataFunc)compareHistoryInts, NULL, g_free, (GDestroyNotify)freeHistoryNode);
    return tree;
}

void build_history_tree(GTree* tree, char* timestamp, char* artist_id, char* duration) {
    char data[11];
    strncpy(data, timestamp, 10);
    data[10] = '\0';

    int n = calculateDateDifference(data);
    Node* node = findOrCreateHistoryNode(tree, n);

    char** artist_array = parse_Artist_string(artist_id);
    if (!artist_array) {
        return;
    }

    for (int i = 0; artist_array[i] != NULL; i++) {
        Data_artist* data_artist = lookupInHistoryHash(node, artist_array[i]);
        if (!data_artist) {
            Data_artist* new_data_artist = createDataArtist();
            setData_ArtistId(new_data_artist, artist_array[i]);
            setTime(new_data_artist, durationToseconds(duration));
            char* key_copy = g_strdup(artist_array[i]);
            insertInHistoryHash(node, key_copy, new_data_artist);
        } else {
            addTime(data_artist, durationToseconds(duration));
        }
    }

    for (int i = 0; artist_array[i] != NULL; i++) {
        free(artist_array[i]);
    }
    free(artist_array);
}

Node* findOrCreateHistoryNode(GTree* tree, int val) {
    Node* node = NULL;
    int searchVal = val;
    node = g_tree_lookup(tree, &searchVal);
    if (!node) {
        node = createHistoryNode(val);
        int* key = g_malloc(sizeof(int));
        *key = val;
        g_tree_insert(tree, key, node);
    }
    return node;
}

void destroy_history_tree(GTree* tree) {
    if (tree) {
        g_tree_destroy(tree);
    }
}

gint compareArtistDurationDesc(gconstpointer a, gconstpointer b) {
    ArtistDuration* ad_a = (ArtistDuration*)a;
    ArtistDuration* ad_b = (ArtistDuration*)b;
    return ad_b->duration - ad_a->duration;
}

void freeArtistDuration(gpointer data) {
    ArtistDuration* ad = (ArtistDuration*)data;
    free(ad);
}

gboolean process_node_top10(gpointer key, gpointer value, gpointer user_data) {
    GHashTable* global_freq = (GHashTable*)user_data;
    Node* node = (Node*)value;

    if (node && node->hashTable) {
        GHashTableIter iter;
        gpointer artist_key, artist_value;
        GList* artist_list = NULL; // Lista para armazenar artistas e durações

        g_hash_table_iter_init(&iter, node->hashTable);
        while (g_hash_table_iter_next(&iter, &artist_key, &artist_value)) {
            char* artist_id = (char*)artist_key;
            Data_artist* artist = (Data_artist*)artist_value;
            int duration = getTime(artist);

            // Alocar e preencher a estrutura ArtistDuration
            ArtistDuration* ad = malloc(sizeof(ArtistDuration));
            if (!ad) {
                fprintf(stderr, "Erro ao alocar memória para ArtistDuration.\n");
                g_hash_table_destroy(global_freq);
                exit(1);
            }
            ad->artist_id = artist_id;
            ad->duration = duration;

            // Adicionar à lista
            artist_list = g_list_prepend(artist_list, ad);
        }

        // Ordenar a lista por ordem decrescente de duração
        artist_list = g_list_sort(artist_list, (GCompareFunc)compareArtistDurationDesc);

        int count = 0;
        for (GList* l = artist_list; l != NULL && count < 10; l = l->next, count++) {
            ArtistDuration* ad = (ArtistDuration*)l->data;

            gpointer current_count = g_hash_table_lookup(global_freq, ad->artist_id);
            if (current_count) {
                int new_count = GPOINTER_TO_INT(current_count) + 1;
                g_hash_table_replace(global_freq, ad->artist_id, GINT_TO_POINTER(new_count));
            } else {
                g_hash_table_insert(global_freq, ad->artist_id, GINT_TO_POINTER(1));
            }
        }

        g_list_free_full(artist_list, freeArtistDuration);
    } else {
        printf("Nodo não encontrado ou hashTable vazia.\n");
    }

    return FALSE; // Continue a iteração
}

void NodeForTop10(Node* node, GHashTable* global_freq) {
    if (node && node->hashTable) {
        GHashTableIter iter;
        gpointer artist_key, artist_value;
        GList* artist_list = NULL; // Lista para armazenar artistas e durações

        g_hash_table_iter_init(&iter, node->hashTable);
        while (g_hash_table_iter_next(&iter, &artist_key, &artist_value)) {
            char* artist_id = (char*)artist_key;
            Data_artist* artist = (Data_artist*)artist_value;
            int duration = getTime(artist);

            // Alocar e preencher a estrutura ArtistDuration
            ArtistDuration* ad = malloc(sizeof(ArtistDuration));
            if (!ad) {
                g_hash_table_destroy(global_freq);
                exit(1);
            }
            ad->artist_id = artist_id;
            ad->duration = duration;

            // Adicionar à lista
            artist_list = g_list_prepend(artist_list, ad);
        }

        // Ordenar a lista por ordem decrescente de duração
        artist_list = g_list_sort(artist_list, (GCompareFunc)compareArtistDurationDesc);

        int count = 0;
        for (GList* l = artist_list; l != NULL && count < 10; l = l->next, count++) {
            ArtistDuration* ad = (ArtistDuration*)l->data;

            // Atualizar frequência global
            gpointer current_count = g_hash_table_lookup(global_freq, ad->artist_id);
            if (current_count) {
                int new_count = GPOINTER_TO_INT(current_count) + 1;
                g_hash_table_replace(global_freq, ad->artist_id, GINT_TO_POINTER(new_count));
            } else {
                g_hash_table_insert(global_freq, ad->artist_id, GINT_TO_POINTER(1));
            }
        }

        g_list_free_full(artist_list, freeArtistDuration);
    }
}