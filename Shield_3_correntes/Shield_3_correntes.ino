#include <HTTPClient.h>
#include <WiFi.h>
#include "string.h"
#include "EmonLib.h"

const char* ssid     = "nome da rede";     // your network SSID (name of wifi network)
const char* password = "senha da rede"; // your network password

char *server = "script.google.com";  // Server URL

char *GScriptId = "sua implementação da planilha"; //planilha
                
const int httpsPort = 443;

TaskHandle_t Task1;
TaskHandle_t Task2;

WiFiClientSecure client;

double Irms1;
double Irms2;
double Irms3;

EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

void setup() {
  
  Serial.begin(115200); 

  emon1.current(36, 90.91);
  emon2.current(39, 90.91);
  emon3.current(34, 90.91);

  connect_wifi();


  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */                  
 
  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 1 */
 
}

void loop() {
 disableCore0WDT();
 }
