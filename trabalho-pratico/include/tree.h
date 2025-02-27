#ifndef TREE_H
#define TREE_H
#include <glib.h>
#include "q3.h"
#include "gestor_user.h"
#include "gestor_artist.h"

/**
 * @brief Estrutura que armazena os dados relativos ao nodo.
 *
 * @param value Valor do nodo.
 * @param generoscount Contagem de reproduções por género.
 */
typedef struct Node Node;

/**
 * @brief Estrutura que armazena os dados relativos aos géneros.
 *
 * @param Metal Contagem de reproduções de Metal.
 * @param Pop Contagem de reproduções de Pop.
 * @param Rock Contagem de reproduções de Rock.
 * @param Blues Contagem de reproduções de Blues.
 * @param Hip_Hop Contagem de reproduções de Hip Hop.
 * @param Classical Contagem de reproduções de Classical.
 * @param Country Contagem de reproduções de Country.
 * @param Electronic Contagem de reproduções de Electronic.
 * @param Jazz Contagem de reproduções de Jazz.
 * @param Reggae Contagem de reproduções de Reggae.
 */
typedef struct Generos Generos;

/**
 * @brief Retorna a contagem de reproduções de um género.
 *
 * @param node Ponteiro para o nodo.
 * @param i Índice do género.
 */
long int getCount(Node* Node, int i);

/**
 * @brief Compara dois inteiros.
 *
 * @param a Ponteiro para o primeiro valor.
 * @param b Ponteiro para o segundo valor.
 */
gint compare_ints(gconstpointer a, gconstpointer b);

/**
 * @brief Cria um novo nodo.
 *
 * Aloca memória para um novo nodo e inicializa os campos com NULL.
 *
 * @param value Valor do nodo.
 */
Node* createNode(int value);

/**
 * @brief Insere uma música no nodo.
 *
 * @param node Ponteiro para o nodo.
 * @param genre Género da música.
 */
void insertMusic(Node* node, const char* genre);

/**
 * @brief Constrói uma árvore balanceada.
 *
 * @param tree Árvore.
 * @param arr Array com os valores.
 * @param start Início do array.
 * @param end Fim do array.
 */
void buildBalancedTree(GTree* tree, int arr[], int start, int end);

/**
 * @brief Função principal para processar os dados e construir a árvore.
 *
 * @param userTable1 Tabela de utilizadores.
 * @param musicTable1 Tabela de músicas.
 */
GTree* binarytree(gestorUser* userTable1, gestorMusic* musicTable1);

/**
 * @brief Liberta a memória alocada para a árvore.
 *
 * @param tree Árvore.
 */
void freeTree(GTree* tree);

#endif