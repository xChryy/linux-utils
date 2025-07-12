#include "ls.h"

/*** Funzione di confronto per ordinamento alfabetico ***/
int compareByName(const void *a, const void *b){
        const FileInfo *fileA = (const FileInfo *)a; // Viene fatto il casting dopo per prendere valori generici
        const FileInfo *fileB = (const FileInfo *)b;

        // Confronta i nomi e ritorna se fileA viene prima, dopo o è uguale a fileB
        return strcmp(fileA->name, fileB->name);
}

/*** Funzione di confronto per ordinamento per tempo (più recente prima) ***/
int compareByTime(const void *a, const void *b){
        const FileInfo *fileA = (const FileInfo *)a;
        const FileInfo *fileB = (const FileInfo *)b;

        // Ordine decrescente: più recente prima
        if(fileA->stat_info.st_mtime > fileB->stat_info.st_mtime) return -1;
        if(fileA->stat_info.st_mtime < fileB->stat_info.st_mtime) return 1;
        return 0;
}

/*** Funzione di confronto  per ordinamento per dimensione (più grande prima) ***/
int compareBySize(const void *a, const void *b){
        const FileInfo *fileA = (const FileInfo *)a;
        const FileInfo *fileB = (const FileInfo *)b;

        // Ordine decrescente: più grande prima
        if(fileA->stat_info.st_size > fileB->stat_info.st_size) return -1;
        if(fileA->stat_info.st_size < fileB->stat_info.st_size) return 1;
        return 0;
}

/*** Funzione per invertire l'ordine di un array ***/
void reverseArray(FileInfo *files, int count){
        FileInfo temp;

        for(int i=0;i<count / 2; i++){
                temp = files[i];
                files[i] = files[count- 1 - i];
                files[count - 1- i] = temp;
        }
}

/*** Funzione principale per ordinare in base ai flag ***/
void sortFiles(FileInfo *files, int count){
        printf("Ordinando %d file...\n", count);

        // Sceglie il tipo di ordinameto
        if(flags.t_flag){
                printf("Ordinamento per tempo\n");
                qsort(files, count, sizeof(FileInfo), compareByTime);
        } else if(flags.S_flag){
                printf("Ordinamento per dimensione\n");
                qsort(files, count, sizeof(FileInfo), compareBySize);
        } else{
                printf("Ordinamento alfabetico\n");
                qsort(files, count, sizeof(FileInfo), compareByName);
        }

        // Se c'è il flag -r, inverte l'ordine
        if(flags.r_flag){
                printf("Inversione dell'ordine\n");
                reverseArray(files, count);
        }
}


/*** Funzione per mosrare informazioni di ordinamento ***/
void showSortingInfo(FileInfo *files, int count){
        printf("\n=== INFORMAZIONI DI ORDINAMENTO ===\n");

        for(int i=0;i<count && i< 10; i++){ // Mostra solo i primi 10
                if(shouldDisplayFile(&files[i])){
                        printf("%s", files[i].name);

                        if(flags.t_flag){
                                char time_str[64];
                                struct tm *tm_info = localtime(&files[i].stat_info.st_mtime);
                                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
                                printf(" [%s]", time_str);
                        }

                        if(flags.S_flag){
                                printf(" [%ld bytes]", files[i].stat_info.st_size);
                        }

                        printf("\n");
                }
        }

        if(count > 10){
                printf("... e altri %d file\n", count - 10);
        }
}

/*** Test dell'ordinamento ***/
int main(){

        printf("=== TEST ORDINAMENTO ===\n");

        // Inizializza i flag
        initFlags();

        // Scansiona la directory corrente
        FileInfo *files;
        int file_count = scanDirectory(".", &files);

        if(file_count > 0){
                printf("\nTest 1: Ordinamento alfabetico\n");
                sortFiles(files, file_count);
                showSortingInfo(files, file_count);

                printf("\nTest 2: Ordinamento per tempo\n");
                flags.t_flag = 1;
                sortFiles(files, file_count);
                showSortingInfo(files, file_count);

                printf("\nTest 3: Ordinamento per tempo inverso\n");
                flags.r_flag = 1;
                sortFiles(files, file_count);
                showSortingInfo(files, file_count);

                // Libera la memoria
                freeFileArray(files, file_count);
        }


        return 0;
}