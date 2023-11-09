#include<dht.h>
#include<Servo.h>
#include<Wire.h>

int flag=0;
int fan=3;
#define dht_apin A0
Servo myservo;
dht DHT;

void setup() {
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);

  Serial.begin(9600);

  myservo.attach(9);
  myservo.write(0);
  Serial.println("The Boyz...");
  delay(2000);
  Serial.println("Servo Testing...");
  Serial.println("Fins closing");
  for(int i=0;i<=180;i++){
    myservo.write(i);
    delay(15);
    }
    delay(1000);
 Serial.println("Fins opening");
  for(int i=180;i>=0;i--){
    myservo.write(i);
    delay(15);
  }
    delay(1000);
    Serial.println("Servo testing complete");
    Serial.println("Entering program for Humidity and Temperature.....");
}

void loop() {
  DHT.read11(dht_apin);
  Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(1000);
   
    
    
  if(DHT.temperature>=32 && DHT.humidity>45 && flag==1){
    Serial.println("Temperature is High \n closing Fins");
    for(int i=0;i<=180;i++){  //close loop
    myservo.write(i);
    delay(15);
    }
    Serial.println("Switching off the exhaust fan");
    digitalWrite(fan,LOW);
    flag=0;
  }


  
  else if(DHT.humidity>=45 && flag==1){
    digitalWrite(fan,HIGH);
    Serial.println("Exhaust ON");
    if(DHT.temperature>=32){
    Serial.println("Temperature is High \n closing Fins");
    for(int i=0;i<=180;i++){  //close loop
    myservo.write(i);
    delay(15);
    }
    Serial.println("Switching off the exhaust fan");
    digitalWrite(fan,LOW);
    flag=0
    ;
  }}


  
  else if(DHT.temperature<32 && DHT.humidity>45 && flag==0)
  {
    Serial.println("Fins are opening...");
    for(int i=180;i>=0;i--){ //open loop
    myservo.write(i);
    delay(15);
  }
  digitalWrite(fan,HIGH);
  flag=1;
  }

}
