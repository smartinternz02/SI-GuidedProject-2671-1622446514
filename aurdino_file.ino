#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String command;
String data="";

void callback(char* topic, byte* payload, unsigned int payloadLength);

// CHANGE TO YOUR WIFI CREDENTIALS
const char* ssid = "Akash Yadav";//your wifi ssid
const char* password = "Akash@469";//your password

// CHANGE TO YOUR DEVICE CREDENTIALS AS PER IN IBM BLUMIX
#define ORG "lxi179"
#define DEVICE_TYPE "ESP32"
#define DEVICE_ID "12345"
#define TOKEN "Yadav@1395121.CoM" //  Authentication Token OF THE DEVICE

//  PIN DECLARATIONS 

int led1 = 36;
int led2 = 39;
int led3 = 34;
int led4 = 2;


//-------- Customise the above values --------
const char publishTopic[] = "iot-2/evt/Data/fmt/json";
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";// 
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;


WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

int publishInterval = 5000; // 30 seconds
long lastPublishMillis;
void publishData();

void setup() {
  
  Serial.begin(115200);
  Serial.println();

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
 
  wifiConnect();
  mqttConnect();
   delay(2000);
Serial.println("oled test");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
}

void loop() {


 if (millis() - lastPublishMillis > publishInterval)
  {
    publishData();
    lastPublishMillis = millis();
  }
  
  if (!client.loop()) {
    mqttConnect();
  }
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected, IP address: "); 
  Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected()) 
  {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    
    initManagedDevice();
    Serial.println();
  }
}

void initManagedDevice() {
  if (client.subscribe(topic)) {
   
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  
  Serial.print("callback invoked for topic: ");
  Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    
    command+= (char)payload[i];
  }
  

  control_func();
  command= "";
}

void control_func()
{
  
  Serial.println(command);
  if(command== "5")
 {

 digitalWrite(led1,LOW);
      
     Serial.println(".......lights are off..........");
    
  }
  else if(command== "1")
  {
     digitalWrite(led1,HIGH);
      
     Serial.println(".......lights are on..........");

  }
  else if(command== "6")
 {


      digitalWrite(led2,LOW);
     Serial.println(".......lights are off..........");
    
  }
  else if(command== "2")
  {
      digitalWrite(led2,HIGH);
     Serial.println(".......lights are on..........");

  }
   else if(command== "7")
 {


      digitalWrite(led3,LOW);
     Serial.println(".......lights are off..........");
    
  }
  else if(command== "3")
  {
    
      digitalWrite(led3,HIGH);
     Serial.println(".......lights are on..........");

  }
   else if(command== "8")
 {


      digitalWrite(led4,LOW);
     Serial.println(".......lights are off..........");
    
  }
  else if(command== "4")
  {
     
      digitalWrite(led4,HIGH);
     Serial.println(".......lights are on..........");

  }
   
  
}

void publishData() 
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.print("Your medicine is");
  display.println(command);
  display.display(); 
}
