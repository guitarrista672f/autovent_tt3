/************************************************************************/
/*                  PROJEC:AUTOVENT FOR TT3                             */
/*                  G.FERNANDO TREVINO                                  */
/*                          7/21/2021                                   */
/************************************************************************/

//***********************variables ***********************************
const int lid_pin=4; //it is physicaly pin 3 in ATtiny85
const int bag_pin=3;//it is physicaly pin 2 in ATtiny85
const int output_pin=2;//it is physicaly pin 7 in ATtiny85

bool lid_open; //senses signal for lid when it is open
bool airbag_down; // senses signal for airbag when it is down

bool cicle=0; // to indicate when the secuencie out-in on autovent is complete(value 1)

int counter=0;//for secuencies out/in of autovent


//***********TIME ******************************************
const int timeOn=100;
const int timeOff=100;
int t_on;
int t_off;
unsigned long time_ini_on=0;
unsigned long time_ini_off=0;
unsigned long time_elapsed_on=0;
unsigned long time_elapsed_off=0;

//**********************Prototypes ***********************************
void monitoreo();
void reset_cicle();
void secuency();

//**********************************************************************
void setup(){
  pinMode(lid_pin,INPUT);
  pinMode(bag_pin,INPUT);
  pinMode(output_pin,OUTPUT);
  digitalWrite(output_pin,LOW);
}
//**************************************************************************
void loop(){
  monitoreo();
  reset_cicle();
  secuency();

  //Time managment

  
  switch(t_on){
    //=========================
    case 0://autovent is in
    break;
    case 1://autovent is out
    time_elapsed_on=millis()-time_ini_on;

    if(time_elapsed_on>=timeOn ) {
      digitalWrite(output_pin,LOW);
      t_on=0;
      t_off=1;
      time_ini_off=millis();
      
    }
    break;
  }
  //======================

  switch(t_off){
    case 0:
    break;

    case 1:
     time_elapsed_off=millis()-time_ini_off;
     if(time_elapsed_off>=timeOff ) {
        t_off=0;
      
     }
    break;
  }
}

//**********************************************FUNCTIONS ********************

void monitoreo(){
  //Read signals
  lid_open = digitalRead(lid_pin);
  airbag_down = digitalRead(bag_pin);
}
//*****************************************
void reset_cicle(){

    if(!lid_open && !airbag_down ){

      cicle=0;
    }
}

//*****************************************

void secuency(){
  
  if(lid_open && airbag_down){
    
          if(cicle==1){
            goto salida;   
          }else{
                if(t_on || t_off){
    
                    goto salida;
                }else{
                  if(counter<=3){
                    digitalWrite(output_pin,HIGH);
                    t_on=1;
                    time_ini_on=millis();
                    counter++;
                  }else{
                    cicle=1;
                    counter=0;
                  }
                }
            }
           
  }
  
salida :;
  
}
