#include "InterruptHandler.h"
#include "BluetoothSerial.h"

extern BluetoothSerial SerialBT;

bool checkForBluetoothInterrupt() {
  if (SerialBT.available()) {
    bluetoothInterrupt = true;
    return true;
  }
  return false;
}
