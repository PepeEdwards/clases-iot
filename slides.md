---
theme: seriph
background: https://images.unsplash.com/photo-1544197150-b99a580bb7a8?w=1920&q=80
class: text-center
title: Capas de Comunicación de Red
transition: slide-left
mdc: true
fonts:
  sans: Roboto
  serif: Roboto Slab
  mono: Fira Code
---

<div class="absolute inset-0 bg-black/65" />

<div class="relative z-10 flex h-full flex-col items-center justify-center">

# Capas de Comunicación de Red

## Clase 8 — Modelo OSI, protocolos y configuración en ESP32

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

# ¿Qué son las capas OSI?

<div class="mt-4 p-4 rounded-2xl border border-blue-400/30 bg-blue-500/10 text-left">
  <div class="text-xs uppercase tracking-wide opacity-60 mb-2">Definición</div>
  <div class="text-base leading-relaxed">
    El <strong>modelo OSI</strong> (Open Systems Interconnection) es un marco de referencia que divide la comunicación en red en <strong>7 capas independientes</strong>, cada una con una responsabilidad específica.
  </div>
</div>

<div class="mt-4 p-3 rounded border border-white/10 bg-white/5 text-sm italic text-center">
  "A network is nothing but a set of agreements — the layers are where those agreements are made."
  <div class="text-xs mt-1 opacity-60 not-italic">— Andrew S. Tanenbaum, Computer Networks</div>
</div>

<div class="grid grid-cols-7 gap-1 mt-5 text-center text-xs">
  <div class="p-2 rounded bg-red-500/20 border border-red-400/40 font-bold">7<br/><span class="opacity-80 font-normal">App</span></div>
  <div class="p-2 rounded bg-orange-500/20 border border-orange-400/40 font-bold">6<br/><span class="opacity-80 font-normal">Pres.</span></div>
  <div class="p-2 rounded bg-yellow-500/20 border border-yellow-400/40 font-bold">5<br/><span class="opacity-80 font-normal">Ses.</span></div>
  <div class="p-2 rounded bg-green-500/20 border border-green-400/40 font-bold">4<br/><span class="opacity-80 font-normal">Trans.</span></div>
  <div class="p-2 rounded bg-teal-500/20 border border-teal-400/40 font-bold">3<br/><span class="opacity-80 font-normal">Red</span></div>
  <div class="p-2 rounded bg-blue-500/20 border border-blue-400/40 font-bold">2<br/><span class="opacity-80 font-normal">Enlace</span></div>
  <div class="p-2 rounded bg-purple-500/20 border border-purple-400/40 font-bold">1<br/><span class="opacity-80 font-normal">Física</span></div>
</div>

<div class="mt-4 p-2 rounded bg-white/5 border border-white/10 text-xs text-center">
  En IoT usamos principalmente las capas <strong>1, 2, 3, 4 y 7</strong>. Las capas 5 y 6 suelen estar implícitas en los protocolos de aplicación.
</div>

<!--
Preguntar: ¿alguien ha escuchado hablar del modelo OSI antes? ¿En qué contexto?
La analogía clásica: enviar una carta. El sobre es capa 2 (enlace), la dirección es capa 3 (IP), el correo postal es capa 4 (transporte), y el texto es capa 7 (aplicación).
Mencionar que las capas 5 y 6 en la práctica moderna están fusionadas en protocolos como TLS/HTTPS.
-->

---
transition: slide-up
---

# Capa 1 — Física

<div class="flex items-center gap-3 mb-3 p-2 rounded bg-purple-500/10 border border-purple-400/20 text-xs">
  <div class="w-7 h-7 rounded-full bg-purple-500/30 border border-purple-400/50 flex items-center justify-center font-bold text-sm shrink-0">1</div>
  <div class="flex-1 opacity-70">Señal de radio, frecuencia, modulación — gestiona bits en el aire sin direcciones ni paquetes</div>
  <div class="flex gap-1"><span class="px-2 py-0.5 rounded bg-purple-500/20 border border-purple-400/30">2.4 GHz</span><span class="px-2 py-0.5 rounded bg-purple-500/20 border border-purple-400/30">Bluetooth</span><span class="px-2 py-0.5 rounded bg-purple-500/20 border border-purple-400/30">802.11</span></div>
</div>

<div class="grid grid-cols-2 gap-2 text-xs mb-3">
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">Qué hace esta capa</div>
    <div>Convierte bits en señales físicas — ondas de radio, pulsos de luz o voltaje. Define frecuencia, potencia de transmisión y esquema de modulación. No sabe qué significan los datos, solo cómo viajar.</div>
  </div>
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">En el ESP32</div>
    <div>El chip integra dos radios en el mismo silicio: un transceptor 802.11 b/g/n para Wi-Fi y un radio Bluetooth 5. Ambos comparten la antena pero operan en tiempos distintos.</div>
  </div>
</div>

<div class="text-xs font-bold uppercase opacity-50 mb-2 tracking-wide">¿Por qué Wi-Fi y Bluetooth usan 2.4 GHz pero son incompatibles?</div>

<div class="grid grid-cols-3 gap-3 text-xs">
  <div class="p-3 rounded bg-white/5 border border-white/10">
    <div class="font-bold mb-2 opacity-60 text-xs uppercase tracking-wide">La banda 2.4 GHz</div>
    <div class="opacity-80">Es una banda <strong>ISM</strong> (Industrial, Scientific, Medical) — libre de licencia en casi todo el mundo. Por eso la eligieron tanto Wi-Fi como Bluetooth. El resultado: <strong>conviven pero compiten</strong> por el mismo espacio de frecuencias.</div>
  </div>
  <div class="p-3 rounded bg-blue-500/10 border border-blue-400/20">
    <div class="font-bold mb-2">Wi-Fi — 802.11</div>
    <div class="opacity-80">Divide la banda en <strong>13 canales anchos (22 MHz)</strong>. Usa <strong>OFDM</strong>: transmite múltiples subportadoras simultáneas. Diseñado para <strong>alto throughput</strong> — streaming, web, archivos grandes.</div>
  </div>
  <div class="p-3 rounded bg-purple-500/10 border border-purple-400/20">
    <div class="font-bold mb-2">Bluetooth / BLE</div>
    <div class="opacity-80">Divide la banda en <strong>40 canales estrechos (2 MHz)</strong>. Usa <strong>FHSS</strong>: salta de canal en canal 1600 veces/segundo. Diseñado para <strong>bajo consumo</strong> — sensores, wearables, beacons.</div>
  </div>
</div>

<div class="mt-3 p-2 rounded bg-white/5 border border-white/10 text-xs text-center">
  Misma frecuencia, arquitecturas opuestas — Wi-Fi prioriza velocidad con canales anchos; Bluetooth prioriza eficiencia con canales estrechos y salto de frecuencia.
</div>

<!--
Analogía: Wi-Fi es como una autopista de 4 pistas — mucho flujo, pero ocupa espacio. BLE es como una moto que zigzaguea entre carriles cambiando rápido.
OFDM (Wi-Fi): divide el canal en cientos de subportadoras paralelas — resistente a interferencia y muy eficiente en espacio.
FHSS (Bluetooth): el salto de frecuencia lo hace casi inmune a interferencia puntual — si un canal está ocupado, salta al siguiente en microsegundos.
Preguntar: ¿por qué creen que el microondas interfiere con el Wi-Fi pero no tanto con el BLE?
Respuesta: el microondas genera ruido en toda la banda 2.4 GHz, pero BLE esquiva rápido los canales afectados. Wi-Fi se queda en su canal y sufre más.
-->

---

# Capa 2 — Enlace de Datos

<div class="flex items-center gap-3 mb-3 p-2 rounded bg-blue-500/10 border border-blue-400/20 text-xs">
  <div class="w-7 h-7 rounded-full bg-blue-500/30 border border-blue-400/50 flex items-center justify-center font-bold text-sm shrink-0">2</div>
  <div class="flex-1 opacity-70">Acceso al medio físico compartido — identifica dispositivos por dirección MAC y organiza datos en frames</div>
  <div class="flex gap-1"><span class="px-2 py-0.5 rounded bg-blue-500/20 border border-blue-400/30">LAN/Wi-Fi</span><span class="px-2 py-0.5 rounded bg-blue-500/20 border border-blue-400/30">ESP-NOW</span></div>
</div>

<div class="grid grid-cols-2 gap-2 text-xs mb-3">
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">Qué hace esta capa</div>
    <div>Empaqueta bits en <strong>frames</strong> con dirección MAC origen y destino. Gestiona quién habla en la red local usando CSMA/CA en Wi-Fi.</div>
  </div>
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">En el ESP32</div>
    <div>Modo <strong>STA</strong> (conecta a AP) o <strong>AP</strong> (crea red propia). La MAC es única por chip. ESP-NOW opera directamente en esta capa.</div>
  </div>
</div>

<div class="text-xs font-bold uppercase opacity-50 mb-2 tracking-wide">Protocolos</div>

<div class="grid grid-cols-2 gap-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-2 rounded bg-blue-500/10 border border-blue-400/20">
      <div class="font-bold mb-1">LAN / Wi-Fi</div>
      <div class="opacity-80">Red local — misma subred sin pasar por router. El ESP32 obtiene su MAC de fábrica. Modos: WIFI_STA, WIFI_AP, WIFI_AP_STA.</div>
    </div>
    <div class="p-2 rounded bg-blue-500/10 border border-blue-400/20">
      <div class="font-bold mb-1">ESP-NOW</div>
      <div class="opacity-80">Protocolo Espressif sobre 802.11. Sin router, sin IP — comunica ESP32 directamente por MAC. Hasta 20 peers, payload 250 bytes, latencia ~1 ms.</div>
    </div>
  </div>
  <div class="text-left">

```cpp
#include <WiFi.h>
#include <esp_now.h>

// Capa 2: modo de acceso al medio
WiFi.mode(WIFI_STA);         // Station — se asocia a un AP
WiFi.macAddress();           // dirección MAC — identidad capa 2

// ESP-NOW: peer-to-peer sobre MAC (sin IP)
uint8_t peer[] = {0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
esp_now_init();
esp_now_peer_info_t info = {};
memcpy(info.peer_addr, peer, 6);
esp_now_add_peer(&info);
esp_now_send(peer, (uint8_t*)"hola", 4);
```

  </div>
</div>

<!--
Diferencia clave: MAC es la identidad de capa 2 (hardware), IP es capa 3 (software).
Analogía: MAC = DNI, IP = domicilio postal.
ESP-NOW es perfecto para sensores en campo donde no hay router — huerto, invernadero, obra.
-->

---

# Capa 3 — Red

<div class="flex items-center gap-3 mb-3 p-2 rounded bg-teal-500/10 border border-teal-400/20 text-xs">
  <div class="w-7 h-7 rounded-full bg-teal-500/30 border border-teal-400/50 flex items-center justify-center font-bold text-sm shrink-0">3</div>
  <div class="flex-1 opacity-70">Direccionamiento y enrutamiento — permite que paquetes crucen redes distintas hasta llegar al destino</div>
  <div class="flex gap-1"><span class="px-2 py-0.5 rounded bg-teal-500/20 border border-teal-400/30">IP</span><span class="px-2 py-0.5 rounded bg-teal-500/20 border border-teal-400/30">Wi-Fi → router</span></div>
</div>

<div class="grid grid-cols-2 gap-2 text-xs mb-3">
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">Qué hace esta capa</div>
    <div>Asigna una dirección lógica (IP) a cada dispositivo. El router decide por qué camino viaja cada paquete para llegar a su destino.</div>
  </div>
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">En el ESP32</div>
    <div>Obtiene IP por DHCP (automático) o configuración estática. <code>WiFi.localIP()</code> retorna la IP asignada en capa 3.</div>
  </div>
</div>

<div class="text-xs font-bold uppercase opacity-50 mb-2 tracking-wide">Protocolos</div>

<div class="grid grid-cols-2 gap-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-2 rounded bg-teal-500/10 border border-teal-400/20">
      <div class="font-bold mb-1">IPv4 + DHCP</div>
      <div class="opacity-80"><strong>DHCP</strong> (Dynamic Host Configuration Protocol) — protocolo que le pide al router una IP disponible al conectarse. El router la asigna y la recuerda. El ESP32 no necesita configuración manual.</div>
    </div>
    <div class="p-2 rounded bg-teal-500/10 border border-teal-400/20">
      <div class="font-bold mb-1">IP Estática</div>
      <div class="opacity-80">IP fija configurada manualmente con <code>WiFi.config()</code>. Necesaria cuando el ESP32 es servidor y otros dispositivos deben conocer su dirección de antemano.</div>
    </div>
  </div>
  <div class="text-left">

```cpp
// DHCP — el router asigna la IP (capa 3)
WiFi.begin("MiRed", "clave");
WiFi.localIP();   // ej. 192.168.1.45 (asignada)
WiFi.gatewayIP(); // ej. 192.168.1.1  (router)

// IP estática — fija, no cambia al reiniciar
IPAddress ip(192,168,1,100);
IPAddress gw(192,168,1,1);
IPAddress sn(255,255,255,0);
WiFi.config(ip, gw, sn);
WiFi.begin("MiRed", "clave");
// → siempre 192.168.1.100
```

  </div>
</div>

<!--
Preguntar: ¿qué IP tiene tu laptop ahora? ¿y tu celular?
Subnets: 192.168.1.x — todos en /24 se comunican directamente sin pasar por gateway.
IP estática es crítica cuando el ESP32 expone un webhook o API REST.
-->

---

# Capa 4 — Transporte

<div class="flex items-center gap-3 mb-3 p-2 rounded bg-green-500/10 border border-green-400/20 text-xs">
  <div class="w-7 h-7 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold text-sm shrink-0">4</div>
  <div class="flex-1 opacity-70">Entrega confiable (TCP) o rápida (UDP) de datos extremo a extremo — los puertos identifican el proceso destino</div>
  <div class="flex gap-1"><span class="px-2 py-0.5 rounded bg-green-500/20 border border-green-400/30">TCP</span><span class="px-2 py-0.5 rounded bg-green-500/20 border border-green-400/30">UDP</span><span class="px-2 py-0.5 rounded bg-green-500/20 border border-green-400/30">Puertos</span></div>
</div>

<div class="grid grid-cols-2 gap-2 text-xs mb-3">
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">Qué hace esta capa</div>
    <div>Segmenta datos, controla flujo y errores. TCP garantiza entrega ordenada. UDP prioriza velocidad. Los puertos separan servicios en un mismo host.</div>
  </div>
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">En el ESP32</div>
    <div><code>WiFiClient</code> usa TCP. <code>WiFiUDP</code> usa UDP. El número de puerto es parte del socket — por eso MQTT usa 1883 y no 80.</div>
  </div>
</div>

<div class="text-xs font-bold uppercase opacity-50 mb-2 tracking-wide">Protocolos</div>

<div class="grid grid-cols-2 gap-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="grid grid-cols-2 gap-2">
      <div class="p-2 rounded bg-green-500/10 border border-green-400/20">
        <div class="font-bold mb-1">TCP</div>
        <div class="opacity-80">3-way handshake, garantía de entrega ordenada. Usado por HTTP, MQTT, WebSocket.</div>
      </div>
      <div class="p-2 rounded bg-yellow-500/10 border border-yellow-400/20">
        <div class="font-bold mb-1">UDP</div>
        <div class="opacity-80">Sin conexión, sin garantía, baja latencia. Usado por NTP, DNS, streaming.</div>
      </div>
    </div>
    <div class="p-2 rounded bg-white/5 border border-white/10">
      <div class="font-bold mb-1">Puertos bien conocidos</div>
      <div class="grid grid-cols-3 gap-x-2 gap-y-0.5 font-mono mt-1">
        <div class="opacity-50 font-sans">Protocolo</div><div class="opacity-50 font-sans">Puerto</div><div class="opacity-50 font-sans">Transport</div>
        <div>HTTP</div><div>80</div><div>TCP</div>
        <div>HTTPS</div><div>443</div><div>TCP</div>
        <div>MQTT</div><div>1883</div><div>TCP</div>
        <div>MQTT+TLS</div><div>8883</div><div>TCP</div>
        <div>NTP</div><div>123</div><div>UDP</div>
      </div>
    </div>
  </div>
  <div class="text-left">

```cpp
// TCP — conexión orientada, garantía de entrega
WiFiClient client;
client.connect("broker.io", 1883); // host + puerto
client.print("datos");
client.stop();

// UDP — sin conexión, baja latencia
WiFiUDP udp;
udp.beginPacket("pool.ntp.org", 123); // puerto 123
udp.endPacket();
```

  </div>
</div>

<!--
Analogía de puertos: la IP es la dirección del edificio, el puerto es el número de departamento.
Por eso pueden correr MQTT (1883) y HTTP (80) en el mismo servidor sin conflicto.
TCP handshake: SYN → SYN-ACK → ACK — antes de enviar un solo byte de datos.
-->

---

# Capas 5 y 6 — Sesión y Presentación

<div class="grid grid-cols-2 gap-2 mb-3">
  <div class="flex items-center gap-3 p-2 rounded bg-yellow-500/10 border border-yellow-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-yellow-500/30 border border-yellow-400/50 flex items-center justify-center font-bold shrink-0 text-xs">5</div>
    <div><span class="font-semibold">Sesión</span><span class="opacity-60 ml-2">Apertura y cierre de conexiones persistentes</span></div>
    <span class="px-1.5 py-0.5 rounded bg-yellow-500/20 border border-yellow-400/30 text-xs ml-auto">WebSocket</span>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-orange-500/10 border border-orange-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-orange-500/30 border border-orange-400/50 flex items-center justify-center font-bold shrink-0 text-xs">6</div>
    <div><span class="font-semibold">Presentación</span><span class="opacity-60 ml-2">Cifrado y formato de datos</span></div>
    <div class="flex gap-1 ml-auto"><span class="px-1.5 py-0.5 rounded bg-orange-500/20 border border-orange-400/30 text-xs">TLS/SSL</span><span class="px-1.5 py-0.5 rounded bg-orange-500/20 border border-orange-400/30 text-xs">JSON</span></div>
  </div>
</div>

<div class="grid grid-cols-2 gap-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-2 rounded bg-yellow-500/10 border border-yellow-400/20">
      <div class="font-bold mb-1">WebSocket — Capa 5</div>
      <div class="opacity-80">Empieza como HTTP (puerto 80/443) y hace <em>upgrade</em> a canal bidireccional full-duplex persistente. El servidor puede enviar datos sin que el cliente pregunte.</div>
    </div>
    <div class="p-2 rounded bg-orange-500/10 border border-orange-400/20">
      <div class="font-bold mb-1">TLS/SSL — Capa 6</div>
      <div class="opacity-80">Cifra el canal TCP antes de enviar datos. HTTPS = HTTP + TLS. MQTT+TLS usa puerto 8883. El ESP32 verifica el certificado del servidor.</div>
    </div>
    <div class="p-2 rounded bg-orange-500/10 border border-orange-400/20">
      <div class="font-bold mb-1">JSON — Capa 6</div>
      <div class="opacity-80">Formato de serialización de datos. Estándar de facto en APIs REST y MQTT. Librería: <code>ArduinoJson</code>.</div>
    </div>
    <div class="p-3 rounded-2xl border border-yellow-400/40 bg-yellow-500/10 flex items-center gap-3">
      <div class="text-2xl shrink-0">🤔</div>
      <div>
        <div class="font-bold text-xs">¿Cuál es la diferencia entre HTTP y HTTPS?</div>
      </div>
    </div>
  </div>
  <div class="text-left">

```cpp
// Capa 5 — WebSocket: sesión bidireccional persistente
WebsocketsClient ws;
ws.onMessage([](WebsocketsMessage m){
  // servidor puede enviar sin que cliente pregunte
});
ws.connect("ws://192.168.1.10:8080/ws");
ws.send("{\"val\":25.3}"); // canal siempre abierto
ws.poll(); // llamar en loop()

// Capa 6 — JSON: serializar / deserializar datos
StaticJsonDocument<64> doc;
doc["temp"] = 25.3;
String body;
serializeJson(doc, body);   // objeto → string
deserializeJson(doc, body); // string → objeto
```

  </div>
</div>

<!--
WebSocket resuelve el polling: en vez de hacer GET cada 5s, el servidor notifica al cliente cuando hay datos nuevos.
TLS en ESP32: usar WiFiClientSecure con setCACert() para HTTPS. setInsecure() solo en desarrollo.
-->

---
transition: slide-up
---

# Capa 7 — Aplicación: HTTP y REST

<div class="flex items-center gap-3 mb-3 p-2 rounded bg-red-500/10 border border-red-400/20 text-xs">
  <div class="w-7 h-7 rounded-full bg-red-500/30 border border-red-400/50 flex items-center justify-center font-bold text-sm shrink-0">7</div>
  <div class="flex-1 opacity-70">La capa que ve el programador — define el idioma con que dos apps intercambian datos</div>
  <div class="flex gap-1"><span class="px-2 py-0.5 rounded bg-red-500/20 border border-red-400/30">HTTP/S</span><span class="px-2 py-0.5 rounded bg-red-500/20 border border-red-400/30">REST</span><span class="px-2 py-0.5 rounded bg-red-500/20 border border-red-400/30">MQTT</span><span class="px-2 py-0.5 rounded bg-red-500/20 border border-red-400/30">Webhook</span></div>
</div>

<div class="grid grid-cols-2 gap-2 text-xs mb-3">
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">Qué hace esta capa</div>
    <div>Define el idioma con que dos apps intercambian datos. No se preocupa de cómo llegan los bytes — eso lo resuelven las capas inferiores.</div>
  </div>
  <div class="p-2 rounded bg-white/5 border border-white/10">
    <div class="font-bold uppercase opacity-50 mb-1 tracking-wide text-xs">En el ESP32</div>
    <div>Actúa como <strong>cliente</strong> (consume APIs) o <strong>servidor</strong> (expone sus datos). Aquí escribes la lógica: qué envías, cuándo y cómo interpretas.</div>
  </div>
</div>

<div class="text-xs font-bold uppercase opacity-50 mb-2 tracking-wide">Protocolos</div>

<div class="grid grid-cols-2 gap-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-2 rounded bg-red-500/10 border border-red-400/20">
      <div class="font-bold mb-1">HTTP / HTTPS</div>
      <div class="opacity-80">Solicitud-respuesta. El cliente pide, el servidor responde. Stateless — cada request es independiente. HTTPS agrega TLS. Puerto 80 / 443.</div>
    </div>
    <div class="p-2 rounded bg-red-500/10 border border-red-400/20">
      <div class="font-bold mb-1">API / REST</div>
      <div class="opacity-80"> Es una arquitectura que trabaja sobre HTTP. Usa URLs como recursos <code>/sensor/temp</code> y verbos HTTP (GET, POST, PUT, DELETE). Respuestas en JSON.</div>
    </div>
  </div>
  <div class="text-left">

```cpp
HTTPClient http;

// GET — pedir un recurso REST
http.begin("http://api.io/sensor/temp");
int code = http.GET();    // → 200 OK
String body = http.getString(); // → {"temp":25.3}
http.end();

// POST — enviar datos al servidor
http.begin("http://api.io/data");
http.addHeader("Content-Type","application/json");
http.POST("{\"temp\":25.3}");
http.end();
```

  </div>
</div>

<!--
HTTP es la base de toda la web. REST es la arquitectura más común en servicios cloud — ThingSpeak, Firebase, InfluxDB usan REST APIs.
Diferencia REST vs RPC: REST organiza recursos (/sensor/1), RPC organiza acciones (getSensor(1)).
-->
---

# Capa 7 — MQTT y Webhook

<div class="flex items-center gap-3 mb-3 p-2 rounded bg-red-500/10 border border-red-400/20 text-xs">
  <div class="w-7 h-7 rounded-full bg-red-500/30 border border-red-400/50 flex items-center justify-center font-bold text-sm shrink-0">7</div>
  <div class="flex-1 opacity-70">Aplicación — patrones de comunicación diseñados para IoT y eventos en tiempo real</div>
  <div class="flex gap-1"><span class="px-2 py-0.5 rounded bg-red-500/20 border border-red-400/30">MQTT</span><span class="px-2 py-0.5 rounded bg-red-500/20 border border-red-400/30">Webhook</span></div>
</div>

<div class="grid grid-cols-2 gap-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-2 rounded bg-red-500/10 border border-red-400/20">
      <div class="font-bold mb-1">MQTT</div>
      <div class="opacity-80">Publicación-suscripción sobre TCP. El <strong>broker</strong> es un servidor intermediario que recibe mensajes y los reenvía a quien corresponde — ningún dispositivo habla directamente con otro. El ESP32 publica en un <em>topic</em> (<code>casa/temp</code>) y cualquier suscriptor lo recibe. Puerto 1883 / 8883 (TLS).</div>
    </div>
    <div class="p-2 rounded bg-red-500/10 border border-red-400/20">
      <div class="font-bold mb-1">Webhook</div>
      <div class="opacity-80">El ESP32 expone una URL y <strong>espera que el servidor la llame</strong> cuando ocurre un evento — al revés de HTTP normal donde el ESP32 pregunta. Útil para recibir comandos o notificaciones desde una app web, un bot de Telegram sin estar consultando constantemente.</div>
    </div>
    <div class="p-2 rounded bg-white/5 border border-white/10">
      <div class="font-bold mb-1 opacity-70">Comparativa de patrones</div>
      <div class="grid grid-cols-3 gap-x-2 gap-y-0.5 mt-1">
        <div class="opacity-50">Patrón</div><div class="opacity-50">Quién inicia</div><div class="opacity-50">Uso ideal</div>
        <div>HTTP</div><div>Cliente</div><div>APIs REST</div>
        <div>WebSocket</div><div>Ambos</div><div>Tiempo real</div>
        <div>MQTT</div><div>Broker</div><div>IoT masivo</div>
        <div>Webhook</div><div>Servidor</div><div>Eventos</div>
      </div>
    </div>
  </div>
  <div class="text-left">

```cpp
// MQTT — pub/sub a través del broker
PubSubClient mqtt(wifiClient);
mqtt.setServer("broker.io", 1883);
mqtt.connect("ESP32");
mqtt.subscribe("casa/led");       // escuchar topic
mqtt.publish("casa/temp", "25.3"); // publicar topic
mqtt.loop(); // mantener conexión (en loop())

// Webhook — ESP32 expone endpoint, servidor llama
AsyncWebServer server(80);
server.on("/webhook", HTTP_POST, handler);
server.begin();
```

  </div>
</div>

<!--
MQTT fue diseñado por IBM en 1999 para monitorear oleoductos por satélite — ancho de banda limitado, conexión inestable.
El broker desacopla productores de consumidores: el sensor no sabe quién lo escucha.
Webhook requiere que el ESP32 tenga IP conocida — usar IP estática o ngrok en desarrollo.
-->

---
transition: slide-up
---

# Resumen — Protocolos por Capa OSI

<div class="flex flex-col gap-1 mt-3">
  <div class="flex items-center gap-3 p-2 rounded bg-red-500/10 border border-red-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-red-500/30 border border-red-400/50 flex items-center justify-center font-bold shrink-0 text-xs">7</div>
    <div class="flex-1"><span class="font-semibold">Aplicación</span></div>
    <div class="flex gap-1 flex-wrap"><span class="px-1.5 py-0.5 rounded bg-red-500/20 border border-red-400/30">HTTP — solicitud/respuesta, stateless, puerto 80/443</span><span class="px-1.5 py-0.5 rounded bg-red-500/20 border border-red-400/30">REST — recursos + verbos HTTP</span><span class="px-1.5 py-0.5 rounded bg-red-500/20 border border-red-400/30">MQTT — pub/sub, broker, 1883</span><span class="px-1.5 py-0.5 rounded bg-red-500/20 border border-red-400/30">Webhook — HTTP POST invertido</span></div>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-orange-500/10 border border-orange-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-orange-500/30 border border-orange-400/50 flex items-center justify-center font-bold shrink-0 text-xs">6</div>
    <div class="flex-1"><span class="font-semibold">Presentación</span></div>
    <div class="flex gap-1"><span class="px-1.5 py-0.5 rounded bg-orange-500/20 border border-orange-400/30">TLS/SSL — cifrado sobre TCP</span><span class="px-1.5 py-0.5 rounded bg-orange-500/20 border border-orange-400/30">JSON — formato de intercambio</span></div>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-yellow-500/10 border border-yellow-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-yellow-500/30 border border-yellow-400/50 flex items-center justify-center font-bold shrink-0 text-xs">5</div>
    <div class="flex-1"><span class="font-semibold">Sesión</span></div>
    <div class="flex gap-1"><span class="px-1.5 py-0.5 rounded bg-yellow-500/20 border border-yellow-400/30">WebSocket — full-duplex persistente sobre HTTP</span></div>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-green-500/10 border border-green-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0 text-xs">4</div>
    <div class="flex-1"><span class="font-semibold">Transporte</span></div>
    <div class="flex gap-1"><span class="px-1.5 py-0.5 rounded bg-green-500/20 border border-green-400/30">TCP — garantía de entrega</span><span class="px-1.5 py-0.5 rounded bg-green-500/20 border border-green-400/30">UDP — baja latencia</span><span class="px-1.5 py-0.5 rounded bg-green-500/20 border border-green-400/30">Puertos — 80 · 443 · 1883</span></div>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-teal-500/10 border border-teal-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-teal-500/30 border border-teal-400/50 flex items-center justify-center font-bold shrink-0 text-xs">3</div>
    <div class="flex-1"><span class="font-semibold">Red</span></div>
    <div class="flex gap-1"><span class="px-1.5 py-0.5 rounded bg-teal-500/20 border border-teal-400/30">IP — DHCP o estática, WiFi.localIP()</span></div>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-blue-500/10 border border-blue-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-blue-500/30 border border-blue-400/50 flex items-center justify-center font-bold shrink-0 text-xs">2</div>
    <div class="flex-1"><span class="font-semibold">Enlace de datos</span></div>
    <div class="flex gap-1"><span class="px-1.5 py-0.5 rounded bg-blue-500/20 border border-blue-400/30">LAN — MAC, frames, STA/AP mode</span><span class="px-1.5 py-0.5 rounded bg-blue-500/20 border border-blue-400/30">ESP-NOW — peer-to-peer, 250 B, sin router</span></div>
  </div>
  <div class="flex items-center gap-3 p-2 rounded bg-purple-500/10 border border-purple-400/20 text-xs">
    <div class="w-6 h-6 rounded-full bg-purple-500/30 border border-purple-400/50 flex items-center justify-center font-bold shrink-0 text-xs">1</div>
    <div class="flex-1"><span class="font-semibold">Física</span></div>
    <div class="flex gap-1"><span class="px-1.5 py-0.5 rounded bg-purple-500/20 border border-purple-400/30">Wi-Fi 802.11 — OFDM, 2.4 GHz, 150 Mbps</span><span class="px-1.5 py-0.5 rounded bg-purple-500/20 border border-purple-400/30">BLE — GFSK, 40 ch, baja energía</span></div>
  </div>
</div>

<div class="mt-3 p-2 rounded bg-white/5 border border-white/10 text-xs text-center">
  Pregunta: si el ESP32 publica temperatura por MQTT a un broker en la nube, ¿qué capas OSI intervienen?
</div>

<!--
La respuesta: Capa 1 (Wi-Fi radio), Capa 2 (frame Wi-Fi + MAC), Capa 3 (IP + routing), Capa 4 (TCP puerto 1883), Capa 7 (MQTT publish).
Dejar abierta la discusión: ¿dónde guardamos los datos del broker? → bases de datos, próxima clase.
-->

---

# Herramientas para Desarrollo Ágil de Sistemas IoT

<div class="grid grid-cols-2 gap-4 mt-4 text-xs">

  <div class="p-4 rounded-lg border border-green-400/40 bg-green-500/10">
    <div class="flex items-center gap-2 mb-2">
      <div class="font-bold text-sm">FastAPI</div>
      <span class="px-1.5 py-0.5 rounded bg-green-500/20 border border-green-400/30 text-xs">Python</span>
      <span class="px-1.5 py-0.5 rounded bg-green-500/20 border border-green-400/30 text-xs">Backend</span>
    </div>
    <div class="opacity-80 mb-3">Framework para crear APIs REST en Python en minutos. Genera documentación interactiva automáticamente en <code>/docs</code>. El ESP32 hace POST a un endpoint y FastAPI guarda el dato, lo procesa o lo reenvía.</div>
    <div class="font-mono bg-black/30 rounded p-2 leading-relaxed text-xs">
      <div class="opacity-50"># instalar y correr</div>
      <div>pip install fastapi uvicorn</div>
      <div>uvicorn main:app --reload</div>
    </div>
  </div>

  <div class="p-4 rounded-lg border border-blue-400/40 bg-blue-500/10">
    <div class="flex items-center gap-2 mb-2">
      <div class="font-bold text-sm">Supabase</div>
      <span class="px-1.5 py-0.5 rounded bg-blue-500/20 border border-blue-400/30 text-xs">API + DB</span>
      <span class="px-1.5 py-0.5 rounded bg-blue-500/20 border border-blue-400/30 text-xs">Cloud</span>
    </div>
    <div class="opacity-80 mb-3">Plataforma open source que combina PostgreSQL con una API REST generada automáticamente. Sin escribir backend — creas la tabla y ya tienes endpoints para insertar y consultar datos desde el ESP32.</div>
    <div class="font-mono bg-black/30 rounded p-2 leading-relaxed text-xs">
      <div class="opacity-50"># ESP32 inserta directo via REST</div>
      <div>POST /rest/v1/lecturas</div>
      <div>{"temp": 25.3, "hum": 60}</div>
    </div>
  </div>

  <div class="p-4 rounded-lg border border-purple-400/40 bg-purple-500/10">
    <div class="flex items-center gap-2 mb-2">
      <div class="font-bold text-sm">PostgreSQL</div>
      <span class="px-1.5 py-0.5 rounded bg-purple-500/20 border border-purple-400/30 text-xs">Base de datos</span>
    </div>
    <div class="opacity-80">Base de datos relacional robusta y de código abierto. Guarda las lecturas de sensores con timestamps, permite consultas SQL complejas y escala a millones de registros. Es la base de datos que usa Supabase internamente.</div>
  </div>

  <div class="p-4 rounded-lg border border-orange-400/40 bg-orange-500/10">
    <div class="flex items-center gap-2 mb-2">
      <div class="font-bold text-sm">Looker Studio</div>
      <span class="px-1.5 py-0.5 rounded bg-orange-500/20 border border-orange-400/30 text-xs">Dashboard</span>
      <span class="px-1.5 py-0.5 rounded bg-orange-500/20 border border-orange-400/30 text-xs">Google</span>
    </div>
    <div class="opacity-80">Herramienta gratuita de Google para crear dashboards interactivos. Se conecta directamente a PostgreSQL o Supabase y visualiza las lecturas del ESP32 en gráficos en tiempo real — sin escribir código de frontend.</div>
  </div>

</div>

<div class="mt-4 p-2 rounded bg-white/5 border border-white/10 text-xs text-center">
  Flujo completo: <strong>ESP32</strong> → POST → <strong>FastAPI / Supabase</strong> → guarda en <strong>PostgreSQL</strong> → visualiza en <strong>Looker Studio</strong>
</div>

<!--
FastAPI genera /docs automáticamente con Swagger UI — mostrar en vivo cómo se ve la documentación interactiva.
Supabase tiene plan gratuito generoso — ideal para proyectos de curso. Crear la tabla en la interfaz web y en segundos tienes una API REST lista.
Looker Studio (antes Google Data Studio) — conectar a Supabase vía PostgreSQL connector, arrastrar campos y generar gráficos de línea de temperatura en tiempo real.
PostgreSQL en local: docker run -e POSTGRES_PASSWORD=pass -p 5432:5432 postgres
-->

---

# ¿Qué es REST y para qué sirven sus requests?

<div class="mt-3 p-3 rounded-2xl border border-red-400/30 bg-red-500/10 text-xs text-left mb-4">
  <strong>REST</strong> (Representational State Transfer) es una forma de organizar una API usando HTTP. Cada <strong>recurso</strong> tiene una URL fija (<code>/sensores/1</code>) y se opera sobre él usando el <strong>verbo</strong> del request — no el nombre de la función.
</div>

<div class="grid grid-cols-2 gap-3 text-xs">
  <div class="flex flex-col gap-2">
    <div class="p-3 rounded-lg border border-blue-400/40 bg-blue-500/10">
      <div class="flex items-center gap-2 mb-1"><span class="font-mono font-bold text-blue-300">GET</span><span class="opacity-60">— Leer</span></div>
      <div class="opacity-80">Pide datos al servidor. No modifica nada. El recurso se identifica en la URL. No lleva body.</div>
      <div class="font-mono opacity-50 mt-1">GET /sensores/1 → {"temp": 25.3}</div>
    </div>
    <div class="p-3 rounded-lg border border-green-400/40 bg-green-500/10">
      <div class="flex items-center gap-2 mb-1"><span class="font-mono font-bold text-green-300">POST</span><span class="opacity-60">— Crear</span></div>
      <div class="opacity-80">Envía datos nuevos al servidor en el body. Crea un nuevo registro. El servidor responde con el objeto creado.</div>
      <div class="font-mono opacity-50 mt-1">POST /lecturas {"temp":25.3} → 201</div>
    </div>
  </div>
  <div class="flex flex-col gap-2">
    <div class="p-3 rounded-lg border border-yellow-400/40 bg-yellow-500/10">
      <div class="flex items-center gap-2 mb-1"><span class="font-mono font-bold text-yellow-300">PUT</span><span class="opacity-60">— Reemplazar</span></div>
      <div class="opacity-80">Reemplaza completamente un recurso existente con los datos del body.</div>
      <div class="font-mono opacity-50 mt-1">PUT /sensores/1 {"nombre":"sala"}</div>
    </div>
    <div class="p-3 rounded-lg border border-orange-400/40 bg-orange-500/10">
      <div class="flex items-center gap-2 mb-1"><span class="font-mono font-bold text-orange-300">PATCH</span><span class="opacity-60">— Modificar</span></div>
      <div class="opacity-80">Actualiza solo los campos enviados en el body, sin tocar el resto del recurso.</div>
      <div class="font-mono opacity-50 mt-1">PATCH /sensores/1 {"activo":false}</div>
    </div>
    <div class="p-3 rounded-lg border border-red-400/40 bg-red-500/10">
      <div class="flex items-center gap-2 mb-1"><span class="font-mono font-bold text-red-300">DELETE</span><span class="opacity-60">— Eliminar</span></div>
      <div class="opacity-80">Elimina el recurso indicado en la URL. No lleva body.</div>
      <div class="font-mono opacity-50 mt-1">DELETE /sensores/1 → 204 No Content</div>
    </div>
  </div>
</div>

<div class="mt-3 p-2 rounded bg-white/5 border border-white/10 text-xs text-center">
  En IoT el ESP32 usa principalmente <strong>GET</strong> (leer datos de un servidor) y <strong>POST</strong> (enviar lecturas). Los veremos en detalle en la siguiente slide.
</div>

<!--
Analogía: la URL es el sustantivo (/sensores/1), el verbo HTTP es la acción (GET, POST, DELETE).
En REST nunca verías /getSensor o /deleteSensor — la acción la define el verbo, no la URL.
PUT vs PATCH: PUT manda el objeto completo y reemplaza todo. PATCH manda solo lo que cambió.
En IoT casi nunca se usa DELETE o PUT desde el ESP32 — son más comunes en interfaces de administración.
-->

---

# REST — GET y POST en detalle

<div class="grid grid-cols-2 gap-3 mt-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-3 rounded-lg border border-blue-400/40 bg-blue-500/10">
      <div class="font-bold mb-2">GET — leer un recurso</div>
      <div class="opacity-80 mb-2">Pide datos al servidor. El recurso se identifica en la URL. No lleva cuerpo (body). El servidor responde con JSON.</div>
      <div class="font-mono bg-black/30 rounded p-2 leading-relaxed">
        <div class="opacity-50">→ Request</div>
        <div>GET /api/sensor/1 HTTP/1.1</div>
        <div>Host: miservidor.com</div>
        <div class="mt-1 opacity-50">← Response 200 OK</div>
        <div>{"id":1, "temp":25.3, "hum":60}</div>
      </div>
    </div>
    <div class="p-3 rounded-lg border border-green-400/40 bg-green-500/10">
      <div class="font-bold mb-2">POST — enviar datos nuevos</div>
      <div class="opacity-80 mb-2">Manda datos al servidor en el body del request. Se usa para crear registros, enviar lecturas, autenticar, etc.</div>
      <div class="font-mono bg-black/30 rounded p-2 leading-relaxed">
        <div class="opacity-50">→ Request</div>
        <div>POST /api/lecturas HTTP/1.1</div>
        <div>Content-Type: application/json</div>
        <div>{"temp":25.3, "hum":60}</div>
        <div class="mt-1 opacity-50">← Response 201 Created</div>
        <div>{"id":42, "status":"ok"}</div>
      </div>
    </div>
  </div>
  <div class="text-left">

```cpp
#include <HTTPClient.h>
HTTPClient http;

// GET — leer temperatura del servidor
http.begin("http://api.io/sensor/1");
int code = http.GET();
if (code == 200) {
  String body = http.getString();
  // body = {"id":1,"temp":25.3,"hum":60}
}
http.end();

// POST — enviar nueva lectura
http.begin("http://api.io/lecturas");
http.addHeader("Content-Type",
               "application/json");
int code2 = http.POST(
  "{\"temp\":25.3,\"hum\":60}"
);
// code2 == 201 → registro creado
http.end();
```

  </div>
</div>

<div class="mt-3 p-2 rounded bg-white/5 border border-white/10 text-xs text-center">
  Los <strong>códigos de respuesta</strong> indican el resultado: <strong>200</strong> OK · <strong>201</strong> Created · <strong>400</strong> Bad Request · <strong>401</strong> Unauthorized · <strong>404</strong> Not Found · <strong>500</strong> Server Error
</div>

<!--
Preguntar: ¿cuándo usarían GET y cuándo POST?
GET = cuando quieren leer el estado de un sensor remoto. POST = cuando el ESP32 envía una nueva medición a la base de datos.
Los códigos de respuesta son importantes — el ESP32 debe verificar que el código sea 200/201 antes de asumir que el servidor recibió los datos.
Mostrar en Postman cómo se ve un GET y un POST reales hacia una API pública de prueba como jsonplaceholder.typicode.com.
-->

---

# API REST con FastAPI — Python

<div class="grid grid-cols-2 gap-4 mt-4">
  <div class="flex flex-col gap-3 text-xs">
    <div class="p-3 rounded-lg border border-green-400/40 bg-green-500/10">
      <div class="font-bold mb-2">¿Cómo funciona?</div>
      <div class="opacity-80">FastAPI convierte funciones Python en endpoints HTTP. El decorador define el verbo y la ruta. Los datos se guardan en un diccionario en memoria — simple para prototipo.</div>
    </div>
    <div class="p-3 rounded bg-white/5 border border-white/10">
      <div class="font-bold mb-2">Levantar el servidor</div>
      <div class="font-mono leading-relaxed">
        <div>pip install fastapi uvicorn</div>
        <div>uvicorn main:app --reload</div>
        <div class="opacity-50 mt-1">→ http://localhost:8000</div>
        <div class="opacity-50">→ http://localhost:8000/docs</div>
      </div>
    </div>
    <div class="p-2 rounded bg-white/5 border border-white/10 text-xs opacity-70">
      <code>/docs</code> genera una interfaz interactiva para probar los endpoints sin Postman.
    </div>
  </div>
  <div class="text-left">

```python
from fastapi import FastAPI

app = FastAPI()
sensores = {}  # diccionario en memoria

@app.get("/sensor/{id}")
def leer(id: int):
    if id not in sensores:
        return {"error": "no encontrado"}
    return sensores[id]

@app.post("/sensor/{id}")
def guardar(id: int, temp: float, hum: float):
    sensores[id] = {"temp": temp, "hum": hum}
    return {"status": "ok", "id": id}
```

  </div>
</div>

<!--
Mostrar en vivo: levantar el servidor, abrir /docs y hacer un POST con id=1, temp=25.3, hum=60. Luego hacer GET /sensor/1 y ver el resultado.
Importante mencionar: el diccionario se borra al reiniciar el servidor — para persistencia real se conecta a PostgreSQL o Supabase.
El ESP32 puede apuntar su HTTPClient a http://<IP-laptop>:8000/sensor/1 y funciona en la misma red local.
-->

---

# SQL y PostgreSQL

<div class="grid grid-cols-2 gap-4 mt-3">
  <div class="flex flex-col gap-2 text-xs">
    <div class="p-3 rounded-lg border border-blue-400/40 bg-blue-500/10">
      <div class="font-bold mb-1">¿Qué es SQL?</div>
      <div class="opacity-80">Lenguaje estándar para crear, consultar y modificar bases de datos relacionales. Los datos se organizan en <strong>tablas</strong> con filas y columnas — como una hoja de cálculo con superpoderes.</div>
    </div>
    <div class="p-3 rounded-lg border border-purple-400/40 bg-purple-500/10">
      <div class="font-bold mb-1">PostgreSQL</div>
      <div class="opacity-80">Motor de base de datos relacional open source, robusto y con soporte para tipos de datos avanzados (JSON, timestamps con zona horaria, arrays). Es el motor que usa Supabase.</div>
    </div>
    <div class="p-2 rounded bg-white/5 border border-white/10">
      <div class="font-bold mb-1 opacity-60">Otros motores SQL</div>
      <div class="grid grid-cols-3 gap-x-2 gap-y-0.5 font-mono">
        <div>SQLite</div><div class="font-sans opacity-70 col-span-2">Archivo local, sin servidor</div>
        <div>MySQL</div><div class="font-sans opacity-70 col-span-2">Muy usado en web (LAMP)</div>
        <div>SQL Server</div><div class="font-sans opacity-70 col-span-2">Microsoft, entornos enterprise</div>
      </div>
    </div>
  </div>
  <div class="text-left">

```sql
CREATE TABLE datos_gateway (
  id           SERIAL PRIMARY KEY,
  timestamp    TIMESTAMPTZ DEFAULT NOW(),
  co2          FLOAT,
  temp_int     FLOAT,
  temp_ext     FLOAT,
  humidity     FLOAT,
  ph           FLOAT
);

-- insertar una lectura
INSERT INTO datos_gateway
  (co2, temp_int, temp_ext, humidity, ph)
VALUES
  (412.5, 23.1, 18.4, 65.2, 7.0);

-- consultar las últimas 10
SELECT * FROM datos_gateway
ORDER BY timestamp DESC
LIMIT 10;
```

  </div>
</div>

<!--
SERIAL = entero autoincremental — PostgreSQL asigna el id automáticamente.
TIMESTAMPTZ = timestamp con zona horaria — importante en IoT para saber exactamente cuándo llegó cada lectura.
DEFAULT NOW() = si no se envía timestamp, PostgreSQL usa la hora actual del servidor.
Supabase crea esta tabla visualmente y genera la API REST automáticamente — mostrar en vivo.
-->

---

# INSERT y SELECT — Agregar filas y buscar en la tabla
```sql
INSERT INTO datos_gateway (timestamp, co2, temp_int, temp_ext, humidity, ph)
VALUES
  ('2025-05-19 08:00:00+00', 410.2, 22.4, 17.1, 63.5, 7.1),
  ('2025-05-19 08:15:00+00', 425.7, 22.9, 17.4, 64.0, 7.0),
  ('2025-05-19 08:30:00+00', 438.1, 23.5, 18.0, 65.8, 6.9),
  ('2025-05-19 08:45:00+00', 401.3, 23.1, 18.3, 66.2, 7.2),
  ('2025-05-19 09:00:00+00', 415.9, 24.0, 19.1, 67.0, 7.0);

-- verificar que se insertaron
SELECT * FROM datos_gateway ORDER BY timestamp;
```

```sql
-- CO2 sobre 420 ppm
SELECT timestamp, co2, temp_int
FROM datos_gateway
WHERE co2 > 420
ORDER BY timestamp;

-- promedio de la última hora
SELECT AVG(co2), AVG(temp_int), AVG(humidity)
FROM datos_gateway
WHERE timestamp >= NOW() - INTERVAL '1 hour';
```

<!--
Notar que el id no se incluye — SERIAL lo asigna PostgreSQL automáticamente (1, 2, 3...).
El timestamp se pasa explícitamente aquí para simular lecturas históricas del ESP32.
En producción el ESP32 enviaría una fila a la vez vía POST a la API, y el servidor haría el INSERT.
DEFAULT NOW() entraría en juego si el ESP32 no manda timestamp — el servidor usa su reloj.
-->

---
layout: center
---

# Actividad

<Image src="/images/actividad_dog.png" class="h-72 mx-auto mt-4 rounded-xl" />

---

# Crear una cuenta en Supabase

<div class="grid grid-cols-2 gap-4 mt-4 text-xs">
  <div class="flex flex-col gap-2">

<v-clicks>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">1</div>
    <div><div class="font-bold mb-1">Ir a supabase.com</div><div class="opacity-70">Hacer clic en <strong>Start your project</strong>. Registrarse con cuenta de GitHub o email.</div></div>
  </div>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">2</div>
    <div><div class="font-bold mb-1">Crear un nuevo proyecto</div><div class="opacity-70">Elegir nombre, contraseña de base de datos y región (<strong>South America</strong> o <strong>US East</strong>). Guardar la contraseña — se necesita después.</div></div>
  </div>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">3</div>
    <div><div class="font-bold mb-1">Abrir el editor SQL</div><div class="opacity-70">En el panel izquierdo: <strong>SQL Editor → New query</strong>. Pegar el <code>CREATE TABLE</code> y ejecutar con <strong>Run</strong>.</div></div>
  </div>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">4</div>
    <div><div class="font-bold mb-1">Obtener las credenciales</div><div class="opacity-70"><strong>Project Settings → API</strong>: copiar la <strong>URL del proyecto</strong> y la <strong>anon key</strong>. Con eso el ESP32 puede hacer POST directo.</div></div>
  </div>

</v-clicks>

  </div>
  <div class="flex flex-col gap-3">
    <div class="p-3 rounded-lg border border-green-400/40 bg-green-500/10 text-xs">
      <div class="font-bold mb-2">Plan gratuito incluye</div>
      <div class="flex flex-col gap-1 opacity-80">
        <div>✓ 500 MB de base de datos PostgreSQL</div>
        <div>✓ API REST generada automáticamente</div>
        <div>✓ 2 GB de transferencia por mes</div>
        <div>✓ Dashboard visual para ver las tablas</div>
        <div>✓ Autenticación de usuarios incluida</div>
      </div>
    </div>
    <div class="p-3 rounded bg-white/5 border border-white/10 text-xs">
      <div class="font-bold mb-2">Una vez creada la tabla, el endpoint queda listo:</div>
      <div class="font-mono leading-relaxed opacity-80">
        <div>POST https://[proyecto].supabase.co</div>
        <div class="pl-4">/rest/v1/datos_gateway</div>
        <div class="mt-1 opacity-50">Authorization: Bearer [anon-key]</div>
      </div>
    </div>
  </div>
</div>

<!--
Recomendar usar GitHub para registrarse — más rápido y no necesita verificar email.
La contraseña de la DB se usa solo para conectarse desde herramientas externas como pgAdmin o Looker Studio — no desde el ESP32.
El proyecto tarda ~2 minutos en aprovisionarse después de crearlo.
Con la anon key el ESP32 puede insertar filas directamente sin backend intermedio.
-->

---

# Instrucciones — Actividad

<div class="flex flex-col gap-2 mt-4 text-xs">

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">1</div>
    <div><span class="font-bold">Crear proyecto gratuito en Supabase</span><span class="opacity-70 ml-2">supabase.com → New project → elegir nombre, contraseña y región. Esperar ~2 min a que quede listo.</span></div>
  </div>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">2</div>
    <div><span class="font-bold">Abrir el SQL Editor</span><span class="opacity-70 ml-2">Panel izquierdo → SQL Editor → New query. Pegar el <code>CREATE TABLE datos_gateway</code> entregado en clase y ejecutar con Run.</span></div>
  </div>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">3</div>
    <div><span class="font-bold">Insertar filas con datos de prueba</span><span class="opacity-70 ml-2">Nueva query → pegar el bloque <code>INSERT INTO datos_gateway</code> con las 5 filas de ejemplo → Run. Verificar en Table Editor que aparecen los registros.</span></div>
  </div>

  <div class="p-3 rounded-lg border border-white/20 bg-white/5 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-green-500/30 border border-green-400/50 flex items-center justify-center font-bold shrink-0">4</div>
    <div><span class="font-bold">Consultar con SELECT</span><span class="opacity-70 ml-2">Ejecutar las queries de ejemplo: <code>SELECT *</code> para ver todo, luego filtrar por <code>co2 &gt; 420</code> y calcular el <code>AVG</code> de la última hora.</span></div>
  </div>

  <div class="p-3 rounded-lg border border-blue-400/30 bg-blue-500/10 flex items-start gap-3">
    <div class="w-6 h-6 rounded-full bg-blue-500/30 border border-blue-400/50 flex items-center justify-center font-bold shrink-0">+</div>
    <div><span class="font-bold">Extra</span><span class="opacity-70 ml-2">Agregar 3 filas propias con valores distintos y escribir una query que filtre por temperatura interior mayor a 23°C ordenada por timestamp.</span></div>
  </div>

</div>

<!--
Cada alumno trabaja en su propio proyecto — el plan free no requiere tarjeta de crédito.
El SQL Editor guarda historial de queries — pueden volver a versiones anteriores si borran algo por error.
-->

---

# Conectar Looker Studio a Supabase

<div class="grid grid-cols-2 gap-4 mt-3 text-xs">
  <div class="flex flex-col gap-2">
    <div class="p-2 rounded-lg border border-orange-400/40 bg-orange-500/10">
      <div class="font-bold mb-1">Looker Studio <span class="opacity-50 font-normal">(antes Google Data Studio)</span></div>
      <div class="opacity-80">Ingresar en <strong>datastudio.google.com</strong> con el correo de la universidad. Crear un informe nuevo con el botón <strong>+</strong>.</div>
    </div>
    <div class="flex flex-col gap-1.5">
      <div class="p-2 rounded border border-white/20 bg-white/5 flex items-start gap-2">
        <div class="w-5 h-5 rounded-full bg-orange-500/30 border border-orange-400/50 flex items-center justify-center font-bold shrink-0 text-xs">1</div>
        <div>En <strong>Añadir datos al informe</strong> buscar y seleccionar <strong>PostgreSQL</strong>.</div>
      </div>
      <div class="p-2 rounded border border-white/20 bg-white/5 flex items-start gap-2">
        <div class="w-5 h-5 rounded-full bg-orange-500/30 border border-orange-400/50 flex items-center justify-center font-bold shrink-0 text-xs">2</div>
        <div>En Supabase: botón <strong>Connect</strong> (arriba a la derecha) → pestaña <strong>Direct</strong> → sección <strong>Connection string</strong>.</div>
      </div>
      <div class="p-2 rounded border border-white/20 bg-white/5 flex items-start gap-2">
        <div class="w-5 h-5 rounded-full bg-orange-500/30 border border-orange-400/50 flex items-center justify-center font-bold shrink-0 text-xs">3</div>
        <div>Copiar los campos <strong>host</strong>, <strong>port</strong>, <strong>database</strong>, <strong>user</strong> y la <strong>contraseña</strong> del proyecto en el formulario de Looker Studio.</div>
      </div>
      <div class="p-2 rounded border border-white/20 bg-white/5 flex items-start gap-2">
        <div class="w-5 h-5 rounded-full bg-orange-500/30 border border-orange-400/50 flex items-center justify-center font-bold shrink-0 text-xs">4</div>
        <div>Seleccionar la tabla <strong>datos_gateway</strong> y hacer clic en <strong>Añadir</strong>.</div>
      </div>
    </div>
  </div>
  <div>
    <Image src="/images/supabase_connect.png" class="rounded-xl border border-white/20 object-contain w-full" />
    <div class="mt-2 p-2 rounded bg-white/5 border border-white/10 text-xs opacity-70 text-center">
      Los campos host, port, database y user se encuentran en esta pantalla
    </div>
  </div>
</div>

<!--
Looker Studio puede tardar unos segundos en verificar la conexión — es normal.
Si aparece error de IPv4: usar Session Pooler en vez de Direct — cambiar el puerto a 6543 y el host al de Session Pooler.
Una vez conectado, arrastrar campos como temp_int y timestamp para crear un gráfico de línea en tiempo real.
-->

---

# Looker Studio — Visualizar los datos

<div class="grid grid-cols-2 gap-4 mt-4 text-xs">
  <div class="flex flex-col gap-2">
    <div class="p-3 rounded-lg border border-orange-400/40 bg-orange-500/10">
      <div class="font-bold mb-2">Agregar una tabla</div>
      <div class="opacity-80 flex flex-col gap-1">
        <div>1. En la barra superior: <strong>Insertar → Tabla</strong></div>
        <div>2. Dibujar el área en el lienzo</div>
        <div>3. En el panel derecho elegir las dimensiones (<strong>timestamp</strong>) y métricas (<strong>co2, temp_int, temp_ext, humidity, ph</strong>)</div>
        <div>4. Ordenar por <strong>timestamp descendente</strong> para ver las lecturas más recientes primero</div>
      </div>
    </div>
    <div class="p-3 rounded-lg border border-blue-400/40 bg-blue-500/10">
      <div class="font-bold mb-2">Agregar un gráfico</div>
      <div class="opacity-80 flex flex-col gap-1">
        <div>1. <strong>Insertar → Gráfico de líneas</strong> (o el de su elección)</div>
        <div>2. Dimensión: <strong>timestamp</strong></div>
        <div>3. Métrica: la variable que quieran visualizar (<strong>co2</strong>, <strong>temp_int</strong>, etc.)</div>
        <div>4. Pueden agregar múltiples métricas en el mismo gráfico para comparar</div>
      </div>
    </div>
  </div>
  <div class="flex flex-col gap-2">
    <div class="p-3 rounded bg-white/5 border border-white/10">
      <div class="font-bold mb-2">Tipos de gráfico recomendados para IoT</div>
      <div class="flex flex-col gap-1 opacity-80">
        <div><strong>Líneas</strong> — evolución de temperatura o CO2 en el tiempo</div>
        <div><strong>Indicador</strong> — mostrar el último valor registrado</div>
        <div><strong>Tabla</strong> — ver todas las lecturas con filtros</div>
        <div><strong>Barras</strong> — comparar promedios por hora o día</div>
      </div>
    </div>
    <div class="p-2 rounded bg-white/5 border border-white/10 text-xs opacity-70">
      El informe se actualiza automáticamente cada vez que llegan nuevos datos a la tabla de Supabase.
    </div>
  </div>
</div>

<!--
Mostrar en vivo: agregar un gráfico de líneas con timestamp en X y temp_int en Y. Aparecen los 5 puntos de los datos insertados.
Indicador: arrastrar co2 como métrica y configurar rango de color (verde < 400, amarillo 400-600, rojo > 600).
El dashboard se puede compartir con un link — ideal para que el equipo vea los datos del ESP32 en tiempo real.
-->
