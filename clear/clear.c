#include <stdio.h>


/*** Escape per resettare la shell ***/
int main(){
        printf("\x1b[H\x1b[2J\x1b[3J");

}