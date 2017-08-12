#include <stdarg.h>
#include <stdio.h>

#if  0
typedef char* va_list; /*va_listä»£è¡¨æŒ‡å‘å­—ç¬¦çš„æŒ‡é’ˆ */
#define _INTSIZEOF(n)   ((sizeo(n)+sizeof(int)-1) &~(sizeof(int)-1))
#define va_start(ap,v)  (ap=(va_list)&v + _INTSIZEOF(v)) 
#define va_arg(ap, t)   (*(t*) ((ap+=_INTSIZEOF(t)) - _INTSIZEOF(t)))   
#define va_end(ap)      (ap=(va_list )0)	
#endif

#if  0
typedef char* va_list; /*va_listä»£è¡¨æŒ‡å‘å­—ç¬¦çš„æŒ‡é’ˆ */
#define _INTSIZEOF(n)   ((sizeo(n)+sizeof(int)-1) &~(sizeof(int)-1))

#define va_start(ap,v)  (ap=(va_list)&v + _INTSIZEOF(v)) 
#define va_end(ap)      (ap=(va_list )0)	

void * va_arg(va_list ap, (void *)t) 
{
//  (*(t*) ((ap+=_INTSIZEOF(t)) - _INTSIZEOF(t))) ;  
	ap+=_INTSIZEOF(t) ;
 return (*(t*))( ap - _INTSIZEOF(t));
}
#endif

#define  __BSP_output_char  uart_PutChar
//#define  __BSP_output_char  Uart_SendChar

extern void  uart_PutChar(unsigned char  c);
//hex_tab±ØĞëÊÇchar£¬²»ÄÜÊÇunsigned char·ñÔò»á´òÓ¡³ö´í
char hex_tab[]={'0','1','2','3','4','5','6','7',\
		        '8','9','A','B','C','D','E','F'};

//first  arg  may error:long unsigned int 
static  unsigned char 
printNum(long  int   num, int base, int sign, int maxwidth, int lead)
//printNum(long unsigned int   num, int base, int sign, int maxwidth, int lead)
{
		//long unsigned int n;
		long  int n;
		int count;
		unsigned char toPrint[64];//#define  MAX_PRINT_NUM  64
		//æ³¨æ„ï¼šä» char toPrint--->unsigned char toPrintï¼Œå¯ä»¥é˜²æ­¢
		//warning: array subscript has type `char'
		
		if((sign == 1) && ((long)num < 0)){
			__BSP_output_char('-');
			num = -num;
			if(maxwidth)maxwidth--;
		}
	
		count=0;
		while( (n=num/base)>0){
				toPrint[count++] = (num - (n * base));
				num = n;
		}
		toPrint[count++] = num;
		
		if(maxwidth && count < maxwidth){
			for (n=maxwidth - count; n; n--)	
				__BSP_output_char(lead);
		}
		//æ‰“å°
		for(n=0; n<count; n++)
			//__BSP_output_char("0123456789ABCDEF"[(int)(toPrint[count - (n+1)])]);
	      __BSP_output_char(  hex_tab[toPrint[count - (n+1)]]  );
		  
		return 0;
}

void  _100ask_printf(char *fmt,...)
{
	 va_list  ap; /*points to each unnamed argument in turn*/
	 char  c,*str;
	 int  lflag,base,sign,width,lead;
	 
	 va_start(ap,fmt);/*make ap point to 1st unnamed arg*/
	 for(; *fmt != '\0'; fmt++)
	 {
	 		lflag=0; base=0; sign=0; width=0;lead=' ';
	 		if(*fmt == '%'){
	 				fmt++;
	 				if(*fmt == '0'){
	 					lead ='0';
	 					fmt++;	
	 				}	
	 			  
	 			  while(*fmt >= '0' && *fmt <= '9'){
	 			  		width *=10;
	 			  	  width += (*fmt - '0');
	 			  	  fmt ++;
	 			  }
	 			  
	 			  if((c=*fmt)=='l'){
	 			  		lflag=1;
	 			  		c = *++fmt;	 			  	
	 			  }
	 			  
	 			  switch(c)
	 			  {
	 			      case 'b':	case 'B':base =  2; sign =0; break;
	 			  	  case 'o':	case 'O':base =  8; sign =0; break;
	 			  	  case 'd':	case 'D':base = 10; sign =1; break;
	 			  	  case 'u':	case 'U':base = 10; sign =0; break;
	 			  	  case 'x':	case 'X':base = 16; sign =0; break;
	 			  	  case 's':for(str = va_arg(ap,char*);*str;str++)
	 			  	  					  __BSP_output_char(*str);
	 			  	  					  break;
	 			  	  //case 'c':__BSP_output_char(va_arg(ap,char));
	 			  	  case 'c':__BSP_output_char(va_arg(ap,int));
	 			  	  					  break;
	 			  	  default:__BSP_output_char(c);
	 			  	  		    break;
	 			  }//swtich
	 			  
	 			  if(base){
	 			  		printNum(lflag ? (long int)va_arg(ap,long int):(long int)va_arg(ap,int),\
	 			  							base,sign,width,lead);	 			  	
	 			  }
	 		}//if
	 		else
	 		{
	 				__BSP_output_char(*fmt);		
	 		}
	 	  
	 }	
	 va_end(ap);	 	
	
}
#if  0
// Replacement (=dummy) for GNU/Linux division-by zero handler 
void __div0 (void)
{
    extern void hang (void);

//  hang();
}

/* add functions to be compiled by CodeSourcery Toolchain */
void __aeabi_ldiv0 (void)
{
    extern void hang (void);

 //  hang();
 }

#endif

void raise(void) 
{
}



int  _100ask_printf_test(void)
{
   char  c_num='h';   
   int i=5;
   

   _100ask_printf("%ld\r\n",-12345678);
   _100ask_printf("%ld\r\n",12345678);
   _100ask_printf("%08x\r\n",0x15);
   _100ask_printf("%d,%d\r\n",15,16);
//   _100ask_printf("c_num=%c,i=%d,%s\r\n",c_num,i,"hello");
   //_100ask_printf("%0x\r\n",0x15);
#if  1	
  // _100ask_printf("%s\r\n","hello");
   _100ask_printf("c_num=%c\r\n",c_num);
   _100ask_printf("c_num=%c,i=%d\r\n",c_num,i);
   _100ask_printf("c_num=%c,i=%d,%s\r\n",c_num,i,"hello");
   _100ask_printf("c_num=%c,i=%d,%s,%x\r\n",c_num,i,"hello",0x1234);
#endif
	return 0;
}




