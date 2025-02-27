#ifndef Q6_H
#define Q6_H
#include "gestor_music.h"
#include "gestor_user.h"

/**
 * @file q6.h
 * @brief Declarações de tipos para a estrutura de dados da questão 6.
 */

/**
 * @brief Declaração opaca da struct User_q6.
 */
typedef struct User_q6 User_q6;

/**
 * @brief Declaração opaca da struct artistas_user.
 */
typedef struct artistas_user artistas_user;

/**
 * @brief Declaração opaca da struct diaCount.
 */
typedef struct diaCount diaCount;

/**
 * @brief Query 6 - Esta função recebe um id de um utilizador, um ano e um N
 * e devolve as estatísticas de um utilizador nesse ano.
 *
 * Esta funçao devolve estatísticas como o tempo que o utilizador ouve música,
 * o número de músicas únicas que ouve, o artista mais ouvido, o dia mais ouvido,
 * o género mais ouvido, o álbum favorito e a hora favorita. Se for recebido um N
 * devolve os N artistas mais ouvidos.
 *
 * @param input - input do ficheiro
 * @param atualine - linha atual do ficheiro
 * @param gestor - gestor de utilizadores
 * @param gestor_m - gestor de músicas
 */
int query6 (char *input, int atualine, gestorUser* gestor,gestorMusic* gestor_m);

#endif