/* 
 * File:   bin2bcd.h
 * Author: Guillermo
 *
 * Created on 11 de Outubro de 2021, 23:17
 */

#ifndef BIN2BCD_H
#define	BIN2BCD_H

#include <string.h>
#include <stdint.h>
#include "bin2bcd.h"

 /**
 * Converte un valor Binario de 12 bits para BCD (16 bits)
 * @param binVal Valor bin?rio  ser convertido em BCD.
 * @return Valor BCD retornado.
 */
uint16_t bin2bcd(uint16_t binVal);


#endif	/* BIN2BCD_H */

