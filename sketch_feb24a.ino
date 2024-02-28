const int RGB_RED_PIN = 3;
const int RGB_GREEN_PIN = 5;
const int RGB_BLUE_PIN = 6; //utilizes these three pins due to the analogue nature
const int DELAY_MS = 5;
const int trigPin=9;
const int echoPin=10;
const int FAN_PIN=11;

int redVal = 0;
int greenVal = 0;
int blueVal = 0;
String cat ; //var for the received data from browser
int nyanCat=0; //parsed to int
float brightnessFraction = 1.0;

void setup() {
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT); // Set the trig pin as an output
  pinMode(echoPin, INPUT); //Set the echo pin as input
  pinMode(FAN_PIN, OUTPUT); //set the FanPin as output
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { //if serial is available
    cat = Serial.readStringUntil('\n'); //get input to \n char
    nyanCat=cat.toInt(); //cat == 0 or 1
    delay(DELAY_MS);
   // Serial.println(nyanCat); Cant print to console, in this case will print to browser side.
  }
 
  if(nyanCat == 1){ //if button send 1, start state, will commence programs
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2);  
    digitalWrite(trigPin, HIGH);  
    delayMicroseconds(10);  
    digitalWrite(trigPin, LOW);  //reset steps for calibrate the sensor
    long duration = pulseIn(echoPin, HIGH); //calculate the duration
    float distance_cm = duration * 0.0343 / 2; //converse to cm
    Serial.print("Distance: "); //print distance to double check
    Serial.print(distance_cm);
    Serial.println(" cm");
 
  
    if (distance_cm > 30) {
      // Turn on the fan if distance is larger than 30cm
      digitalWrite(FAN_PIN, HIGH);
      for(int i=0;i<256;i++){ //wrote a loop to circle different colors
        setRGBLedColorAndBrightness(i, (i+125)%255, (i+62)%255, brightnessFraction);
        delay(DELAY_MS);
      }
    }
    else if (distance_cm<=30 && distance_cm>10) {
      // Turn  the fan to half speed
      analogWrite(FAN_PIN, 122);
      setRGBLedColorAndBrightness(0, 255, 0, brightnessFraction); //light up green light
    }
    else{
      digitalWrite(FAN_PIN, LOW); //turn off the fan
      setRGBLedColorAndBrightness(0, 0, 255, brightnessFraction); //light up red light
    }
  }
  else{
    setRGBLedColorAndBrightness(0, 0, 0, brightnessFraction); //turn off LED
    digitalWrite(FAN_PIN, nyanCat); //turn off fan
    delay(DELAY_MS);
  }
  
}


//function for generating color
void setRGBLedColorAndBrightness(int red, int green, int blue, float brightness_fraction){
  int r_real = red * brightness_fraction;
  int g_real = green * brightness_fraction;
  int b_real = blue * brightness_fraction;

  analogWrite(RGB_RED_PIN, r_real);
  analogWrite(RGB_GREEN_PIN, g_real);
  analogWrite(RGB_BLUE_PIN, b_real);
}
