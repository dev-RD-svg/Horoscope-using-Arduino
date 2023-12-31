**Hardware Used:** Arduino Uno Grove-LCD RGB Backlight Potentiometer Pushbutton Yellow LED Green LED Blue LED Red LED 

**Software/Libraries Used:** Arduino IDE 2.0.0 Grove LCD library 

**Technical Description**

The Arduino program accepts the date of birth as input on the LCD and asks for a date, a month, and a year one by one in that order from the user. The interactive principle used here is that the user receives feedback after allowing input each time and after giving DOB values, the given data is displayed on the LCD screen as output. The user is then asked to confirm the DOB before proceeding to calculate the user’s zodiac and identify the element. Zodiac is calculated based on the English calendar chart and each of the 12 zodiacs is categorized into 4 elements: Fire, Water, Air, and Earth, and are represented by red, blue, yellow, and green LEDs respectively. The functionality of the program is that while the user is displayed the zodiac sign from the input DOB, the corresponding LED symbolized for the element will lighten up. Following this, a message is displayed on the screen which is the resulting horoscope (calculated using the random() function) for the user with regards to the Barnum effect.
