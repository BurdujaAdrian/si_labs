// Minimal Timer1 Interrupt Test for Arduino (ATmega328P)
#define LED_PIN 13 // Use the built-in LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Disable interrupts during setup
  cli();

  // Reset Timer1 registers to a known state
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Set compare match register for a 1 Hz interrupt (16MHz/64/25000 = 10Hz, use 25000 for 0.5Hz? Let's use 15624 for 1Hz)
  // Formula: OCR1A = (16,000,000 / (prescaler * desired freq)) - 1
  // For 1 Hz: (16e6 / (256 * 1)) - 1 = 62499 (too high for 16-bit)
  // For 2 Hz with /256: (16e6 / (256 * 2)) - 1 = 31249
  // For 1 Hz with /1024: (16e6 / (1024 * 1)) - 1 = 15624
  OCR1A = 15624; // Interrupt roughly once per second

  // Turn on CTC mode (WGM12 = 1)
  TCCR1B |= (1 << WGM12);

  // Set prescaler to 1024 (CS12 = 1, CS10 = 1)
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Re-enable global interrupts
  sei();
}

// The ISR - toggles the LED
ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void loop() {
  // Absolutely nothing here. The LED should toggle by itself.
}