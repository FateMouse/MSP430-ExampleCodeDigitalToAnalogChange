/*
//DA ����ĵ�ѹ ��ʽ
//2*V�ο���ѹ*��DA/1024��
//ʵ����ϵ�Դ��ѹ��3.3V ,�ο���ѹ��1.65V
// 512��ʱ�� ������ǲο���ѹ 1.65V
//
*/
#include <msp430x14x.h>

#define  DIN_High   P3OUT|=BIT1        //�ߵ�ƽ     P31   
#define  DIN_Low    P3OUT&=~BIT1       //�͵�ƽ    5615 ����IO

#define  CS_High    P2OUT|=BIT5        //�ߵ�ƽ           
#define  CS_Low     P2OUT&=~BIT5       //�͵�ƽ   Ƭѡ�͵�ƽ��Ч 

#define  SCLK_High   P3OUT|=BIT3;      // �ߵ�ƽ  ʱ���ź�
#define  SCLK_Low    P3OUT&=~BIT3;     // �͵�ƽ    P33



void DA_10Bit(unsigned int DA_10)
{
   unsigned char i;
   
   DA_10<<=6;               // �������λ��λ
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
  P2DIR|=BIT5;                       // IO��ʼ��
 
  DA_10Bit(1023);                     //
  
  while(1);
}
