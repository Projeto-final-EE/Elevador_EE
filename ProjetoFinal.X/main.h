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

//Includes
#include "bin2bcd.h"
    
//Defines
#define flip_matrix  true
#define DUTY 500
// Enums
typedef enum{
    START,
    FIRST_NUM,
    SECOND_NUM,
    CR    
}State;

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

//Maquinas de Estados
State state = START; // O estado que indica qual valor o EUSART esta aguardando
enum estadoMov{ Repouso, Espera, EmTrajeto, RetornaS0}mov=Repouso;

//variaveis USART
char rxValue; // Variavel para receber as informacoes do USART
bool waitRX = false; // Indica se o micro-controlador deve aguardar pelos valores de origem e destino do elevador
bool RXaccepted = false; // Indica que o valor recebido pela comunicacao serial e valida
uint8_t contComandos=0 ; //Numero de comandos enviados ao elevador

//Dados para envio
uint8_t pulsoEncoder = 0;       // Numero de pulsos do encoder
float velocidadeMotor = 0;   // Velocidade do motor (transformar em 9 bits))
uint8_t flag = 0x00;            // Flag auxiliar para CCP4
uint16_t t1 = 0, t2 = 0;        // Tempo 1 e 2 para CCP4

uint8_t origem = 0, oTemp; // Indica origem da chamada do elevador
uint8_t destino = 0, dTemp; // Indica o destino do elevador
uint8_t andarAtual = 0; // Indica o andar atual
uint8_t altura; // Valor da altura atual
uint16_t temperatura; // Valor da temperatura do motor

bool subindo = true; //flag que indica se o elevador estA subindo ou descendo
uint8_t MatrixLed[8]; //Matrix de Dados que armazena o valor a ser transmito por SPI para a matrix de LED
uint8_t destinoSub= 0b00000000; // indice 1 para andar 1, 2 para andar 2 e 3 para andar 3
uint8_t destinoDesc= 0b00000000;// indice 0 para andar 0, 1 para andar 1 e 2 para andar 2

//Funcoes

/**
 * Funcao para checar se o char � um n�mero entre '0' e '3', que sao os andares de operacao do elevador
 * @param floor
 * @return true se o char � um n�mero entre '0' e '3' e false se nao �
 */
bool isValidFloor(char floor);

/**
  @Summary
    Timer1 Interrupt Handler function

  @Description
 Essa funcao envia as informacoes atuais sobre o elevador por meio da comunicacao serial

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void sendInfo(void);

void organizaTrajeto();

//func�es SPI
void txSpi( uint8_t *data, size_t dataSize); //funcao que realiza a transmissao da matriz de Dados para a Matriz de LED
void matrixUpdate(); //Funcao que converte os valores da Matriz de Dados para a forma recebida pela Matriz de LED
void initMatrix(); //Inicializacao da matriz de LED

//Interrupcoes sensores
void chegadaS1(); //função acionada ao sensor S1 ser acionado
void chegadaS2(); //função acionada ao sensor S2 ser acionado
void chegadaS3(); //função acionada ao sensor S3 ser acionado
void chegadaS4(); //função acionada ao sensor S4 ser acionado

//Funcoes Ponte-H
void controleMovimento();


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

