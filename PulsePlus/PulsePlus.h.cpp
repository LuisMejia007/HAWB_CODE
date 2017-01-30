/*
  PulsePlus.cpp - Pulse library for Wiring & Arduino
   Copyright (c) 2014 David Gomez.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  */
#include "Arduino.h"
#include "PulsePlus.h"

// Constructors ////////////////////////////////////////////////////////////////
PulsePlus::PulsePlus(int pin) {

  pinMode(pin, OUTPUT);
  _pin = pin;
}

// Public Methods //////////////////////////////////////////////////////////////


void PulsePlus::PulseH(long time) {

  digitalWrite(_pin, HIGH);
  delay(time);
  digitalWrite(_pin, LOW);
}

void PulsePlus::PulseL(long time) {

  digitalWrite(_pin, LOW);
  delay(time);
  digitalWrite(_pin, HIGH );
}

void PulsePlus::PulseHVar(long timeH,long timeL) {

  digitalWrite(_pin, HIGH);
  delay(timeH);
  digitalWrite(_pin, LOW);
  delay(timeL);
}

void PulsePlus::PulseLVar(long timeL, long timeH) {

  digitalWrite(_pin, LOW);
  delay(timeL);
  digitalWrite(_pin, HIGH );
  delay(timeH);
}

void PulsePlus::PulseTrain(long time, long times) {
 int i=0;
	 for (i=0; i<times;i++){
	  digitalWrite(_pin, HIGH);
	  delay(time);
	  digitalWrite(_pin, LOW );
	  delay(time);
	}
}

void PulsePlus::PulseTrainVar(long timeH, long timeL, long times) {
 int i=0;
	 for (i=0; i<times;i++){
	  digitalWrite(_pin, HIGH);
	  delay(timeH);
	  digitalWrite(_pin, LOW );
	  delay(timeL);
	}
}