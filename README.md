# Solar-dryer-iTech-hackfest-
<h2>A project developed for iTech Hackfest Conducted at PSG</h2>
<h1>SOLAR DRYER</h1>
Solar dryers are devices that use solar energy to dry substances, especially food. Solar dryers use the heat from sun to remove the moisture content of food substances. There are two general types of solar dryers: Direct and indirect.

<h2>Problem Statement</h2>
We have chosen to develop a project using direct solar dryer concept.Generally a direct solar dryer uses 3-4 exhaust fans which consumes more power, as they run the whole time until the drying process is completed.
<h2>Objective</h2>
Our main objective is to reduce the power consumption, using an efficient method to dry the contents placed inside the container.
<h2>Innovation</h2>
We have found a effective way to maintain the required humidity and temperature inside the container, using a minimum number of exhaust fans. To reduce the power consumption, we have implemented louver mechanism as it controls the incoming  sunlight with low power consumption and so the exhaust fans do not run for a long period of time. Hence, the power consumed is reduced.

<h2>Requirements</h2>

<h3>Electronic Components</h3>

-->Arduino UNO R3

-->Exhaust Fan (CPU Cooler Fan)

-->Servo MG90S

-->DHT11 (Humidity and Temperature sensor)

<h3>Other Components</h3>

-->Container Box

-->Acrylic Board (3mm)

-->Jumper Cables

-->Louver Mechanism

<h2>Working</h2>

We have attached fins, to adjust the amount of sunlight entering the container. A servo motor will be used to control the fins(via louver mechanism).
At first, to increase the temperature inside the container, we decrease the humidity using an exhaust fan (i.e. Temperature is inversely proportional to Humidity). As the internals of the container is completely coated in black, for effective absorption of heat, and when the temperature specified is out of range, the fins close and isolate the container from any external heat exchanges. After the temperature decreases, the fins are opened to allow the sunlight to enter the container again, this process is repeated several times until the item placed in the container reaches an optimal condition (i.e. dried).


![Github](https://user-images.githubusercontent.com/65480054/187011317-9a728abe-737f-4a6f-97c2-dc0cc703c76e.jpg)


<h2>Source Code</h2>

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
        flag=0;
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
