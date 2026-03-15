// #region full
#include <esp_now.h>
#include <WiFi.h>

// ── MAC del receptor (cambiar por la tuya) ──
uint8_t macReceiver[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

// ── Estructura de datos compartida (debe ser IGUAL en el receptor) ──
typedef struct DatosSensor {
  float temperatura;
  float humedad;
  int   contador;
  bool  alerta;
} DatosSensor;

DatosSensor datos;

// ── Callback: se ejecuta tras cada envío ──
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Estado envío: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  // Registrar peer (receptor)
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, macReceiver, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error registrando peer");
    return;
  }
  Serial.println("Sender listo.");
}

void loop() {
  datos.temperatura = random(200, 350) / 10.0;  // simulado
  datos.humedad     = random(400, 900) / 10.0;
  datos.contador++;
  datos.alerta = datos.temperatura > 30.0;

  esp_now_send(macReceiver, (uint8_t *)&datos, sizeof(datos));
  delay(2000);
}
// #endregion full
