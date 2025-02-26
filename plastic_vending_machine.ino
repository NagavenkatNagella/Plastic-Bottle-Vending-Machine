#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define servo motors
Servo servo1;
Servo servo2;

// Define IR sensor pin
const int irSensorPin = 2;

// Initialize LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define servo motor angles
const int servo1OpenAngle = 90;
const int servo1CloseAngle = 0;
const int servo2OpenAngle = 45;
const int servo2CloseAngle = 0;

void setup() {
    // Attach servos to respective pins
    servo1.attach(5);
    servo2.attach(6);
    
    // Set IR sensor pin as input
    pinMode(irSensorPin, INPUT);
    
    // Initialize LCD
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    
    // Display welcome message
    lcd.clear();
    lcd.print("Welcome to Plastic");
    lcd.setCursor(0, 1);
    lcd.print("Bottle Vending Mach");
    delay(5000);
    
    // Display instruction
    lcd.clear();
    lcd.print("Place the bottle");
    lcd.setCursor(0, 1);
    lcd.print("under sensor");
}

void loop() {
    // Read IR sensor value
    int irState = digitalRead(irSensorPin);
    
    if (irState == LOW) {  // Assuming LOW means object detected
        // Display thank you message
        lcd.clear();
        lcd.setCursor(0, 0);  // Move cursor to the first row
        lcd.print("Thanks for");  // Print first part of the message
        
        lcd.setCursor(5, 1);  // Move cursor to column 5 of the second row
        lcd.print("bottle");
        
        // Rotate first servo to 90 degrees
        servo1.write(servo1OpenAngle);
        delay(1000);
        
        // Return first servo to 0 degrees
        servo1.write(servo1CloseAngle);
        delay(500);
        
        // Display collect reward message
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Collect the");

        lcd.setCursor(0, 1);
        lcd.print("Reward");
        
        // Rotate second servo to 45 degrees
        servo2.write(servo2OpenAngle);
        delay(1000);
        
        // Return second servo to 0 degrees
        servo2.write(servo2CloseAngle);
        delay(500);
        
        // Display thank you message
        lcd.clear();
        lcd.print("Thank You");
        lcd.setCursor(0, 1);
        lcd.print("Welcome Again");
        delay(2000);
        
        // Reset to initial message
        lcd.clear();
        lcd.print("Place the bottle");
        lcd.setCursor(0, 1);
        lcd.print("under sensor");
    }
}
