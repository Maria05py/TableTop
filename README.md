# TableTop
Documentación del proyecto "TableTop" para el evento ExpoCenfo de la Universidad Cenfotec. Este proyecto propone la creación de un prototipo de mesa multifuncional que maximiza el uso de sistemas ciberfísicos, promoviendo el bienestar y acercando la tecnología a distintas generaciones.

## Olimpiadas de Computación inteligente (ExpoCenfo)
El presente proyecto forma parte de uno de los tantos equipos participantes de las Olimpiadas de Computación inteligente, la cual corresponden a una competencia costarricense con sede en la Universidad Cenfotec, abierta a todos los estudiantes universitarios entusiastas de la tecnología que deseen aceptar el reto y competir en la mejor creación de un sistema ciberfísico. Dicho evento tiene lugar el día miércoles 21 de agosto con cede en la Universidad Cenfotec. El sitio oficial del evento, incluyendo las normativas y demás especificaciones, se encuentran en el siguiente enlace: [link](https://ucenfotec.ac.cr/expocenfo/).

## ¿Qué es TableTop?
Este proyecto se centra en una mesa con un display de luces LED, diseñada para ayudar a niños pequeños a mejorar su ansiedad, habilidades motoras y atención. La mesa utiliza sensores infrarrojos para encender, apagar y controlar las luces, lo que permite su uso en juegos de rapidez, concentración y diversas terapias. Además, se integra una aplicación móvil que permitirá cambiar las luces, seleccionar juegos y gestionar funciones básicas a través de tecnología RFID. A futuro también se contempla el uso de Alexa para comandos de voz, proporcionando instrucciones y funcionalidades accesibles para los más pequeños. Adicionalmente, se busca la posibilidad de actualizar juegos y características desde la nube, manteniendo la mesa al día con nuevas opciones. La mesa no es solo un espacio físico, sino un entorno terapéutico y de aprendizaje que utiliza tecnología avanzada para ofrecer experiencias cercanas al uso de la tecnología.
El propósito principal de esta mesa inteligente es crear un entorno seguro y atractivo para que los niños de la casa puedan aprender y relajarse al mismo tiempo. Permitiendo a los niños interactuar con la tecnología en un ambiente controlado, esta mesa inteligente permitirá a los más pequeños de la casa practicar sus habilidades tecnológicas y mejorar su enfoque a través de juegos interactivos y estimulantes a través del uso de luces LEDs, todo esto sin exponerlo a los niños a las redes sociales y aplicaciones con contenido inapropiado y violencia, permitiéndoles estar educados, entretenidos y seguros en el mundo online. 
Los beneficios de este proyecto para los niños de la casa son:

-**Desarrollo de habilidades cognitivas y motoras:** Esta mesa incorpora la diversión y el aprendizaje por medio de juegos que requieren concentración y resolución de problemas, como Tetris o patrones de luz, lo que les ayuda a desarrollar habilidades cognitivas como la memoria, la lógica, la concentración y el pensamiento crítico.

-**Habilidades Tecnológicas:** Ayuda a los niños a familiarizarse con la tecnología en un entorno seguro mientras les ayuda a desarrollar habilidades tecnológicas tempranas, lo que es crucial en el mundo actual.

-**"Relajación por medio de estimnulación sensorial controlada":** 
-Relajación por medio de estimnulación sensorial controlada: La luz suave y los patrones de color cambiantes crean un ambiente sensorial que promueve la calma y la concentración.

-**Aulas interactivas:** La mesa busca convertirse en una herramienta ideal para aulas interactivas, donde los estudiantes pueden participar en actividades grupales o individuales que fomenten la colaboración, la concentración y el aprendizaje a través de la tecnología. Para futuras aplicaciones nuestra mesa inteligente tiene el potencial de ser una herramienta poderosa no solo en el hogar, sino también en entornos educativos y terapéuticos.
****
El presente proyecto es un prototipo equipado con las funcionalidades básicas de: Conectarse a su debida aplicación, mostrar patrones de movimiento en el display LED y reaccionar ante los estímulos de los sensores infrarojos. 

## Índice de Contenido
1. [Organización del repositorio](#Organización-del-repositorio)
2. [Diseño 3D](#diseño-3d)
3. [Materiales no electrónicos](#materiales-no-electrónicos)
4. [Materiales electrónicos](#materiales-electrónicos)
5. [Pasos y creación ](#pasos-y-creación)
6. [Códigos y librerías empleadas](#códigos-y-librerías-empleadas)
7. [Usos y problemas detectados](#Usos-y-problemas-detectados)
8. [Licencia](#licencia)

## Carpetas y organización del repositorio:
**"Códigos":**
- Los archivos tipo C++, header, librerías y .ino necesarios para la correcta ejecución de las diferentes funcionalidades de la mesa.
- Módulos y librerías empleadas para la correcta ejecución del código principal.

**"Modelos3D":**
- Archivos correspondentes a las piezas a cortar por medio de la cortadora láser (Piezas_Superiores.skp)
- Archivos correspondientes al modelo 3D de la mesa completa (Base_mesa_en_melamina.skp)  

**"Licencia":**
- Licencia del presente proyecto y detalles sobre las restricciones correspondientes. 

**"Modelos3D":**
- Archivos correspondentes a las piezas a cortar por medio de la cortadora láser (Piezas_Superiores.skp)
- Archivos correspondientes al modelo 3D de la mesa completa (Base_mesa_en_melamina.skp)  

**"Documentos":**
- Presentación de los integrantes, detalles sobre el proyecto, implementación y resultados obtenidos.

## Diseño 3D:
El diseño 3D, a cargo del estudiante Braulio Garro Marín, fue creado desde 0 en el software "SketchUp". A continuación se muestran las dimensiones y el diseño general de la mesa, además de las piezas a cortar para el acabado final, en este caso melamina. 

![Imagen de WhatsApp 2024-06-18 a las 14 02 02_3d3d445a](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/fea3f383-6097-4f18-80c6-11b914b5fcbc)
![Imagen de WhatsApp 2024-06-18 a las 14 02 02_32868ecb](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/84a7232d-6e8e-4d38-9dd1-e6dcd4ce62df)
![Imagen de WhatsApp 2024-06-18 a las 14 02 03_3f1b13b2](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/ed11710f-07cf-4d60-bdb2-ba66b35399bf)
![Imagen de WhatsApp 2024-06-08 a las 18 51 28_593eec7b](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/4246552a-8e69-4ef2-93f1-8037917c496c)
![Imagen de WhatsApp 2024-06-08 a las 18 51 59_6e4e2997](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/2996a9c4-739b-466a-9585-86846bbcc135)
![Imagen de WhatsApp 2024-08-16 a las 15 52 16_07ad1a83](https://github.com/user-attachments/assets/c0473fe2-94e7-4e53-8424-f0b0f1d7c29e)

## Materiales no electrónicos:
- Melamina (2500mm x 1830mm)
- MDF (122cm x 244cm)
  
## Materiales electrónicos:
- Placa de desarrollo ESP32.
- Cargador de iones de litio multicelda 2S, 3S, 4S.
- uJPM TXS0108E 8-Channel Logic Level Bi-Directional Converter.
- Convertidor buck ajustable de 1000W.
- Tira de luces LED WS2811 (100 LEDs utilizados en este caso).
- Módulo de placa multiplexor digital analógico (7 utilizados en este caso).
- Módulo de sensor de evitación infrarrojo IR (x100 sensores de evitación en este caso).
- Módulo RFID.
- Etiqueta universal ultraligera de 25mm.
- Cable de cobre de distintos grosores.
- Estaño.
- Cables (Preferiblemente de gran cantidad de colores en pro de mejorar la simplicidad de los pasos). 
  
## Pasos y creación:
Una vez cortadas y listas las piezas, se procede a armar la mesa en su totalidad: Unión de cada parte de la melamina (base de la mesa), uniones entre los separadores de la matriz (correspondientes a las "dentaduras"), etc... 

![image](https://github.com/user-attachments/assets/cea96dda-4b39-48cc-afbb-f9b701a0e02d)
![image](https://github.com/user-attachments/assets/ab316317-6fc9-4fa2-8db5-f5c170075d2d)
![image](https://github.com/user-attachments/assets/9cddcc93-1087-4b29-9495-8d67c8af48c2)
![image](https://github.com/user-attachments/assets/98d67322-14f6-40d8-8412-d35c240fbdb2)

Enlistados en orden, con respecto a los componentes electónicos, primeramente se deben de calibrar los 100 sensores infrarrojos para que los mismos reaccionen ante una distancia similar al momento de pasar la mano por encima de los infrarrojos correspondientes, esto se logra ajustando el "Distance Adjust" (Mirar la imagen de referencia). Seguidamente, se procede a cortar cable de 3 tres colores diferentes (En nuestro caso rojo, verde y negro) de 5cm para conectar correctamente cada uno de los pines de la tira de LED (5V, GRN y DO) respectivamente.  

![image](https://github.com/user-attachments/assets/2c02cb5e-a3f0-4da5-8d44-7647c383b616)

![Imagen de WhatsApp 2024-08-20 a las 17 43 21_59c6724c](https://github.com/user-attachments/assets/751931e9-5802-462f-8462-bf4397f7b7c8)
![image](https://github.com/user-attachments/assets/be3ef577-d0fc-41c9-b9e3-aff1f6c9b0c3)
(Corte de los cables y uso de la protoboard para calibrar los 100 sensores infrarojos a utilizar. Se recomienda el uso de la protoboard para probar al menos 5 seonsores infrarojos a la vez en pro de agilizar el proceso de creación.)

Una vez conectados los pines en tiras de 10 LEDs (colocando soldadura a cada final de los cables y colocando cada color en su pin correspondiente) como es posible visualizar en las siguientes imágenes.

![Imagen de WhatsApp 2024-08-20 a las 17 44 42_55fda35c](https://github.com/user-attachments/assets/5f4c7657-ddb4-4b23-b351-3f3ff5901109)
(Imagen de referencia: Colores y l+ogica detrás de las conexiones entre los respectivos leds. Nota: Cables de 5cm de longitud.)

![image](https://github.com/user-attachments/assets/e75d7ab4-8aed-4f1d-bdf3-5083e333dd1f)
![image](https://github.com/user-attachments/assets/deed618c-77c6-4638-b285-7de243821142)
![image](https://github.com/user-attachments/assets/4c2cef89-ea78-4df5-ba46-4a564869e9fa)
![image](https://github.com/user-attachments/assets/5faa360f-aaec-4ef5-a2cf-50a391a99a63)

Luego se deben de pegar con silicón los 100 sensores infrarrojos a los separadores de la matriz con silicón caliente. Seguidamente se sueldan los pines GND, 5+ y output entre sí como es posible observar en las siguientes fotografías.

![image](https://github.com/user-attachments/assets/985cd7f6-e2ed-48e9-9cc3-8d96c03b7654)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_f2a4d858](https://github.com/user-attachments/assets/b5e2ec93-259d-41d5-8a67-c49765612f34)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_85e9ffc6](https://github.com/user-attachments/assets/6ed487dd-6677-4b03-8f43-cdc099f4fda1)
![Imagen de WhatsApp 2024-08-15 a las 14 14 28_cd028e31](https://github.com/user-attachments/assets/6e28e663-47e0-4ad0-9cc2-49c20b4d5b0c)

Seguidamente, para probar las luces fue utilizada una mini matriz de pruebas, para la cual fue utilizda la versión de "LEDMatrix.ino, editada por Matthew Kaye. El código original se puede encontrar en el siguiente enlace: https://github.com/N00d13/10x10_LED_MATRIX_ANIMATIONS. (Paso opcional)

![placa de pruebas](https://github.com/user-attachments/assets/6a004c6f-42af-4e99-a255-8d5191c240c0)

Las conexiones de esta mini versión del display son las mismas utilizadas en el display final, el cual consiste en 

![Imagen de WhatsApp 2024-08-11 a las 13 56 32_20282ce5](https://github.com/user-attachments/assets/9e46617e-34ac-4399-9eff-49172ecd25af)

Para crear el display final se colocan las respectivas tiras de leds de forma en la que queden centradas con respecto a las diferentes cuadrículas de la matriz. Las conexiones entre cada una de las tiras se encuentran debajo de la tabla correspondiente. 

![Imagen de WhatsApp 2024-08-16 a las 23 11 40_c0f88f87](https://github.com/user-attachments/assets/a1d1e9e4-0f1c-4222-875c-df0e3e4b3c2d)
![Imagen de WhatsApp 2024-08-16 a las 23 14 34_636a6f1e](https://github.com/user-attachments/assets/58da91ab-2b2f-4863-8540-1ec982f6ca87)

Antes de completar el proceso de montaje del display, se recomienda comprobar el estado de todos los LEDs de la matriz mediante animaciones, dibujos y demás, como se puede observar en las siguientes imágenes. 

![Imagen de WhatsApp 2024-08-17 a las 18 15 02_96942961](https://github.com/user-attachments/assets/0e985deb-0709-499b-86c6-a509c6283b00)
![Imagen de WhatsApp 2024-08-18 a las 12 11 58_bb98c2f2](https://github.com/user-attachments/assets/76872487-675b-47b6-8a41-62a9dde6f59c)
![Imagen de WhatsApp 2024-08-18 a las 16 06 51_b8d5f709](https://github.com/user-attachments/assets/0f7f23f8-8b5f-4d6c-851e-5407ff1b81b6)


## Códigos, mapeados y librerías empleadas:

**"Librerías empleadas":**
- *FastLED*: Es necesaria la utilización de la presente linrería 

**"Mapeado de los lEDs":**

 9,  10,  29,  30,  49,  50,  69,  70,  89,  90,
 8,  11,  28,  31,  48,  51,  68,  71,  88,  91,
 7,  12,  27,  32,  47,  52,  67,  72,  87,  92,
 6,  13,  26,  33,  46,  53,  66,  73,  86,  93,
 5,  14,  25,  34,  45,  54,  65,  74,  85,  94,
 4,  15,  24,  35,  44,  55,  64,  75,  84,  95,
 3,  16,  23,  36,  43,  56,  63,  76,  83,  96,
 2,  17,  22,  37,  42,  57,  62,  77,  82,  97,
 1,  18,  21,  38,  41,  58,  61,  78,  81,  98,
 0,  19,  20,  39,  40,  59,  60,  79,  80,  99
 
## Resultados de la implementación:

## Usos y problemas detectados:


## Participantes:
- Braulio Garro Marín
- María Jesús Rodríguez Molina
- Geisel Thais Hernández Quesada
- Melina Valeska Soto Badilla
  
## Licencia:
Este proyecto está licenciado bajo los términos de la Licencia Creative Commons. 

![image](https://github.com/user-attachments/assets/681f2a88-7127-487d-ab5a-e2d6f7267443)

TableTop © 2024 by TableTop is licensed under CC BY-SA 4.0. To view a copy of this license, visit https://creativecommons.org/licenses/by-sa/4.0/

