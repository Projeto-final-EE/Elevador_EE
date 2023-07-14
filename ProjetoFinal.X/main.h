/* 
 * File:   main.h
 * Author: AC Tecnologia
 *
 * Created on 13 de Julho de 2023, 19:54
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

//Defines
#define flip_matrix  true

//Constantes 
const uint8_t matrix_conf[] = {
    0x09,0x00,  // Decode mode = 0
    0x0A,0x00,  // Intensity 1/32
    0x0B,0x07,  // Scan Limit
    0x0C,0x01,  // Shutdown mode = 1
    0x0F,0x01,  // Display-Test = 1
    0x0F,0x00,  // Display-Test = 0
};  ///< Configuração da matriz de  LEDs

/**
 * Variaveis Globais 
*/
union{
    char v;
    struct{
        char o : 4;
        char d : 4;
    };
}rxValue; // Variavel para receber as informa��es do USART
bool waitRX = false; // Indica se o micro-controlador deve aguardar pelos valores de origem e destino do elevador
bool RXaccepted = false; // Indica que o valor recebido pela comunica��o serial � valida

uint8_t origem; // Indica origem da chamada do elevador
uint8_t destino; // Indica o destino do elevador

bool subindo = true; //flag que indica se o elevador est� subindo ou descendo
uint8_t MatrixLed[8]; //Matrix de Dados que armazena o valor a ser transmito por SPI para a matrix de LED
uint8_t destinoSub= 0; // indice 1 para andar 1, 2 para andar 2 e 3 para andar 3
uint8_t destinoDesc= 0;// indice 0 para andar 0, 1 para andar 1 e 2 para andar 2

//Funções

/**
 * Funcao para checar se o char � um n�mero entre '0' e '3', que sao os andares de operacao do elevador
 * @param floor
 * @return true se o char � um n�mero entre '0' e '3' e false se nao �
 */
bool isValidFloor(char floor);

//func�es SPI
void txSpi( uint8_t *data, size_t dataSize); //funcao que realiza a transmissao da matriz de Dados para a Matriz de LED
void matrixUpdate(); //Funcao que converte os valores da Matriz de Dados para a forma recebida pela Matriz de LED
void initMatrix(); //Inicializacao da matriz de LED
void chegadaS1(); //função acionada ao sensor S1 ser acionado
void chegadaS2(); //função acionada ao sensor S2 ser acionado
void chegadaS3(); //função acionada ao sensor S3 ser acionado
void chegadaS4(); //função acionada ao sensor S4 ser acionado
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

