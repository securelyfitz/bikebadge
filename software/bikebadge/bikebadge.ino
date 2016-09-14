#define F_CPU 1000000
#define pwm0 0
#define pwm1 1

#include <CapacitiveSensor.h>

bool pressed=false;
int revs=128;

CapacitiveSensor   cs_3_2 = CapacitiveSensor(3,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_3_4 = CapacitiveSensor(3,4);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil

void setup()
{
  pinMode(pwm0, OUTPUT);
  pinMode(pwm1, OUTPUT);
}

void loop()
{
  for (float i=0;i<(3.1415*2);i+=(3.1415/revs))
  {
    analogWrite(pwm0,127*(cos(i)+1));
    analogWrite(pwm1,127*(sin(i)+1));
  if (pressed){
    if((cs_3_4.capacitiveSensor(1)<10)and(cs_3_2.capacitiveSensor(1)<10)){
       pressed=false;
    }
  }else{
    if(cs_3_4.capacitiveSensor(1)>50){
      pressed=true;
      if (revs>=2)revs/=2;
    }
    if(cs_3_2.capacitiveSensor(1)>50){
      pressed=true;
      if(revs<=16000)revs*=2;
    }
  }
  }
}
