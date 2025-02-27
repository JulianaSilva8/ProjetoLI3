#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../../include/gestor_user.h"
#include "../../include/tree.h"
#include "../../include/gestor_artist.h"
#include "../../include/gestor_music.h"
#include "../../include/user.h"

struct Generos {
    int Metal;
    int Pop;
    int Rock;
    int Blues;
    int Hip_Hop;
    int Classical;
    int Country;
    int Electronic;
    int Jazz;
    int Reggae;
};

struct Node {
    int value;
    long int generoscount[10];
};

long int getCount(Node* node, int i){
    return node->generoscount[i];
}

gint compare_ints(gconstpointer a, gconstpointer b) {
    return *(int*)a - *(int*)b;
}

void freeNode(Node* node){
    g_free(node);
}

Node* createNode(int value) {
    Node* newNode = g_malloc(sizeof(Node));
    newNode->value = value;

    // Inicializa os arrays generos e generoscount
    for (int i = 0; i < 10; i++) {
        newNode->generoscount[i] = 0;
    }

    return newNode;
}

/**
 * @brief Retorna o índice do género.
 *
 * @param genre Género.
 */
int getGenreIndex(const char* genre) {
    if (strcmp(genre, "Metal") == 0) return 0;
    if (strcmp(genre, "Pop") == 0) return 1;
    if (strcmp(genre, "Rock") == 0) return 2;
    if (strcmp(genre, "Blues") == 0) return 3;
    if (strcmp(genre, "Hip Hop") == 0) return 4;
    if (strcmp(genre, "Classical") == 0) return 5;
    if (strcmp(genre, "Country") == 0) return 6;
    if (strcmp(genre, "Electronic") == 0) return 7;
    if (strcmp(genre, "Jazz") == 0) return 8;
    if (strcmp(genre, "Reggae") == 0) return 9;
    return -1; // Gênero não encontrado
}

void insertMusic(Node* node, const char* genre) {
    int index = getGenreIndex(genre);

    node->generoscount[index]++;

}

void buildBalancedTree(GTree* tree, int arr[], int start, int end) {
    if (start > end) return;

    int mid = (start + end) / 2;
    Node* newNode = createNode(arr[mid]);

    int* key = g_malloc(sizeof(int));
    *key = newNode->value;

    g_tree_insert(tree, key, newNode);

    buildBalancedTree(tree, arr, start, mid - 1);
    buildBalancedTree(tree, arr, mid + 1, end);
}

GTree* binarytree(gestorUser* gestorUser,gestorMusic* musicTable) {

  
    GTree* tree = g_tree_new_full(compare_ints, NULL, g_free, (GDestroyNotify)freeNode);

    int arr[101];

    for (int i = 0; i <= 100; i++) {
        arr[i] = i;
    }

    buildBalancedTree(tree, arr, 0, 100);

    UserIterator userIterator;
    initUserIterator(&userIterator, gestorUser);
    
    User* user;

    while ((user = getNextUser(&userIterator)) != NULL) {
        Music* music = criaMusic();
        char* listagostos = getListaMusicas(user);
        char* datanascimento = getDataNascimento(user);

        int val = idade(datanascimento);
        // encontra o node correspondente ao valor
        Node* node = g_tree_lookup(tree, &val);
        if (!node) {
            node = createNode(val);
            int* key = g_malloc(sizeof(int));
            *key = node->value;

            g_tree_insert(tree, key, node);
        }

        // processa os likes musicais
        char music_id[8];

        for (size_t i = 0; i < strlen(listagostos) ; i++) {
            if (listagostos[i] == '\'') {
                i++;
                int k = 0;

                while (listagostos[i] != '\'' && k < 8) {
                    music_id[k++] = listagostos[i++];
                }
                music_id[k] = '\0';


                Music* music = gestorMusic_lookup(musicTable,music_id);

                char* genre = getGenre(music);

                insertMusic(node, genre);

                free(genre);
            }

        }

        free(listagostos);
        free(datanascimento);
        freeMusic(music);
    }

    return tree;
}

void freeTree(GTree* tree) {
    g_tree_destroy(tree);
}