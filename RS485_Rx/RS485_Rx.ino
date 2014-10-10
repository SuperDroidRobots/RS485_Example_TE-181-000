//=========================HEADER=============================================================
/*
   RS485 Example Code (Rx) for the TE-181-000 ST485 Breakout
   AUTHOR: Jason Traud
   DATE: October 10, 2014
   
   This is a simple test program to recieve arbitrary data (an incremental number)
   over RS-485 to a reciever using the ST485 Breakout, which is part number TE-181-000
                                                       
   Please see the link below for additional information and datasheets:
   http://www.superdroidrobots.com/shop/item.aspx/rs485-breakout-board/1522/
   
   Hardware: Arduino Mega R3      (MCU-049-000)
             RS485 Breakout Board (TE-181-000)
           
   
   RS485 Breakout     -------------      Arduno Uno
   -----------------                    -------
            DI     -------------------   Tx1 / D14   
            DE     -------------------   D2       
            !RE    -------------------   D2 *     
            RO     -------------------   Rx1 / D15 
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

// Recieved data from the RS-485 transicever 
unsigned char rxByte;

// Timeout counter
unsigned int counter = 0;

void setup() {
  Serial.begin(57600);
  Serial1.begin(57600);
  pinMode(RS485_EN, OUTPUT);
  digitalWrite(RS485_EN, LOW);
}

void loop() {
  
  // Check for available packets from serial port 1
  if (Serial1.available() > 0) {
    rxByte = Serial1.read();    // If we have a packet, read it and store it
    Serial.println(rxByte);     // Print the data to the serial monitor
    counter = 0;                // Reset our counter
  }
  
  // If we do not have data waiting in our buffer, then we need to
  // increment our timeout counter and display a prompt when we've
  // sufficiently timed out
  else {
    counter = counter + 1;
    if (counter > 50000) {
      Serial.println("[nd]");
      counter = 0;
    }
  }   
}
