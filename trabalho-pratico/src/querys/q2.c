#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <glib.h>
#include "../../include/q2.h"
#include "../../include/gestor_artist.h"
#include "../../include/gestor_music.h"
#include "../../include/parser_inputs.h"
#include "../../include/utils.h"

void acumulaDuracaoArtistas(gestorArtist* gestorArtist, gestorMusic* gestorMusic) {
    MusicIterator musicIterator;
    initMusicIterator(&musicIterator, gestorMusic);

    Music* music;
    while ((music = getNextMusic(&musicIterator)) != NULL) {
        char* artistIdListStr = getMusicArtistId(music);
        char* musicD = getMusicDuration(music);
        int duration = durationToseconds(musicD); // Converte a duração para segundos para facilitar a soma
        char* artistIdsStr = strdup(artistIdListStr); // Copia a string para não a alterar
        free(artistIdListStr);
        // Encontra o primeiro e último parentices
        char* start = strchr(artistIdsStr, '[');
        char* end = strrchr(artistIdsStr, ']');

        // Se encontrar os parentices remove-os
        if (start && end && start < end) {
            *end = '\0';
            memmove(artistIdsStr, start + 1, strlen(start));
        }

        // Remove as aspas e espaços
        for (char* p = artistIdsStr; *p; p++) {
            if (*p == '\'' || *p == ' ') {
                memmove(p, p + 1, strlen(p));
                p--;
            }
        }
        char* token = strtok(artistIdsStr, ","); // Separa os artistas por vírgula
        // Percorre os artistas e soma a duração
        while (token != NULL) {
            char* artistId = strdup(token);
            Artist* artist = procuraArtist(gestorArtist, artistId); // Procura o artista

            addArtistDuration(artist, duration);  // Soma a duração
            free(artistId);
            token = strtok(NULL, ",");
        }
        free(musicD);
        free(artistIdsStr);
    }
}

int query2(char *input, int atualine, gestorArtist* gestorArtist, gestorMusic* gestorMusic) {

    bool existe_S = false;
    char **lista_inputs = NULL;

    existe_S = gestor_parser(input, existe_S, &lista_inputs);

    int N = atoi(lista_inputs[0]);

    // Reseta a duração dos artistas
    resetArtistDurations(gestorArtist);

    // Acumula a duration das musicas por artista
    acumulaDuracaoArtistas(gestorArtist, gestorMusic);

    // Filtra os artistas por pais e ordena por ordem decrescente
    GList* artistList = filtraArtistasPorPais(gestorArtist, lista_inputs[1]);
    artistList = ordenaArtistasPorDuracao(artistList);

    // Imprime o top N artistas
    imprimeTopNArtistas(artistList, N, atualine,existe_S);

    g_list_free(artistList);

    // free memoria
    for (int i = 0; lista_inputs[i] != NULL; i++) {
        free(lista_inputs[i]);
    }
     free(lista_inputs);


    return 0;
}