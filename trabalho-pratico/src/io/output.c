#include "../../include/output.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Verifica se o último caracter de um ficheiro é um '\n'.
 *
 * @param filename Nome do ficheiro.
 */
bool is_last_char_newline(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }

    fseek(file, -1, SEEK_END);
    char last_char = fgetc(file);
    fclose(file);

    return last_char == '\n';
}

void output(char *string, int n_atual, bool existe_s, bool ficheiro_vazio) {
    char filename[64];
    sprintf(filename, "resultados/command%d_output.txt", n_atual);

    FILE *check_file = fopen(filename, "r");
    bool file_exists = (check_file != NULL);
    if (file_exists) {
        fclose(check_file);
    }

    bool last_char_newline = file_exists && is_last_char_newline(filename);


    FILE *cmd = fopen(filename, "a");
    if (cmd == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    if (ficheiro_vazio) {
        fprintf(cmd, "\n");
    } else {
        char sym = existe_s ? '=' : ';';
        if (!file_exists || last_char_newline || string[0] == '\n') {
            fprintf(cmd, "%s", string);
        } else {
            fprintf(cmd, "%c%s", sym, string);
        }
    }
    fclose(cmd);
}