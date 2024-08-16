# TableTop
Documentación del proyecto "TableTop" para el evento ExpoCenfo de la Universidad Cenfotec. Este proyecto propone la creación de una mesa multifuncional que maximiza el uso de sistemas ciberfísicos, promoviendo el bienestar y acercando la tecnología a distintas generaciones.

## ¿Qué es TableTop?
Este proyecto se centra en una mesa con un display de luces LED, diseñada para ayudar a niños pequeños a mejorar su ansiedad, habilidades motoras y atención. La mesa utiliza sensores infrarrojos para encender, apagar y controlar las luces, lo que permite su uso en juegos de rapidez, concentración y diversas terapias. Además, se integrará una aplicación móvil que permitirá cambiar las luces, seleccionar juegos y gestionar funciones básicas a través de tecnología RFID. A futuro también se contempla el uso de Alexa para comandos de voz, proporcionando instrucciones y funcionalidades accesibles para los más pequeños. Adicionalmente, se busca la posibilidad de actualizar juegos y características desde la nube, manteniendo la mesa al día con nuevas opciones. La mesa no es solo un espacio físico, sino un entorno terapéutico y de aprendizaje que utiliza tecnología avanzada para ofrecer experiencias cercanas al uso de la tecnología.

El presente proyecto es un prototipo equipado con las funcionalidades básicas de: Conectarse a su debida aplicación, mostrar patrones de movimiento en el display LED y reaccionar ante los estímulos de los sensores infrarojos. 

## Olimpiadas de Computación inteligente (ExpoCenfo)
Las Olimpiadas de Computación inteligente corresponden a una competencia costarricense con sede en la Universidad Cenfotec, abierta a todos los estudiantes universitarios entusiastas de la tecnología que deseen aceptar el reto y competir en la mejor creación de un sistema ciberfísico. Dicho evento tiene lugar el día miércoles 21 de agosto con cede en la Universidad Cenfotec. 
El sitio oficial del evento, incluyendo las normativas y demás especificaciones, se encuentran en el siguiente enlace: [link](https://ucenfotec.ac.cr/expocenfo/).

## Contenidos:
- Proyecto presentado
- Pasos llevados durante la creación
- Materiales
  - Materiales no electrónicos
  - Materiales electrónicos
- Código utilizado
- Licencia


## Diseño 3D:
![Imagen de WhatsApp 2024-06-18 a las 14 02 02_3d3d445a](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/fea3f383-6097-4f18-80c6-11b914b5fcbc)
![Imagen de WhatsApp 2024-06-18 a las 14 02 02_32868ecb](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/84a7232d-6e8e-4d38-9dd1-e6dcd4ce62df)
![Imagen de WhatsApp 2024-06-18 a las 14 02 03_3f1b13b2](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/ed11710f-07cf-4d60-bdb2-ba66b35399bf)
![Imagen de WhatsApp 2024-06-08 a las 18 51 28_593eec7b](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/4246552a-8e69-4ef2-93f1-8037917c496c)
![Imagen de WhatsApp 2024-06-08 a las 18 51 59_6e4e2997](https://github.com/Maria05py/TableTop---ExpoCenfo-/assets/160543497/2996a9c4-739b-466a-9585-86846bbcc135)

(El diseño 3D le corresponden al estudiante Braulio Garro Marín)

## Pasos llevados a cabo durante la creación:

Debido a las dimensiones de la mesa y su complejidad a nivel de hardware, el proceso de creacióm tomó gran cantidad de días. El proceso inició con el corte y unión de las dimensiones de madera, la calibración de los 100 sensores infrarrojos y la soldadura de los 100 LEDs. Luego, se creó una matriz de menor dimensión para la ejecución y prueba de código en menor escala y se soldaron las conexiones base. 

![image](https://github.com/user-attachments/assets/cea96dda-4b39-48cc-afbb-f9b701a0e02d)
![image](https://github.com/user-attachments/assets/ab316317-6fc9-4fa2-8db5-f5c170075d2d)
![image](https://github.com/user-attachments/assets/9cddcc93-1087-4b29-9495-8d67c8af48c2)
![image](https://github.com/user-attachments/assets/98d67322-14f6-40d8-8412-d35c240fbdb2)
![image](https://github.com/user-attachments/assets/5faa360f-aaec-4ef5-a2cf-50a391a99a63)
![image](https://github.com/user-attachments/assets/be3ef577-d0fc-41c9-b9e3-aff1f6c9b0c3)
![image](https://github.com/user-attachments/assets/deed618c-77c6-4638-b285-7de243821142)
![image](https://github.com/user-attachments/assets/e75d7ab4-8aed-4f1d-bdf3-5083e333dd1f)
![image](https://github.com/user-attachments/assets/4c2cef89-ea78-4df5-ba46-4a564869e9fa)
![image](https://github.com/user-attachments/assets/985cd7f6-e2ed-48e9-9cc3-8d96c03b7654)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_f2a4d858](https://github.com/user-attachments/assets/b5e2ec93-259d-41d5-8a67-c49765612f34)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_85e9ffc6](https://github.com/user-attachments/assets/6ed487dd-6677-4b03-8f43-cdc099f4fda1)
![Imagen de WhatsApp 2024-08-11 a las 13 56 32_20282ce5](https://github.com/user-attachments/assets/9e46617e-34ac-4399-9eff-49172ecd25af)
![Imagen de WhatsApp 2024-08-15 a las 14 14 28_cd028e31](https://github.com/user-attachments/assets/6e28e663-47e0-4ad0-9cc2-49c20b4d5b0c)

## Materiales no electrónicos:
- Melamina 
- Silicón caliente
  
## Materiales electrónicos:
- Placa de desarrollo ESP32
- Cargador de iones de litio multicelda 2S, 3S, 4S
- uJPM TXS0108E 8-Channel Logic Level Bi-Directional Converter
- Convertidor buck ajustable de 1000W
- Tira de luces LED WS2811 (x100 LEDs)
- Módulo de placa multiplexor digital analógico
- Módulo de sensor de evitación infrarrojo IR (x100 sensores de evitación)
- Módulo RFID
- Teclado AD de cinco teclas con botón analógico para placa de expansión arduino
- Etiqueta universal ultraligera de 25mm
- Cable de cobre de distintos grosores 


## Explicación del código:
## Manual de mapeado:
## Usos y problemas detectados:
## Librerías empleadas: 

## Participantes:
- Braulio Garro Marín
- María Jesús Rodríguez Molina
- Geisel Thais Hernández Quesada
- Melina Valeska Soto Badilla
  
## Licencia:
Creative Commons 
