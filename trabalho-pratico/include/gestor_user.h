#ifndef GESTOR_USER_H
#define GESTOR_USER_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <glib.h>
#include "user.h"
#include "gestor_music.h"

/**
 * @brief Estrutura que armazena o gestor de utilizadores.
 *
 * @param hashTable hashTable que armazena os utilizadores.
 */
typedef struct gestorUser gestorUser;

/**
 * @brief Estrutura que armazena o iterador de utilizadores.
 *
 * @param iter Iterador da hashTable.
 * @param initialized Flag que indica se o iterador foi inicializado.
 */
typedef struct {
    GHashTableIter iter;
    gboolean initialized;
} UserIterator;

/**
 * @brief Cria um novo gestor de utilizadores.
 *
 * Aloca memória para um novo gestor de utilizadores e inicializa a hashTable com as funções de hash e comparação de strings.
 *
 * @return Ponteiro para o gestor de utilizadores.
 */
gestorUser* criaGestorUser();

/**
 * @brief Liberta a memória alocada para o gestor de utilizadores.
 *
 * Liberta a memória alocada para a hashTable e para o gestor de utilizadores.
 *
 * @param gestor Ponteiro para o gestor de utilizadores.
 */
void freeGestorUser(gestorUser* gestor);

/**
 * @brief Insere um utilizador no gestor de utilizadores.
 *
 * @param gestor Ponteiro para o gestor de utilizadores.
 * @param user Ponteiro para o utilizador.
 */
void insereUser(gestorUser* gestorUser, User* user);

/**
 * @brief Procura um utilizador no gestor de utilizadores.
 *
 * @param gestor Ponteiro para o gestor de utilizadores.
 * @param username Nome de utilizador.
 */
User* procuraUser(gestorUser* gestorUser, const char* username);


/**
 * @brief Inicializa o iterador de utilizadores.
 *
 * @param userIterator Ponteiro para o iterador de utilizadores.
 * @param gestorUser Ponteiro para o gestor de utilizadores.
 */
void initUserIterator(UserIterator* userIterator, gestorUser* gestorUser);

/**
 * @brief Obtém o próximo utilizador.
 *
 * @param userIterator Ponteiro para o iterador de utilizadores.
 */
User* getNextUser(UserIterator* userIterator);

/**
 * @brief Retorna o número de utilizadores.
 *
 * @param hashtable Ponteiro para o gestor de utilizadores.
 */
unsigned long int getNumberUser(gestorUser* gestorUser);

#endif