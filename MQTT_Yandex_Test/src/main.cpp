#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>



/*
Кусок кода связанный с точкой доступа
*/
const char *ssid = "Pit";
const char *password = "mylittlefox";
bool connectdone = false;
/*
Яндекс CLOUD
*/

const char *mqttServer = "mqtt.cloud.yandex.net";
int mqttPort = 8883;
const char *username = "arefue59v89ugs6blklm";   //username and ID
const char *devicepassword = "GHty66258*-KKL";
const char *test_sr ="-----BEGIN CERTIFICATE-----\n \
MIIDUzCCAjqgAwIBAgIBADANBgkqhkiG9w0BAQ0FADBDMQswCQYDVQQGEwJ1czEM\n\
MAoGA1UECAwDUFBUMRIwEAYDVQQKDAlsb2NhbGhvc3QxEjAQBgNVBAMMCWxvY2Fs\n\
aG9zdDAeFw0yMTA2MjkxNTQxNDBaFw0yMjA2MjkxNTQxNDBaMEMxCzAJBgNVBAYT\n\
AnVzMQwwCgYDVQQIDANQUFQxEjAQBgNVBAoMCWxvY2FsaG9zdDESMBAGA1UEAwwJ\n\
bG9jYWxob3N0MIIBIzANBgkqhkiG9w0BAQEFAAOCARAAMIIBCwKCAQIAyOJ/chse\n\
W+oAMAKd0s8Z2Rt+c8oh4J2RjX8TapZap0e0hqtlC6Sp5unkTMfQll44oUx33W/d\n\
+9UGdCpXaOqPGD5gVs8nV04dFt1fgsoc1uzVEOOC+0MtwQ4RDtbKdUvD/M6xXilR\n\
wuzcJDH5HKYh/Tx+L7hjK7Mp/Xt6UXQpqtm+hvBdOI4OD7XCOole0maJfiEIk9ik\n\
hACQ2JdkVhsY/sVvkAfiAjsHW6tg1m2mHaOn6j/8KTfFBZOQNcEmErz2/bcIwij/\n\
hm4crKIM85D1dZIigcNJ5C/1wsN3tlwJJacoiAmLMQRFTDkXQnuektdT1YaV7Us1\n\
WTTYas/3PgrnyBcCAwEAAaNQME4wHQYDVR0OBBYEFFYBi5K11aIaXhX7k+DYBTOW\n\
mEMjMB8GA1UdIwQYMBaAFFYBi5K11aIaXhX7k+DYBTOWmEMjMAwGA1UdEwQFMAMB\n\
Af8wDQYJKoZIhvcNAQENBQADggECAAKg2cHHfIYRtPvVkLtcS5ducbzQtW4O15C7\n\
i7YuMo4YllfWy9J57/QXf9JeaA13S1/ptc6lz17Uhqt/hwdPRLQZZB4ACKX94H9e\n\
uthNc9goTN3c00xJ39o3fT7o3oDvqYvVitZ2jhblg5DChUDFnt1Hl7hPDlzpvwdB\n\
5GicMFWiOh+Jt+C29L/FdUi3P9NKMsnQOQLg//97u0VTvPHhmhdrjF6YSyMEpo/G\n\
RpXcOjthl0x9EsNWvxiVO94u3t18rSahjGFbUyde47DKXhE1YsWJsQ00scL8Wpv0\n\
O9nHmi2mV9NLNhiOTTraoQfQPUKbPn5+6/1wLBoT3UgsocFZpxww\n\
-----END CERTIFICATE-----";


WiFiClientSecure wclient; //wifi client
PubSubClient client (wclient);
BearSSL::X509List x509(test_sr);


void setup() {
  
  Serial.begin(115200);
  // put your setup code here, to run once:
  WiFi.begin(ssid, password);
  Serial.print("Connecting to.....");
  Serial.print(ssid);
  Serial.println("...");
  client.setServer(mqttServer, mqttPort);
  client.setBufferSize(1024);
  client.setKeepAlive(15);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
    Serial.println('\n');
    Serial.println("Connection Estabilished");
    Serial.print("IP Adress: \t");
    Serial.println(WiFi.localIP());
    wclient.setInsecure();
  
  
  //client.setCallback(callback);
  while(!client.connect("IoTESP", username,devicepassword))
  {

 
    Serial.println(client.state());
    delay (1000);
    if(client.connected())
    {
      Serial.println("Connected");
    }
  }

  if(client.publish("$devices/arefue59v89ugs6blklm/state/Cruid","estData"))
  {
    Serial.println("Publish");

  }else{
    Serial.println("NOt publish");
  }
    
  

}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}