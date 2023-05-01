 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author: Sarah
 *
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG |= (1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG &= (~(1<<BIT)))

/*Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/*Rotate right the register value with specific number of rotates*/
#define ROR(REG,num) (REG= (REG>>num) | (REG<<(8-num)) )

/*Rotate left the register value with specific number of rotates*/
#define ROL(REG,num) (REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return 1 if yes */
#define BIT_IS_SET(REG,BIT)  (REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return 1 if yes*/
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)) )

/* Get specific bit with 1 or 0 */
#define GET_BIT(REG,BIT_NUM) ( ( REG & (1<<BIT_NUM) ) >> BIT_NUM )




#endif /* COMMON_MACROS_H_ */
