
#ifndef  __AM437X_INT_H__
#define   __AM437X_INT_H__

#define MPU_INTC      0x48240100
#define MPU_INT_DIST  0x48241000

/* ICD: Interrupt Controller Distributor */
#define ICDDCR       (*(volatile unsigned long *)(MPU_INT_DIST + 0x000))        /* Distributor Control Register */
#define ICDICTR      (*(volatile unsigned long *)(MPU_INT_DIST + 0x004))        /* Interrupt Controller Type Register */
#define ICDIIDR      (*(volatile unsigned long *)(MPU_INT_DIST + 0x008))        /* Distributor Implementer Identification Register */
#define ICDISR(n)    (*(volatile unsigned long *)(MPU_INT_DIST + 0x080 + 4*n))  /* Interrupt Security Registers */
#define ICDISER(n)   (*(volatile unsigned long *)(MPU_INT_DIST + 0x100 + 4*n))  /* Interrupt Set-Enable Registers */
#define ICDICER(n)   (*(volatile unsigned long *)(MPU_INT_DIST + 0x180 + 4*n))  /* Interrupt Clear-Enable Registers */
#define ICDISPR(n)   (*(volatile unsigned long *)(MPU_INT_DIST + 0x200 + 4*n))  /* Interrupt Set-Pending Registers */
#define ICDICPR(n)   (*(volatile unsigned long *)(MPU_INT_DIST + 0x280 + 4*n))  /* Interrupt Clear-Pending Registers */
#define ICDABR(n)    (*(volatile unsigned long *)(MPU_INT_DIST + 0x300 + 4*n))  /* Active Bit registers */
#define ICDIPR(n)    (*(volatile unsigned long *)(MPU_INT_DIST + 0x400 + 4*n))  /* Interrupt Priority Registers */
#define ICDIPTR(m, byte)   (*(volatile unsigned char *)(MPU_INT_DIST + 0x800 + 4*m + byte))  /* Interrupt Processor Targets Registers */
#define ICDICFR(n)   (*(volatile unsigned char *)(MPU_INT_DIST + 0xc00 + 4*n))  /* Interrupt Configuration Registers */


/* ICC: Interrupt Controller Communication */
#define ICCICR       (*(volatile unsigned long *)(MPU_INTC + 0x000)) /* CPU Interface Control Register */
#define ICCPMR       (*(volatile unsigned long *)(MPU_INTC + 0x004)) /* Interrupt Priority Mask Register */
#define ICCBPR       (*(volatile unsigned long *)(MPU_INTC + 0x008)) /* Binary Point Register */
#define ICCIAR       (*(volatile unsigned long *)(MPU_INTC + 0x00C)) /* Interrupt Acknowledge Register */
#define ICCEOIR      (*(volatile unsigned long *)(MPU_INTC + 0x010)) /* End Of Interrupt Register */
#define ICCRPR       (*(volatile unsigned long *)(MPU_INTC + 0x014)) /* Running Priority Register */
#define ICCHPIR      (*(volatile unsigned long *)(MPU_INTC + 0x018)) /* Highest Pending Interrupt Register */
#define ICCABPR      (*(volatile unsigned long *)(MPU_INTC + 0x01C)) /* Aliased Non-secure Binary Point Register */
#define ICCIDR       (*(volatile unsigned long *)(MPU_INTC + 0x0FC)) /* CPU Interface Implementer Identification Register */

/* irq number */
#define IRQ_TIMER2   100

#define  GPIOINT5A   180
#define  GPIOINT5B   181	 

#endif /* __AM437X_INT_H__ */

