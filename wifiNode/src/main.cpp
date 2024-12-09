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
#define BACK_LEFT_KNEE 14
#define BACK_LEFT_HIP 15
#define BACK_RIGHT_HIP 0
#define BACK_RIGHT_KNEE 2


int currentServo = -1; // Servo actualmente moviéndose, -1 significa ninguno

// Pines del SW-520D
const int tiltSensorPin = D5;  // GPIO pin para el sensor de nivel (SW520D)

// Instancia del PCA9685 y el servidor web
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();
AsyncWebServer server(80);

// Definir rango del servo
#define SERVOMIN 150  // Ancho de pulso mínimo (ángulo 0 grados)
#define SERVOMAX 600  // Ancho de pulso máximo (ángulo 180 grados)

// Variables para la secuencia de movimiento
enum RobotState {
  IDLE,
  WALKING,
  TILTING
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
  currentServo = num; // Actualizar el servo actual
  pca9685.setPWM(num, 0, position);
  currentServo = -1; // Restablecer el servo actual
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

int walkRepeats = 0; // Número de repeticiones completadas
const int maxRepeats = 3; // Número total de repeticiones deseadas
// Secuencia de caminar completa
void walkSequence() {

 if (walkRepeats >= maxRepeats) { // Si se completaron las repeticiones, reiniciar estado
    currentState = IDLE;
    Serial.println("Secuencia de caminar completada.");
    walkRepeats = 0; // Reiniciar contador para próximas ejecuciones
    return;
  }

  switch (sequenceStep) {
    case 0:  // mover la pata delantera izquierda
      
     
      moveServo(FRONT_LEFT_HIP, SERVOMAX/2.5);  // 6
      delay(100);
      moveServo(FRONT_LEFT_KNEE, SERVOMAX/2);  // 4
      delay(100);
      moveServo(FRONT_LEFT_HIP, 450);  // 6
      delay(100);
      moveServo(FRONT_LEFT_KNEE, 550);  // 4
      position();
      movementStartTime = millis();
      sequenceStep++;
      break;

    case 1:  // mover la pata trasera derecha
      if (millis() - movementStartTime >= movementDelay) {
        /*#define BACK_RIGHT_HIP 0
          #define BACK_RIGHT_KNEE 2 */
          moveServo(4, 650);
          moveServo(10,150);
          delay(200);
        moveServo(BACK_RIGHT_KNEE, 300);  // 2
        delay(100);
        moveServo(BACK_RIGHT_HIP, 700);   // 0 antes srvomax
        delay(100);
        moveServo(BACK_RIGHT_HIP, 500);   // 0
        delay(100);
        moveServo(BACK_RIGHT_KNEE, 400);  // 2
        delay(100);
          
          moveServo(4, 600);
          moveServo(10,200);
          position2();
        movementStartTime = millis();
        sequenceStep++;
      }
      break;

    case 2:  // mover la pata delantera derecha
      if (millis() - movementStartTime >= movementDelay) {
        /*#define FRONT_RIGHT_HIP 9
          #define FRONT_RIGHT_KNEE 10*/
       /*moveServo(FRONT_RIGHT_HIP, SERVOMIN*2);  //9
        delay(100);
        moveServo(FRONT_RIGHT_KNEE, SERVOMIN*2); //10
        delay(100);
        moveServo(FRONT_RIGHT_HIP, 250);  //9
        delay(100);
        moveServo(FRONT_RIGHT_KNEE, 150); //10
        delay(100);*/
        moveServo(BACK_RIGHT_KNEE, 300); //nuevo inclinacion en para derecha trassera para que la pata derecha delantera toque bien el suelo

         moveServo(FRONT_RIGHT_HIP, 550);  //9
        delay(100);
        moveServo(FRONT_RIGHT_KNEE, 300); //10
        delay(100);
        moveServo(FRONT_RIGHT_HIP, 250);  //9
        delay(100);
        moveServo(FRONT_RIGHT_KNEE, 300); //10

        moveServo(BACK_RIGHT_KNEE, 400); //nuevo antes nada acomodo el pie trasero
        delay(100);
        movementStartTime = millis();
        sequenceStep++;
      }
      break;

    case 3:  // Lmover la pata trasera izquierda
      if (millis() - movementStartTime >= movementDelay) {
        /*#define BACK_LEFT_HIP 14
          #define BACK_LEFT_KNEE 15*/
          moveServo(4, 650);
          moveServo(10,150);
          delay(100);
           moveServo(BACK_LEFT_KNEE, 500); // 15 antes 240
          delay(100);
        
          moveServo(BACK_LEFT_HIP,350);//14 antes 300
          delay(100);
        
   
          moveServo(BACK_LEFT_KNEE, 450); // 15 antes 300
         moveServo(BACK_LEFT_HIP,400);//14 antes 500

          
          position2(); //nuevo antes nada acomodo los pies traseros ver si se lelga a ejecutar todo
           moveServo(4, 600);
          moveServo(10,200);
        movementStartTime = millis();
        sequenceStep = 0;  // Reinicia la secuencia
        position();//nuevo
        position2();//nuevo
        walkRepeats++; // Incrementar el contador de repeticiones
        Serial.print("Repetición ");
        Serial.print(walkRepeats);
        Serial.println(" completada.");/*
        currentState = IDLE;
        Serial.println("Secuencia de caminar completada");*/
      }
      break;

    
  }
}


// Función para inclinarse
void tiltRobot() {
  currentState = TILTING;

/* moveServo(4, 600);  // pos inciial 
   moveServo(10, 200);  */
  // Configurar ángulos iniciales
  int angleFrontLeft = 600;  // Ángulo inicial de 90 grados
  int angleFrontRight = 200; // Ángulo inicial de 90 grados

  //int angleBackLeft = 450;  // Ángulo inicial hip 15
  //int angleBackRight = 500; // Ángulo inicial hip 0

  int angleFrontLeftHip = 450;  // Ángulo inicial hip 15
  int angleFrontRightHip = 300; // Ángulo inicial hip 0
  // Bajar las patas delanteras hasta que el SW-520D detecte inclinación
  do {
    angleFrontLeft += 10;  // Bajar la pata delantera izquierda
    angleFrontRight -= 10; // Bajar la pata delantera derecha

   // angleBackLeft -=10;
   // angleBackRight +=10; 

    angleFrontLeftHip += 10;  // Bajar la pata delantera izquierda
    angleFrontRightHip -= 10; // Bajar la pata delantera derecha
  //  if (angleBackLeft >= 400) angleBackLeft = 400;
   // if (angleBackRight >= 600) angleBackRight = 600;
    
    // Límite de ángulo para no exceder
   /* if (angleFrontLeft >= SERVOMAX+100) angleFrontLeft = SERVOMAX;
    if (angleFrontRight >= SERVOMIN-100) angleFrontRight = SERVOMAX;
    */
    // Mover los servos
    moveServo(4, angleFrontLeft);
    moveServo(10, angleFrontRight);
    
    /*moveServo(15, angleBackLeft);
    moveServo(0, angleBackRight);
    */
    moveServo(FRONT_LEFT_HIP, angleFrontLeftHip);
    moveServo(FRONT_RIGHT_HIP, angleFrontRightHip);
    
    delay(50); // Pequeña pausa para movimientos suaves

  } while (digitalRead(tiltSensorPin) == LOW); // Continuar hasta detectar inclinación

  Serial.println("Robot inclinado. Nivel detectado.");
  currentState = IDLE;
  position();

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
    <html lang="es">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Control del Robot Arduino</title>
      <style>
         body {
    font-family: 'Verdana', sans-serif;
    background-color: #fce4ec;
    margin: 0;
    padding: 20px;
    display: flex;
    flex-direction: column;
    align-items: center;
    color: #6f2c91;
  }

  h1 {
    color: #ad4b99;
    margin-bottom: 20px;
  }

  .button {
    background-color: #ff6f61;
    border: none;
    color: white;
    padding: 15px 25px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 18px;
    margin: 10px;
    cursor: pointer;
    border-radius: 30px;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    transition: background-color 0.3s, transform 0.2s;
  }

  .button:hover {
    background-color: #e65c5c;
    transform: translateY(-2px);
  }

  .servo-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    margin-top: 20px;
  }

  .servo-row {
    display: flex;
    justify-content: center;
    margin-bottom: 10px;
  }

  .servo {
    width: 60px;
    height: 60px;
    background-color: #fff0f5;
    border: 1px solid #ff77a6;
    border-radius: 15px;
    margin: 5px;
    display: flex;
    align-items: center;
    justify-content: center;
    box-shadow: 0 2px 6px rgba(255, 105, 180, 0.3);
    transition: background-color 0.3s;
  }

  .servo.active {
    background-color: #ff4081; /* Color activo */
    color: white;
    box-shadow: 0 0 15px rgba(255, 64, 129, 0.9); /* Resalte dinámico */
    font-weight: bold;
  }
        .sensor-output {
          background-color: #fff;
          border: 1px solid #ffd1dc;
          border-radius: 15px;
          padding: 20px;
          margin-top: 20px;
          width: 350px;
          text-align: center;
          box-shadow: 0 4px 12px rgba(255, 105, 180, 0.5);
        }
        .sensor-title {
          font-size: 24px;
          color: #ad4b99;
          margin-bottom: 10px;
        }
        .sensor-state {
          font-size: 32px;
          font-weight: bold;
          color: #ff4081;
        }
        
        .status { font-size: 24px; margin: 20px 0; }
        

      </style>
    </head>
      <body>
        <h1>Control de Robot Cuadrúpedo</h1>
        <button class="button" onclick="startWalk()">Iniciar caminar</button>
        <button class="button" onclick="position()">Posición de arranque</button>
        <button class="button" onclick="startTilt()">Inclinarse</button>
       
        <div class="sensor-output">
          <div class="sensor-title">Sensor de Nivel (activo: 30°)</div>
          <div class="sensor-state" id="nivel">
            <p id="sensorData"> </p>


        </div>
        </div>
         
        
       <div id="servoContainer"></div>
        
        <script>

          setInterval(() => {
            fetch("/sensor").then(response => response.text()).then(data => {
              document.getElementById("sensorData").innerText = "" + data;
            });
          }, 1000);

         function updateSensorState() {
            fetch('/sensor')
              .then(response => response.text())
              .then(state => {
                const sensorStateElement = document.getElementById('sensorState');
                sensorStateElement.textContent = state === "0" ? "Nivelado" : "Inclinación Detectada";
              })
              .catch(error => console.error('Error al consultar el sensor:', error));
          }
        function startTilt() {
          fetch('/tilt').then(() => console.log('Inclinación iniciada'));
        }
// Obtener el contenedor principal
const servoContainer = document.getElementById("servoContainer");

// Orden de los servos (en filas)
const servoOrder = [
  [1, 5, 11, 13], // Primera fila
  [0, 6, 9, 15],  // Segunda fila
  [2, 4, 10, 14]  // Tercera fila
];

// Crear las filas de servos
servoOrder.forEach((nivel) => {
  const fila = document.createElement("div");
  fila.className = "servo-row";

  nivel.forEach((id) => {
    const servo = document.createElement("div");
    servo.className = "servo";
    servo.id = `servo${id}`; // ID único para cada servo
    servo.innerText = `Servo ${id}`;
    fila.appendChild(servo);
  });

  servoContainer.appendChild(fila);
});

// Resaltar dinámicamente el servo activo
function resaltarServoActivo() {
  fetch('/currentServo') // Consultar el servo activo desde el servidor
    .then((response) => response.text())
    .then((servoActual) => {
      const servos = document.querySelectorAll(".servo");
      servos.forEach((servo) => servo.classList.remove("active")); // Quitar cualquier resaltado previo

      if (servoActual !== "-1") { // Si hay un servo activo
        const servoActivo = document.getElementById(`servo${servoActual}`);
        if (servoActivo) {
          servoActivo.classList.add("active"); // Agregar la clase activa
        }
      }
    })
    .catch((error) => console.error('Error al obtener el servo activo:', error));
}

// Actualizar el resaltado periódicamente
setInterval(resaltarServoActivo, 200); // Llamar cada 200ms

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
server.on("/currentServo", HTTP_GET, [](AsyncWebServerRequest *request) {
  Serial.print("Servo activo: ");
  Serial.println(currentServo); // Muestra el valor en la consola serial
  request->send(200, "text/plain", String(currentServo)); // Devuelve el valor al cliente
});

   server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request) {
    int sensorValue = digitalRead(tiltSensorPin);
    if (sensorValue == HIGH) {
      request->send(200, "text/plain", "Nivel detectado");
    } else {
      request->send(200, "text/plain", "Nivel no detectado");
    }
  });


 server.on("/tilt", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (currentState == IDLE) {
      tiltRobot();
      request->send(200, "text/plain", "Inclinación completada");
    } else {
      request->send(200, "text/plain", "Robot ocupado");
    }
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
