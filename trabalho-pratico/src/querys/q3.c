#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../../include/gestor_music.h"
#include "../../include/gestor_user.h"
#include "../../include/tree.h"
#include "../../include/parser_inputs.h"
#include "../../include/q3.h"
#include "../../include/output.h"

struct GenreCount{
    char* genre;
    int count;
};

struct musicsgenders {
    int generoscount[10];
};

int compare_genre_counts(const void *a, const void *b) {
    const GenreCount* genreA = (const GenreCount*)a;
    const GenreCount* genreB = (const GenreCount*)b;

    if (genreB->count != genreA->count) {
        return genreB->count - genreA->count;
    }

    return strcmp(genreA->genre, genreB->genre);
}

musicsgenders initialize_genre_counts() {
    musicsgenders total;
    for (int i = 0; i < 10; i++) {
        total.generoscount[i] = 0;
    }
    return total;
}

musicsgenders count_genres_in_range(int start, int end, GTree* arvore) {
    musicsgenders total = initialize_genre_counts();

    for (int i = start; i <= end; i++) {
        Node* node = g_tree_lookup(arvore, &i);
        if (node) {
            for (int j = 0; j < 10; j++) {
                total.generoscount[j] += getCount(node,j);
            }
        }
    }
    return total;
}

int check_all_genres_zero(GenreCount* genres, int num_genres) {
    for (int i = 0; i < num_genres; i++) {
        if (genres[i].count != 0) {
            return 0;
        }
    }
    return 1;
}

int write_genre_counts_to_file(int line1, GenreCount* genres, int num_genres, int all_zero, bool existe_s) {
    if (all_zero) {
        output(NULL, line1, existe_s, all_zero);
    } else {
        qsort(genres, num_genres, sizeof(GenreCount), compare_genre_counts);

        for (int i = 0; i < num_genres; i++) {
            char count_str[12]; // Assumindo que o número não excede 11 dígitos
            sprintf(count_str, "%d", genres[i].count);

            output(genres[i].genre, line1, existe_s, 0);
            output(count_str, line1, existe_s, 0);
            output("\n", line1, existe_s, 0);
        }
    }
    return 0;
}

int q3(int line1, char* input, GTree* arvore) {
    bool existe_S = false ;

    char **lista_inputs = NULL;

    existe_S = gestor_parser(input, existe_S, &lista_inputs);

    int start = atoi(lista_inputs[0]);
    int end = atoi(lista_inputs[1]);

    musicsgenders total = count_genres_in_range(start, end, arvore);

    GenreCount genres[] = {
        {"Metal", total.generoscount[0]},
        {"Pop", total.generoscount[1]},
        {"Rock", total.generoscount[2]},
        {"Blues", total.generoscount[3]},
        {"Hip Hop", total.generoscount[4]},
        {"Classical", total.generoscount[5]},
        {"Country", total.generoscount[6]},
        {"Electronic", total.generoscount[7]},
        {"Jazz", total.generoscount[8]},
        {"Reggae", total.generoscount[9]}
    };

    int num_genres = sizeof(genres) / sizeof(genres[0]);
    int all_zero = check_all_genres_zero(genres, num_genres);

    for (int i = 0; lista_inputs[i] != NULL; i++) {
        free(lista_inputs[i]);
    }
    free(lista_inputs);

    return write_genre_counts_to_file(line1, genres, num_genres, all_zero,existe_S);
}