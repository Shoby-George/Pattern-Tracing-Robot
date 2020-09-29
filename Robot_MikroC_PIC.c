#include "built_in.h"

#define on 1;
#define off 0;

sbit RIGHT_WHEEL at LATD1_bit;
sbit LEFT_WHEEL at LATD3_bit;

char uart_rd;
char direction_rd[20];
unsigned char i, j;
void forward();
void left();
void right();
void right45();
void left45();
void right135();
void left135();
void reverse();

int FORWARD_TIME = 2000;
int LEFT_TIME = 500;
int RIGHT_TIME = 500;
int STOP_TIME = 100;
int LEFT45_TIME = 250;
int RIGHT45_TIME = 250;
int LEFT135_TIME = 750;
int RIGHT135_TIME = 750;
int REVERSE_TIME = 1000;

void main() {

  TRISD0_bit = 0;                       //Make RD0(pin 19) & RD1(pin 20) as o/p
  TRISD1_bit = 0;
  LATD0_bit = 0;                        //Output 0V to RD0 & RD1
  LATD1_bit = 0;

  TRISD2_bit = 0;                       //Make RD2(pin 21) & RD3(pin 22) as o/p
  TRISD3_bit = 0;
  LATD2_bit = 0;                        //Output 0V to RD2 & RD3
  LATD3_bit = 0;

  UART1_Init(9600);                     // Initialize UART module at 9600 bps
  Delay_ms(100);                        // Wait for UART module to stabilize

  UART1_Write_Text("READY");            //Write READY

  while (1) {                           // Endless loop
    if(UART1_Data_Ready()){
      uart_rd = UART1_Read();           // Read the received data
      if(uart_rd == 0x53){              //If 'S', start storing data to direction_rd array
        i = 0;
        while(1){
          if(UART1_Data_Ready()){
            uart_rd = UART1_Read();     //Read data
            if(uart_rd != 0x58){        //If data received is not 'X',
              direction_rd[i] = uart_rd;//store data received to direction_rd array,
              i++;
            }else{
              break;                    //else stop storing data
            }
          }
        }
        for(j = 0;j < i;j++){           //Access each element of direction_rd array
          if(direction_rd[j] == 0x66){        //If 'f'
            forward();
          }else if(direction_rd[j] == 0x72){  //If 'r'
            right();
            forward();
          }else if(direction_rd[j] == 0x6C){  //If 'l'
            left();
            forward();
          }else if(direction_rd[j] == 0x61){  //If 'a'
            reverse();
            forward();
          }else if(direction_rd[j] == 0x62){  //If 'b'
            right45();
            forward();
          }else if(direction_rd[j] == 0x63){  //If 'c'
            right135();
            forward();
          }else if(direction_rd[j] == 0x64){  //If 'd'
            left45();
            forward();
          }else if(direction_rd[j] == 0x65){  //If 'e'
            left135();
            forward();
          }
        }
      }
    }
  }
}

void forward(){
     RIGHT_WHEEL = on;
     LEFT_WHEEL = on;
     Vdelay_ms(FORWARD_TIME);
     RIGHT_WHEEL = off;
     LEFT_WHEEL = off;
     Vdelay_ms(STOP_TIME);
}

void left(){
     RIGHT_WHEEL = on;
     Vdelay_ms(LEFT_TIME);
     RIGHT_WHEEL = off;
}

void right(){
     LEFT_WHEEL = on;
     Vdelay_ms(RIGHT_TIME);
     LEFT_WHEEL = off;
}

void right45(){
     LEFT_WHEEL = on;
     Vdelay_ms(RIGHT45_TIME);
     LEFT_WHEEL = off;
}

void left45(){
     RIGHT_WHEEL = on;
     Vdelay_ms(LEFT45_TIME);
     RIGHT_WHEEL = off;
}

void right135(){
     LEFT_WHEEL = on;
     Vdelay_ms(RIGHT135_TIME);
     LEFT_WHEEL = off;
}

void left135(){
     RIGHT_WHEEL = on;
     Vdelay_ms(LEFT135_TIME);
     RIGHT_WHEEL = off;
}

void reverse(){
     RIGHT_WHEEL = on;
     Vdelay_ms(REVERSE_TIME);
     RIGHT_WHEEL = off;
}
