typedef struct {
    boolean power;
    int duration;
} signal;


const signal A {true, 850};
const signal B {true, 400};
const signal C {false, 500};
const signal D {false, 950};

#define LIGHT_LOOPS 4
#define INTERMISSION 20000

#define TX_PIN D1

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

signal preamble[] = {B,C,B,C,B,C,B,C,B,C,B,C,B,C,B,C,B,C,B,C,B,C,B,C};
signal light[] = {A,C,B,D,A,C,A,C,B,D,B,D,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,B,D,B,D,B,D,A,C,A,C,B,D,A,C,B,D,B,D,A,C,B,D,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,B,C};
signal speed0[] = {A,C,B,D,A,C,A,C,B,D,B,D,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,B,D,B,D,B,D,A,C,A,C,B,D,A,C,B,D,B,D,A,C,B,D,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,B,D,B,C};
signal speed3[] = {A,C,B,D,A,C,A,C,B,D,B,D,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,B,D,B,D,B,D,A,C,A,C,B,D,A,C,B,D,B,D,A,C,B,D,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,A,C,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,A,C,A,C,B,C};
signal speed2[] = {A,C,B,D,A,C,A,C,B,D,B,D,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,B,D,B,D,B,D,A,C,A,C,B,D,A,C,B,D,B,D,A,C,B,D,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,A,C,B,D,B,D,B,D,B,D,B,D,A,C,A,C,A,C,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,A,C,B,D,C};
signal speed1[] = {A,C,B,D,A,C,A,C,B,D,B,D,A,C,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,A,C,B,D,B,D,B,D,A,C,A,C,B,D,A,C,B,D,B,D,A,C,B,D,A,C,A,C,B,D,A,C,A,C,A,C,A,C,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,B,D,A,C,B,D,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,B,D,A,C,B,D};

unsigned long previous = 0;
const long interval = 10000;

void setup(){
    pinMode(BUILTIN_LED, OUTPUT);
    pinMode (TX_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("init");
}

void toggleLight(){
    //do the preamble (24)
    Serial.println(millis());
    Serial.print("Preamble ");
    Serial.println(ARRAY_SIZE(preamble));
    for(int repeat = 0; repeat < 3; repeat++){
      for(int burst = 0; burst < ARRAY_SIZE(preamble); burst++){
        Serial.print(burst);
        Serial.print(" ");
          Serial.print(preamble[burst].power);
          Serial.println(preamble[burst].duration);
          digitalWrite(TX_PIN, preamble[burst].power);
          delayMicroseconds(preamble[burst].duration);
      }
      delayMicroseconds(10000);
      Serial.println("Message");
      for(int burst = 0; burst < ARRAY_SIZE(light); burst++){
          digitalWrite(TX_PIN, light[burst].power);
          delayMicroseconds(light[burst].duration);
      }
    delayMicroseconds(INTERMISSION);
    }
    Serial.println("Done");
}

void loop(){
    if(millis() - previous >= interval){
      previous = millis();
      digitalWrite(BUILTIN_LED, HIGH);
      toggleLight();
      digitalWrite(BUILTIN_LED, LOW);
    }
    delay(5000);
}
