/*
  PulsePlus library for Arduino & Wiring
  Copyright (c) 2014 David Gomez.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

PulsePlus(pin);
PulseH(long); //H -> t -> L
PulseL(long); //L -> t -> H
PulseHVar(long, long);  //H -> t1 -> L -> t2
PulseLVar(long, long);  //L -> t1 -> H -> t2
PulseTrain(long, long); //H -> t -> L  -> t -> H for n times
PulseTrainVar(long, long, long); //H -> t1 -> L -> t2  -> H  for n times
  
*/


#include <PulsePlus.h>

PulsePlus Pulse(13); 

void setup() {                
  
}

void loop() {

Pulse.PulseTrainVar(1000, 2000, 5);

delay (4000);
}