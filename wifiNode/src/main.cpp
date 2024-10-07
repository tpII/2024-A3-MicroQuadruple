#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

// Configura la red WiFi del NodeMCU
const char* ssid = "NodeMCU_AP";
const char* password = "12345678";

// Crear instancia del PCA9685 y el servidor web
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();
AsyncWebServer server(80);

// Definir rango del servo
#define SERVOMIN 150  // Ancho de pulso mínimo (ángulo 0 grados)
#define SERVOMAX 600  // Ancho de pulso máximo (ángulo 180 grados)

// Función para mover el servo
void moveServo(uint8_t num, uint16_t position) {
  pca9685.setPWM(num, 0, position);
}
void resetPCA9685() {
    Wire.beginTransmission(0x40);  // Dirección I2C del PCA9685
    Wire.write(0x00);  // Registro de modo
    Wire.write(0x00);  // Reiniciar al modo normal
    Wire.endTransmission();
    pca9685.begin();  // Inicializar nuevamente
    pca9685.setPWMFreq(60);  // Configurar frecuencia para servos
}
void setup() {
  Serial.begin(115200);
  
  // Inicializa el PCA9685
  pca9685.begin();
  pca9685.setPWMFreq(60);  // Frecuencia para servos
  delay(10);  // Pausa para asegurarse de que el controlador se inicie correctamente


  // Configurar el NodeMCU como Access Point
  WiFi.softAP(ssid, password);
  Serial.println("IP del NodeMCU:");
  Serial.println(WiFi.softAPIP());
server.begin();
  // Ruta principal con un botón para controlar el servo
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", R"rawliteral(
      <!DOCTYPE html>
      <html>
      <body>
        <h1>Controlar Servo</h1>
        <button onclick="moveServo0()">Mover Servo0</button>
        <button onclick="moveServo1()">Mover Servo1</button>
        <button onclick="moveServo2()">Mover Servo2</button>
        
        <button onclick="moveServo5()">Mover Servo5</button>
        <button onclick="moveServo6()">Mover Servo6</button>
        <button onclick="moveServo7()">Mover Servo7</button>

        <button onclick="moveServo9()">Mover Servo9</button>
        <button onclick="moveServo10()">Mover Servo10</button>
        <button onclick="moveServo11()">Mover Servo11</button>
      
        <button onclick="moveServo13()">Mover Servo13</button>
        <button onclick="moveServo14()">Mover Servo14</button>
        <button onclick="moveServo15()">Mover Servo15</button>
        
        
        <script>
          function moveServo0() {
            fetch("/servo").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo1() {
            fetch("/servo1").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo2() {
            fetch("/servo2").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo5() {
            fetch("/servo5").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo6() {
            fetch("/servo6").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo7() {
            fetch("/servo7").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo9() {
            fetch("/servo9").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo10() {
            fetch("/servo10").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo11() {
            fetch("/servo11").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo13() {
            fetch("/servo13").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo14() {
            fetch("/servo14").then(response => {
              console.log('Servo Movido');
            });
          }
          function moveServo15() {
            fetch("/servo15").then(response => {
              console.log('Servo Movido');
            });
          }
        </script>
      </body>
      </html>
    )rawliteral");
  });

  // Ruta que mueve el servo
  server.on("/servo", HTTP_GET, [](AsyncWebServerRequest *request){
   moveServo(0, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(0, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
server.on("/servo1", HTTP_GET, [](AsyncWebServerRequest *request){
   moveServo(1, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(2, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo2", HTTP_GET, [](AsyncWebServerRequest *request){
   moveServo(2, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(2, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo5", HTTP_GET, [](AsyncWebServerRequest *request){
    moveServo(5, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(5, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo6", HTTP_GET, [](AsyncWebServerRequest *request){
    moveServo(6, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(6, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo7", HTTP_GET, [](AsyncWebServerRequest *request){
    moveServo(7, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(7, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo9", HTTP_GET, [](AsyncWebServerRequest *request){
   
    moveServo(9, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(9, SERVOMAX);  // Mover servo al ángulo máximo
    
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo10", HTTP_GET, [](AsyncWebServerRequest *request){
   
    moveServo(10, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(10, SERVOMAX);  // Mover servo al ángulo máximo
   
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo11", HTTP_GET, [](AsyncWebServerRequest *request){
  
    moveServo(11, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(11, SERVOMAX);  // Mover servo al ángulo máximo
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo13", HTTP_GET, [](AsyncWebServerRequest *request){
  
    moveServo(13, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(13, SERVOMAX);  // Mover servo al ángulo máximo
    
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo14", HTTP_GET, [](AsyncWebServerRequest *request){
   
    moveServo(14, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(14, SERVOMAX);  // Mover servo al ángulo máximo
    
    request->send(200, "text/plain", "Servo movido");
  });
  server.on("/servo15", HTTP_GET, [](AsyncWebServerRequest *request){
   
    moveServo(15, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(15, SERVOMAX);  // Mover servo al ángulo máximo
    
    request->send(200, "text/plain", "Servo movido");
  });
  

  // Iniciar el servidor
  server.begin();
}

void loop() {
  // No se requiere código aquí, el servidor se encarga del manejo
}
