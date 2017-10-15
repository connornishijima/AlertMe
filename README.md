![#AlertMe Library](https://i.imgur.com/TiQ5zEf.jpg)

**Did you know your ESP8266 could send Email and SMS without any extra hardware or paid services like Twilio?**

With AlertMe, your ESP8266 project can:

- Email you when an external sensor triggers, such as a button press, tilt, vibration, or any other sensor/interrupt combo you can think of!
- Text you when a motion sensor detects something it shouldn't!
- Quickly connect to any WiFi network, with hotspot configuration of your notification settings!
- Send Email through the provider of your choice via SMTP! (\**Only Gmail tested so far*)
- Send SMS through your cell phone carrier's SMS-to-Email portal! (Over 200 worldwide carriers supported)

----------
# Contents
- [Usage](#usage)
- [Reliability & Security](#reliability-and-security)
- [Free SMS Capability](#free-sms-capability)
- [Installation](#installation)
- [Dependencies](#dependencies)
- [Email Configuration](#email-configuration)
- [Functions](#functions)
- [Contributing](#contributing)
- [License and credits](#license-and-credits)
----------
# Usage

**Here's a quick example, which will automatically reconfigure as a configuration hotspot if it can't connect to a saved network/server:**

    #include "AlertMe.h"
    AlertMe alert;
    void setup() {
      alert.connect();
      alert.send("AlertMe Demo", "This is an email demonstrating the AlertMe library!", "johndoe@gmail.com");
    }
    void loop(){}

This would send an email with your subject line "AlertMe Demo", with the contents you specify, to johndoe@gmail.com! Simple as that.

# Reliablity and Security

No need to worry about reliance on any extra services but your email provider. If you're pairing this with Gmail, you can pretty well guarantee 100% uptime through them. As far as security goes, the data is sent over HTTPS/SSL to the SMTP server of your choice, which is encrypted as WPA2 traffic on your network, and stored quite securely with any name-brand email service!

**HOWEVER**, The credentials you input for WiFi and SMTP are stored away inside the ESP8266's filesystem, which could be read back if your ESP8266 is stolen by a stranger *who just-so-happens to know* how to access the SPIFFS filesystem on this type of microcontroller *and* knows that the credentials are in base64. Highly unlikely, but a possiblity. Be safe! Your smartphone being stolen is a much more likely and threatening scenario than this. I highly recommend creating an email account specifically for your ESP8266.

# Free SMS Capability

Most cell carriers are including unlimited text nowadays due to the focus being on data plans, so if you have a smartphone with a data plan, odds are that unlimited texts are already included in the cost! This is done through an Email-to-SMS portal provided by almost every carrier in the world. For example:

| Phone Number | Carrier | SMS Portal                         |
|--------------|---------|------------------------------------|
| 555-123-4567 | Verizon | 5551234567@vtext.com               |
| 123-456-7890 | AT&T    | 1234567890@txt.att.net             |
| 555-555-5555 | Sprint  | 5555555555@messaging.sprintpcs.com |

These special email addresses forward the mail recieved to the specified phone number!

**A list of over 200 supported worldwide carriers can be found at the bottom of this page:**  
https://martinfitzpatrick.name/list-of-email-to-sms-gateways/

----------
# Installation

~~**With Arduino Library Manager:**~~ **Coming soon!**

~~1. Open *Sketch > Include Library > Manage Libraries* in the Arduino IDE.~~
~~2. Search for "Volume", (look for "Connor Nishijima") and select the latest version.~~
~~3. Click the Install button and Arduino will prepare the library and examples for you!~~

**Manual Install:**

1. Click "Clone or Download" above to get an "AlertMe-master.zip" file.
2. Extract it's contents to the libraries folder in your sketchbook.
3. Rename the folder from "AlertMe-master" to just "AlertMe".

----------
# Dependencies

You'll need these two libraries already installed for AlertMe to work:

- **Arduino JSON**: https://github.com/bblanchon/ArduinoJson
- **WiFiManager**: https://github.com/tzapu/WiFiManager

----------
# Email Configuration

To send Email or SMS, you'll need to get SMTP access with your email provider. A quick Google search for "[Provider] SMTP port" will usually get you what you need. There's too many to cover here, so I'll go over Gmail usage:

SMTP Port: 465
SMTP Server: smtp.gmail.com
SMTP Email: **your Gmail address**
SMTP Password **your Gmail password**

**ALMOST DONE!**

These are the four inputs you need to enter on the AlertMe configuration hotspot, but you're not quite done yet. To allow your Gmail account to accept SMTP connections from your ESP8266, follow the steps of this instruction guide: https://support.google.com/accounts/answer/6010255

After you've entered your config info, and set up your Gmail account for SMTP access, be sure to reboot your ESP8266 and check that the configuration is saved!

***TIP**: place **alert.debug(true)** above **alert.connect()** and watch the Serial monitor for connection reports!*

----------
# Functions

**AlertMe alert**;

This initializes the AlertMe library after import. "alert" can be any word you want, as long as it's reflected in the rest of your code.

void **alert.connect**(bool **debug_wifi** = false);

When called, the underlying WiFiManager code first checks to see if there's a saved WiFi network to continue connecting to. If it can't, your ESP8266 will reconfigure as a hotspot named "AlertMe Configuration" and prompt you to enter your WiFi/SMTP credentials. (Once connected, visit http://192.168.4.1 in your browser to do this)

After a WiFi connection is established, AlertMe makes a test authorization with your email provider over SMTP. If it can't connect or authorize, AlertMe falls back to hosting the configuration hotspot again until this step is successful. **debug_wifi** can be enabled to see WiFiManager information output to Serial.

const char* **alert.send**(String **subject_line**, String **message**, String **destination**);

*This is where the magic happens.* This function sends an Email/SMS of **subject_line**/**message** to **destination**! If successful, the word "SENT" is returned. If not, an error message from SMTP is returned, such as "Could not connect to mail server".

void **alert.debug**(bool **enabled**);

When enabled, SMTP and filesystem debug information will be sent over Serial.

void **alert.config**();

Allows you to call up the config hotspot at all, a good practice would be adding this at the top of your setup() function:

    if(digitalRead(config_pin) == LOW){
        alert.config();
    }

void **alert.reset**(bool **format** == false);

Used to reset WiFi configuration, and delete saved SMTP credentials from the ESP8266. Good for if you're giving this microcontroller to someone else!

const char* **alert.get_error**();

Used to get the last SMTP error encountered, such as if you just used an alert.send() destined for an invalid email address.

----------
# Contributing
Any advice or pull requests are welcome. :)

----------
# License and Credits
**Developed for free by Connor Nishijima in response to a [proprietary cash-grab](https://www.tindie.com/products/pixeltwenty/add-text-and-email-alerts-to-anything/)**

**AlertMe includes modified code from these sources:**  
Borya's Gmail Sender: http://www.instructables.com/id/ESP8266-GMail-Sender/
Adam Rudd's arduino-base64: https://github.com/adamvr/arduino-base64

**Released under the [GPLv3 license](http://www.gnu.org/licenses/gpl-3.0.en.html).**
