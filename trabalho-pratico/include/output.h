#ifndef OUTPUT_H
#define OUTPUT_H
#include <stdbool.h>

/**
 * @brief Adiciona uma string a um ficheiro para fazer o output.
 *
 * @param string String a adicionar.
 * @param n_atual Número do comando atual.
 * @param existe_s Flag que indica se o input tem 'S'.
 * @param ficheiro_vazio Flag que indica se o ficheiro está vazio.
 */
void output(char *string, int n_atual, bool existe_s, bool ficheiro_vazio);

#endif