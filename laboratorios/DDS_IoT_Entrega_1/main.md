# Laboratorio 1 — Entrega 1
## Comunicación ESP-NOW, Sensado y Registro de Datos en la Nube

*Diseño y Desarrollo de Sistemas IoT*  
Facultad de Ingeniería y Ciencias Aplicadas — Universidad de los Andes

**Fecha límite de entrega:** 27 de marzo, 23:59 hrs (vía Canvas)

---

## 1. Introducción

Este laboratorio constituye la primera aproximación práctica al ecosistema de desarrollo con microcontroladores ESP32 en el contexto de sistemas IoT. A lo largo de cuatro desafíos progresivos, deberán construir y validar los bloques fundamentales que representan algunos de los sistemas de instrumentación del proyecto del curso: interacción con actuadores LED RGB programable, detección de presencia con radar UART, medición ambiental con sensor digital, comunicación inalámbrica mediante el protocolo ESP-NOW y registro automático de datos en la nube a través de Google Sheets.

La experiencia está diseñada para que el equipo distribuya responsabilidades de manera deliberada, de modo que cada integrante adquiera dominio sobre una parte del sistema y, al mismo tiempo, comprenda cómo se integra con el resto.

---

### 1.1 Trabajo en Equipo y Distribución de Roles

El laboratorio debe realizarse en grupos de **cuatro (4) integrantes**. Antes de comenzar, el equipo debe definir y registrar en la bitácora los roles de cada integrante. Se sugiere la siguiente distribución, aunque el equipo puede adaptarla según sus fortalezas:

| Rol | Responsabilidades principales |
|---|---|
| **Hardware** | Montaje del circuito en protoboard, conexionado de sensores y actuadores, elaboración del diagrama eléctrico final. |
| **Firmware** | Programación de ambos ESP32, integración de librerías, depuración del código y documentación de funciones. |
| **Datos y Nube** | Configuración del App Script en Google Sheets, diseño del *webhook* HTTP, validación del registro de datos. |
| **Documentación** | Redacción del informe, registro fotográfico, elaboración de diagramas de arquitectura y consolidación de la entrega. |

Los roles no son excluyentes: se espera colaboración transversal durante todo el laboratorio, especialmente en los desafíos de integración.

---

## 2. Materiales

Cada equipo dispondrá del siguiente kit de componentes para el desarrollo del laboratorio:

| Componente | Cant. | Descripción |
|---|---|---|
| ESP32-S3-WROOM-1 | 2 | Microcontrolador principal con Wi-Fi, Bluetooth y soporte ESP-NOW. Incluye LED RGB WS2812 integrado en la placa. |
| Sensor DHT11 | 1 | Sensor digital de temperatura y humedad relativa. Rango: 0–50 °C, 20–90 % HR. |
| Sensor Radar HLK-LD2420 | 1 | Radar de presencia y movimiento por comunicación UART a 3,3 V. Detecta distancia del objetivo. |
| Protoboard | 1 | Placa de prototipado sin soldadura. |
| Jumpers macho–macho | x | Cables de conexión para protoboard. |

---

## 3. Protocolos de Comunicación

En este laboratorio se emplean tres protocolos de comunicación: **ESP-NOW** para la transmisión inalámbrica entre los dos ESP32, **UART** para la lectura del sensor radar HLK-LD2420, y **HTTP** para el registro de datos en Google Sheets mediante un *Web App* de Google Apps Script. La descripción técnica detallada de cada protocolo, sus parámetros de configuración y su rol en la arquitectura del sistema forman parte de los contenidos requeridos en el informe de la entrega (véase sección [5.3](#53-estructura-del-informe)).

---

## 4. Desafíos

Los cuatro desafíos están diseñados para construirse de forma incremental. El Desafío 4 integra los resultados de los tres anteriores.

---

### 4.1 Desafío 1 — Entorno de Desarrollo y Control del LED RGB WS2812

**Objetivo:** Configurar el entorno de desarrollo para ESP32-S3 en Arduino IDE y controlar el LED RGB WS2812 integrado en la placa mediante la librería `Adafruit_NeoPixel`, modificando su color y nivel de brillo de forma programática.

#### Paso 1: Instalación de Arduino IDE

Descargar e instalar Arduino IDE 2.x desde https://www.arduino.cc/en/software. Una vez abierto el programa, agregar el soporte para placas ESP32.

1. Abrir Arduino IDE y dirigirse a **File → Preferences**.
2. En el campo *Additional boards manager URLs*, ingresar la siguiente dirección y confirmar con **OK**:  
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. Dirigirse a **Tools → Board → Boards Manager**, buscar `esp32` (Espressif Systems) e instalar la versión más reciente.
4. Conectar el ESP32-S3 por USB. En **Tools → Board**, seleccionar **ESP32S3 Dev Module**.
5. En **Tools → Port**, seleccionar el puerto COM correspondiente al dispositivo conectado.

#### Paso 2: Instalación de la Librería Adafruit NeoPixel

En Arduino IDE, dirigirse a **Sketch → Include Library → Manage Libraries**, buscar `Adafruit NeoPixel` e instalar la librería publicada por Adafruit Industries. Una vez completada la instalación, la librería quedará disponible en **Sketch → Include Library** bajo la sección *Contributed libraries*.

#### Paso 3: Identificación del Pin del LED WS2812

El módulo ESP32-S3-WROOM-1 incorpora un LED RGB WS2812B directamente en la placa, conectado al **GPIO 48** en la mayoría de los módulos de desarrollo basados en este chip. Antes de programar, siempre se recomienda verificar el esquemático del fabricante, ya que algunos asignan este periférico a un GPIO distinto.

#### Paso 4: Implementación del Firmware

Con el entorno configurado y la librería instalada, el equipo debe escribir el firmware que inicialice el objeto `Adafruit_NeoPixel` con el GPIO y la cantidad de LEDs correctos, y que controle el color y el brillo del LED de forma cíclica mediante las funciones `setPixelColor()`, `setBrightness()` y `show()` *(se revisará un ejemplo de implementación durante la clase).*

#### Criterio de Aceptación

El Desafío 1 se considera completado cuando el LED RGB enciende en al menos tres colores distintos con diferentes niveles de brillo de forma cíclica y reproducible, y cada cambio de estado queda reflejado en el monitor serial. Documentar con fotografías del hardware.

---

### 4.2 Desafío 2 — Detección de Proximidad con Radar HLK-LD2420 y Comunicación ESP-NOW

**Objetivo:** Conectar el sensor radar HLK-LD2420 al ESP32 Nodo, leer la distancia del objetivo detectado y transmitirla mediante ESP-NOW al ESP32 Gateway. El Gateway debe indicar visualmente la proximidad del objeto mediante el LED RGB según la siguiente escala:

| Condición | Color LED | Descripción |
|---|---|---|
| Sin detección o distancia > 200 cm | Rojo | Objeto fuera de rango o ausente |
| 100 cm ≤ distancia ≤ 200 cm | Naranja | Objeto en rango intermedio |
| Distancia < 100 cm | Verde | Objeto en proximidad cercana |

#### Paso 1: Conexionado del HLK-LD2420 al Nodo ESP32

El sensor HLK-LD2420 se alimenta a 3,3 V y se comunica mediante UART. Realizar las conexiones de alimentación según la tabla siguiente y seleccionar los pines TX/RX de forma justificada.

| Pin HLK-LD2420 | Pin ESP32-S3 | Descripción |
|---|---|---|
| VCC | 3V3 | Alimentación 3,3 V |
| GND | GND | Tierra común |
| TX | GPIO a definir (RX) | Salida de datos del sensor |
| RX | GPIO a definir (TX) | Entrada de comandos al sensor |

**Importante:** Los niveles lógicos del HLK-LD2420 son de 3,3 V, lo que lo hace compatible directo con el ESP32-S3. No se requiere divisor de voltaje ni adaptador de nivel lógico.

**Pregunta de diseño:** El ESP32-S3 reserva el bus `UART0` para la comunicación con el monitor serial a través del puerto USB. ¿Qué ocurriría si se conectara el sensor HLK-LD2420 a los pines de ese mismo bus? Consideren esta restricción al momento de seleccionar los GPIOs y justifique su elección en el informe.

#### Paso 2: Instalación de la Librería LD2420

La comunicación con el sensor es mediante el protocolo UART, pero para simplificar las cosas durante este laboratorio nos apoyaremos de una librería hecha por la comunidad para el `LD2420`, disponible en el siguiente repositorio:

https://github.com/cyrixninja/LD2420

Para instalarla en Arduino IDE, seguir la siguiente secuencia:

| # | Acción | Detalle |
|---|---|---|
| 1 | Descargar el repositorio | En la página de GitHub, hacer clic en **Code → Download ZIP** y guardar el archivo en el equipo. |
| 2 | Abrir el gestor de librerías | En Arduino IDE, ir a **Sketch → Include Library → Add .ZIP Library…** |
| 3 | Seleccionar el archivo | Navegar hasta el archivo `.zip` descargado y confirmar con **Abrir**. Arduino IDE instalará la librería automáticamente. |
| 4 | Verificar la instalación | Crear un nuevo sketch y agregar `#include "LD2420.h"`. Si no aparece ningún error de compilación, la instalación fue exitosa. |

#### Paso 3: Inicialización del Sensor y Lectura de Distancia

Una vez instalada la librería, el equipo debe inicializar el objeto `LD2420` sobre `Serial2` con los pines definidos, configurar el rango de detección y el intervalo de actualización, y obtener la distancia medida mediante el método `getDistance()` dentro del ciclo principal *(se revisará un ejemplo de inicialización y lectura durante la clase).*

#### Paso 4: Obtención de la Dirección MAC del Gateway

Para establecer la comunicación ESP-NOW, el Nodo debe conocer la dirección MAC del Gateway antes de compilar su firmware. Cargar un sketch temporal en el ESP32 Gateway que imprima su dirección MAC por el monitor serial utilizando `WiFi.macAddress()`, registrar el valor obtenido y utilizarlo en la configuración del *peer* ESP-NOW del Nodo *(se revisará un ejemplo de este sketch durante la clase).*

#### Paso 5: Implementación del Sistema

Con los bloques anteriores validados de forma independiente, el equipo debe integrar en el **Nodo**: la lectura periódica del radar, el empaquetado de la distancia medida en una estructura de datos y su transmisión vía ESP-NOW al Gateway. En el **Gateway**: la recepción del paquete y el control del LED RGB según la escala de proximidad definida *(se revisará la estructura básica de un sistema ESP-NOW emisor–receptor durante la clase).*

#### Criterio de Aceptación

El Desafío 2 se considera completado cuando el LED del Gateway refleja correctamente los tres estados de proximidad en respuesta al movimiento de un objeto frente al radar, y ambos monitores seriales registran los eventos de transmisión y recepción. Documentar con fotografías del hardware y capturas del monitor serial para cada uno de los tres estados.

---

### 4.3 Desafío 3 — Medición Ambiental con DHT11 y Registro en Google Sheets

**Objetivo:** Conectar el sensor DHT11 al ESP32 Gateway, conectar dicho ESP32 a una red Wi-Fi y enviar las lecturas de temperatura y humedad a una hoja de cálculo de Google Sheets mediante un *endpoint* creado con Google Apps Script.

#### 1. Configuración del Hardware

El sensor DHT11 tiene tres pines: VCC (3,3 V o 5 V), GND y DATA. Conectar el pin DATA a un GPIO libre del ESP32 Gateway. Instalar la librería `DHT sensor library` de Adafruit desde el gestor de librerías de Arduino IDE.

#### 2. Creación del Endpoint en Google Apps Script

a. Crear una nueva hoja de cálculo en Google Sheets y nombrar la primera hoja `Datos`.  
b. Definir los encabezados en la fila 1: `Timestamp`, `Temperatura (°C)`, `Humedad (%)`.  
c. En Google Sheets, ir a **Extensiones → Apps Script** e implementar una función `doGet(e)` que lea los parámetros `temp` y `hum` de la petición y los registre en la hoja mediante `appendRow()` *(se revisará el código completo del script durante la clase).*  
d. Guardar el script y hacer clic en **Implementar → Nueva implementación**.  
e. Seleccionar tipo **Aplicación web**, configurar *Ejecutar como* "Yo" y *Quién tiene acceso* como "Cualquier persona".  
f. Autorizar los permisos solicitados y copiar la URL del *Web App* generada.

La URL obtenida debe reemplazarse en el firmware del ESP32 y tratarse como información confidencial; no debe compartirse públicamente.

#### 3. Firmware del ESP32 Gateway

El equipo debe desarrollar el firmware basándose en las librerías `DHT.h` y `HTTPClient.h`, enviando una petición HTTP GET a la URL del Apps Script con los parámetros `temp` y `hum`. Se recomienda una frecuencia de envío de **30 segundos** para no saturar la hoja de cálculo durante las pruebas *(se revisará la estructura de la petición HTTP GET durante la clase).*

**Pregunta de diseño:** ¿Cuáles son las consecuencias de no configurar una frecuencia de muestreo razonable? Consideren el impacto tanto en el volumen de datos almacenados como en el comportamiento del microcontrolador y la disponibilidad del servicio receptor, y justifique la frecuencia elegida por el equipo en el informe.

#### Criterio de Aceptación

El Desafío 3 se considera completado cuando la hoja de cálculo de Google Sheets registra al menos 10 filas de datos con *timestamps* correctos y valores de temperatura y humedad coherentes con el ambiente del laboratorio. Documentar con capturas de pantalla de la hoja de cálculo y fotografías del circuito implementado.

---

### 4.4 Desafío 4 — Integración del Sistema Completo

**Objetivo:** Integrar los tres desafíos anteriores en un sistema que simula una aplicación de casa inteligente. El Nodo monitorea el entorno con el radar HLK-LD2420; cuando detecta presencia a menos de 200 cm, notifica al Gateway vía ESP-NOW. El Gateway, que cuenta con el sensor DHT11, registra la temperatura ambiente del instante en Google Sheets para que un sistema externo —como una calefacción automática— pueda tomar decisiones basadas en ese dato.

#### Arquitectura del Sistema

| Componente | Función en el Sistema |
|---|---|
| **Nodo ESP32** | Monitorea el entorno con el radar HLK-LD2420 vía UART. Cuando detecta presencia a menos de 200 cm, transmite vía ESP-NOW al Gateway la distancia medida y un indicador de detección. |
| **Gateway ESP32** | Recibe el paquete ESP-NOW. Mide la temperatura ambiente con el DHT11 en el instante de la notificación. Registra en Google Sheets el *timestamp*, la distancia reportada y la temperatura medida. Controla el LED RGB para indicar el estado del sistema. |
| **Google Sheets** | Servidor de datos en la nube. Cada fila representa un evento de detección con su temperatura asociada, disponible para que un sistema externo evalúe si activar la calefacción u otro actuador. |

#### Estructura del Paquete ESP-NOW

El equipo debe definir una estructura de datos en el firmware del Nodo que incluya al menos los campos `movimiento` (booleano) y `distancia_cm` (flotante), y transmitirla como arreglo de bytes mediante `esp_now_send()`. La temperatura **no** se incluye en el paquete: es responsabilidad del Gateway medirla localmente con el DHT11 en el momento en que recibe la notificación *(se revisará la definición de la estructura y su uso durante la clase).*

#### Lógica de Comportamiento del LED en el Gateway

1. Al recibir un paquete con `movimiento == true` (distancia < 200 cm): destello azul breve (100 ms) para confirmar recepción, seguido de LED **rojo** sostenido mientras el evento está activo.
2. Al recibir un paquete con `movimiento == false`: LED **verde** sostenido indicando que no hay presencia detectada.
3. Sin paquetes recibidos en los últimos 5 segundos: LED **apagado** para indicar pérdida de comunicación con el Nodo.

#### Columnas Sugeridas en Google Sheets

`Timestamp` &nbsp; `Distancia_cm` &nbsp; `Temperatura_C` &nbsp; `Humedad_%` &nbsp; `Alerta`

El campo `Alerta` puede contener un valor como `SI` o `NO` según si la temperatura registrada supera un umbral definido por el equipo, simulando la decisión de activar la calefacción.

**Pregunta de diseño:** En este sistema el Nodo transmite un paquete ESP-NOW únicamente cuando el radar detecta presencia a menos de 200 cm, en lugar de enviar la distancia de forma continua. ¿Qué ventajas tiene este enfoque basado en eventos frente a una transmisión constante? Considerando esta arquitectura, identifique además al menos dos limitaciones concretas de ESP-NOW que podrían afectar el funcionamiento del sistema en un despliegue real.

#### Criterio de Aceptación

El Desafío 4 se considera completado cuando el sistema registra en Google Sheets al menos **20 eventos** durante una prueba de 10 minutos, cada uno con datos de distancia, temperatura y humedad coherentes con el entorno, el LED del Gateway responde correctamente en cada caso y no se observan reinicios inesperados en ninguna de las dos placas.

---

## 5. Entrega del Laboratorio

### 5.1 Formato y Plazo

La entrega se realiza **exclusivamente a través de Canvas** antes del **27 de marzo a las 23:59 hrs**. Entregas fuera de plazo no serán evaluadas salvo justificación previa aprobada por el cuerpo docente.

### 5.2 Contenido de la Entrega

La entrega debe incluir los siguientes elementos en un único archivo comprimido (`.zip`):

1. **Informe en PDF** con los contenidos descritos en la sección [5.3](#53-estructura-del-informe).
2. **Códigos fuente** de ambos ESP32 (`.ino`) con comentarios explicativos en cada función relevante.
3. **Link público a Google Sheets** con los datos recolectados durante el Desafío 4 (incluir en el informe y en un archivo `README.txt`).
4. **Fotografías del sistema** en funcionamiento (mínimo 4 fotografías: circuito montado, y captura de Google Sheets con datos).

### 5.3 Estructura del Informe

El informe debe redactarse en formato profesional y contener las siguientes secciones:

1. **Portada:** Nombre del equipo, integrantes, roles asignados y fecha.
2. **Descripción de Materiales:** Especificaciones técnicas relevantes de cada componente utilizado y justificación de los pines seleccionados.
3. **Tabla de Conexiones:** Tabla completa de conexiones a los diferentes GPIOs y pines de cada sensor.
4. **Protocolos de Comunicación:** Descripción de ESP-NOW, UART y HTTP/Google Apps Script en el contexto del sistema implementado. Incluir diagrama de flujo de datos desde la detección hasta el registro en la nube.
5. **Arquitectura Final del Sistema:** Diagrama de bloques que muestre los componentes, los protocolos entre ellos y el flujo de información de extremo a extremo.
6. **Observaciones:** Bitácora con los incidentes, errores encontrados y soluciones implementadas durante el laboratorio.

---

## 6. Criterios de Evaluación

Se otorga **1,0 punto base** a todas las entregas realizadas dentro del plazo. Los puntos restantes (6,0) se distribuyen según la siguiente rúbrica:

| Criterio | Puntos | Descripción |
|---|---|---|
| **Desafíos 1 y 2** | 1,2 | Evidencia de funcionamiento del LED WS2812 (colores y brillo) y del sistema radar + ESP-NOW con indicación visual correcta. |
| **Desafío 3** | 0,8 | Hoja de cálculo pública con al menos 10 registros de temperatura y humedad con *timestamps* correctos. |
| **Desafío 4 — Sistema Integrado** | 1,0 | Hoja de cálculo con al menos 20 eventos que incluyan distancia y temperatura. LED del Gateway responde correctamente. Sin reinicios inesperados. |
| **Informe — Diagrama y Arquitectura** | 0,6 | Diagrama de conexiones completo y legible. Diagrama de bloques de la arquitectura del sistema con protocolos identificados. |
| **Informe y Preguntas de Diseño** | 2,0 | Se evalúa profundidad técnica, coherencia con el sistema implementado y claridad de la argumentación. |
| **Código Fuente** | 0,4 | Código comentado, legible y estructurado. Funciones con descripción. Sin código muerto ni variables sin usar. |

**Nota:** La ausencia de alguno de los archivos requeridos (código, link a Google Sheets, fotografías) será penalizada con 0,3 puntos por elemento faltante, descontados del total.
