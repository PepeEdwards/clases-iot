#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define PH_PIN    1      // GPIO1 — analog input from PH4502C
#define SDA_PIN   5      // GPIO5 — I2C data
#define SCL_PIN   6      // GPIO6 — I2C clock

#define PH_SLOPE  -5.70
#define PH_OFFSET  21.34

// 72x40 OLED display over hardware I2C
U8G2_SSD1306_72X40_ER_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);

void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);  // set ADC range to 0–3.3 V
  display.begin();
}

void loop() {
  float voltage = analogRead(PH_PIN) * 3.3 / 4095.0;
  float ph      = PH_SLOPE * voltage + PH_OFFSET;

  // Print to Serial
  Serial.print("pH: ");
  Serial.println(ph, 2);

  // Show on OLED
  char phText[8];
  dtostrf(ph, 4, 2, phText);  // format float as string, e.g. "7.34"

  display.clearBuffer();
  display.setFont(u8g2_font_helvB08_tr);  // small font for label
  display.drawStr(0, 10, "pH level");
  display.setFont(u8g2_font_helvB18_tr);  // big font for value
  display.drawStr(4, 36, phText);
  display.sendBuffer();

  delay(2000);
}
