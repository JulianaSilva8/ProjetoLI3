#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/music.h"

struct Music {
    char* musicid;
    char* title;
    char* artist_id;
    char* album_id;
    char* duration;
    char* genre;
    char* year;
    char* lyrics;
};

char* getMusicId(const Music* music) {
    return strdup(music->musicid);
}

char* getGenre(const Music* music) {
    return strdup(music->genre);
}

char* getMusicDuration(const Music* music) {
    return strdup(music->duration);
}

char* getMusicArtistId(const Music* music) {
    return strdup(music->artist_id);
}

char* getMusicAlbumId(const Music* music) {
    return strdup(music->album_id);
}

Music* criaMusic() {
    Music* music = (Music*)malloc(sizeof(Music));
    if (music == NULL) {
        fprintf(stderr, "Erro\n");
        exit(1);
    }
    music->musicid = NULL;
    music->title = NULL;
    music->artist_id = NULL;
    music->album_id = NULL;
    music->duration = NULL;
    music->genre = NULL;
    music->year = NULL;
    music->lyrics = NULL;
    return music;
}

void freeMusic(Music* musics) {
    free(musics->musicid);
    free(musics->title);
    free(musics->artist_id);
    free(musics->album_id);
    free(musics->duration);
    free(musics->genre);
    free(musics->year);
    free(musics->lyrics);
    free(musics);
}

void musicField(Music* music, int index, const char* value) {
    char* trim = strdup(value);
    // verificar as aspas
    if (trim[0] == '"' && trim[strlen(trim) - 1] == '"') {
        trim[strlen(trim) - 1] = '\0'; // remove as últimas aspas
        memmove(trim, trim + 1, strlen(trim)); // Shift para a esquerda para remover as primeiras aspas
    }

    switch (index) {
        case 0:
            music->musicid = strdup(trim);
            break;
        case 2:
            music->artist_id = strdup(trim);
            break;
        case 3:
            music->album_id = strdup(trim);
            break;
        case 4:
            music->duration = strdup(trim);
            break;
        case 5:
            music->genre = strdup(trim);
            break;
        default:
            break;
    }
    free(trim);
}

void printerro(Music* musica,int flag,char* header,char** token2) {
    char filename[64];
    FILE *cmd;

    sprintf(filename, "resultados/musics_errors.csv");
    cmd = fopen(filename, "a");
    if (flag == 0) fprintf(cmd, "%s\n",header);
    if (musica == NULL) {
        fprintf(cmd, "\n");
        fclose(cmd);
        return;
    }
    fprintf(cmd, "\"%s\";%s;\"%s\";\"%s\";\"%s\";\"%s\";%s;%s\n",
    musica->musicid, token2[1], musica->artist_id, musica->album_id,musica->duration, musica->genre, token2[6],token2[7]);
    fclose(cmd);
}