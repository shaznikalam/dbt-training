#include <SoftwareSerial.h>

const int mq3 = 11;     
const int ledPin1 =  9;      
const int ledPin2 =  10;
const int buzz =  12; 
int mq3State = 0;    



int sensorPin = A4;
int sensorValue;
#define RX 2 // TX of esp8266 in connected with Arduino pin 2
#define TX 3 // RX of esp8266 in connected with Arduino pin 3
String WIFI_SSID = "wifi12345678";// WIFI NAME
String WIFI_PASS = "wifi12345678"; // WIFI PASSWORD
String API = "H9AT65DESRBVE6 35";// Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false;   
SoftwareSerial esp8266(RX,TX); 
void setup() {

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(mq3, INPUT);
  
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ WIFI_SSID +"\",\""+ WIFI_PASS +"\"",20,"OK");
}
void loop() {

  mq3State = digitalRead(mq3);
  
 sensorValue = analogRead(sensorPin);
 String getData="GET /update?api_key="+ API+"&field1="+map(mq3State,HIGH,LOW,100,0);
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);



  if (mq3State == HIGH) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(buzz, LOW);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(buzz, HIGH);
  }

 
 //delay(1500);
 countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}
void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
    countTimeCommand++;
  } 
  if(found == true)
  {
    Serial.println("OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  } 
  found = false;
 }