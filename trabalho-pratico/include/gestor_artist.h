#ifndef GESTOR_ARTIST_H
#define GESTOR_ARTIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "artist.h"

/**
 * @brief Estrutura que armazena o gestor de artistas.
 *
 * @param hashTable hashTable que armazena os artistas.
 */
typedef struct gestorArtist gestorArtist;

/**
 * @brief Verifica se um artista existe no gestor de artistas.
 *
 * @param a Gestor de artistas.
 * @param artisteId Id do artista.
 */
bool gestorArtist_existeArtista(gestorArtist* gestor, const char* id);

/**
 * @brief Cria um novo gestor de artistas.
 *
 * Aloca memória para um novo gestor de artistas e inicializa a hashTable com as funções de hash e comparação de strings.
 *
 * @return Ponteiro para o gestor de artistas.
 */
gestorArtist* criaGestorArtist();

/**
 * @brief Liberta a memória alocada para o gestor de artistas.
 *
 * Liberta a memória alocada para a hashTable e para o gestor de artistas.
 *
 * @param gestor Ponteiro para o gestor de artistas.
 */
void freeGestorArtist(gestorArtist* gestor);

/**
 * @brief Insere um artista no gestor de artistas.
 *
 * @param gestor Ponteiro para o gestor de artistas.
 * @param artist Ponteiro para o artista.
 */
void insereArtist(gestorArtist* gestor, Artist* artist);

/**
 * @brief Procura um artista no gestor de artistas.
 *
 * @param gestor Ponteiro para o gestor de artistas.
 * @param artist_id Id do artista.
 */
Artist* procuraArtist(gestorArtist* gestor, const char* artist_id);

/**
 * @brief Reseta a duração de todos os artistas para 0.
 *
 * @param gestorArtist Ponteiro para o gestor de artistas.
 */
void resetArtistDurations(gestorArtist* gestorArtist);

/**
 * @brief Filtra os artistas por país.
 *
 * @param gestorArtist Ponteiro para o gestor de artistas.
 * @param country País a filtrar.
 */
GList* filtraArtistasPorPais(gestorArtist* gestorArtist, const char* country);

#endif