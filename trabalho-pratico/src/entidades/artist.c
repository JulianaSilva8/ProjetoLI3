#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/types.h>
#include "../../include/artist.h"
#include "../../include/gestor_music.h"
#include "../../include/output.h"
#include "../../include/utils.h"

struct Artist {
    char* artistId;
    char* name;
    char* description;
    char* recipe_per_stream;
    char* id_constituent;
    char* country;
    char* type;
    int artistDuration;
    int album_count;
    float total_recipe;
    float total_recipe_part;
};

char* getArtistId(const Artist* artist) {
    return strdup(artist->artistId);
}

char* getArtistCountry(const Artist* artist) {
    return strdup(artist->country);
}

char* getArtistName(const Artist* artist) {
    return strdup(artist->name);
}

char* getArtistType(const Artist* artist) {
    return strdup(artist->type);
}

char* getArtistIdConstituent(const Artist* artist) {
    return strdup(artist->id_constituent);
}

int getArtistDuration(const Artist* artist) {
    return artist->artistDuration;
}

int getArtistAlbumCount(const Artist* artist) {
    return artist->album_count;
}

void setAlbumCount(Artist* artist) {
    artist->album_count++;
}

void setRepCount(Artist* artist) {
    artist->total_recipe+= atof(artist->recipe_per_stream);
}

void setRepCountPart(Artist* artist,Artist* artist_a,int num) {
    artist->total_recipe_part+= atof(artist_a->recipe_per_stream)/num;
}

void addArtistDuration(Artist* artist, int duration) {
    if (artist != NULL) {
        artist->artistDuration += duration;
    }
}

Artist* criaArtist() {
    Artist* artist = (Artist*)malloc(sizeof(Artist));
    if (artist == NULL) {
        fprintf(stderr, "Erro\n");
        exit(1);
    }
    artist->artistId = NULL;
    artist->name = NULL;
    artist->description = NULL;
    artist->recipe_per_stream = NULL;
    artist->id_constituent = NULL;
    artist->country = NULL;
    artist->type = NULL;
    artist->artistDuration = 0;
    artist->album_count = 0;
    artist->total_recipe = 0;
    artist->total_recipe_part = 0;
    return artist;
}

void freeArtist(Artist* artists) {
    free(artists->artistId);
    free(artists->name);
    free(artists->description);
    free(artists->recipe_per_stream);
    free(artists->id_constituent);
    free(artists->country);
    free(artists->type);
    free(artists);
}

void artistField(Artist* artist, int index, const char* value) {
    char* trim = strdup(value);
    // Verifica as aspas
    if (trim[0] == '"' && trim[strlen(trim) - 1] == '"') {
        trim[strlen(trim) - 1] = '\0'; // Remove as últimas aspas
        memmove(trim, trim + 1, strlen(trim)); // Shift para a esquerda para remover as primeiras
    }

    switch (index) {
        case 0:
            artist->artistId = strdup(trim);
            break;
        case 1:
            artist->name = strdup(trim);
            break;
         case 3:
             artist->recipe_per_stream = strdup(trim);
             break;
        case 4:
            artist->id_constituent = strdup(trim);
            break;
        case 5:
            artist->country = strdup(trim);
            break;
        case 6:
            artist->type = strdup(trim);
            break;
        default:
            break;
    }
    free(trim);
}

void resetArtistDuration(Artist* artist) {
    if (artist != NULL) {
        artist->artistDuration = 0;
    }
}

int comparaArtistDuration(const Artist* a, const Artist* b) {
    return b->artistDuration - a->artistDuration;
}

GList* ordenaArtistasPorDuracao(GList* artistList) {
    return g_list_sort(artistList, (GCompareFunc)comparaArtistDuration);
}

bool validaElementos(const char* type, const char* id_constituent) {
    // strcasecmp para ignorar maiúsculas e minúsculas
    return !(strcasecmp(type, "individual") == 0 && strlen(id_constituent) != 2);
}

/**
 * Função que cria uma matriz com os dados para o output das queries 1 e 2.
 */
void matriz_q1_artist(char ***matrix, const Artist *artist) {

    *matrix = (char **)malloc(6 * sizeof(char *));

    (*matrix)[0] = (char *)malloc((strlen(artist->name) + 1) * sizeof(char));
    strcpy((*matrix)[0], artist->name);

    (*matrix)[1] = (char *)malloc((strlen(artist->type) + 1) * sizeof(char));
    strcpy((*matrix)[1], artist->type);

    char string_duration[16];

    int hours = artist->artistDuration / 3600;
    int minutes = (artist->artistDuration % 3600) / 60;
    int seconds = artist->artistDuration % 60;

    sprintf(string_duration, "%02d:%02d:%02d", hours, minutes, seconds);

    (*matrix)[2] = (char *)malloc((strlen(string_duration) + 1) * sizeof(char));
    strcpy((*matrix)[2], string_duration);

    (*matrix)[3] = (char *)malloc((strlen(artist->country) + 1) * sizeof(char));
    strcpy((*matrix)[3], artist->country);

    int num_alb = artist->album_count;

    char num_alb_str[12];
    sprintf(num_alb_str, "%d", num_alb);

    (*matrix)[4] = (char *)malloc((strlen(num_alb_str) + 1) * sizeof(char));
    strcpy((*matrix)[4], num_alb_str);

    float count =  artist->total_recipe + artist->total_recipe_part;

    char count_str[16];
    sprintf(count_str, "%.2f", count);

    (*matrix)[5] = (char *)malloc((strlen(count_str) + 2) * sizeof(char));
    strcpy((*matrix)[5], count_str);
    int t = strlen(count_str);
    (*matrix)[5][t] = '\n'; // Adiciona '\n' ao final
    (*matrix)[5][t + 1] = '\0';  // Adiciona o caractere nulo ao final
}

void printArtist(Artist *artist, int n, int ficheiro_vazio, bool existe_s) {
    if (artist == NULL) {
        output(NULL, n, true, ficheiro_vazio);
    } else {
        char **matrix = NULL;
        matriz_q1_artist(&matrix, artist);

        for (int i = 0; i < 4; i++) {
            output(matrix[i], n, existe_s, 0);
        }
        output("\n", n, existe_s, 0);

        freeMatrix(matrix, 6);
    }
}

void imprimeTopNArtistas(GList *artistList, int N, int n_atualine, bool existe_s) {
    GList *current = artistList; // Aponta para o início da lista
    int artistasImpressos = 0;
    while (current != NULL && artistasImpressos < N) { // Enquanto houver artistas e ainda não tivermos impresso N artistas
        Artist *artist = (Artist *)current->data;
        printArtist(artist, n_atualine, 0, existe_s);
        current = current->next;
        artistasImpressos++;
    }

    // Se não printarmos artistas (lista vazia ou N == 0), cria na mesma o ficheiro com o \n
    if (artistasImpressos == 0) {
        printArtist(NULL, n_atualine, 1, existe_s);
    }
}

/**
 * Função que cria uma matriz com os dados para o output da query 4
 */
void getDataToMatrix2(char ***matrix, char* topartist, int max_freq, char* tipo) {
    *matrix = (char **)malloc(3 * sizeof(char *));

    (*matrix)[0] = (char *)malloc((strlen(topartist) + 1) * sizeof(char));
    strcpy((*matrix)[0], topartist);

    (*matrix)[1] = (char *)malloc((strlen(tipo) + 1) * sizeof(char));
    strcpy((*matrix)[1], tipo);

    char frequencia[16];
    sprintf(frequencia, "%d", max_freq);

    (*matrix)[2] = (char *)malloc((strlen(frequencia) + 2) * sizeof(char));
    strcpy((*matrix)[2], frequencia);
}

void printArtist2(char* topartist, int n, int ficheiro_vazio, char* tipo, int max_freq, bool existe_s) {
    if (topartist == NULL) {
        output(NULL, n, true, ficheiro_vazio);
    } else {
        char **matrix = NULL;
        getDataToMatrix2(&matrix, topartist, max_freq, tipo);

        for (int i = 0; i < 3; i++) {
            output(matrix[i], n, existe_s, 0);
        }

        output("\n", n, existe_s, 0);

        freeMatrix(matrix, 3);
    }
}

void erroArtist(Artist* artist,int flag,char* header,char* token2) {
    char filename[64];
    FILE *cmd;

    sprintf(filename, "resultados/artists_errors.csv");
    cmd = fopen(filename, "a");
    if (flag == 0) fprintf(cmd, "%s\n",header);
    if (artist == NULL) {
        fprintf(cmd, "\n");
        fclose(cmd);
        return;
    }
    fprintf(cmd, "\"%s\";\"%s\";%s;\"%s\";\"%s\";\"%s\";\"%s\"\n",
    artist->artistId, artist->name, token2, artist->recipe_per_stream, artist->id_constituent, artist->country, artist->type);
    fclose(cmd);
}