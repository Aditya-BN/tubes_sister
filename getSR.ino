void adxlInit()
{
  if (!accel.begin())
  {
    Serial.println("No valid sensor found");
    while (1);
  }
  lcd.setCursor(0, 1);
  lcd.print("Sensor Ready!");

  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PENDETEKSI GEMPA");
}

float getSR(int sampling_delay)
{
  float x1, x2, y11, y2, z1, z2;
  float dx, dy, dz, dt, sr;
  uint16_t t1, t2;

  sensors_event_t event;
  accel.getEvent(&event);
  x1 = event.acceleration.x;
  y11 = event.acceleration.y;
  z1 = event.acceleration.z;
  t1 = millis();

  delay(sampling_delay);

  accel.getEvent(&event);
  x2 = event.acceleration.x;
  y2 = event.acceleration.y;
  z2 = event.acceleration.z;
  t2 = millis();

  dt = t2 - t1;
  dx = (((x2 - x1) * 1000) / dt) / 10;
  dy = (((y2 - y11) * 1000) / dt) / 10;
  dz = (((z2 - z1) * 1000) / dt) / 10;

  sr = sqrt((dx * dx) + (dy * dy) + (dz * dz));
  //  Serial.println(sr);

  return sr;
}
