/*
//DA 输出的电压 公式
//2*V参考电压*（DA/1024）
//实验板上电源电压是3.3V ,参考电压是1.65V
// 512的时候 ，输出是参考电压 1.65V
//
*/
#include <msp430x14x.h>

#define  DIN_High   P3OUT|=BIT1        //高电平     P31   
#define  DIN_Low    P3OUT&=~BIT1       //低电平    5615 数据IO

#define  CS_High    P2OUT|=BIT5        //高电平           
#define  CS_Low     P2OUT&=~BIT5       //低电平   片选低电平有效 

#define  SCLK_High   P3OUT|=BIT3;      // 高电平  时钟信号
#define  SCLK_Low    P3OUT&=~BIT3;     // 低电平    P33



void DA_10Bit(unsigned int DA_10)
{
   unsigned char i;
   
   DA_10<<=6;               // 数据向高位移位
   SCLK_Low;                
   CS_High;
   SCLK_High;
   SCLK_Low;
   
   CS_Low;
   for(i=0;i<12;i++)
   {
      SCLK_Low;
      if(DA_10&0x8000)
         DIN_High;
      else
         DIN_Low;
      
      SCLK_High;
      DA_10<<=1;
      
   }
   CS_High;  

}


void main()
{
  
  WDTCTL = WDTPW + WDTHOLD;          // Stop watchdog
  

  P3DIR|=BIT1+BIT3;
  P2DIR|=BIT5;                       // IO初始化
 
  DA_10Bit(1023);                     //
  
  while(1);
}
