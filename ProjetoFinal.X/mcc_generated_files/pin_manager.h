/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1827
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set S3 aliases
#define S3_TRIS                 TRISAbits.TRISA0
#define S3_LAT                  LATAbits.LATA0
#define S3_PORT                 PORTAbits.RA0
#define S3_ANS                  ANSELAbits.ANSA0
#define S3_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define S3_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define S3_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define S3_GetValue()           PORTAbits.RA0
#define S3_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define S3_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define S3_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define S3_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set RA1 procedures
#define RA1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define RA1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define RA1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define RA1_GetValue()              PORTAbits.RA1
#define RA1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define RA1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define RA1_SetAnalogMode()         do { ANSELAbits.ANSA1 = 1; } while(0)
#define RA1_SetDigitalMode()        do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set Temp aliases
#define Temp_TRIS                 TRISAbits.TRISA2
#define Temp_LAT                  LATAbits.LATA2
#define Temp_PORT                 PORTAbits.RA2
#define Temp_ANS                  ANSELAbits.ANSA2
#define Temp_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Temp_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Temp_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Temp_GetValue()           PORTAbits.RA2
#define Temp_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Temp_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Temp_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Temp_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA3 procedures
#define RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RA3_GetValue()              PORTAbits.RA3
#define RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RA3_SetAnalogMode()         do { ANSELAbits.ANSA3 = 1; } while(0)
#define RA3_SetDigitalMode()        do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set Enc aliases
#define Enc_TRIS                 TRISAbits.TRISA4
#define Enc_LAT                  LATAbits.LATA4
#define Enc_PORT                 PORTAbits.RA4
#define Enc_ANS                  ANSELAbits.ANSA4
#define Enc_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Enc_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Enc_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Enc_GetValue()           PORTAbits.RA4
#define Enc_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Enc_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Enc_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define Enc_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RA6 procedures
#define RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define RA6_GetValue()              PORTAbits.RA6
#define RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set Dir aliases
#define Dir_TRIS                 TRISAbits.TRISA7
#define Dir_LAT                  LATAbits.LATA7
#define Dir_PORT                 PORTAbits.RA7
#define Dir_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define Dir_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define Dir_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define Dir_GetValue()           PORTAbits.RA7
#define Dir_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define Dir_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set S1 aliases
#define S1_TRIS                 TRISBbits.TRISB0
#define S1_LAT                  LATBbits.LATB0
#define S1_PORT                 PORTBbits.RB0
#define S1_WPU                  WPUBbits.WPUB0
#define S1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define S1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define S1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define S1_GetValue()           PORTBbits.RB0
#define S1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define S1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define S1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define S1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)

// get/set CS aliases
#define CS_TRIS                 TRISBbits.TRISB1
#define CS_LAT                  LATBbits.LATB1
#define CS_PORT                 PORTBbits.RB1
#define CS_WPU                  WPUBbits.WPUB1
#define CS_ANS                  ANSELBbits.ANSB1
#define CS_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define CS_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define CS_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define CS_GetValue()           PORTBbits.RB1
#define CS_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define CS_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define CS_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define CS_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define CS_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set S2 aliases
#define S2_TRIS                 TRISBbits.TRISB3
#define S2_LAT                  LATBbits.LATB3
#define S2_PORT                 PORTBbits.RB3
#define S2_WPU                  WPUBbits.WPUB3
#define S2_ANS                  ANSELBbits.ANSB3
#define S2_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define S2_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define S2_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define S2_GetValue()           PORTBbits.RB3
#define S2_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define S2_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define S2_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define S2_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define S2_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define S2_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF0 pin functionality
 * @Example
    IOCBF0_ISR();
 */
void IOCBF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF0_SetInterruptHandler() method.
    This handler is called every time the IOCBF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF0_SetInterruptHandler(IOCBF0_InterruptHandler);

*/
extern void (*IOCBF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF0_SetInterruptHandler() method.
    This handler is called every time the IOCBF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF0_SetInterruptHandler(IOCBF0_DefaultInterruptHandler);

*/
void IOCBF0_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF3 pin functionality
 * @Example
    IOCBF3_ISR();
 */
void IOCBF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_InterruptHandler);

*/
extern void (*IOCBF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_DefaultInterruptHandler);

*/
void IOCBF3_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/