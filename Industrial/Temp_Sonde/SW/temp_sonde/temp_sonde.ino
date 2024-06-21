#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float temperature[] = {-40, 0, 25, 50, 100, 200, 300, 400, 500, 600, 700, 800, 850};
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
  //voltage to temp
  temp = interpolateVoltageToTemperature(voltage);

  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage);
  lcd.setCursor(0, 1);
  lcd.print("Temp:   ");
  lcd.print(temp);
  lcd.print(char(223));
  lcd.print("C");

  Serial.print(" Voltage: ");
  Serial.print(voltage);
  Serial.print(" Temp: ");
  Serial.println(temp);

  delay(250);
  if(temp >= 100){
    lcd.clear();
  }
}

float interpolateVoltageToTemperature(float voltage) {
  int i;
  for (i = 0; i < 12; i++) {
    if (voltage >= voltageTable[i] && voltage <= voltageTable[i + 1]) {
      break;
    }
  }

  float temp = temperature[i] + (voltage - voltageTable[i]) * (temperature[i + 1] - temperature[i]) / (voltageTable[i + 1] - voltageTable[i]);
  return temp;
}
