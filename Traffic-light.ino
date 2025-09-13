#define RED 12
#define YELLOW 8
#define GREEN 2
#define BUTTON 4

// State definitions for the traffic light
const int state_red = 0;
const int state_yellow = 1;
const int state_green = 2;

int curr_state;                // Current state of the traffic light
unsigned long start_time;      // Time marker for state changes

volatile unsigned long myMillis = 0;  // Custom millis counter (incremented by Timer1 ISR)

// Timer1 Compare Match A interrupt service routine (fires every 1ms)
ISR(TIMER1_COMPA_vect) {
  myMillis++;   // Increment custom millis counter
}

// Configure Timer1 to generate 1ms interrupts
void setupTimer1() {
  TCCR1A = 0;                // Normal mode (no PWM)
  TCCR1B = (1 << WGM12);     // CTC (Clear Timer on Compare Match) mode
  OCR1A = 250;               // Compare value for 1ms (with prescaler 64 on 16MHz clock)
  TIMSK1 |= (1 << OCIE1A);   // Enable Compare Match A interrupt
  TCCR1B |= (1 << CS11) | (1 << CS10); // Start timer with prescaler 64
}

// Initial setup
void setup() {
  setupTimer1();   // Start Timer1
  sei();           // Enable global interrupts

  // Configure LED pins as outputs
  DDRB |= (1 << PB4);   // RED LED on PB4
  DDRB |= (1 << PB0);   // YELLOW LED on PB0
  DDRD |= (1 << PD2);   // GREEN LED on PD2

  // Configure button pin as input with internal pull-up
  DDRD &= ~(1 << PD4);  // PD4 as input
  PORTD |= (1 << PD4);  // Enable pull-up resistor on PD4

  curr_state = state_red;     // Start with RED light
  start_time = myMillis;      // Record start time
}

// Main loop (state machine)
void loop() {

  switch(curr_state){

    case state_red:
      PORTB |= (1 << PB4);    // RED LED ON
      PORTB &= ~(1 << PB0);   // YELLOW LED OFF
      PORTD &= ~(1 << PD2);   // GREEN LED OFF

      // After 5 seconds, go to GREEN state
      if (myMillis - start_time >= 5000) {
        curr_state = state_green;
        start_time = myMillis;
      }
      break;

    case state_yellow:
      PORTB &= ~(1 << PB4);   // RED LED OFF
      PORTB |= (1 << PB0);    // YELLOW LED ON
      PORTD &= ~(1 << PD2);   // GREEN LED OFF

      // After 2 seconds, go to RED state
      if (myMillis - start_time >= 2000) {
        curr_state = state_red;
        start_time = myMillis;
      }
      break;

    case state_green:
      PORTB &= ~(1 << PB4);   // RED LED OFF
      PORTB &= ~(1 << PB0);   // YELLOW LED OFF
      PORTD |= (1 << PD2);    // GREEN LED ON

      // After 5 seconds, go to YELLOW state
      if (myMillis - start_time >= 5000) {
        curr_state = state_yellow;
        start_time = myMillis;
      }
      break;
  }

  // Button check: if pressed (PD4 LOW), force RED state immediately
  if ((PIND & (1 << PD4)) == 0){
    curr_state = state_red;
    start_time = myMillis;
  }
}
