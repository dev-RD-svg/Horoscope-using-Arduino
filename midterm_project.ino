//---------Program to take input date of birth from user and display horoscope results------------------

//--------------------------ASSUMPTIONS-------------------------------
//1. User's horoscopes are 

#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

const int numRows = 2;
const int numCols = 16;

int dateDob = 0; int monthDob = 0; int YearDob = 0; 
int setConfirm = 0;
bool flag_date = false; bool flag_month = false; bool flag_year = false; bool flag_zodiac = true;
bool flag = false; bool confirm = false; bool setProgramOff = false;
String element_Water = "Water";
String element_Fire = "Fire";
String element_Air = "Air"; 
String element_Earth = "Earth";
String horoscopeDetail[4] = {"You will have a Good day","Ask help from a friend!","You will have a Bad day","Pick 7!"};

void setup() {
  Serial.begin(57600);
  // set up the LCD's number of columns and rows:
  lcd.begin(numCols, numRows);
  pinMode(8,INPUT_PULLUP); // button
  pinMode(5,OUTPUT); // yellow LED
  pinMode(3,OUTPUT); // red LED
  pinMode(11,OUTPUT); // green LED
  pinMode(10,OUTPUT); // blue LED
}

void loop() {
  int sensorValue_input; int reply;
  char yes = 'yes'; char no = 'no';
  String userZodiac;

  if(flag_zodiac){
    //--------------INPUT DOB FROM USER - START---------------------- 

    if(!flag_date){ //enter statement block only when input date is null
      int sensorValue_Dob = analogRead(A0); //read the input on analog pin 0
      int sensorValue_Date = map(sensorValue_Dob, 0, 1023, 01, 31);
      // set the cursor to column 0, line 1
      lcd.setCursor(0, 0);
      lcd.print("Enter Date!"); //delay(2000);
      lcd.setCursor(0, 1);
      if (sensorValue_Date < 10) lcd.print(" "); // 0-9 add one space
      if (sensorValue_Date < 100) lcd.print(" "); // 0-99 add one space
      lcd.print(sensorValue_Date);
      int setDate = checkBtnTrigger(sensorValue_Date);
      dateDob = setDate;  
      //Serial.print(dateDob);
      if(dateDob != 0){ //enter statement block only when button is pressed
        flag = true;
        flag_date = true; //determiner set to true. So line 39 is no longer satisfied for future loops
        lcd.clear();
        lcd.print("Thanks!"); delay(2000); 
        lcd.clear();
        //Serial.print(dateDob); delay(100);      
      }
    }
    if(flag && !flag_month){ //enter statement block only when input date is not null and input month is null
      int sensorValue_Dob1 = analogRead(A0);
      int sensorValue_Month = map(sensorValue_Dob1, 0, 1023, 01, 12);
      
      lcd.setCursor(0, 0);
      lcd.print("Now enter Month!");//delay(2000);//lcd.clear();
      lcd.setCursor(0, 1);
      //Serial.print(sensorValue_Dob1);  
      if (sensorValue_Month < 10) lcd.print(" "); // 0-9 add one space
      if (sensorValue_Month < 100) lcd.print(" "); // 0-99 add one space
      lcd.print(sensorValue_Month); 
      //Serial.print(sensorValue_Month); delay(1000);
      int setMonth = checkBtnTrigger(sensorValue_Month);
      monthDob = setMonth; 
      if(monthDob != 0){  //enter statement block only when button is pressed
        flag = false;
        flag_month = true; //determiner set to true. So line 61 is no longer satisfied for future loops
        lcd.clear();
        lcd.print("Great!"); delay(2000); 
        lcd.clear();
        //Serial.print(dateDob); delay(100);
        //Serial.print(monthDob);
      }
    }
    if(!flag && flag_month && !flag_year){//enter statement block only when input date, month is not null and input year is null
      //flag = false;
      int sensorValue_Dob2 = analogRead(A0);
      int sensorValue_Year = map(sensorValue_Dob2, 0, 1023, 1970, 2000);
      
      lcd.setCursor(0, 0);
      lcd.print("Now enter Year!");
      lcd.setCursor(0, 1);
      //Serial.print(sensorValue_Dob2);  
      if (sensorValue_Year < 10) lcd.print(" "); // 0-9 add one space
      if (sensorValue_Year < 100) lcd.print(" "); // 0-99 add one space
      if (sensorValue_Year < 1000) lcd.print(" "); // 0-999 add one space
      lcd.print(sensorValue_Year); 
      //Serial.print(sensorValue_Year); delay(1000);
      int setYear = checkBtnTrigger(sensorValue_Year);
      YearDob = setYear; 
      if(YearDob != 0){  //enter statement block only when button is pressed
        flag = true;
        flag_year = true; //determiner set to true. So line 85 is no longer satisfied for future loops
        lcd.clear();
        lcd.print("Awesome!"); delay(2000); 
        lcd.clear();
        //Serial.print(dateDob); delay(100);
        //Serial.print(monthDob);delay(100);
        //Serial.print(YearDob);delay(100);
      }
    }
    //--------------INPUT DOB FROM USER - END---------------------- 

    //---------------DISPLAY OUTPUT ON LCD - START------------

    if(flag_year == true && flag_month == true && flag_date == true){ //enter statement block only when input date, month, year is not null
      if(flag){
        lcd.setCursor(0, 0);
        lcd.print("You entered"); delay(200);
        for(int i =0; i < 5; i++ ){
          delay(200);
          lcd.print(".");
        }
        //.......display dob on LCD......
        lcd.setCursor(3, 1);
        char buffer[17];
        sprintf(buffer, "%02d-%02d-%4d", dateDob, monthDob, YearDob);
        lcd.print(buffer); delay(2000); 
        lcd.clear();
        flag= false;
      }
      lcd.setCursor(0, 0);
      lcd.print("CONFIRM 1:Y::2:N");
      lcd.setCursor(0, 1);
      int sensorValue = analogRead(A0);
      //...........Ask user to confirm data provided as input before proceeding to display horoscope.........
      int sensorValue_No = map(sensorValue, 0, 511, 2, 2); //option NO
      int sensorValue_Yes = map(sensorValue, 512, 1023, 1, 1); //option YES
      if(sensorValue >= 0 && sensorValue < 512){
        lcd.print(sensorValue_No); 
        sensorValue_input = sensorValue_No;
      }
      else{
        lcd.print(sensorValue_Yes); 
        sensorValue_input = sensorValue_Yes;
      }
      setConfirm = checkBtnTrigger(sensorValue_input);
      //Serial.print(setConfirm); delay(100);
      if(setConfirm == 2){ //user confirmed NO 
        //..........Restart input DOB input from user........
        flag= false;    
        flag_year = false;
        flag_month = false; 
        flag_date = false; delay(1000);//restart program and make date, month, year NULL
        lcd.clear();
      }
      else if(setConfirm == 1){//user confirmed YES
        lcd.clear();
        //.......proceed to display zodiac, element & horoscope......
        switch(monthDob){
          case 1: //January
            if(dateDob <= 19) userZodiac = "Capricorn";
            if(dateDob >= 20) userZodiac = "Aquarius";
            break;
          case 2: //February
            if(dateDob <= 18) userZodiac = "Aquarius";
            if(dateDob >= 19) userZodiac = "Pisces";
            break;
          case 3: //March
            if(dateDob <= 19) userZodiac = "Pisces";
            if(dateDob >= 21) userZodiac = "Aries";
            break;
          case 4: //April
            if(dateDob <= 19) userZodiac = "Aries";
            if(dateDob >= 20) userZodiac = "Taurus";
            break;
          case 5: //May
            if(dateDob <= 20) userZodiac = "Taurus";
            if(dateDob >= 21) userZodiac = "Gemini";
            break;
          case 6: //June
            if(dateDob <= 21) userZodiac = "Gemini";
            if(dateDob >= 22) userZodiac = "Cancer";
            break;
          case 7: //July
            if(dateDob <= 22) userZodiac = "Cancer";
            if(dateDob >= 23) userZodiac = "Leo";
            break;
          case 8: //August
            if(dateDob <= 22) userZodiac = "Leo";
            if(dateDob >= 23) userZodiac = "Virgo";
            break;
          case 9: //September
            if(dateDob <= 22) userZodiac = "Virgo";
            if(dateDob >= 23) userZodiac = "Libra";
            break;
          case 10: //October
            if(dateDob <= 23) userZodiac = "Libra";
            if(dateDob >= 24) userZodiac = "Scorpio";
            break;
          case 11: //November
            if(dateDob <= 21) userZodiac = "Scorpio";
            if(dateDob >= 22) userZodiac = "Sagittarius";
            break;
          case 12: //December
            if(dateDob <= 21) userZodiac = "Sagittarius";
            if(dateDob >= 22) userZodiac = "Capricorn";
            break;
        }
        //Serial.print((String)userZodiac); delay(100);
        lcd.setCursor(0, 0);
        lcd.print("You are"); 
        for(int i =0; i < 5; i++ ){
          delay(200);
          lcd.print(".");
        }
        lcd.setCursor(0, 1);
        //Serial.println(userZodiac); //delay(3000);
        lcd.print(userZodiac); //display user's zodian sign based on DOB provided
        flag_zodiac = false;
        //.......user's element is displayed using colorful LEDs.....
        if(userZodiac == "Libra" || userZodiac == "Gemini" || userZodiac == "Aquarius"){
          digitalWrite(5,HIGH); // yellow LED represents AIR element.
        }
        if(userZodiac == "Aries" || userZodiac == "Leo" || userZodiac == "Sagittarius"){
          digitalWrite(3,HIGH); delay(3000);// red LED represents AIR element.
        }
        if(userZodiac == "Taurus" || userZodiac == "Virgo" || userZodiac == "Capricorn"){
          digitalWrite(11,HIGH); delay(3000); // green LED represents AIR element.
        }
        if(userZodiac == "Pisces" || userZodiac == "Cancer" || userZodiac == "Scorpio"){
          digitalWrite(10,HIGH);  delay(3000); // blue LED represents AIR element.
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Horoscope");  //display user's horoscope using Barnum effect
        for(int i =0; i < 2; i++ ){
          delay(200);
          lcd.print(".");
        }
        delay(2000);
        reply = random(1,5); // set a number between 1 and 4.
        //Serial.print(reply);
        lcd.clear();lcd.setCursor(16, 0);
        lcd.print(horoscopeDetail[reply - 1]);
        // scroll string length positions to the left and to move it offscreen left:
        for (int positionCounter = 0; positionCounter < horoscopeDetail[reply - 1].length(); positionCounter++) {
          lcd.scrollDisplayLeft(); // scroll one position left
          delay(500); // wait a bit:
        }
        //flag = true;
        delay(2000);
        lcd.clear(); lcd.setCursor(0, 0);
        if(!setProgramOff){ //statement block to be executed for the first time until condition is set false
          lcd.print("Ok bye!");
          analogWrite(5,255); delay(200);
          analogWrite(3,255); delay(200);
          analogWrite(11,255); delay(200);
          analogWrite(10,255); delay(200);

          for(int i = 255 ; i <= 205 ; i= i-50){
            analogWrite(5,i); 
            analogWrite(3,i); 
            analogWrite(11,i); 
            analogWrite(10,i); 
          }
          analogWrite(5,0); 
          analogWrite(3,0); 
          analogWrite(11,0); 
          analogWrite(10,0);
          delay(1000);
          lcd.clear();
          setProgramOff = true; //determiner set to false. no longer executes statement block from line 254
        }
      }
    }

    //---------------DISPLAY OUTPUT ON LCD - END------------
  }
}

int checkBtnTrigger(int input){
  int setValue;
  int btn_setNext = digitalRead(8);//sets value to 0 when button is pressed
  //Serial.print(input);
  if(btn_setNext == 0){
      setValue = input;
      //Serial.print(setValue);
      delay(100);
    }
    else{
      setValue = 0;
    }
  return setValue;
}







//----------------REDUNDANT CODE BELOW---------------------
int checkBtnTrigger_Date(int input){
  int setDate;
  int btn_setNext = digitalRead(8);//sets value to 0 when pressed
  //Serial.print(btn_setNext);
  if(btn_setNext == 0){
      setDate = input;
      //Serial.print(setDate);
      delay(100);
    }
    else{
      setDate = 0;
    }
  return setDate;
}

int checkBtnTrigger_Month(int input){
  int setMonth;
  int btn_setNext = digitalRead(8);//sets value to 0 when pressed
  //Serial.print(input);
  if(btn_setNext == 0){
      setMonth = input;
      //Serial.print(setMonth);
      delay(100);
    }
    else{
      setMonth = 0;
    }
  return setMonth;
}

int checkBtnTrigger_Year(int input){
  int setYear;
  int btn_setNext = digitalRead(8);//sets value to 0 when pressed
  //Serial.print(input);
  if(btn_setNext == 0){
      setYear = input;
      //Serial.print(setYear);
      delay(100);
    }
    else{
      setYear = 0;
    }
  return setYear;
}
