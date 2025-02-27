#ifndef Q2_H
#define Q2_H
#include "gestor_music.h"
#include "gestor_artist.h"

/**
 * @brief Acumula a duração de todas as músicas de um artista
 *
 * Esta função recebe um gestor de artistas e um gestor de músicas e acumula a duração
 * de todas as músicas de um artista.
 *
 * @param gestorArtist - gestor de artistas
 * @param gestorMusic - gestor de músicas
 */
void acumulaDuracaoArtistas(gestorArtist* gestorArtist, gestorMusic* gestorMusic);

/**
 * @brief Query 2 - Recebe um número N e um país (opcional) e devolve o Top N artistas
 * com mais duração total de música nesse país
 *
 * Se o país não for especificado, devolve o Top N artistas com mais duração total de
 * música mundialmente, se for recebe apenas desse país.
 *
 * @param input - Número N e país (opcional)
 * @param atualine - linha atual do ficheiro
 * @param gestorArtist - gestor de artistas
 * @param gestorMusic - gestor de músicas
 */
int query2(char *input, int atualine, gestorArtist* gestorArtist, gestorMusic* gestorMusic);

#endif