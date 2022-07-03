#define A 5
#define B 6
#define X1 7
#define X2 8
#define Y A0

String inputString = "";
bool stringComplete = false;

unsigned long last_time = 0;
String state = "0000\n";
String ystate = "";

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(X1, OUTPUT);
  pinMode(X2, OUTPUT);
  pinMode(Y, INPUT);

  Serial.begin(9600);
  Serial.println("inputs| output");
  Serial.println("ABXX  | Y ");
  Serial.println("  12  |   ");
  Serial.println("------|---");
}

void loop() {
  if (stringComplete) {
    state = inputString;
    if (inputString[0] == '1') {
      digitalWrite(A, HIGH);
    } else {
      digitalWrite(A, LOW);
    }
    if (inputString[1] == '1') {
      digitalWrite(B, HIGH);
    } else {
      digitalWrite(B, LOW);
    }
    if (inputString[2] == '1') {
      digitalWrite(X1, HIGH);
    } else {
      digitalWrite(X1, LOW);
    }
    if (inputString[3] == '1') {
      digitalWrite(X2, HIGH);
    } else {
      digitalWrite(X2, LOW);
    }

    // reset input string
    inputString = "";
    stringComplete = false;
  }

  if (millis() >= last_time + 1000) {
    if(analogRead(Y) > 500) {
      ystate = "HIGH";
    } else {
      ystate = "LOW";
    }
    Serial.print(state.substring(0,4));
    Serial.print("  | ");
    Serial.println(ystate);
    last_time = millis();
  }
//  Serial.println(last_time);
}

void serialEvent() {
  while(Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
