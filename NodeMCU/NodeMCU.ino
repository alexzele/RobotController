#include <NewPingESP8266.h>

/* include library */
#include <ESP8266WiFi.h>

/* define WiFi cretentials */
#define SSID "Roboto"
#define PASSWORD "RobotoPass"

/* define L298N or L293D motor control pins */
#define leftMotorForward   2    /* GPIO2(D4) -> IN3   */
#define rightMotorForward  15   /* GPIO15(D8) -> IN1  */
#define leftMotorBackward  0    /* GPIO0(D3) -> IN4   */
#define rightMotorBackward 13   /* GPIO13(D7) -> IN2  */

/* define L298N or L293D enable pins */
#define rightMotorENB 14   /* GPIO14(D5) -> Motor-A Enable */
#define leftMotorENB  12   /* GPIO12(D6) -> Motor-B Enable */

/* define trigger, echo pins and maximum proximity for proximity sensor */
#define TRIGGER 5 /*  GPIO5(D1) -> Trigger  */
#define ECHO 4    /*  GPI04(D2) -> Echo    */
#define MAXPROX 8 /*  Maximum proximity in CM

/* WiFi settings */
IPAddress subnet(255, 255, 255, 0);
IPAddress apIP(10, 10, 10, 1);
WiFiServer server(666);
WiFiClient client;

/* Sonar constructor  */
NewPingESP8266 sonar(TRIGGER, ECHO);

/* data received from application */
String  data = "";

/* open variable to prevent memory allocation in run */
int i = 0;
int c = 0;

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
  Serial.println("Booting up");
  Serial.println("Starting ap");

  /* Setting WiFi */
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(SSID, PASSWORD);
  
  /* Starting server */
  server.begin();

  Serial.println("Server started");
  Serial.println("Ready");
}

void loop()
{
  /* If the server available, run the "checkClient" function */
  client = server.available();
  if (isWall() && data == "forward"){
    MotorStop();
  }
  if (!client) {
    return;
  }

  data = client.readStringUntil('\r');

  /************************ Run function according to incoming data from application *************************/

  /* If the incoming data is "forward", run the "MotorForward" function */
  if (data == "forward") {
    Serial.println("moving forward");
    MotorForward();
  }
  /* If the incoming data is "backward", run the "MotorBackward" function */
  else if (data == "backward") {
    Serial.println("moving backwards");
    MotorBackward();
  }
  /* If the incoming data is "left", run the "TurnLeft" function */
  else if (data == "left") {
    Serial.println("moving left");
    TurnLeft();
  }
  /* If the incoming data is "right", run the "TurnRight" function */
  else if (data == "right") {
    Serial.println("moving right");
    TurnRight();
  }
  /* If the incoming data is "stop", run the "MotorStop" function */
  else if (data == "stop") {
    Serial.println("stopping motor");
    MotorStop();
  }
}

/********************************************* FORWARD *****************************************************/
void MotorForward(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)
{
  digitalWrite(leftMotorENB, LOW);
  digitalWrite(rightMotorENB, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

bool isWall(void){
  c = 0;
  /* if on 3 checks the distance is less than MAXPROX the function will return true  */
  for(i=0; i < 3; i++){
    if (sonar.ping_cm() < MAXPROX){
      c+=1;
    }
    return (c==3);
  }
}
