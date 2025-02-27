#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>

/**
 * @brief Função que converte uma string de duração para segundos se estiver no
 * formato correto.
 *
 * @param duration String de duração.
 */
int durationToseconds(const char* duration);

/**
 * @brief Calcula a diferença de semanas entre a data de entrada e a data de referência.
 *
 * A data de referência é 2024/09/09 e foi dada no guião.
 *
 * @param dataStr Data de entrada.
 */
int calculateDateDifference(const char* dateStr);

/**
 * @brief Função que liberta a memória alocada para uma matriz.
 *
 * @param matrix Matriz a libertar.
 * @param size Tamanho da matriz.
 */
void freeMatrix(char **matrix, int size);

/**
 * @brief Faz o parsing de uma string de artistas.
 *
 * @param artists_str String de artistas.
 */
char** parse_Artist_string(char* artists_str);

/**
 * @brief Converte uma duração no formato "HH:MM:SS" para segundos.
 *
 * Esta função converte uma string de duração no formato "HH:MM:SS" para o total de segundos.
 *
 * @param duracao String contendo a duração no formato "HH:MM:SS".
 * @return O total de segundos representado pela duração.
 */
int duracao_to_seconds(const char* duracao);

#endif