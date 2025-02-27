#ifndef Q4_H
#define Q4_H
#include <glib.h>
#include <stdio.h>
#include "tree_data_history.h"
#include "gestor_music.h"
#include "gestor_artist.h"
#include "gestor_user.h"

/**
 * @brief Query 4 - Esta função recebe duas datas e devolve informações do artista
 * que esteve mais vezes no top 10 semanal nesse intervalo.
 *
 * Esta funçao recebe um intervalo de datas e devolve o id, o tipo e o número de vezes que
 * esse artista esteve no top 10 semanal nesse intervalo. Se não for especificado um intervalo,
 * é devolvida a informação do artista que esteve mais vezes no top 10 semanal desde sempre. O
 * top 10 é feito de acordo com a duração total de música ouvida.
 *
 * @param input - input do ficheiro
 * @param atualine - linha atual do ficheiro
 * @param gestor_a - gestor de artistas
 * @param tree_data - árvore do histórico
 */
int query4(char *input, int atualine, gestorArtist* gestor_a, GTree* tree_data);

#endif