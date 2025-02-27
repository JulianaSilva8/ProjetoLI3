#include "../../include/q1.h"
#include "../../include/parser_inputs.h"
#include "../../include/output.h"
#include "../../include/utils.h"
#include <stdio.h>

/**
 * @brief Função que guarda os outputs da query 1.
 *
 * @param foundUser Utilizador encontrado.
 * @param foundArtist Artista encontrado.
 * @param atualine Número da linha atual.
 * @param existe_s Flag que indica se o input tem 'S'.
 */
void guardar_outputs(User* foundUser, Artist* foundArtist, int atualine, bool existe_s) {
    char **matrix = NULL;

    if (foundUser != NULL) {
        getDataOnMatrix(&matrix, foundUser);
        for (int i = 0; i < 5; i++) {
            output(matrix[i], atualine, existe_s, 0);
        }
        freeMatrix(matrix,5);

    } else if(foundArtist!=NULL) {
        matriz_q1_artist(&matrix, foundArtist);
        int array[] = {0,1,3,4,5};

        for (int i = 0; i < 5; i++) {
            output(matrix[array[i]],atualine, existe_s, 0);
        }
        freeMatrix(matrix,6);

    } else output("User not found", atualine, existe_s, 1);
}

int query1(char *input, int atualine, gestorUser* gestor,gestorArtist* gestor_a) {
    bool existe_S = false;
    char **lista_inputs = NULL;

    existe_S = gestor_parser(input, existe_S, &lista_inputs);

    User* foundUser = procuraUser(gestor, lista_inputs[0]);
    Artist* foundArtist = procuraArtist(gestor_a, lista_inputs[0]);

    guardar_outputs(foundUser,foundArtist,atualine,existe_S);

    // free memória
    for (int i = 0; lista_inputs[i] != NULL; i++) {
        free(lista_inputs[i]);
    }
    free(lista_inputs);

    return 0;
}