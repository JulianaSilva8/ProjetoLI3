#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "../include/gestor_user.h"
#include "../include/gestor_music.h"
#include "../include/gestor_artist.h"
#include "../include/gestor_history.h"
#include "../include/tree.h"
#include "../include/q1.h"
#include "../include/q2.h"
#include "../include/q4.h"
#include "../include/q5.h"
#include "../include/load_db.h"
#include "../include/gestor_query.h"
#include "../include/utils.h"
#include "../include/main_interativo.h"
#include <sys/resource.h>

int get_argv_length(char** argv) {
    int count = 0;
    while (argv[count] != NULL) {
        count++;
    }
    return count;
}


int process_input(const char* caminho, const char* input_file) {
    char dataset[100], datasetmusics[100], datasetartists[100];
    char datasetalbuns[100], datasethistorical[100];

    snprintf(dataset, sizeof(dataset), "%s/users.csv", caminho);
    snprintf(datasetmusics, sizeof(datasetmusics), "%s/musics.csv", caminho);
    snprintf(datasetartists, sizeof(datasetartists), "%s/artists.csv", caminho);
    snprintf(datasetalbuns, sizeof(datasetalbuns), "%s/albums.csv", caminho);
    snprintf(datasethistorical, sizeof(datasethistorical), "%s/history.csv", caminho);

    FILE* data_set = fopen(dataset, "r");
    FILE* users = fopen(input_file, "r");
    FILE* data_set_musics = fopen(datasetmusics, "r");
    FILE* data_set_artists = fopen(datasetartists, "r");
    FILE* data_set_albuns = fopen(datasetalbuns, "r");
    FILE* data_set_historical = fopen(datasethistorical, "r");

    gestorArtist* hashTableartists = load_artists(data_set_artists);
    gestorAlbuns* hashtablealbuns = load_albuns(data_set_albuns, hashTableartists);
    gestorMusic* hashTablemusics = load_musics(data_set_musics, hashTableartists, hashtablealbuns);
    gestorUser* hashTableusers = load_users(data_set, hashTablemusics);
    GTree* tree_data = load_historical(data_set_historical, hashTableusers, hashTablemusics, hashTableartists);
    
    GTree* arvore = binarytree(hashTableusers, hashTablemusics);
    void** matrix_data = fazmatrix_q5(hashTablemusics, hashTableusers);

    char buffer[256];
    char input[256];
    int line1 = 0;

    while (fgets(buffer, sizeof(buffer), users) != NULL) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        snprintf(input, sizeof(input), "%s", buffer);
        line1++;
        gestor_query(input, line1, hashTableusers, hashTablemusics, hashTableartists, arvore, tree_data, matrix_data);
    }

    freeMatrixData(matrix_data, hashTableusers);
    free(matrix_data);
    fclose(users);
    freeTree(arvore);
    freeTree(tree_data);
    freeGestorUser(hashTableusers);
    freeGestorMusic(hashTablemusics);
    freeGestorArtist(hashTableartists);
    freeGestorAlbuns(hashtablealbuns);

    return 0;
}

int main(int argc, char** argv) {
    int len = get_argv_length(argv);
    if (len==1) {
        return main_interativo();
    }
    return process_input(argv[1], argv[2]);
}