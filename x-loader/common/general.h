/* ============================================================================
*                       MultiMedia Solutions
*   (c) Copyright 2009, MultiMedia Solutions  All Rights Reserved.
*
*   Use of this software is controlled by the terms and conditions found
*   in the license agreement under which this software has been supplied.
* =========================================================================== */
/**
*  @file  general.h
*
*  Common macros, constants and type definitions
*
*  @author  Pavel Nedev
*
*  @date  17/11/2009
*
*  @version  1.00
*/
/* ========================================================================== */

#ifndef _GENERAL_H
#define _GENERAL_H

/******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/

/******************************************************************************
 * 32-bit signed integer types
 ******************************************************************************/
// typedef signed int      s32;
typedef volatile s32    vs32;

/******************************************************************************
 * 32-bit unsigned integer types
 ******************************************************************************/
// typedef unsigned int    u32;
typedef volatile u32    vu32;

/******************************************************************************
 * 16-bit signed integer types
 ******************************************************************************/
// typedef signed short    s16;
typedef volatile s16    vs16;

/******************************************************************************
 * 16-bit unsigned integer types
 ******************************************************************************/
// typedef unsigned short    u16;
typedef volatile u16      vu16;

/******************************************************************************
 * 8-bit signed integer types
 ******************************************************************************/
// typedef signed char    s8;
typedef volatile s8    vs8;

/******************************************************************************
 * 8-bit unsigned integer types
 ******************************************************************************/
// typedef unsigned char    u8;
typedef volatile u8      vu8;



/******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#ifndef NULL
#define NULL    (void*)0
#endif



/******************************************************************************
 * VARIABLE OPERATION MACROS
 ******************************************************************************/
/* ========================================================================== */
/**
*  @def  RD_FIELD    macro_description
*/
/* ========================================================================== */
#define RD_FIELD(var, pos, mask)    ((var & (mask)) >> (pos))

/* ========================================================================== */
/**
*  @def  WR_FIELD    macro_description
*/
/* ========================================================================== */
#define WR_FIELD(var, pos, mask, val) \
                                    var = (var & ~(mask)) | ((val) << (pos))



/******************************************************************************
 * OTHER MACROS
 ******************************************************************************/
/* ========================================================================== */
/**
*  @def  MIN    macro_description
*/
/* ========================================================================== */
#define MIN(x, y)    (((x) < (y)) ? (x) : (y))

/* ========================================================================== */
/**
*  @def  MAX    macro_description
*/
/* ========================================================================== */
#define MAX(x, y)    (((x) > (y)) ? (x) : (y))

/* ========================================================================== */
/**
*  @def  CEIL    macro_description
*/
/* ========================================================================== */
#define CEIL(x, y)    ((((x) % (y)) == 0) ? ((x) / (y)) : (((x) / (y)) + 1))

#endif /* _GENERAL_H */
