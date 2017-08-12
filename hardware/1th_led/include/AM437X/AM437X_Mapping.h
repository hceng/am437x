
#ifndef  AM437X_MAPPING_H__
#define  AM437X_MAPPING_H__
//#include  "AM437X_Mapping.h"

/*gpio寄存器基地址；*/

#define GPIO0_BASE            0x44E07000    //P140
#define GPIO1_BASE            0x4804C000    //P143
#define GPIO2_BASE            0x481AC000    //P144
#define GPIO3_BASE            0x481AE000    //P144
#define GPIO4_BASE            0x48320000    //P146
#define GPIO5_BASE            0x48322000    //P146

/**/
#define UART0_BASE            0x44E09000


/*ADC寄存器基地址； P139_146*/
/*注：这里的ADC0_BASE和ADC0_DMA_BASE、ADC1_BASE和ADC1_DMA_BASE在手册上的名字是一样的*/
#define ADC0_BASE            0x44E0D000   //P140
#define ADC0_DMA_BASE        0x54C00000   //P139
#define ADC1_BASE            0x4834C000   //P146
#define ADC1_DMA_BASE        0x54800000   //P139

/*DMTIMER相关寄存器基地址； P140-146*/
#define DMTIMER0_BASE        0x48E05000  //140
#define DMTIMER1_1MS_BASE    0x44E31000  //141
#define DMTIMER2_BASE        0x48040000  //P142
#define DMTIMER3_BASE        0x48042000
#define DMTIMER4_BASE        0x48044000
#define DMTIMER5_BASE        0x48046000
#define DMTIMER6_BASE        0x48048000
#define DMTIMER7_BASE        0x4804A000
#define DMTIMER8_BASE        0x481C1000  //P144
#define DMTIMER9_BASE        0x4833D000  //P146
#define DMTIMER10_BASE       0x4833F000
#define DMTIMER11_BASE       0x48341000
/*RTC Registers基地址； P141*/
#define RTCSS_BASE 			 0x44E3E000 
/*WDT1 Registers基地址； P141*/
#define WDT1_BASE            0x44E35000
/*SyncTimer Registers基地址； P141*/
#define SYNCTIMER_BASE       0x44E86000

/*INTC相关寄存器基地址； P145*/
#define DISTRIBUTOR_BASE     0x48241000   //MPU_INT_DIST  MPU Interrupt Distributor
#define CPU_INTERFACE_BASE   0x48240100   //MPU_INTC      MPU Interrupt Controller Interfaces

/*I2C相关寄存器基地址； P142、144*/
#define I2C1_BASE            0x4802A000  //P142
#define I2C2_BASE            0x4819C000  //P144

/*McSPI相关寄存器基地址； P142、144*/
#define MCSPI0_BASE          0x48030000  //P142
#define MCSPI1_BASE          0x481A0000  //P144
#define MCSPI2_BASE          0x481A2000  
#define MCSPI3_BASE          0x481A4000  
#define MCSPI4_BASE          0x48345000  

/*QSPI相关寄存器基地址； P138*/
#define QSPI1_BASE           0x30000000  //P138
#define QSPI2_BASE           0x47900000  

/*PRCM_CM相关寄存器基地址； P140*/
#define CM_CEFUSE_BASE       0x44DF8700  //P140
#define CM_DEVICE_BASE       0x44DF4100  
#define CM_DPLL_BASE         0x44DF4200  
#define CM_GFX_BASE          0x44DF8400  
#define CM_MPU_BASE          0x44DF8300  
#define CM_PER_BASE          0x44DF8800  
#define CM_RTC_BASE          0x44DF8500  
#define CM_WKUP_BASE         0x44DF2800  

#define PRM_CEFUSE_BASE      0x44DF0700
#define PRM_DEVICE_BASE      0x44DF4000
#define PRM_GFX_BASE         0x44DF0400
#define PRM_MPU_BASE         0x44DF0300
#define PRM_PER_BASE         0x44DF0800

/*Control Module相关寄存器基地址； P141*/
#define CONTROL_MODULE_BASE  0x44E10000  //P141

/*PWM Module相关寄存器基地址； P145*/
#define PWMSS0_BASE          0x48300000  //P145
//#define PWMSS0_ECAP_BASE     0x48300100  //P145
//#define PWMSS0_EQEP_BASE     0x48300180  //P145
//#define PWMSS0_EPWM_BASE     0x48300200  //P145

#define PWMSS1_BASE          0x48302000  //P145
//#define PWMSS1_ECAP_BASE     0x48302100  //P145
//#define PWMSS1_EQEP_BASE     0x48302180  //P145
//#define PWMSS1_EPWM_BASE     0x48302200  //P145

#define PWMSS2_BASE          0x48304000  //P145
//#define PWMSS2_ECAP_BASE     0x48304100  //P145
//#define PWMSS2_EQEP_BASE     0x48304180  //P145
//#define PWMSS2_EPWM_BASE     0x48304200  //P145

#define PWMSS3_BASE          0x48306000  //P145
//#define PWMSS3_EPWM_BASE     0x48306200  //P145

#define PWMSS4_BASE          0x48308000  //P145
//#define PWMSS4_EPWM_BASE     0x48308200  //P145

#define PWMSS5_BASE          0x4830A000  //P145
//#define PWMSS5_EPWM_BASE     0x4830A200  //P145



#endif

