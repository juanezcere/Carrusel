#define DO4  262
#define RE4  294
#define MI4  330
#define FA4  349
#define FAS4  370
#define SOL4  392
#define LA4  440
#define LAS4  466
#define SI4  494
#define DO5  523
#define RE5  587

#define LIGHT 13
#define MOTOR 9
#define SPEAK 7
#define PLAY  8

int noteDuration = 500;
int noteDelay = noteDuration + 50;
int staccato = 0;
int shuffle = 0;
int transposedNote;
int transpose = 0;

int notes[54] = {
  DO4, FA4, FA4, SOL4, FA4, MI4, RE4, RE4, RE4, SOL4, SOL4, LA4, SOL4, FA4, MI4, DO4, DO4,
  LA4, LA4, LAS4, LA4, SOL4, FA4, RE4, DO4, DO4, RE4, SOL4, MI4, FA4, DO4, FA4, FA4, FA4,
  MI4, MI4, FA4, MI4, RE4, DO4, SOL4, LA4, SOL4, SOL4, FA4, FA4, DO5, DO4, DO4, DO4,
  RE4, SOL4, MI4, FA4
};

int durations[54] = {
  2, 2, 3, 3, 3, 3, 2, 2, 2, 2, 3, 3, 3, 3, 2, 2, 2,
  2, 3, 3, 3, 3, 2, 2, 3, 3, 2, 2, 2, 1, 2, 2, 2, 2,
  1, 2, 2, 2, 2, 1, 2, 2, 3, 3, 3, 3, 2, 2, 3, 3,
  2, 2, 2, 1
};

void setup() {
  pinMode(LIGHT, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(SPEAK, OUTPUT);
  digitalWrite(MOTOR, HIGH);
  pinMode(PLAY, INPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() {
  if (!digitalRead(PLAY)) {
    digitalWrite(LIGHT, HIGH);
    digitalWrite(MOTOR, LOW);
    transpose = 5;
    noteDuration = 700;
    for (int i = 0; i < sizeof(notes) / sizeof(int); i++) {
      transposedNote = notes[i] + (notes[i] * transpose);
      Serial.println(transposedNote);
      noteDelay = (noteDuration / durations[i]) + staccato;
      tone(SPEAK, transposedNote, (noteDuration / durations[i]) - staccato);
      delay(noteDelay);
      noTone(SPEAK);
      digitalWrite(LIGHT, !digitalRead(LIGHT));
    }
    digitalWrite(MOTOR, HIGH);
    digitalWrite(LIGHT, LOW);
    delay(noteDelay * 2);
  }
  delay(500);
}
