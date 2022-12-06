#include <LiquidCrystal.h>
#include "lcd.h"
const int RS = 9;
const int enable = 8;
const int d4 = 7;
const int d5 = 6;
const int d6 = 5;
const int d7 = 4;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

void lcdInit(){
  lcd.begin(16, 2);
  lcd.print("Press click");
  lcd.setCursor(0,1);
  lcd.print("to enter");
}

void startMenu(){
  lcd.setCursor(0, 0);
  lcd.print("Press click");
  lcd.setCursor(0, 1);
  lcd.print("to enter");
}

void menuOptions(int choice){
  if (choice == 1){
    lcd.setCursor(0, 0);
    lcd.print(">Play  Setup");
    lcd.setCursor(0, 1);
    lcd.print(" HighScore  Exit");
  }
  if (choice == 2){
    lcd.setCursor(0, 0);
    lcd.print(" Play >Setup");
    lcd.setCursor(0, 1);
    lcd.print(" HighScore  Exit");
  }
  if (choice == 3){
    lcd.setCursor(0, 0);
    lcd.print(" Play  Setup");
    lcd.setCursor(0, 1);
    lcd.print(">HighScore  Exit");
  }
  if (choice == 4){
    lcd.setCursor(0, 0);
    lcd.print(" Play  Setup");
    lcd.setCursor(0, 1);
    lcd.print(" HighScore >Exit");
  }
}

void setUp(int level, bool choice){
  if (choice){
    lcd.setCursor(0, 0);
    if (level == 1){
      lcd.print(">Level: Easy");
    }
    if (level == 2){
      lcd.print(">Level: Medium");
    }
    if (level == 3){
      lcd.print(">Level: Hard");
    }
    lcd.setCursor(0, 1);
    lcd.print(" Exit");
  }
  else
  {
    lcd.setCursor(0, 0);
    if (level == 1){
      lcd.print(" Level: Easy");
    }
    if (level == 2){
      lcd.print(" Level: Medium");
    }
    if (level == 3){
      lcd.print(" Level: Hard");
    }
    lcd.setCursor(0, 1);
    lcd.print(">Exit");
    
  }
}

void highScoreMenu(bool choice){
  if (choice){
    lcd.setCursor(0,0);
    lcd.print("HighScore: ");
    getHighScore = getScore();
    lcd.print(getHighScore);
    lcd.setCursor(0, 1);
    lcd.print(">Reset");
    lcd.print("  Exit");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("HighScore: ");
    getHighScore = getScore();
    lcd.print(getHighScore);
    lcd.setCursor(0, 1);
    lcd.print(" Reset");
    lcd.print(" >Exit");
  }
}

void lcdPlay(int lives, int score){
  if (lives > 0){
    lcd.setCursor(0, 0);
    lcd.print("Lives:");
    lcd.print(lives);
    lcd.setCursor(0, 1);
    lcd.print("Score:");
    lcd.print(score);
  }
}


//I used here DELAY because at the beginning of the game menu I will display only the info about the game(so it doesn't interrupt anything)
void introduction(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Creator Name:");
  lcd.setCursor(0, 1);
  lcd.print("Boroseanu Darius");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("github.com/");
  lcd.setCursor(0, 1);
  lcd.print("Darius02");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Game:");
  lcd.setCursor(0, 1);
  lcd.print("   Tetris");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("@UnibucRobotics2022");
  delay(2000);
  lcd.clear();
  
}