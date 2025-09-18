/*How to use a seven-segment LED display.
  created by the SriTu Tech team.
  Read the code below and use it for any of your creations.
  Home Page
*/
byte pin[] = {2, 3, 4, 5, 6, 7, 8, 9};//arduino pin array
 
int number[9][8] = {//number array
  {1, 1, 0, 0, 0, 1, 1, 1},//1
  {0, 0, 1, 0, 0, 0, 1, 0},//2
  {1, 0, 0, 0, 0, 0, 1, 0},//3
  {1, 1, 0, 0, 0, 1, 0, 0},//4
  {1, 0, 0, 0, 1, 0, 0, 0},//5
  {0, 0, 0, 0, 1, 0, 0, 0},//6
  {1, 1, 0, 0, 0, 0, 0, 1},//7
  {0, 0, 0, 0, 0, 0, 0, 0},//8
  {1, 1, 0, 0, 0, 0, 0, 0},//9
};
 

void setup() {

  // Set pins 2-7 (PORTD2..7) as output
DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

// Set pins 8-9 (PORTB0..1) as output
DDRB |= (1 << PB0) | (1 << PB1);

}
 
void loop() {
  for (int a = 0; a < 9; a++) {

  for (int b = 0; b < 8; b++) {
    
    // Check which Arduino pin we are dealing with
    switch (pin[b]) {
      case 2: if (number[a][b]) PORTD |=  (1 << PD2); else PORTD &= ~(1 << PD2); break;
      case 3: if (number[a][b]) PORTD |=  (1 << PD3); else PORTD &= ~(1 << PD3); break;
      case 4: if (number[a][b]) PORTD |=  (1 << PD4); else PORTD &= ~(1 << PD4); break;
      case 5: if (number[a][b]) PORTD |=  (1 << PD5); else PORTD &= ~(1 << PD5); break;
      case 6: if (number[a][b]) PORTD |=  (1 << PD6); else PORTD &= ~(1 << PD6); break;
      case 7: if (number[a][b]) PORTD |=  (1 << PD7); else PORTD &= ~(1 << PD7); break;
      case 8: if (number[a][b]) PORTB |=  (1 << PB0); else PORTB &= ~(1 << PB0); break;
      case 9: if (number[a][b]) PORTB |=  (1 << PB1); else PORTB &= ~(1 << PB1); break;
    }
  }
  _delay_ms(500); 
}


}