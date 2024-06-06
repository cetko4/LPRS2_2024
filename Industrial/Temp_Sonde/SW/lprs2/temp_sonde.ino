#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float temperature[] = {-40, 0, 25, 50, 100, 200, 300, 400, 500, 600, 700, 800, 850};
float resistanceTable[] = {170.2, 201, 220.1, 239, 276.4, 349.5, 420.2, 488.6, 554.6, 618.3, 679.7, 738.7, 767.3};
float voltageTable[] = {0.73 ,0.84, 0.9, 0.96, 1.08, 1.29, 1.48, 1.64, 1.78, 1.91, 2.02, 2.12, 2.17};

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int analogPin = A1;
  float voltage = 0;
  float resistance = 0;
  float temp = 0;
  voltage = analogRead(analogPin) / 204.6;
  resistance = interpolateResist(voltage);
  temp = interpolateTemperature(resistance);

  lcd.setCursor(0, 0);
  lcd.print("Resist: ");
  lcd.print(resistance);
  lcd.setCursor(0, 1);
  lcd.print("Temp:   ");
  lcd.print(temp);
  lcd.print(" C");

  Serial.print(" Resist: ");
  Serial.print(resistance);
  Serial.print(" Temp: ");
  Serial.println(temp);

  delay(500);
  if(temp > 100){
    lcd.clear();
  }
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

float interpolateResist(float voltage) {
  int i;
  for (i = 0; i < 12; i++) {
    if (voltage >= voltageTable[i] && voltage <= voltageTable[i + 1]) {
      break;
    }
  }

  float resist = resistanceTable[i] + (voltage - voltageTable[i]) * (resistanceTable[i + 1] - resistanceTable[i]) / (voltageTable[i + 1] - voltageTable[i]);
  return resist;
}
