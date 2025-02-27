#ifndef LOAD_DB_H
#define LOAD_DB_H
#include "gestor_user.h"
#include "gestor_artist.h"
#include "gestor_music.h"
#include "gestor_albuns.h"
#include "gestor_history.h"

/**
 * @brief Carrega os utilizadores do ficheiro.
 *
 * @param fp Ponteiro para o ficheiro.
 * @param gestorMusic Ponteiro para o gestor de músicas.
 */
gestorUser* load_users(FILE* fp, gestorMusic* gestorMusic);

/**
 * @brief Carrega os artistas do ficheiro.
 *
 * @param fp Ponteiro para o ficheiro.
 */
gestorArtist* load_artists(FILE* fp);

/**
 * @brief Carrega as músicas do ficheiro.
 *
 * @param fp Ponteiro para o ficheiro.
 * @param gestorArtistas Ponteiro para o gestor de artistas.
 * @param gestorAlbuns Ponteiro para o gestor de álbuns.
 */
gestorMusic* load_musics(FILE* fp,gestorArtist* gestorArtistas, gestorAlbuns* gestorAlbuns);

/**
 * @brief Carrega os álbuns do ficheiro.
 *
 * @param fp Ponteiro para o ficheiro.
 * @param gestorArtistas Ponteiro para o gestor de artistas.
 */
gestorAlbuns* load_albuns(FILE* fp,gestorArtist* gestorArtistas);

/**
 * @brief Carrega o histórico do ficheiro.
 *
 * @param fp Ponteiro para o ficheiro.
 * @param gestor Ponteiro para o gestor de utilizadores.
 * @param gestor_m Ponteiro para o gestor de músicas.
 * @param gestor_a Ponteiro para o gestor de artistas.
 */
GTree* load_historical(FILE* fp, gestorUser* gestor, gestorMusic* gestor_m,gestorArtist* gestor_a);

#endif