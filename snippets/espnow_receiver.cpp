// #region full
#include <esp_now.h>
#include <WiFi.h>

// ── Misma estructura que el Sender (EXACTAMENTE igual) ──
typedef struct DatosSensor {
  float temperatura;
  float humedad;
  int   contador;
  bool  alerta;
} DatosSensor;

DatosSensor datosRecibidos;

// ── Callback: se ejecuta cada vez que llegan datos ──
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&datosRecibidos, incomingData, sizeof(datosRecibidos));

  Serial.println("──── Datos Recibidos ────");
  Serial.printf("De MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.printf("Temperatura: %.1f C\n",  datosRecibidos.temperatura);
  Serial.printf("Humedad:     %.1f %%\n", datosRecibidos.humedad);
  Serial.printf("Contador:    %d\n",      datosRecibidos.contador);
  Serial.printf("Alerta:      %s\n",      datosRecibidos.alerta ? "SI" : "OK");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }
  // Solo registrar callback de recepcion — no necesita conocer la MAC del sender
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receptor listo. Esperando datos...");
}

void loop() {
  // El loop puede hacer otras cosas mientras espera
  // OnDataRecv es llamado automaticamente por el hardware WiFi
  delay(10);
}
// #endregion full
