 #include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Welcome!");
  Serial.println("Approximate your ID card to the reader...");
  Serial.println();
  pinMode(3,OUTPUT); //GREEN
  pinMode(4,OUTPUT); //RED
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "43 9F 10 27") //Card - 43 9F 10 27 Key Chain  B2 AB 92 79
  {
    Serial.println("Authorized access");
    Serial.println("Attendeance updated - Roll number 1D100");
    Serial.println();
    digitalWrite(4,1);
    delay(3000);
    digitalWrite(4,0);
  }
 
 else   {
    Serial.println("Access denied");
    Serial.println("Student details not found! Please contact admin");
    Serial.println();
    digitalWrite(3,1);
    delay(3000);
    digitalWrite(3,0);
  }
} 
