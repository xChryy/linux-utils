#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Struttura per i flag
struct {
    int number;
    int number_nonblank;
    // altri flag...
} flags = {0, 0}; // Inizializza tutti i flag a 0

// Dichiarazioni delle funzioni
void basicMode(FILE* file);
void readFile(char* filename);
void printLineWithNumber(char* line, int* line_counter, int* nonblank_counter);
void printHelp();


/*** Lettura base del file ***/
void basicMode(FILE* file) {
    char line[100];
    int line_counter = 1;
    int nonblank_counter = 1;

    while (fgets(line, 100, file)) {
        printLineWithNumber(line, &line_counter, &nonblank_counter);
    }

    fclose(file);
}

/*** Funzione di supporto che stampa la numerazione  ***/
void printLineWithNumber(char* line, int* line_counter, int* nonblank_counter) {
    int is_blank_line = (line[0] == '\n');

    if (flags.number_nonblank == 1) {
        if (!is_blank_line) {
            printf("%d\t%s", (*nonblank_counter)++, line);
        } else {
            printf("%s", line);
        }
    } else if (flags.number == 1) {
        printf("%d\t%s", *line_counter, line);
    } else {
        printf("%s", line);
    }

    (*line_counter)++;
}

/*** Funzione per leggere un file ***/
void readFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    basicMode(file);
    // fclose viene chiamata dentro basicMode
}

/*** Lettura delle opzioni disponibili ***/
void printHelp(){
        printf("cat è un binario che ti permette di aprire qualsiasi file mostrandone il suo contenuto. \n\n"
                "Il formato richiesto è il seguente:\n"
                "./cat [options] [filename]\n\n"

                "Le opzioni disponibili sono le seguenti:\n\n"
                "-n     Mostra l'indice della riga\n"
                "-b     Mostra l'indice della riga escludendo quelle vuote\n"
                "-h     Mostra la lista delle opzioni disponibili\n"
                "-v     Mostra la versione disponibile\n");
        exit(1);
}

/*** Lettura della versione attuale ***/
void printVersion(){
        printf("cat v. 0.0.1\tMade with <3 by 0xChryy\n");
        exit(1);
}

int main(int argc, char* argv[]) {
    int opt;

    // Parsing degli argomenti
    while ((opt = getopt(argc, argv, "nbhv")) != -1) {
        switch (opt) {
            case 'n':
                flags.number = 1;
                break;
            case 'b':
                flags.number_nonblank = 1;
                break;
            case 'h':
                printHelp();
                break;
            case 'v':
                printVersion();
                break;
            default:
                fprintf(stderr, "Uso: %s [-n] [-b] [-h] [-v] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Se non ci sono file specificati, leggi da stdin
    if (optind >= argc) {
        basicMode(stdin);
    } else {
        // Processa tutti i file specificati
        for (int i = optind; i < argc; i++) {
            readFile(argv[i]);
        }
    }

    return 0;
}