#include <IRremote.h>
#define rosso 8 // definisco dove è luce rossa
#define verde 4 // definisco dove è luce verde
#define blu 7 // definisco dove è luce blu
const byte IR_RECEIVE_PIN = 2; // definisco input del ir recever
void setup()
{
   Serial.begin(9600); // porta seriale
   Serial.println("IR Receive by Matteo"); // titolo
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
   pinMode(rosso, OUTPUT); // autput alla luce rossa
   pinMode(verde, OUTPUT); // autput alla luce verde
   pinMode(blu, OUTPUT); // autput alla luce verde
   
}

void loop(){
  
   if (IrReceiver.decode()){
      String ir_code = String(IrReceiver.decodedIRData.command, HEX); // decode del codice
      Serial.println(ir_code); //riferisce nella porta seriale il codice

      if(ir_code == "4"){ // se il codice è uguale a 4 
        digitalWrite(rosso, HIGH); // luce rossa accesa
        Serial.println("rosso"); // scrive nella porta seriale quale luce è accesa
      }else{ // se il codice non è uguale a 4 
        digitalWrite(rosso, LOW); // luce rossa spenta
      }
      if(ir_code == "5"){
        digitalWrite(verde, HIGH);
        Serial.println("verde");
      }else{
        digitalWrite(verde, LOW);
      }
      if(ir_code == "6"){
        digitalWrite(blu, HIGH);
        Serial.println("blu");
      }else{
        digitalWrite(blu, LOW);
      }
      if(ir_code == "7"){
        digitalWrite(blu, HIGH);
        digitalWrite(verde, HIGH);
        digitalWrite(rosso, HIGH);
        Serial.println("bianco");
      }
      if(ir_code == "b"){ // se il codice è uguale a b (flash)
        while (true) { // loop infinito 
        digitalWrite(blu, HIGH); // luce blu accesa
        digitalWrite(verde, LOW); // luce verde spenta
        digitalWrite(rosso, LOW); // luce rossa spenta
        delay(100); // aspetta 100 milli secondi
        digitalWrite(verde, HIGH);
        digitalWrite(blu, LOW);
        delay(100);
        digitalWrite(rosso, HIGH);
        digitalWrite(verde, LOW);
        delay(100);
        if (IrReceiver.decode()){
          String ir_code = String(IrReceiver.decodedIRData.command, HEX);
          Serial.println(ir_code);
          IrReceiver.resume();
          if (ir_code == "f"){ // se il codice è uguale a f 
            break; // ferma il loop
        }
      }
    }     
  }
  IrReceiver.resume();   
 }
}
