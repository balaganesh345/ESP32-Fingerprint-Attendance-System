#include <Adafruit_Fingerprint.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

String userName[10] = {"","Alice","Bob","Charlie","David"};

bool userStatus[10];
unsigned long loginTime[10];

void setup()
{
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  if (finger.verifyPassword())
  {
    Serial.println("Fingerprint sensor ready");
  }
  else
  {
    Serial.println("Sensor not found");
    while(1);
  }

  for(int i=0;i<10;i++)
  {
    userStatus[i] = false;
  }
}

void loop()
{
  int id = getFingerprintID();

  if(id == -1)
  {
    Serial.println("Place finger...");
  }
  else
  {
    Serial.print("User: ");
    Serial.println(userName[id]);

    if(userStatus[id] == false)
    {
      loginTime[id] = millis();
      userStatus[id] = true;

      Serial.print(userName[id]);
      Serial.println(" LOGIN");
      Serial.print("Login Time(ms): ");
      Serial.println(loginTime[id]);
    }
    else
    {
      unsigned long logoutTime = millis();
      unsigned long workTime = logoutTime - loginTime[id];

      userStatus[id] = false;

      Serial.print(userName[id]);
      Serial.println(" LOGOUT");

      Serial.print("Logout Time(ms): ");
      Serial.println(logoutTime);

      Serial.print("Working Time(ms): ");
      Serial.println(workTime);
    }
  }

  delay(3000);
}

int getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerSearch();
  if (p != FINGERPRINT_OK) return -1;

  return finger.fingerID;
}
