#include "ls.h"

#define MAX_FILES 1000

/*** Scansiona una directory e restituisce un array di FileInfo ***/
int scanDirectory(const char *dir_path, FileInfo **files){
        DIR *dir;
        struct dirent *entry;
        FileInfo *file_list;
        int count = 0;

        printf("Scansionando directory:  %s\n", dir_path);

        // Apre la directory
        dir = opendir(dir_path);
        if(!dir){
                perror("opendir()");
                return 0;
        }

        // Alloca spazio per la lista dei file
        file_list = malloc(sizeof(FileInfo) * MAX_FILES);
        if(!file_list){
                perror("malloc()");
                closedir(dir);
                return 0;
        }

        //  Legge tutti i file nella directory
        while((entry = readdir(dir)) != NULL  && count < MAX_FILES){
                // Crea FileInfo per questo file
                file_list[count] = createFileInfo(entry->d_name, dir_path);
                count++;
        }

        closedir(dir);

        printf("Trovati %d file\n", count);
        *files = file_list;
        return count;
}

/*** Libera un array  di FileInfo ***/
void freeFileArray(FileInfo *files, int count){
        for(int i=0;i<count;i++){
                freeFileInfo(&files[i]);
        }
        free(files);
}

/*** Stampa semplicemente i nomi dei file ***/
void simpleDisplay(FileInfo *files, int count){
        printf("\n=== CONTENUTO DIRECTORY ===\n");

        for(int i=0;i<count;i++){
                if(shouldDisplayFile(&files[i])){
                        printf("%s\n", files[i].name);
                }
        }

        printf("=== FINE CONTENUTO ===\n");
}


int main(){
        printf("=== TEST SCANSIONE DIRECTORY ===\n");

        // Inizializza i flag
        initFlags();

        // Scansiona la directory corrente
        FileInfo *files;
        int  file_count = scanDirectory(".", &files);

        if(file_count > 0){
                printf("\nTest 1: Senza flag -a (nasconde file nascosti)\n");
                simpleDisplay(files, file_count);

                printf("\nTest 2: Con flag -a (mostra file nascosti)\n");
                flags.a_flag = 1;
                simpleDisplay(files, file_count);

                // Libera la memoria
                freeFileArray(files, file_count);
        }else{
                printf("Errore nella scansione della directory\n");
        }

        return 0;
}