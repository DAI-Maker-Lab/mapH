#define VERSION 0.1
#define PASTEBINKEY   "b711cd2e1b2e5f08fa4f2f51c538dd6e"
#define PASTEBINUSER  "3189ffc48fa57d26e80f53382b156557"
#define UTCOFFSET   -6

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

#include <Adafruit_FONA.h>    //  https://github.com/adafruit/Adafruit_FONA
#include <SoftwareSerial.h>   //  Standard software serial library

#define BUTTON 2              //  Button to send reading
#define FONA_PS 5             //  FONA power status pin
#define FONA_KEY 6            //  FONA Key pin
#define FONA_TX 7             //  UART pin from FONA
#define FONA_RX 8             //  UART pin to FONA
#define FONA_RST 9            //  FONA reset pin
#define GREEN 10              //  Green status LED
#define RED 11                //  Red status LED
#define PH_PIN A0             //  pH reading from DFRobot unit

boolean buttonPressed = false;
boolean fix = false;
unsigned long tick = 0;
unsigned long cadence = 10000;  //  ms between position updates

float latitude;
float longitude;

Adafruit_FONA fona = Adafruit_FONA (FONA_RST);
SoftwareSerial fonaSerial = SoftwareSerial (FONA_TX, FONA_RX);



static void buttonPress() {
  if(fix == true) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);
    buttonPressed = true;
  }
}



void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(FONA_KEY, OUTPUT);
  pinMode(FONA_RX, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);

  Serial.begin(57600);
  Serial.print(F("mapH v"));
  Serial.println(VERSION);
  Serial.print(__DATE__);   //  Compile data and time helps identify software uploads
  Serial.print(F(" "));
  Serial.println(__TIME__);

  fonaOn();

  fona.enableGPS(true);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress, FALLING);
  interrupts();
}



void loop() {
  if(millis() > tick) {
    if(fona.GPSstatus() < 2) {
      fix = false;
    } else {
      fix = true;
    }
    tick = millis() + cadence;
  }

  //fix = true;     //  For indoor debugging

  if(buttonPressed == true) {
    sendReading();
    buttonPressed = false;
  }

  if(fix == true) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  } else {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }
}



boolean fonaOn() {
  if(digitalRead(FONA_PS) == LOW) {        //  If the FONA is off...
    Serial.print(F("Powering FONA on..."));
    while (digitalRead(FONA_PS) == LOW) {
      digitalWrite(FONA_KEY, LOW);  //  ...pulse the Key pin low...
      wait(500);
    }
    digitalWrite(FONA_KEY, HIGH);        //  ...and then return it to high
    Serial.println(F(" done."));
  }
  
  Serial.println(F("Initializing FONA..."));
  
  fonaSerial.begin(4800);                      //  Open a serial interface to FONA
  
  if(fona.begin(fonaSerial) == false) {        //  Start the FONA on serial interface
    Serial.println(F("FONA not found. Check wiring and power."));
    return false;
  } else {
    Serial.print(F("FONA online. "));
    
    unsigned long gsmTimeout = millis() + 30000;
    boolean gsmTimedOut = false;

    Serial.print(F("Waiting for GSM network... "));
    while(1) {
      byte network_status = fona.getNetworkStatus();
      if(network_status == 1 || network_status == 5) break;
      
      if(millis() >= gsmTimeout) {
        gsmTimedOut = true;
        break;
      }
      wait(250);
    }

    if(gsmTimedOut == true) {
      Serial.println(F("timed out. Check SIM card, antenna, and signal."));
      return false;
    } else {
      Serial.println(F("done."));
    }

    //  RSSI is a measure of signal strength -- higher is better; less than 10 is worrying
    byte rssi = fona.getRSSI();
    Serial.print(F("RSSI: "));
    Serial.println(rssi);

    wait(3000);    //  Give the network a moment

    //fona.setGPRSNetworkSettings(F("hologram"));    //  Set APN to your local carrier

    if(rssi > 5) {
      if(fona.enableGPRS(true) == false) {
        //  Sometimes enableGPRS() returns false even though it succeeded
        if(fona.GPRSstate() != 1) {
          for(byte GPRSattempts = 0; GPRSattempts < 5; GPRSattempts++) {
            Serial.println(F("Trying again..."));
            wait(2000);
            fona.enableGPRS(true);
            
            if(fona.GPRSstate() == 1) {
              Serial.println(F("GPRS is on."));
              break;
            } else {
              Serial.print(F("Failed to turn GPRS on... "));
            }
          }
        }
      }
    }
    else {
      Serial.println(F("Can't transmit, network signal strength is poor."));
      gsmTimedOut = true;
    }

    clockSet();
    
    return true;
  }
}



void flushFona() {
  // Read all available serial input from FONA to flush any pending data.
  while(fona.available()) {
    char c = fona.read();
    Serial.print(c);
  }
}



void fonaOff() {
  wait(5000);        //  Shorter delays yield unpredictable results

  //  We'll turn GPRS off first, just to have an orderly shutdown
  if(fona.enableGPRS(false) == false) {
    if(fona.GPRSstate() == 1) {
      Serial.println(F("Failed to turn GPRS off."));
    } else {
      Serial.println(F("GPRS is off."));
    }
  }

  wait(500);

  // Power down the FONA if it needs it
  if(digitalRead(FONA_PS) == HIGH) {     //  If the FONA is on...
    fona.sendCheckReply(F("AT+CPOWD=1"), F("OK")); //  ...send shutdown command...
    digitalWrite(FONA_KEY, HIGH);                  //  ...and set Key high
  }
}



void wait(unsigned int ms) { //  Non-blocking delay function
  unsigned long period = millis() + ms;
  while(millis() < period) {
    Serial.flush();
  }
}



boolean sendReading() {
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  
  char timeBuffer[23];
  uint8_t timestamp[7];
  float speed_kph, heading, speed_mph, altitude;

  fona.getTime(timeBuffer, 23);
  fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);

  int i = 0;

  char *token;
  token = strtok(timeBuffer, " ,\"/.:-");
  while(token != NULL) {
    timestamp[i] = atoi(token);
    i++;
    token = strtok(NULL, " ,\"/.:-");
  }
  
  float pH = takeReading();

  char data[200];

  char latChar[10];
  char lonChar[10];
  char phChar[10];

  dtostrf(latitude, 8, 4, latChar);
  dtostrf(longitude, 8, 4, lonChar);
  dtostrf(pH, 5, 2, phChar);

  //  Construct the body of the POST request:
  if(timestamp[4] < 10) {   //  Add a leading zero if necessary
    sprintf(data, "api_dev_key=%s&api_user_key=%s&&api_option=paste&api_paste_code={\"lat\":\"%s\",\"lon\":\"%s\",\"pH\":\"%s\",\"timestamp\":\"%d/%d/%d %d:0%d\"}\r\n", PASTEBINKEY, PASTEBINUSER, latChar, lonChar, phChar, timestamp[0], timestamp[1],timestamp[2],timestamp[3],timestamp[4]);
  } else {
    sprintf(data, "api_dev_key=%s&api_user_key=%s&&api_option=paste&api_paste_code={\"lat\":\"%s\",\"lon\":\"%s\",\"pH\":\"%s\",\"timestamp\":\"%d/%d/%d %d:%d\"}\r\n", PASTEBINKEY, PASTEBINUSER, latChar, lonChar, phChar, timestamp[0], timestamp[1],timestamp[2],timestamp[3],timestamp[4]);
  }
  
  //  The stock fona.HTTP_POST_start FONA library sequence was working from the US but 
  //  not on the Cellcard network in Cambodia, so we'll construct the sequence ourselves:
  
  fona.sendCheckReply (F("AT+HTTPTERM"), F("OK"));
  fona.sendCheckReply (F("AT+HTTPINIT"), F("OK"));
  fona.sendCheckReply (F("AT+HTTPPARA=\"CID\",1"), F("OK"));
  fona.sendCheckReply (F("AT+HTTPPARA=\"UA\",\"FONA\""), F("OK"));
  fona.sendCheckReply (F("AT+HTTPPARA=\"URL\",\"pastebin.com/api/api_post.php\""), F("OK"));
  fona.sendCheckReply(F("AT+HTTPSSL=1"), F("OK"));    //  Pastebin requires SSL
  fona.HTTP_para (F("CONTENT"), F("application/x-www-form-urlencoded"));
  
  Serial.print (F("AT+HTTPDATA="));
  Serial.print (strlen (data));
  Serial.println (F(",10000"));
  
  fona.print (F("AT+HTTPDATA="));
  fona.print (strlen (data));
  fona.println (F(",10000"));
  fona.expectReply (F("DOWNLOAD"));
  
  Serial.println (data);
  fona.println (data);
  fona.expectReply (F("OK"));

  int method = 0;
  int statuscode = 0;
  int length = 0;
  
  fona.sendCheckReply (F("AT+HTTPACTION=1"), F("OK"));
  fona.readStringUntil (": ");

  //  For reasons that are not clear, AT+HTTPACTION in this context is returning an 
  //  inconsistent number of zeroes before starting the METHOD,STATUS,LENGTH sequence.
  //  We'll ignore any initial zeroes since we're executing a POST command (1).
  
  while (method == 0)
  {
    method = fona.parseInt();
  }
  
  statuscode = fona.parseInt();
  length = fona.parseInt();

  Serial.print (F("Status Code: "));
  Serial.println (statuscode);
  Serial.print (F("Length: "));
  Serial.println (length);
          
  fona.HTTP_POST_end();

  if (statuscode == 200)
  {
    Serial.println (F("Upload succeeded."));
    return true;
  }
  else
  {
    Serial.println (F("Upload appeared to fail."));
    return false;
  }
}



float takeReading() {
  boolean red = false;
  boolean green = true;

  int sampleSize = 100;
  unsigned long pHreading = 0;
  
  for(int i = 0; i < sampleSize; i++) {
    digitalWrite(RED, red);
    digitalWrite(GREEN, green);
    pHreading += analogRead(PH_PIN);
    wait(100);
    red != red;
    green != green;
  }

  pHreading = pHreading / sampleSize;    //  Average the readings
  float voltage = pHreading * (5.0 / 1023.0);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);

  return 3.5 * voltage;
}



void clockSet() {
  wait(1000);    //  Give time for any trailing data to come in from FONA

  fona.enableRTC(true);

  int netOffset;

  char theDate[17];

  Serial.println(F("Attempting to get time from GSM location service..."));

  flushFona();    //  Flush any trailing data

  fona.sendCheckReply(F("AT+CIPGSMLOC=2,1"), F("OK"));    //  Query GSM location service for time
  
  fona.parseInt();                    //  Ignore first int
  int secondInt = fona.parseInt();    //  Ignore second int -- necessary on some networks/towers
  int netYear = fona.parseInt();      //  Get the results -- GSMLOC year is 4-digit
  int netMonth = fona.parseInt();
  int netDay = fona.parseInt();
  int netHour = fona.parseInt();      //  GSMLOC is _supposed_ to get UTC; we will adjust
  int netMinute = fona.parseInt();
  int netSecond = fona.parseInt();    //  Our seconds may lag slightly, of course

  if(netYear < 2016 || netYear > 2050 || netHour > 23) { //  If that obviously didn't work...
    netSecond = netMinute;  //  ...shift everything up one to capture that second int
    netMinute = netHour;
    netHour = netDay;
    netDay = netMonth;
    netMonth = netYear;
    netYear = secondInt;

    Serial.println(F("Recombobulating..."));
  }

  if(netYear < 2016 || netYear > 2050 || netHour > 23) {   // If that still didn't work...
    Serial.println(F("GSM location service failed."));
    /*   ...the we'll get time from the NTP pool instead: 
     *  (https://en.wikipedia.org/wiki/Network_Time_Protocol)
     */
    fona.enableNTPTimeSync(true, F("0.daimakerlab.pool.ntp.org"));
    Serial.println(F("Attempting to enable NTP sync."));
    
    wait(15000);                 // Wait for NTP server response
    
    fona.println(F("AT+CCLK?")); // Query FONA's clock for resulting NTP time              
    netYear = fona.parseInt();    // Capture the results
    netMonth = fona.parseInt();
    netDay = fona.parseInt();
    netHour = fona.parseInt();    // We asked NTP for UTC and will adjust below
    netMinute = fona.parseInt();
    netSecond = fona.parseInt();  // Our seconds may lag slightly
  }

  if((netYear < 1000 && netYear >= 16 && netYear < 50) || (netYear > 1000 && netYear >= 2016 && netYear < 2050)) {
  //  If we got something that looks like a valid date...
    //  Adjust UTC to local time
    if((netHour + UTCOFFSET) < 0) {           //  If our offset + the UTC hour < 0...
      netHour = (24 + netHour + UTCOFFSET);   //  ...add 24...
      netDay = (netDay - 1);                  //  ...and adjust the date to UTC - 1
    } else {
      if((netHour + UTCOFFSET) > 23) {        //  If our offset + the UTC hour > 23...
        netHour = (netHour + UTCOFFSET - 24); //  ...subtract 24...
        netDay = (netDay + 1);                //  ...and adjust the date to UTC + 1
      } else {
        netHour = (netHour + UTCOFFSET);      //  Otherwise it's straight addition
      }
    }

    Serial.print(F("Obtained current time: "));
    sprintf(theDate, "%d/%d/%d %d:%d", netDay, netMonth, netYear, netHour, netMinute);
    Serial.println(theDate);

    //setTime(netHour, netMinute, netSecond, netDay, netMonth, netYear);   //set the system time to 23h31m30s on 13Feb2009
  } else {
    Serial.println(F("Didn't find reliable time. Will continue to use RTC's current time."));
  }

  wait(200);              //  Give FONA a moment to catch its breath
}
