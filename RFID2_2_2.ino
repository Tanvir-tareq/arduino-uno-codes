#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4
#define RST_PIN D3

MFRC522 rfid(SS_PIN, RST_PIN);

byte authorizedUID[4] = {0x5B, 0xA0, 0xB3, 0x02};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println(F("Access Control System Ready - waiting for card..."));
}

void loop() {
 
  static unsigned long lastHeartbeat = 0;
  if (millis() - lastHeartbeat > 2000) {
    Serial.println(F("(Scanning for RFID card...)"));
    lastHeartbeat = millis();
  }


  if (!rfid.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }

  Serial.println(F("Card detected! Trying to read UID..."));

  
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println(F("Failed to read UID. Try again."));
    return;
  }

 
  Serial.print(F("Card UID: "));
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print(F(" 0"));
    else Serial.print(F(" "));
    Serial.print(rfid.uid.uidByte[i], X );
  }
  Serial.println();

  
  bool accessGranted = false;
  if (rfid.uid.size == sizeof(authorizedUID)) {
    accessGranted = true;
    for (byte i = 0; i < rfid.uid.size; i++) {
      if (rfid.uid.uidByte[i] != authorizedUID[i]) {
        accessGranted = false;
        break;
      }
    }
  }

 
  if (accessGranted) {
    Serial.println(F(">>> ACCESS GRANTED! You can enter. <<<"));
  } else {
    Serial.println(F(">>> ACCESS DENIED! Basai ja. <<<"));
  }

  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1500);  
}
