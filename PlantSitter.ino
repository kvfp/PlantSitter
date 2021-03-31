// Vivien Frances Pabuna

// soil sensor calibration
const int airValue = 605;
const int waterValue = 320;
int minMoistureLevel = 5;

int minTimeLength = 0;
int waterLength = 0;

// pins
int pumpPin = 2;
int ledPin = 12;
int soilPin = A2;

int buzzerPin = 3;
int tempPin = 4;
int lightPin = 5;

int greenBtnPin = 6;
int yellowBtnPin = 7;

// references
float soilMoistureValue = 0;
float soilMoisturePercent = 0;
int yellowBtnState = 0;
int greenBtnState = 0;
int wateringSystemOn = 1;

// plant profiles
int profileToggleState = 1; // currently ranges from 1 to 5
int plantProfileMinMoisture[5] = {2, 0, 30, 0, 0};
int plantProfileMinTime[5] = {0, 0, 0, 10, 86400};
int plantProfileWaterTime[5] = {0, 0, 0, 10, 20};

// profile 1 - water if soil moisture is less than given value (2%)
// profile 2 - do not water at all (unless manually enabled)
// profile 3 - water if soil moisture is less than given value (30%)
// profile 4 - water for 10 seconds then wait another 10 seconds before watering again (demo purposes)
// profile 5 - water once for 20 seconds every day (86400 seconds)

// // // // // // // // // // // // // // //

void
setup()
{
  Serial.begin(9600);

  // initialize ouputs
  pinMode(pumpPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // initialize inputs
  pinMode(soilPin, INPUT);
  pinMode(yellowBtnPin, INPUT);
  pinMode(greenBtnPin, INPUT);
  
  digitalWrite(ledPin, HIGH);
  delay(500);
}

void loop()
{
  // take pin inputs
  soilMoistureValue = analogRead(soilPin);
  yellowBtnState = digitalRead(yellowBtnPin);
  greenBtnState = digitalRead(greenBtnPin);

  int targetMoistureLevel = plantProfileMinMoisture[profileToggleState - 1];
  minMoistureLevel = targetMoistureLevel;

  // make calculations
  soilMoisturePercent = map(soilMoistureValue, airValue, waterValue, 0, 100);

  // print calculations
  Serial.println("SOIL MOISTURE:");
  Serial.println(soilMoisturePercent);

  if (greenBtnState == HIGH) {
    digitalWrite(pumpPin, HIGH);
  } else {
    digitalWrite(pumpPin, LOW);
    // toggle settings
    if (yellowBtnState == HIGH)
    {
      // handle profile toggle from 1 to 5
      if (profileToggleState < 5)
      {
        profileToggleState = profileToggleState + 1;
      }
      else
      {
        profileToggleState = 1;
      }

      // reference profile details
      int targetMoistureLevel = plantProfileMinMoisture[profileToggleState - 1];
      minMoistureLevel = targetMoistureLevel;

      minTimeLength = plantProfileMinTime[profileToggleState - 1];
      waterLength = plantProfileWaterTime[profileToggleState - 1];

      // check if the profile is the one that doesn't water at all
      // represent this with the led
      if (minTimeLength == 0 && targetMoistureLevel == 0) {
        if (wateringSystemOn == 1) {
          wateringSystemOn = 0;
          digitalWrite(ledPin, LOW);
        }
      } else {
        if (wateringSystemOn == 0) {
          wateringSystemOn = 1;
          digitalWrite(ledPin, HIGH);
        }
      }

      // play reference sound
      // number of beeps = profile number
      for (int i = 0; i < profileToggleState; i++)
      {
        tone(buzzerPin, 800, 200);
        delay(1000);
      }

    }

    if (waterLength == 0) {
      // if the profile setting is triggered by moisture level
      if (soilMoisturePercent < minMoistureLevel) {
        digitalWrite(pumpPin, HIGH);
      } else {
        digitalWrite(pumpPin, LOW);
      }      
    } else {
      // if the profile setting is triggered by time
      int initialProfileState = profileToggleState;
      minTimeLength = plantProfileMinTime[profileToggleState - 1];
      waterLength = plantProfileWaterTime[profileToggleState - 1];

      // start watering sound
      tone(buzzerPin, 1300, 1000);
      delay(1000);

      // water for number of seconds specified
      digitalWrite(pumpPin, HIGH);
      for (int i = 0; i < waterLength; i++) {
        if (initialProfileState != profileToggleState) {
          break;
        }
        delay(1000);
      }

      // end watering sound
      tone(buzzerPin, 300, 1000);
      delay(1000);
      digitalWrite(pumpPin, LOW);
      // wait for next watering
      for (int i = 0; i < minTimeLength; i++) {
        if (initialProfileState != profileToggleState) {
          break;
        }
        delay(1000);
      }
      digitalWrite(pumpPin, LOW);
    }
  }
  delay(1000);
}
