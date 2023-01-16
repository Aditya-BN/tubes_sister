void relayInit()
{
  // relay ada 2
  // relay 1 untuk memutus 12V
  // relay 2 untuk memutus ground

  pinMode(relay_vcc, OUTPUT);
  pinMode(relay_gnd, OUTPUT);

  digitalWrite(relay_vcc, HIGH);
  digitalWrite(relay_gnd, HIGH);
}

bool isDanger(float sr_val)
{
  // menetukan dan memastikan apakah terjadi gempa
  // Alat memang harus di reset ketika 'terlanjur' terjadi gempa. safety aspect.
  // eqCount tidak akan ter-reset nilainya kecuali alat direset manual.
  
  eqCount += (sr_val > 5) ?  1 : 0;
  return (eqCount > 5) ? true : false;
}

void relay(bool matikan)
{
  // Alat memang harus di reset ketika 'terlanjur' terjadi gempa. safety aspect.
  if (matikan) {
    digitalWrite(relay_vcc, LOW);
    digitalWrite(relay_gnd, LOW);
  }
  else {}
}
