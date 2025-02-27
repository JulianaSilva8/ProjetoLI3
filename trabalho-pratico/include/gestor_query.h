#ifndef GESTOR_QUERY_H
#define GESTOR_QUERY_H
#include "gestor_user.h"
#include "gestor_music.h"
#include "gestor_artist.h"
#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q6.h"
#include "tree.h"
#include "tree_data_history.h"

/**
 * @brief Função que executa as queries de acordo com o número do input.
 *
 * @param input - input do ficheiro
 * @param line1 - linha atual do ficheiro
 * @param hashTableusers - gestor de utilizadores
 * @param hashTablemusics - gestor de músicas
 * @param hashTableartists - gestor de artistas
 * @param arvore - árvore de músicas
 * @param tree_data - árvore do histórico
 * @param matriz_q5 - matriz com os dados
 */
void gestor_query(char* input,int line1,gestorUser* hashTableusers,gestorMusic* hashTablemusics, gestorArtist* hashTableartists,GTree* arvore, GTree* tree_data, void** matriz_q5);

#endif