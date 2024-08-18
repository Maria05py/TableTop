# TableTop
Documentación del proyecto "TableTop" para el evento ExpoCenfo de la Universidad Cenfotec. Este proyecto propone la creación de un prototipo de mesa multifuncional que maximiza el uso de sistemas ciberfísicos, promoviendo el bienestar y acercando la tecnología a distintas generaciones.

## ¿Qué es TableTop?
Este proyecto se centra en una mesa con un display de luces LED, diseñada para ayudar a niños pequeños a mejorar su ansiedad, habilidades motoras y atención. La mesa utiliza sensores infrarrojos para encender, apagar y controlar las luces, lo que permite su uso en juegos de rapidez, concentración y diversas terapias. Además, se integra una aplicación móvil que permitirá cambiar las luces, seleccionar juegos y gestionar funciones básicas a través de tecnología RFID. A futuro también se contempla el uso de Alexa para comandos de voz, proporcionando instrucciones y funcionalidades accesibles para los más pequeños. Adicionalmente, se busca la posibilidad de actualizar juegos y características desde la nube, manteniendo la mesa al día con nuevas opciones. La mesa no es solo un espacio físico, sino un entorno terapéutico y de aprendizaje que utiliza tecnología avanzada para ofrecer experiencias cercanas al uso de la tecnología.

El presente proyecto es un prototipo equipado con las funcionalidades básicas de: Conectarse a su debida aplicación, mostrar patrones de movimiento en el display LED y reaccionar ante los estímulos de los sensores infrarojos. 

## Olimpiadas de Computación inteligente (ExpoCenfo)
Las Olimpiadas de Computación inteligente corresponden a una competencia costarricense con sede en la Universidad Cenfotec, abierta a todos los estudiantes universitarios entusiastas de la tecnología que deseen aceptar el reto y competir en la mejor creación de un sistema ciberfísico. Dicho evento tiene lugar el día miércoles 21 de agosto con cede en la Universidad Cenfotec. El sitio oficial del evento, incluyendo las normativas y demás especificaciones, se encuentran en el siguiente enlace: [link](https://ucenfotec.ac.cr/expocenfo/).

## Índice de Contenido
1. [Diseño 3D](#diseño-3d)
2. [Materiales no electrónicos](#materiales-no-electrónicos)
3. [Materiales electrónicos](#materiales-electrónicos)
4. [Pasos y creación ](#pasos-y-creación)
5. [Códigos y librerías empleadas](#códigos-y-librerías-empleadas)
6. [Usos y problemas detectados](#Usos-y-problemas-detectados)
8. [Licencia](#licencia)

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
- Cables. 
  
## Pasos y creación:
Una vez creado el diseño, cortadas y listas las piezas, se procede a armar la mesa en su totalidad (Unión de cada parte de la melamina, uniónes entre los separadores de la matriz). 

![image](https://github.com/user-attachments/assets/cea96dda-4b39-48cc-afbb-f9b701a0e02d)
![image](https://github.com/user-attachments/assets/ab316317-6fc9-4fa2-8db5-f5c170075d2d)
![image](https://github.com/user-attachments/assets/9cddcc93-1087-4b29-9495-8d67c8af48c2)
![image](https://github.com/user-attachments/assets/98d67322-14f6-40d8-8412-d35c240fbdb2)

Elistados en orden, primeramente se deben de calibrar los 100 sensores infrarojos para que los mismos reaccionen ante una distancia similar al momento de pasar la mano por encima de los infrarojos correspondientes. Seguidamente, se procede a cortar cable 3 tres colores diferentes (En nuestro caso rojo, verde y negro) de 5cm para conectar correctamente cada uno de los pines LED (5V, GRN y DO) respectivamente. 

![image](https://github.com/user-attachments/assets/be3ef577-d0fc-41c9-b9e3-aff1f6c9b0c3)
(Corte de los cables y uso de la protoboard para la calibrar los 100 sensores infrarojos a utilizar)

Una vez conectados los pines en tiras de 10 LEDs (colocando soldadura a cada final de los cables y colocando cada color en su pin correspondiente) como es posible visualizar en las siguientes imágenes.

![image](https://github.com/user-attachments/assets/e75d7ab4-8aed-4f1d-bdf3-5083e333dd1f)
![image](https://github.com/user-attachments/assets/deed618c-77c6-4638-b285-7de243821142)
![image](https://github.com/user-attachments/assets/4c2cef89-ea78-4df5-ba46-4a564869e9fa)
![image](https://github.com/user-attachments/assets/5faa360f-aaec-4ef5-a2cf-50a391a99a63)

Luego se deben de pegar con silicón los 100 sensores infrarrojos a los separadores de la matriz con silicón caliente. Seguidamente se soldan los pines GND, 5+ y output entre sí como es posible observar en las siguientes fotografías.

![image](https://github.com/user-attachments/assets/985cd7f6-e2ed-48e9-9cc3-8d96c03b7654)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_f2a4d858](https://github.com/user-attachments/assets/b5e2ec93-259d-41d5-8a67-c49765612f34)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_85e9ffc6](https://github.com/user-attachments/assets/6ed487dd-6677-4b03-8f43-cdc099f4fda1)
![Imagen de WhatsApp 2024-08-15 a las 14 14 28_cd028e31](https://github.com/user-attachments/assets/6e28e663-47e0-4ad0-9cc2-49c20b4d5b0c)

Seguidamente, para probar las luces fue utilizada una mini versión del código "[nombre del código que contiene las animaciones en el arduino mega]" y "[nombre del cóigo usado para mostrar el texto]" (Paso opcional)

![placa de pruebas](https://github.com/user-attachments/assets/6a004c6f-42af-4e99-a255-8d5191c240c0)

Las conexiones de esta mini versión del display son las mismas utilizadas en el display final, el cual consiste en 

![Imagen de WhatsApp 2024-08-11 a las 13 56 32_20282ce5](https://github.com/user-attachments/assets/9e46617e-34ac-4399-9eff-49172ecd25af)

Para crear el display final se colocan las respectivas tiras de leds de forma en la que queden centradas con respecto a las diferentes cuadrículas de la matriz. Las conexiones entre cada una de las tiras se encuentran debajo de la tabla correspondiente. 

![Imagen de WhatsApp 2024-08-16 a las 23 11 40_c0f88f87](https://github.com/user-attachments/assets/a1d1e9e4-0f1c-4222-875c-df0e3e4b3c2d)
![Imagen de WhatsApp 2024-08-16 a las 23 14 34_636a6f1e](https://github.com/user-attachments/assets/58da91ab-2b2f-4863-8540-1ec982f6ca87)


## Códigos, mapeados y librerías empleadas:

## Usos y problemas detectados:


## Participantes:
- Braulio Garro Marín
- María Jesús Rodríguez Molina
- Geisel Thais Hernández Quesada
- Melina Valeska Soto Badilla
  
## Licencia:
Este proyecto está licenciado bajo los términos de la Licencia Creative Commons.

![image](https://github.com/user-attachments/assets/681f2a88-7127-487d-ab5a-e2d6f7267443)

