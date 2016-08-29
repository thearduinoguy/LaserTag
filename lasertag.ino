
#include <LiquidCrystal.h>

#include <IRremoteInt.h>

#include <Button.h>
#include <IRremote.h>

#define BUTTON_PIN 2
#define PULLUP false
#define INVERT false
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.
#define FLASH_PIN   5        // Muzzle flash LED
#define IR_PIN      4

// Object creation
IRsend irsend;
Button myBtn(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// default settings
int MAX_AMMO = 250;
int AMMO = MAX_AMMO;
int HEALTH = 100;
int CHARGES = 10;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.home();
  lcd.print("  MHS Lasertag");
  lcd.setCursor(2,1);
  lcd.print("Game System");
  pinMode(FLASH_PIN, OUTPUT);
  pinMode(IR_PIN, OUTPUT);

  delay(1000);
  lcd.clear();
}

void waitForReload() {
  delay(5000);
  AMMO = MAX_AMMO;
}

void updateDisplay() {
  lcd.home();
  lcd.print("T1 P12 C");
  lcd.print(CHARGES);
  lcd.print(" R");
  lcd.print(AMMO);
  lcd.print(" ");
  lcd.setCursor(2,1);
  lcd.print("HEALTH: ");
  lcd.print(HEALTH);
  lcd.print("% ");
}

void loop() {

  myBtn.read();                    //Read the button

  if (myBtn.isPressed()) {       //If the button was pressed, change the LED state
    analogWrite(4, 150);
    AMMO -= 1;

    digitalWrite(FLASH_PIN, HIGH);
    irsend.sendSony(AMMO, 16); delay(15
      );
    digitalWrite(FLASH_PIN, LOW);
    analogWrite(4, 0);
  }
  if (AMMO == 0) {
    waitForReload();
  }
  updateDisplay();
}




