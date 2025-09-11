#define LED1 2
#define LED2 4
#define LED3 8
#define LED4 12

int counter = 0;


// void setup() {
//   // put your setup code here, to run once:
//   pinMode(LED1, OUTPUT);
//   pinMode(LED2, OUTPUT);
//   pinMode(LED3, OUTPUT);
//   pinMode(LED4, OUTPUT);


// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   digitalWrite(LED1, (counter & 0b0001) ? HIGH : LOW);
//   digitalWrite(LED2, (counter & 0b0010) ? HIGH : LOW);
//   digitalWrite(LED3, (counter & 0b0100) ? HIGH : LOW);
//   digitalWrite(LED4, (counter & 0b1000) ? HIGH : LOW);

//   counter++;
//   if (counter > 15) { 
//     //reset after 1111
//     counter = 0;


//   }

//   delay(500);

//   }

// Bare Metal Version
void setup() {

    DDRD |= (1 << PD2); // LED 1
    DDRD |= (1 << PD4);
    DDRB |= (1 << PB0);
    DDRB |= (1 << PB4);
    
  }

void loop(){

  //Clear LED bits

  PORTD &= ~((1 << PD2) | ~(1<<PD4));
  PORTB &= ~((1 << PB0) | ~(1 << PB4));

  if (counter & 0b0001) PORTD |= (1 << PD2); //LED1
  if (counter & 0b0010) PORTD |= (1 << PD4); //LED2
  if (counter & 0b0100) PORTB |= (1 << PB0); //LED3
  if (counter & 0b1000) PORTB |= (1 << PB4); //LED4

  counter++;
  if (counter > 15) counter = 0;

  _delay_ms(500);


}


