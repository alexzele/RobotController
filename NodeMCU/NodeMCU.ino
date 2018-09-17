/* include library */
#include <ESP8266WiFi.h>

/* define port */
WiFiClient client;
WiFiServer server(666);

/* WIFI settings */
const char* ssid = "XXXXXX";
const char* password = "XXXXXXX";

//static ip
IPAddress ip(192, 168, 1, 177);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

/* data received from application */
String  data =""; 

/* define L298N or L293D motor control pins */
int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */


/* define L298N or L293D enable pins */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */

void setup()
{
  /* initialize motor control pins as output */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  /* start server communication */
  Serial.begin(9600);
  Serial.println("booting up");
  Serial.println("Connecting to WIFI");
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  server.begin();

  Serial.println("Server started");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
  
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) {
      return; 
    }
    data = checkClient();

/************************ Run function according to incoming data from application *************************/
    Serial.println("loop is running");

    /* If the incoming data is "forward", run the "MotorForward" function */
    if (data == "forward") {
      MotorForward();
      Serial.println("moving forward");
    }
    /* If the incoming data is "backward", run the "MotorBackward" function */
    else if(data == "backward") {
      MotorBackward();
      Serial.println("moving backwards");
    }
    /* If the incoming data is "left", run the "TurnLeft" function */
    else if (data == "left"){
      TurnLeft();
      Serial.println("moving left");
    }
    /* If the incoming data is "right", run the "TurnRight" function */
    else if (data == "right"){
      TurnRight();
      Serial.println("moving right");
    }
    /* If the incoming data is "stop", run the "MotorStop" function */
    else if (data == "stop") MotorStop();
} 

/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient(void)
{
  while(!client.available()) {/*do nothing*/}; 
  String request = client.readStringUntil('\r');
  //client.flush();
  return request;
}
