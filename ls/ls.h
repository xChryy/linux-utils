#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>


/*** Struttura per i flag del comando ls ***/
typedef struct{
        int a_flag;         // -a (mostra i file nascosti)
        int l_flag;         // -l (formato long)
        int F_flag;         // -F (indicatori di tipo)
        int r_flag;         // -r (ordine inverso)
        int t_flag;         // -t (ordina per tempo)
        int S_flag;         // -S (ordina per dimensione)
        int d_flag;         //  -d (directory come file)
        int one_flag;       // -1 (un file per riga)
        int color_flag;     // --color
} Flags;


/*** Struttura per contenere informazioni di un file ***/
typedef struct{
        char *name;               // Nome del file
        char *path;               // Path completo
        struct stat stat_info;    // Informazioni stat
        int is_directory;         // è una directory?
        int is_hidden;            // è un file nascosto?
}FileInfo;


/*** Variabile globale per i flag ***/
extern Flags flags;

/*** Dichiarazionni delle funzioni ***/
void initFlags(void);
int parseArguments(int argc, char *argv[]);
void displayUsage(void);
FileInfo createFileInfo(const char *name, const char *parent_path);
void debugFileInfo(const FileInfo *file);
int shouldDisplayFile(const FileInfo *file);
void freeFileInfo(FileInfo *file);



#endif //LS_H