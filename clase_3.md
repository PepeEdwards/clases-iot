---
theme: seriph
background: https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEhu4MVA6NXFxJjPPfaVckUv1Qo12mk7f0oS6mPIa_pwvO2bZSplXWIHvbdyZWEsGdYQTAAKZ_5-BkzJEaQ9poIXn8jPcxBiPRVEYbvjEYlElkvEoM0GuUVQOVCCuE7LjfZ5W0tGvFqDjoGw/s0/3770921.jpg
class: text-center
title: Tipos de Sensores, ADC y Señales Digitales
transition: slide-left
mdc: true
fonts:
  sans: Roboto
  serif: Roboto Slab
  mono: Fira Code
---

<div class="absolute inset-0 bg-black/60" />

<div class="relative z-10 flex h-full flex-col items-center justify-center">

# Tipos de Sensores, ADC y Señales Digitales

## Introduccion a variables fisicas y lectura en sistemas IoT

<div class="pt-10">
  <span @click="$slidev.nav.next" class="px-2 py-1 rounded cursor-pointer" flex="~ justify-center items-center gap-2" hover="bg-white bg-opacity-10">
    Presiona espacio para continuar <div class="i-carbon:arrow-right inline-block"/>
  </span>
</div>

</div>

---
transition: fade-out
---

# Contenido

<Toc maxDepth="1" columns="2" class="text-sm" />

---
transition: slide-up
---

# Variables Comunes en IoT

<div class="grid grid-cols-3 gap-4 mt-6 text-left">

  <div class="p-4 rounded-lg border border-red-400/40 bg-red-500/10">
    <Image src="/images/clase_3/termistor.png" class="h-24 mx-auto mb-3 rounded-lg object-contain bg-white/90 p-2" />
    <div class="font-bold">Temperatura</div>
    <div class="text-sm opacity-85">Medicion termica del ambiente o de una superficie.</div>
  </div>

  <div class="p-4 rounded-lg border border-pink-400/40 bg-pink-500/10">
    <Image src="/images/clase_3/ph-sensor.jpg" class="h-24 mx-auto mb-3 rounded-lg object-contain bg-white/90 p-2" />
    <div class="font-bold">pH</div>
    <div class="text-sm opacity-85">Acidez o alcalinidad en soluciones liquidas.</div>
  </div>

  <div class="p-4 rounded-lg border border-yellow-400/40 bg-yellow-500/10">
    <Image src="/images/clase_3/light_sensor.webp" class="h-24 mx-auto mb-3 rounded-lg object-contain bg-white/90 p-2" />
    <div class="font-bold">Luz</div>
    <div class="text-sm opacity-85">Intensidad luminica para detectar dia, sombra o iluminacion.</div>
  </div>

  <div class="p-4 rounded-lg border border-green-400/40 bg-green-500/10">
    <Image src="/images/clase_3/acelerometer_sensor.png" class="h-24 mx-auto mb-3 rounded-lg object-contain bg-white/90 p-2" />
    <div class="font-bold">Movimiento</div>
    <div class="text-sm opacity-85">Presencia, vibracion o desplazamiento de objetos o personas.</div>
  </div>

  <div class="p-4 rounded-lg border border-blue-400/40 bg-blue-500/10">
    <Image src="/images/clase_3/piezoelectric-force-sensor.jpg" class="h-24 mx-auto mb-3 rounded-lg object-contain bg-white/90 p-2" />
    <div class="font-bold">Presion</div>
    <div class="text-sm opacity-85">Cambios de presion en aire, fluidos o superficies.</div>
  </div>

  <div class="p-4 rounded-lg border border-white/20 bg-white/5">
    <div class="text-3xl mb-2">🧭</div>
    <div class="font-bold">Otros sensores</div>
    <div class="text-sm opacity-85">Gas, distancia, humedad y muchas otras variables utiles en IoT.</div>
  </div>

</div>

<div class="mt-6 p-3 rounded bg-white/5 border border-white/10 text-sm">
  En el laboratorio trabajaremos con distintas magnitudes fisicas, pero la idea central sera siempre la misma: medir, interpretar y tomar decisiones a partir de datos.
</div>

---

<div class="h-full flex items-center justify-center">
  <div class="max-w-4xl mx-auto p-8 rounded-2xl border border-yellow-400/40 bg-yellow-500/10 shadow-lg">
    <div class="flex items-center gap-5">
      <div class="text-6xl leading-none shrink-0">🤔</div>
      <div class="text-3xl font-bold leading-tight text-left">
      ¿Que tipos de señales entrega cada uno de ellos?
      </div>
    </div>
  </div>
</div>

---

# Senales analogas y digitales

<div class="grid grid-cols-2 gap-6 items-center mt-4">
  <div>
    <Image src="/images/clase_3/analog_vs_digital.jpg" class="h-72 mx-auto rounded-xl border border-white/20 bg-white/90 p-2 object-contain" />
  </div>
  <div class="text-left">
    <div class="p-4 rounded-lg border border-blue-400/40 bg-blue-500/10 mb-4">
      <div class="font-bold text-lg mb-2">Senal analoga</div>
      <div class="text-sm">
        Puede tomar muchos valores dentro de un rango continuo. Un sensor analogo no entrega solo 0 o 1, sino una variacion de voltaje proporcional a lo que esta midiendo.
      </div>
    </div>
    <div class="p-4 rounded-lg border border-green-400/40 bg-green-500/10">
      <div class="font-bold text-lg mb-2">Senal digital</div>
      <div class="text-sm">
        Entrega estados discretos, normalmente <code>HIGH</code> o <code>LOW</code>. Es util cuando solo queremos saber si algo ocurre o no ocurre, o cuando el sensor ya procesa internamente la medicion.
      </div>
    </div>
  </div>
</div>

<div class="mt-5 text-sm p-3 rounded bg-white/5 border border-white/10">
  La gran diferencia es que la señal analoga representa un valor continuo, mientras que la digital representa niveles definidos que el microcontrolador puede leer directamente.
</div>

---

# De analogo a digital

<div class="grid grid-cols-2 gap-8 mt-8 text-left">
  <div>
    <div class="font-bold text-lg mb-3">Senal original</div>
    <ul class="text-sm leading-relaxed">
      <li>Muchos sensores parten siendo analogos y primero generan una variacion electrica.</li>
      <li>La variable fisica suele modificar una resistencia, y eso cambia el voltaje del circuito.</li>
      <li>Ese voltaje representa un valor continuo asociado a temperatura, luz, humedad u otra magnitud.</li>
    </ul>
  </div>

  <div>
    <div class="font-bold text-lg mb-3">Conversion y modulos</div>
    <ul class="text-sm leading-relaxed">
      <li>El <code>ADC</code> toma ese voltaje analogo y lo convierte en un numero digital.</li>
      <li>Muchos sensores vienen montados sobre una placa que llamamos modulo o "driver".</li>
      <li>Esa placa acondiciona la señal y, en muchos casos, la traduce a una salida digital mas facil de leer.</li>
    </ul>
  </div>
</div>

<div class="mt-8 max-w-2xl mx-auto rounded-2xl border border-yellow-200/60 bg-yellow-50/90 px-6 py-5 text-yellow-950/80 shadow-md">
  <div class="text-lg font-bold leading-snug">
    Como podria conectar un sensor analogo a mi computador?
  </div>
</div>

---

# ADC del ESP32-S3

<div class="grid grid-cols-2 gap-6 items-center mt-4">
  <div class="text-left">
    <ul class="text-sm leading-relaxed">
      <li>El ESP32-S3 tiene <strong>dos ADC SAR</strong>: <code>ADC1</code> y <code>ADC2</code>.</li>
      <li>En total puede trabajar con <strong>hasta 20 canales</strong> analogicos.</li>
      <li>Su resolucion nativa es de <strong>12 bits</strong>, con configuraciones que pueden llegar hasta <strong>13 bits</strong>.</li>
      <li>Puede medir aproximadamente entre <strong>0 V y 3.1 V</strong>, segun la atenuacion configurada.</li>
      <li>Su referencia interna es cercana a <strong>1100 mV</strong>.</li>
    </ul>
  </div>
  <div>
    <Image src="/images/clase_3/adc-resolution.png" class="h-72 mx-auto rounded-xl border border-white/20 bg-white/90 p-2 object-contain" />
  </div>
</div>

<div class="mt-5 grid grid-cols-2 gap-6 text-left">
  <div class="p-4 rounded-lg border border-blue-400/30 bg-blue-500/10 text-sm">
    Una lectura digital simple guarda estados de <strong>1 bit</strong>: encendido o apagado, <code>HIGH</code> o <code>LOW</code>.
  </div>
  <div class="p-4 rounded-lg border border-emerald-400/30 bg-emerald-500/10 text-sm">
    Un ADC hace algo parecido, pero en vez de un solo estado crea una <strong>ventana de niveles</strong> y guarda en que seccion cae la señal analoga.
  </div>
</div>

<div class="mt-4 text-sm p-3 rounded bg-white/5 border border-white/10">
  Mientras mas bits tiene el ADC, mas secciones puede distinguir y mejor representa los pequeños cambios de la señal.
</div>

---

# Caso base: piezoelectrico y brillo del NeoPixel

<div class="grid grid-cols-2 gap-6 mt-4">
  <div class="text-left">
```cpp
#include <Adafruit_NeoPixel.h>

const int piezoPin = 4;

void setup() {
  pinMode(piezoPin, INPUT);
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);
}

void loop() {
  int lectura = analogRead(piezoPin);
  int brillo = map(lectura, 0, 4095, 0, 255);
  neopixelWrite(RGB_BUILTIN, brillo, 0, 0);
}
```
  </div>
  <div class="text-left">
    <ul class="text-sm leading-relaxed mb-4">
      <li>El sensor piezoelectrico se conecta a un pin <code>INPUT</code> para leer la señal analoga.</li>
      <li>El ESP32-S3 ya tiene un NeoPixel integrado, asi que no hace falta un LED externo.</li>
      <li>La lectura del ADC se mapea desde <code>0-4095</code> a un brillo entre <code>0-255</code>.</li>
      <li><code>pinMode(pin, INPUT)</code> se usa para recibir señal desde el sensor.</li>
      <li><code>pinMode(pin, OUTPUT)</code> se usa cuando queremos manejar un actuador en un pin externo.</li>
      <li>En este ejemplo, el pin analogico mide y el NeoPixel interno responde sin ocupar otro pin de salida.</li>
    </ul>
  </div>
</div>
 <div class="rounded-2xl border border-red-300/30 bg-red-500/10 px-5 py-4 text-sm">
  <div class="text-xs uppercase tracking-wide opacity-70 mb-2">⚠️ Peligro</div>
  <div class="leading-snug">
    Si configuras un pin como <code>OUTPUT</code> y lo dejas en <code>HIGH</code>, pero lo conectas directo a <code>GND</code>, produces un cortocircuito. El caso opuesto tambien es peligroso: un pin en <code>LOW</code> conectado directo a <code>3.3V</code>. Eso puede dañar el pin o la placa.
  </div>
</div>

---

# Caso base: una senal digital

<div class="grid grid-cols-2 gap-6 items-start mt-4">
  <div>
    <Image src="/images/clase_3/pull_up_down.jpg" class="h-40 mx-auto rounded-xl border border-white/20 bg-white/90 p-2 object-contain" />
    <Image src="/images/clase_3/pull_down_button.png" class="h-40 mx-auto mt-4 rounded-xl border border-white/20 bg-white/90 p-2 object-contain" />
  </div>
  <div class="text-left">
    <div class="p-4 rounded-lg border border-sky-400/30 bg-sky-500/10 text-sm mb-4">
      <div class="font-bold mb-2">Pull-up</div>
      <div>
        El pin queda normalmente en <code>HIGH</code>. Cuando presionamos el boton, lo conectamos a <code>GND</code> y la lectura cambia a <code>LOW</code>.
      </div>
    </div>
    <div class="p-4 rounded-lg border border-rose-400/30 bg-rose-500/10 text-sm">
      <div class="font-bold mb-2">Pull-down</div>
      <div>
        El pin queda normalmente en <code>LOW</code>. Cuando presionamos el boton, lo conectamos a <code>VCC</code> y la lectura cambia a <code>HIGH</code>.
      </div>
    </div>
    <div class="mt-3 text-sm p-3 rounded border border-amber-300/30 bg-amber-500/10 text-left">
      El ESP32 puede usar resistencias internas de pull-up y pull-down, pero siempre conviene evaluar si el circuito necesita una resistencia externa para lograr mayor estabilidad o compatibilidad con el montaje real.
    </div>
  </div>
</div>

<div class="mt-5 text-sm p-3 rounded bg-white/5 border border-white/10">
  La idea clave es evitar que el pin quede "flotando". Las resistencias pull-up y pull-down fuerzan un estado estable cuando nadie toca el boton.
</div>


---

# Ejemplo: pull-down y NeoPixel interno

<div class="grid grid-cols-2 gap-6 mt-4">
  <div class="text-left">
    <div class="p-4 rounded-lg border border-emerald-400/30 bg-emerald-500/10 text-sm">
      <div class="font-bold mb-2">Idea</div>
      <div>
        Usamos un boton en configuracion <code>pull-down</code>. Cuando no se presiona, el pin queda en <code>LOW</code>. Cuando se presiona, pasa a <code>HIGH</code> y encendemos el NeoPixel interno del ESP32-S3.
      </div>
    </div>

```cpp
const int boton = 4;

void setup() {
  pinMode(boton, INPUT_PULLDOWN);
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);
}

void loop() {
  if (digitalRead(boton) == HIGH) {
    neopixelWrite(RGB_BUILTIN, 0, 40, 0);
  } else {
    neopixelWrite(RGB_BUILTIN, 0, 0, 0);
  }
}
```

  </div>

  <div class="text-left">
    <div class="p-4 rounded-lg border border-white/20 bg-white/5 text-sm mb-4">
      <div class="font-bold mb-2">Lectura esperada</div>
      <ul class="leading-relaxed">
        <li>Boton suelto: <code>LOW</code></li>
        <li>Boton presionado: <code>HIGH</code></li>
        <li>Accion: cambiar el color del LED RGB integrado</li>
      </ul>
    </div>
    <div class="max-w-md rounded-2xl border border-yellow-200/60 bg-yellow-50/90 px-5 py-4 text-yellow-950/80 shadow-sm">
      <div class="text-xs uppercase tracking-wide opacity-70 mb-2">Precaucion</div>
      <div class="text-sm leading-snug">
        ⚠️ No conectes directamente un pin a <code>3.3V</code> y <code>GND</code> sin resistencia o sin revisar el circuito del boton. Tampoco asumas que todos los pines soportan cualquier configuracion sin mirar el pinout.
      </div>
    </div>
  </div>
</div>

---
transition: slide-up
---

# Desafío 2: ESP-NOW entre Nodo y Gateway

<div class="grid grid-cols-2 gap-6 mt-4">
  <div class="text-sm text-left">
    <div class="font-bold mb-2">Cómo funciona</div>
    <ul class="space-y-2">
      <li>El <strong>Gateway</strong> debe imprimir primero su dirección MAC.</li>
      <li>El <strong>Nodo</strong> copia esa MAC en su firmware para registrar al Gateway como <code>peer</code>.</li>
      <li>Luego el Nodo empaqueta la distancia del radar y la envía por <code>ESP-NOW</code>.</li>
      <li>El Gateway recibe el dato y actualiza el LED RGB según la cercanía detectada.</li>
    </ul>
  </div>
  <div class="text-sm text-left">
    <div class="font-bold mb-2">Orden recomendado</div>
    <ol class="space-y-2">
      <li>Cargar un sketch temporal en el Gateway para imprimir su MAC.</li>
      <li>Anotar la MAC que aparece en el monitor serial.</li>
      <li>Pegar esa MAC en el firmware del Nodo.</li>
      <li>Inicializar <code>WiFi.mode(WIFI_STA)</code> y <code>esp_now_init()</code>.</li>
      <li>Registrar el peer y recién después enviar datos.</li>
    </ol>
  </div>
</div>

<div class="mt-4 p-3 rounded bg-yellow-500/10 border border-yellow-400/30 text-sm">
Si ambos ESP32 van a enviarse datos entre sí, cada uno debe conocer la MAC del otro. Para este desafío basta con que el Nodo conozca primero la MAC del Gateway.
</div>

---
transition: fade-out
---

# Desafío 2: código base ESP-NOW

<div class="grid grid-cols-2 gap-5 mt-2">
<div>

```cpp
// Gateway: imprimir MAC
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("MAC Gateway: ");
  Serial.println(WiFi.macAddress());
}

void loop() {}
```

</div>

<div>

```cpp
// Nodo: registrar MAC del Gateway
#include <WiFi.h>
#include <esp_now.h>

uint8_t peer[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};

typedef struct {
  int radar;
  int contador;
} Payload;

Payload data = {0, 0};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_peer_info_t info = {};
  memcpy(info.peer_addr, peer, 6);
  esp_now_add_peer(&info);
}
```

</div>

</div>

---
transition: slide-left
---

# Desafío 2: envío base por ESP-NOW

```cpp
typedef struct {
  int radar;
  int contador;
} Payload;

Payload data = {0, 0};

void loop() {
  data.radar = random(0, 2);
  data.contador++;
  esp_now_send(peer, (uint8_t *)&data, sizeof(data));
  delay(1000);
}
```

---
transition: slide-left
---

# Desafío 2: radar HLK-LD2420

<div class="grid grid-cols-2 gap-6 mt-3">
<div>

**Cómo interactuar con el radar**

| HLK-LD2420 | ESP32-S3 |
|---|---|
| `VCC` | `3V3` |
| `GND` | `GND` |
| `TX` | `GPIO RX` a definir |
| `RX` | `GPIO TX` a definir |

<div class="mt-4 text-sm p-3 rounded bg-orange-500/15 border border-orange-400/40">
El radar habla por <code>UART</code>. Conviene usar un puerto serial distinto al monitor USB para no mezclar la lectura del sensor con la depuración por <code>Serial</code>.
</div>

</div>

<div class="text-sm text-left">

**Instalar librería ZIP**

1. Descargar el repositorio de la librería.
2. En Arduino IDE ir a `Sketch > Include Library > Add .ZIP Library...`
3. Seleccionar el archivo `.zip`.
4. Verificar con un sketch que `#include "LD2420.h"` compile.

**Idea general**

- La librería encapsula el protocolo serial del radar.
- Se inicializa sobre un puerto serial dedicado al radar.
- Luego se actualiza el estado del sensor y se captura la distancia detectada.
- Esa distancia se empaqueta y se envía al Gateway por `ESP-NOW`.

</div>
</div>

---
transition: fade-out
---

# Desafío 2: código base del radar

<div class="grid grid-cols-2 gap-5 mt-2">
<div>

```cpp
#include <SoftwareSerial.h>
#include "LD2420.h"

SoftwareSerial sensorSerial(8, 9); // RX, TX
LD2420 radar;

void onObjectDetected(int distance) {
  Serial.print("Object at ");
  Serial.print(distance);
  Serial.println(" cm");
}
```

</div>

<div>

```cpp
void setup() {
  Serial.begin(115200);
  sensorSerial.begin(115200);

  if (radar.begin(sensorSerial)) {
    Serial.println("Radar initialized!");
    radar.onDetection(onObjectDetected);
  }
}

void loop() {
  radar.update();
  delay(10);
}
```

</div>
</div>

---
transition: slide-up
---

# Desafío 3: configurar WiFi

```cpp
#include <WiFi.h>

const char* SSID = "NombreDeRed";
const char* PASS = "ClaveDeRed";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
```

<div class="mt-4 text-sm">
Si WiFi no conecta, revisar SSID, clave, banda de `2.4 GHz` y distancia al AP.
</div>

---
transition: fade-out
---

# Desafío 3: registrar datos en Google Sheets

<div class="grid grid-cols-2 gap-6 mt-3">
<div>

**Arquitectura simple**

1. Google Apps Script publica un endpoint web.
2. ESP32 envía un `HTTP POST`.
3. El script agrega una fila a la planilla.

```js
function doPost(e) {
  const sheet = SpreadsheetApp.getActiveSheet();
  const data = JSON.parse(e.postData.contents);
  sheet.appendRow([new Date(), data.nodo, data.valor]);
  return ContentService.createTextOutput("ok");
}
```

</div>

<div>

```cpp
#include <WiFi.h>
#include <HTTPClient.h>

void enviarDato(float valor) {
  HTTPClient http;
  http.begin("https://script.google.com/macros/s/TU_ID/exec");
  http.addHeader("Content-Type", "application/json");
  String body = "{\"nodo\":\"esp32-01\",\"valor\":" + String(valor, 2) + "}";
  int code = http.POST(body);
  Serial.println(code);
  http.end();
}
```

</div>
</div>

<div class="mt-4 p-3 rounded bg-blue-500/10 border border-blue-400/30 text-sm">
Para producción esto no es ideal, pero para casos simples sirve muy bien para registrar mediciones y evidencias rápidas.
</div>

---
transition: slide-left
---

# Entrega del laboratorio

<div class="grid grid-cols-2 gap-6 mt-4">
<div class="text-sm text-left">

**Formato y plazo**

- Entrega solo por `Canvas`.
- Fecha límite: **27 de marzo de 2026, 23:59 hrs**.
- Entregas fuera de plazo no se evalúan salvo autorización previa del equipo docente.
- Subir un único archivo comprimido `.zip`.

</div>

<div class="text-sm text-left">

**El `.zip` debe incluir**

1. Informe en `PDF`.
2. Códigos fuente de ambos `ESP32` (`.ino`).
3. Link público a `Google Sheets` y también en `README.txt`.
4. Fotografías del sistema en funcionamiento.

</div>
</div>

<div class="mt-4 p-3 rounded bg-yellow-500/10 border border-yellow-400/30 text-sm">
Mínimo esperado en fotos: circuito montado y captura de Google Sheets con datos.
</div>

---
transition: fade-out
---

# Informe y evaluación

<div class="grid grid-cols-2 gap-6 mt-4">
<div class="text-sm text-left">

**Estructura del informe**

1. Portada con equipo, integrantes, roles y fecha.
2. Materiales y justificación de pines.
3. Tabla completa de conexiones.
4. Protocolos de comunicación del sistema.
5. Arquitectura final y flujo de datos.
6. Observaciones, errores y soluciones.

</div>

<div class="text-sm text-left">

**Indicaciones del curso**

- Comentar las funciones relevantes del código.
- Explicar por qué eligieron esos GPIOs.
- Mostrar el flujo completo: radar → ESP-NOW → WiFi/HTTP → Sheets.
- Documentar incidentes reales, no solo el resultado final.
- Hay `1,0` punto base por entregar dentro de plazo.

</div>
</div>

<div class="mt-4 p-3 rounded bg-blue-500/10 border border-blue-400/30 text-sm">
Mientras más trazable sea la entrega, más fácil es evaluar su trabajo: conexiones claras, código comentado, evidencia visual y datos registrados.
</div>

---
transition: fade-out
---

<div class="h-full flex flex-col items-center justify-center text-center">
  <div class="text-2xl mb-8">Gracias por la atención</div>
  <Image src="/images/clase 2/fin.png" class="h-72 mx-auto rounded-lg" />
</div>

<style>
h1 {
  background-color: #2B90B6;
  background-image: linear-gradient(45deg, #7dd3fc 10%, #0f766e 45%, #f59e0b 90%);
  background-size: 100%;
  -webkit-background-clip: text;
  -moz-background-clip: text;
  -webkit-text-fill-color: transparent;
  -moz-text-fill-color: transparent;
}
</style>
