#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int analogPin = A1;
float resistance = 0; 

float temperature[] = {-40, 0, 25, 50, 100, 200, 300, 400, 500, 600, 700, 800, 850};
float resistanceTable[] = {170.2, 201, 220.1, 239, 276.4, 349.5, 420.2, 488.6, 554.6, 618.3, 679.7, 738.7, 767.3};

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  resistance = analogRead(analogPin);
  float temp = interpolateTemperature(resistance);

  lcd.setCursor(0, 0);
  lcd.print("Resist: ");
  lcd.print(resistance);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  Serial.print(" Resist: ");
  Serial.print(resistance);
  Serial.print(" Temp: ");
  Serial.println(temp);

  delay(2000);
}

float interpolateTemperature(float resistance) {
  int i;
  for (i = 0; i < 12; i++) {
    if (resistance >= resistanceTable[i] && resistance <= resistanceTable[i + 1]) {
      break;
    }
  }

  float temp = temperature[i] + (resistance - resistanceTable[i]) * (temperature[i + 1] - temperature[i]) / (resistanceTable[i + 1] - resistanceTable[i]);
  return temp;
}
