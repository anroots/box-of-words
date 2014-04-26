

/**
 * Get the code for the currently pressed button.
 * 
 * Returns one of the button constants (ex. getPressedBtn() == btnLeft)
 * or 0 when no button is currently pressed.
**/
byte getPressedBtn() {
  
  // Read all button pin analog values into an array
  int buttonValues[4] = {
    readButton(btnEnter),
    readButton(btnBack),
    readButton(btnLeft),
    readButton(btnRight)
  };
  

  // Determine whether any of the buttons is currently active
  boolean hasLow = false;
  for (byte i = 0; i < 4; i++) {
    if (buttonValues[i] <= btnLowMaxThreshold) {
      hasLow = true;
    } else {
    }
  }
  
  // No button pressed
  if (!hasLow) {
    return 0;
  }

  // Determine which of the button pins has a analogRead value closest to GND
  byte lowestIndex = 0;
  for (byte i = 1; i < 4; i++) {
    if (buttonValues[i] < buttonValues[i-1]) {
      lowestIndex = i;
    }
  }
  
  // Return the button constant of the currently active button
  switch (lowestIndex) {
    case 0: return btnEnter; break;
    case 1: return btnBack; break;
    case 2: return btnLeft; break;
    case 3: return btnRight; break;
  }
  
  // This should never happen, yet you never know...
  return 0;
  
}

/**
 * Get the analogRead value of the specified button pin.
 * The reading is automatically debounced if the button is active.
**/
int readButton(byte btnPin) {
   int btnVal = analogRead(btnPin);
  
  if (btnVal <= btnLowMaxThreshold) {
    delay(20);
    return analogRead(btnPin);
  }
  
  return btnVal;
}
