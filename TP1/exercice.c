//
// Created by arnaud on 08/03/23.
//
#include "stdio.h"
#include "stdlib.h"
#define n 5

char getclasse(int bit1){
    if (bit1 < 128){
        return 'A';
    } else if (bit1 < 192){
        return 'B';
    } else if (bit1 < 224){
        return 'C';
    } else if (bit1 < 240){
        return 'D';
    } else{
        return 'E';
    }
}

void printinfo(int* bits, int32_t adr){
    printf("# addnet %d.%d.%d.%d/%d \n", bits[0], bits[1], bits[2], bits[3], bits[4]);
    printf("Classe: %c \n", getclasse(bits[0]));
    int32_t masque = adr;
    for (int i = 0; i < bits[4]; i++){
        masque = masque & 1;
        masque = masque << 1;
        printf("%d", masque);
    }
}

int main(int argc, char *argv[]){
    int bits[n];
    for (int i = 0; i < n; i++){
        bits[i] = atoi(argv[i + 1]);
    }
    int32_t adresse_ip = bits[0];
    for (int i = 1; i < n - 1; i++){
        adresse_ip = adresse_ip << 8;
        adresse_ip = adresse_ip | bits[i];
    }
    printinfo(bits, adresse_ip);
}