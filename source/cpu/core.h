/*
 * File:		core.h
 * Purpose:		Definitions common to all ARM Cortex M4 processors
 *
 * Notes:
 */

#ifndef __CORE_H__
#define __CORE_H__
/******************************************************************************/

// function prototypes for arm_cm4.c
void stop(void);
void wait(void);
void write_vtor(int);

/******************************************************************************/
  /*!< Macro to enable all interrupts. */
#define EnableInterrupts    asm("CPSIE i");

  /*!< Macro to disable all interrupts. */
#define DisableInterrupts   asm("CPSID i");
/******************************************************************************/

/*
 * Misc. Defines
 */
#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	(1)

#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	(0)

#ifdef	NULL
#undef	NULL
#endif
#define NULL	(0)

#ifdef  ON
#undef  ON
#endif
#define ON      (1)

#ifdef  OFF
#undef  OFF
#endif
#define OFF     (0)

#ifdef  OK
#undef  OK
#endif
#define OK		(1)

#ifdef  ERROR
#undef  ERROR
#endif
#define ERROR	(0)

#define PI      (3.14159265359)

#define ABS(a)      ((a)>=0 ? (a) : (-(a)))
#define MAX(a,b )   ((a)>=(b) ? (a) : (b))
#define MIN(a,b )   ((a)<(b) ? (a) : (b))

#define CLR_BIT(reg,bit)        reg &= ~(1 << (bit))
#define SET_BIT(reg,bit)        reg |= (1 << (bit))
#define REV_BIT(reg,bit)        reg ^= (1 << (bit))
#define BIT_IS_HIGH(reg,bit)    (0 != ((reg) & (1 << (bit))))
#define BIT_IS_LOW(reg,bit)     (0 != ((reg) ^ (1 << (bit))))

/******************************************************************************/
/*
 * The basic data types
 */
typedef unsigned char	        uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */
typedef unsigned long long	uint64; /* 64 bits */

typedef signed char             int8;   /*  8 bits */
typedef signed short int        int16;  /* 16 bits */
typedef signed long int         int32;  /* 32 bits */
typedef signed long long        int64;  /* 64 bits */

typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
typedef volatile int32		vint32; /* 32 bits */
typedef volatile int64		vint64; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */
typedef volatile uint64		vuint64; /* 32 bits */

typedef uint8   INT8U;
typedef int8    INT8S;
typedef uint16  INT16U;
typedef int16   INT16S;
typedef uint32  INT32U;
typedef int32   INT32S;
typedef uint64  INT64U;
typedef int64   INT64S;


// function prototype for main function
void main(void);

/******************************************************************************/
#endif	/* __CORE_H__ */

