#include <Stepper.h>

//modify these
const uint16_t Len = 1; //Set the length to match the number of points
const uint8_t SpeedSet = 50;
/*scale is what the shape dimensions are be multiplied by 
 * (pick number 1 or 2) */
uint8_t Scale = 1; 
const uint8_t CircleSize = 5;


Stepper MyStepper1(200, 4, 5, 6, 7);
Stepper MyStepper2(200, 8, 9, 10, 11);

//modify this
const int8_t Delta[Len][2] PROGMEM = { {1,-1} }; // Add in the instruction set here

void setup()
{
  MyStepper1.setSpeed(SpeedSet);
  MyStepper2.setSpeed(SpeedSet);
  Serial.begin(9600);
}

uint16_t j = 0;
uint8_t Stepped = 0;
void loop()
{
  int8_t xRem = pgm_read_byte(&Delta[j][0]);
  int8_t dx = xRem;
  int8_t yRem = pgm_read_byte(&Delta[j][1]);
  int8_t dy = yRem;
  if (dx < 0)
  {
    xRem = - (dx);
  }
  if (dy < 0)
  {
    yRem = - (dy);
  }
  int step1 = 0;
  int step2 = 0;
  while (xRem > 0 || yRem > 0)
  {
    if (xRem > 0)
    {
      if (dx > 0)
      {
        step1 += 1;
        step2 += 1;
      }
      else if (dx < 0)
      {
        step1 -= 1;
        step2 -= 1;
      }
      xRem--;
    }
    if (yRem > 0)
    {
      if (dy < 0)
      {
        step1 += 1;
        step2 -= 1;
      }
      else if (dy > 0)
      {
        step1 -= 1;
        step2 += 1;
      }
      yRem--;
    }
  }
  int abs1 = step1;
  int abs2 = step2;
  if (step1 < 0)
  {
    abs1 = - (step1);
  }
  if (step2 < 0)
  {
    abs2 = - (step2);
  }
  float ratio12;
  float ratio21;
  if ((abs1 + abs2) > 0)
  {
    ratio12 = (float) abs1 / (float) (abs1 + abs2);
    ratio21 = (float) abs2 / (float) (abs1 + abs2);
  }
  else
  {
    ratio12 = 1.0;
    ratio21 = 1.0;
  }
  
  float s1 = 0;
  float s2 = 0;
  if (Scale <= 0)
  {
    Scale = 1;
  }
  abs1 = (int) (abs1 * Scale);
  abs2 = (int) (abs2 * Scale);
  
  uint8_t circleInc = 0;
  while ((abs1 + abs2) > 0)
  {
    s1 += ratio12;
    s2 += ratio21;
    if (s1 >= 1.0 && abs1 > 0)
    {
      if (step1 > 0)
      {
        MyStepper1.step(1);
        abs1--;
        s1 -= 1.0;
        Stepped++;
      }
      else if (step1 < 0)
      {
        MyStepper1.step(-1);
        abs1--;
        s1 -= 1.0;
        Stepped++;
      }
    }

    if (s2 >= 1.0 && abs2 > 0)
    {
      if (step2 > 0)
      {
        MyStepper2.step(1);
        abs2--;
        s2 -= 1.0;
        Stepped++;
      }
      else if (step2 < 0)
      {
        MyStepper2.step(-1);
        abs2--;
        s2 -= 1.0;
        Stepped++;
      }
    }

    if (Stepped >= 4)
    {
      uint8_t circle = circleInc % 8;
      if (circle == 0)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper1.step(1);
          MyStepper2.step(1);
        }
        circleInc = 0;
      }
      else if (circle == 1)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper2.step(1);
        }
      }
      else if (circle == 2)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper1.step(-1);
          MyStepper2.step(1);
        }
      }
      else if (circle == 3)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper1.step(-1);
        }
      }
      else if (circle == 4)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper1.step(-1);
          MyStepper2.step(-1);
        }
      }
      else if (circle == 5)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper2.step(-1);
        }
      }
      else if (circle == 6)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper1.step(1);
          MyStepper2.step(-1);
        }
      }
      else if (circle == 7)
      {
        for (int i = 0; i < CircleSize; i++)
        {
          MyStepper1.step(1);
        }
      }
      Stepped = 0;
      circleInc++;
    }
  }

  j++;
  if (j >= Len)
  {
    while (1) {}
  }
}
