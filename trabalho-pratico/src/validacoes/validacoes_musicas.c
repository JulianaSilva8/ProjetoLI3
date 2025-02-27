#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include <math.h>
#include "../../include/gestor_artist.h"
#include "../../include/gestor_music.h"
#include "../../include/artist.h"
#include "../../include/gestor_albuns.h"
#include "../../include/validacoes_musicas.h"

int validatempo(const char* tempo) {
    // checkar se length é 8 chars
    if (strlen(tempo) != 8) return 0;

    for (int i = 0; i < 8; i++) {
        if ((i == 2 || i == 5)) {
            if (tempo[i] != ':') return 0;
        } else {
            if (!isdigit((unsigned char)tempo[i])) return 0;
        }
    }

    char horas[3], minutos[3], segundos[3];
    strncpy(horas, tempo, 2);
    horas[2] = '\0';
    strncpy(minutos, tempo + 3, 2);
    minutos[2] = '\0';
    strncpy(segundos, tempo + 6, 2);
    segundos[2] = '\0';

    int h = atoi(horas);
    int m = atoi(minutos);
    int s = atoi(segundos);

    if (h < 0 || h > 99 || m < 0 || m > 59 || s < 0 || s > 59) return 0;

    return 1;
}

int validaartistas(char* artistas, gestorArtist* Table_artistas) {
    int tamanho = strlen(artistas);

    // verificar se n tem []
    if (artistas[0] != '[' || artistas[tamanho - 1] != ']') return 0;

    char* current = artistas + 1;  // saltar '['
    char id[9];  // 8 chars + null

    while (*current && current < artistas + tamanho - 1) {  // parar antes de ']'
        // ignorar espaço e ,
        while (*current && (*current == ' ' || *current == ',')) {
            current++;
        }

        // ignorar ' se existir
        if (*current == '\'') {
            current++;
        }

        // extrair o id
        if (strlen(current) < 8) return 0;
        strncpy(id, current, 8);
        id[8] = '\0';

        // validar formato id
        if (id[0] != 'A') return 0;
        for (int i = 1; i < 8; i++) {
            if (!isdigit(id[i])) return 0;
        }

        if (!gestorArtist_existeArtista(Table_artistas, id)) {
            return 0;
        }

        // avança prox id
        current += 8;
        if (*current == '\'') {
            current++;
        }
    }

    return 1;
}

int validaAlbuns(const char* albuns, gestorAlbuns* Table_albuns) {
    const char* current = albuns;
    char id[9];

    while (*current) {
        // Verificar se há 8 caracteres
        if (strlen(current) < 8) return 0;

        // Copiar os 8 primeiros caracteres para 'id'
        strncpy(id, current, 8);
        id[8] = '\0';

        // Validar formato do ID: começa com "AL" seguido de 6 dígitos
        if (id[0] != 'A' || id[1] != 'L') return 0;
        for (int i = 2; i < 8; i++) {
            if (!isdigit(id[i])) return 0;
        }

        // Verificar se o ID existe no gestor de álbuns
        if (!gestorAlbum_existeAlbum(Table_albuns, id)) {
            return 0;
        }

        current += 8;
    }
    return 1;
}

void artists_id_process(char* artistas,gestorArtist* Table_artistas,int flag){
    int tamanho = strlen(artistas);

    char* current = artistas + 1;  // saltar '['
    char id[9];  // 8 chars + null

    while (*current && current < artistas + tamanho - 1) {  // parar antes de ']'
        // ignorar espaço e ,
        while (*current && (*current == ' ' || *current == ',')) {
            current++;
        }

        // ignorar ' se existir
        if (*current == '\'') {
            current++;
        }

        // extrair o id
        if (strlen(current) < 8) return;
        strncpy(id, current, 8);
        id[8] = '\0';

        switch(flag){
            case 0://contagem album
                Artist* artist = procuraArtist(Table_artistas,id);
                setAlbumCount(artist);
                break;
            case 1://calculo receita
                calculo_part(id, Table_artistas);
                break;
        }
        // avança prox id
        current += 8;
        if (*current == '\'') {
            current++;
        }
    }
    return;
}

/**
 * Calcula a receita da participação de cada artista.
 */
void calculo_part(const char* id, void* Table_artistas) {
    Artist* artist = procuraArtist(Table_artistas, id);
    if (artist == NULL) return;

    char* artist_type = getArtistType(artist);
    char* id_const = getArtistIdConstituent(artist);

    // Se o artista for um grupo, processar cada artista individual no id_constituent
    if (strcmp(artist_type, "group") == 0) {
        setRepCount(artist);//calcular receita do artista coletivo (grupo) da mesma forma que o individual

        //Criar cópia limpa de id_const (sem [ ], ')
        char* clean_id_const = strdup(id_const);
        for (char* p = clean_id_const; *p; p++) {
            if (*p == '[' || *p == ']' || *p == '\'') {
                *p = ' ';
            }
        }

        int capacity = 32;  // capacidade inicial
        int count_tokens = 0;
        char** tokens = malloc(capacity * sizeof(char*));

        char* token = strtok(clean_id_const, ", ");
        while (token != NULL) {
            // Se ficar cheio dobrar o tamanho do array
            if (count_tokens >= capacity) {
                capacity *= 2;
                tokens = realloc(tokens, capacity * sizeof(char*));
            }
            tokens[count_tokens++] = token;

            token = strtok(NULL, ", ");
        }

        // Percorrer tokens
        for (int i = 0; i < count_tokens; i++) {
            Artist* constituent_artist = procuraArtist(Table_artistas, tokens[i]);
            if (constituent_artist != NULL) { // ir a cada artista do constituent e adicionar receita participação
                setRepCountPart(constituent_artist, artist, count_tokens);
            }
        }

        free(tokens);
        free(clean_id_const);
    }
    else {
        setRepCount(artist);//se for individual o calculo é feito normalmente tal como o coletivo
    }

    free(artist_type);
    free(id_const);
}


/**
 * Contar o número de artistas no id_constituent.
 */
int countIds(const char* idString) {
    int count = 0;
    const char* current = idString;

    while (*current != '\0') {
        // Ignora espaços em branco e vírgulas
        while (*current == ' ' || *current == ',') {
            current++;
        }

        // Conta o ID se houver um
        if (*current != '\0') {
            count++;
            // Avança até o próximo delimitador
            while (*current != ' ' && *current != ',' && *current != '\0') {
                current++;
            }
        }
    }

    return count;
}