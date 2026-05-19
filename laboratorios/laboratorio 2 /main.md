# Laboratorio 2 — Entrega 2
## Sensado de pH, Visualización en Pantalla y Comunicación ESP-NOW

*Diseño y Desarrollo de Sistemas IoT*  
Facultad de Ingeniería y Ciencias Aplicadas — Universidad de los Andes

---

## 1. Introducción

Este laboratorio introduce la integración de sensores analógicos, pantallas OLED y comunicación inalámbrica entre microcontroladores en el contexto de sistemas IoT. A lo largo de cuatro desafíos, construirán un sistema de monitoreo de pH distribuido: un nodo de adquisición basado en ESP32-C3 que lee, calibra y visualiza el pH localmente, y un gateway basado en el módulo Heltec ESP32-S3 V4 que recibe los datos vía ESP-NOW y los despliega en su propia pantalla. La experiencia cubre el ciclo completo de un nodo sensor: acondicionamiento de señal analógica, calibración en campo, transmisión inalámbrica y presentación de datos.

---

### 1.1 Trabajo en Equipo y Distribución de Roles

El laboratorio debe realizarse en grupos de **cuatro (4) integrantes**. Antes de comenzar, el equipo debe definir y registrar en la bitácora los roles de cada integrante. Se sugiere la siguiente distribución:

| Rol | Responsabilidades principales |
|---|---|
| **Hardware** | Montaje del circuito en protoboard, conexionado del sensor y botón, elaboración del diagrama eléctrico final. |
| **Firmware Nodo** | Programación del ESP32-C3: lectura ADC, calibración, pantalla OLED y transmisión ESP-NOW. |
| **Firmware Gateway** | Programación del Heltec ESP32-S3: recepción ESP-NOW y visualización de pH en pantalla OLED integrada. |
| **Documentación** | Redacción del informe, registro fotográfico, diagramas de arquitectura y consolidación de la entrega. |

---

## 2. Materiales

| Componente | Cant. | Descripción |
|---|---|---|
| ESP32-C3 OLED 0.96" | 1 | Microcontrolador nodo sensor. Incluye pantalla OLED 72×40 px integrada (I2C: SCL→GPIO6, SDA→GPIO5). |
| Heltec ESP32-S3 V4 | 1 | Microcontrolador gateway. Incluye pantalla OLED integrada (SCL→GPIO18, SDA→GPIO17) y antena LoRa. |
| Módulo PH4502C + sonda | 1 | Módulo acondicionador de señal para sonda de pH. Salida analógica 0–3,3 V compatible con ESP32. |
| Botón táctil | 1 | Pulsador de 4 pines para montar en protoboard. |
| Solución tampón KCl pH 7 | 1 | Solución de calibración de cloruro de potasio a pH 7. |
| Protoboard | 1 | Placa de prototipado sin soldadura. |
| Jumpers macho–macho | × | Cables de conexión. |
| Level shifter 5V↔3,3V *(opcional)* | 1 | Necesario si el módulo PH4502C se alimenta a 5 V y la salida analógica supera 3,3 V. |

> **Nota sobre el level shifter:** El módulo PH4502C puede alimentarse tanto a 5 V como a 3,3 V. Si se opera a 3,3 V (VCC del ESP32), la salida analógica (Po) permanece dentro del rango ADC del ESP32-C3 y no se requiere adaptador de nivel. Si se opera a 5 V, la salida puede superar 3,3 V y dañar el ADC; en ese caso se debe agregar un divisor de voltaje o un level shifter en la línea Po→GPIO.

---

## 3. Descripción del Hardware

### 3.1 ESP32-C3 OLED — Pines Reservados

El módulo ESP32-C3 utilizado en este laboratorio incorpora una pantalla OLED de 72×40 px conectada **internamente** a los siguientes pines:

| Función integrada | GPIO |
|---|---|
| OLED SCL (I2C clock) | GPIO6 |
| OLED SDA (I2C data) | GPIO5 |

Estos pines **no deben usarse** para ningún periférico externo. Los pines disponibles para conexiones externas son:

| GPIO | Función alternativa | Uso sugerido |
|---|---|---|
| GPIO0 | ADC CH0 (A0) | Analógico |
| GPIO1 | ADC CH1 (A1) | **Salida analógica del PH4502C (Po)** |
| GPIO2 | ADC CH2 (A2) | Analógico |
| GPIO3 | ADC CH3 (A3) | Analógico / Digital |
| GPIO4 | Digital | Digital |
| GPIO9 | BOOT button | **Botón de usuario** (activo en LOW) |
| GPIO10 | Digital | Digital |
| GPIO20 | RX (Serial) | Serial |
| GPIO21 | TX (Serial) | Serial |

> **Pregunta de diseño:** ¿Por qué GPIO9 ya tiene una resistencia pull-up integrada en el módulo y cómo simplifica esto el circuito del botón?

### 3.2 Heltec ESP32-S3 V4 — Pines Reservados

El módulo Heltec ESP32-S3 V4 tiene los siguientes pines reservados para periféricos integrados que **no deben usarse** para conexiones externas:

| Función integrada | GPIO |
|---|---|
| OLED SCL | GPIO18 |
| OLED SDA | GPIO17 |
| OLED RST | GPIO21 |
| LED WS2812 (LED_Write) | GPIO35 |
| Botón de usuario (USER_SW) | GPIO0 |
| LoRa NSS | GPIO8 |
| LoRa SCK | GPIO9 |
| LoRa MOSI | GPIO10 |
| LoRa MISO | GPIO11 |
| LoRa RST | GPIO12 |
| LoRa BUSY | GPIO13 |

Para este laboratorio, el Heltec actúa únicamente como receptor ESP-NOW con visualización en pantalla (Esto lo harán ustedes conectando el resto de los sensores del kit).

---

## 4. Desafíos

Los cuatro desafíos están diseñados para construirse de forma incremental. El Desafío 4 integra los resultados de los anteriores.

---

### 4.1 Desafío 1 — Conexión del Sensor de pH al ESP32-C3

**Objetivo:** Configurar el entorno de desarrollo para el ESP32-C3, identificar los pines disponibles, conectar el módulo PH4502C y verificar que la lectura analógica llega correctamente al microcontrolador.

#### Paso 1: Configuración de Arduino IDE para ESP32-C3

Si el soporte para ESP32 no está instalado, agregar el repositorio de Espressif:

1. Abrir Arduino IDE y dirigirse a **File → Preferences**.
2. En *Additional boards manager URLs* ingresar:  
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. Ir a **Tools → Board → Boards Manager**, buscar `esp32` e instalar la versión más reciente de **Espressif Systems**.
4. Conectar el ESP32-C3 por USB y en **Tools → Board** seleccionar **ESP32C3 Dev Module**.
5. En **Tools → Port** seleccionar el puerto correspondiente.

> **Importante:** Algunos módulos ESP32-C3 requieren mantener presionado el botón BOOT al conectar por primera vez para entrar en modo de programación. Si el puerto no aparece, intentar este procedimiento.

#### Paso 2: Instalación de la Librería U8g2

La pantalla OLED integrada se controla con la librería **U8g2**:

1. En Arduino IDE ir a **Sketch → Include Library → Manage Libraries**.
2. Buscar `U8g2` (autor: oliver) e instalar la versión más reciente.

#### Paso 3: Conexionado del Módulo PH4502C

Realizar las conexiones según la siguiente tabla. Verificar la tensión de alimentación antes de conectar (ver nota sobre level shifter en sección 2):

| Pin PH4502C | Pin ESP32-C3 | Descripción |
|---|---|---|
| VCC | 3V3 | Alimentación 3,3 V |
| GND | GND | Tierra común |
| Po (salida analógica) | GPIO1 | Señal de pH en voltaje |

Los pines To (temperatura) y BNC (sonda de pH) del módulo son los que conectan directamente a la sonda. El ajuste grueso de offset se realiza con el potenciómetro del módulo; el ajuste fino se realiza por software en el Desafío 2.

#### Paso 4: Análisis del Firmware

A continuación se presenta el firmware base para este desafío, desglosado por bloques. El equipo debe **transcribir, compilar y cargar** el código completo comprendiendo cada sección antes de pasar al siguiente desafío.

---

**Bloque 1 — Librerías y constantes**

Se incluyen las librerías necesarias y se definen los pines y las constantes del modelo de pH. `PH_SLOPE` es la pendiente de la curva del electrodo (valor típico del fabricante). `PH_OFFSET` desplaza la curva verticalmente y es el valor que se ajustará durante la calibración en el Desafío 2.

```cpp
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define PH_PIN    1
#define SDA_PIN   5
#define SCL_PIN   6

#define PH_SLOPE   -5.70
#define PH_OFFSET   21.34
```

---

**Bloque 2 — Objeto de la pantalla**

Esta línea crea el objeto que representa la pantalla OLED. Los parámetros indican: orientación (`U8G2_R0` = sin rotación), sin pin de reset (`U8X8_PIN_NONE`), y los pines de reloj y datos I2C. El nombre largo `U8G2_SSD1306_72X40_ER` identifica exactamente el controlador y la resolución de la pantalla integrada en el módulo.

```cpp
U8G2_SSD1306_72X40_ER_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);
```

---

**Bloque 3 — Setup**

`analogSetAttenuation(ADC_11db)` configura el ADC para que pueda leer voltajes de hasta 3,3 V. Sin esta línea el rango máximo es aproximadamente 1 V, y la lectura del sensor saturará y dará valores incorrectos.

```cpp
void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  display.begin();
}
```

---

**Bloque 4 — Lectura del sensor y conversión a pH**

`analogRead` devuelve un número entero entre 0 y 4095 (ADC de 12 bits). Multiplicarlo por `3.3 / 4095.0` convierte ese valor crudo a voltios. Luego se aplica la ecuación lineal `pH = pendiente × voltaje + offset` para obtener el pH.

```cpp
float voltage = analogRead(PH_PIN) * 3.3 / 4095.0;
float ph      = PH_SLOPE * voltage + PH_OFFSET;
```

---

**Bloque 5 — Visualización en pantalla OLED**

La pantalla trabaja con un buffer en memoria: primero se borra (`clearBuffer`), luego se dibuja todo lo que se quiere mostrar, y finalmente se envía el buffer completo a la pantalla (`sendBuffer`). Esto evita parpadeos. `dtostrf` convierte el número flotante de pH a una cadena de texto (`char[]`) porque `drawStr` solo puede dibujar texto, no números directamente.

```cpp
char phText[8];
dtostrf(ph, 4, 2, phText);

display.clearBuffer();
display.setFont(u8g2_font_helvB08_tr);
display.drawStr(0, 10, "pH level");
display.setFont(u8g2_font_helvB18_tr);
display.drawStr(4, 36, phText);
display.sendBuffer();
```

Los dos `setFont` usan fuentes de distinto tamaño: una pequeña para la etiqueta "pH level" y una grande para el valor numérico. Las coordenadas en `drawStr(x, y, texto)` indican la posición en píxeles desde la esquina superior izquierda de la pantalla (72×40 px).

---

#### Criterio de Aceptación

El Desafío 1 se considera completado cuando el monitor serial imprime valores de pH numéricos de forma continua y la pantalla OLED del ESP32-C3 muestra el valor actualizado cada 2 segundos.

---

### 4.2 Desafío 2 — Calibración del Sensor con Solución pH 7

**Objetivo:** Calibrar el sensor de pH utilizando la solución tampón de KCl (pH 7) ajustando la constante `PH_OFFSET` del firmware, de modo que la lectura mostrada coincida con el pH de referencia.

#### Paso 1: Preparación

1. Enjuagar la sonda de pH con agua destilada y secarla suavemente con papel absorbente.
2. Sumergir la sonda en la solución tampón de KCl (pH 7). Esperar **al menos 60 segundos** para que la sonda se estabilice.
3. Observar los valores que aparecen en el monitor serial.

#### Paso 2: Ajuste del Offset por Software

La relación entre voltaje y pH es lineal:

```
pH = PH_SLOPE × voltaje + PH_OFFSET
```

Si la pantalla muestra un valor distinto de 7,00 con la sonda en la solución de referencia, calcular el nuevo offset despejando de la ecuación:

```
PH_OFFSET_nuevo = 7.00 − (PH_SLOPE × voltaje_medido)
```

Reemplazar el valor de `PH_OFFSET` en el código, recompilar y volver a cargar el firmware. Repetir hasta que la lectura muestre **7,00 ± 0,10**.

> **Nota:** El potenciómetro del módulo PH4502C permite un ajuste grueso de offset en hardware. Si la lectura está muy lejos de 7 (más de 2 unidades), ajustar primero el potenciómetro y luego afinar por software.

#### Criterio de Aceptación

El Desafío 2 se considera completado cuando la pantalla muestra una lectura estable dentro del rango 6,90–7,10 con la sonda sumergida en la solución tampón.

---

### 4.3 Desafío 3 — Medición de Muestras

**Objetivo:** Utilizar el sistema calibrado para medir el pH de al menos dos sustancias conocidas y comparar los resultados con los valores de referencia.

#### Paso 1: Procedimiento de Medición

Para cada muestra:
1. Retirar la sonda de la muestra anterior, enjuagar con agua destilada y secar.
2. Sumergir la sonda en la nueva muestra y esperar al menos 30 segundos.
3. Registrar el valor estabilizado que aparece en pantalla y en el monitor serial.

#### Paso 2: Muestras Requeridas

| Muestra | pH de referencia | pH medido (completar) |
|---|---|---|
| Solución KCl pH 7 (verificación) | 7,00 | |
| Vinagre blanco o jugo de limón | 2,4 – 3,0 | |
| Muestra libre (a elección del equipo) | — | |

Para la muestra libre, el equipo puede elegir cualquier líquido disponible (agua del grifo, bebida, etc.) y estimar su pH de referencia antes de medir.

#### Criterio de Aceptación

El Desafío 3 se considera completado cuando se registran mediciones para las tres muestras y el vinagre o jugo de limón marca entre 2,0 y 3,5.

---

### 4.4 Desafío 4 — Comunicación ESP-NOW con el Heltec ESP32-S3 V4

**Objetivo:** Transmitir la lectura de pH del ESP32-C3 (nodo sensor) al Heltec ESP32-S3 V4 (gateway) mediante el protocolo ESP-NOW, activando el envío con un botón físico y mostrando el valor recibido en la pantalla OLED del gateway.

#### Paso 1: Configuración de Arduino IDE para Heltec ESP32-S3 V4

El Heltec ESP32-S3 V4 requiere su propio soporte de placa adicional al de Espressif:

1. En **File → Preferences → Additional boards manager URLs** agregar (separado por coma del anterior):  
   `https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/3.3.8/package_heltec_esp32_index.json`
2. En **Tools → Board → Boards Manager** buscar `Heltec` e instalar **Heltec ESP32 Series Dev-boards**.
3. Seleccionar **Tools → Board → Heltec ESP32 Series → WiFi LoRa 32 (V4)**.
4. Verificar que la pantalla OLED integrada funciona cargando el ejemplo **File → Examples → Heltec ESP32 Dev-Boards → OLED → SSD1306SimpleDemo**.

#### Paso 2: Obtención de la Dirección MAC del Gateway

El Nodo ESP32-C3 necesita conocer la dirección MAC del Gateway antes de poder enviarle datos. ESP-NOW usa la MAC como dirección de destino, de la misma forma que una carta necesita una dirección postal. Cargar el siguiente sketch en el **Heltec ESP32-S3** y anotar la dirección MAC que aparece en el monitor serial:

```cpp
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA);
  delay(500);
}

void loop() {
  String mac = WiFi.macAddress();
  if (mac == "00:00:00:00:00:00") {
    Serial.println("Esperando inicialización WiFi...");
  } else {
    Serial.print("MAC Gateway: ");
    Serial.println(mac);
  }
  delay(1000);
}
```

Registrar la dirección obtenida (formato `AA:BB:CC:DD:EE:FF`). Se usará en el paso siguiente.

#### Paso 3: Conexión del Botón al ESP32-C3

Conectar el botón táctil entre **GPIO9** y **GND**. GPIO9 ya cuenta con una resistencia pull-up interna, por lo que no se necesita resistencia externa. El pin lee `LOW` cuando el botón está presionado.

| Pin botón | Pin ESP32-C3 |
|---|---|
| Terminal A | GPIO9 |
| Terminal B | GND |

#### Paso 4: Firmware del Nodo ESP32-C3

El nodo inicializa ESP-NOW, registra el gateway como destinatario (*peer*), y envía la lectura de pH cada vez que se presiona el botón.

---

**Configuración de ESP-NOW y registro del peer**

Reemplazar `AA:BB:CC:DD:EE:FF` con la MAC obtenida en el Paso 2. El arreglo `gatewayMac` le indica al nodo a quién enviar los datos.

```cpp
#include <WiFi.h>
#include <esp_now.h>

uint8_t gatewayMac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

void setup() {
  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, gatewayMac, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);
}
```

---

**Estructura del paquete**

Para enviar datos por ESP-NOW se define una estructura que agrupa toda la información que viaja en cada mensaje. Definirla igual en el nodo y en el gateway es obligatorio: si las estructuras no coinciden, los datos se interpretan incorrectamente en el receptor.

```cpp
typedef struct {
  float ph;
} PhPacket;

PhPacket paquete;
```

---

**Envío al presionar el botón**

El botón se lee con `digitalRead`. Cuando el pin pasa de HIGH a LOW (flanco de bajada), se toma una lectura y se envía. `esp_now_send` transmite los bytes de la estructura al gateway.

```cpp
#define BTN_PIN 9

void loop() {
  static bool lastState = HIGH;
  bool state = digitalRead(BTN_PIN);

  if (lastState == HIGH && state == LOW) {
    float voltage  = analogRead(PH_PIN) * 3.3 / 4095.0;
    paquete.ph     = PH_SLOPE * voltage + PH_OFFSET;

    esp_now_send(gatewayMac, (uint8_t *)&paquete, sizeof(paquete));
    Serial.print("Enviado pH: ");
    Serial.println(paquete.ph, 2);
  }

  lastState = state;
  delay(20);
}
```

---

**Promedio de muestras**

En los desafíos anteriores se tomó una sola lectura. Pero que se hace con el ruido? una única muestra puede ser imprecisa. Una mejora es tomar varias lecturas consecutivas y promediarlas antes de enviar:

```cpp
float leerPhPromedio() {
  float suma = 0;
  for (int i = 0; i < 10; i++) {
    float v = analogRead(PH_PIN) * 3.3 / 4095.0;
    suma += PH_SLOPE * v + PH_OFFSET;
    delay(10);
  }
  return suma / 10.0;
}
```

Llamar a `leerPhPromedio()` en lugar de calcular el pH directamente al presionar el botón. ¿Cuánto cambia el valor respecto a la lectura simple? ¿Con cuántas muestras deja de mejorar?

---

**Historial de mediciones**

Actualmente el sistema solo recuerda el último valor enviado. ¿Qué habría que agregar al firmware para guardar las últimas N mediciones y poder consultarlas después? Pensar en:

- ¿Qué estructura de datos usarían para almacenar un historial de lecturas?

---

**Marca de tiempo**

Cada medición enviada incluye solo el valor de pH. En una aplicación real es fundamental saber *cuándo* se tomó cada muestra. ¿Qué opciones existen para agregar fecha y hora a cada paquete?

- `millis()` da el tiempo transcurrido desde el encendido, pero se reinicia a cero si se corta la alimentación. ¿Es útil?
- Para tener hora real se necesita un módulo RTC externo (ej. DS3231) o sincronizar vía red con NTP (`configTime`). ¿Cuál de las dos opciones sería viable con el hardware disponible en el kit?

#### Paso 5: Firmware del Gateway Heltec ESP32-S3

El gateway espera paquetes ESP-NOW en segundo plano mediante una función de *callback* que el sistema llama automáticamente cada vez que llega un mensaje. El equipo debe implementar:

```cpp
#include <WiFi.h>
#include <esp_now.h>

typedef struct {
  float ph;
} PhPacket;

void onReceive(const uint8_t *mac, const uint8_t *data, int len) {
  PhPacket paquete;
  memcpy(&paquete, data, sizeof(paquete));

  Serial.print("pH recibido: ");
  Serial.println(paquete.ph, 2);

  // Aquí mostrar el valor en la pantalla OLED del Heltec
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onReceive);
}

void loop() {}
```

> **Nota:** En el Heltec ESP32-S3 V4, la pantalla OLED se inicializa con la librería U8g2 apuntando a GPIO17/GPIO18. El equipo debe adaptar el código de visualización del Desafío 1 a este firmware.

#### Paso 6: Ajuste de Potencia de Transmisión WiFi

El ESP32-C3 permite regular la potencia de su antena (usada también por ESP-NOW). En el laboratorio, con los dispositivos a pocos metros, no es necesaria la potencia máxima:

```cpp
// En setup(), después de esp_now_init():
esp_wifi_set_max_tx_power(40);  // ~10 dBm  (rango: 8 ≈ 2 dBm, 84 ≈ 20 dBm)
```

**Pregunta de diseño:** ¿Qué implicaciones tiene operar ESP-NOW a máxima potencia en un entorno con múltiples dispositivos WiFi? ¿En qué escenarios sería preferible reducir la potencia de transmisión?

#### Criterio de Aceptación

El Desafío 4 se considera completado cuando al presionar el botón en el ESP32-C3, el valor de pH medido aparece en la pantalla OLED del Heltec ESP32-S3 V4 en menos de 1 segundo y ambos monitores seriales registran los eventos de envío y recepción.
