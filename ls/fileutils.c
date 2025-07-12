#include "ls.h"

/*** Inizializza tutti i flag a 0 ***/
void initFlags(void){
        flags.a_flag = 0;
        flags.l_flag = 0;
        flags.F_flag = 0;
        flags.r_flag = 0;
        flags.t_flag = 0;
        flags.S_flag = 0;
        flags.d_flag = 0;
        flags.one_flag = 0;
        flags.color_flag = 0;
}

/*** Determina se il file è nascosto ***/

int isHiddenFile(const char *name){
        return(name[0] == '.' && strcmp(name, ".") != 0 && strcmp(name, "..") != 0);
}

/*** Crea una struttura FileInfo per un file ***/
FileInfo createFileInfo(const char *name, const char *dir_path){
        FileInfo file;

        // Alloca memoria per il nome
        file.name = malloc(strlen(name) + 1);
        strcpy (file.name,  name);

        // Determina se è  nascosto
        file.is_hidden = isHiddenFile(name);

        // Costruisce il path completo
        if(dir_path && strcmp(dir_path, ".") != 0){
                file.path = malloc(strlen(dir_path) + strlen(name) + 2);
                sprintf(file.path, "%s/%s", dir_path, name);
        }else{
                file.path = malloc(strlen(name) + 1);
                strcpy(file.path, name);
        }

        // Ottiene informazioni stat
        if(stat(file.path, &file.stat_info) == 0){
                file.is_directory = S_ISDIR(file.stat_info.st_mode);
        }else{
                //Se stat fallisce, inizializza con valori di default
                memset(&file.stat_info, 0, sizeof(struct stat));
                file.is_directory = 0;
                perror("stat");
        }

        return file;

}

/*** Libera la memoria di una struttura FileInfo ***/
void freeFileInfo(FileInfo *file){
        if(file->name){
                free(file->name);
                file->name = NULL;
        }
        if(file->path){
                free(file->path);
                file->path = NULL;
        }
}

/*** Determina se un file deve essere mostrato in base ai flag ***/
int shouldDisplayFile(const FileInfo *file){
        // Se non c'è -a, nascondi i file nascosti
        if(!flags.a_flag && file->is_hidden){
                return 0;  //Non mostrare
        }
        // Altre condizioni possono essere aggiunte qui

        return 1;  // Mostra
}


/*** Stampa informazioni per un file ***/
void debugFileInfo(const FileInfo *file){
        printf("DEBUG: File: %s\n", file->name);
        printf("        Path: %s\n", file->path);
        printf("        Hidden: %s\n", file->is_hidden ? "Sì" : "No");
        printf("        Directory: %s\n", file->is_directory ? "Sì":  "No");
        printf("        Size: %ld bytes\n", file->stat_info.st_size);
        printf("        Permissions: %o\n", file->stat_info.st_mode & 0777);
        printf("---\n");
}