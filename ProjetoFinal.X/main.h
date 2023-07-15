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


//Variaveis Globais
bool subindo = true; //flag que indica se o elevador est� subindo ou descendo
uint8_t MatrixLed[8]; //Matrix de Dados que armazena o valor a ser transmito por SPI para a matrix de LED
uint8_t destinoSub= 0; // indice 1 para andar 1, 2 para andar 2 e 3 para andar 3
uint8_t destinoDesc= 0;// indice 0 para andar 0, 1 para andar 1 e 2 para andar 2

//Maquinas de Estados
enum estadoMov{ Repouso, IniciarTrajeto, EmTrajeto, RetornaS0}mov=Repouso;

//func�es SPI
void txSpi( uint8_t *data, size_t dataSize); //funcao que realiza a transmissao da matriz de Dados para a Matriz de LED
void matrixUpdate(); //Funcao que converte os valores da Matriz de Dados para a forma recebida pela Matriz de LED
void initMatrix(); //Inicializacao da matriz de LED
void chegadaS1(); //função acionada ao sensor S1 ser acionado
void chegadaS2(); //função acionada ao sensor S2 ser acionado
void chegadaS3(); //função acionada ao sensor S3 ser acionado
void chegadaS4(); //função acionada ao sensor S4 ser acionado

//Fun��es Ponte-H
void controleMovimento();
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

