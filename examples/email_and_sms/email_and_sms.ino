/*
 * AlertMe EMAIL & SMS DEMO (that you have to scroll past the comments to see)
 * by Connor Nishjima 2017
 * 
 * Did you know an ESP8266 can not only send emails, but SMS too - without any
 * extra hardware? Well, technically. SMTP is easy enough, then you can use it 
 * to send emails to your cell-carrier's Email-to-SMS portal! If you have
 * unlimited texting (as most carriers do now that data is the focus) then this
 * SMS feature costs you virtually nothing!
 * 
 * This sketch uses WiFiManager and ArduinoJSON to persistently store WiFi and
 * SMTP connection credentials in the ESP8266's SPIFFS filesystem. This way, on
 * each boot we can immediately reconnect to the network and test our connection
 * to the SMTP server.
 * 
 * When there is no working network credentials to connect to, the ESP8266 will
 * host a WiFi AP named "AlertMe Configuration". Connect to this access point,
 * and visit http://192.168.4.1 in your browser to enter new WiFi and SMTP credentials!
 * 
 * Unless your WiFi network or email provider changes, you'll only have to do this
 * step once. We're going to assume you're using Gmail for this example, so the
 * SMTP information may differ for your provider. To allow sending emails through
 * outside services on Gmail, you'll need to follow the steps for your account here:
 * 
 * https://support.google.com/accounts/answer/6010255
 * 
 * With the WiFiManager portal on the "AlertMe Configuration" network at
 * http://192.168.1.4/, you'll want to use these inputs:
 * 
 * SMTP Port: 465
 * SMTP Server: smtp.gmail.com
 * Email Address: yourgmailaddress@gmail.com
 * Password: your_gmail_password
 * 
 * Once entered, the ESP8266 will retry a WiFi connection, and then test the SMTP
 * credentials you entered. If successfully configured, it will send two messages:
 * 
 * - Email to "youremailaddress@gmail.com" containing the milliseconds since start
 * - SMS to "yourphonenumber@yoursmsgateway.com" with a random 16-bit integer
 * 
 * From now on, the WiFi and SMTP credentials are stored for future use, and
 * alert.connect() will connect and continue without hesitation! If you want to
 * change your saved information any time, just use alert.config(). You can check
 * for a gounded pin at boot to trigger this with a switch.
 * 
 * A NOTE FROM THE DEVELOPER -----------
 * 
 * Don't use this for spam. Don't you do it.
 * I assume no responsibility for how this is used.
 */
 
#include "AlertMe.h" // This includes all of the references to WiFiManager and ArduinoJSON that we need
AlertMe alert;

uint8_t config_pin = 12;

String to_email = "johndoe@gmail.com";  // The email address to send the message to
String to_sms = "5551234567@carriersmsportal.com"; // Look up your carrier's Email-to-SMS gateway here: https://martinfitzpatrick.name/list-of-email-to-sms-gateways/

String subject_line = "AlertMe Demo";
String message;

void setup() {
  Serial.begin(250000);
  pinMode(config_pin,INPUT_PULLUP);
  if(config_pin == LOW){ // Short pin to GND for config AP
    alert.config();
  }
  
  //alert.debug(true); // uncomment for debug/SMTP data
  
  Serial.print("\nConnecting to WIFI/SMTP...");
  alert.connect(); // Connect to WiFi, then test connect to SMTP server.
                   // If we fail with either, or they aren't configured,
                   // host an AP portal for configuration.
                   // alert.connect(true) prints WiFi debug info

  Serial.println("Connected!");
  // Finally, let's send some alerts!

  message = "This was email sent from the AlertMe library running on an ESP8266 with the Chip ID "+String(ESP.getChipId())+"! It's been " + String(millis()) + " milliseconds since this code started.";
  Serial.print("Sending Email...");
  Serial.println(alert.send(subject_line, message, to_email)); // alert.send() returns "SENT" on success, or a specific error message on failure

  message = "This was email sent from the AlertMe library! A random 16-bit integer: " + String(random(0, 65536));
  Serial.print("Sending SMS...");
  Serial.println(alert.send(subject_line, message, to_sms));
}

void loop() {
  // put your main code here, to run repeatedly:

}
