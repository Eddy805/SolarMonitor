/*
 *  SolarMonitor.h
 *  
 *  Monitoring solution for solar system
 *  
 */

#define LVPIN A0                              // load voltage pin
#define LCPIN A1                              // load current pin
#define SVPIN A2                              // solar voltage pin
#define SCPIN A3                              // solar current pin
#define BVPIN A4                              // battery voltage pin
#define BCPIN A5                              // battery current pin

#define VOLTAGELO     0                       // voltage for analogRead = 0     (in .1 V, 10 = 1V)
#define VOLTAGEHI   250                       // voltage for analogRead = 1023  (in .1 V)
#define CURRENTLO -2000                       // current for analogRead = 0     (in mA)
#define CURRENTHI  2000                       // current for analogRead = 1023  (in mA)

#define READINTERVAL 10000                    // read interval in milliseconds

#define DEBUG 1                               // comment to turn off debugging

int loadVoltage, loadCurrent;                 // variables for sensor-values
int solarVoltage, solarCurrent;               //
int batteryVoltage, batteryCurrent;           //

unsigned long currentMillis, previousMillis;  // variables for time management

/*******************************************************************************
 *  formatValue
 *  
 *  format value as string (dest), depending on unit
 *  
 */

void formatValue(char *dest, int value, char unit) {
  char valueStr[5];
 
  switch (unit) {
    case 'A':   // ampere, input is in mA
      sprintf(dest, "%d mA", value);
      break;
    case 'V':   // volt, input is in .1 V
      dtostrf(.1 * value, 4, 1, valueStr);
      sprintf(dest, "%s V", valueStr);
      break;
    default:
      sprintf(dest, "???");
      break;
  } 
}

/******************************************************************************* 
 *  readVoltage, readCurrent
 *  
 *  read voltage/current from pin
 */

int readVoltage(int pin){
  int value;
  
  value = analogRead(pin);

#ifdef DEBUG
  Serial.print("readVoltage (pin, value): ");
  Serial.print(pin);
  Serial.print(", ");
  Serial.println(value);
#endif

  return map(value, 0, 1023, VOLTAGELO, VOLTAGEHI);  
}

int readCurrent(int pin){
  int value;
  
  value = analogRead(pin);

#ifdef DEBUG
  Serial.print("readCurrent (pin, value): ");
  Serial.print(pin);
  Serial.print(", ");
  Serial.println(value);
#endif

  return map(value, 0, 1023, CURRENTLO, CURRENTHI);  
}

/******************************************************************************* 
 *  readValues
 *  
 *  read values from sensor pins
 */

void readValues() {
  char tmp[16];
  
  Serial.print("Reading load voltage... ");
  loadVoltage = readVoltage(LVPIN);
  formatValue(tmp, loadVoltage, 'V');
  Serial.println(tmp);
  
  Serial.print("Reading load current... ");
  loadCurrent = readCurrent(LCPIN);
  formatValue(tmp, loadCurrent, 'A');
  Serial.println(tmp);

  Serial.print("Reading battery voltage... ");
  batteryVoltage = readVoltage(BVPIN);
  formatValue(tmp, batteryVoltage, 'V');
  Serial.println(tmp);
  
  Serial.print("Reading battery current... ");
  batteryCurrent = readCurrent(BCPIN);
  formatValue(tmp, batteryCurrent, 'A');
  Serial.println(tmp);

  Serial.print("Reading solar voltage... ");
  solarVoltage = readVoltage(SVPIN);
  formatValue(tmp, solarVoltage, 'V');
  Serial.println(tmp);
  
  Serial.print("Reading solar current... ");
  solarCurrent = readCurrent(SCPIN);
  formatValue(tmp, solarCurrent, 'A');
  Serial.println(tmp);
}

/*******************************************************************************
 *  setup
 */

void setup() {

  // Initialize measurements

  loadVoltage = 0;
  loadCurrent = 0;
  solarVoltage = 0;
  solarCurrent = 0;
  batteryVoltage = 0;
  batteryCurrent = 0;

  // Initialize time

  previousMillis = 0;

  // Initialize serial communication

  Serial.begin(9600);
  Serial.println("*** SolarMonitor started ***");

#ifdef DEBUG
  Serial.print("Sample interval (seconds): ");
  Serial.println(.001 * READINTERVAL);
  Serial.print("Voltage mapping LO (V): ");
  Serial.println(.1 * VOLTAGELO, 1);
  Serial.print("Voltage mapping HI (V): ");
  Serial.println(.1 * VOLTAGEHI, 1);
  Serial.print("Current mapping LO (mA): ");
  Serial.println(CURRENTLO);
  Serial.print("Current mapping HI (mA): ");
  Serial.println(CURRENTHI);    
#endif  
  
  // Initialize WIFI
  // @TODO

  // Initialize MQTT
  // @TODO
  
}

void loop() {
  currentMillis = millis();
  if (currentMillis > previousMillis + READINTERVAL || currentMillis < previousMillis) {    // is it time to process?
    previousMillis = currentMillis;
    readValues();
    
    #ifdef DEBUG
      Serial.print("Loop processtime (msec): ");
      Serial.println(millis() - currentMillis);
    #endif
  }
}
