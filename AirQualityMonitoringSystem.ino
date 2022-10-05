#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "KampungTongah"; //Access Point
const char* password = "sayasiapaya"; // Password

// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";
// Service API Key
//String apiKey = "7CGDICJHW1MDAHWS";
//String apiKey = "F4JBL0K3Y9OS8YZU"; //node1
//String apiKey = "SO9DAMIEFG1Z278V"; //node2
String apiKey = "ICOWWBGUGVXEZ4U0"; //node3

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
}
void loop() {
  String httpRequestData = "api_key=" + apiKey + "&field1=0&field2=0&field3=0&field4=0&field5=0&field6=0&field7=0&field8=0";
  //send data to thingspeak every 5 minutes
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200) {
        statusNet = "OK";
      }
      else {
        statusNet = String(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
/**********************************************************************************************************************************************************************************/
