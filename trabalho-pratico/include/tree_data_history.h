#ifndef TREE_DATA_HISTORY_H
#define TREE_DATA_HISTORY_H
#include <glib.h>
#include "data_artist.h"

/**
 * @brief Estrutura que armazena os dados relativos ao histórico.
 *
 * @param value Valor do nodo.
 * @param hashTable hashTable.
 */
typedef struct Node {
    int value;
    GHashTable* hashTable;
} Node;

/**
 * @brief Estrutura que armazena o Id do artista e a duração total.
 *
 * @param artist_id Id do artista.
 * @param duration Duração total.
 */
typedef struct {
    char* artist_id;
    int duration;
} ArtistDuration;

/**
 * @brief Cria um novo nodo.
 *
 * Aloca memória para um novo nodo e inicializa os campos com NULL.
 *
 * @param value Valor do nodo.
 */
Node* createHistoryNode(int value);

/**
 * @brief Liberta a memória alocada para um nodo.
 *
 * Liberta a memória alocada para os campos de um nodo e para o nodo em si.
 *
 * @param node Ponteiro para o nodo.
 */
void freeHistoryNode(Node* node);

/**
 * @brief Insere um valor na hashTable de um nodo.
 *
 * @param node Ponteiro para o nodo.
 * @param key Chave do valor.
 * @param data_artist Ponteiro para a estrutura Data_artist.
 */
void insertInHistoryHash(Node* node, const char* key, Data_artist* data_artist);

/**
 * @brief Procura um valor na hashTable de um nodo.
 *
 * @param node Ponteiro para o nodo.
 * @param key Chave do valor.
 */
Data_artist* lookupInHistoryHash(Node* node, const char* key);

/**
 * @brief Procura um nodo na árvore.
 *
 * @param tree Árvore.
 * @param value Valor do nodo.
 */
Node* findHistoryNode(GTree* tree, int value);

/**
 * @brief Função de comparação para ordenação.
 *
 * @param a Ponteiro para o primeiro valor.
 * @param b Ponteiro para o segundo valor.
 */
gint compareHistoryInts(gconstpointer a, gconstpointer b);

/**
 * @brief Inicializa a árvore de histórico.
 */
GTree* init_history_tree();

/**
 * @brief Encontra ou cria um nodo na árvore.
 *
 * @param tree Árvore.
 * @param val Valor do nodo.
 */
Node* findOrCreateHistoryNode(GTree* tree, int val);

/**
 * @brief Destroi a árvore de histórico.
 *
 * @param tree Árvore.
 */
void destroy_history_tree(GTree* tree);

/**
 * @brief Cria a árvore de histórico.
 *
 * @param tree Árvore.
 * @param timestamp Timestamp.
 * @param artist_id Id do artista.
 * @param duration Duração.
 */
void build_history_tree(GTree* tree, char* timestamp, char* artist_id, char* duration);

/**
 * @brief Compara a duração de dois artistas.
 *
 * @param a Ponteiro para o primeiro artista.
 * @param b Ponteiro para o segundo artista.
 */
gint compareArtistDurationDesc(gconstpointer a, gconstpointer b);

/**
 * @brief Liberta a memória alocada para a estrutura ArtistDuration.
 *
 * @param data Ponteiro para a estrutura ArtistDuration.
 */
void freeArtistDuration(gpointer data);

/**
 * @brief Processa um nodo para obter o top 10 artistas de todos os artistas.
 *
 * @param key Chave do nodo.
 * @param value Valor do nodo.
 * @param user_data Dados do utilizador.
 */
gboolean process_node_top10(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Processa um nodo para obter o top 10 artistas dos artistas do intervalo de input da query 4.
 *
 * @param node Ponteiro para o nodo.
 * @param global_freq Frequência global.
 */
void NodeForTop10(Node* node, GHashTable* global_freq);

#endif