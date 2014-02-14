#define latchPin 9
#define clockPin 8
#define dataPin 10

// Start in a diagonal
byte ledData[] = {B1000, B0100, B0010, B0001};
long serialData;
byte serialRow;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  serialRow = 0;
}

void loop() {
  getSerial();
  for (byte row = 0; row < 4; row++) {
    byte dataToSend = (1 << (row+4)) | (15 & ~ledData[row]);
    // setlatch pin low so the LEDs don't change while sending in bits
    digitalWrite(latchPin, LOW);
    // shift out the bits of dataToSend to the 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, dataToSend);
    //set latch pin high- this sends data to outputs so the LEDs will light up
    digitalWrite(latchPin, HIGH);
  }
}

void getSerial() {
  byte serialIn = 0;
  if(Serial.available() > 0) {
    serialIn = Serial.read();
    switch(serialIn) {
      case 13: // Enter
        Serial.print("Setting row ");
        Serial.print(serialRow);
        Serial.print(" to ");
        Serial.println(serialData, BIN);
        ledData[serialRow] = serialData;
        serialData = 0;
        break;
      case 44: // Comma
        Serial.print("Setting row to ");
        Serial.println(serialData);
        if(serialData < 4) {
          serialRow = serialData;
        }
        serialData = 0;
        break;
      default:
        serialIn -= 48;
        serialData = (serialData << 1) + serialIn;
    }
  }
}

void turnOn(int row, int col) {
  ledData[row] = ledData[row] | (1 << col);
}

void turnOff(int row, int col) {
  ledData[row] = ledData[row] & ~(1 << col);
}
