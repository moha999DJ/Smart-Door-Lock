#include <LiquidCrystal.h>

#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_sv_SE.h>

#include <Keypad.h> // the library for the 4x4 keypad
#include <LiquidCrystal_I2C.h> // the library for the i2c 1602 lcd
#include <Servo.h> // the library to control the servo motor
LiquidCrystal_I2C lcd(0x27,20,4); // gets the lcd 
Servo servo;

#define Password_Length 8 // the length of the password, if the password is 4 digits long set this to 5
int Position = 0; // position of the servo
char Particular[Password_Length]; // the password length 
char Specific[Password_Length] = "1A2B3C4"; // the password which is called specific in the code, change this to anything you want with the numbers 0-9 an dthe letters A-D
byte Particular_Count = 0, Specific_Count = 0; // counts the amount of digits and and checks to see if the password is correct
char Key; 
const byte ROWS = 4; // the amount of rows on the keypad
const byte COLS = 4; // the amount of columns on the keypad
char keys[ROWS][COLS] = { // sets the rowns and columns
  // sets the keypad digits
  {'1','2','3','A'}, 
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
bool SmartDoor = true; // the servo 
// the pins to plug the keypad into
byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2, 1}; 
Keypad myKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); // gets the data from the keypad

// locked charcater
byte Locked[8] = { 
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111
};
// open character
byte Opened[8] = {
  B01110,
  B00001,
  B00001,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111
};
void setup()
{
  servo.attach(0); // attaches the servo to pin 0
  ServoClose(); // closes the servo when you say this function
  lcd.init(); // initializes the lcd 
  lcd.backlight(); // turns on the backlight
  lcd.setCursor(0,0); // sets the cursor on the lcd
  lcd.print("HAMA DJEOUADI :)"); // prints the text/charater
  lcd.setCursor(6,1); // sets the cursor on the lcd
  lcd.print("Door!"); // prints text
  delay(4000); // waits 4 seconds
  lcd.clear(); // clears the lcd diplay

}

void loop()
{
  if (SmartDoor == 0) // opens the smart door
  {
    Key = myKeypad.getKey(); // the word key = myKeypad which gets the value

    if (Key == '#') // when the '#' key is pressed

    {
      lcd.clear(); // clears the lcd diplay
      ServoClose(); // closes the servo motor
      lcd.setCursor(2,0); // sets the cursor on the lcd
      lcd.print("Door Closed"); // prints the text to the lcd
      lcd.createChar(0, Locked); // prints the locked character 
      lcd.setCursor(14,0); // sets the cursor on the lcd
      lcd.write(0); // prints the first character when you are on the door closed page
      delay(3000); // waits 3 seconds
      SmartDoor = 1; // closes the door
    }
  }

  else Open(); // keeps the door open
}

void clearData() // clears the data
{
  while (Particular_Count != 0) // counts the digits pressed
  {
    Particular[Particular_Count--] = 0; // counts how many digits
  }
  return; // returns the data
}

void ServoOpen() // opens the servo
{
  for (Position = 180; Position >= 90; Position -= 5) { // moves from 0 to 180 degrees
    servo.write(Position); // moves to the postion
    delay(15); // waits 15 milliseconds
  }
}

void ServoClose() // closes the servo
{
  for (Position = 90; Position <= 180; Position += 5) { // moves from position 0 to 180 degrees
    servo.write(Position); // moves to the position
    delay(15); // waits 15 milliseconds
  }
}

void Open() // function declarations
{
  lcd.setCursor(1,0); // sets the cursor on the lcd
  lcd.print("Enter Password"); // prints the text
  
  Key = myKeypad.getKey(); // gets the keys you press from the keypad
  if (Key)
  {
    Particular[Particular_Count] = Key; 
    lcd.setCursor(Particular_Count, 1); // sets the cursor on the lcd
    lcd.print("*"); // prints '*' instead of the password
    Particular_Count++; // counts the length of the password
  }

  if (Particular_Count == Password_Length - 1) // gets the length of the password 
  {
    if (!strcmp(Particular, Specific)) // counts the length and checks to see if the password is correct
    {
      lcd.clear();
      ServoOpen(); // moves the servo 180 degrees
      lcd.setCursor(2,0); // sets the cursor on the lcd
      lcd.print("Door Opened");
      lcd.createChar(1, Opened);
      lcd.setCursor(14,0); // sets the cursor on the lcd
      lcd.write(1);
      lcd.setCursor(0,1); // sets the cursor on the lcd
      lcd.print("Press # to Close");
      SmartDoor = 0;
    }
    else {
      lcd.clear();
      lcd.setCursor(0,0); // sets the cursor on the lcd
      lcd.print("Wrong Password"); // prints the text/character
      lcd.setCursor(0,1);
      lcd.print("Try Again In");
      lcd.setCursor(13,1);
      lcd.print("10");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("09");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("08");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("07");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("06");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("05");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("04");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("03");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("02");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("01");
      delay(1000);
      lcd.setCursor(13,1);
      lcd.print("00");
      delay(1000);
      lcd.clear();
      SmartDoor = 1; // closes the smart door
    }
    clearData(); // clears the data
  }
}
