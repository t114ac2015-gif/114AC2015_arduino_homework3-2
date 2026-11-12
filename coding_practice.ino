
const int ledPin = 3;
const int buttonPin = 2;

// LED 模式
int ledMode = 0;

// 按鈕狀態
int buttonState = LOW;
int lastButtonReading = LOW;

// 防彈跳
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// LED 閃爍計時
unsigned long previousMillis = 0;
bool ledState = HIGH;

// 閃爍速度
const unsigned long slowInterval = 1000;
const unsigned long mediumInterval = 500;
const unsigned long fastInterval = 200;

void setup() {
  pinMode(ledPin, OUTPUT);

  // 按鈕使用外部模組的 VCC
  pinMode(buttonPin, INPUT);

  // 初始狀態：LED 恆亮
  digitalWrite(ledPin, HIGH);
}

void loop() {

  // ===== 按鈕讀取 =====

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      // 偵測按下按鈕
      if (buttonState == HIGH) {

        ledMode++;

        // 第4次按下回到恆亮
        if (ledMode > 3) {
          ledMode = 0;
        }

        // 重設閃爍計時
        previousMillis = millis();

        // 切換模式時先亮燈
        ledState = HIGH;
        digitalWrite(ledPin, HIGH);
      }
    }
  }

  lastButtonReading = reading;


  // ===== LED 模式控制 =====

  // 模式0：恆亮
  if (ledMode == 0) {
    digitalWrite(ledPin, HIGH);
  }

  // 模式1、2、3：不同速度閃爍
  else {

    unsigned long interval;

    if (ledMode == 1) {
      interval = slowInterval;
    }
    else if (ledMode == 2) {
      interval = mediumInterval;
    }
    else {
      interval = fastInterval;
    }

    // 判斷是否達到閃爍時間
    if (millis() - previousMillis >= interval) {

      previousMillis = millis();

      ledState = !ledState;

      digitalWrite(ledPin, ledState);
    }
  }
}
