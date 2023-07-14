/* 
 * File:   main.h
 * Author: Victor
 *
 * Created on 13 July 2023, 22:06
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Variaveis Globais 
*/
union{
    char v;
    struct{
        char o : 4;
        char d : 4;
    };
}rxValue; // Variavel para receber as informações do USART
bool waitRX = false; // Indica se o micro-controlador deve aguardar pelos valores de origem e destino do elevador
bool RXaccepted = false; // Indica que o valor recebido pela comunicação serial é valida

uint8_t origem; // Indica origem da chamada do elevador
uint8_t destino; // Indica o destino do elevador

bool isValidFloor(char floor);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

