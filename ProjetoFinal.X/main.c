/*
 * 
 * Grupo 5
 * 
 * Thalis Ianzer
 * Victor Cruz
 * Jordano dos Santos
 * Guilherme Costa
 * 
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"

void acionaponte(){
    while(mover){        
        PWM3_LoadDutyValue(511);
        if (subindo==true){
            __delay_ms(500);
            Dir_SetHigh();
        }
        else {
            __delay_ms(500);
            Dir_SetLow();
        }
    }
}
void gotoa1(){
    subindo = false;
    while(!IOCBF0){
        mover=true;
        acionaponte();
    }
}
void gotoa2(){
    if(andaratual>proxandar){
        subindo=false;
        while(!IOCBF3){
            mover=true;
            acionaponte();
        }
    }
    else{
        subindo=true;
        while(!IOCBF3){
            mover=true;
            acionaponte();
        }
    }
}
void gotoa3(){
    if(andaratual>proxandar){
        subindo=false;
        while(PIR2bits.C1IF){
            mover=true;
            acionaponte();
        }
    }
}
void gotoa4(){
    subindo = true;
    while(PIR2bits.C2IF=0){
        mover=true;
        acionaponte();
    }
}


void path(){
    if (pathup>0){
        while(pathup>0){
        }
    }
}

void orderpath(){
    uint8_t j = 5;
    
    
}




void readrx(){
    uint8_t i=0;
    for(i<5,i++;){
        rxdata = EUSART_Read();
        origens.bytes[i] = rxdata&&00001111;
        destinos.bytes[i]= rxdata&&11110000;                
    }
}


void interrupcaoCCP4(){
    
    if (pulsoEncoder <= 215){
        pulsoEncoder++;
    } else {
        pulsoEncoder = 0;
    }
    
    if(!flag){
        t1 = (CCPR4H << 8) + CCPR4L;   // Tempo da primeira interrupcao
        flag = 0x01;
    } else {
        t2 = (CCPR4H << 8) + CCPR4L;   // Tempo da segunda interrupcao
        flag = 0x02;
        
        velocidadeMotor = (0.8372 * pulsoEncoder) / ((t2 - t1) / 1000000); // (mm/pulsos) / (tempo(s))
    }
}

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
    andaratual=0;
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
    andaratual=1;
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
    andaratual=2;
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
    andaratual=3;
}

void main(void)
{
    SYSTEM_Initialize();
    
    //Handlers das Interrupçoes
        /*Caso a Interrupcao nao tenha handler,
            a funcao esta sendo chamada dentro da funcao de interrupcao do periferico*/
    CCP4_SetCallBack(interrupcaoCCP4);
    IOCBF3_SetInterruptHandler(chegadaS1);
    IOCBF3_SetInterruptHandler(chegadaS2);
    
    
    //Incializacao do SPI
    CS_SetHigh();                   //Mantem Desativado o CS
    SPI1_Open(SPI1_DEFAULT);        // Configura MSSP1
    initMatrix();                   // Configura matrizes
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

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