#define r 7.5
/*
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 6, 2);
*/
volatile int octavos=0;
int octavosD=0;
unsigned long ms0=0, msF;
bool LectureON=true;

void setup() {
  Serial.begin(9600);
  /*
   pinMode(13,OUTPUT);
   digitalWrite(13,LOW);
   */
  //lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(3), interrupcion0, FALLING);
}

void interrupcion0()// Funcion que se ejecuta durante cada interrupion
{
  octavos++;
  octavosD++;
}

void loop() {
  /*//USAR SI NO OCUPO  "ATTACHINTERRUPT()"
  delay(1);
  if (analogRead(0) * 5.0 / 1023.0 < 4 && LectureON){
    octavos++;
    octavosD++;
    LectureON=false;
  }else if(analogRead(0) * 5.0 / 1023.0 > 3 && !LectureON){
    LectureON=true;
  }
  */

  if(millis()%3000 == 0){ //MUESTRA LOS DATOS CADA ** 3s **!!
    /* OPCION PARA MOSTRAR DATOS!
    Serial.println(analogRead(0)*5.0/1023.0);
    Serial.println(octavos);
    Serial.println(octavos/8);     // #vueltas
    Serial.println(octavos/8.0);   // #vueltas EN FLOAT
    Serial.println(millis());      // tiempo transcurrido
    Serial.println(msF);           // periodo de tiempo
    Serial.println(vF);            // vueltas / periodo de tiempo
     */
    msF=millis()-ms0;
    detachInterrupt(digitalPinToInterrupt(3));
    //******* RPM=((octavos*(60000/msF))/8); *******
    Serial.print("Vel: ");
    Serial.print((octavos*(60000.0/msF))/8.0);
    Serial.println(" RPM");
    /*lcd.print("Vel: ");
    lcd.print((octavos*(60000.0/msF))/8.0);
    lcd.print(" RPM");
    */
    /*  //VELOCIDAD EN m/s
    Serial.print("Vel: ");
    Serial.print((((octavos*((2*M_PI*r)/8))/100))/(msF/1000));
    Serial.println(" m/s");
    lcd.print("Vel ");
    lcd.print((((octavos*((2*M_PI*r)/8))/100))/(msF/1000));
    lcd.print(" m/s");
    */
    
    Serial.print("Distancia: ");
    Serial.print(((octavosD/8 * (2*M_PI*r)) + (octavosD%8 * (2*M_PI*r/8)))/100);
    Serial.println('m');
    Serial.println();
    /*lcd.setCursor(0,1);
    lcd.print("Dist: ");
    lcd.print(((octavosD/8 * (2*M_PI*r)) + (octavosD%8 * (2*M_PI*r/8)))/100);
    lcd.print('m');
    lcd.setCursor(0,0);
    */
    octavos=0;
    ms0=millis();
    attachInterrupt(digitalPinToInterrupt(3), interrupcion0, FALLING);
  }
}
