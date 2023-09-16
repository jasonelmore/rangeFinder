
#include <SR04.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <Servo.h>
//Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
//int pos = 0; //variable to store the servo position

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
//#define ECHO_PIN 18
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

#define SOUND_SPEED 0.0343
#define SOUND_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
delay(500);
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
  
   // Clear the buffer
  //display.clearDisplay();

//  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
//   Serial.begin(38400);
   //delay(1000);
}

void loop() {

  //clears the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  //sets the TRIG_PIN to a high state for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  //reads the echopin and returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  //calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  //converts to inches
  distanceInch = distanceCm * SOUND_INCH;
  
  //Clears display and sets text size and cursor position
  //display.clearDisplay();
  //delayMicroseconds(10);
  //display.setTextSize(1); //Normal 1:1 pixel scale
 // display.setCursor(0,0);
 
  //Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  //Displays the results onto the OLED Screen
  display.clearDisplay();
  display.setCursor(0, 12);
  //Displays distance in CM
  display.print(distanceInch);
  display.print(" inch");

  //Display distance in inches
  //display.print(distanceInch);
  //display.print(" Inch")
  display.display();
  delay(500);
  
}
