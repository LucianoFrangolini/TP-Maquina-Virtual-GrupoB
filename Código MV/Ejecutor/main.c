#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "memoria.h"
#include "funciones.h"

typedef void (*VectorFunciones[4096])(Memoria*);

//instruccion  memoria->RAM[memoria->VectorRegistros[4]]
//operando 1   memoria->RAM[memoria->VectorRegistros[4]+1]
//operando 2   memoria->RAM[memoria->VectorRegistros[4]+2]

int main(int argc, char *argv[])
{

    Memoria memoria;
    Header header;
    VectorFunciones vecF;
    int ip, cod;

    //FILE *arch=fopen("","rb");
    FILE *arch=fopen(argv[1],"rb");

    srand (getpid());   //Cambia la semilla en cada ejecución del programa para la instrucción random

    vecF[0x00]=&MOV;
    vecF[0x01]=&ADD;
    vecF[0x02]=&SUB;
    vecF[0x03]=&SWAP;
    vecF[0x04]=&MUL;
    vecF[0x05]=&DIV;
    vecF[0x06]=&CMP;
    vecF[0x07]=&SHL;
    vecF[0x08]=&SHR;
    vecF[0x09]=&AND;
    vecF[0x0A]=&OR;
    vecF[0x0B]=&XOR;

    vecF[0xF0]=&SYS;
    vecF[0xF1]=&JMP;
    vecF[0xF2]=&JZ;
    vecF[0xF3]=&JP;
    vecF[0xF4]=&JN;
    vecF[0xF5]=&JNZ;
    vecF[0xF6]=&JNP;
    vecF[0xF7]=&JNN;
    vecF[0xF8]=&LDL;
    vecF[0xF9]=&LDH;
    vecF[0xFA]=&RND;
    vecF[0xFB]=&NOT;

    vecF[0xFF1]=&STOP;

    fread(&header,sizeof(Header),1,arch);
    fread(&memoria,sizeof(Memoria),1,arch);

    fclose(arch);

    system("cls");

    ip = memoria.VectorDeRegistros[5]++;
    //cod = decodificaCodigo(memoria.RAM[ip]);
    cod = decodificaCodigo(0x0C1FFFFF); //Esta linea es para probar entrar a las funciones, despues BORRAR y usar la de arriba
    //decodificaOperandos(0x0C1FFFFF,&op1,&op2);
    vecF[cod](&memoria);

   /* while( (0 <= memoria.VectorDeRegistros[5]) && (memoria.VectorDeRegistros[5]<memoria.VectorDeRegistros[0]) ){
        //Aca van las lineas de arriba
    }*/

    return 0;
}

