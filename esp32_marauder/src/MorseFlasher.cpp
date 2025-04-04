#include <Arduino.h>

// Created by ChatGPT, and symbols added by Bing Chat, original idea by Nikolai Søndre
static const int LED = 4;
static const int dotDuration = 350;
static const int dashDuration = 3 * dotDuration;
static const int interLetterPause = 2 * dotDuration;
static const int interWordPause = 4 * dotDuration;
static const int bufferSize = 50;  // max length of the input buffer

static char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

//For Numbers
static char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----."
};

static char* symbols[] = {
  ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", // . , ? , etc.
  "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", // ( ), :, etc.
  "-...-", ".-.-.", "--...-", ".-..-.", ".--.-.", // = , + , / , @ , etc.
  "..--.-", "-....-", // _ , -
};

static void dot() {
  Serial.print(".");
  digitalWrite(LED, HIGH);
  delay(dotDuration);
  digitalWrite(LED, LOW);
  delay(dotDuration);
}

static void dash() {
  Serial.print("-");
  digitalWrite(LED, HIGH);
  delay(dashDuration);
  digitalWrite(LED, LOW);
  delay(dotDuration);
}

static void shortspace() {
  delay(interLetterPause);
}

static void space() {
  digitalWrite(LED, LOW);
  delay(interWordPause);
}

static char inputBuffer[bufferSize + 1]; // input buffer
static int bufferIndex = 0;           // current index in the input buffer

void morse_setup() {
  pinMode(LED, OUTPUT);
  //Serial.begin(9600);
}

void morse_loop() {
  if (Serial.available()) {
    bufferIndex = 0;
    Serial.print("Message: ");

    while (Serial.available()) {
      char input = Serial.read();
      Serial.print(input);

      // add the input to the buffer
      inputBuffer[bufferIndex] = tolower(input);
      bufferIndex = (bufferIndex + 1) % bufferSize;
      if (input == 10 || input == 13) {
        inputBuffer[bufferIndex++] = ' ';
        Serial.flush();
        break;
      }
    }
  }

  // repeat the last input forever
  for (int i = 0; i < bufferIndex; i++) {
    if (Serial.available()) {
      Serial.println();
      break;
    }

    char input = inputBuffer[i];
    if (input == ' ' || (input >= 'a' && input <= 'z') || (input >= '0' && input <= '9')) {
      Serial.println();
      Serial.print(input);
      Serial.print(": ");

      const char* pattern;
      if (input >= 'a' && input <= 'z')
        pattern = letters[input - 'a'];
      else if (input >= '0' && input <= '9')
        pattern = numbers[input - '0'];
      else
        pattern = symbols[input - '.' + 6];

      if (pattern) {
        for (int j = 0; pattern[j]; j++) {
          if (pattern[j] == '.') dot();
          else if (pattern[j] == '-') dash();
        }
      } else {
        space();
      }

      shortspace();
    }
  }
}
