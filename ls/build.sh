#!/bin/bash

echo "=== COMPILAZIONE PROGETTO LS ==="

# Crea directory per i file oggetto
mkdir -p build

# Compila fileutils.c
echo "1. Compilando fileutils.c..."
gcc -Wall -Wextra -std=c99 -c fileutils.c -o build/fileutils.o
if [ $? -ne 0 ]; then
        echo "Errore nella compilazione di directory.c"
        exit 1
fi

# Compila sorting.c
echo "3. Compilando sorting.c..."
gcc -Wall -Wextra -std=c99 -c sorting.c -o build/sorting.o
if [ $? -ne 0 ]; then
        echo "Errore nella compilazione di sorting.c"
        exit 1
fi

# Compila test_basic
echo "4. Compilando test_basic.c..."
gcc -Wall -Wextra -std=c99 test_basic.c build/fileutils.o -o build/test_basic
if [ $? -ne 0 ]; then
        echo "Errore nella compilazione di test_basic"
        exit 1
fi

# Compila test directory
echo "5. Compilando test_directory..."
gcc  -Wall -Wextra -std=c99 -DTEST_DIRECTORY directory.c build/fileutils.o -o build/test_directory
if [ $? -ne 0 ]; then
        echo "Errore nella compilazione di test directory"
        exit 1
fi

echo ""
echo "=== COMPILAZIONE COMPLETATA ==="
echo ""
echo "Eseguibili creai in build/:"
echo "- test_basic: Test delle funzioni base"
echo "- test_directory: Test scansione directory"
echo "- test_sorting: Test ordinamento"
echo ""
echo "Per eseguire i test:"
echo "  ./build/test_basic"
echo "  ./build/test_directory"
echo "  ./build/test_sorting"
echo ""

# Funzione per eseguire tutti i ttest
if [ "$1" = "run" ]; then
        echo "=== ESECUZIONE DEI TEST ==="
        echo ""

        echo "--- Test Basic ---"
        ./build/test_basic
        echo ""

        echo "--- Test Directory ---"
        ./build/test_directory
        echo ""

        echo "--- Test Sorting ---"
        ./build/test_sorting
        echo ""

        echo "=== FINE TEST ==="
fi