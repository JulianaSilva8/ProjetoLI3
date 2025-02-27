#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../include/q4.h"
#include "../../include/tree_data_history.h"
#include "../../include/utils.h"
#include "../../include/gestor_artist.h"
#include "../../include/data_artist.h"
#include "../../include/artist.h"

int query4(char *input, int atualine, gestorArtist* gestor_a, GTree* tree_data) {
    bool existe_S = false;
    char **lista_inputs = NULL;
    GHashTable* global_freq = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,NULL);

    existe_S = gestor_parser(input, existe_S, &lista_inputs);

    if (lista_inputs==NULL) {
        // input sem datas, processa a arvore toda
        g_tree_foreach(tree_data, (GTraverseFunc)process_node_top10, global_freq);
    } else {
        char *date_start = lista_inputs[0];
        char *date_end = lista_inputs[1];

        int difStart = calculateDateDifference(date_end);
        int difEnd = calculateDateDifference(date_start);

        for (int i = 0; lista_inputs[i] != NULL; i++) {
            free(lista_inputs[i]);
        }
        free(lista_inputs);

        for (; difStart <= difEnd; difStart++) {
            Node* node = findHistoryNode(tree_data, difStart);
             if (node) {
                NodeForTop10(node, global_freq);
            }
        }
    }

    // Encontrar o artista com maior frequência e artist_id mais baixo
    char* top_artist = NULL;
    int max_freq = 0;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, global_freq);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int freq = GPOINTER_TO_INT(value);
        char* current_artist = (char*)key;

        if (freq > max_freq) {
            max_freq = freq;
            top_artist = current_artist;
        }
        else if (freq == max_freq) {
            if (top_artist == NULL || strcmp(current_artist, top_artist) < 0) {
                top_artist = current_artist;
            }
        }
    }

     if (top_artist) {
        Artist* artista = procuraArtist(gestor_a, top_artist);
        char* tipo = getArtistType(artista);
        printArtist2(top_artist, atualine, 1, tipo, max_freq, existe_S);
        free(tipo);
    } else {
        printArtist2(NULL, atualine, 1, "", max_freq, existe_S);
    }

    g_hash_table_destroy(global_freq);

    return 0;
}