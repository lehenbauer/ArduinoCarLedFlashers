
// pushbutton pin
#define PB_PIN 12

#define LOWEST_LED 8
#define HIGHEST_LED 11

#define LOWER_LEFT_LED 8
#define UPPER_LEFT_LED 9
#define UPPER_RIGHT_LED 10
#define LOWER_RIGHT_LED 11

#define STATUS_LED LED_BUILTIN
#define DIAGNOSTIC_LED 13

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
  // configure pushbutton for input with internal pullup
  // switch will be open or shorted, so with the pullup we will
  // see state of 1 when open, 0 when pressed
  pinMode(PB_PIN, INPUT_PULLUP);

  // configure for output all DIO pins driving LEDs
  pinMode(DIAGNOSTIC_LED, OUTPUT);
  pinMode(LOWER_LEFT_LED, OUTPUT);
  pinMode(UPPER_LEFT_LED, OUTPUT);
  pinMode(UPPER_RIGHT_LED, OUTPUT);
  pinMode(LOWER_RIGHT_LED, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
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

void set_left_bottom(int state) {
	digitalWrite (LOWER_LEFT_LED, state);
}

void set_right_bottom(int state) {
	digitalWrite (LOWER_RIGHT_LED, state);
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
	int j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			if (pushbutton_peek()) return;
			func1(ON);
			func2(OFF);
			set_status(ON);
			delay(50);
			if (pushbutton_peek()) return;
			func1(OFF);
			func2(OFF);
			set_status(OFF);
			delay(50);
			if (pushbutton_peek()) return;
		}
		delay(50);
		if (pushbutton_peek()) return;

		for (j = 0; j < 3; j++) {
			if (pushbutton_peek()) return;
			func1(OFF);
			func2(ON);
			set_status(ON);
			delay(50);
			if (pushbutton_peek()) return;
			func1(OFF);
			func2(OFF);
			set_status(OFF);
			delay(50);
			if (pushbutton_peek()) return;
		}
		delay(50);
		if (pushbutton_peek()) return;
	}
}

void slow_flash (void (*func1)(int), void(*func2)(int)) {
	int i;

	for (i = 0; i < 4; i++) {
		if (pushbutton_peek()) return;
		func1(ON);
		func2(OFF);
		set_status(ON);
		delay(250);
		if (pushbutton_peek()) return;
		func1(OFF);
		func2(ON);
		set_status(OFF);
		delay(250);
	}
}

void all_flash () {
	int i;

	quick_flash (set_diagonal1, set_diagonal2);
	if (pushbutton_peek()) return;
	slow_flash(set_diagonal1, set_diagonal2);
}
		
void top_on_bottom_flash () {
	int i;

	set_upper(ON);

	quick_flash (set_left_bottom, set_right_bottom);
	if (pushbutton_peek()) return;
}
		
		
int pushbutton_peek () {
	if (digitalRead (PB_PIN) == LOW) {
		if (pbState == UP) {
			return 1;
		}
		return 0;
	} else {
		if (pbState == DOWN) {
			pbState = UP;
		}
	}
}

int pushbutton_pressed () {
	// pin is low when button is pressed.
	// when it is pressed we will be called
	// many times while it is down so we keep
	// track of its state and only return 1
	// once per time it is pressed
	if (digitalRead (PB_PIN) == LOW) {
      digitalWrite (DIAGNOSTIC_LED, HIGH);
	  delay(50);  // debounce via a breif delay
		if (pbState == UP) {
			pbState = DOWN;
			return 1;
		}
	} else {
      // digitalWrite (DIAGNOSTIC_LED, LOW);
		if (pbState == DOWN) {
			pbState = UP;
		}
	}
	return 0;
}

void set_status (int state) {
	digitalWrite (STATUS_LED, state);
}

void heartbeat () {
	static int heartbeat = 0;

	if (heartbeat++ > 20) {
		digitalWrite (DIAGNOSTIC_LED, HIGH);
		heartbeat = 0;
	} else {
		digitalWrite (DIAGNOSTIC_LED, LOW);
	}
}

void
run_program () {
	heartbeat();
	switch (program) {
		case 0:
			set_all(OFF);
			set_status (OFF);
			delay(50);
			return;

		case 1:
			set_upper(ON);
			set_lower(OFF);
			set_status (ON);
			delay(50);
			return;

		case 2:
			set_upper(OFF);
			set_lower(ON);
			set_status (ON);
			delay(50);
			return;

		case 3:
			set_all(ON);
			digitalWrite (STATUS_LED, ON);
			set_status (ON);
			delay(50);
			return;

		case 4:
			all_flash();
			return;

		case 5:
			top_on_bottom_flash();
			return;

		case 6:
			program = 0;
	}
}

// the loop function runs over and over again forever
void loop() {
	if (pushbutton_pressed()) {
		program++;
	}

	run_program();
}
