#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/gestor_user.h"
#include "../../include/gestor_music.h"
#include "../../include/q5.h"
#include "../../include/parser_inputs.h"
#include "../../include/recomendador.h"
#include "../../include/output.h"
#include "../../include/utils.h"

char* nomesGeneros[10] = {
    "Metal",
    "Pop",
    "Rock",
    "Blues",
    "Hip Hop",
    "Classical",
    "Country",
    "Electronic",
    "Jazz",
    "Reggae"
};

void buildmatrix(gestorMusic *gestor_music, User* user, char*** matrix_user, int *** user_gender, int line_atual) {
    int index_max = getHistoricoSize(user);

    char* username = getUsername(user);
    strcpy((*matrix_user)[line_atual] ,username);
    free(username);
    for (int i = 0; i < index_max; i++) {
        char* music_id = getMusicId_Historico(user, i);
        Music* music = procuraMusic(gestor_music, music_id);
        free(music_id);

        char* genre = getGenre(music);
        int genre_index = getGenreIndex(genre);
        if (genre_index != -1) {
            (*user_gender)[line_atual][genre_index]++;
        }
        free(genre);
    }
}

void** fazmatrix_q5(gestorMusic* gestorMusic, gestorUser* gestorUser) {
    UserIterator userIterator;
    initUserIterator(&userIterator, gestorUser);

    User* user;
    int n_users = getNumberUser(gestorUser);

    char **matrix_user = (char **)malloc(n_users * sizeof(char *));
    for (unsigned long int i = 0; i < n_users; i++) {
        matrix_user[i] = (char *)malloc(9 * sizeof(char));
    }

    int **user_gender = (int **)malloc(n_users * sizeof(int *));
    for (unsigned long int i = 0; i < n_users; i++) {
        user_gender[i] = (int *)malloc(10 * sizeof(int));
        memset(user_gender[i], 0, 10 * sizeof(int)); // Inicializa a matriz com zeros
    }

    int line_atual = 0;
    while ((user = getNextUser(&userIterator)) != NULL) {
        buildmatrix(gestorMusic, user, &matrix_user, &user_gender, line_atual);
        line_atual++;
    }

    void** result = (void**)malloc(2 * sizeof(void*));
    result[0] = matrix_user;
    result[1] = user_gender;

    return result;
}

void freeMatrixData(void** matriz_q5, gestorUser* gestorUser) {
    char** matrix_user = (char**)matriz_q5[0];
    int** user_gender = (int**)matriz_q5[1];

    int n_users = getNumberUser(gestorUser);

    for (unsigned long int i = 0; i < n_users; i++) {
        free(matrix_user[i]);
    }
    free(matrix_user);

    for (unsigned long int i = 0; i < n_users; i++) {
        free(user_gender[i]);
    }
    free(user_gender);
}

void query5(void** data, gestorUser* gestorUser, char* input, int line1) {
    char **lista_inputs = NULL;
    bool existe_S;
    existe_S = gestor_parser(input, existe_S, &lista_inputs);

    User* input_user = procuraUser(gestorUser, lista_inputs[0]);
    if (input_user == NULL || lista_inputs[1][0] == '0') {
        for (int i = 0; lista_inputs[i] != NULL; i++) {
            free(lista_inputs[i]);
        }
        free(lista_inputs);

        output("\n", line1, existe_S, 1);
        return;
    }

    char **matrix_user = (char **)data[0];
    int **user_gender = (int **)data[1];

    int n_users = getNumberUser(gestorUser);

    int n = atoi(lista_inputs[1]);
    char **output1 = recomendaUtilizadores(lista_inputs[0], user_gender, matrix_user, nomesGeneros, n_users, 10, n);

    for (int i = 0; i < n; i++) {
        output(output1[i], line1, existe_S, 0);
        output("\n", line1, existe_S, 0);
    }

    for (int i = 0; lista_inputs[i] != NULL; i++) {
        free(lista_inputs[i]);
    }
    free(output1);
    free(lista_inputs);
}