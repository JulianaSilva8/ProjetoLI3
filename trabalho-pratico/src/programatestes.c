#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    int query;
    int linhaAtual;
    char resultado[100];
} Discrepancia;

/**
 * Conta quantos testes existem para cada query
 */
int contaTestesPorQuery(const char *filename, int queryNum) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int nTestes = 0;
    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), file)) { // Lê cada linha do input.txt
        if (linha[0] - '0' == queryNum) {  // Verifica se a linha corresponde à query especificada
            nTestes++;
        }
    }

    fclose(file);
    return nTestes;
}

/**
 * Compara os resultados e os resultados esperados linha a linha
 */
Discrepancia *compararArquivos(const char *resultado, const char *esperado, int query, int *numDiscrepancias) {
    FILE *fileResultado = fopen(resultado, "r");
    FILE *fileEsperado = fopen(esperado, "r");

    if (!fileResultado || !fileEsperado) {
        printf("Erro ao abrir arquivos: %s ou %s\n", resultado, esperado);
        if (fileResultado) fclose(fileResultado);
        if (fileEsperado) fclose(fileEsperado);
        return NULL;
    }

    char linhaResultado[MAX_LINE_LENGTH];
    char linhaEsperado[MAX_LINE_LENGTH];
    int linhaAtual = 1;
    int discrepancias = 0;
    int tamanhoDiscrepancias = 10; //Inicialmente guarda 10 discrepancias
    Discrepancia *arrayDiscrepancias = malloc(tamanhoDiscrepancias * sizeof(Discrepancia));

    while (fgets(linhaResultado, sizeof(linhaResultado), fileResultado) && fgets(linhaEsperado, sizeof(linhaEsperado), fileEsperado)) {
        if (strcmp(linhaResultado, linhaEsperado) != 0) { // Se as linhas forem diferentes
            if (discrepancias >= tamanhoDiscrepancias) { // Se o array de discrepancias estiver cheio, realoca mais memoria
                tamanhoDiscrepancias *= 2;
                arrayDiscrepancias = realloc(arrayDiscrepancias, tamanhoDiscrepancias * sizeof(Discrepancia));
                if (arrayDiscrepancias == NULL) { // Verifica se a realocação foi bem sucedida
                    printf("Erro de realloc!\n");
                    exit(EXIT_FAILURE);
                }
            }
            arrayDiscrepancias[discrepancias].query = query; // Guarda a query onde a discrepancia foi encontrada
            arrayDiscrepancias[discrepancias].linhaAtual = linhaAtual; // Guarda a linha onde a discrepancia foi encontrada
            strncpy(arrayDiscrepancias[discrepancias].resultado, resultado, sizeof(arrayDiscrepancias[discrepancias].resultado) - 1); // Guarda o nome do arquivo onde a discrepancia foi encontrada
            arrayDiscrepancias[discrepancias].resultado[sizeof(arrayDiscrepancias[discrepancias].resultado) - 1] = '\0'; // Garante que a string é terminada com '\0'
            discrepancias++;
        }
        linhaAtual++;
    }

    fclose(fileResultado);
    fclose(fileEsperado);

    if (discrepancias == 0) { // Se não houver discrepancias encontradas, liberta a memória alocada e retorna NULL
        free(arrayDiscrepancias);
        return NULL;
    }

    *numDiscrepancias = discrepancias; // Numero de discrepancias encontradas
    return arrayDiscrepancias; // Retorna o array de discrepancias

}

/**
 * Compara os resultados com os resultados esperados e devolve as discrepancias
 */
int executarTestes(int numTestes, const char *prefixoResultado, const char *prefixoEsperado, int query) {
    int testesOk = 0; // Número de testes ok
    int numDiscrepancias = 0; // Número de discrepâncias
    int tamanhoDiscrepancias = 10; // Inicializa o array com espaço para 10 discrepâncias
    Discrepancia *discrepanciaResultado = malloc(tamanhoDiscrepancias * sizeof(Discrepancia)); // Aloca memória para discrepâncias

    if (!discrepanciaResultado) { // Verifica se a alocação foi bem sucedida
        printf("Erro de alocação de memória para discrepâncias!\n");
        exit(EXIT_FAILURE);
    }

    // Encontra o índice inicial e final dos testes da query atual
    int startIndex = 1;
    for (int q = 1; q < query; q++) {
        startIndex += contaTestesPorQuery("input.txt", q);
    }
    int endIndex = startIndex + numTestes - 1;

    for (int i = startIndex; i <= endIndex; i++) {
        char resultado[100], esperado[100]; // Buffers para armazenar os caminhos dos arquivos
        sprintf(resultado, "%s/command%d_output.txt", prefixoResultado, i);
        sprintf(esperado, "%s/command%d_output.txt", prefixoEsperado, i);
        int numDiscrepanciasLocal = 0; // Discrepâncias no teste específico
        Discrepancia *discrepancias = compararArquivos(resultado, esperado, query, &numDiscrepanciasLocal);

        if (numDiscrepanciasLocal == 0) { // Se não houver discrepâncias, incrementa o número de testes ok
            testesOk++;
        } else {
            if (numDiscrepancias + numDiscrepanciasLocal > tamanhoDiscrepancias) { // Se o array de discrepâncias estiver cheio, realoca mais memória
                tamanhoDiscrepancias = numDiscrepancias + numDiscrepanciasLocal; // Atualiza o tamanho do array
                discrepanciaResultado = realloc(discrepanciaResultado, tamanhoDiscrepancias * sizeof(Discrepancia)); // Realoca memória
                if (!discrepanciaResultado) { // Verifica se a realocação foi bem sucedida
                    printf("Erro de realloc para discrepâncias!\n");
                    exit(EXIT_FAILURE);
                }
            }
            for (int j = 0; j < numDiscrepanciasLocal; j++) { // Copia as discrepâncias especificas para o array de discrepâncias totais
                discrepanciaResultado[numDiscrepancias++] = discrepancias[j];
            }
            free(discrepancias);
        }
    }
    printf("Q%d: %d de %d testes ok!\n", query, testesOk, numTestes);

    for (int i = 0; i < numDiscrepancias; i++) { // Exibe as discrepâncias encontradas
        printf("Discrepância na query %d: linha %d de \"%s\"\n", query, discrepanciaResultado[i].linhaAtual, discrepanciaResultado[i].resultado);
    }

    free(discrepanciaResultado);
    discrepanciaResultado = NULL;
    return testesOk;
}

/**
 * Mede o tempo entre dois instantes.
 */
double medirTempo(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;
}

/**
 * Cria um arquivo temporário com os inputs correspondentes a cada query.
 */
void criarArquivoTemporario(const char *input, int query, const char *arquivoTemp) {
    FILE *file = fopen(input, "r");
    FILE *temp = fopen(arquivoTemp, "w");
    if (!file || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        exit(EXIT_FAILURE);
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), file)) {
        if (linha[0] - '0' == query) { // Verifica se a linha corresponde à query especificada
            fputs(linha, temp);
        }
    }

    fclose(file);
    fclose(temp);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Uso: %s <dataset> <input.txt> <resultados-esperados>\n", argv[0]);
        return 1;
    }

    const char *dataset = argv[1];
    const char *input = argv[2];
    const char *prefixoEsperado = argv[3];

    struct rusage r_usage;
    double tempoExecucao;
    double tempoTotal = 0.0;
    double arrayTempoQueries[6]={0}; // Array para armazenar os tempos de cada query
    char arquivoTemp[50];

    for (int query = 1; query <= 6; query++) {
    int numTestes = contaTestesPorQuery(input, query);
        if (numTestes > 0) {
            snprintf(arquivoTemp, sizeof(arquivoTemp), "input_query%d.txt", query);
            criarArquivoTemporario(input, query, arquivoTemp); // Cria o arquivo temporário para a query atual
            struct timespec start, end;
            char executaMain[256];
            char executaQuerys[256];

            snprintf(executaMain, sizeof(executaMain), "./programa-principal %s %s", dataset, input); // Executa o programa
            system(executaMain);

            // Executa o input de cada query para saber o tempo
            snprintf(executaQuerys, sizeof(executaQuerys), "./programa-principal %s %s", dataset, arquivoTemp);
            clock_gettime(CLOCK_REALTIME, &start);
            system(executaQuerys);
            clock_gettime(CLOCK_REALTIME, &end);

            executarTestes(numTestes, "resultados", prefixoEsperado, query);

            tempoExecucao = medirTempo(start, end);
            arrayTempoQueries[query - 1] = tempoExecucao;
            tempoTotal += tempoExecucao;

            remove(arquivoTemp); // Remove o arquivo temporário depois de o usar
        }
    }
    getrusage(RUSAGE_CHILDREN, &r_usage);
    double memoriaMB = r_usage.ru_maxrss / 1024.0;
    printf("Memória utilizada: %.2f MB\n", memoriaMB);

    printf("Tempos de execução:\n");
    for (int query = 1; query <= 6; query++) {
    printf(" Q%d: %.3f ms\n", query, arrayTempoQueries[query - 1]);
    }

    printf("Tempo total: %.3f s\n", tempoTotal / 1000.0);

    return 0;
}