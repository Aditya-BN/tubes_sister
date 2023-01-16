void mqttInit()
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  MqttConnect();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MQTT Connected!");
}

void MqttConnect()
{
  // menyambungkan ke server mqtt untuk pengiriman data
  if (!client.connected())
  {
    statusMqtt = false;
    Serial.println(statusMqtt);
    if (millis() - lastReconnectAttempt > 2000)
    {
      lastReconnectAttempt = millis();
      char mqttClientId[] = namaMesin;
      
      // Attempt to reconnect
      if (client.connect(mqttClientId))
      {
        char topicCharArr[30];
        
        // Publish alamat IP alat ke server
        sprintf(topicCharArr, "%s/%s/%s", "tubes", namaMesin, "ip");
        client.publish(topicCharArr, WiFi.localIP().toString().c_str(), true);
        lastReconnectAttempt = 0;
        statusMqtt = true;
      }
    }
  }
  else  // Ketika terhubung ke server mqtt
  {
    statusMqtt = true;
    client.loop();
  }
}

// callback buat kalo ada pesan masuk dari mqtt nya
// belum terpakai untuk saat ini
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
