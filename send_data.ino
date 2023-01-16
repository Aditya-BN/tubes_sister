void SendDataToServer(float data)
{
  char dataCharArr[10];
  dtostrf(data, -1, 2, dataCharArr); //4 is mininum width, 3 is precision; float value is copied onto buffer
  
  char topicCharArr[50] = "";
  sprintf(topicCharArr, "%s/%s/%s", "tubes", namaMesin, "data");
  client.publish(topicCharArr, dataCharArr);

//  DisplayData(dataCharArr, senTypeName, 10);

#if debug > 2
  Serial.print("Send data to: "); Serial.print(topicCharArr);
  Serial.print(" data: "); Serial.println(dataCharArr);
#endif
}
