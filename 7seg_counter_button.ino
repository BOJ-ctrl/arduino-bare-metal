#define BUTTON 12                   // Define the button pin as Arduino digital pin 12
byte pin[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Array of Arduino pins connected to 7-segment display segments

int button_prev = 0;                // Tracks previous button state (used for edge detection / debouncing)
int count = 0;                      // Counter for which number to display (0–8, cycles with modulo)
int button_state;                   // Variable to store the raw button input state

// Lookup table for digits 1–9 on a 7-segment display
// Each row corresponds to a number, each column to a segment (1 = ON, 0 = OFF)
int number[9][8] = {
  {1, 1, 0, 0, 0, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 0, 1, 0}, // 2
  {1, 0, 0, 0, 0, 0, 1, 0}, // 3
  {1, 1, 0, 0, 0, 1, 0, 0}, // 4
  {1, 0, 0, 0, 1, 0, 0, 0}, // 5
  {0, 0, 0, 0, 1, 0, 0, 0}, // 6
  {1, 1, 0, 0, 0, 0, 0, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0, 0}, // 8
  {1, 1, 0, 0, 0, 0, 0, 0}, // 9
};

void setup() {
  // Set pins PD2–PD7 (Arduino D2–D7) as outputs for 7-segment display segments
  DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

  // Set pins PB0 and PB1 (Arduino D8–D9) as outputs for display segments
  DDRB |= (1 << PB0) | (1 << PB1);

  // Set PB4 (Arduino D12) as input
  DDRB &= ~(1 << PB4);

  // Enable internal pull-up resistor on PB4 (button pin)
  PORTB |= (1 << PB4);
}

void loop() {
  // Read button state from PINB register (bit 4 → PB4)
  button_state = PINB & (1 << PB4);

  // If button is pressed (logic LOW because of pull-up) and was not pressed before
  if ((button_state == 0) && (button_prev == 0)) {
    _delay_ms(50);            // Debounce delay
    button_prev = 1;          // Mark button as pressed
    count = (count + 1) % 9;  // Increment count and wrap around after 9
  }

  // If button is released (PB4 = HIGH)
  if (button_state == 16) {   // 16 decimal = bitmask 0b00010000
    button_prev = 0;          // Reset button state
  }
  
  // Update the 7-segment display with the current number
  for (int b = 0; b < 8; b++) {
    switch (pin[b]) {
      case 2: if (number[count][b]) PORTD |=  (1 << PD2); else PORTD &= ~(1 << PD2); break;
      case 3: if (number[count][b]) PORTD |=  (1 << PD3); else PORTD &= ~(1 << PD3); break;
      case 4: if (number[count][b]) PORTD |=  (1 << PD4); else PORTD &= ~(1 << PD4); break;
      case 5: if (number[count][b]) PORTD |=  (1 << PD5); else PORTD &= ~(1 << PD5); break;
      case 6: if (number[count][b]) PORTD |=  (1 << PD6); else PORTD &= ~(1 << PD6); break;
      case 7: if (number[count][b]) PORTD |=  (1 << PD7); else PORTD &= ~(1 << PD7); break;
      case 8: if (number[count][b]) PORTB |=  (1 << PB0); else PORTB &= ~(1 << PB0); break;
      case 9: if (number[count][b]) PORTB |=  (1 << PB1); else PORTB &= ~(1 << PB1); break;
    }
  }
}
