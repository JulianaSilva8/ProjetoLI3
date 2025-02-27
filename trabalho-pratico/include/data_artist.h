#ifndef DATA_ARTIST_H
#define DATA_ARTIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura que armazena o Id do artista e o tempo total de reprodução.
 *
 * @param artist_id Id do artista.
 * @param time Tempo total de reprodução.
 */
typedef struct Data_artist Data_artist;

/**
 * @brief Retorna o Id do artista.
 *
 * @param artist Ponteiro para a estrutura Data_artist.
 */
char* getData_ArtistId(const Data_artist* artist);

/**
 * @brief Retorna o tempo de reprodução do histórico.
 *
 * @param artist Ponteiro para a estrutura Data_artist.
 */
int getTime(const Data_artist* artist);

/**
 * @brief Define o Id do artista.
 *
 * @param artist Ponteiro para a estrutura Data_artist.
 * @param new_id Novo Id do artista.
 */
void setData_ArtistId(Data_artist* artist, const char* new_id);

/**
 * @brief Define o tempo de reprodução do histórico.
 *
 * @param artist Ponteiro para a estrutura Data_artist.
 * @param new_time Novo tempo de reprodução.
 */
void setTime(Data_artist* artist, int new_time);

/**
 * @brief Adiciona tempo ao tempo de reprodução do histórico.
 *
 * @param artist Ponteiro para a estrutura Data_artist.
 * @param add_time Tempo a adicionar.
 */
void addTime(Data_artist* artist, int add_time);

/**
 * @brief Cria uma nova estrutura Data_artist.
 *
 * Aloca memória para uma nova estrutura Data_artist e inicializa os campos com NULL.
 *
 * @return Ponteiro para a estrutura Data_artist.
 */
Data_artist* createDataArtist();

/**
 * @brief Liberta a memória alocada para a estrutura Data_artist.
 *
 * Liberta a memória alocada para os campos da estrutura Data_artist e para a estrutura em si.
 *
 * @param artist Ponteiro para a estrutura Data_artist.
 */
void freeDataArtist(Data_artist* artist);

#endif