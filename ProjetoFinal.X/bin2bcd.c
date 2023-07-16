/*
 * File:   bin2bcd.c
 * Author: Guillermo
 *
 * Created on 11 de Outubro de 2021, 23:16
 */

#include "bin2bcd.h"

uint16_t bin2bcd(uint16_t binVal){
    union{
        uint32_t shift;         ///< Para dislocar os dados
        struct{
            uint8_t     :8;     ///< Valor bin?rio de entrada (bits 7-0)
            uint8_t     :4;     ///< Valor bin?rio de entrada (bits 11-8)
            uint8_t d3  :4;     ///< D?gito 0 (LSB)
            uint8_t d2  :4;     ///< D?gito 1
            uint8_t d1  :4;     ///< D?gito 2
            uint8_t d0  :4;     ///< D?gito 3 (MSB)
            uint8_t     :4;     ///< Bits n?o usados
        }dat;
    }dataU;
    memset(&dataU,0,4);  // Zera data
    dataU.shift = (uint32_t)binVal;
    for(uint8_t i=0;i<12;i++){  // Quantidades de rodadas igual ao tamanho de dataU.dat.bin
			if(dataU.dat.d0>=5){
				dataU.dat.d0 = dataU.dat.d0 + 3;
			}
			if(dataU.dat.d1>=5){
				dataU.dat.d1 = dataU.dat.d1 + 3;
			}
            if(dataU.dat.d2>=5){
				dataU.dat.d2 = dataU.dat.d2 + 3;
			}
            if(dataU.dat.d3>=5){
				dataU.dat.d3 = dataU.dat.d3 + 3;
			}
			dataU.shift = dataU.shift<<1; // Desloca dataU.shift para a esquerda uma posi??o
    }
    return (uint16_t)(dataU.shift>>12);
}


