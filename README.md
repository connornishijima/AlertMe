![#AlertMe Library](https://i.imgur.com/TiQ5zEf.jpg)

**Did you know your ESP8266 could send Email and SMS without any extra hardware or paid services like Twilio?**

With AlertMe, your ESP8266 project can:

- Email you when an external sensor triggers, such as a button press, tilt, vibration, or any other sensor/interrupt combo you can think of!
- Text you when a external motion sensor detects motion where there shouldn't be!
- Quickly connect to any WiFi network, with hotspot configuration of your notification settings!
- Send Email through the provider of your choice via SMTP! (\**Only Gmail tested so far*)
- Send SMS through your cell phone carrier's SMS-to-Email portal! (Over 200 worldwide carriers support this)

Here's a quick example, which will automatically reconfigure as a configuration hotspot if it can't connect to a saved network/server:

    #include "AlertMe.h"
    AlertMe alert;
    void setup() {
      alert.connect();
      alert.send("AlertMe Demo, "This is an email demonstrating the AlertMe library!", "johndoe@gmail.com");
    }
    void loop(){}
