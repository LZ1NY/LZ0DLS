#include <DigitalToggle.h>

#include <Wire.h>
#include <avr/interrupt.h>  
#include <avr/io.h>

#include <SoftwareSerial.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 


#define MAX_STRING_LEN  100

#define ledPin 2
#define CWPin  2
#define speaker 3

#define rxPin 4
#define txPin 5

#define fixPin 6
#define controlPin 7

#define si570_address 0x55 

SoftwareSerial gps =  SoftwareSerial(rxPin, txPin);
byte pinState = 0;



byte cnt=0;
unsigned int cnt_pause=0;
byte symbol=0;
byte *ptr;
byte x = 0;
boolean send_wspr;
boolean send_next_wspr;
boolean pause;
boolean send_cw;
boolean wait_sync;
int one_tit=60;
char  time[9];
char *ptime=time;
boolean start_stop;
#define charA 1,2,0,
#define charB 2,1,1,1,0,
#define charC 2,1,2,1,0,
#define charD 2,1,1,0,
#define charE 1,0,

#define charK 2,1,2,0,
#define charL 1,2,1,1,0,
#define charN 2,1,0,
#define charO 2,2,2,0,
#define charP 1,2,2,1,0,
#define charQ 2,2,1,2,0,
#define charR 1,2,1,0,
#define charS 1,1,1,0,
#define charW 1,2,2,0,
#define charZ 2,2,1,1,0,

#define char0 2,2,2,2,2,0,
#define char1 1,2,2,2,2,0,
#define char2 1,1,2,2,2,0,
#define char6 2,1,1,1,1,0,

 char cw_id_string[] = {charL charZ char0 charD charL charS 6,charW charS charP charR 6, charB charE charA charC charO charN 6, charK charN char1 char2 charP charQ 6, char6 char0 char0 charA charS charL 100};


//***************************************************************************************
      
// LZ0DLS KN12 37
/* 
 byte message[] ={
 3, 3, 0, 0, 2, 2, 0, 2,  1, 2, 0, 0, 3, 3, 1, 2, 2, 0, 3, 0, 0, 3, 0, 3, 3, 1, 1, 2, 2, 0,\
 0, 0, 2, 0, 3, 2, 2, 1, 2, 3, 2, 2, 2, 0, 2, 2, 1, 2, 3, 3, 0, 0, 3, 3, 0, 1, 0, 2, 2, 3,\
 3, 2, 3, 2, 0, 0, 0, 3, 3, 0, 1, 0, 1, 0, 3, 2, 1, 2, 0, 1, 2, 2, 1, 0, 1, 3, 0, 0, 0, 3,\
 3, 2, 3, 2, 3, 2, 2, 0, 3, 2, 0, 2, 0, 0, 3, 0, 2, 1, 0, 2, 1, 1, 3, 0, 1, 1, 0, 0, 1, 1,\
 2, 1, 2, 0, 2, 1, 1, 3, 2, 0, 0, 2, 2, 1, 0, 1, 2, 0, 3, 3, 0, 2, 0, 2, 2, 2, 0, 3, 1, 0,\
 3, 2, 1, 1, 2, 0, 0, 1, 3, 2, 0, 0                  };
 */

// LZ1NY KN12 10
/*
byte message[] ={
  3, 3, 2, 0, 0, 0, 2, 0, 1, 2, 2, 0, 3, 3, 3, 0, 2, 2, 1, 2, 2, 1, 0, 3, 1, 3, 3, 2, 0, 2,\
      0, 2, 2, 2, 3, 2, 2, 1, 2, 1, 2, 0, 0, 2, 2, 0, 1, 0, 3, 3, 2, 0, 3, 3, 2, 3, 0, 2, 0, 3,\
      3, 2, 3, 0, 0, 2, 0, 1, 1, 0, 3, 2, 1, 0, 3, 2, 1, 2, 0, 1, 2, 2, 1, 2, 1, 1, 2, 0, 2, 1,\
      3, 2, 3, 2, 1, 2, 2, 0, 3, 0, 2, 2, 2, 0, 3, 0, 0, 1, 2, 0, 3, 3, 3, 2, 3, 1, 2, 2, 1, 3,\
      0, 1, 0, 2, 2, 1, 3, 1, 2, 2, 2, 2, 0, 1, 0, 3, 2, 0, 1, 1, 2, 0, 0, 2, 2, 2, 2, 1, 1, 2,\
      1, 0, 3, 1, 0, 0, 2, 3, 1, 2, 0, 0 };

 */      
      
      
      
// LZ0DLS KN12 10
 byte message[] ={  
     3, 3, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 1, 1, 0, 2, 0, 3, 2, 0, 1, 0, 3, 3, 3, 1, 2, 2, 2,\
     0, 2, 2, 0, 3, 2, 2, 3, 2, 1, 2, 2, 2, 2, 2, 0, 1, 0, 3, 3, 0, 0, 3, 1, 0, 3, 0, 2, 2, 3,\
     3, 2, 3, 0, 0, 0, 0, 1, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 0, 1, 2, 0, 1, 2, 1, 3, 0, 0, 0, 1,\
     3, 2, 3, 2, 3, 2, 2, 0, 3, 0, 0, 0, 0, 0, 3, 0, 2, 1, 0, 0, 1, 3, 3, 2, 1, 1, 0, 0, 1, 3,\
     2, 3, 2, 2, 2, 1, 1, 1, 2, 0, 0, 2, 2, 3, 0, 3, 2, 0, 3, 1, 0, 2, 0, 2, 2, 0, 0, 1, 1, 0,\
     3, 0, 1, 3, 2, 0, 0, 3, 3, 2, 0, 0};


byte frq[5][6]={
  //step 0 10.136 500 MHz   actual -> 10.140 230
  // dial 10.1387
  { 0x53, 0xC2, 0xA9, 0x2d, 0x53, 0xa1 },
 // step 1
  { 0x53, 0xC2, 0xA9, 0x2d, 0x5a, 0x14  },
  // step 2
  { 0x53, 0xC2, 0xA9, 0x2d, 0x60, 0x87  },
  // step 3
  { 0x53, 0xC2, 0xA9, 0x2d, 0x66, 0xfa  },

  { 0x53, 0xC2, 0xA0, 0x56, 0x00, 0xB1  },
};

//Timer2 overflow interrupt vector handler, called (16,000,000/256)/256 times per second
ISR(TIMER2_OVF_vect) {
  if(send_cw) {return;}
  if(wait_sync) {return;}
  
  
  
   //cnt_pause++;
   //if (cnt_pause==29297) { 
   //cnt_pause = 0; pause = false; send_cw=true;}
 
  // if (!pause)  {
    if (true){
              cnt++;
              if (cnt == 167) { cnt = 0;  send_next_wspr = true; }    }
  
   

    
  

  
}  
//***************************************************************************************
void timer_setup() {  //Timer2 Settings: Timer Prescaler /256, WGM mode 0
          TCCR2A = 0;
          TCCR2B = 1<<CS22 | 1<<CS21;
          //Timer2 Overflow Interrupt Enable  
          TIMSK2 = 1<<TOIE2;  //reset timer
          TCNT2 = 0;}
          
//****
void(* resetFunc) (void) = 0; //declare reset function @ address 0


//**********************************************
/*void digtalToggled(uint_8_t pin) {
  digitalWrite(pin, 1);
  delay(200);
  digitalWrite(pin, 0);}*/
//**********************************************
void setup(){
          timer_setup();
          
          pinMode(ledPin, OUTPUT);
          pinMode(CWPin, OUTPUT);
          pinMode(rxPin, INPUT);
          pinMode(txPin, OUTPUT);
          pinMode(txPin, OUTPUT);
          pinMode(controlPin, OUTPUT);
          
          digitalWrite(fixPin,0);
          
          delay(500);
          Wire.begin(); // join i2c bus (address optional for master)
          delay(500);
          Serial.begin(9600);
          gps.begin(4800);
          switch_off();
            send_cw = false;
            send_wspr=false;
            send_next_wspr=false;
            
            
            pause=false;
            wait_sync = true;
            Serial.print("LZ0DLS Start 73!\n");
            
}
//---------------------------------------------------------------------------------------------
void freeze(){  Wire.beginTransmission(si570_address); 
                Wire.write(137);       
                Wire.write(0x10);              
                Wire.endTransmission(); 
                delay(10);}

//---------------------------------------------------------------------------------------------
void unfreeze(){  Wire.beginTransmission(si570_address); 
                  Wire.write( (uint8_t) 137);       
                  Wire.write( (uint8_t) 0 );              
                  Wire.endTransmission(); }
//---------------------------------------------------------------------------------------------
// 1 tit
// 2 taa
// 0 - end of char
void tit(void){ digitalWrite(CWPin,1); tone(speaker, 600);  delay(one_tit);   noTone(speaker); digitalWrite(CWPin,0); delay(one_tit);}
void taa(void){ digitalWrite(CWPin,1); tone(speaker, 600);  delay(3*one_tit); noTone(speaker); digitalWrite(CWPin,0); delay(one_tit);}
void mmm(void){   delay(3*one_tit); }

void send_cw_id(void){
  byte cw_cnt =0 ;
  while(send_cw){   switch (cw_id_string[cw_cnt]){
                    case 0:
                          delay(3*one_tit);
                          break;   
                    case 1:
                          tit();
                          break;
                    case 2:
                          taa();
                        break;
                    case 6:  
                        delay(6*one_tit);
                        break;
 
                     default:
                           {send_cw=false;
                           delay(10*one_tit);
                           wait_sync = true;
                               }
                            }
                            
                      cw_cnt++;      
    
   }
    


}


//***************************************************************************************
void send_one(byte znak){
        byte row = message[znak];  
        freeze();
        Wire.beginTransmission(si570_address); 
        Wire.write(7); 
        ptr = &frq[row][0];
        Wire.write(ptr, 6); 
        //Serial.print(frq[row][5]        , HEX);  Serial.print(" ")  ;    
        Wire.endTransmission();   
        unfreeze(); 
        delay(10);
        Wire.beginTransmission(si570_address); 
        Wire.write(135); 
        Wire.write(0x40);             
        Wire.endTransmission();  
 
        Serial.print(znak ,DEC);  Serial.print(" ");   if (znak%10==0)      Serial.print("\n");

}
//***************************************************************************************

 
 void switch_off(){
 
   freeze();
        Wire.beginTransmission(si570_address); 
        
        Wire.write(7); 
        ptr = &frq[4][0];
        Wire.write(ptr, 6); 
        Wire.endTransmission();   
       
        unfreeze(); 
        delay(10);
        Wire.beginTransmission(si570_address); 
        Wire.write(135); 
        Wire.write(0x40);             
        Wire.endTransmission();  

 
 }
//-----------------------------------------------------------------------------------------
boolean read_GPGGA(){
      char row[80];
      char someChar;
      char* ptr;
      ptr = &row[0];
      
   
      while  (!gps.available())        { ; }           
      someChar=gps.read();
      
      if( someChar == 0x24 ) start_stop=true;
      
      if (start_stop) {
       digitalToggle(controlPin); 
      while ( someChar != 0x0a ){*ptr = someChar; 
                                 ptr++;
                                 while  (!gps.available())        {  ; }
                                 someChar=gps.read();  
                                 
                                 //Serial.write(someChar);
                                 
                                 
                            
                          
                          
                                    }
       *ptr = 0; start_stop=false; }
      
       else {   return false;}
       
       char   *p;


       //Serial.println(row);
      
     // $GPGGA,220116.11,,N.412,E,1,04, 10.72, 413M, 37,M,,*66   
      if (strstr( row, "$GPGGA" ) == NULL) {return false; }//if not $GPGGA
     
      
      p = strtok(row, "," )     ;
      
      ptime = strtok(NULL, "," ); 
      p = strtok(NULL, "," ); //Serial.write(p);Serial.print("\n"); // 4241.249
      p = strtok(NULL, "," ); //Serial.write(p);Serial.print("\n"); // N
      p = strtok(NULL, "," ); //Serial.write(p);Serial.print("\n"); // 02315
      
      p = strtok(NULL, "," ); //Serial.write(p);Serial.print("\n"); // E
      
      p = strtok(NULL, "," ); //Serial.write(p);Serial.print("\n"); // 1/0 fix
      if(atoi(p) == 1) {      
          Serial.print("FIX OK \n\n"); 
          digitalWrite(fixPin,1);
          return true;}
      else {
          Serial.print("Not FIX \n\n");
          digitalWrite(fixPin,0);
          return false;   }
        
     // p = strtok(NULL, "," ); Serial.write(p);Serial.print("\n");// num satellites
    //  p = strtok(NULL, "," ); Serial.write(p);Serial.print("\n"); // 413 masl

}



void waiting(){
        // timer_setup();  wait_sync=false;   send_wspr=true;  return;
        char mins[3];
        char secs[6];
        
        unsigned int msec;
 
    if(read_GPGGA() ) {
        //Serial.write(ptime);Serial.print("\n");                         // hhmmss.dd
        char *to=mins;
        strncpy(to,ptime+2,2);mins[2]=0;
        
        to=secs;
        strncpy(to,ptime+4,5);secs[5]=0;
        
        
        msec = (unsigned int) (atof(secs)*1000) ;
      
       Serial.print("min:"); Serial.write(mins);Serial.print("\n");
       Serial.print("sec:"); Serial.write(secs);Serial.print("\n");
    
       if(msec<1000){
         msec = 1000-msec; 
       Serial.print("remain msec:"); Serial.print(msec, DEC);Serial.print("\n");}
       
     
       //Serial.print("fake minutes:"); Serial.print(atoi(mins), DEC);Serial.print("\n");
       if (atoi(mins)%4==0) {
               Serial.print("Start!!!\n");
                timer_setup();
                wait_sync=false;
                send_wspr=true;
              }
       
       
       
  }



}

void loop1()
{

  waiting();
  
  
}


  void loop ()
{
      digitalWrite(controlPin,0);
      if (send_next_wspr && send_wspr)    {
                  digitalWrite(CWPin,1);
                  send_one(symbol);
                  symbol++;
                  digitalToggle(controlPin);
                  if (symbol == 162) 
                        { symbol=0; send_wspr=false; wait_sync=true; digitalWrite(CWPin,0);resetFunc();}
                  send_next_wspr = false; }






      //if (send_cw){send_cw_id();}

      if (wait_sync){waiting();}
}   



/*
// Function to return a substring defined by a delimiter at an index
char* subStr (char* str, char delim, int index) {
   char *act, *sub, *ptr;
   char copy[MAX_STRING_LEN];
   int i;

   // Since strtok consumes the first arg, make a copy
   strcpy(copy, str);

   for (i = 1, act = copy; i <= index; i++, act = NULL) {
	//Serial.print(".");
	sub = strtok_r(act, &delim, &ptr);
	if (sub == NULL) break;
   }
   return sub;

}

*/


/*
Rocwell  $GPGGA,220116.11,4241.249,N,02315.412,E,1,04, 10.72, 413M, 37,M,,*66
doc      $GPGGA,123519,   4807.038,N,01131.000,E,1,08, 0.9,   545.4,M,46.9,M,,*47
         $GPGGA,      ,           , ,         , ,0,01,    ,        , ,,,,*67



Where:
     GGA          Global Positioning System Fix Data
     123519       Fix taken at 12:35:19 UTC
     4807.038,N   Latitude 48 deg 07.038' N
     01131.000,E  Longitude 11 deg 31.000' E
     1            Fix quality: 0 = invalid
                               1 = GPS fix (SPS)
                               2 = DGPS fix
                               3 = PPS fix
			       4 = Real Time Kinematic
			       5 = Float RTK
                               6 = estimated (dead reckoning) (2.3 feature)
			       7 = Manual input mode
			       8 = Simulation mode
     08           Number of satellites being tracked
     0.9          Horizontal dilution of position
     545.4,M      Altitude, Meters, above mean sea level
     46.9,M       Height of geoid (mean sea level) above WGS84
                      ellipsoid
     (empty field) time in seconds since last DGPS update
     (empty field) DGPS station ID number
     *47          the checksum data, always begins with *

*/









  
// registers 7 - 12

/*byte frq[5][6]={
  //step 0 10.138900MHz
  { 0x53, 0xC2, 0xA9, 0x56, 0x9D, 0x57 },
 // step 1
  { 0x53, 0xC2, 0xA9, 0x56, 0xA3, 0xCA  },
  // step 2
  { 0x53, 0xC2, 0xA9, 0x56, 0xAA, 0x3D  },
  // step 3
  { 0x53, 0xC2, 0xA9, 0x56, 0xB0, 0xB1  },

  { 0x53, 0xC2, 0xA0, 0x56, 0x00, 0xB1  },
};

//         7       0x53
//         8       0xC2
//         9       0xA9
//       10       0x30
//        11       0xC4
//        12       0x70

byte frq[5][6]={
  //step 0 10.136 700 MHz
  { 0x53, 0xC2, 0xA9, 0x30, 0xc4, 0x70 },
 // step 1
  { 0x53, 0xC2, 0xA9, 0x30, 0xca, 0xe3  },
  // step 2
  { 0x53, 0xC2, 0xA9, 0x30, 0xd1, 0x56  },
  // step 3
  { 0x53, 0xC2, 0xA9, 0x30, 0xd7, 0xc9  },

  { 0x53, 0xC2, 0xA0, 0x56, 0x00, 0xB1  },
};*/


/*

      Register   Data
         7       0x53
         8       0xC2
         9       0xA9
        10       0x2D
        11       0x53
        12       0xA1

step - 0x673
*/

/*
void send_wspr_message(){
  for(byte znak=0;znak<163; znak++)
        send_one(znak);
        
        freeze();
        Wire.beginTransmission(si570_address); 
        Wire.write(7); 
        ptr = &frq[4][0];
        Wire.write(ptr, 6); 
        Wire.endTransmission();   
       
        unfreeze(); 
        delay(10);
        Wire.beginTransmission(si570_address); 
        Wire.write(135); 
        Wire.write(0x40);             
        Wire.endTransmission();  

        delay(8000);}
*/

