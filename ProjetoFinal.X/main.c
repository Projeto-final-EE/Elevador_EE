/*
        Grupo 5

        Thalis Ianzer
        Jordano Santos
        Victor Cruz
        Guilherme Costa

*/

#include "mcc_generated_files/mcc.h"
#include "main.h"


/**
 * Funcao que aplica as mascaras as variaveis destinoSub e DestinoDesc que controlam as paradas do elvador aos andares
 * @param void
 * @return void
*/
void organizaTrajeto(){
    uint8_t mascaraOrigem = 1<<origem;                          // Desloca o bit '1' ate a posicao do andar escolhido com origem
    uint8_t mascaraDestino = 1<<destino;                        // Desloca o bit '1' ate a posicao do andar escolhido com destino
    
    if(origem == 0){
        destinoSub = destinoSub | mascaraDestino;
    }else if (origem < destino)
    {
        destinoSub =destinoSub | mascaraOrigem | mascaraDestino;// Aplica ambas as mascaras simultaneamente aos andares de destino de subida
    }else if(origem > destino){                                 // Elevador sobe até a origem e depois desce ate o destino
        destinoSub = destinoSub| mascaraOrigem;
        destinoDesc = destinoDesc| mascaraDestino;
    }

    if (mov == RetornaS0)                                       // Caso o percuso ja tenha acabado e ele estiver esperando um novo comando
    {
        mov = EmTrajeto;                                        // Retoma o trajeto
        //Reinicia o Timer4
        TMR4_WriteTimer(0);
        TMR4_StartTimer;
    }else{
        mov = EmTrajeto;
    }
    
}

/**
 * Funcao que altera o sentido de movimento do elevador
 * @param void
 * @return void
*/
void alteraSentido(){
    if (destinoSub != 0 && mov == RetornaS0)
    {
        mov = EmTrajeto;
    }else if(destinoDesc ==0 && destinoSub == 0){
        mov = Espera;
    }

}

/**
 * Funcao para checar se o char eh um numero entre '0' e '3', que sao os andares de operacao do elevador
 * @param floor
 * @return true se o char for um numero entre '0' e '3' e false se nao for
 */
bool isValidFloor(char floor){
    return floor >= '0' && floor <= '3';
}

/**
 * Funcao que calcula temperatura da ponte H
 * @param void
 * @return uint16_t temperatura
 */
uint16_t calcTemp(){
    return ((ADC_GetConversion(2) / 1024.f) * 999);
}

/**
 * Funcao que envia os dados por UART
 * @param void
 * @return void
*/
void sendInfo(){    
    bcd16_t bcd;
    static uint8_t aux_altura = 0;
    uint8_t destinoAtual=0;
    uint16_t velocidade;
    uint8_t mascara=0;
    
    if (subindo){
        mascara = 0b00000001;
    }else{
         mascara = 0b0001000;
    }
    for(uint8_t i = 0; i<4; i++ ){
        uint8_t v= 0;
        if(subindo){
            mascara = mascara<<1;
            v =destinoSub&mascara;
        }else{
            mascara = 1>>mascara;
            v =destinoDesc&mascara;
        }
        if(v !=0 ){
            destinoAtual = v;
            break;
        }
    }
   
    switch(destinoAtual){
        case 2:
            destinoAtual=1;
            break;
        case 4:
            destinoAtual=2;
            break;
        case 8:
            destinoAtual = 3;
            break;
        default:
            destinoAtual = 4;
    }
    
    altura = (1.5 * pulsoEncoder);                      // Ajusta o valor da altura/pulsoEnconder
    velocidadeMotor = abs(altura - aux_altura)/ 0.300;  // (mm/pulsos) / (tempo(s))    
    velocidade = (uint16_t)(velocidadeMotor * 10);      // Ajustando o valor da velocidade para ser enviado
    aux_altura = altura;

    temperatura = calcTemp();           // Calcula a temperatura
    
    EUSART_Write('$');                  // Caracter inicial
    
    EUSART_Write(0x30 + andarAtual);    // Envia o andar atual em ASCII
    EUSART_Write(0x2C);                 // Envia a virgula
    EUSART_Write(0x30 + destinoAtual);  // Envia o andar destino em ASCII
    EUSART_Write(0x2C);                 // Envia a virgula
    EUSART_Write(0x30 + motor);         // Envia o estado atual do motor
    
    EUSART_Write(0x2C);                 // Envia a virgula
    // Enviando a altura em mm
    bcd.v = bin2bcd(altura);
    EUSART_Write(bcd.num2 + 0x30);      // Envia o primeiro digito
    EUSART_Write(bcd.num3 + 0x30);      // Envia o segundo digito
    EUSART_Write(bcd.num4 + 0x30);      // Envia o terceiro digito
    EUSART_Write(0x2C);                 // Envia a virgula
    // Enviando a velocidade em mm/s
    bcd.v = bin2bcd(velocidade);
    EUSART_Write(bcd.num2 + 0x30);      // Envia o primeiro digito
    EUSART_Write(bcd.num3 + 0x30);      // Envia o segundo digito
    EUSART_Write(0x2E);                 // Envia o ponto
    EUSART_Write(bcd.num4 + 0x30);      // Envia o digito decimal
    EUSART_Write(0x2C);                 // Envia a virgula
    // Enviando a temperatura em C
    bcd.v = bin2bcd(temperatura);
    EUSART_Write(bcd.num1 + 0x30);      // Envia o primeiro digito
    EUSART_Write(bcd.num2 + 0x30);      // Envia o segundo digito
    EUSART_Write(bcd.num3 + 0x30);      // Envia o terceiro digito
    EUSART_Write(0x2E);                 // Envia o ponto
    EUSART_Write(bcd.num4 + 0x30);      // Envia o digito decimal
    EUSART_Write(0x0D);                 // Envia o carriage return
}

/**
 * Funcao que trata interrupção do CCP4 (Enconder)
 * @param void
 * @return void
*/
void interrupcaoCCP4(){
    if (subindo){
        pulsoEncoder++;
    } else {
        pulsoEncoder--;
    }
}

/**
 * Funcao que realiza a comunicacao com a matriz de leds
 * @param void
 * @return void
*/
void txSpi( uint8_t *data, size_t dataSize){
    CS_SetLow();                        // Ativa CS
    SPI1_ExchangeBlock(data,dataSize);  // Tx
    CS_SetHigh();                       // Desativa CS
}

/**
 * Funcao que atualiza os dados na matriz de led
 * @param void
 * @return void
*/
void matrixUpdate(){
    uint8_t data[2];                    // Buffer para tx spi
    if (flip_matrix){                   // No Lab Remoto a imagem aparece invertida na horizontal
        for(uint8_t i=8;i>0;i--){       // Endereca digitos 7..0
            data[0] = i;                // Digito i da Matriz
            data[1] = MatrixLed[i-1];   // Valor do digito i da Matriz  
            txSpi(data, 2);             // Tx valores dos d?gitos dig para as matrizes
        }
    /*}else{
        uint8_t index = 7;              //Indice da matrix de dados
        for(uint8_t i=1;i<9;i++){       // Endereca digitos 0..7

            data[0] = i;                // Digito i da Matriz
            data[1] = MatrixLed[index]; // Valor do digito i da Matriz  
            txSpi(data, 2);             // Tx valores dos digitos dig para as matrizes
            index--;
        }
    }*/
}

/**
 * Funcao de inicialização da matriz de led
 * @param void
 * @return void
*/
void initMatrix(){
    uint8_t data[4];                    // Buffer para tx spi
    uint8_t k=0;                        // Ponteiro do arranjo da configuração das matrizes
   for(uint8_t  i =0; i<8; i++){        // Zera digitos
            MatrixLed[i] = 0;
        }        
    for(uint8_t i=0;i<6;i++){           // Envia os 8 valores de configuração
        for(uint8_t j=0;j<4;j=j+2){
            data[j]= matrix_conf[k];    // Define o endereço dos registradores de configuracao
            data[j+1]= matrix_conf[k+1];// Define o valor dos registradores de configuracao
        }
        k=k+2;                          // Inc ponteiro da configuracao     
        txSpi(data, 4);                // Tx configuracao para a  matriz de LED
        if(i==4){                       // Display-Test
            //__delay_ms(800);
        }
    }
}

/**
 * Funcao que realiza o controle do movimento do motor para cada caso
 * @param void
 * @return void
*/
void controleMovimento(){
    static uint8_t cont = 0;
    switch(mov){
        case Repouso:
            PWM3_LoadDutyValue(0);
            cont = 0;
            break;
        case Espera:
            if (cont >=4){
                mov = RetornaS0; //Caso não tenha tido atualizacoes no trajeto entra em retornaS0
                cont = 0;
            }else{
                cont++;
            }
            break;
        case EmTrajeto:
            PWM3_LoadDutyValue(DUTY);
            cont = 0;
            break;
        case RetornaS0:
            PWM3_LoadDutyValue(DUTY);
            cont = 0;
            break;
    }
    
    if(destinoSub != 0 && mov != RetornaS0){//Determina o sentido do movimento do motor
        //Seta o movimento ascendente do motor
        subindo = true;
        Dir_SetHigh();
        if(mov == EmTrajeto /*|| mov == RetornaS0*/){
            MatrixLed[5] =  0b01100000;
            MatrixLed[6] =  0b11000000;
            MatrixLed[7] =  0b01100000;
            motor = 1;
        }
    }else{
        //Seta o movimento ascendente do motor
        subindo = false;
        Dir_SetLow();
        if(mov == EmTrajeto || mov == RetornaS0){
            MatrixLed[5] =  0b11000000;
            MatrixLed[6] =  0b01100000;
            MatrixLed[7] =  0b11000000;
            motor = 2;
        }
    }
    
    MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;
    matrixUpdate();
}

/**
 * Funcao para apagar flag dos destinos e desenhar a barra na matriz de led
 * @param void
 * @return void
*/
void apagaFlag(){
    MatrixLed[5] =  0b00100000;
    MatrixLed[6] =  0b00100000;
    MatrixLed[7] =  0b00100000;
    MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;
}

/**
 * Funcao que trata a interrupção do sensor S1
 * @param void
 * @return void
*/
void chegadaS1(){ 
    //Atualizacao da variavel da matrix de de Dados com o numero 0 mais a direcao de movimento do elevador
    motor = 0;
    andarAtual = 0;
    pulsoEncoder = 1;
    
    //Ao chegar no primeiro andar o elevador ja finalizou todo seu trajeto
    //Atualizacao da variavel da matrix de de Dados com o numero 0 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b01111110;
    MatrixLed[1] = 0b10000001;
    MatrixLed[2] = 0b10000001;
    MatrixLed[3] = 0b01111110;
    MatrixLed[4] = 0;
    /*MatrixLed[5] =  0b00100000;
    MatrixLed[6] =  0b00100000;
    MatrixLed[7] =  0b00100000;*/
    if(subindo){                                //seta apontando pra cima
        destinoSub = destinoSub & 0b11111110;   //limpa a flag que mantem o andar 3 como destino do elevador
    }else{                                      //seta apontando pra baixo
        destinoDesc = destinoDesc & 0b11111110; //limpa a flag que mantem o andar 0 como destino do elevador
        mov = Repouso;
        //contComandos = 0;
        TMR4_StartTimer();
    }
    apagaFlag();
    matrixUpdate();
    
    /*MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;*/
}

/**
 * Funcao que trata a interrupcao do sensor S2
 * @param void
 * @return void
*/
void chegadaS2(){
    //Atualizacao da variavel da matrix de de Dados com o numero 1 mais a direcao de movimento do elevador
    motor = 0;
    andarAtual = 1;
    
    //Caso o Andar 3 seja um ponto de Parada reinicia o TRM1 que controla o tempo de espera do elevador
    if((((destinoSub & 0b00000010) == 2 )&& subindo)||(!subindo &&((destinoDesc & 0b00000010) == 2) ) ){ 
        PWM3_LoadDutyValue(0);//Desligando o Movimento do Motor
        TMR4_WriteTimer(0); 
        TMR4_StartTimer();
    }
    
    //Atualizacao da variavel da matrix de de Dados com o numero 1 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b00000000;
    MatrixLed[1] = 0b01000001;
    MatrixLed[2] = 0b11111111;
    MatrixLed[3] = 0b00000001;
    MatrixLed[4] = 0;
    /*MatrixLed[5] =  0b00100000;
    MatrixLed[6] =  0b00100000;
    MatrixLed[7] =  0b00100000;*/
    if(subindo){                                //seta apontando pra cima
        destinoSub = destinoSub & 0b11111101;   //limpa a flag que mantem o andar 3 como destino do elevador
        mov = EmTrajeto;
    }else{                                      //seta apontando pra baixo
        destinoDesc = destinoDesc & 0b11111101; //limpa a flag que mantem o andar 1 como destino do elevador
        
        //Controle dos estados
        if(destinoDesc == 0){
            mov = RetornaS0;
        }
    }

    alteraSentido();
    /*MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;*/
    apagaFlag();
    matrixUpdate();
}

/**
 * Funcao que trata a interrupcao do sensor S3
 * @param void
 * @return void
*/
void chegadaS3(){
    //Atualização da variavel da matrix de de Dados com o numero 2 mais a direcao de movimento do elevador
    motor = 0;
    andarAtual = 2;
    
   //Caso o Andar 3 seja um ponto de Parada reinicia o TRM1 que controla o tempo de espera do elevador
    if((((destinoSub & 0b00000100) == 4 )&& subindo)||(!subindo &&((destinoDesc & 0b00000100) == 4 )) ){ 
        PWM3_LoadDutyValue(0);//Desligando o Movimento do Motor
        TMR4_WriteTimer(0);
        TMR4_StartTimer();
    }
    
    //Atualização da variavel da matrix de de Dados com o numero 2 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b01000011;
    MatrixLed[1] = 0b10000101; 
    MatrixLed[2] = 0b10001001; 
    MatrixLed[3] = 0b01110001; 
    MatrixLed[4] = 0;
    /*MatrixLed[5] =  0b00100000;
    MatrixLed[6] =  0b00100000;
    MatrixLed[7] =  0b00100000;*/
    if(subindo){                                //seta apontando pra cima
        destinoSub = destinoSub & 0b11111011;   //limpa a flag que mantem o andar 3 como destino do elevador
    }else{                                      //seta apontando pra baixo
        destinoDesc = destinoDesc & 0b11111011; //limpa a flag que mantem o andar 2 como destino do elevador
    }
    /*MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;*/
    apagaFlag();
    matrixUpdate();
    
    //Controle dos estados
    alteraSentido();
}

/**
 * Funcao que trata a interrupcao do sensor S4
 * @param void
 * @return void
*/
void chegadaS4(){
    //Atualizacao da variavel da matrix de de Dados com o numero 3 mais a direcao de movimento do elevador
    motor = 0;
    andarAtual = 3;
    pulsoEncoder = 120;
    
    //Caso o Andar 3 seja um ponto de Parada reinicia o TRM1 que controla o tempo de espera do elevador
    if((((destinoSub & 0b00001000) == 8 )&& subindo)||(!subindo &&((destinoDesc & 0b00001000) == 8 )) ){ 
        PWM3_LoadDutyValue(0);//Desligando o Movimento do Motor
        TMR4_WriteTimer(0);
        TMR4_StartTimer();
    }
    
    //Atualizacao da variavel da matrix de de Dados com o numero 3 mais a direcao de movimento do elevador
    MatrixLed[0] = 0b10000001;
    MatrixLed[1] = 0b10010001;
    MatrixLed[2] = 0b10010001;
    MatrixLed[3] = 0b01101110;
    MatrixLed[4] = 0;
    /*MatrixLed[5] =  0b00100000;
    MatrixLed[6] =  0b00100000;
    MatrixLed[7] =  0b00100000;*/
    if(subindo){                                //seta apontando pra cima
        destinoSub = destinoSub & 0b11110111;   //limpa a flag que mantem o andar 3 como destino do elevador
    }else{                                      //seta apontando pra baixo
        destinoDesc = destinoDesc & 0b11110111; //limpa a flag que mantem o andar 2 como destino do elevador
    }
    /*MatrixLed[7] = MatrixLed[7] | destinoSub;
    MatrixLed[6] = MatrixLed[6] | destinoDesc;*/
    apagaFlag();
    matrixUpdate();
    
    //Controle dos estados
    alteraSentido();
    if(destinoSub != 0 ){
        destinoSub = 0;
    }
}

/**
 * Funcao principal
*/
void main(void)
{
    SYSTEM_Initialize();
    
    //Handlers das Interrupcoes
    /* Caso a Interrupcao nao tenha handler,
     * a funcao esta sendo chamada dentro da funcao de interrupcao do periferico
     */
    IOCBF0_SetInterruptHandler(chegadaS1);
    IOCBF3_SetInterruptHandler(chegadaS2);
    TMR4_SetInterruptHandler(controleMovimento);
    TMR0_SetInterruptHandler(sendInfo);
    CCP4_SetCallBack(interrupcaoCCP4);
    
    //Incializacao do SPI
    CS_SetHigh();                   //Mantem Desativado o CS
    SPI1_Open(SPI1_DEFAULT);        // Configura MSSP1
    initMatrix();                   // Configura matrizes

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    chegadaS1();
    while (1)
    {
        // Add your application code
        if(EUSART_is_rx_ready()){
            rxValue = EUSART_Read();
            if(rxValue == '$') state = START;
            switch(state){
                case START:
                    if(rxValue == '$'){
                        state = FIRST_NUM;
                    }
                    break;
                case FIRST_NUM:
                    if(isValidFloor(rxValue)){
                        oTemp = rxValue - 0x30;
                        state = SECOND_NUM;
                    }else{
                        state = START;
                    }
                    break;
                case SECOND_NUM:
                    if(isValidFloor(rxValue)){
                        dTemp = rxValue - 0x30;
                        state = CR;
                    }else{
                        state = START;
                    }
                    break;
                case CR:
                    if(rxValue == 0x0D){
                        origem = oTemp;
                        destino = dTemp;
                        // Chamar alguma funcao
                        organizaTrajeto();
                        contComandos++; //incrementa o contador de comandos eviados ao micro max 5
                    }
                    state = START;
                    break;
                default:
                    state = START;
            }
        }
    }
}