#define BUTTON 2
#define LED 12

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(BUTTON, INPUT_PULLUP);
//   pinMode(LED, OUTPUT);

// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if (digitalRead(BUTTON) == LOW){
//     digitalWrite(LED, HIGH);
//     delay(1000);
//     digitalWrite(LED, LOW);
//     delay(1000);
//   }

// }

void setup() {

  DDRD &= ~(1 << DDD5);

  PORTD |= (1 << PD2);

  DDRB |= (1 << DDB4);

  
}

void loop() {
  // check if PB5 (button) is LOW
  if ((PIND & (1 << PD2)) == 0) {  // button pressed
    PORTB |= (1 << PB4);   // LED ON (set PB4 high)
    _delay_ms(1000);       // 1 second delay
    PORTB &= ~(1 << PB4);  // LED OFF (clear PB4)
    _delay_ms(1000);       // 1 second delay
  }
}


