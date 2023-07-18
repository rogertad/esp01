#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "chess2g";            // fill in here your router or wifi SSID
const char* password = "gambitodadama";  // fill in here your router or wifi password

ESP8266WebServer server(80);
#define RELAY 0  // relay connected to  GPIO0
int porta = LED_BUILTIN;
boolean flag = false;

int contador = 0;

void setup() {
  Serial.begin(115200);

  delay(1000);

  pinMode(RELAY, OUTPUT);
  pinMode(porta, OUTPUT);
  digitalWrite(RELAY, HIGH);
  digitalWrite(porta, HIGH);

  delay(1000);

  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  server.on("/", handleRoot);
  //server.on("/getparam", handleParam);

  server.begin();

  delay(333);
}


void handleRoot() {
  flag = !flag;
  contador++;

  server.stop();
  server.close();
  delay(555);

  digitalWrite(RELAY, flag);
  digitalWrite(porta, flag);

  delay(555);

  server.on("/", handleRoot);
  server.begin();
  server.send(200, "text/html", "<h1>Ola, ESP01! contador = " + String(contador) + " </h1>");
}




void loop() {

  //flag = !flag;

  //digitalWrite(RELAY, flag);
  //digitalWrite(porta, flag);
  //delay(1000);
  server.handleClient();
}
