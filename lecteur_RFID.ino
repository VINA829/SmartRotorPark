#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9         
#define SS_PIN          10  
#define LED_VERT  7
#define LED_ROUGE 6

MFRC522 lecteur_carte(SS_PIN , RST_PIN);

byte uid_autorise[4] = {0xA3, 0x05, 0xF2, 0x01};


void setup() {
  Serial.begin(9600);
  SPI.begin();
  lecteur_carte.PCD_Init();
  pinMode(LED_VERT,OUTPUT);
  pinMode(LED_ROUGE,OUTPUT);
  digitalWrite(LED_VERTE, LOW);
  digitalWrite(LED_ROUGE, LOW);
}

void loop() {
  byte i
  
  if(!lecteur_carte.PICC_IsNewCardPresent()) //S'il n'y a pas de carte 
  {
    return ;  
  }
  
  if(!lecteur_carte.PICC_ReadCardSerial()) //Echec de lecture de l'UID
  {
    return ;  
  }

  //Affichage de l'UID lu 
  Serial.print("UID detecte : ");
  for (i = 0; i < lecteur_carte.uid.size; i++) {
    if (lecteur_carte.uid.uidByte[i] < 0x10) {
      Serial.print(" 0");
    } else {
      Serial.print(" ");
    }
    Serial.print(lecteur_carte.uid.uidByte[i], HEX);
  }
  Serial.println();
  

  if(comparaison_uid(lecteur_carte.uid.uidByte , lecteur_carte.uid,size))
  {
    digitalWrite(LED_VERTE, HIGH);
    digitalWrite(LED_ROUGE, LOW);
    ouvrirServo();
    delay(5000); // 
    fermerServo();
    
  }
  else 
  {
    digitalWrite(LED_VERTE, LOW);
    digitalWrite(LED_ROUGE, HIGH);  
  }

  delay(2000);

  digitalWrite(LED_VERTE, LOW);
  digitalWrite(LED_ROUGE, LOW);

  // Ferme proprement la communication avec la carte
  lecteur_carte.PICC_HaltA(); 
  lectaur_carte.PCD_StopCrypto1();
  

}

//Foction qui compare l'uid de la carte present et celle de la carte autorisée
bool comparaison_uid(byte *uid_carte , byte taille)
{
  byte i ; 
  if(taille != sizeof(uid_autorise))
  {
    return (false);
  }  
  for (i=0 ; i< taille ; i++ )
  {
    if(uid_carte[i] != uid_autorise[i])
    {
      return (false);
    }    
  }

  return(true);
}

void ouvrirServo()
  {
    for (pos = 0 ; pos <=90 ;pos++)
    {
      monServo.write(pos);
      delay(15);
    }
  }

  void fermerServo()
  {
    for (pos = 90 ; pos >=0 ;pos--)
    {
      monServo.write(pos);
      delay(15);
    }
