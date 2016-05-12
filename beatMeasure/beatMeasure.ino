#include <avr/interrupt.h>

uint8_t a = 1;
uint16_t val = 0;
int cnt = 0;
int data = 0;
float dur = 0;
int bpm = 0;

void initTimer()
{
  TIMSK1 |= (1 << TOIE1);
  TCCR1A = 0b00000000;
}

void startTimer()
{
  TCCR1B |= 0b00000101;
  TCCR1B &= ~(0b00000010);
}

void stopTimer()
{
  TCCR1B &= ~(0b00000101);
}

void resetTimer()
{
  TCNT1H = 0b00000100;
  TCNT1L = 0b10010100;
  //a =0;
}

uint16_t timerVal()
{
  return TCNT1H*256+TCNT1L;
}

void setup()
{
  initTimer();
  analogReference(INTERNAL2V56);
  Serial.begin(9600);
 // pinMode(A8,INPUT);
}


void loop()
{
  data = analogRead(8);
 // Serial.println(data);
  if(data > 30 && data < 50)
  {
    if(cnt == 0)
    {
      startTimer();
    }
    cnt++;
//    delay(1000);
//    Serial.println(data);
  }
  if(cnt == 10)
  {
    stopTimer();
    val = timerVal();
   float dur = (val*0.0064+a*4.194)/cnt;
    bpm = 60/dur;
    //Serial.println(a);
    Serial.println(val);
   // Serial.println(dur);
  //Serial.println("Complete =   " + String(bpm));
    resetTimer();
    cnt=0;
    a=0;
  }

  
}
/*ISR(TIMER1_OVF_vect)
{
  a++;
     Serial.println(a);
}*/
