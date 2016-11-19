
// pushbutton pin
#define PB_PIN 2

#define LOWEST_LED 8
#define HIGHEST_LED 11

#define LOWER_LEFT_LED 8
#define UPPER_LEFT_LED 9
#define UPPER_RIGHT_LED 10
#define LOWER_RIGHT_LED 11 

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PB_PIN, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOWER_LEFT_LED, OUTPUT);
  pinMode(UPPER_LEFT_LED, OUTPUT);
  pinMode(UPPER_RIGHT_LED, OUTPUT);
  pinMode(LOWER_RIGHT_LED, OUTPUT);
}


void all_on() {
  int led;

    for (led = LOWEST_LED; led <= HIGHEST_LED; led++) {
      digitalWrite (led, HIGH);
    }
}

void all_off() {
  int led;
  
    for (led = LOWEST_LED; led <= HIGHEST_LED; led++) {
      digitalWrite (led, LOW);
    }
}

void switch_test() {
  if (digitalRead (PB_PIN) == LOW) {
    all_on ();
  } else {
    all_off ();
  }
}

void test_pattern() {
    int led;

    for (led = LOWEST_LED; led <= HIGHEST_LED; led++) {
      digitalWrite (led, HIGH);
      delay(250);
      digitalWrite (led, LOW);
    }
}

void blink_all_at_once () {
  int led;

  all_on();
  delay(250);
  all_off();
  delay(250);
}

// the loop function runs over and over again forever
void loop() {
  switch_test();

  // test_pattern();
  // blink_all_at_once();
}
