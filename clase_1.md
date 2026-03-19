---
#theme: seriph
background: https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEhu4MVA6NXFxJjPPfaVckUv1Qo12mk7f0oS6mPIa_pwvO2bZSplXWIHvbdyZWEsGdYQTAAKZ_5-BkzJEaQ9poIXn8jPcxBiPRVEYbvjEYlElkvEoM0GuUVQOVCCuE7LjfZ5W0tGvFqDjoGw/s0/3770921.jpg

class: 'text-center'
info: |
  ## Sistemas Embebidos & SBC
  Introducción a microcontroladores, Single Board Computers y el ecosistema IoT.

  Del microcontrolador al Linux embebido.
transition: slide-left
title: Sistemas Embebidos & SBC
mdc: true

fonts:
  sans: Roboto
  serif: Roboto Slab
  mono: Fira Code
---

# Sistemas Embebidos - SBC - IoT

Introducción microcontroladores, Linux embebido y sistemas IoT

<div class="pt-12">
  <span @click="$slidev.nav.next" class="px-2 py-1 rounded cursor-pointer" flex="~ justify-center items-center gap-2" hover="bg-white bg-opacity-10">
    Presiona espacio para continuar <div class="i-carbon:arrow-right inline-block"/>
  </span>
</div>

<div class="abs-br m-6 flex gap-2">
  <button @click="$slidev.nav.openInEditor()" title="Open in Editor" class="text-xl slidev-icon-btn opacity-50 !border-none !hover:text-white">
    <div class="i-carbon:edit" />
  </button>
</div>

<!--
Bienvenida al módulo de Sistemas Embebidos. Presentarte brevemente y mencionar qué van a ver hoy: desde qué es un microcontrolador hasta el ecosistema IoT con ESP32. Preguntar a mano alzada quién ya programó alguna vez un Arduino o Raspberry Pi.
-->

---
layout: default
transition: fade-out
---

# Contenido

<Toc maxDepth="1" columns="2" class="text-sm"></Toc>

<!--
Recorrer brevemente el índice para que los estudiantes sepan hacia dónde vamos. Mencionar que hay anécdotas históricas, comparaciones prácticas y que al final van a entender por qué el ESP32 es tan popular en IoT.
-->

---
transition: slide-up
---

# ¿Qué es un sistema embebido?

<div class="grid grid-cols-4 gap-4 mt-4">

  <div class="p-4 col-span-3 rounded border border-white/20 bg-white/5">

  **Situación:** Tengo una estufa y me gustaría que se prenda y apague sola.

  - El Mecánico: Le ponemos un reloj para que la apague
  - El Eléctrico: Diseño un circuito, que la apague
  - El Programador... <v-click> **¿Y si le ponemos un computador?** </v-click>

  </div>

  <div class="p-4 rounded border border-white/20 bg-white/5 flex items-center justify-center">
    <div class="text-7xl">👩‍🔧</div>
  </div>

  <div class="p-4 rounded border border-white/20 bg-white/5">
    <Image src="/images/Pie-de-metro-digital.png" class="h-25 mx-auto mt-1" />
  </div>
  <div class="p-4 rounded border border-white/20 bg-white/5">
    <Image src="/images/Unidad de control de motor.jpg" class="h-25 mx-auto mt-1" />
  </div>
  <div class="p-4 rounded border border-white/20 bg-white/5">
    <Image src="/images/horno_digital.png" class="h-25 mx-auto mt-1" />
  </div>
  <div class="p-4 rounded border border-white/20 bg-white/5">
    <Image src="/images/termometrodigital.jpg" class="h-25 mx-auto mt-1" />
  </div>

  <div class="p-4 col-span-4">
    <v-click> <strong>"Es un computador pequeño que va integrado para controlar cualquier producto"</strong> </v-click>
  </div>


</div>

---
transition: slide-down
---

# Línea de tiempo de los sistemas embebidos

<div class="grid grid-cols-3 mt-4">


<div class="p2">
<Image src="/images/Apolo_Guidance_computer.png" class="h-40 mx-auto mt-1" />
</div>

<div class="p2">
<Image src="/images/Intel_C4004.jpg" class="h-40 mx-auto mt-1" />
</div>

<div class="p2">
<Image src="/images/Sintonizador de radio aereo.jpg" class="h-40 mx-auto mt-1" />
</div>

<div class="p2 col-span-3">
```mermaid {scale: 0.5}
timeline
    title Historia de los sistemas embebidos
    1969 : Apollo Guidance Computer
         : Primer sistema embebido crítico
    1971 : Intel 4004
         : Primer microprocesador comercial
    1992 : Parallax BASIC Stamp
         : Microcontrolador educativo popular
    2005 : Arduino Uno
         : Open-source para todos
    2012 : Raspberry Pi Model B
         : Linux en una sola placa
    2016 : ESP32
         : WiFi + BT + dual-core a $5
    2026 : Hoy
         : SBCs más potentes que PCs de los 2000s
```
</div>

</div>
<!-- IMAGE SUGGESTION: Colocar ./images/Apolo_Guidance_computer.png junto al timeline, referencia visual al primer sistema embebido. Ver también: https://hackaday.com/2018/11/12/an-apollo-guidance-computer-laid-bare/ -->

<!--
Contextualizar: llevamos más de 50 años haciendo sistemas embebidos. El Apollo Guidance Computer navegó a la Luna con menos poder de cómputo que una calculadora moderna. Preguntar: ¿cuántos sistemas embebidos creen que tienen en su casa?
-->

<style>
h1 {
  background-color: #2B90B6;
  background-image: linear-gradient(45deg, #4EC5D4 10%, #146b8c 20%);
  background-size: 100%;
  -webkit-background-clip: text;
  -moz-background-clip: text;
  -webkit-text-fill-color: transparent;
  -moz-text-fill-color: transparent;
}
</style>

---
transition: fade-out
---

# Propósitos: ¿para qué sirven?

<div grid="~ cols-2 gap-4" class="mt-2">

<div v-click class="p-3 rounded-lg border border-white/20 bg-white/5">
<div class="font-bold text-sm mb-1">🤖 Hobby</div>
<Image src="/images/Robot Hobby talleres Microcontrolador 1_.png" class="h-30 mx-auto mt-1" />
<div class="text-sm mt-1">Robots, juegos, proyectos creativos de taller</div>
</div>

<div v-click class="p-3 rounded-lg border border-white/20 bg-white/5">
<div class="font-bold text-sm mb-1">🎓 Educación</div>
<Image src="/images/Microbit education microcontroller.png" class="h-30 mx-auto mt-1" />
<div class="text-sm mt-1">Micro:bit, kits escolares, aprendizaje visual</div>
</div>

<div v-click class="p-3 rounded-lg border border-white/20 bg-white/5">
<div class="font-bold text-sm mb-1">🌡️ Control</div>
<Image src="/images/Generadores helocos ejemplo control.png" class="h-30 mx-auto mt-1" />
<div class="text-sm mt-1">Estaciones meteorológicas, automatización industrial</div>
</div>

<div v-click class="p-3 rounded-lg border border-white/20 bg-white/5">
<div class="font-bold text-sm mb-1">🛒 Productos comerciales</div>
<Image src="/images/Mechanical Keyboard Example Product.jpg" class="h-30 mx-auto mt-1" />
<div class="text-sm mt-1">Teclados mecánicos, controles de videojuegos, electrodomésticos</div>
<!-- IMAGE SUGGESTION: Agregar también ./images/mechaniocal keyboard example 1 product.png -->
<!-- REFERENCIA: https://hackaday.com/2017/11/10/an-awesome-open-mechanical-keyboard/ -->
</div>

</div>

<style>
.slidev-page,
.slidev-layout,
.slidev-layout * {
  user-select: text !important;
  -webkit-user-select: text !important;
}
</style>

<!--
Mostrar cada caso con v-click progresivo. En "Hobby" mencionar los robots que hicieron en los talleres (hay fotos de eso). En "Productos comerciales" preguntar: ¿cuántos usan un teclado mecánico? Adivinen qué microcontrolador tiene adentro.
-->

---
layout: image-right
image: ./images/arduino uno r3.png
transition: slide-left
---

# Microcontroladores

- ⚡ <b>Bajo consumo</b>: vive en baterías o sensores remotos y despierta solo cuando lo necesitas.
- 🧠 <b>Procesador completo</b>: tiene CPU, memoria y periféricos integrados en un chip del tamaño de una uña.
- 🔌 <b>Multiples interfaces</b>: UART, SPI, I²C, ADC, PWM, USB, WiFi/BT, radiofrecuencias, GPS, etc., para hablar con sensores, memorias y redes.
- 🛠️ <b>Diseñado para una tarea</b>: controla motores, luces, sensores o protocolos de radio sin tener que cargar un sistema operativo completo.

<!--
-->

---
layout: image-right
image: ./images/Arduino team history.jpg
transition: slide-up
---

# Arduino

**Ivrea, Italia — 2005**

El proyecto nació en el **Interaction Design Institute Ivrea (IDII)** con una motivación muy práctica:

- Los estudiantes trabajaban con **BASIC Stamp** (~$50 USD)
- Demasiado caro para un contexto educativo
- La idea: *hagamos algo más barato y fácil para diseñadores, no solo ingenieros*
- Massimo Banzi lidera el proyecto junto a David Cuartielles, Tom Igoe, Gianluca Martino y David Mellis



<!-- IMAGE SUGGESTION: Agregar ./images/basic stamp board parallax.jpg como imagen secundaria o en comentario visual para el BASIC Stamp -->

<!--
Hacer pausa dramática en "el nombre no viene de un lab...". Dejar que la audiencia especule. Luego pasar a la siguiente diapositiva para el reveal. Esta es la slide de setup de la anécdota.
-->

---
layout: image-right
image: ./images/Bar di re arduino.png
transition: fade-out
---

# Bautizado en un bar 🍺

El **Bar di Re Arduino** era el café donde se juntaba el equipo en Ivrea.

<v-clicks>

- El bar lleva el nombre del **Rey Arduin de Ivrea** (rey de Italia 1002–1014)
- Banzi le puso "Arduino" al proyecto en honor al bar
- *Un proyecto que cambió el mundo maker... bautizado por el bar de la esquina*

</v-clicks>

<br>

<div v-click class="p-3 rounded bg-blue-500/20 border border-blue-400/40">

🔀 Arduino técnicamente fue un **fork** del proyecto **Wiring** (también desarrollado en el IDII).

</div>

<!-- IMAGE SUGGESTION: Agregar ./images/Arduino team history.jpg en una segunda columna o debajo para mostrar al equipo fundador -->

<!--
El "giro de taller" es para generar debate: ¿es Arduino realmente original? La respuesta es sí, porque lo que hicieron fue mucho más que copiar — mejoraron el hardware, la IDE, la comunidad y la documentación. Wiring existe aún hoy pero Arduino ganó por comunidad y ecosistema.
-->

---
layout: image-right
image: ./images/Raspberry Pi Model B 2012.png
transition: slide-left
---

# Single Board Computers (SBC)

**Una computadora completa en una sola placa**

<v-clicks>

- 2012: Raspberry Pi Foundation lanza el **Model B** con 256MB de RAM
- Objetivo original: enseñar programación a niños en el Reino Unido
- Precio: **$35 USD** — Linux completo en formato de tarjeta de crédito
- La comunidad explotó: servidores, media centers, robots, IoT...

</v-clicks>

<br>

<!--
Preguntar: ¿quién tiene una Raspberry Pi en casa? ¿para qué la usan? Mencionar que la RPi cambió la idea de low-cost computing — no solo para niños, sino para makers, industria y educación. Destacar el rol de la Foundation sin fines de lucro.
-->

---
layout: image-right
image: ./images/Raspberry pi zero on a magazine.jpg
transition: fade-out
---

# El boom y la crisis de chips

**2015:** Raspberry Pi Zero — **$5 USD**, el SBC más barato de la historia

<v-clicks>

- Se publicó en la revista MagPi y venía **incluida en la tapa**
- La comunidad de SBCs creció exponencialmente
- **2020–2022:** Pandemia + escasez global de semiconductores

</v-clicks>

<div v-click class="p-3 rounded bg-red-500/20 border border-red-400/40 mt-3">

⚠️ Una Raspberry Pi que costaba $35 llegó a venderse por **$100–$150** en el mercado secundario

</div>

<!-- IMAGE SUGGESTION: ./images/chip shortage ilustration with cats.png como slide adicional o imagen decorativa -->

<!--
La imagen de la revista MagPi con la RPi Zero pegada en la tapa es icónica. Mostrarla. La crisis de chips fue real: se paralizaron fábricas de autos, consolas y electrónica en general. Esto creó una oportunidad de mercado que aprovecharon fabricantes chinos, lo que democratizó aún más el acceso.
-->

---
transition: slide-up
---

# El ecosistema SBC hoy

<div grid="~ cols-4 gap-3" class="mt-2">

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<Image src="/images/Raspberry Pi Model B 2012.png" class="h-20 mx-auto mb-2" />
<strong>Raspberry Pi</strong>
<div class="text-xs opacity-60">La original. Mayor comunidad.</div>
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<Image src="/images/Banana Pi.png" class="h-20 mx-auto mb-2" />
<strong>Banana Pi</strong>
<div class="text-xs opacity-60">Compatible con ecosistema RPi</div>
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<Image src="/images/orange-pi-cm5.jpg" class="h-20 mx-auto mb-2" />
<strong>Orange Pi</strong>
<div class="text-xs opacity-60">Rockchip, muy costo-eficiente</div>
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<Image src="/images/raxda board.png" class="h-20 mx-auto mb-2" />
<strong>Radxa / Rock Pi</strong>
<div class="text-xs opacity-60">Rockchip, NVMe, M.2</div>
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<Image src="/images/jetson-nano-board.jpg" class="h-20 mx-auto mb-2" />
<strong>NVIDIA Jetson</strong>
<div class="text-xs opacity-60">GPU integrada para ML/IA</div>
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<Image src="/images/Arduino uno Q SBC.png" class="h-20 mx-auto mb-2" />
<strong>Arduino (Qualcomm)</strong>
<div class="text-xs opacity-60">Linux en Arduino — nueva era</div>
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<div class="h-20 flex items-center justify-center text-3xl">🍎</div>
<strong>Apple Silicon</strong>
<div class="text-xs opacity-60">M1/M2/M3 — ARM en desktop</div>
<!-- IMAGE SUGGESTION: Agregar imagen de Apple M1/M2 chip die o MacBook -->
</div>

<div v-click class="text-center p-3 rounded border border-white/20 bg-white/5">
<div class="h-20 flex items-center justify-center text-2xl opacity-50">+ más</div>
<strong>Los demás...</strong>
<div class="text-xs opacity-60">Rock Pi, Khadas, BeagleBone...</div>
</div>

</div>

<!--
La competencia es buena para el precio y la innovación. Mencionar que Qualcomm compró Arduino y lanzó el Arduino Portenta X8 con Linux. Apple es el ejemplo más mainstream de ARM llegando al desktop/laptop — el M1 fue un punto de inflexión.
-->

---
layout: image-right
image: ./images/arm cortex processor diagram.jpg
transition: slide-left
---

# ARM vs x86

<div class="mt-2 text-sm">

| | **ARM** | **x86** |
|---|---|---|
| Diseño | RISC | CISC |
| Instrucciones | Simples y fijas | Complejas y variables |
| Consumo | Bajo (mW–W) | Alto (W–TDP) |
| Licenciamiento | Arm Holdings (royalties) | Intel / AMD (fabricantes) |
| Ejemplos | Cortex-M, Apple M2, Snapdragon | Intel Core, AMD Ryzen |

</div>

<div v-click class="mt-2 p-2 text-sm rounded bg-purple-500/20 border border-purple-400/40">

🤔 Tanto microcontroladores como SBCs usan mayoritariamente **ARM**... pero no todos.
ESP32-C3/C6 también usan **RISC-V**, y algunas placas usan **MIPS** o **x86** (Intel NUC).

</div>

<!-- IMAGE SUGGESTION: ./images/arm cortex m0 block diagram processor.png para una vista más detallada del núcleo Cortex-M0 -->
<!-- IMAGE SUGGESTION: ./images/arm cortex m0 xr die.jpg para mostrar el die real del chip -->

<!--
No profundizar demasiado en arquitecturas — el objetivo es que entiendan que no todo corre en la misma arquitectura y que compilar para ARM no es lo mismo que compilar para x86. Esto es especialmente relevante cuando quieran correr Docker o binarios en una RPi. El ejemplo de Apple M1 es útil: incluso macOS migró a ARM en 2020.
-->

---
transition: slide-up
---

# ¿Cuándo conviene uno u otro?

### Microcontrolador (bare-metal) vs SBC (Linux)

<div class="mt-3 space-y-2">

<div class="flex items-center gap-4 p-3 rounded border border-white/10 bg-white/5">
  <div class="w-28 text-sm font-bold">💰 Costo</div>
  <div class="flex-1">
    <div class="text-xs opacity-60 mb-1">Microcontrolador</div>
    <div class="text-green-400">●●●●● ~$1–15 USD</div>
  </div>
  <div class="flex-1">
    <div class="text-xs opacity-60 mb-1">SBC</div>
    <div class="text-yellow-400">●●●○○ ~$15–80 USD</div>
  </div>
</div>

<div class="flex items-center gap-4 p-3 rounded border border-white/10 bg-white/5">
  <div class="w-28 text-sm font-bold">⚡ Consumo</div>
  <div class="flex-1">
    <div class="text-green-400">●●●●● μW – mW (deep sleep)</div>
  </div>
  <div class="flex-1">
    <div class="text-red-400">●●○○○ 2–10 W constantes</div>
  </div>
</div>

<div class="flex items-center gap-4 p-3 rounded border border-white/10 bg-white/5">
  <div class="w-28 text-sm font-bold">⏱️ Arranque</div>
  <div class="flex-1">
    <div class="text-green-400">●●●●● Milisegundos</div>
  </div>
  <div class="flex-1">
    <div class="text-yellow-400">●●○○○ 10–60 segundos (Linux)</div>
  </div>
</div>

<div class="flex items-center gap-4 p-3 rounded border border-white/10 bg-white/5">
  <div class="w-28 text-sm font-bold">🌐 Conectividad</div>
  <div class="flex-1">
    <div class="text-yellow-400">●●●○○ WiFi/BT básico (ESP32)</div>
  </div>
  <div class="flex-1">
    <div class="text-green-400">●●●●● Ethernet, WiFi, USB, etc.</div>
  </div>
</div>

<div class="flex items-center gap-4 p-3 rounded border border-white/10 bg-white/5">
  <div class="w-28 text-sm font-bold">💪 Potencia </div>
  <div class="flex-1">
    <div class="text-yellow-400">●●●○○ Baja frecuencia y ➖ memoria</div>
  </div>
  <div class="flex-1">
    <div class="text-green-400">●●●●● Alta frecuencia y ➕ memoria</div>
  </div>
</div>

</div>

<!--
Hacer analogía con videojuego: cada plataforma tiene sus stats. Un microcontrolador es como un guerrero especializado — rápido, eficiente, pero limitado en habilidades. Un SBC es el mago con todo el arsenal pero necesita tiempo para prepararse. Casos reales: termostato industrial → micro; servidor domótico → SBC.
-->

---
layout: image-right
image: ./images/arduino ide.png
transition: fade-out
---

# Arduino: filosofía y comunidad

- **Open-source hardware y software** desde el primer día
- IDE simplificada: `setup()` + `loop()` — sin conocer sistemas operativos
- **Shields**: módulos apilables para agregar funciones sin soldar
- Comunidad masiva: foros, tutoriales, librerías para todo
- Más de **10 millones** de placas vendidas al 2015

<!-- IMAGE SUGGESTION: ./images/Arduino community magazine.png para mostrar la revista -->
<!-- IMAGE SUGGESTION: ./images/arduino older boards.jpg para mostrar la evolución de placas -->

<!--
Destacar que la filosofía "no solo para ingenieros" fue lo que lo diferenció. Un diseñador gráfico podía hacer un prototipo interactivo sin saber C++ profundo. Esto democratizó la electrónica. Mencionar que Arduino tiene IDEs, librerías y ejemplos incluidos — la curva de aprendizaje es mucho más suave que STM32 o ESP-IDF.
-->

---
layout: center
transition: slide-left
---

# Espressif: la alternativa

<div class="text-center mb-4">
  <div class="text-4xl mb-2">🌍</div>
  <div class="text-2xl font-bold">Democratizar el acceso a la tecnología</div>
  <div class="text-base opacity-70 mt-1">Shanghai, China — fundada en 2008</div>
</div>

<div grid="~ cols-3 gap-4" class="mt-3">

<div v-click class="text-center p-4 rounded-lg border border-green-400/40 bg-green-500/10">
  <div class="text-3xl mb-2">🔓</div>
  <div class="font-bold">Open Source</div>
  <div class="text-sm opacity-70">Todo el SDK (ESP-IDF) es open-source en GitHub</div>
</div>

<div v-click class="text-center p-4 rounded-lg border border-blue-400/40 bg-blue-500/10">
  <div class="text-3xl mb-2">📐</div>
  <div class="font-bold">Open Hardware</div>
  <div class="text-sm opacity-70">Diseños de referencia públicos para fabricantes</div>
</div>

<div v-click class="text-center p-4 rounded-lg border border-purple-400/40 bg-purple-500/10">
  <div class="text-3xl mb-2">💸</div>
  <div class="font-bold">Accesibilidad</div>
  <div class="text-sm opacity-70">WiFi + BT a $2–5 USD — antes era impensable</div>
</div>

</div>

<!--
Contrastar con STM (corporación francesa-italiana), Qualcomm (empresa estadounidense que compró ARM Cortex ecosystem) y otros. Espressif es inusual: una empresa china que adoptó open-source y open-hardware como filosofía central, no como estrategia de marketing. Esto les ganó la confianza de la comunidad maker global.
-->

---
layout: image-right
image: ./images/esp8266 board.jpg
transition: fade-out
---

# ESP8266: el origen de todo

**2014: WiFi por menos de $1 USD**

<v-clicks>

- Espressif lanza el **ESP8266** 
- Llegó sin documentación en inglés
- La comunidad lo descifró — reverse engineering masivo
- Primero se usaba como módulo AT-command desde Arduino (era más fácil)
- Luego se destapó que **el ESP8266 es en sí mismo es un microcontrolador**

</v-clicks>

<div v-click class="mt-4 p-3 rounded bg-yellow-500/20 border border-yellow-400/40">

🔥 En 2014 WiFi para makers costaba $30+ USD con shields. El ESP8266 lo llevó a **$1**. Fue una revolución.

</div>

<!--
La historia del ESP8266 es un clásico de cultura hacker: nadie esperaba que eso pasara. La comunidad de Hackaday lo documentó, le hizo ingeniería inversa y encontró cómo programarlo directamente. Esto obligó a Espressif a publicar documentación en inglés y abrazar a la comunidad maker. El ESP32 fue la respuesta "oficial" a ese amor de la comunidad.
-->

---
layout: image-right
image: ./images/esp32 s3.jpg
backgroundSize: contain
transition: slide-up
---

# Línea de tiempo del ESP32

<div class="mt-2 space-y-2 text-sm">

<div class="flex gap-3 p-2 rounded border border-white/10 bg-white/5">
  <div class="font-mono text-blue-400 w-16">2016</div>
  <div><b>ESP32</b> — Dual-core Xtensa LX6, WiFi + BT 4.2, 520KB SRAM</div>
</div>

<div class="flex gap-3 p-2 rounded border border-white/10 bg-white/5">
  <div class="font-mono text-blue-400 w-16">2019</div>
  <div><b>ESP32-S2</b> — Single-core, USB nativo, mayor seguridad</div>
</div>

<div class="flex gap-3 p-2 rounded border border-white/10 bg-white/5">
  <div class="font-mono text-blue-400 w-16">2020</div>
  <div><b>ESP32-C3</b> — RISC-V, ultra low-cost, WiFi 4 + BLE 5</div>
</div>

<div class="flex gap-3 p-2 rounded border border-white/10 bg-white/5">
  <div class="font-mono text-blue-400 w-16">2021</div>
  <div><b>ESP32-S3</b> — Dual-core, acelerador ML/AI, USB OTG</div>
</div>

<div class="flex gap-3 p-2 rounded border border-white/10 bg-white/5">
  <div class="font-mono text-blue-400 w-16">2022</div>
  <div><b>ESP32-C6</b> — WiFi 6 (802.11ax), Thread, Zigbee, RISC-V</div>
</div>

<div class="flex gap-3 p-2 rounded border border-white/10 bg-white/5">
  <div class="font-mono text-green-400 w-16">2023+</div>
  <div><b>ESP32-P4</b> — Dual-core 400MHz, sin radio, procesamiento intensivo</div>
</div>

</div>

<!--
Notar la tendencia: cada generación agrega capacidad de procesamiento, más protocolos de conectividad y mejora la eficiencia energética. El ESP32-C3 fue especialmente importante porque usó RISC-V — Espressif apostando por una arquitectura open-source para no pagar royalties a ARM.
-->

---
transition: fade-out
---

# ESP32: ecosistema de herramientas

<div grid="~ cols-3 gap-4" class="mt-4">

<div class="p-3 rounded-lg border border-white/20 bg-white/5 text-center">
  <Image src="/images/arduino ide logo.png" class="h-14 mx-auto mb-2" />
  <div class="font-bold">Arduino IDE</div>
  <div class="text-sm opacity-70 mt-1">
    El más accesible. Soporte oficial de Espressif. Ideal para principiantes.
  </div>
  <div class="mt-2 text-xs p-1 rounded bg-green-500/20">
    ✅ Para empezar rápido
  </div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5 text-center">
  <Image src="/images/micropython logo.png" class="h-14 mx-auto mb-2" />
  <div class="font-bold">MicroPython</div>
  <div class="text-sm opacity-70 mt-1">
    Python en el microcontrolador. REPL interactivo. Excelente para prototipar.
  </div>
  <div class="mt-2 text-xs p-1 rounded bg-blue-500/20">
    ✅ Para prototipado rápido
  </div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5 text-center">
  <Image src="/images/esp-idf logo.png" class="h-14 mx-auto mb-2" />
  <div class="font-bold">ESP-IDF</div>
  <div class="text-sm opacity-70 mt-1">
    Framework oficial de Espressif. C/C++. Control total. Usado en producción.
  </div>
  <div class="mt-2 text-xs p-1 rounded bg-orange-500/20">
    ✅ Para proyectos serios
  </div>
</div>

</div>

<div v-click class="mt-6 text-center text-sm opacity-70">

También existe **PlatformIO** (IDE unificado), **CircuitPython** (Adafruit), y **Rust** embebido 🦀

</div>

<!--
De menor a mayor complejidad: Arduino IDE → MicroPython → ESP-IDF. Para el taller usaremos principalmente Arduino IDE o MicroPython por accesibilidad. ESP-IDF es lo que corren los productos comerciales — es el framework que usa el firmware del ESP32 en millones de dispositivos IoT reales.
-->

---
layout: image-right
image: ./images/esp32 processor block diagram.jpg
backgroundSize: contain
transition: slide-left
---

# Arquitectura del ESP32

**Visión general del hardware*
- **CPU**: Dual-core Xtensa LX6 @ 240 MHz (o RISC-V en variantes C/H)
- **Memoria**: 520 KB SRAM interna + Flash externa (tipicamente 4MB)
- **GPIO**: 34 pines configurables (entrada/salida digital, ADC, PWM, touch)
- **ADC**: 12-bit, hasta 18 canales
- **Comunicación**: I2C, SPI, UART, I2S, CAN, Ethernet MAC
- **PWM**: LEDC (16 canales) + MCPWM para motores

<!-- IMAGE SUGGESTION: ./images/IOT esp32 architecture diagram.png como referencia adicional de arquitectura completa -->

<!--
Comparar con Arduino Uno: ATmega328 es 8-bit, 16MHz, 2KB RAM. El ESP32 es 32-bit, 240MHz, 520KB RAM, con WiFi y BT incluidos. No es competencia — es otra liga. Hacer el ejercicio mental: ¿cuántos Arduino Uno necesitarías para igualar un ESP32?
-->

---
transition: fade-out
---

# ¿Cómo se ejecuta un programa en el ESP32?

<div class="p-4 text-center">

```mermaid {scale: 0.65}
block-beta
  columns 5
  block:bootstrap["🔧 BOOTSTRAP"]:5
    columns 5
    space:5
    space:5
    A["🔌 Power ON"] space B["ROM Bootloader\n(en chip, inmutable)"] space C["2nd Stage Bootloader\n(en Flash, actualizable)"]
  end
  block:exec["▶️ EJECUCIÓN"]:5
    columns 5
    space:5
    space:5
    F["▶️ setup()\nloop()"] space E["Copia a SRAM\n(ejecución)"] space
    D["Partición de App\n(tu firmware en Flash)"]
  end

  A --> B
  B --> C
  C --> D
  D --> E
  E --> F

  style A fill:#2B90B6,stroke:#4EC5D4,color:#fff
  style F fill:#2d6b2d,stroke:#4EC5D4,color:#fff
  style bootstrap display:block,text-align:top;
```
</div>

<div grid="~ cols-4 gap-4" class="mt-3">

<div class="p-3 rounded border border-white/20 bg-white/5 text-center">
  <div class="text-2xl mb-1">💾</div>
  <div class="font-bold text-sm">Flash</div>
  <div class="text-xs opacity-60">Almacenamiento no volátil. Persiste sin energía. Aquí vive tu código.</div>
</div>

<div class="p-3 rounded border border-white/20 bg-white/5 text-center">
  <div class="text-2xl mb-1">🧠</div>
  <div class="font-bold text-sm">SRAM</div>
  <div class="text-xs opacity-60">Memoria rápida volátil. Aquí se ejecuta el código. Se borra al apagar.</div>
</div>

<div class="p-3 rounded border border-white/20 bg-white/5 text-center">
  <div class="text-2xl mb-1">🔧</div>
  <div class="font-bold text-sm">Bootloader</div>
  <div class="text-xs opacity-60">Primer código que corre. Inicializa hardware y carga tu firmware.</div>
</div>

<div class="p-3 rounded border border-white/20 bg-white/5 text-center">
  <div class="text-2xl mb-1">📦</div>
  <div class="font-bold text-sm">Firmware</div>
  <div class="text-xs opacity-60">Tu programa compilado. El "sistema operativo" del dispositivo.</div>
</div>

</div>

<!--
Analogía con PC: ROM Bootloader = BIOS/UEFI (inmutable). 2nd Stage Bootloader = GRUB o Windows Boot Manager. Flash = disco duro (SSD). SRAM = RAM. El concepto de "flashear" un dispositivo viene exactamente de esto: grabar el firmware en la memoria Flash. Cuando hacen "upload" desde Arduino IDE, están flasheando.
-->

---
layout: image-right
image: ./images/ESP32 Dev Kit.png
transition: slide-up
---

# Radio 2.4 GHz y energía

**WiFi + Bluetooth en el mismo chip**

<div v-click class="mt-2 p-2 rounded text-sm">

**Casos de uso por conectividad:**
- **WiFi 802.11** b/g/n (2.4 GHz): hogar inteligente, datos en tiempo real
- **BLE 4.2/5.0**: wearables, proximidad, bajo consumo
- **ZigBee/Thread**: redes malladas, IoT industrial
- Otros: LoRa, NB-IoT/GSM (celular), Ethernet, GPS...

</div>

<div v-click class="text-sm opacity-70 mt-3">

🔋 En **Deep Sleep** (~10 μA) una batería de 1000 mAh puede durar **más de 1 año** con lecturas periódicas. **Activo** (~240 mA) podría llegar a durar unas **~4 horas**.

</div>

<!--
El Deep Sleep es revolucionario para sensores IoT con batería. Ejemplo real: sensor de temperatura que despierta cada 10 minutos, lee temperatura, transmite por WiFi y vuelve a dormir. El tiempo activo (<1 segundo) vs dormido (9 minutos 59 segundos) hace que la batería dure meses. Mencionar consideraciones de antena: la radio puede interferir con el ADC en algunos pins.
-->

---
layout: image-right
image: ./images/IoT devices on the streets.jpg
transition: slide-left
---

# ¿Qué es IoT?

**Internet of Things — Internet de las Cosas**

<v-clicks>

- **Dispositivos** físicos con capacidad de sensar y actuar
- **Conectividad** para transmitir datos (WiFi, BLE, LoRa, 4G)
- **Datos** procesados localmente o en la nube
- **Acción** automatizada basada en la información

</v-clicks>

<div v-click class="mt-4 p-3 rounded bg-blue-500/20 border border-blue-400/40">

🌐 Hoy hay más de **15 mil millones** de dispositivos IoT conectados globalmente.
Para 2030 se proyectan más de **29 mil millones**.

</div>

<!-- IMAGE SUGGESTION: ./images/Smart home iot devices.png como slide complementaria o imagen adicional -->

<!--
Preguntar: ¿cuántos dispositivos IoT tienen en su casa ahora mismo? (TV smart, celular, router, cámara de seguridad, asistente de voz, etc.) La respuesta suele sorprender. IoT no es ciencia ficción — ya está en todas partes, la mayoría de las veces invisible.
-->

---
transition: fade-out
---

# Componentes de un sistema IoT

<div grid="~ cols-3 gap-4" class="mt-2">

<div class="p-3 rounded-lg border border-white/20 bg-white/5">
  <div class="text-2xl mb-1 text-center">🌡️</div>
  <div class="font-bold text-center mb-1">Sensores</div>
  <div class="text-sm opacity-70">
    Capturan datos del mundo físico: temperatura, humedad, presión, luz, movimiento, gas...
  </div>
  <div class="text-xs mt-2 opacity-50">DHT22, BME280, PIR, LDR...</div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5">
  <div class="text-2xl mb-1 text-center">⚙️</div>
  <div class="font-bold text-center mb-1">Actuadores</div>
  <div class="text-sm opacity-70">
    Producen un efecto en el mundo físico: motores, relés, LEDs, buzzer, servo, display...
  </div>
  <div class="text-xs mt-2 opacity-50">SG90, OLED, Relay module...</div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5">
  <div class="text-2xl mb-1 text-center">🧠</div>
  <div class="font-bold text-center mb-1">Microcontrolador / SBC</div>
  <div class="text-sm opacity-70">
    El cerebro: lee sensores, toma decisiones, controla actuadores, gestiona conectividad.
  </div>
  <div class="text-xs mt-2 opacity-50">ESP32, Arduino, RPi...</div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5">
  <div class="text-2xl mb-1 text-center">📡</div>
  <div class="font-bold text-center mb-1">Conectividad</div>
  <div class="text-sm opacity-70">
    Canal de comunicación: WiFi, Bluetooth, LoRa, Zigbee, 4G/5G, Ethernet.
  </div>
  <div class="text-xs mt-2 opacity-50">MQTT, HTTP, WebSocket...</div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5">
  <div class="text-2xl mb-1 text-center">☁️</div>
  <div class="font-bold text-center mb-1">Nube / Servidor</div>
  <div class="text-sm opacity-70">
    Almacena, procesa y visualiza datos. Lógica de negocio y dashboards.
  </div>
  <div class="text-xs mt-2 opacity-50">AWS IoT, Home Assistant, Node-RED...</div>
</div>

<div class="p-3 rounded-lg border border-white/20 bg-white/5">
  <div class="text-2xl mb-1 text-center">📱</div>
  <div class="font-bold text-center mb-1">Interfaz / App</div>
  <div class="text-sm opacity-70">
    El humano en el loop: apps móviles, dashboards web, alertas, automatizaciones.
  </div>
  <div class="text-xs mt-2 opacity-50">Grafana, Blynk, Home Assistant UI...</div>
</div>

</div>

<!--
Para cada componente dar un ejemplo concreto y tangible. Hacer la pregunta: "¿qué pasa si falla la conectividad? ¿el sensor deja de funcionar?" — respuesta: no, depende de si hay lógica local. Eso lleva a hablar de edge computing. Este modelo de 6 componentes es el framework conceptual de todo el módulo de IoT.
-->

---
transition: slide-up
---

# Flujo típico de un sistema IoT

<div class="text-center mt-20">

```mermaid {scale: 0.6}
block-beta
  columns 7
  
  B["📡 Transmisión\nWiFi / MQTT / HTTP"] space
  C["⚙️ Procesamiento\nCloud / Edge"] space
  D["📊 Visualización\nDashboard / Alerta"] space
  E["🎯 Decisión\nRegla / ML / Humano"]
  space:7
  A["🌡️ Medición\nSensor captura dato"]
  space:5
  F["🔧 Acción\nActuador / Notificación"]
  space:7

  A --> B
  B --> C
  C --> D
  D --> E
  E --> F
  
  F --> A
  
  style A fill:#2B90B6
  style F fill:#2d6b2d
  style E fill:#a050f0
```
</div>

<div v-click class="mt-3 p-3 rounded bg-white/5 border border-white/20">

**Ejemplo concreto:** Estación meteorológica con ESP32
`DHT22` → mide temperatura → `WiFi/MQTT` → `Home Assistant` → dashboard → si T > 28°C → `relay` enciende ventilador

</div>

<!-- IMAGE SUGGESTION: ./images/IOT esp32 architecture diagram.png como imagen complementaria del flujo -->
<!-- IMAGE SUGGESTION: ./images/iot device architecture diagram.png para arquitectura general -->

<!--
Este flujo es el mapa del tesoro de todo el módulo. Todo lo que vamos a construir en los talleres sigue este patrón. Pedir que identifiquen cada componente del ejemplo de la estación meteorológica con los nodos del diagrama. Mencionar que el "feedback loop" es lo que convierte un sistema de monitoreo en un sistema de control automático.
-->

---
layout: center
class: text-center
transition: fade-out
---

# Resumen del módulo

<div grid="~ cols-3 gap-4" class="mt-4">

<div v-click class="p-3 rounded border border-white/20 bg-white/5">
  <div class="text-2xl mb-1">🔬</div>
  <div class="text-sm font-bold">Sistemas Embebidos</div>
  <div class="text-xs opacity-60 mt-1">Propósito específico, bare-metal, eficiencia</div>
</div>

<div v-click class="p-3 rounded border border-white/20 bg-white/5">
  <div class="text-2xl mb-1">💻</div>
  <div class="text-sm font-bold">SBC</div>
  <div class="text-xs opacity-60 mt-1">Embedded Linux, más potente, más consumo</div>
</div>

<div v-click class="p-3 rounded border border-white/20 bg-white/5">
  <div class="text-2xl mb-1">⚡</div>
  <div class="text-sm font-bold">Microcontrolador</div>
  <div class="text-xs opacity-60 mt-1">Bajo consumo, interfaces, tiempo real</div>
</div>

<div v-click class="p-3 rounded border border-white/20 bg-white/5">
  <div class="text-2xl mb-1">🔵</div>
  <div class="text-sm font-bold">Arduino</div>
  <div class="text-xs opacity-60 mt-1">Filosofía open, comunidad, shields</div>
</div>

<div v-click class="p-3 rounded border border-white/20 bg-white/5">
  <div class="text-2xl mb-1">🔴</div>
  <div class="text-sm font-bold">Raspberry Pi</div>
  <div class="text-xs opacity-60 mt-1">Educación, Linux completo, periféricos avanzados</div>
</div>

<div v-click class="p-3 rounded border border-white/20 bg-white/5">
  <div class="text-2xl mb-1">🟦</div>
  <div class="text-sm font-bold">ESP32</div>
  <div class="text-xs opacity-60 mt-1">WiFi+BT, open-source, IoT ideal</div>
</div>

</div>

<div v-click class="mt-4 text-lg">

**Siguiente:** Primeros pasos con ESP32 🚀

</div>

<!--
Cierre del módulo. Recapitular los puntos clave en 2 minutos. Abrir espacio para preguntas. Si hay tiempo, hacer una demo en vivo: flashear un ESP32 con un "Hola Mundo" (blink LED) desde Arduino IDE para que vean el flujo completo en tiempo real.
-->

---
layout: center
class: text-center
---
# ¡Gracias por su atención!

Preguntas...

<Image src="/images/question_cat.jpg" class="h-40 mx-auto mt-4" />


---
layout: center
class: text-center
---

# Referencias y recursos

<div class="mt-6 space-y-4 text-left max-w-2xl mx-auto">

<div class="p-3 rounded border border-white/20 bg-white/5">
  <div class="font-bold">🚀 Apollo Guidance Computer</div>
  <a href="https://hackaday.com/2018/11/12/an-apollo-guidance-computer-laid-bare/" class="text-blue-400 text-sm">hackaday.com — An Apollo Guidance Computer Laid Bare</a>
</div>

<div class="p-3 rounded border border-white/20 bg-white/5">
  <div class="font-bold">⌨️ Teclado mecánico open-source</div>
  <a href="https://hackaday.com/2017/11/10/an-awesome-open-mechanical-keyboard/" class="text-blue-400 text-sm">hackaday.com — An Awesome Open Mechanical Keyboard</a>
</div>

<div class="p-3 rounded border border-white/20 bg-white/5">
  <div class="font-bold">📚 Documentación ESP-IDF</div>
  <a href="https://docs.espressif.com/projects/esp-idf/en/latest/" class="text-blue-400 text-sm">docs.espressif.com</a>
</div>

<div class="p-3 rounded border border-white/20 bg-white/5">
  <div class="font-bold">🍓 Raspberry Pi Foundation</div>
  <a href="https://www.raspberrypi.org" class="text-blue-400 text-sm">raspberrypi.org</a>
</div>

</div>

<div class="mt-8 text-sm opacity-50">

Presentación creada con [Slidev](https://sli.dev) · Imágenes propias del taller y de dominio público

</div>

<!--
Dejar estas referencias disponibles para que los estudiantes profundicen por su cuenta. Hackaday es especialmente valioso — tiene artículos técnicos accesibles sobre hardware real. La documentación de ESP-IDF es la fuente de verdad para el ESP32.
-->

<style>
.slidev-layout,
.slidev-layout * {
  user-select: text !important;
  -webkit-user-select: text !important;
}

html,
body,
#app {
  user-select: text !important;
  -webkit-user-select: text !important;
}
</style>
