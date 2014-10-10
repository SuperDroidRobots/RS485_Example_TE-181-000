//=========================HEADER=============================================================
/*
   RS485 Example Code (Tx) for the TE-181-000 ST485 Breakout
   AUTHOR: Jason Traud
   DATE: October 10, 2014
   
   This is a simple test program to send arbitrary data (an incremental number)
   over RS-485 to a reciever using the ST485 Breakout, which is part number TE-181-000
                                                       
   Please see the link below for additional information and datasheets:
   http://www.superdroidrobots.com/shop/item.aspx/rs485-breakout-board/1522/
   
   Hardware: Arduino Uno R3       (MCU-050-000)
             RS485 Breakout Board (TE-181-000)
           
   
   RS485 Breakout     -------------      Arduno Uno
   -----------------                    -------
            DI     -------------------   Tx / D1   
            DE     -------------------   D2       
            !RE    -------------------   D2 *     
            RO     -------------------   Rx / D0 
            +5V    -------------------   Vcc (+5V)
            GND    -------------------   GND
                                                   
    *NOTE: The solder jumper can be populated to control the data and recieve
           enable pins with a single wire.    
			
   License: CCAv3.0 Attribution-ShareAlike (http://creativecommons.org/licenses/by-sa/3.0/)
   You're free to use this code for any venture. Attribution is greatly appreciated. 

//============================================================================================
*/

// Our hardware pin to control the direction for the RS-485 bus
#define RS485_EN 2

// Our counter that we're using as our dummy data to send
unsigned char counter = 0;


void setup() {
  Serial.begin(57600);            // We're communicating over the hardware UART
  pinMode(RS485_EN, OUTPUT);      // Declares our enable pin as an output
  digitalWrite(RS485_EN, HIGH);   // Sets the output high to put us in transmit mode
}

void loop() {
  
  digitalWrite(RS485_EN, HIGH);  // 1. Raise the enable line to put us in Tx mode
  delay(5);                      // 2. A slight delay to be sure the enable line is high before we transmit
  Serial.write(counter);         // 3. Send our data
  delay(3);                      // 4. A slight delay so that our final bits leave the ST485 before we move to Rx mode
  digitalWrite(RS485_EN, LOW);   // 5. End the conversation, and switch to Rx mode
  
  // Slow ourselves down a bit
  delay(200);
  
  // Increment our data and loop it back to 0 before an
  // overflow occurs
  counter = counter + 1;
  if (counter > 250)
    counter = 0;
}
