#ifndef MUSIC_H
#define MUSIC_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Estrutura que armazena os dados relativos à música.
 *
 * @param musicid Id da música.
 * @param title Título da música.
 * @param artist_id Id do artista.
 * @param album_id Id do álbum.
 * @param duration Duração da música.
 * @param genre Género da música.
 * @param year Ano de lançamento da música.
 * @param lyrics Letra da música.
 */
typedef struct Music Music;

/**
 * @brief Retornao Id da música.
 *
 * @param music Ponteiro para a música.
 */
char* getMusicId(const Music* music);

/**
 * @brief Retorna Id do artista da música.
 *
 * @param music Ponteiro para a música.
 */
char* getMusicArtistId(const Music* music);

/**
 * @brief Retorna Id do álbum da música.
 *
 * @param music Ponteiro para a música.
 */
char* getMusicAlbumId(const Music* music);

/**
 * @brief Retorna a duração da música.
 *
 * @param music Ponteiro para a música.
 */
char* getMusicDuration(const Music* music);

/**
 * @brief Retorna o género da música.
 *
 * @param music Ponteiro para a música.
 */
char* getGenre(const Music* music);

/**
 * @brief Cria uma nova estrutura Music.
 *
 * Aloca memória para uma nova estrutura Music e inicializa os campos com NULL.
 *
 * @return Ponteiro para a estrutura Music.
 */
Music* criaMusic();

/**
 * @brief Liberta a memória alocada para a estrutura Music.
 *
 * Liberta a memória alocada para os campos da estrutura Music e para a estrutura em si.
 *
 * @param musics Ponteiro para a estrutura Music.
 */
void freeMusic(Music* musics);

/**
 * @brief Preenche um campo da música com o valor fornecido.
 *
 * @param musics Ponteiro para a estrutura Music.
 * @param index Índice do campo a preencher.
 * @param value Valor a preencher no campo.
 */
void musicField(Music* musics, int index, const char* value);

/**
 * @brief Envia as músicas não válidas para a pasta de erros.
 *
 * @param musica Ponteiro para a música.
 * @param flag Flag que indica se a música é válida.
 * @param header Cabeçalho do ficheiro.
 * @param token2 Token a ser impresso.
 */
void printerro(Music* musica,int flag,char* header,char** token2);

#endif