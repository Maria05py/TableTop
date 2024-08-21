#include <SPI.h>
#include <MFRC522.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include "BluetoothSerial.h" 
#include <LEDMatrix.h>
#include <LEDSprites.h>
#include <LEDText.h>
#include <FontMatrise.h>

#include "Plasma.cpp" //Plasma class file
#include "Lines.cpp" //Lines class file
#include "InterruptHandler.h"

#define DATA_PIN 27 //Pin used on arduino
#define WIDTH 10 //Width of matrix
#define HEIGHT 10 //Height of matrix
#define NUM_LEDS WIDTH * HEIGHT //Total size of matrix
#define BRIGHTNESS 240 //Brightness of the Matrix. Maximum is 255
#define FRAMES_PER_SECOND  120 //This is for the doMultipleAnimations method. A lower number is slower animations

//Codigo para tetris

#define LED_PIN        27
#define COLOR_ORDER    GRB
#define CHIPSET        WS2811
#define MATRIX_WIDTH   10
#define MATRIX_HEIGHT  10
#define MATRIX_TYPE    HORIZONTAL_MATRIX

CRGB leds[NUM_LEDS];

// Pines de control para los multiplexores
const int muxS0 = 26;  // Pin de selección S0
const int muxS1 = 25;  // Pin de selección S1
const int muxS2 = 33;  // Pin de selección S2
const int muxS3 = 32;  // Pin de selección S3

const int muxSIG[] = {13, 12, 35, 34, 15, 2, 4}; // Array de pines de señal para 7 multiplexores

// Cambiado WS2812B a WS2811 para tu tira LED específica
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, 10, HEIGHT, WIDTH/10, 1, 
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE + 
    NEO_TILE_BOTTOM + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE);

cLEDMatrix<MATRIX_WIDTH, -MATRIX_HEIGHT, MATRIX_TYPE> ledsTetris;


#define TARGET_FRAME_TIME    15  // Desired update rate, though if too many leds it will just run as fast as it can!
#define INITIAL_DROP_FRAMES  20  // Start of game block drop delay in frames

// Bluetooth input
enum btnInput {NONE, ROTATE, DOWN, LEFT, RIGHT};
btnInput currentInput = NONE;

const uint8_t TetrisIData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(11110000),
  // Frame 2
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(11110000),
  // Frame 4
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000)
};
const uint8_t TetrisIMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11110000),
  // Frame 2
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11110000),
  // Frame 4
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000)
};
const uint8_t TetrisJData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(22200000),
  B8_3BIT(00200000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(02000000),
  B8_3BIT(02000000),
  B8_3BIT(22000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(20000000),
  B8_3BIT(22200000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(22000000),
  B8_3BIT(20000000),
  B8_3BIT(20000000)
};
const uint8_t TetrisJMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11100000),
  B8_1BIT(00100000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000)
};
const uint8_t TetrisLData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(33300000),
  B8_3BIT(30000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(33000000),
  B8_3BIT(03000000),
  B8_3BIT(03000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(00300000),
  B8_3BIT(33300000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(30000000),
  B8_3BIT(30000000),
  B8_3BIT(33000000)
};
const uint8_t TetrisLMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11100000),
  B8_1BIT(10000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000),
  B8_1BIT(01000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(00100000),
  B8_1BIT(11100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000)
};
const uint8_t TetrisOData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000)
};
const uint8_t TetrisOMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000)
};
const uint8_t TetrisSData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(05500000),
  B8_3BIT(55000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(50000000),
  B8_3BIT(55000000),
  B8_3BIT(05000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(05500000),
  B8_3BIT(55000000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(50000000),
  B8_3BIT(55000000),
  B8_3BIT(05000000)
};
const uint8_t TetrisSMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(01100000),
  B8_1BIT(11000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(01100000),
  B8_1BIT(11000000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000)
};
const uint8_t TetrisTData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(66600000),
  B8_3BIT(06000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(06000000),
  B8_3BIT(66000000),
  B8_3BIT(06000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(06000000),
  B8_3BIT(66600000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(60000000),
  B8_3BIT(66000000),
  B8_3BIT(60000000)
};
const uint8_t TetrisTMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11100000),
  B8_1BIT(01000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000)
};
const uint8_t TetrisZData[] = 
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(77000000),
  B8_3BIT(07700000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(07000000),
  B8_3BIT(77000000),
  B8_3BIT(70000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(77000000),
  B8_3BIT(07700000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(07000000),
  B8_3BIT(77000000),
  B8_3BIT(70000000)
};
const uint8_t TetrisZMask[] = 
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(01100000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(01100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000)
};

#define TETRIS_SPR_WIDTH  4
#define TETRIS_SPR_HEIGHT 4
const uint8_t *TetrisSprData[] = { TetrisIData, TetrisJData, TetrisLData, TetrisOData, TetrisSData, TetrisTData, TetrisZData };
const uint8_t *TetrisSprMask[] = { TetrisIMask, TetrisJMask, TetrisLMask, TetrisOMask, TetrisSMask, TetrisTMask, TetrisZMask};
const struct CRGB TetrisColours[] = { CRGB(0, 255, 255), CRGB(0, 0, 255), CRGB(255, 165, 0), CRGB(255, 255, 0), CRGB(50, 205, 50), CRGB(255, 0, 255), CRGB(255, 0, 0) };

uint8_t PlayfieldData[MATRIX_HEIGHT * ((MATRIX_WIDTH + 7) / 8) * _3BIT];
uint8_t PlayfieldMask[MATRIX_HEIGHT * ((MATRIX_WIDTH + 7) / 8) * _1BIT];
uint8_t CompletedLinesData[TETRIS_SPR_HEIGHT * ((MATRIX_WIDTH + 7) / 8) * _1BIT];
const struct CRGB CompletedLinesColour[] = { CRGB(255, 255, 255) };
cSprite Playfield, CompletedLines, CurrentBlock;
cLEDSprites Sprites(&ledsTetris);

unsigned char AttractMsg[144], GameOverMsg[88];
char BlankMsg[32];
cLEDText TetrisMsg;

uint8_t DropDelay;
boolean AttractMode, NextBlock;
int16_t TotalLines;
unsigned int HighScore = 0, LastScore;

uint16_t PlasmaTime, PlasmaShift;
uint32_t LoopDelayMS, LastLoop;

//Termina Codigo para tetris

// Para el RFID
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear objeto MFRC522

// Código del "MAIN"
bool cardPresent = false;  // Estado de la tarjeta (si está presente o no)
bool lastCardPresent = false; // Estado previo de la tarjeta

BluetoothSerial SerialBT;



// Colores de texto en un ciclo
const uint16_t colors[] = {
  matrix->Color(255, 87, 51), // Naranja
  matrix->Color(0, 128, 128), // Teal
  matrix->Color(255, 20, 147), // Rosado
  matrix->Color(165, 42, 42)  // Marrón
}; 

bool bluetoothInterrupt = false;
int amountColours = 4; // Número de colores en el ciclo
int x = WIDTH; // Posición inicial del texto
int pass = 0;  // Control para el ciclo de colores
bool firstCardPresent = false;
unsigned long previousMillis = 0;    // Variable para almacenar el tiempo anterior
const long RFIDinterval = 1000;          // Intervalo de 1000 ms (1 segundo)

int SensorMapping[100] = {
  1, 20, 21, 31, 41, 51, 61, 71, 81, 91, 
  2, 19, 22, 32, 42, 52, 62, 72, 82, 92, 
  3, 18, 23, 33, 43, 53, 63, 73, 83, 93, 
  4, 17, 24, 34, 44, 54, 64, 74, 84, 94, 
  5, 16, 25, 35, 45, 55, 65, 75, 85, 95, 
  6, 15, 26, 36, 46, 56, 66, 76, 86, 96, 
  7, 14, 27, 37, 47, 57, 67, 77, 87, 97, 
  8, 13, 28, 38, 48, 58, 68, 78, 88, 98, 
  9, 12, 29, 39, 49, 59, 69, 79, 89, 99, 
  10, 11, 30, 40, 50, 60, 70, 80, 90, 100
};

int sensorState[100];

void setup() {
//Codigo set Multiplexores
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  // Configurar los pines de señal de los multiplexores como entrada
  for (int i = 0; i < 7; i++) {
    pinMode(muxSIG[i], INPUT);
  }

    //Set up Bluetooth
    Serial.begin(115200);
    SPI.begin();  // Iniciar SPI sin especificar pines
    mfrc522.PCD_Init();  // Iniciar MFRC522
    SerialBT.begin("TableTop_BT");
    Serial.println("The device is ready to pair!");
    // Cambiado WS2812B a WS2811 para tu tira LED específica
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS); // Configuración específica para WS2811
    matrix->begin(); //Sets up matrix
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);
    matrix->setTextColor(colors[pass]); // Inicializa con el primer color


    //Tetris SETUP
    //Serial.begin(115200);
    //SerialBT.begin("ESP32Tetris");
    
    //FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(ledsTetris[0], ledsTetris.Size());
    //FastLED.setBrightness(200);
    //FastLED.clear(true);
    //FastLED.show();

    memset(PlayfieldData, 0, sizeof(PlayfieldData));
    memset(PlayfieldMask, 0, sizeof(PlayfieldMask));
    Playfield.Setup(ledsTetris.Width(), ledsTetris.Height(), PlayfieldData, 1, _3BIT, TetrisColours, PlayfieldMask);
    Playfield.SetPositionFrameMotionOptions(0, 0, 0, 0, 0, 0, 0, 0, 0);
    Sprites.AddSprite(&Playfield);

    memset(CompletedLinesData, 0, sizeof(CompletedLinesData));
    CompletedLines.Setup(ledsTetris.Width(), TETRIS_SPR_HEIGHT, CompletedLinesData, 1, _1BIT, CompletedLinesColour, CompletedLinesData);
    CompletedLines.SetPositionFrameMotionOptions(0, 0, 0, 0, 0, 0, 0, 0, 0);

    TetrisMsg.SetFont(MatriseFontData);
    sprintf((char *)BlankMsg, "%.*s", _min(((ledsTetris.Height() + TetrisMsg.FontHeight()) / (TetrisMsg.FontHeight() + 1)), (int)sizeof(BlankMsg) - 1), "                              ");
    sprintf((char *)AttractMsg, "%sTETRIS%sSCORE %u%sHIGH %u%sANY BUTTON TO START%s", BlankMsg, BlankMsg, LastScore, BlankMsg, (int)HighScore, BlankMsg, BlankMsg);
    TetrisMsg.Init(&ledsTetris, TetrisMsg.FontWidth() + 1, ledsTetris.Height(), (ledsTetris.Width() - TetrisMsg.FontWidth()) / 2, 0);
    TetrisMsg.SetBackgroundMode(BACKGND_LEAVE);
    TetrisMsg.SetScrollDirection(SCROLL_UP);
    TetrisMsg.SetTextDirection(CHAR_UP);
    TetrisMsg.SetFrameRate(1);
    TetrisMsg.SetOptionsChangeMode(INSTANT_OPTIONS_MODE);
    TetrisMsg.SetText(AttractMsg, strlen((const char *)AttractMsg));
    AttractMode = true;
    LoopDelayMS = TARGET_FRAME_TIME;
    LastLoop = millis() - LoopDelayMS;
    PlasmaShift = (random8(0, 5) * 32) + 64;
    PlasmaTime = 0;


    //En of Tetris SETUP



    FastLED.clear();
}

void loop() {
  //doPlasma(); 
  doSpell("TableTop", -55);
  if (SerialBT.available()) {    // Check if data is available on Bluetooth
    String receivedData = "";    // Variable to hold the received data

    while (SerialBT.available()) {
      receivedData += (char)SerialBT.read();  // Read data byte by byte
      delay(20); // Delay to allow more data to be read if coming in a stream
      
    }

    Serial.println("Received via Bluetooth: " + receivedData); // Print received data to serial port

    // Call the appropriate function based on receivedData
    selectFunction(receivedData);
    //retona a la vista de TableTop
        while (true) {
      if (checkForBluetoothInterrupt()) { // Verifica si hay interrupción
        break; // Sal del bucle si hay datos disponibles en Bluetooth
      }
      doSpell("TableTop", -55);
    }
  }

  cardPresent = mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();

    // Obtener el tiempo actual
  unsigned long currentMillis = millis();

  if (cardPresent && !lastCardPresent) {
    if (!firstCardPresent) {
      // Si es la primera vez que se coloca la tarjeta
      Serial.println("Card Present"); 
      selectFunction("cardPresent");
      firstCardPresent = true;
    } else {
      // Si es la segunda vez que se coloca la tarjeta
      Serial.println("Card absent");
      selectFunction("cardAbsent");
      firstCardPresent = false;
    }
  }

  if (currentMillis - previousMillis >= RFIDinterval) {
    previousMillis = currentMillis; // Actualizar el tiempo anterior
    lastCardPresent = cardPresent;  // Actualizar el estado previo
    mfrc522.PICC_HaltA();
  }
}

void selectFunction(String data) {
  if (data == "i") {
    while (true) {
      if (checkForBluetoothInterrupt()) { // Verifica si hay interrupción
        break; // Sal del bucle si hay datos disponibles en Bluetooth
      }
      doSpell("TableTop", -55);
    }
    
  } else if (data == "p") {
    while (true) {
      if (checkForBluetoothInterrupt()) { // Verifica si hay interrupción
        break; // Sal del bucle si hay datos disponibles en Bluetooth
      }
      doPlasma(); // Ejecuta la función
    }
    } else if (data == "m") { // Nueva opción para leer sensores y controlar LEDs
    while (true) {
      if (checkForBluetoothInterrupt()) { // Verifica si hay interrupción
        break; // Sal del bucle si hay datos disponibles en Bluetooth
      }

      // Leer el estado de los sensores
      leerSensores();

      // Controlar los LEDs según el estado de los sensores
      controlarLEDs();

      // Mantener el estado de los LEDs durante 1 segundo
      delay(100);
    }
  } else if (data == "l") {
    while (true) {
      if (checkForBluetoothInterrupt()) { // Verifica si hay interrupción
        break; // Sal del bucle si hay datos disponibles en Bluetooth
      }
      doLines(); // Ejecuta la función
    }
  } else if (data == "cardPresent") {
    // Ejecuta secuencia de caras cuando la tarjeta está presente
    draw_face1();
    delay(1000);
    text_1();
    delay(1000);

    draw_face2();
    delay(1000);
    text_2();
    delay(1000);

    draw_face3();
    delay(1000);
    text_3();
    delay(1000);

    draw_face4();
    delay(1000);
    text_4();
    delay(1000);
  } else if (data == "cardAbsent") {
    // Ejecuta la animación de despedida cuando la tarjeta no está presente
    draw_sadface1();
    delay(1000);
    draw_sadface2();
    delay(1000); 
    draw_sadface3();
    delay(1000);
    draw_sadface4();
    delay(1000);
    FastLED.clear();
  } else if (data == "t") { //tetr
    bool Gamestatus = true;
      FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(ledsTetris[0], ledsTetris.Size());
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.clear(true);
      FastLED.show();
    while (true) {

      Gamestatus = processGameLogic(); // Usa processGameLogic() para determinar el estado del bucle
      if (!Gamestatus) {
        break; // Sal del bucle si processGameLogic() devuelve false
      }
    }
  } else {
    Serial.println("Invalid option received.");
  }
}

void doPlasma() {
    Plasma plasma(leds, WIDTH, HEIGHT);
    plasma.start();
    FastLED.clear(); // Limpia la pantalla después de la animación
}


void doLines() {
    Lines lines(leds, WIDTH, HEIGHT);
    lines.start();
    FastLED.clear(); // Limpia la pantalla después de la animación
}

//doPlasma2 is modified from LDIRKO's Pastbin code found at this link: https://pastebin.com/6xT72A46

void doPlasma2(){
  int plasmaBrightness = 240; //The brightness is lower for doPlasma2. Change the added amount to BRIGHTNESS to your desire.
  int plasmaSpeed = 7; //Speed that the plasma changes colours, larger is slower  
  for (uint16_t time = 0, cycles = 0; cycles < 6521; time += 128, cycles++) { //Cycle is amount of time the animations runs. This runs for ~60 seconds
    uint16_t ms = millis();
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        uint8_t index = inoise8(i * 41, j * 41, ms / plasmaSpeed);  // x and y not change, only change z value with time increment for nice plasma looking noise original 4
        leds[XYNumberFind(i, j)] = CHSV((index + ms / 200) % 255, 255, plasmaBrightness); // within palette
      }
    }
    FastLED.delay(1);
  }
  FastLED.clear(); //clears matrix for next animation
}

uint8_t XYNumberFind(uint8_t x, uint8_t y) { return (y * WIDTH + x);}    //Function to find LED coordinates in LED matrix, 

//Next Part is for the multiple animations that are meshed together
//It is a modified version of the FASTLED example library, "DemoReal100"

// Forward declaration for addGlitter to ensure it's recognized before being used
void addGlitter(fract8 chanceOfGlitter);

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {rainbow, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void doMultipleAnimations(){
  gCurrentPatternNumber = 0; // resets the parttern number to 0 every time doMultipleAnimations is called
  bool animationsFinished = false;
  int amountAnimations = 0;
  while(animationsFinished == false){
    gPatterns[gCurrentPatternNumber]();
    // send the 'leds' array out to the actual LED strip
    FastLED.show();  
    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND); 
    // do some periodic updates
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // cycles the base color through the rainbow
    EVERY_N_SECONDS( 25 ){ // changes animation every n seconds
      nextPattern(); 
      amountAnimations++;
    } 
    if(amountAnimations == 7){
      animationsFinished = true;
    }
  }
  FastLED.clear(); //clears matrix for next animation
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter(fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

// Función para imprimir frases en la matriz
void doSpell(const char* phrase, int endPosition) {
  bool finishedSpelling = false;
  unsigned long previousMillis = 0;
  const long interval = 60; // Intervalo en milisegundos para el desplazamiento

  while (!finishedSpelling) {
    // Check for Bluetooth interrupt
    if (checkForBluetoothInterrupt()) {
      return;  // Exit the function if an interrupt is detected
    }

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      matrix->fillScreen(0); // Limpia la pantalla
      matrix->setCursor(x, 1); // Establece la posición del texto
      matrix->print(phrase); // Imprime la frase

      if (--x < endPosition) {
        // Cuando el texto sale completamente de la pantalla
        x = matrix->width(); // Reinicia la posición del texto
        if (++pass >= amountColours) pass = 0; // Cambia el color del texto
        matrix->setTextColor(colors[pass]);
        finishedSpelling = true;
      }

      matrix->show(); // Muestra los LEDs
    }
  }
}

//Tetris Game here
bool processGameLogic()
{
  if (abs((long)(millis() - LastLoop)) >= LoopDelayMS)
  {
    LastLoop = millis();
    FastLED.clear();

    // Fill background with dim plasma
    #define PLASMA_X_FACTOR  24
    #define PLASMA_Y_FACTOR  24
    for (int16_t x = 0; x < MATRIX_WIDTH; x++)
    {
      for (int16_t y = 0; y < MATRIX_HEIGHT; y++)
      {
        int16_t r = sin16(PlasmaTime) / 256;
        int16_t h = sin16(x * r * PLASMA_X_FACTOR + PlasmaTime) + cos16(y * (-r) * PLASMA_Y_FACTOR + PlasmaTime) + sin16(y * x * (cos16(-PlasmaTime) / 256) / 2);
        ledsTetris(x, y) = CHSV((uint8_t)((h / 256) + 128), 255, 64);
      }
    }
    uint16_t OldPlasmaTime = PlasmaTime;
    PlasmaTime += PlasmaShift;
    if (OldPlasmaTime > PlasmaTime)
      PlasmaShift = (random8(0, 5) * 32) + 64;

    if (AttractMode)
    {
      if (currentInput != NONE)
      {
        AttractMode = false;
        memset(PlayfieldData, 0, sizeof(PlayfieldData));
        memset(PlayfieldMask, 0, sizeof(PlayfieldMask));
        Sprites.RemoveSprite(&CurrentBlock);
        LastScore = 0;
        TotalLines = 0;
        DropDelay = INITIAL_DROP_FRAMES;
        CurrentBlock.SetXChange(-1);
        NextBlock = true;
        currentInput = NONE;
      }
    }
    else
    {
      if (Sprites.IsSprite(&CompletedLines))  // We have highlighted complete lines, delay for visual effect
      {
        if (CompletedLines.GetXCounter() > 0)
          CompletedLines.SetXCounter(CompletedLines.GetXCounter() - 1);
        else
        {
          Sprites.RemoveSprite(&CompletedLines);
          // Remove completed lines from playfield sprite
          uint8_t *Data = PlayfieldData;
          uint8_t *Mask = PlayfieldMask;
          uint16_t Mbpl = (MATRIX_WIDTH + 7) / 8;
          uint16_t Dbpl = Mbpl * _3BIT;
          int16_t k;
          for (int16_t i = (MATRIX_HEIGHT - 1) * Dbpl, j = (MATRIX_HEIGHT - 1) * Mbpl; i >= 0; i -= Dbpl, j -= Mbpl)
          {
            for (k = 0; k < MATRIX_WIDTH; k += 8)
            {
              if ((uint8_t)(0xff00 >> _min(MATRIX_WIDTH - k, 8)) != Mask[j + (k / 8)])
                break;
            }
            if (k >= MATRIX_WIDTH)
            {
              memmove(&Data[Dbpl], &Data[0], i);
              memset(&Data[0], 0, Dbpl);
              memmove(&Mask[Mbpl], &Mask[0], j);
              memset(&Mask[0], 0, Mbpl);
              i += Dbpl;
              j += Mbpl;
            }
          }
        }
      }
      else
      {
        if (CurrentBlock.GetXChange() >= 0) // We have a current block
        {
          // Check for user input
          if (currentInput == ROTATE)
          {
            currentInput = NONE;
            if ((CurrentBlock.GetCurrentFrame() % 2) == 1)
            {
              if (CurrentBlock.GetXChange() == 0)
                CurrentBlock.m_X = _min(CurrentBlock.m_X, MATRIX_WIDTH - TETRIS_SPR_WIDTH);
              else if ((CurrentBlock.GetXChange() != 3) && (CurrentBlock.GetFlags() & SPRITE_EDGE_X_MAX))
                --CurrentBlock.m_X;
            }
            CurrentBlock.IncreaseFrame();
            Sprites.DetectCollisions(&CurrentBlock);
            if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              CurrentBlock.DecreaseFrame();
          }

          if (currentInput == LEFT && (!(CurrentBlock.GetFlags() & SPRITE_EDGE_X_MIN)))
          {
            currentInput = NONE;
            CurrentBlock.m_X--;
            Sprites.DetectCollisions(&CurrentBlock);
            if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              CurrentBlock.m_X++;
          }

          else if (currentInput == RIGHT && (!(CurrentBlock.GetFlags() & SPRITE_EDGE_X_MAX)))
          {
            currentInput = NONE;
            CurrentBlock.m_X++;
            Sprites.DetectCollisions(&CurrentBlock);
            if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              CurrentBlock.m_X--;
          }

          if (currentInput == DOWN)
          {
            currentInput = NONE;
            CurrentBlock.SetYCounter(1);
          }

          // Do block checks for bottom or collision
          if (CurrentBlock.GetYCounter() <= 1)
          {
            if (CurrentBlock.GetFlags() & SPRITE_EDGE_Y_MIN)
              NextBlock = true;
            else
            {
              --CurrentBlock.m_Y;
              Sprites.DetectCollisions(&CurrentBlock);
              ++CurrentBlock.m_Y;
              if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              {
                // Block has collided check for game over
                int16_t MaxY = MATRIX_HEIGHT - 2;
                if ((CurrentBlock.GetCurrentFrame() % 2) == 1)
                {
                  if (CurrentBlock.GetXChange() == 0)
                    MaxY -= 2;
                  else if (CurrentBlock.GetXChange() != 3)
                    MaxY -= 1;
                }
                else if (CurrentBlock.GetXChange() == 0)
                    ++MaxY;
                if (CurrentBlock.m_Y < MaxY)
                  NextBlock = true;
                else
                {
                  // Game over
                  CurrentBlock.SetYCounter(2);  // Stop last block moving down!
                  AttractMode = true;
                  if (LastScore > HighScore)
                  {
                    HighScore = LastScore;
                    sprintf((char *)GameOverMsg, "%sGAME OVER%sNEW HIGH SCORE %u%s", BlankMsg, BlankMsg, LastScore, BlankMsg);
                  }
                  else
                    sprintf((char *)GameOverMsg, "%sGAME OVER%sSCORE %u%s", BlankMsg, BlankMsg, LastScore, BlankMsg);
                  sprintf((char *)AttractMsg, "%sTETRIS%sSCORE %u%sHIGH %u%sANY BUTTON TO START%s", BlankMsg, BlankMsg, LastScore, BlankMsg, HighScore, BlankMsg, BlankMsg);
                  TetrisMsg.SetText(GameOverMsg, strlen((char *)GameOverMsg));
                  TetrisMsg.SetBackgroundMode(BACKGND_DIMMING, 0x40);
                }
              }
            }
          }
        }
        if (NextBlock)  // Start new block
        {
          if (CurrentBlock.GetXChange() >= 0) // We have a current block so add to playfield before creating new block
          {
            Playfield.Combine(CurrentBlock.m_X, CurrentBlock.m_Y, &CurrentBlock);
            Sprites.RemoveSprite(&CurrentBlock);
            // Make completed lines highlight sprite & score
            memset(CompletedLinesData, 0, sizeof(CompletedLinesData));
            CompletedLines.m_Y = -1;
            uint8_t *Mask = PlayfieldMask;
            uint16_t Mbpl = (MATRIX_WIDTH + 7) / 8;
            int16_t j, numlines = 0;
            for (int16_t i = (MATRIX_HEIGHT - 1) * Mbpl, y = 0; i >= 0; i -= Mbpl, ++y)
            {
              for (j = 0; j < MATRIX_WIDTH; j += 8)
              {
                if ((uint8_t)(0xff00 >> _min(MATRIX_WIDTH - j, 8)) != Mask[i + (j / 8)])
                  break;
              }
              if (j >= MATRIX_WIDTH)
              {
                if (CompletedLines.m_Y == -1)
                  CompletedLines.m_Y = y;
                memset(&CompletedLinesData[((TETRIS_SPR_HEIGHT - 1) - (y - CompletedLines.m_Y)) * Mbpl], 0xff, Mbpl);
                numlines++;
              }
            }
            if (numlines > 0)
            {
              CompletedLines.SetXCounter(15);  // Set delay for highlight display to 15 loops
              Sprites.AddSprite(&CompletedLines);
            }
            LastScore += 1;
            if (numlines == 1)
              LastScore += 4;
            else if (numlines == 2)
              LastScore += 12;
            else if (numlines == 3)
              LastScore += 20;
            else if (numlines == 4)
              LastScore += 40;
            TotalLines += numlines;
            DropDelay = _max(1, INITIAL_DROP_FRAMES - (TotalLines / 5));
          }
          // Start new block
          uint8_t j = random8(sizeof(TetrisSprData) / sizeof(TetrisSprData[0]));
          CurrentBlock.Setup(TETRIS_SPR_WIDTH, TETRIS_SPR_WIDTH, TetrisSprData[j], 4, _3BIT, TetrisColours, TetrisSprMask[j]);
          CurrentBlock.SetPositionFrameMotionOptions((MATRIX_WIDTH / 2) - 1, MATRIX_HEIGHT, 0, 0, 0, 0, -1, DropDelay, SPRITE_DETECT_COLLISION | SPRITE_DETECT_EDGE);
          CurrentBlock.SetXChange(j);
          Sprites.AddSprite(&CurrentBlock);
          NextBlock = false;
        }
        Sprites.UpdateSprites();
      }
    }
    Sprites.RenderSprites();
    if (AttractMode)
    {
      if (TetrisMsg.UpdateText() == -1)
      {
        TetrisMsg.SetText(AttractMsg, strlen((char *)AttractMsg));
        TetrisMsg.SetBackgroundMode(BACKGND_LEAVE);
        Sprites.RemoveSprite(&CurrentBlock);
        memset(PlayfieldData, 0, sizeof(PlayfieldData));
        memset(PlayfieldMask, 0, sizeof(PlayfieldMask));
      }
    }
    FastLED.show();
  }
  if (SerialBT.available())
  {
    char keyPress = (char)SerialBT.read();
    switch (keyPress)
    {
      case 'w':
        currentInput = ROTATE;
        break;
      case 'a':
        currentInput = LEFT;
        break;
      case 's':
        currentInput = DOWN;
        break;
      case 'd':
        currentInput = RIGHT;
        break;
      case 'x': //Exit Game
        FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS); // Configuración específica para WS2811
        matrix->begin(); //Sets up matrix
        matrix->setTextWrap(false);
        matrix->setBrightness(BRIGHTNESS);
        matrix->setTextColor(colors[pass]); // Inicializa con el primer color
        return false;
        break;
    }
    Serial.println(currentInput);
  }
  return true;
}

//End of Tetris Game

void controlarLEDs() {
  for (int i = 0; i < 100; i++) {
    int sensorPos = SensorMapping[i] - 1; // Restar 1 para convertir la posición del sensor a índice de array
    if (sensorState[sensorPos] == HIGH) {
      leds[i] = CRGB(0, 0, 0); // Encender el LED en blanco si el sensor está activo
    } else {
      leds[i] = CRGB(200, 200, 200); // Apagar el LED si el sensor está inactivo
    }
  }
  
  FastLED.show(); // Actualizar los LEDs para reflejar los cambios
}

void leerSensores() {
  // Iterar sobre todos los sensores
  for (int i = 0; i < 100; i++) {
    int muxIndex = i / 16; // Determina qué multiplexor usar
    int sensorIndex = i % 16; // Determina qué salida del multiplexor leer

    // Configurar los pines de selección para elegir la salida del multiplexor
    digitalWrite(muxS0, bitRead(sensorIndex, 0));
    digitalWrite(muxS1, bitRead(sensorIndex, 1));
    digitalWrite(muxS2, bitRead(sensorIndex, 2));
    digitalWrite(muxS3, bitRead(sensorIndex, 3));

    // Leer el estado del sensor desde el pin de señal del multiplexor correspondiente
    sensorState[i] = digitalRead(muxSIG[muxIndex]);
  }
}

void draw_face1() { 
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(255, 255, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(255, 255, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(255, 255, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void draw_face2() { // Carita para la derecha
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(255, 255, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(255, 255, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(255, 255, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(255, 255, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}
void draw_face3() { //Carita al revés
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(255, 255, 0);
  leds[25] = CRGB(255, 255, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(255, 255, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(255, 255, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void draw_face4() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(255, 255, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(255, 255, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(255, 255, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

// Para los hi
void text_1() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(255, 255, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(255, 255, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}
void text_2(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(255, 255, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(255, 255, 0);
  leds[43] = CRGB(255, 255, 0);
  leds[44] = CRGB(255, 255, 0);
  leds[45] = CRGB(255, 255, 0);
  leds[46] = CRGB(255, 255, 0);
  leds[47] = CRGB(255, 255, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void text_3(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(255, 255, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(255, 255, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(255, 255, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(255, 255, 0);
  leds[45] = CRGB(255, 255, 0);
  leds[46] = CRGB(255, 255, 0);
  leds[47] = CRGB(255, 255, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(255, 255, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void text_4(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(255, 255, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(255, 255, 0);
  leds[25] = CRGB(255, 255, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(255, 255, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void draw_sadface1(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(255, 255, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(255, 255, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(255, 255, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(255, 255, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(255, 255, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}
void draw_sadface2(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(255, 255, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(255, 255, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(255, 255, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void draw_sadface3(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(255, 255, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(255, 255, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}

void draw_sadface4(){
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(255, 255, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(255, 255, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(255, 255, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(255, 255, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
}


