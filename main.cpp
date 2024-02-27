#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "millis.h"
#include <string.h>
#include <stdlib.h>


// https://wokwi.com/projects/365067824797777921


// ******************SHOW Hederlige Harrys Cars: ************************

char*getRandomHarrysText(char*buffer[3]){
    char *randomText = buffer[rand() % 3];
    return randomText;
}

void showHarrysText(char*text, char*buffer[3], bool flag){
    HD44780 lcd;
    if (text == buffer[2]){
        if (flag == true) {
            lcd.WriteText (text);}
            else{
                lcd.Clear();
            }
    }
    else {
        lcd.WriteText(text);}  
        
    
}

// ******************SHOW Farmor Ankas Pajer AB: ************************

char*getRandomPajerText(char*buffer[2]){
    char *randomText = buffer[rand() % 2];
    return randomText;
}

void showPajerText(char*text, char*buffer[2], bool flag){
    HD44780 lcd;    
    if (text == buffer[1]){
        if (flag == true) {
            lcd.WriteText (text);}
            else{
                lcd.Clear();
            }
    }
    else {
        lcd.WriteText(text);}          
    
}


// ******************SHOW Svarte Petters Svartbyggen: ************************

char*selectTextPetters (char*buffer[2], int min) {
    if (min % 2 == 0) {
        return buffer[0];
    }
    else {
        return buffer[1];
    }

}


// ******************SHOW Långbens detektivbyrå: ************************

char*selectTextLangbens (char*buffer[2], int hour) {
    if (hour % 2 == 0) {
        return buffer[0];
    }
    else {
        return buffer[1];
    }

}   



int main(void){


// Hederlige Harrys Cars:
//Paid 5000. Want to randomly show one of these three messages
// Show for 8 sec

char harrysMessage1[20] = "Köp bil hos Harry"; // regular text
char harrysMessage2[31] = "En god bilaffär (för Harry!)"; // regular text
char harrysMessage3[31] = "Hederlige Harrys Bilar"; // blinking text

char* harrysPtr1 = harrysMessage1;
char* harrysPtr2 = harrysMessage2;
char* harrysPtr3 = harrysMessage3;

char*harrysCars[3] = {harrysPtr1, harrysPtr2, harrysPtr3};

// Farmor Ankas Pajer AB: 
// Paid 3000. Want to randomly show one of these two messages
// Show for 4 sec

char pajerMessage1[25] = "Köp paj hos Farmor Anka"; // blinking text
char pajerMessage2[38] = "Skynda innan Mårten ätit alla pajer"; // regular text
char* pajerPtr1 = pajerMessage1;
char* pajerPtr2 = pajerMessage2;

char*ankasPajer[2] = {pajerPtr1, pajerPtr2};

// Svarte Petters Svartbyggen: 
// Paid 1500. Wanna show
// Show for 2 sec

char pettersMessage1[26] = "Låt Petter bygga åt dig"; // text - på jämna minuter
char pettersMessage2[25] = "Bygga svart? Ring Petter"; // text - på ojämna minuter
char* pettersPtr1 = pettersMessage1;
char* pettersPtr2 = pettersMessage2;

char*pettersScartbyggen[2] = {pettersPtr1, pettersPtr2};




// Långbens detektivbyrå: 
// Betalat 4000. Wanna show
// Show for 6 sec

char langbensMessage1[25] = "Mysterier? Ring Långben"; // text - on even hours
char langbensMessage2[25] = "Långben fixar biffen";  //  text - on uneven hours

char* langbensPtr1 = langbensMessage1;
char* langbensPtr2 = langbensMessage2;

char* langbensByra[2] = {langbensMessage1, langbensMessage2}; 
    
HD44780 lcd;

int msec, min, hour; 
bool flagTillBlinck = true;

while (1)  {
   
for (hour = 0; hour < 24; hour ++){
    char*showLangbensText = selectTextLangbens (langbensByra, hour);    
    for (min = 0; min < 60; min ++) {  
        char*showPettersText = selectTextPetters (pettersScartbyggen, min); 
        for (msec = 0; msec < 600; msec += 200) { 
            char*showHarrysRandomText = getRandomHarrysText(harrysCars);
            char*showPajerRandomText = getRandomPajerText(ankasPajer);                 
            
            for (int showTime = 0; showTime <200; showTime++) {
                lcd.Clear();
                lcd.GoTo(0,0);
                flagTillBlinck = !flagTillBlinck;
                if (showTime>=0 && showTime<80) {                
                    showHarrysText(showHarrysRandomText, harrysCars, flagTillBlinck);                   
                }
                if (showTime>=80 && showTime<140) {                    
                    lcd.WriteText(showLangbensText);                   
                }   
               
                if (showTime>=140 && showTime<180) {                   
                    showPajerText(showPajerRandomText, ankasPajer, flagTillBlinck);
                }
                   
                if (showTime>=180 && showTime<200) {
                    lcd.WriteText(showPettersText);
                } 
                _delay_ms(100);            
            } 
                    
        }  
     
    }             
}
}
    return 0;
}




