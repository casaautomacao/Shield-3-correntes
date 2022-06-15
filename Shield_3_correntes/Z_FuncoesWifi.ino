void connect_wifi(void)
{
  
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
  
    delay(500);
    Serial.print(WiFi.status());
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void enviarMedicao()
{
  HTTPClient http;
  
  String url = String("https://script.google.com") + "/macros/s/" + GScriptId + "/exec?" + "value1=" + Irms1 + "&value2=" + Irms2 + "&value3=" + Irms3;
  
  
  Serial.print("Making a request");
  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  String payload;
  if (httpCode > 0) { //Check for the returning code
    payload = http.getString();

    Serial.println(httpCode);
    Serial.println(payload);
    //     testdrawstyles(payload);
    //if (httpCode == 200 or httpCode == 201) tempPing.Saida(0);
  }
  else {
    Serial.println("Error on HTTP request");
  }
  http.end();

}
