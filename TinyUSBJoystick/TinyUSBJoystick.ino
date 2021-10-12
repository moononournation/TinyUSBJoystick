//DigiJoystick test and usage documentation
#define XPIN A0
#define YPIN A1
#define AVG_READ 100
#define ANALOG_MAX 1023

#include "DigiJoystick.h"
long x_centre;
long y_centre;

long avg_reading(uint8_t pin) {
  long t = 0;
  for (int i = 0; i < AVG_READ; i++) {
    delay(10);
    t += analogRead(pin);
  }
  return t / AVG_READ;
}

byte map_reading(long v, long v_centre, long out_from, long out_centre, long out_to) {
  if (v == v_centre) {
    return out_centre;
  } else if (v < v_centre) {
    return map(v, 0, v_centre, out_from, out_centre);
  } else { // v > v_centre
    return map(v, v_centre, ANALOG_MAX, out_centre, out_to);
  }
}

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(0, INPUT_PULLUP);
  x_centre = avg_reading(XPIN);
  y_centre = avg_reading(YPIN);
}


void loop() {
  // If not using plentiful DigiJoystick.delay() calls, make sure to
  //DigiJoystick.update(); // call this at least every 50ms
  // calling more often than that is fine
  // this will actually only send the data every once in a while unless the data is different

  // you can set the values from a raw byte array with:
  // char myBuf[8] = {
  //   x, y, xrot, yrot, zrot, slider,
  //   buttonLowByte, buttonHighByte
  // };
  // DigiJoystick.setValues(myBuf);

  // Or we can also set values like this:
  DigiJoystick.setX(map_reading(analogRead(XPIN), x_centre, 0, 128, 255));
  DigiJoystick.setY(map_reading(analogRead(YPIN), y_centre, 255, 128, 0));
  DigiJoystick.setButtons((char)(digitalRead(0) ? 0x00 : 0x01), 0x00);
  //  DigiJoystick.setX((byte) (millis() / 100)); // scroll X left to right repeatedly
  //  DigiJoystick.setY((byte) 0x30);
  //  DigiJoystick.setXROT((byte) 0x60);
  //  DigiJoystick.setYROT((byte) 0x90);
  //  DigiJoystick.setZROT((byte) 0xB0);
  //  DigiJoystick.setSLIDER((byte) 0xF0);

  // it's best to use DigiJoystick.delay() because it knows how to talk to
  // the connected computer - otherwise the USB link can crash with the
  // regular arduino delay() function
  DigiJoystick.delay(50); // wait 50 milliseconds

  // we can also set buttons like this (lowByte, highByte)
  //DigiJoystick.setButtons(0x00, 0x00);
}