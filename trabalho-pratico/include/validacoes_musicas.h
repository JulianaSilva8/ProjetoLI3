#ifndef VALIDACOES_MUSICAS_H
#define VALIDACOES_MUSICAS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include "gestor_artist.h"
#include "gestor_albuns.h"
#include "artist.h"

/**
 * @brief Valida se o tempo está no formato correto.
 *
 * @param tempo Tempo a validar.
 */
int validatempo(const char* tempo);

/**
 * @brief Valida se os artistas existem e estão no formato correto.
 *
 * @param artista Artista a validar.
 * @param Table_artistas Gestor de artistas.
 */
int validaartistas(char* artista, gestorArtist* Table_artistas);

/**
 * @brief Recebe vários artistas e processa cada um.
 *
 * @param artistas String com os artistas.
 * @param Table_artistas Gestor de artistas.
 * @param flag Flag que indica o que fazer com os artistas.
 */
void artists_id_process(char* artistas,gestorArtist* Table_artistas,int flag);

/**
 * @brief Valida se os albuns existem no gestor albuns e se estão no formato correto.
 *
 * @param albuns Albuns a validar.
 * @param Table_albuns Gestor de albuns.
 */
int validaAlbuns(const char* albuns, gestorAlbuns* Table_albuns);

#endif