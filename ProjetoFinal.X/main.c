/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1827
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
const uint8_t matrix_conf[] = {
    0x09,0x00,  // Decode mode = 0
    0x0A,0x00,  // Intensity 1/32
    0x0B,0x07,  // Scan Limit
    0x0C,0x01,  // Shutdown mode = 1
    0x0F,0x01,  // Display-Test = 1
    0x0F,0x00,  // Display-Test = 0
};  ///< Configuração da matriz de  LEDs

#define flip_matrix  true

bool subindo = true;
uint8_t MatrixLed[8];
uint8_t destinoSub= 0; // indice 1 para andar 1, 2 para andar 2 e 3 para andar 3
uint8_t destinoDesc= 0;// indice 0 para andar 0, 1 para andar 1 e 2 para andar 2
void txSpi( uint8_t *data, size_t dataSize){
    CS_SetLow();            // Ativa CS
    SPI1_ExchangeBlock(data,dataSize);// Tx
    CS_SetHigh();          // Desativa CS
    
    //__delay_us(1);
}

void matrixUpdate(){
    uint8_t data[2];                   // Buffer para tx spi
    if (flip_matrix){                        // No Lab Remoto a imagem aparece invertida na horizontal
        for(uint8_t i=8;i>0;i--){          // Endere?a digitos 7..0
            data[0] = i;                   // Digito i da Matriz
            data[1] = MatrixLed[i-1];    // Valor do digito i da Matriz  
            txSpi(data, 2);        // Tx valores dos d?gitos dig para as matrizes
        }
    }else{
        uint8_t index = 7;                  //Indice da matrix de dados
        for(uint8_t i=1;i<9;i++){          // Endere?a digitos 0..7

            data[0] = i;                   // Digito i da Matriz
            data[1] = MatrixLed[index];    // Valor do digito i da Matriz  
            txSpi(data, 2);        // Tx valores dos d?gitos dig para as matrizes
            index--;
        }
    }
}
   
void initMatrix(){
    uint8_t data[4];            // Buffer para tx spi
    uint8_t k=0;                // Ponteiro do arranjo da configuração das matrizes
   for(uint8_t  i =0; i<8; i++){// Zera dígitos
            MatrixLed[i] = 0;
        }        
    for(uint8_t i=0;i<6;i++){   // Envia os 8 valores de configuração
        for(uint8_t j=0;j<4;j=j+2){
            data[j]= matrix_conf[k];    // Define o endereço dos registradores de configuração
            data[j+1]= matrix_conf[k+1];// Define o valor dos registradores de configuração
        }
        k=k+2;                  // Inc ponteiro da configuração     
        txSpi( data, 4); // Tx configuração para a  matriz de LED
        if(i==4){               // Display-Test
            //__delay_ms(800);
        }
    }
}

void chegadaS1(){ //função acionada ao sensor S1 ser acionado
    //Atualização da variavel da matrix de de Dados com o numero 0 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b01111110;
    MatrixLed[1] = 0b10000001;
    MatrixLed[2] = 0b10000001;
    MatrixLed[3] = 0b01111110;
    MatrixLed[4] = 0;
    if(subindo){//seta apontando pra cima
        MatrixLed[5] =  0b01100000;
        MatrixLed[6] =  0b11000000;
        MatrixLed[7] =  0b01100000;
    }else{ //seta apontando pra baixo
        MatrixLed[5] =  0b11000000;
        MatrixLed[6] =  0b01100000;
        MatrixLed[7] =  0b11000000;
        destinoDesc = destinoDesc & 0b11111110; //limpa a flag que mantem o andar 0 como destino do elevador
    }
    matrixUpdate();
}

void chegadaS2(){ //função acionada ao sensor S2 ser acionado
    //Atualização da variavel da matrix de de Dados com o numero 1 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b00000000;
    MatrixLed[1] = 0b01000001;
    MatrixLed[2] = 0b11111111;
    MatrixLed[3] = 0b00000001;
    MatrixLed[4] = 0;
    if(subindo){//seta apontando pra cima
        MatrixLed[5] =  0b01100000;
        MatrixLed[6] =  0b11000000;
        MatrixLed[7] =  0b01100000;
        destinoSub = destinoSub & 0b11111101; //limpa a flag que mantem o andar 1 como destino do elevador
    }else{ //seta apontando pra baixo
        MatrixLed[5] =  0b11000000;
        MatrixLed[6] =  0b01100000;
        MatrixLed[7] =  0b11000000;
        destinoDesc = destinoDesc & 0b11111101; //limpa a flag que mantem o andar 1 como destino do elevador
    }
    MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;
    matrixUpdate();
}

void chegadaS3(){ //função acionada ao sensor S3 ser acionado
    //Atualização da variavel da matrix de de Dados com o numero 2 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b01000011;
    MatrixLed[1] = 0b10000101; 
    MatrixLed[2] = 0b10001001; 
    MatrixLed[3] = 0b01110001; 
    MatrixLed[4] = 0;
    if(subindo){//seta apontando pra cima
        MatrixLed[5] =  0b01100000;
        MatrixLed[6] =  0b11000000;
        MatrixLed[7] =  0b01100000;
        destinoSub = destinoSub & 0b11111011; //limpa a flag que mantem o andar 2 como destino do elevador
    }else{ //seta apontando pra baixo
        MatrixLed[5] =  0b11000000;
        MatrixLed[6] =  0b01100000;
        MatrixLed[7] =  0b11000000;
        destinoDesc = destinoDesc & 0b11111011; //limpa a flag que mantem o andar 2 como destino do elevador
    }
    MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;
    matrixUpdate();
}

void chegadaS4(){ //função acionada ao sensor S4 ser acionado
    //Atualização da variavel da matrix de de Dados com o numero 3 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b10000001;
    MatrixLed[1] = 0b10010001;
    MatrixLed[2] = 0b10010001;
    MatrixLed[3] = 0b01101110;
    MatrixLed[4] = 0;
    if(subindo){//seta apontando pra cima
        MatrixLed[5] =  0b01100000;
        MatrixLed[6] =  0b11000000;
        MatrixLed[7] =  0b01100000;
        destinoSub = destinoSub & 0b11110111; //limpa a flag que mantem o andar 3 como destino do elevador
    }else{ //seta apontando pra baixo
        MatrixLed[5] =  0b11000000;
        MatrixLed[6] =  0b01100000;
        MatrixLed[7] =  0b11000000;
        destinoDesc = destinoDesc & 0b11110111; //limpa a flag que mantem o andar 3 como destino do elevador
    }
    MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;
    matrixUpdate();
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:
    
    //Handlers das Interrupçoes
        /*Caso a Interrupcao nao tenha handler,
            a funcao esta sendo chamada dentro da funcao de interrupcao do periferico*/
    IOCBF3_SetInterruptHandler(chegadaS1);
    IOCBF3_SetInterruptHandler(chegadaS2);
    
    
    //Incializacao do SPI
    CS_SetHigh(); //Mantem Desativado o CS
    SPI1_Open(SPI1_DEFAULT);        // Configura MSSP1
    initMatrix();                   // Configura matrizes
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        // Add your application code
        chegadaS1();
        __delay_ms(1000);
        chegadaS2();
        __delay_ms(1000);
        chegadaS3();
        __delay_ms(1000);
        chegadaS4();
    }
}
/**
 End of File
*/