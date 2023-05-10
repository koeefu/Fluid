/************ ir sensor part ************/
// variables will change:
int sensorState = 0, lastState = 0;

//led pin
int LED1 = 8;
int LED2 = 5;
// int swi_led = 7;

int IR = A1;
int thre_ir = 80;

float irValue;

float cross;

// int light_swi;

/************ pulse sensor variables ************/
// int pulseSensor = A5;
int LED13 = 12;

int Signal;
int Threshold = 20;

float lightValue;
int lightState;

void setup() {
  Serial.begin(9600);

  /************ ir sensor part **********/
  // initialize the LED pin as an output:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  /************ light sensor part ************/
  pinMode(LED13, OUTPUT);
}

void loop() {
  ir_sensor();

  //monitor
  int IRBBState = analogRead(IR);  // read the value of IR Break Beam A1
  delay(1);
  int lightSwitch = analogRead(A2);  // read the value of second light sensor switch
  delay(1);
  int lightState = analogRead(A0);  // read the value of light sensor

  /******************** threshold for ir sensor ********************/
  if (sensorState > 100) {
    irValue = 1;
    // Serial.print(irValue);
  } else if (sensorState == 0) {
    irValue = 1;
    // Serial.print(irValue);
  } else {
    irValue = 10000;
  }
  Serial.print(irValue);
  Serial.print(",");

  // Serial.print(sensorState);
  // Serial.print(",");

  // Serial.print(Signal);
  // Serial.print(",");

  // Serial.print(lightState);
  // Serial.print(",");

  /***************** light switch *******************/
  // if (lightSwitch > 320) {
  //   light_swi = 1;
  //   digitalWrite(swi_led, HIGH);
  //   // delay(100);
  // } else {
  //   light_swi = 0;
  //   digitalWrite(swi_led, LOW);
  //   // delay(100);
  // }

  // Serial.print(light_swi);
  // Serial.print(",");

  /******************* threshold for lightsensor *******************/
  if (lightState > 500) {
    lightValue = map(lightState, 500, 850, 0.1, 10);
    cross = 0.3;
    digitalWrite(LED13, HIGH);
  } else {
    lightValue = 0.1;
    cross = 1;
    digitalWrite(LED13, LOW);
  }
  Serial.print(cross);
  Serial.print(",");
  Serial.println(lightValue);
  delay(1);
  //delay(500);
}

void ir_sensor() {
  // read the state of the pushbutton value:
  sensorState = analogRead(IR);
  //Serial.println(sensorState);

  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState < 50) {
    // turn LED on:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(500);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(500);
  }

  lastState = sensorState;

  // int lightSensor = analogRead(A0);
  // delay(1);
}