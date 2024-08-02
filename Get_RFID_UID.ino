#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10

MFRC522 mfrc522(SS_PIN, RST_PIN);
String UIDCard = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan your RFID Card:");
  for (int i = 0; i < 20; i++) {
    Serial.print(".");
    delay(50);
  }
  Serial.println("");
}

void loop() {
  //Wait until new tag is available
  while (getUID())
  {
    Serial.print("UID: ");
    Serial.println(UIDCard);

    for (int i = 0; i < 20; i++) {
      Serial.print(".");
      delay(50);
    }
    delay(3000);
  }
}
boolean getUID()
{
  if (! mfrc522.PICC_IsNewCardPresent()) {
    //Serial.println("card Not found");
    return false;
  }

  if (! mfrc522.PICC_ReadCardSerial()) {
    //Serial.println("Not able to read the card");
    return false;
  }
  UIDCard = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    UIDCard.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UIDCard.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  UIDCard.toUpperCase();
  UIDCard = UIDCard.substring(1);

  mfrc522.PICC_HaltA();
  return true;
}