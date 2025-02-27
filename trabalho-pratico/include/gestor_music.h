#ifndef GESTOR_MUSIC_H
#define GESTOR_MUSIC_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "gestor_artist.h"
#include "gestor_albuns.h"
#include "music.h"

/**
 * @brief Estrutura que armazena o gestor de músicas.
 *
 * @param hashTable hashTable que armazena as músicas.
 */
typedef struct gestorMusic gestorMusic;

/**
 * @brief Estrutura para iterar sobre a hashTable de músicas.
 *
 * Esta estrutura contém um iterador para a hashTable de músicas e um indicador de inicialização.
 */
typedef struct {
    GHashTableIter iter;
    gboolean initialized; 
} MusicIterator;

/**
 * @brief Cria um novo gestor de músicas.
 *
 * Aloca memória para um novo gestor de músicas e inicializa a hashTable com as funções de hash e comparação de strings.
 *
 * @return Ponteiro para o gestor de músicas.
 */
gestorMusic* criaGestorMusic();

/**
 * @brief Insere uma música no gestor de músicas.
 *
 * @param gestor Ponteiro para o gestor de músicas.
 * @param music Ponteiro para a música.
 */
void insereMusic(gestorMusic* gestor, Music* Music);

/**
 * @brief Procura uma música no gestor de músicas.
 *
 * @param gestor Ponteiro para o gestor de músicas.
 * @param music Id da música.
 */
Music* procuraMusic(gestorMusic* hashTable, const char* music);

/**
 * @brief Liberta a memória alocada para o gestor de músicas.
 *
 * Liberta a memória alocada para a hashTable e para o gestor de músicas.
 *
 * @param gestor Ponteiro para o gestor de músicas.
 */
void freeGestorMusic(gestorMusic* gestor);

/**
 * @brief Procura uma música no gestor de músicas.
 *
 * @param gestor Ponteiro para o gestor de músicas.
 * @param key Id da música.
 */
Music* gestorMusic_lookup(gestorMusic* gestor, const char* key);


/**
 * @brief Inicializa um iterador de músicas.
 *
 * Inicializa um iterador para percorrer a hashTable de músicas.
 *
 * @param musicIterator Ponteiro para o iterador de músicas.
 * @param musicTable Ponteiro para o gestor de músicas.
 */
void initMusicIterator(MusicIterator* musicIterator, gestorMusic* musicTable);

/**
 * @brief Retorna a próxima música no iterador.
 *
 * Retorna a próxima música no iterador de músicas. Se não houver mais músicas, retorna NULL.
 *
 * @param musicIterator Ponteiro para o iterador de músicas.
 * @return Ponteiro para a próxima música ou NULL se não houver mais músicas.
 */
Music* getNextMusic(MusicIterator* musicIterator);

#endif