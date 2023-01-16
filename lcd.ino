void lcdInit()
{
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("hello");
  lcd.clear();
}
