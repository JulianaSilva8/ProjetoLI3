#ifndef PARSER_INPUTS_H
#define PARSER_INPUTS_H
#include <stdbool.h>


/**
 * @brief Parser de inputs.
 *
 * @param input Input.
 * @param existe_s Flag que indica se o input tem 'S'.
 * @param lista_inputs Lista de strings.
 */
bool gestor_parser(char* input, bool existe_s, char*** lista_inputs);

#endif