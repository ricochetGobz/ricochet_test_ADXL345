#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const int CERCLE = 0;
const int DEMI_CERCLE = 1;
const int PETALE = 2;
const int LOSANGE = 3;
const int TRIANGLE = 4;
const int VAGUE = 5;

float X;
float Y;
float Z;

int currentFace;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Accelerometer Test");
  Serial.println("");
  
  /* Initialise the sensor */
  if(!accel.begin()) {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  /* Higher values will have a wider measurement range. Lower values will have more sensitivity.*/
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
  // Update cube orientation
  updateCubeOrientation();

  // Checks if a new face is really detected and if it is not the same face
  int faceDetected = getFaceDetected();

  if(faceDetected != -1 && faceDetected != currentFace) {
    currentFace = faceDetected;
    sendNewFace(faceDetected);
  }
  delay(500);
}

void updateCubeOrientation() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);

  X = event.acceleration.x;
  Y = event.acceleration.y;
  Z = event.acceleration.z;
 
  Serial.print("X: "); Serial.print(X); Serial.print(", Z: "); Serial.println(Z); //Serial.print("Y: "); Serial.println(Y);
}

int getFaceDetected() {
  int faceDetected = -1;
  
  // Target Z = 26
  if(Z > 25 && Z < 28) {
    faceDetected = CERCLE; 

  // Target Z = 46
  } else if(Z > 45 && Z < 47) { 
    faceDetected = DEMI_CERCLE;
    
  // Target X = -18
  } else if(X > -19 && X < -17) {
     faceDetected = PETALE;

  // Target X = -4  
  } else if(X > -5 && X < -3) {
    faceDetected = LOSANGE;
    
  // Target X = 5
  } else if(X > 4 && X < 6) {
    faceDetected = TRIANGLE;

  // Target X = -9
  } else if(X > -10 && X < -8) { 
    faceDetected = VAGUE;
  }
  return faceDetected;
}

void sendNewFace(int newFace) {
  Serial.print("New face detected : ");
  switch(newFace) {
    case(CERCLE):
      Serial.println("CERCLE");
      break;
    case(DEMI_CERCLE):
      Serial.println("DEMI_CERCLE");
      break;
    case(PETALE):
      Serial.println("PETALE");
      break;
    case(LOSANGE):
      Serial.println("LOSANGE");
      break;
    case(TRIANGLE):
      Serial.println("TRIANGLE");
      break;
    case(VAGUE):
      Serial.println("VAGUE");
      break;
    default:
      Serial.println("ERROR");
  }
}
