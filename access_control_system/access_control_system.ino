#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10      

MFRC522 mfrc522(SS_PIN, RST_PIN);  
 
void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader...");
  Serial.println();
 
}
 
void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
 
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  Serial.print("UID tag : ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
 Serial.println(content.substring(1));

}