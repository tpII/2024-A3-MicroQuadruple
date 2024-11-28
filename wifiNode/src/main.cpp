#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

// Configuración WiFi del NodeMCU
const char* ssid = "NodeMCU_AP";
const char* password = "12345678";

// Asignación de servos para las patas
#define FRONT_LEFT_HIP 6
#define FRONT_LEFT_KNEE 4
#define FRONT_RIGHT_HIP 9
#define FRONT_RIGHT_KNEE 10
#define BACK_LEFT_HIP 14
#define BACK_LEFT_KNEE 15
#define BACK_RIGHT_HIP 0
#define BACK_RIGHT_KNEE 2


// Instancia del PCA9685 y el servidor web
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();
AsyncWebServer server(80);

// Definir rango del servo
#define SERVOMIN 150  // Ancho de pulso mínimo (ángulo 0 grados)
#define SERVOMAX 600  // Ancho de pulso máximo (ángulo 180 grados)

// Variables para la secuencia de movimiento
enum RobotState {
  IDLE,
  WALKING
};
RobotState currentState = IDLE;

int sequenceStep = 0;  // Controla la secuencia de movimiento
unsigned long movementStartTime = 0; // Tiempo de inicio de cada movimiento
int movementDelay = 300;  // Tiempo entre movimientos en ms

// Función para inicializar el PCA9685
void initPCA9685() {
  Wire.begin();
  pca9685.begin();
  pca9685.setPWMFreq(60);  // Frecuencia de 60Hz para servos
}

// Función para mover un servo
void moveServo(uint8_t num, uint16_t position) {
  pca9685.setPWM(num, 0, position);
}
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

// Secuencia de caminar completa
void walkSequence() {
  switch (sequenceStep) {
    case 0:  // Levantar patas 1 (trasera derecha) y 3 (delantera izquierda)
      
     
      moveServo(FRONT_LEFT_HIP, SERVOMAX);  // 6
      delay(100);
      moveServo(FRONT_LEFT_KNEE, SERVOMAX/2.5);  // 4
      delay(100);
      moveServo(FRONT_LEFT_HIP, 450);  // 6
      delay(100);
      moveServo(FRONT_LEFT_KNEE, 550);  // 4
      
      movementStartTime = millis();
      sequenceStep++;
      break;

    case 1:  // Mover patas 1 y 3 hacia adelante
      if (millis() - movementStartTime >= movementDelay) {
        /*#define BACK_RIGHT_HIP 0
          #define BACK_RIGHT_KNEE 2 */
        moveServo(BACK_RIGHT_KNEE, 300);  // 2
        delay(100);
        moveServo(BACK_RIGHT_HIP, SERVOMAX);   // 0
        delay(100);
        moveServo(BACK_RIGHT_HIP, 500);   // 0
        delay(100);
        moveServo(BACK_RIGHT_KNEE, 400);  // 2
        delay(100);
       
        movementStartTime = millis();
        sequenceStep++;
      }
      break;

    case 2:  // Bajar patas 1 y 3
      if (millis() - movementStartTime >= movementDelay) {
        /*#define FRONT_RIGHT_HIP 9
          #define FRONT_RIGHT_KNEE 10*/
        moveServo(FRONT_RIGHT_HIP, SERVOMIN*2);  //9
        delay(100);
        moveServo(FRONT_RIGHT_KNEE, SERVOMIN*2); //10
        delay(100);
        moveServo(FRONT_RIGHT_HIP, 250);  //9
        delay(100);
        moveServo(FRONT_RIGHT_KNEE, 150); //10
        delay(100);
        
        movementStartTime = millis();
        sequenceStep++;
      }
      break;

    case 3:  // Levantar patas 2 (trasera izquierda) y 4 (delantera derecha)
      if (millis() - movementStartTime >= movementDelay) {
        /*#define BACK_LEFT_HIP 14
          #define BACK_LEFT_KNEE 15*/
          moveServo(BACK_LEFT_KNEE, SERVOMAX/2.5); // 15
          delay(100);
          moveServo(BACK_LEFT_HIP,SERVOMAX/2);//14
          delay(100);
          moveServo(BACK_LEFT_KNEE, 450); // 15
          delay(100);
          moveServo(BACK_LEFT_HIP,550);//14
          delay(100);
          
        movementStartTime = millis();
        sequenceStep++;
      }
      break;

    case 4:  // Mover patas 2 y 4 hacia adelante
      /*if (millis() - movementStartTime >= movementDelay) {
        moveServo(BACK_LEFT_HIP, 250);   // Mover hacia adelante
        moveServo(FRONT_RIGHT_HIP, 250); // Mover hacia adelante
        movementStartTime = millis();
        
      }*/
     sequenceStep++;
      break;

    case 5:  // Bajar patas 2 y 4
      if (millis() - movementStartTime >= movementDelay) {
        moveServo(BACK_LEFT_KNEE, 450);  // Extender rodilla pata 2
        moveServo(FRONT_RIGHT_KNEE, 450); // Extender rodilla pata 4
        movementStartTime = millis();
        sequenceStep = 0;  // Reinicia la secuencia
        currentState = IDLE;
        Serial.println("Secuencia de caminar completada");
      }
      break;
  }
}

// Configuración inicial
void setup() {
  Serial.begin(115200);
  initPCA9685();

  // Configuración de Access Point
  WiFi.softAP(ssid, password);
  Serial.println("IP del NodeMCU:");
  Serial.println(WiFi.softAPIP());

  // Configuración de rutas del servidor
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", R"rawliteral(
      <!DOCTYPE html>
      <html>
      <body>
        <h1>Control de Robot Cuadrúpedo</h1>
        <button onclick="startWalk()">Iniciar caminar</button>
         <button onclick="position()">Posición de arranque</button>

        <script>
          function startWalk() {
            fetch('/startWalk').then(response => console.log('Iniciando caminar'));
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

        </script>
      </body>
      </html>
    )rawliteral");
  });

  server.on("/startWalk", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (currentState == IDLE) {
      currentState = WALKING;
      sequenceStep = 0;
      request->send(200, "text/plain", "Secuencia de caminar iniciada");
    } else {
      request->send(200, "text/plain", "Robot ocupado");
    }
  });
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

  // Iniciar el servidor
  server.begin();
}

// Bucle principal
void loop() {
  if (currentState == WALKING) {
    walkSequence();
  }
}
