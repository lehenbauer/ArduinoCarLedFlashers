
// pushbutton pin
#define PB_PIN 2

#define LOWEST_LED 8
#define HIGHEST_LED 11

#define LOWER_LEFT_LED 8
#define UPPER_LEFT_LED 9
#define UPPER_RIGHT_LED 10
#define LOWER_RIGHT_LED 11 

#define DOWN 0
#define UP 1

#define ON HIGH
#define OFF LOW



int pbState = UP;

int upperSolidOn = 0;
int lowerSolidOn = 0;

int program = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PB_PIN, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOWER_LEFT_LED, OUTPUT);
  pinMode(UPPER_LEFT_LED, OUTPUT);
  pinMode(UPPER_RIGHT_LED, OUTPUT);
  pinMode(LOWER_RIGHT_LED, OUTPUT);
}

void set_all(int state) {
  int led;

    for (led = LOWEST_LED; led <= HIGHEST_LED; led++) {
      digitalWrite (led, state);
    }
}

void set_upper(int state) {
	digitalWrite (UPPER_LEFT_LED, state);
	digitalWrite (UPPER_RIGHT_LED, state);
}

void set_lower(int state) {
	digitalWrite (LOWER_LEFT_LED, state);
	digitalWrite (LOWER_RIGHT_LED, state);
}

void set_left(int state) {
	digitalWrite (LOWER_LEFT_LED, state);
	digitalWrite (UPPER_LEFT_LED, state);
}

void set_right(int state) {
	digitalWrite (LOWER_RIGHT_LED, state);
	digitalWrite (UPPER_RIGHT_LED, state);
}

void set_diagonal1(int state) {
	digitalWrite (UPPER_LEFT_LED, state);
	digitalWrite (LOWER_RIGHT_LED, state);
}

void set_diagonal2(int state) {
	digitalWrite (UPPER_RIGHT_LED, state);
	digitalWrite (LOWER_LEFT_LED, state);
}

void quick_flash (void (*func1)(int), void(*func2)(int)) {
	int i;

	for (i = 0; i < 3; i++) {
		func1(ON);
		func2(OFF);
		delay(50);
		set_all(OFF);
		delay(50);
	}

	for (i = 0; i < 3; i++) {
		func1(OFF);
		func2(ON);
		delay(50);
		set_all(OFF);
		delay(50);
	}
}

void slow_flash (void (*func1)(int), void(*func2)(int)) {
	int i;

	for (i = 0; i < 4; i++) {
		func1(ON);
		func2(OFF);
		delay(250);
		func1(OFF);
		func2(ON);
		delay(250);
	}
}

void all_flash () {
	int i;

	for (i = 0; i < 2; i++) {
		quick_flash (set_diagonal1, set_diagonal2);
	}
	slow_flash(set_diagonal1, set_diagonal2);
}
		


int pushbutton_pressed () {
	// pin is low when button is pressed.
	// when it is pressed we will be called
	// many times while it is down so we keep
	// track of its state and only return 1
	// once per time it is pressed
	if (digitalRead (PB_PIN) == LOW) {
      digitalWrite (LED_BUILTIN, HIGH);
		if (pbState == UP) {
			pbState = DOWN;
			return 1;
		}
	} else {
      digitalWrite (LED_BUILTIN, LOW);
		if (pbState == DOWN) {
			pbState = UP;
		}
	}
	return 0;
}

void
run_program () {
	switch (program) {
		case 0: 
			set_all(OFF);
			return;

		case 1:
			set_upper(ON);
			set_lower(OFF);
			return;

		case 2:
			set_upper(OFF);
			set_lower(ON);
			return;

		case 3:
			set_all(ON);
			return;

		case 4:
			all_flash();
			return;

		case 5:
			program = 0;
	}
}

// the loop function runs over and over again forever
void loop() {
	if (pushbutton_pressed()) {
		program++;
	}

	run_program();

  // switch_test();
  // test_pattern();
  // blink_all_at_once();
}
