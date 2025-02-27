#ifndef Q3_H
#define Q3_H
#include <glib.h>
#include <stdio.h>
#include "tree.h"
#include "gestor_music.h"
#include "gestor_user.h"

/**
 * @brief Estrutura que armazena o número de gostos por género musical
 *
 * @param genre Género musical
 * @param count Número de gostos
 */
typedef struct  GenreCount GenreCount;

/**
 * @brief Estrutura que armazena o número total de gostos por género musical
 *
 * @param generoscount Array com o número de gostos por género musical
 */
typedef struct musicsgenders musicsgenders;

/**
 * @brief Função que compara o número de gostos por género musical
 *
 * @param a Género musical
 * @param b Género musical
 */
int compare_genre_counts(const void *a, const void *b);

/**
 * @brief Função que inicializa o número de gostos por género musical
 *
 * @return Número de gostos por género musical
 */
musicsgenders initialize_genre_counts();

/**
 * @brief Função que conta o número de gostos por género musical no intervalo
 *
 * @param start Idade inicial
 * @param end Idade final
 * @param arvore Árvore de músicas
 */
musicsgenders count_genres_in_range(int start, int end, GTree* arvore);

/**
 * @brief Função que verifica se todos os géneros têm contagem zero
 *
* @param genres Array com o número de gostos por género musical
* @param num_genres Número de géneros
 */
int check_all_genres_zero(GenreCount* genres, int num_genres);

/**
 * @brief Função que escreve o número de gostos por género musical no ficheiro
 *
 * @param line1 Linha atual do ficheiro
 * @param genres Array com o número de gostos por género musical
 * @param num_genres Número de géneros
 * @param all_zero Flag que indica se todos os géneros têm contagem zero
 * @param existe_s Flag que indica se o ficheiro tem a opção -s
 */
int write_genre_counts_to_file(int line1, GenreCount* genres, int num_genres, int all_zero, bool existe_s);

/**
 * @brief Query 3 - Esta função recebe duas idades e devolve o número total de gostos
 * por género musical
 *
 * Esta funçao recebe um intervalo de idades e devolve o número total de
 * gostos em cada género musical nesse intervalo
 *
 * @param line1 - linha atual do ficheiro
 * @param input - intervalo de idades
 * @param arvore - árvore de músicas
 */
int q3(int line1, char* input, GTree* arvore);

#endif