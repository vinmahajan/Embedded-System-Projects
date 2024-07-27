#include <LiquidCrystal.h>
#include <Keypad.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial sim800L(2, 3);

JsonDocument doc;


/* Display */
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

/* Keypad setup */
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {7, 6, 5, 4};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);


void setup() {
  lcd.begin(16, 2);
  showStartupMessage();
  Serial.begin(9600);
  sim800L.begin(9600);
  // sim800L.println("AT");
  // updateSerial();

  char Menu[] = "[{\"Code\":\"A1\",\"Item\":\"Menue1\",\"Price\":512},{\"Code\":\"A2\",\"Item\":\"Menue2\",\"Price\":100},{\"Code\":\"A3\",\"Item\":\"Menue3\",\"Price\":81},{\"Code\":\"A4\",\"Item\":\"Menue4\",\"Price\":842},{\"Code\":\"A5\",\"Item\":\"Menue5\",\"Price\":842},{\"Code\":\"A6\",\"Item\":\"Menue6\",\"Price\":27},{\"Code\":\"A7\",\"Item\":\"Menue7\",\"Price\":84}]";
  deserializeJson(doc, Menu);

}



void loop() {

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Enter Codes");

  String incodes[] = {};
  unsigned int arr_length = 0;
  int lcdlane = 0;
  bool interrupt = false;
  auto key = keypad.getKey();

  while (key != '#') {
    if (key) {
      if (arr_length == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
      }
      Serial.println(key);
      lcd.print(key);
      String cod = String(key);
      key = keypad.getKey();

      while (key != '*') {
        if (key) {
          Serial.println(key);
          lcd.print(key);

          cod += String(key);
          if (cod == "00") {
            // lcd.clear();
            interrupt = true;
            break;
          }
        }
        key = keypad.getKey();
      }
      if (interrupt) {
        break;
      }

      lcd.print("+");

      if (arr_length == 5) {
        lcd.setCursor(0, 1);
      }
      incodes[arr_length++] = cod;
      cod = "";
    }
    key = keypad.getKey();
  }

  if (!interrupt) {
    int totalAmount = 0;
    String billText = "";
    for (int i = 0; i < arr_length; i++) {
      for (int j = 0; j < doc.size(); j++) {
        const char* codes = doc[j]["Code"];
        // String codeStr(codes); // Convert char* to String for comparison

        if (incodes[i] == String(codes)) {
          int16_t price = doc[j]["Price"];
          totalAmount += price;

          const char* item = doc[j]["Item"];
          String temptext = String(item) + ": " + String(price) + " Rs.\n";
          billText += temptext;
          // Serial.print(item);
          // Serial.print(": ");
          // Serial.println(price);
          break;
        }

      }


    }
    billText += ("\nTotal Bill Amount: " + String(totalAmount) + " Rs.\nThank You!");
    // Serial.println(totalAmount);
    // Serial.println(billText);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total: ");
    lcd.print(totalAmount);
    lcd.print(" Rs.");
    lcd.setCursor(2, 1);
    lcd.print("# to Next");

    key = keypad.getKey();

    while (key != '#') {
      key = keypad.getKey();

    }

    // Mobile No. code
    String mobileNumber = "+91";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Mobile No.");
    lcd.setCursor(1, 1);
    lcd.print(mobileNumber);
    lcd.print(" ");

    key = keypad.getKey();

    while (key != '#') {
      if (key && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*')
      {
        lcd.print(key);
        mobileNumber += key;
      }
      if (key == '*') {
        mobileNumber = "+91";
        lcd.setCursor(0, 1);
        lcd.print("                 ");
        lcd.setCursor(1, 1);
        lcd.print(mobileNumber);
        lcd.print(" ");
      }

      key = keypad.getKey();
    }
    // Serial.println(mobileNumber);


    // Bill Sending.
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("Sending Bill...");
    SendSMS(billText, mobileNumber);

    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("Bill Sent.");
    delay(5000);
  }


}


void showStartupMessage() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  delay(500);

  lcd.setCursor(1, 1);
  String message = "Paperless bill.";
  for (byte i = 0; i < message.length(); i++) {
    lcd.print(message[i]);
    delay(100);
  }
  delay(500);

}

void SendSMS(String billText, String mobileNumber) {
  Serial.println(billText);
  Serial.println(mobileNumber);
  delay(5000);

}


