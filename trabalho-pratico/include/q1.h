#ifndef Q1_H
#define Q1_H
#include "gestor_user.h"
#include "gestor_artist.h"

/**
 * @brief Query 1 - Recebe um Id de um utilizador ou artista e devolve algumas informações sobre o mesmo
 *
 * Esta função tem dois casos, ou recebe o número de identificação de um utilizador e retorna o seu email,
 * primeiro nome, último nome, idade e país, ou recebe o número de identificação de um artista e retorna o seu nome,
 * tipo, país, número de albums feitos individualmente e a receita total do mesmo.
 *
 * @param input - Id do utilizador ou artista
 * @param atualine - linha atual do ficheiro
 * @param gestor - gestor de utilizadores
 * @param gestor_a - gestor de artistas
 */
int query1(char *input, int atualine, gestorUser* gestor,gestorArtist* gestor_a);

#endif