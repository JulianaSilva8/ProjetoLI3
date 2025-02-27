#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/parser_inputs.h"

/**
 * @brief Separa strings entre aspas.
 *
 * @param lista_inputs Lista de strings.
 * @param input Input.
 * @param contagem Contagem de strings.
 * @param string_atual String atual.
 */
int separa_entre_aspas(char*** lista_inputs, char* input, int* contagem, int string_atual) {

    input++; // Avança a primeira aspa
    *contagem += 1; // Conta a primeira aspa

    int len = 0;

    while (input[len] != '"' && input[len] != '\0') {
        len++;
    }

    // Aloca memória para a string
    (*lista_inputs)[string_atual] = (char*)malloc((len+1) * sizeof(char));

    strncpy((*lista_inputs)[string_atual], input, len);
    (*lista_inputs)[string_atual][len] = '\0';

    *contagem += len + 1; // Adiciona o tamanho da string e a aspa final

    return 1;
}

bool gestor_parser(char* input, bool existe_s, char*** lista_inputs) {
    if (input[1] == 'S') {
        existe_s = true;
        input = input + 1;
    } else {
        existe_s = false;
    }
    if(strlen(input) < 2) return existe_s;
    input = input + 2;
    int string_atual = 0;
    int len = strlen(input);
    int n_atual = 0;

    // Conta o número de strings
    int num_strings = 1;
    for (int i = 0; i < len; i++) {
        if (input[i] == ' ') {
            num_strings++;
        }
    }

    *lista_inputs = (char**)malloc((num_strings + 2) * sizeof(char*));

    while (n_atual < len) {
        while (input[n_atual] == ' ') {
            n_atual++;
        }
        if(input[n_atual] == '"'){
            int contagem = 0;
            string_atual = string_atual + separa_entre_aspas(lista_inputs,input+n_atual, &contagem,string_atual);
            n_atual += contagem;

        }
        else{
        int word_len = 0;
        while (input[n_atual + word_len] != ' ' && input[n_atual + word_len] != '\0' ) {
            word_len++;
        }
        (*lista_inputs)[string_atual] = (char*)malloc((word_len +1) * sizeof(char));

        strncpy((*lista_inputs)[string_atual], &input[n_atual], word_len);
        (*lista_inputs)[string_atual][word_len] = '\0';
        string_atual++;
        n_atual += word_len;
        }
    }

    (*lista_inputs)[string_atual] = NULL; // Null termina o array


    return existe_s;
}