#ifndef GESTOR_HISTORY_H
#define GESTOR_HISTORY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "history.h"

/**
 * @brief Estrutura que armazena o gestor de históricos.
 *
 * @param hashTable hashTable que armazena os históricos.
 */
typedef struct gestorHistory gestorHistory;

/**
 * @brief Cria um novo gestor de históricos.
 *
 * Aloca memória para um novo gestor de históricos e inicializa a hashTable com as funções de hash e comparação de strings.
 *
 * @return Ponteiro para o gestor de históricos.
 */
gestorHistory* criaGestorHistory();

/**
 * @brief Liberta a memória alocada para o gestor de históricos.
 *
 * Liberta a memória alocada para a hashTable e para o gestor de históricos.
 *
 * @param gestor Ponteiro para o gestor de históricos.
 */
void freeGestorHistory(gestorHistory* gestor);

/**
 * @brief Insere um histórico na hashTable do gestorHistory.
 *
 * @param gestor Ponteiro para o gestor de históricos.
 * @param history Ponteiro para o histórico.
 */
void insereHistory(gestorHistory* gestor, History* history);

/**
 * @brief Procura e retorna um histórico específico da hashTable pelo historyId.
 *
 * @param gestor Ponteiro para o gestor de históricos.
 * @param historyId Id do histórico.
 */
History* procuraHistory(gestorHistory* gestor, const char* historyId);

#endif