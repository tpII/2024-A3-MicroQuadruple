#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

// Configura la red WiFi del NodeMCU
const char* ssid = "NodeMCU_AP";
const char* password = "12345678";
// Asignación de servos para las patas
#define FRONT_LEFT_HIP 5
#define FRONT_LEFT_KNEE 6
#define FRONT_RIGHT_HIP 2
#define FRONT_RIGHT_KNEE 3
#define BACK_LEFT_HIP 13
#define BACK_LEFT_KNEE 14
#define BACK_RIGHT_HIP 0
#define BACK_RIGHT_KNEE 1

// Crear instancia del PCA9685 y el servidor web
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();
AsyncWebServer server(80);

// Definir rango del servo
#define SERVOMIN 150  // Ancho de pulso mínimo (ángulo 0 grados)
#define SERVOMAX 600  // Ancho de pulso máximo (ángulo 180 grados)

// Pin del sensor SW520D
const int tiltSensorPin = D5;  // GPIO pin para el sensor de nivel (SW520D)
void resetPCA9685() {
    Wire.beginTransmission(0x40);  // Dirección I2C del PCA9685
    Wire.write(0x00);              // Registro de modo
    Wire.write(0x00);              // Reiniciar al modo normal
    Wire.endTransmission();
    pca9685.begin();               // Inicializar nuevamente
    pca9685.setPWMFreq(60);        // Configurar frecuencia para servos
}
// Función para mover el servo
void moveServo(uint8_t num, uint16_t position) {
  pca9685.setPWM(num, 0, position);
}

// Secuencia para caminar
void position() {
  //Para 2
  moveServo(5, 330);  //
  delay(250);
  moveServo(6, 450);  //
  delay(250);
  moveServo(4, 600);  // 
  delay(250);
  
  //pata 3
  moveServo(11, 200);  // 
  delay(250);
  moveServo(9, 300);  // 
  delay(250);
  moveServo(10, 200);  //
  delay(250);
  Serial.println("Secuencia completada");
}
void position2() {
  //Pata 1
  moveServo(1, 500);  //
  delay(250);
  moveServo(0, 500);  //
  delay(250);
  moveServo(2, 400);  // 
  delay(250);
  
  //pata 4
  moveServo(13, 350);  // 
  delay(250);
  moveServo(14, 450);  // 
  delay(250);
  moveServo(15, 450);  //
  delay(250);
  Serial.println("Secuencia completada");
}
// Secuencia de un paso de caminar
// Secuencia de un paso de caminar
void walkStep() {
  // Levantar patas 3 (delantera derecha) y 4 (trasera izquierda) simultáneamente

  moveServo(6,SERVOMAX/2.5);
  delay(200);
  moveServo(4, SERVOMAX/2);
  delay(200);
  moveServo(6,450);
  delay(100);
  moveServo(4, 550);   // Delantera derecha - levantar
  delay(100);
  position();

 
/* // Levantar patas 3 (delantera derecha) y 4 (trasera izquierda) simultáneamente
  moveServo(7,SERVOMAX/1.5);
  delay(1000);
  moveServo(7, SERVOMAX);
  delay(200);
  moveServo(6,SERVOMIN);
  delay(100);
  moveServo(7, SERVOMIN/2);   // Delantera derecha - levantar
  delay(100);
  moveServo(6, SERVOMAX/1.5);
  
  delay(200);
  moveServo(7, 333);   // Delantera derecha - levantar
  
  delay(100);
 // moveServo(2, SERVOMIN);     // Trasera izquierda - levantar
  delay(100);

 
  // Levantar patas 3 (delantera derecha) y 4 (trasera izquierda) simultáneamente
  moveServo(4,SERVOMAX/1.5);
  delay(100);
  
  moveServo(6,SERVOMIN);
  delay(100);
  moveServo(4, SERVOMIN);   // Delantera derecha - levantar
  delay(100);
  moveServo(6, SERVOMAX/1.5);
  
  delay(200);
  moveServo(4, 333);   // Delantera derecha - levantar
  
  delay(100);
 // moveServo(2, SERVOMIN);     // Trasera izquierda - levantar
  delay(100);

  // Mover patas 3 y 4 hacia adelante
  moveServo(FRONT_RIGHT_HIP, 250);   // Delantera derecha - hacia adelante
  moveServo(BACK_LEFT_HIP, 250);     // Trasera izquierda - hacia adelante
  delay(200);

  // Bajar patas 3 y 4
  moveServo(FRONT_RIGHT_HIP, 300);   // Delantera derecha - posición normal
  moveServo(BACK_LEFT_HIP, 300);     // Trasera izquierda - posición normal
  delay(200);

  // Levantar patas 1 (trasera derecha) y 2 (delantera izquierda) simultáneamente
  moveServo(BACK_RIGHT_HIP, 350);    // Trasera derecha - levantar
  moveServo(FRONT_LEFT_HIP, 350);    // Delantera izquierda - levantar
  delay(200);

  // Mover patas 1 y 2 hacia adelante
  moveServo(BACK_RIGHT_HIP, 250);    // Trasera derecha - hacia adelante
  moveServo(FRONT_LEFT_HIP, 250);    // Delantera izquierda - hacia adelante
  delay(200);

  // Bajar patas 1 y 2
  moveServo(BACK_RIGHT_HIP, 300);    // Trasera derecha - posición normal
  moveServo(FRONT_LEFT_HIP, 300);    // Delantera izquierda - posición normal
  delay(200);
*/
  Serial.println("Paso completado");
}
void walkStep2() {
 moveServo(10,SERVOMAX/2);

 delay(100);
 // moveServo(2, SERVOMIN);     // Trasera izquierda - levantar
 moveServo(2,300);
 delay(100);
 moveServo(0,SERVOMAX);
  delay(100);
  moveServo(0,500);
  moveServo(2,400);
  Serial.println("Paso parte 2 completado");
}

void walkStep3() {
  // Levantar patas 3 (delantera derecha) y 4 (trasera izquierda) simultáneamente
  /* moveServo(6,SERVOMAX/2.5);
  delay(200);
  moveServo(4, SERVOMAX/2);
  delay(200);
  moveServo(6,450);
  delay(100);
  moveServo(4, 550);   // Delantera derecha - levantar
  delay(100);
  position();*/
moveServo(9,SERVOMIN*2.5);

 delay(200);
 
 moveServo(10,SERVOMIN*2);
 delay(200);
 moveServo(9,250);
  delay(200);
 moveServo(10,150);
 /*
  moveServo(9,SERVOMAX/4.5);
  delay(200);
  moveServo(10, SERVOMAX/4);
  delay(200);
  moveServo(9,250);
  delay(100);
  moveServo(10, 200);   // Delantera derecha - levantar
  delay(100);
  position();
*/
  Serial.println("Paso completado");
}

void setup() {
  Serial.begin(115200);
  resetPCA9685();
  // Inicializa el PCA9685
  pca9685.begin();
  pca9685.setPWMFreq(60);  // Frecuencia para servos
  delay(10);  // Pausa para asegurarse de que el controlador se inicie correctamente


  // Configurar el NodeMCU como Access Point
  WiFi.softAP(ssid, password);
  Serial.println("IP del NodeMCU:");
  Serial.println(WiFi.softAPIP());

    // Inicializar el pin del sensor SW520D como entrada
  pinMode(tiltSensorPin, INPUT);

server.begin();
  // Ruta principal con un botón para controlar el servo
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", R"rawliteral(
      <!DOCTYPE html>
      <html>
      <body>
       <h1>Control de Robot Cuadrúpedo</h1>
         <button onclick="walkStep()">Caminar un paso</button>

          <button onclick="walkStep2()">Caminar un paso 2</button>
  <button onclick="walkStep3()">Caminar un paso 3</button>

         <h1>Controlar Robot</h1>
        <button onclick="position()">Posición de arranque</button>

        <h1>Controlar Servo y Leer Sensor</h1>
        <button onclick="moveServo0()">Mover Servo0</button>
        <p id="sensorData">Estado del Sensor: </p>

         

        <h1>Controlar Servo</h1>
        <button onclick="moveServo0()">Mover Servo0</button>
        <button onclick="moveServo1()">Mover Servo1</button>
        <button onclick="moveServo2()">Mover Servo2</button>
        
        <button onclick="moveServo5()">Mover Servo5</button>
        <button onclick="moveServo6()">Mover Servo6</button>
        <button onclick="moveServo4()">Mover Servo4</button>

        <button onclick="moveServo9()">Mover Servo9</button>
        <button onclick="moveServo10()">Mover Servo10</button>
        <button onclick="moveServo11()">Mover Servo11</button>
      
        <button onclick="moveServo13()">Mover Servo13</button>
        <button onclick="moveServo14()">Mover Servo14</button>
        <button onclick="moveServo15()">Mover Servo15</button>
        
        
        <script>

           function walkStep() {
            fetch("/walk").then(response => {
            console.log('Paso ejecutado 1');
            });
          }
           
   function walkStep2() {
    fetch("/walk2").then(response => {
      console.log('Paso ejecutado 2');
      });
  }
         function walkStep3() {
    fetch("/walk3").then(response => {
      console.log('Paso ejecutado 3');
      });
  }
         function position() {
            fetch("/position").then(response => {
              return response.text();
            }).then(data => {
              console.log(data);
            }).catch(error => {
              console.error('Error:', error);
            });
            fetch("/position2").then(response => {
              return response.text();
            }).then(data => {
              console.log(data);
            }).catch(error => {
              console.error('Error:', error);
            });
          }

        setInterval(() => {
            fetch("/sensor").then(response => response.text()).then(data => {
              document.getElementById("sensorData").innerText = "Estado del Sensor: " + data;
            });
          }, 1000);
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
          function moveServo4() {
            fetch("/servo4").then(response => {
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


 server.on("/walk", HTTP_GET, [](AsyncWebServerRequest *request){
    walkStep();  // Ejecutar un paso
    request->send(200, "text/plain", "Paso ejecutado");
  });
  server.on("/walk2", HTTP_GET, [](AsyncWebServerRequest *request){
      walkStep2();  // Ejecutar un paso
    request->send(200, "text/plain", "Paso ejecutado");
  });
 server.on("/walk3", HTTP_GET, [](AsyncWebServerRequest *request){
      walkStep3();  // Ejecutar un paso
    request->send(200, "text/plain", "Paso ejecutado");
  });
 // Ruta que lee el estado del sensor SW520D
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    int sensorValue = digitalRead(tiltSensorPin);
    if (sensorValue == HIGH) {
      request->send(200, "text/plain", "Nivel detectado");
    } else {
      request->send(200, "text/plain", "Nivel no detectado");
    }
  });
 // Ruta que activa la secuencia de caminar
  server.on("/position", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Iniciando secuencia...");
    position();  // Llamar a la secuencia de caminar
    request->send(200, "text/plain", "Robot posicionado");
  });
  server.on("/position2", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Iniciando secuencia...");
    position2();  // Llamar a la secuencia de caminar
    request->send(200, "text/plain", "Robot posicionado");
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
    moveServo(1, SERVOMAX);  // Mover servo al ángulo máximo
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
  server.on("/servo4", HTTP_GET, [](AsyncWebServerRequest *request){
    moveServo(4, SERVOMIN);  // Mover servo al ángulo mínimo
    delay(1000);  // Esperar 1 segundo
    moveServo(4, SERVOMAX);  // Mover servo al ángulo máximo
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
