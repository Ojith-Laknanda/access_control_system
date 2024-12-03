#define relay1 A5
#define relay2 A4
#define relay3 A3
#define buzzer 5

#define led1 4 //red
#define led2 3 //blue
#define led3 2 //green

#define RX_PIN 2
#define TX_PIN 3



int delay_time=1000;
 
byte max_size=4;// this is for the limit the array size and read only 4 of them
String mechanic[] ={"EB 6D 4D 01","49 47 B0 48","E6 84 E6 FA"};
String engineer[] = {"7B 9C 50 00","6B 1E A6 00","E5 B5 4A 63","E0 2A 4A 63"};
String worker[] = {"1B 1B 9A 00","B9 34 AC 48",""}; //39 D7 87 48


void setup() {
  Serial.begin(115200);

  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  
  pinMode(buzzer,OUTPUT);
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);

  digitalWrite(led1,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led2,LOW);
  
  Serial.println("Serial coms are ready");
  Serial.println();

}

void loop() {
  if(Serial.available()>0){
    String cardUid=Serial.readStringUntil("\n");
    cardUid .trim();

      
    switch(isAccessGranted(cardUid)){
    case 0: // for engs
      {
        Serial.println("Access Granted for engineer");
        access();
        digitalWrite(relay2,LOW);
        digitalWrite(led3,HIGH);
        delay(delay_time);
        digitalWrite(led3,LOW);
        break;
      }
      break;
    case 1:// for mechanics
      {
        Serial.println("Access Granted for mechanic");
        access();
        digitalWrite(relay3,LOW);
        digitalWrite(led3,HIGH);
        digitalWrite(led2,HIGH);
        delay(delay_time);
        digitalWrite(led3,LOW);
        digitalWrite(led2,LOW);
        break;
      }
    case 2:// for workers
      {
        Serial.println("Access Granted for worker");
        access();
        digitalWrite(relay1,LOW);     
        digitalWrite(led2,HIGH);
        delay(delay_time);
        digitalWrite(led2,LOW);
        break;
      }
    default:// defult access denied
      {
        Serial.println("Access denied");
        alarm();
        digitalWrite(relay1,HIGH);
        digitalWrite(relay2,HIGH);
        digitalWrite(relay3,HIGH);

        
        break;
      }
  }
  }
  // Serial.println("closed");
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
  Serial.println();
  delay(delay_time);
 
}
 
// Function to check if access is granted based on RFID tag
int isAccessGranted(String tagID) {
  for (int i = 0; i <max_size ; i++) {
    if (engineer[i] == tagID) {
       
        return 0;
    }else if(mechanic[i] == tagID ){  
     
      return 1;
    }else if(worker[i] == tagID){
     
      return 2;
    }
  }
 
  return -1; // Deny access for others
}
 
void alarm(){
  for(int i=0;i<=5;i++){
    digitalWrite(buzzer,HIGH);
    digitalWrite(led1,HIGH);
    // Serial.println("buzzer on with access");
    delay(500);
    digitalWrite(buzzer,LOW);
    digitalWrite(led1,LOW);
    delay(500);
  }

}
void access(){
  digitalWrite(buzzer,HIGH);
  // Serial.println("buzzer on with access");
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(50);
  digitalWrite(buzzer,HIGH);
  // Serial.println("buzzer on with access");
  delay(50);
  digitalWrite(buzzer,LOW);
  
}
