
// Declaración de librerías para sensores y GPS.
#include "Adafruit_Sensor.h" 
#include "SparkFun_TB6612.h" //Driver de motores
#include "Adafruit_MPU6050.h" //IMU
#include "Adafruit_BMP085.h" //Barometro
#include "Adafruit_HMC5883_U.h" //Magnetometro
#include "Adafruit_GPS.h" //GPS

// Constantes, variables, instancias para motores.
#define AIN1 17
#define BIN1 15
#define AIN2 18
#define BIN2 14
#define PWMA 19
#define PWMB 13
#define STBY 16
const int offsetA = 1; 
const int offsetB = 1;
  Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
  Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

//Constantes, variables, instancias para IMU.
float Ax, Ay, Az, Gx, Gy, Gz, temperaturaMPU;
  Adafruit_MPU6050 mpu;

//Constantes, variables, instancias para barómetro.
float alturaRelativa, alturaAbsoluta, presionBarometrica;
float muestraPresion, temperaturaBMP;
boolean banderaPresionSuelo = false;
  Adafruit_BMP085 bmp;

//Constantes, variables, instancias para magnetómetro.
float heading, declinacionMagnetica = 0.1745329252; //En grados = +10° 39'
float magX, magY, magZ;
  Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

//Constantes, variables, instancias para GPS.
#define GPSSerial Serial1
#define GPSECHO false
float latitud, longitud, satelites;
uint32_t timer = millis();
  Adafruit_GPS GPS(&GPSSerial);

//Constantes, variables, instancias para comeback.
float latitudObjetivo = 0.0, longitudObjetivo = 0.0; //Se ingresan manual
float headingObjetivo = 0.0, distanciaObjetive = 0.0; //Se calculan

//Constantes, variables, instancias para aterrizaje;
boolean banderaAterrizaje = false, banderaElevacionPositiva = false, banderaGiroscopio = false;
boolean banderaElevacionNegativa = false, banderaMovimiento = false;
float alturaMaxima = 1000.0;
uint16_t contadorAscenso = 0, contadorDescenso = 0;
uint32_t timer2 = millis();

void setup(){
  //Inicializar IMU, Barometro, magnetometro, GPS y comunicacion Serial.
  Serial.begin(115200);
  GPS.begin(9600); //Para GPS GPIO0(TX) Y GPIO1(RX) 
  mpu.begin(); 
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  bmp.begin();
  mag.begin();
}

void loop(){
  imu();
  brujula();
  barometro();
  ubicacion();
  
  if (millis() - timer2 > 1000 && banderaMovimiento == false) //Comprobar cambios de altura cada 1s
    elevationCheck();

  ruta();
  if (banderaMovimiento == true)
    returnHome();
}

void returnHome(){

  if (distanciaObjetive > 3) {
    if (headingObjetivo > heading + 1){
      right(motor1, motor2, 255);
    }

    if (headingObjetivo < heading - 1){
      left(motor1, motor2, 255);
    }

    if (headingObjetivo < heading + 2 && headingObjetivo > heading - 1){
      forward(motor1, motor2, 255);
    }
  }

    if (distanciaObjetive < 3) {
      motor2.drive(255,3000);
      motor1.drive(-255,3000);
      motor2.brake();
      motor1.brake();
      delay(60000);
  }

}
