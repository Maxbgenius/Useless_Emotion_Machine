const int mainToggleSwitchPin = 2;
const int limitSwitchPin = 3;

const int ledPin = 13;
const int extendArmPin = 12;
const int retractArmPin = 11;

const int redLEDPin = 10;
const int greenLEDPin = 9;

const int vibratorPin = 8;

const int screamerPin = 7;

boolean ledOn = false;
int currentCycleNumber;
boolean mainToggleSwitch;
boolean armLimitSwitch;
String armState;
String oldArmState;

String checkArmState() //my sexy function that checks system inputs/outputs and determines the system state
{
  boolean mainToggleSwitch = digitalRead(mainToggleSwitchPin);
  boolean armLimitSwitch = digitalRead(limitSwitchPin);

  if (mainToggleSwitch == LOW && armLimitSwitch == HIGH)
  {
    armState = "retracting";
  }
  else if (mainToggleSwitch == HIGH && armLimitSwitch == LOW || mainToggleSwitch == HIGH && armLimitSwitch == HIGH)
  {
    armState = "extending";
  }
  else if (mainToggleSwitch == LOW && armLimitSwitch == LOW    )
  {
    armState = "retracted";
  }
  return armState;
}


void setup()
{
  Serial.begin(9600);

  pinMode(mainToggleSwitchPin, INPUT);
  pinMode(limitSwitchPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);

  pinMode(extendArmPin, OUTPUT);
  pinMode(retractArmPin, OUTPUT);

  pinMode(vibratorPin, OUTPUT);

  pinMode(screamerPin, OUTPUT);
  
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(vibratorPin, LOW);
  digitalWrite(screamerPin, LOW);

  currentCycleNumber = 0;
  oldArmState = "retracted";

  mainToggleSwitch = digitalRead(mainToggleSwitchPin);
  armLimitSwitch = digitalRead(limitSwitchPin);

  while (armState != "retracted")
  {
    digitalWrite(retractArmPin, HIGH);
    delay(5);
    checkArmState();
  }

}


void loop()
{
  checkArmState();   //Outputs the current state of the system (retracted. extending, or retracting)

  if (armState == "retracted")
  {
    digitalWrite(extendArmPin, LOW);
    digitalWrite(retractArmPin, LOW);
  }
  else if (armState == "extending")
  {
    digitalWrite(extendArmPin, HIGH);
    digitalWrite(retractArmPin, LOW);
  }
  else if (armState == "retracting")
  {
    digitalWrite(extendArmPin, LOW);
    digitalWrite(retractArmPin, HIGH);
  }

  if (oldArmState != armState)  //increments the count if state has changed in any way since the last loop
  {
    ++currentCycleNumber;
    oldArmState = armState;
  }

  oldArmState == armState;  //set old arm state equal to current arm state

  if (currentCycleNumber > 0 && currentCycleNumber <= 10) //controls emotional signals to red and green LED, vibrator, and screamer
  {
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(vibratorPin, LOW);
    digitalWrite(screamerPin, LOW);
  }

  else if (currentCycleNumber > 10 && currentCycleNumber <= 20)
  {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
    if (currentCycleNumber > 10 && currentCycleNumber <= 20 && armState == "retracting")
    {
      digitalWrite(vibratorPin, HIGH);
      digitalWrite(screamerPin, LOW);
    }
    else
    {
      digitalWrite(vibratorPin, LOW);
      digitalWrite(screamerPin, LOW);
    }
  }

  else if (currentCycleNumber > 20 && currentCycleNumber <= 25)
  {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
    if (currentCycleNumber > 15 && currentCycleNumber <= 25 && armState == "retracting")
    {
      digitalWrite(vibratorPin, HIGH);
      digitalWrite(screamerPin, HIGH);
    }
    else
    {
      digitalWrite(vibratorPin, LOW);
      digitalWrite(screamerPin, LOW);
    }
  }

  else if (currentCycleNumber > 25)
  {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(vibratorPin, HIGH);
    digitalWrite(screamerPin, HIGH);
  }

  else
  {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(vibratorPin, LOW);
    digitalWrite(screamerPin, LOW);
  }
  
  mainToggleSwitch = digitalRead(mainToggleSwitchPin);
  armLimitSwitch = digitalRead(limitSwitchPin);

//print useful stats to monitor
  Serial.print(currentCycleNumber);
  Serial.print("\t");
  Serial.print(armState);
  Serial.print("\t");
  Serial.print(mainToggleSwitch);
  Serial.print("\t");
  Serial.println(armLimitSwitch );
  delay(5);
}






