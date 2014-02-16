#define latchPin 9
#define clockPin 8
#define dataPin 10

#define rowMax 4
#define rowMin 1
#define stateMax 15

// Start entire board off
int ledData[] = {0, 0, 0, 0};
boolean rowSet = false;
byte serialRow;
unsigned long serialData;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Go board, Go!");
}

void loop()
{
  getSerial();
  for(byte row = 0; row < 4; row++)
  {
    byte dataToSend = (1 << (row+4)) | (15 & ~ledData[row]);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, dataToSend);
    digitalWrite(latchPin, HIGH);
  }
}

void getSerial()
{
  byte serialIn = 0;
  if(Serial.available() > 0)
  {
    serialIn = Serial.read();
    if(serialIn == 13) // Enter
    {
      processCommand();
    }
    else if(serialIn >= 48 && serialIn <= 57) // 0-9
    {
      serialIn -= 48;
      serialData = (serialData * 10) + serialIn;
    }
    else
    {
      Serial.println("Unrecognized input.");
    }
  }
}

void processCommand()
{
  if(!rowSet)
  {
    if(serialData > rowMax || serialData < rowMin)
    {
      Serial.println("Row out of bounds!");
      Serial.println("Send new row between " + String(rowMin) + "-" + String(rowMax));
    }
    else
    {
      serialRow = serialData;
      rowSet = true;
      Serial.println("Row " + String(serialRow) + " selected");
    }
  }
  else
  {
    if(serialData > stateMax)
    {
      Serial.println("State out of bounds!");
      Serial.println("Send new state between 0-" + String(stateMax));
    }
    else
    {
      ledData[serialRow] = serialData;
      rowSet = false;
      Serial.println("Set state to {" + String(ledData[serialRow]) + "}");
    }
  }
  serialData = 0;
}
