#include "ls.h"

/*** Definizione della variabile globale ***/
Flags flags;

int main(){
        printf("=== TEST BASIC LS FUNCTIONS ===\n\n");

        // Inizializza i flag
        initFlags();
        printf("1. Flag inizializzati\n");

        // Test creazione FileInfo per alcuni file
        printf("\n2. Test Creazione FileInfo:\n");

        // Testa con il file corrente
        FileInfo file1 = createFileInfo("test_basic.c", ".");
        printf("File creato: %s\n", file1.name);
        debugFileInfo(&file1);

        // Testa con la directory corrente
        FileInfo file2 = createFileInfo(".", NULL);
        printf("Directory creata: %s\n", file2.name);
        debugFileInfo(&file2);

        // Test shouldDisplayFile
        FileInfo hidden_file = createFileInfo(".hidden", ".");
        printf("\n3.  Test shouldDisplayFile:\n");
        printf("File normale (senza -a):%s\n",
                        shouldDisplayFile(&file1) ? "Mostrato" : "Nascosto");

        // Abilita flag -a e esta di nuovo
        flags.a_flag = 1;
        printf("File nascosto (con -a) %s\n",
                        shouldDisplayFile(&hidden_file) ? "Mostrato" : "Nascosto");

        //Libera la memoria
        freeFileInfo(&file1);
        freeFileInfo(&file2);
        freeFileInfo(&hidden_file);

        printf("\n=== TEST COMPLETATO ===\n");
        return 0;


}