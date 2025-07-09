#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PATH_MAX 100

char cwd[PATH_MAX];


/*** Inizializzazione delle funzioni ***/
void changeDirectory(char* path);
void printHelp();
void printVersion();


/*** Gestisce il cambio della directory ***/
void changeDirectory(char* path){
        char fullpath[PATH_MAX];

        if(path[0] == '/'){
                if(chdir(path) != 0) perror("chdir ha fallito\n");
        }else{
                if(getcwd(cwd, sizeof(cwd)) != NULL){
                        snprintf(fullpath, sizeof(fullpath)+1, "%s/%s", cwd, path);
                        if(chdir(fullpath) != 0) perror("chdir ha fallito\n");
                }
        }
}

/*** Stampa del comando Help ***/
void printHelp(){
        printf("cd è un binario che ti permette di spostarti in un altro percorso rispetto a quello attuale\n\n"
                "Il formato richiesto è il seguente:\n"
                "./cd [path]\n\n"
                "Le opzioni disponibili sono le seguenti:\n"
                "-h Mostra l'elenco delle opzioni disponibili\n"
                "-v Mostra la versione attuale del programma\n"

                        );

        exit(1);
}

/*** Stampa del comando Version ***/
void printVersion(){
        printf("cd binary v. 0.0.1\tMade with <3 by 0xChryy\n");
        exit(1);
}

int main(int argc, char *argv[]){
        int opt;
        if(argc>1){
                while ((opt = getopt(argc, argv, "hv")) != -1){  //Per ogni opzione che trova
                        switch(opt){
                                case 'h':
                                        printHelp();
                                        break;
                                case 'v':
                                        printVersion();
                                        break;
                                default:
                                        for(int i=0;i<argc;i++){
                                                if(argv[i][0] == '-'){
                                                        printf("Comando non valido");
                                                }else{
                                                        changeDirectory(argv[i]);   //Cambio di directory
                                                }
                                        }
                                        break;
                        }
                }
        }
        return 0;
}