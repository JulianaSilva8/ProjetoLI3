#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "../../include/gestor_user.h"
#include "../../include/gestor_artist.h"
#include "../../include/gestor_music.h"
#include "../../include/validacoes_musicas.h"
#include "../../include/gestor_albuns.h"
#include "../../include/albuns.h"
#include "../../include/gestor_history.h"
#include "../../include/tree_data_history.h"
#include "../../include/artist.h"
#include "../../include/utils.h"

gestorUser* load_users(FILE* fp, gestorMusic* gestorMusic){
    gestorUser* gestor = criaGestorUser();

    char str[1000];
    char header[1000];
    int erro_flag = 0;

    // Lê a primeira linha (campos username, nome, país etc) para a ignorar
    if (fgets(header, sizeof(header), fp) != NULL) header[strcspn(header, "\n")] = 0;

    while (fgets(str, sizeof(str), fp) != NULL) {
        // Remover \n
        str[strcspn(str, "\n")] = 0;

        User* user = criaUser();
        char* token = strtok(str, ";");
        int index = 0;
        while (token != NULL) {
            userField(user, index, token);
            token = strtok(NULL, ";");
            index++;
        }
        //libertar sempre a memoria ao usar getters
        char* email = getEmail(user);
        char* subscriçao = getSubscriçao(user);
        char* data_nascimento = getDataNascimento(user);
        char* lista_musicas = getListaMusicas(user);

        if (emailValida(email) && subValida(subscriçao) && dataValida(data_nascimento) && listaValida(lista_musicas,gestorMusic)) {
            insereUser(gestor, user);
        }
        else
        {
            erro(user,erro_flag,header);
            freeUser(user);
            erro_flag = 1;//para saber se o que estou a passar é o header
        }
        //libertar memoria getters
        free(lista_musicas);
        free(email);
        free(subscriçao);
        free(data_nascimento);
    }
    fclose(fp);
    return gestor;
}

gestorMusic* load_musics(FILE* fp,gestorArtist* gestorArtistas, gestorAlbuns* gestorAlbuns) {
    gestorMusic* gestor = criaGestorMusic();

    char str[10000];
    char header[1000];
    int erro_flag = 0;
    char* token2[10] = {0};

    // Lê a primeira linha (campos username, nome, país, etc.) para ignorá-la
    if (fgets(header, sizeof(header), fp) != NULL) header[strcspn(header, "\n")] = 0;

    while (fgets(str, sizeof(str), fp) != NULL) {
        // Remove \n
        str[strcspn(str, "\n")] = 0;

        Music* musics = criaMusic();
        char* token = strtok(str, ";");
        int index = 0;


        while (token != NULL) {
            if (index!=1 && index!=6 && index!=7)musicField(musics, index, token);
            else token2[index] = strdup(token);
            token = strtok(NULL, ";");
            index++;
        }
        char* tempo = getMusicDuration(musics);
        char* artistid = getMusicArtistId(musics);
        char* albumid = getMusicAlbumId(musics);
        if(validatempo(tempo)== 1 && validaartistas(artistid,gestorArtistas) && validaAlbuns(albumid, gestorAlbuns) == 1){
        insereMusic(gestor, musics);
        }
        else{
            printerro(musics,erro_flag,header,token2);
            freeMusic(musics);
            erro_flag = 1;
        }
        free(tempo);
        free(artistid);
        free(albumid);
        for (int i = 0; i < 10; i++) {
            if (token2[i] != NULL) {
                free(token2[i]);
                token2[i] = NULL;
            }
        }
    }
    fclose(fp);
    return gestor;
}

gestorArtist* load_artists(FILE* fp) {
    gestorArtist* gestor = criaGestorArtist();

    char str[10000];
    char header[1000];
    int erro_flag = 0;
    char* token2;

    // Ignora a primeira linha (cabeçalho)
    if (fgets(header, sizeof(header), fp) != NULL) header[strcspn(header, "\n")] = 0;

    while (fgets(str, sizeof(str), fp) != NULL) { //lê linha a linha do dataset
        str[strcspn(str, "\n")] = 0; // Remove o \n

        Artist* artist = criaArtist(); // Cria um novo artista
        char* token = strtok(str, ";");
        int index = 0;

        while (token != NULL) {
            if (index!=2) artistField(artist, index, token); // Preenche os campos do artista
            else token2 = strdup(token);
            token = strtok(NULL, ";");
            index++;
        }
        char* artistId = getArtistId(artist);
        char* artistType = getArtistType(artist);
        char* artistIdConstituent = getArtistIdConstituent(artist);
        // Validações
        if (validaElementos(artistType, artistIdConstituent)==true) {
            insereArtist(gestor, artist);
        } else {
            erroArtist(artist,erro_flag,header, token2);
            freeArtist(artist);
            erro_flag = 1;
        }
        free(artistType);
        free(artistIdConstituent);
        free(artistId);
        free(token2);
    }
    fclose(fp);
    return gestor;
}

gestorAlbuns* load_albuns(FILE* fp,gestorArtist* gestorArtistas) {
    gestorAlbuns* gestor = criaGestorAlbuns();

    char str[10000];
    char header[1000];

    // Lê a primeira linha (campos username, nome, país, etc.) para ignorá-la
    if (fgets(header, sizeof(header), fp) != NULL) header[strcspn(header, "\n")] = 0;

    while (fgets(str, sizeof(str), fp) != NULL) {
        // Remove \n
        str[strcspn(str, "\n")] = 0;

        Album* album = criaAlbum();
        char* token = strtok(str, ";");
        int index = 0;

        while (token != NULL) {
            albumField(album, index, token);
            token = strtok(NULL, ";");
            index++;
        }
            char* artistAlbumID = getAlbumArtistId(album);
            insereAlbum(gestor, album);
            artists_id_process(artistAlbumID,gestorArtistas,0);//contagem album
            free(artistAlbumID);

    }
    fclose(fp);
    return gestor;
}

GTree* load_historical(FILE* fp, gestorUser* gestor, gestorMusic* gestor_m, gestorArtist* gestor_a) {
    char str[10000];
    char header[1000];
    int erro_flag = 0;

    GTree *tree = init_history_tree();

    // Lê a primeira linha (campos username, nome, país, etc.) para ignorá-la
    if (fgets(header, sizeof(header), fp) != NULL) header[strcspn(header, "\n")] = 0;

    while (fgets(str, sizeof(str), fp) != NULL) {
        // Remove \n
        str[strcspn(str, "\n")] = 0;

        History* history = criaHistory();
        char* token = strtok(str, ";");
        int index = 0;

        while (token != NULL) {
            historyField(history, index, token);
            token = strtok(NULL, ";");
            index++;
        }

        char* timestamp = getTimestamp_History(history);
        char* duration = getDuration_History(history);
        char* plataforma = getPlatform_History(history);
        char* music_id = getMusicId_History(history);

        if(validatempo(duration) && (strcasecmp(plataforma, "mobile") == 0 || strcasecmp(plataforma, "desktop") == 0)){
            char* username = getUserid_History(history);
            User* user = procuraUser(gestor, username);
            setHistory(user, history);

            Music* musica = procuraMusic(gestor_m,music_id);
            char* artist_id = getMusicArtistId(musica);
            artists_id_process(artist_id,gestor_a,1);//fazer calculo receita

            build_history_tree(tree,timestamp,artist_id,duration);

            free(username);
            free(artist_id);
          }
        else{
            erro_history(history, erro_flag, header);
            erro_flag = 1;
        }
        free(timestamp);
        free(duration);
        free(plataforma);
        free(music_id);

        freeHistory(history);
    }
    fclose(fp);
    return tree;
}