
/* Broches */
const byte PIN_LED_R = 4;
const byte PIN_LED_G = 5;
const byte PIN_LED_B = 6;

int toneVal; 
int buzzer =8;
int i=0;
int bouton=10;
int bas=0;
int haut=0;

float sinVal;  

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
  const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
  const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
  int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
  PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {  //initialisation de toute les variables et composants
  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
  pinMode(buzzer,OUTPUT);
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_LED_B, OUTPUT);
  }
  
}




void alarm(){ // fonction qui fait sonner le buzzer
    for(int x=0; x<180; x++){                   // crée une variable "x" de type "int" dont la valeur de départ est de 0 et qui lorsqu'elle est inférieur 
                                                 // à 180 augmente de +1. Ce qui permet de s'arrurer que la valeur sinusoïdale ne va pas dans le négatif.     
        sinVal = (sin(x*(3.1412/180)));         // permet de convertir la valeur de x en radians pour la suite du programme.
        toneVal = 2000+(int(sinVal*1000));      // formule qui permet de convertir la variable en une nouvelle varianble "toneVal" qui défénira la fréquence du Buzzer.
        tone(buzzer, toneVal);                      // utilise la fonction tone, constituer du numéro de la Broche (13) et de la fréquence (toneVal)
        delay(2); 
      }
  
}

int BPM(){ //sous programme qui permet de gerer la led rgb en fontcion de la detection de nb de battement de coeurs par minute 
   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
    Serial.println(myBPM);                        // Print the value inside of myBPM. 
  }

  if(myBPM<55){
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_R, LOW);// tension cardiaque basse
    digitalWrite(PIN_LED_G, LOW);    
    alarm();
  }
  
  if (myBPM>165){
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_G, LOW);
    digitalWrite(PIN_LED_R, HIGH); // tension cardiaque haute
    alarm();
  }
  
  if(myBPM>55 && myBPM<165){
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_R, LOW);
    digitalWrite(PIN_LED_G, HIGH);
     digitalWrite(buzzer, LOW);
  }
  
  return myBPM;
  
}

void DANGER(int bouton){ // fait clignoter des leds en violet, allume une alarme et s'active en cas de chute du patient  
  while(true){
    alarm();    
    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_G, LOW);
    delay(50);
    digitalWrite(PIN_LED_R, LOW);
    digitalWrite(PIN_LED_B, LOW);    
    
    if(bouton=1){
      break;
   }  
  }
  
 return 0;

}

/*voici la bouble principale */
void loop() {         //boucle principal qui permet de transmettre les information de chute ou de BPM au smartphone 
  int bp=BPM();
  delay(20);                    

} 
