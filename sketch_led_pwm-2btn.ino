/*
 * Playing around with two buttons that control a LED brightness
 * using pwm. One led is made brighter/dimmer using the
 * buttons. When max brightness is readhed, the other led is
 * simply turned on.
 */

int ledPwm = 9; // The pin for pulse-width LED
int ledMax = 8; // The pin for the green LED indicating max value
int buttonPin1 = 3; // button 1
int buttonPin2 = 2; // button 2

void setup() 
{
  pinMode(ledPwm, OUTPUT); 
  pinMode(ledMax, OUTPUT); 
  pinMode(buttonPin1, INPUT); 
  pinMode(buttonPin2, INPUT); 

  // We will use Serial output for debugging
  Serial.begin(9600);
}

int value = -1;
int stepValue = 80;
int stepMillis = 500;
int maxValue = 240;
void loop() 
{ 
  int lastValue = value;
  String statusStr1 = "Max value reached";
  String statusStr = "";
  
  if(digitalRead(buttonPin1) == LOW)
  {
    value -= stepValue;
    delay(stepMillis);
  }
  else if(digitalRead(buttonPin2) == LOW)
  {
    value += stepValue;
    delay(stepMillis);
  }
  value = constrain(value, 0, maxValue);
  if (lastValue != value)
  {
    if (value == maxValue)
    {
      Serial.print(statusStr1+" ");
      digitalWrite(ledMax, HIGH); 
    }
    else
    {
      digitalWrite(ledMax, LOW);
    }
 
    Serial.println(value);
    analogWrite(ledPwm, value);
  }
  delay(5);
}
