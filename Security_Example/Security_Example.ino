#include <require_cpp11.h>
#include <deprecated.h>
#include <MFRC522Extended.h>
#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN    9            //pin RST ada di nomor 9
#define SS_PIN    10            //pin SS ada di nomor 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

String read_rfid;               //RFID dibaca
String ok_rfid_1 = "B3B05A11";  //ini UID milik card punya saya

int lock1 = 2;                  //saya memasang di port 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(lock1, OUTPUT);

}

void buka_kunci1(){
  digitalWrite(lock1,LOW);
}

void tutup_kunci1(){
  Serial.println("Kunci 1 tertutup!!");   //pesan yang muncul 
  digitalWrite(lock1,HIGH);
  delay(500);
  digitalWrite(lock1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( ! mfrc522.PICC_IsNewCardPresent())
      return;

  if ( ! mfrc522.PICC_ReadCardSerial())
      return;

  if (read_rfid==ok_rfid_1) {

    buka_kunci1();            //awalnya, kunci dalam keadaan terbuka
    
  } else {

    tutup_kunci1();         //ketika di tab, kunci akan tertutup
    
  }
  return;
}
