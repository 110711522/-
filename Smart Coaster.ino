/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 14 Jan 2021 03:21:37 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <LWiFi.h>

char _lwifi_ssid[] = "Adloe";
char _lwifi_pass[] = "6612823321";

void invokeThingSpeak(const String& key, const String& p1, const String& p2, const String& p3, const String& p4, const String& p5, const String& p6, const String& p7, const String& p8)
{
  // Initialize the Ethernet client library
  // with the IP address and port of the server
  // that you want to connect to (port 80 is default for HTTP):
  static WiFiClient client;

  if (client.connect("api.thingspeak.com", 80)) {
  const String payload = String() + "{\"api_key\":\"" + key
                        + "\",\"field1\":\"" + p1
                        + "\",\"field2\":\"" + p2
                        + "\",\"field3\":\"" + p3
                        + "\",\"field4\":\"" + p4
                        + "\",\"field5\":\"" + p5
                        + "\",\"field6\":\"" + p6
                        + "\",\"field7\":\"" + p7
                        + "\",\"field8\":\"" + p8
                        + "\"}";

      const String url = String() + "https://api.thingspeak.com/update";

      client.println(String() + "POST " + url + " HTTP/1.1");
      client.println("Host: api.thingspeak.com");
      client.println("User-Agent: BlocklyDuino/1.0");
      client.println("Content-Type: application/json;charset=utf-8");
      client.print("Content-Length: ");
      client.println(payload.length());
      client.println("User-Agent: BlocklyDuino/1.0");
      client.println("Accept: */*");
      client.println("Connection: close");

      client.println();
      client.print(payload);

      client.println();
      delay(300);
  } else {
    // Serial.println("failed to connect to ThingSpeak");
  }

  // wait for server response
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
      char c = client.read();
      // Serial.print(c);
      delay(1);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
      //Serial.println();
      //Serial.println("disconnecting from server passively.");
      client.stop();
  } else {
    // otherwise we actively stop the connection. we'll reconnect next time.
    //Serial.println("disconnecting from server.");
    client.stop();
  }
}

void setup()
{

  pinMode(13, OUTPUT);

  pinMode(12, OUTPUT);

  pinMode(11, OUTPUT);

}


void loop()
{
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  invokeThingSpeak("yourkey", String(0), String(0), String(0), String(0), String(0), String(0), String(0), String(0));
  if (analogRead(A0) <= 10) {
    analogWrite(13, 255);
    u8g2.firstPage();
    do {
      u8g2.drawStr(0, 0, String("喝水量嚴重不足").c_str());
      u8g2.drawLine(0, 11, 30, 11);

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    tone(14, 494);

  } else if (analogRead(A0) <= 30) {
    analogWrite(12, 255);
    u8g2.firstPage();
    do {
      u8g2.drawStr(0, 0, String("喝水量不足").c_str());
      u8g2.drawLine(0, 11, 30, 11);

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    tone(14, 349);
  } else {
    analogWrite(11, 255);
    u8g2.firstPage();
    do {
      u8g2.drawStr(0, 0, String("喝水量充足").c_str());
      u8g2.drawLine(0, 11, 30, 11);

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    tone(14, 262);

  }
  delay(60000);
}