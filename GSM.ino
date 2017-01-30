  #include "PulsePlus.h"

// POWER PIN
int GSM_PWR         = 13;

// SIM STATUS
int GSM_SWT         = 11;

// POWER STATUS
int GSM_STAT        = 12;

// RINGING STATUS
int GSM_RI          = 10;

boolean GSMSerial   = false;
String GSMSerialIn  = "";

PulsePlus Pulse(GSM_PWR); 

void setup() {
  // Launch serial for GSM.
  Serial.begin(38400);

  // Write pulses from PWR (powers on/off GSM)
  pinMode(GSM_PWR, OUTPUT);

  // Read pulses from SWT (indicates SIM status)
  pinMode(GSM_SWT, INPUT);

  // Read pulses from STAT (indicates power status)
  pinMode(GSM_STAT, INPUT);

  // Read pulses from RI (indicates ringer status)
  pinMode(GSM_RI, INPUT);

  // Power on the board.
  ToggleGSM();
}

void loop() {
  // Read pulses on the SWT pin (SIM add/remove)
  int duration = pulseIn(GSM_SWT, LOW);
  if (duration > 0) {
    Serial.println("DroneCell SIM Card inserted.");
  }

  duration = pulseIn(GSM_STAT, HIGH);
  if (duration > 0) {
    Serial.println("GSM I/O.");
  }

  duration = pulseIn(GSM_RI, HIGH);
  if (duration > 0) {
    Serial.println("GSM is ringing.");
  }

  if (GSMSerial) {
    Serial.println(GSMSerialIn);
    // clear the string:
    GSMSerialIn = "";
    GSMSerial = false;
  }
}

// Power on/off the AT5600 DroneCell
void ToggleGSM() {
  Serial.println("Sending I/O to DroneCell...");
  Pulse.PulseL(2);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    GSMSerialIn += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      GSMSerial = true;
    }
  }
}

