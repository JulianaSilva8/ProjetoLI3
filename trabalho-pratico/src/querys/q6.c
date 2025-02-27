
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <glib.h>
#include "../../include/gestor_music.h"
#include "../../include/gestor_user.h"
#include "../../include/parser_inputs.h"
#include "../../include/q6.h"
#include "../../include/user.h"
#include "../../include/output.h"
#include "../../include/utils.h"

#define SIZE_STRUCT 80 // Define SIZE_STRUCT with an appropriate value
#define MAX_PLAYBACKS 30


struct AlbumCount {
    char album[128];
    int total_time;  
};

typedef struct {
    char artist_id[9];
    int total_time;         
    char musicas[100][9];  // ids das musicas distintas
    int musicas_count;      
} ArtistStats;

struct User_q6{
    int listening_total;
    int unica_count;
    char* artista_t;
};

struct generoCount {
    char genero[20];   
    int total_time;
};

struct ArtistCount {
    char id[9];
    int total_time; 
};

struct diaCount {
    char dia[11]; // YYYY/MM/DD+'\0' =10+1
    int count;
}; 

struct artistas_user {
    char artistas[SIZE_STRUCT][5][9]; 
    int num_artistas[SIZE_STRUCT]; // saber quantos artistas tenho em cada
    char topArtists[SIZE_STRUCT][30]; 
    int topArtistsCount; 
    struct artistas_user* prox;
};


int compareArtist(const void* a, const void* b) {
    const ArtistStats* A = (const ArtistStats*)a;
    const ArtistStats* B = (const ArtistStats*)b;

    if (A->total_time < B->total_time)
        return 1; 
    if (A->total_time > B->total_time)
        return -1; 
    return strcmp(A->artist_id, B->artist_id); 
}


struct artistas_user* setArtists(User* user, gestorMusic* gestormusic) {
    struct artistas_user* artistasUser = malloc(sizeof(struct artistas_user));
    if (!artistasUser) return NULL;

    struct artistas_user* head = artistasUser;

    int h_size = getHistoricoSize(user);

    for (int i = 0; i < h_size; i++) {
        if (i >= SIZE_STRUCT) {
            artistasUser->prox = malloc(sizeof(struct artistas_user));
            artistasUser = artistasUser->prox;
        }
        char* music_id = getMusicId_Historico(user, i); 
        Music* musica = procuraMusic(gestormusic, music_id);
        char* artistas_id = getMusicArtistId(musica);

        char* current = artistas_id + 1; // ignorar [
        size_t len = strlen(artistas_id);
        char* end = artistas_id + len - 1; // ignorar o ultimo char ]

        // contador artistas nesta reprpoduçao
        int artist_count = 0;

        while (current < end && artist_count < 5) { 
            // ignorar espaços e ' ,
            while (current < end && (isspace((unsigned char)*current) || *current == ',' || *current == '\'')) {
                current++;
            }   
            
            if (current >= end) break;

            // extrair id do artista
            char id[9];
            strncpy(id, current, 8);
            id[8] = '\0';

            // guardar o artista na entrada atual
            strcpy(artistasUser->artistas[i % SIZE_STRUCT][artist_count], id);
            artist_count++;

            // avaçar para o proximo artista
            current += 8;

            if (*current == '\'') {
                current++;
            }
        }

        artistasUser->num_artistas[i % SIZE_STRUCT] = artist_count;

        free(artistas_id);
        free(music_id);
    }

    artistasUser->prox = NULL;
    return head;
}

void freeArtists(struct artistas_user* head) {
    struct artistas_user* tmp;

    while (head != NULL) {
        tmp = head;
        head = head->prox;
        free(tmp);
    }
}

void TopNArtists(char* musicid,char* timestamp, artistas_user* artistas_user,  ArtistStats* artists, int *nArtistas,char playbacks_unicos[][30],int *unique_count, char* duration , int i) {
    char key[30];
    snprintf(key, sizeof(key), "%s|%s", musicid, timestamp);

    // verificar se o playback ja foi processado
    bool already_processed = false;
    for (int j = 0; j < *unique_count; j++) {
        if (strcmp(playbacks_unicos[j], key) == 0) {
            already_processed = true;
            break;
        }
    }

    if (!already_processed && *unique_count < MAX_PLAYBACKS) {
        strcpy(playbacks_unicos[*unique_count], key);
        (*unique_count)++;

        // percorrer todos os artistas desta entrada
        for (int a = 0; a < artistas_user->num_artistas[i]; a++) {
            const char* artist_id = artistas_user->artistas[i][a];
            int seg = duracao_to_seconds(duration);

            // verificar se o artista ja existe
            bool foundArtist = false;
            int idxArtist = -1;
            for (int aIdx = 0; aIdx < *nArtistas; aIdx++) {
                if (strcmp(artists[aIdx].artist_id, artist_id) == 0) {
                    foundArtist = true;
                    idxArtist = aIdx;
                    break;
                }
            }

            // se n existir, adicionar
            if (!foundArtist && *nArtistas < 1000) {
                strcpy(artists[*nArtistas].artist_id, artist_id);
                artists[*nArtistas].total_time = seg;
                artists[*nArtistas].musicas_count = 1;
                strcpy(artists[*nArtistas].musicas[0], musicid);
              
                (*nArtistas)++;
            }
            
            // se existir, acumular o tempo e contar musicas distintas
            if (foundArtist) {
                artists[idxArtist].total_time += seg;
               
                // verificar se a musica ja foi contada para o artista atual
                bool foundMusic = false;
                const char* musicID = musicid;
                for (int m = 0; m < artists[idxArtist].musicas_count; m++) {
                    if (strcmp(artists[idxArtist].musicas[m], musicID) == 0) {
                        foundMusic = true;
                        break;
                    }
                }
                
                if (!foundMusic && artists[idxArtist].musicas_count < 100) {
                    strcpy(artists[idxArtist].musicas[artists[idxArtist].musicas_count], musicID);
                    artists[idxArtist].musicas_count++;
                }
            }
        }
    }
}

void SortNArtists(int *nArtistas, ArtistStats* artists, int N, bool existe_s, char** output, int *topArtistsCount){
    if (*nArtistas == 0) {
        // nenhum artista ouvido neste ano
        *topArtistsCount = 0;
           
        return;
    }

    // ordenar os artistas por tempo decrescente e id ascendente
    qsort(artists, *nArtistas, sizeof(ArtistStats), compareArtist);

    // limpar o array topArtists antes de adicionar novos
    *topArtistsCount = 0;

    // determinar o numero de artistas a serem adicionados 
    int limit = (N > 0 && N < *nArtistas) ? N : *nArtistas;

    for (int i = 0; i < limit; i++) {
        // criar a string: artist_id;#musics;HH:MM:SS
        int total = artists[i].total_time;
        if(total == 0) return;
        int h = total / 3600;
        int m = (total % 3600) / 60;
        int s = (total % 60);
        char time_str[10];
        sprintf(time_str, "%02d:%02d:%02d", h, m, s);

        int musicas_distintas = artists[i].musicas_count;

        char sym = existe_s ? '=' : ';';

        // guardar resultado
        char linha[64];
        snprintf(linha, sizeof(linha), "\n%s%c%d%c%s", artists[i].artist_id, sym, musicas_distintas, sym, time_str);

       

        output[i] = malloc(strlen(linha) + 1 ); 
        strcpy(output[i], linha);
        (*topArtistsCount)++;
    }

    artists = NULL;
}

void FavHora(char* timestamp, char* duration, int* h_total_time){
    char h_str[3]; // "HH"+'\0'
    h_str[0] = timestamp[11];
    h_str[1] = timestamp[12];
    h_str[2] = '\0';

    int h = atoi(h_str); 
    if (h >= 0 && h < 24) {
        // converte a duraçao para segundos e acumula
        int seg = duracao_to_seconds(duration);
        h_total_time[h] += seg;
    }
}

void sortFavHora(int* h_total_time, char** outputarray){
    int max_index = 0;
    for (int h = 1; h < 24; h++) {
        if (h_total_time[h] > h_total_time[max_index]) {
            max_index = h;
        }
    }
    // converte a hora para o formato HH
    char fav_hour[3];
    sprintf(fav_hour, "%02d", max_index);

    strcpy(outputarray[6], fav_hour);
}

void FavAlbum(char* music_id, gestorMusic* gestor, char* duration, int *nAlbuns, struct AlbumCount* albumCount){
     // concerter duraçao para segundos
    int seg = duracao_to_seconds(duration);

    // obter struct music
    Music* m = procuraMusic(gestor, music_id);
    // se n existir musica, ignora
    if (!m) return;
                
    // sacar id do album
    char* album = getMusicAlbumId(m);
    // se n existir album, ignora
    if (!album) return;
                

    // procurar se album ja esta no array
    bool found = false;
    for (int a = 0; a < *nAlbuns; a++) {
        if (strcmp(albumCount[a].album, album) == 0) {
            albumCount[a].total_time += seg;
            found = true;
            break;
        }
    }
    // se n encontrei, adiciono novo registo
    if (!found && *nAlbuns < 1000) {
        strncpy(albumCount[*nAlbuns].album, album, 127);
        albumCount[*nAlbuns].album[127] = '\0'; // safety
        albumCount[*nAlbuns].total_time = seg;
        (*nAlbuns)++;
    }
    free(album);
}

void sortAlbuns(int *nAlbuns, struct AlbumCount* albumCount, char** outputarray) {
    int max_idx = 0;
    for (int i = 1; i < *nAlbuns; i++) {
        // maior tempo total
        if (albumCount[i].total_time > albumCount[max_idx].total_time) {
            max_idx = i;
        }
        // em caso de empate escolhe album com id menor
        else if (albumCount[i].total_time == albumCount[max_idx].total_time) {
            if (strcmp(albumCount[i].album, albumCount[max_idx].album) < 0) {
                max_idx = i;
            }
        }
    }
    strcpy(outputarray[5], albumCount[max_idx].album);
}

void FreqGenre(struct generoCount* generos, gestorMusic* gestor, char* musicId, char* duration, int* nGeneros) {
    int seg = duracao_to_seconds(duration); 
                
    // obter struct music e depois o genero
    Music* m = procuraMusic(gestor, musicId);
    if (!m) return; // se n existir musica, ignora
    
    char* genero = getGenre(m); 

    // verifico se o genero ja esta no array
    int found = 0;
    for (int g = 0; g < *nGeneros; g++) {
        if (strcmp(generos[g].genero, genero) == 0) {
            generos[g].total_time += seg;
            found = 1;
            break;
        }
    }
    // se n encontrar, adiciono
    if (!found && *nGeneros < 10) {
        strcpy(generos[*nGeneros].genero, genero);
        generos[*nGeneros].total_time = seg;
        (*nGeneros)++;
    }

    free(genero);
}

void sortGenre(char** outputarray, int nGeneros, struct generoCount* generos){

    if (nGeneros == 0) {
        return;
    }
    // encontrar genero com maior tempo total
    int max_idx = 0;
    for (int i = 1; i < nGeneros; i++) {
        if (generos[i].total_time > generos[max_idx].total_time) {
            max_idx = i;
        }
        else if (generos[i].total_time == generos[max_idx].total_time) {
            // desempate por ordem alfabetica
            if (strcmp(generos[i].genero, generos[max_idx].genero) < 0) {
                max_idx = i;
            }
        }
    }
    strcpy(outputarray[4], generos[max_idx].genero);

}

void updateDiasArray(diaCount* dias, int* ndias, const char* timestamp) {
    // extrai apenas a parte YYYY/MM/DD 
    // formato original: YYYY/MM/DD HH:MM:SS
    char dia_str[11];
    strncpy(dia_str, timestamp, 10);
    dia_str[10] = '\0'; // terminar a string

    // verifica se o dia ja existe no array
    bool found = false;
    for (int j = 0; j < *ndias; j++) {
        if (strcmp(dias[j].dia, dia_str) == 0) {
            dias[j].count++;
            found = true;
            break;
        }
    }
    // se n existe, adicionamos com count = 1
    if (!found && *ndias < 1000) {
        strcpy(dias[*ndias].dia, dia_str);
        dias[*ndias].count = 1;
        (*ndias)++;
    }
}

void findTopDia(char** outputarray, diaCount* dias, int ndias) {
    // se n há nenhum dia neste ano, limpa a variavel e sai
    if (ndias == 0) {
        strcpy(outputarray[3], "\0"); 
        return;
    }
    // procurar o dia com mais reproduções
    // desempate dia mais recente 
    int max_idx = 0;
    for (int i = 1; i < ndias; i++) {
        // se encontrar count maior, atualiza
        if (dias[i].count > dias[max_idx].count) {
            max_idx = i;
        }
        else if (dias[i].count == dias[max_idx].count) {
            if (strcmp(dias[i].dia, dias[max_idx].dia) > 0) {
                max_idx = i;
            }
        }
    }
    // guardar o resultado para user->data_mais_ouvida
 
    strcpy(outputarray[3], dias[max_idx].dia);
}

void sortFreqArtist(int* artistas_unicos, struct ArtistCount* artistas,char** output_querry){

    if (artistas_unicos == 0) return;

    // encontrar o indice do artista com maior tempo total
    // em caso de empate devolve o id menor 
    int max_index = 0;
    for (int i = 1; i < *artistas_unicos; i++) {
        if (artistas[i].total_time > artistas[max_index].total_time ||
           (artistas[i].total_time == artistas[max_index].total_time &&
            strcmp(artistas[i].id, artistas[max_index].id) < 0)) {
            max_index = i;
        }
    }

    //copiar o id do artista mais ouvido para o user
    strcpy(output_querry[2], artistas[max_index].id);


}

void arrayFreqArtist(User_q6* user_q6, const char* ano, artistas_user* artista_User, int i, int* artistas_unicos, const char* duration, struct ArtistCount* artistas) {

    int seg = duracao_to_seconds(duration);
   
    // percorrer todos os artistas desta entrada
    for (int a = 0; a < artista_User->num_artistas[i]; a++) {
        const char* artist_id = artista_User->artistas[i][a];
        
        bool found = false;

        // verificar se o artista ja esta no array
        for (int j = 0; j < *artistas_unicos; j++) {
             
            if (strcmp(artistas[j].id, artist_id) == 0) {
                // se encontrado, soma a duraçao
                artistas[j].total_time += seg;
                found = true;
               
                break;
            }
        }

        // c.c adiciona novo registo
        if (!found && *artistas_unicos < 1000) {
        strcpy(artistas[*artistas_unicos].id, artist_id);
        artistas[*artistas_unicos].total_time = seg;
        (*artistas_unicos)++;
        }
    }
            

}

void check_musicavista(char musicas_vistas[100][9], char* music_id, artistas_user* artistasUser, int artist_index, User_q6* user_q6 ) {
    bool found = false;
    // Cve se a musica já existe nas  musicas_vistas
    for (int i = 0; i < user_q6->unica_count; i++) {
        if (strcmp(musicas_vistas[i], music_id) == 0) {
            found = true;
            break;
        }
    }
    // senão encontrar adiciona
    if (!found && user_q6->unica_count < 100) {
        strcpy(musicas_vistas[user_q6->unica_count], music_id);
        user_q6->unica_count++;
    }
}

void tratarinput(User_q6* user_q6, char** outputarray) {
    char resultado[12];
    int horas = user_q6->listening_total / 3600;  
    int minutos = (user_q6->listening_total % 3600) / 60;
    int segundos = user_q6->listening_total % 60;
    snprintf(resultado, sizeof(resultado), "%02d:%02d:%02d", horas, minutos, segundos);
    strcpy(outputarray[0], resultado);
}

int fazquery(char** outputarray, char** outputTop10,artistas_user* artistasUser, User* user, const char* ano, User_q6* user_q6, gestorMusic* gestorMusic, bool existe_s, char** lista_inputs) {
    int h_size = getHistoricoSize(user);
    char musicas_vistas[100][9] = {0};
    struct ArtistCount artistas[500] = {0}; 
    struct generoCount generos[10] = {0};
    struct AlbumCount albums[100] = {0};
    struct AlbumCount albumCount[100] = {0};
    int h_total_time[24] = {0};
    int nAlbums = 0;
    int nGeneros = 0;
    int artistas_unicos = 0;
    user_q6->listening_total = 0;
    diaCount dias[366] = {0};
    int ndias = 0;
    ArtistStats* artists = NULL;
    
    if(lista_inputs[2]!=NULL) {
        artists = malloc(1000 * sizeof(ArtistStats));
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 9; j++) {
                artists[i].artist_id[j] = NULL;
            }
            artists[i].total_time = 0;
        }
    }

    char playbacks_unicos[MAX_PLAYBACKS][30] = {0};
    int unique_count = 0;

    for (int i = 0; i < h_size; i++) {
        
        char* music_id = getMusicId_Historico(user, i); 
        char* timestamp = getTimestamp_Historico(user, i);
        char* duration = getDuration_Historico(user, i);
        
        if (strncmp(timestamp, ano, 4) == 0) {
            
            user_q6->listening_total += duracao_to_seconds(duration); // acumular duraçao
            
            check_musicavista(musicas_vistas, music_id, artistasUser, i, user_q6);
            
            arrayFreqArtist(user_q6, ano, artistasUser, i, &artistas_unicos, duration, artistas);
            
            updateDiasArray(dias, &ndias, timestamp);

            FreqGenre(generos, gestorMusic, music_id, duration, &nGeneros);

            FavAlbum(music_id, gestorMusic, duration, &nAlbums, albums);

            FavHora(timestamp, duration, h_total_time);

            if(lista_inputs[2]!=NULL) TopNArtists(music_id, timestamp, artistasUser, artists, &unique_count, playbacks_unicos, &unique_count, duration, i);
        }
        free(duration);
        free(timestamp);
        free(music_id);
    }

    tratarinput(user_q6,outputarray);
    snprintf(outputarray[1], 12, "%d", user_q6->unica_count);
    sortFreqArtist(&artistas_unicos, artistas, outputarray);
    findTopDia(outputarray, dias, artistas_unicos);
    sortGenre(outputarray, nGeneros, generos);
    sortAlbuns(&nAlbums, albums, outputarray);
    sortFavHora(h_total_time, outputarray);

    int topArtistsCount = 0;
    if (lista_inputs[2] != NULL) {
        int N = atoi(lista_inputs[2]);
       
        SortNArtists(&unique_count, artists, N, existe_s, outputTop10, &topArtistsCount);
        // Free the main array
        free(artists);
    }
    if (artists!=NULL) {
    

    }
    
    return topArtistsCount;
}

void q6_outputs(char** output_array, int atualine, bool existe_s,char** outputTop10, int n) {
    if (strcmp(output_array[0], "00:00:00") != 0) {
        
        for (int i = 0; i < 7; i++) {
            output(output_array[i], atualine, existe_s, 0);
            
        } 
        
        for(int i = 0 ; i < n; i++){
            output(outputTop10[i], atualine, existe_s, 0);
        }
        output("\n", atualine, existe_s, 0);
    }
    else{
        output("", atualine, existe_s, 1);
    }
}




int query6 (char *input, int atualine, gestorUser* gestor,gestorMusic* gestor_m){
    bool existe_S = false ;
    char **lista_inputs = NULL;

    //lista_inputs[0] = ID input lista_inputs[1] = ano input lista_inputs[2] = top N
    existe_S = gestor_parser(input, existe_S, &lista_inputs);
    User* foundUser = procuraUser(gestor, lista_inputs[0]);
    
    if(foundUser == NULL) {
        output("User not found", atualine, existe_S, 1); 
    }
    else{
        const char* ano = lista_inputs[1];

        artistas_user* artistasUser = setArtists(foundUser, gestor_m);

        char** output =(char**)malloc(7 * sizeof(char*));
        for (int i = 0; i < 7; i++) {
            output[i] = (char*)malloc(120 * sizeof(char));
        }

        User_q6* userq6 = malloc(sizeof(User_q6));
        userq6->listening_total = 0;
        userq6->unica_count = 0;
        userq6->artista_t=0;

        char** outputTop10;
        if(lista_inputs[2])outputTop10 = malloc(atoi(lista_inputs[2]) * sizeof(char*));

        int n = fazquery(output, outputTop10,artistasUser, foundUser,  ano,  userq6, gestor_m, existe_S, lista_inputs);
    
        q6_outputs(output, atualine, existe_S, outputTop10, n);

        for (int k = 0; k < n ; k++) {
            free(outputTop10[k]);
        }

    
        for(int i  = 0 ; i < 7; i++){
            if(output[i]!=NULL)free(output[i]);
        }
        if(output!=NULL)free(output);
        if(lista_inputs[2]) free(outputTop10);

        freeArtists(artistasUser);

        free(userq6);
    }
    
    if (lista_inputs) {
        for (int i = 0; lista_inputs[i] != NULL; i++) {
            free(lista_inputs[i]);
        }
        free(lista_inputs);
    }

    return 0;
}