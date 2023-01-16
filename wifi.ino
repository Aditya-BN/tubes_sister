void SetupWifi()
{
  uint8_t reconnectAttempt = 0;
  delay(10);

#if debug > 0
  Serial.print("Connecting to ");
  Serial.println(ssid);
#endif

  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.println(ssid);

  for (int i = 0 ; i < 16; i++) 
  {
    lcd.scrollDisplayLeft(); 
    delay(100);
  } 

  WiFi.mode(WIFI_STA);
#if wifiDHCP == 0
  WiFi.config(staticIP , subnet , gateway);
#endif
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED)
  {
#if debug > 0
    Serial.print(" .");
#endif

    delay(500);

    lcd.setCursor(0,1);
    lcd.print(" .");

    reconnectAttempt++;
    
    if (reconnectAttempt > 15)
    {
#if debug > 0
      Serial.print("\n udah reconnect sebanyak: ");
      Serial.println(reconnectAttempt);
      Serial.println("\n Wifi failed to connect, resetting!");
#endif

      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Wifi failed to connect, resetting!");
      ESP.reset();
    }
  }

#if debug > 0
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi connected!");
  lcd.setCursor(0,1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());

  delay(500);
}

void checkWifi()
{
  // cek apakah wifi masih tersambung
  statusWifi = (WiFi.status() != WL_CONNECTED) ? false : true;
}
