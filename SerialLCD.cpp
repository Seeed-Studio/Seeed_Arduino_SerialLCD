/*
 * SerialLCD.cpp
 * Serial LCD driver Library
 *
 * Copyright (c) 2010 seeed technology inc.
 * Author        :   Jimbo.We
 * Contribution  :   Visweswara R 
 * Create Time   :   Dec 2010
 * Change Log    :   Modified 15 March,2012 for Arduino 1.0 IDE by Frankie.Chu
 *  
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SerialLCD.h"

SerialLCD::SerialLCD(uint8_t rx, uint8_t tx):SoftwareSerial(rx,tx)
{

}

/********** High level commands, for the user! **********/

// Initialize the Serial LCD Driver. SerialLCD Module initiates the communication.
void SerialLCD::begin()
{
    SoftwareSerial::begin(9600);
    /*while(1)
    {
        if ( SoftwareSerial::available() > 0 &&  SoftwareSerial::read()==SLCD_INIT )
        {
            SoftwareSerial::write(SLCD_INIT_ACK);
            break;
        }
    }*/
    delay(2);
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_POWER_OFF); 
    delay(1);
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_POWER_ON);
    delay(1);
    SoftwareSerial::write(SLCD_INIT_ACK);
    while(1)
    {
        if (SoftwareSerial::available() > 0 &&SoftwareSerial::read()==SLCD_INIT_DONE)
            break;
    }
    delay(2);
}

// Clear the display
void SerialLCD::clear()
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_CLEAR_DISPLAY);   
}

// Return to home(top-left corner of LCD)
void SerialLCD::home()
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_RETURN_HOME);  
    delay(2);//this command needs more time;  
}

// Set Cursor to (Column,Row) Position
void SerialLCD::setCursor(uint8_t column, uint8_t row)
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER); 
    SoftwareSerial::write(SLCD_CURSOR_HEADER); //cursor header command
    SoftwareSerial::write(column);
    SoftwareSerial::write(row);
}

// Switch the display off without clearing RAM
void SerialLCD::noDisplay() 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_DISPLAY_OFF);    
}

// Switch the display on
void SerialLCD::display() 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_DISPLAY_ON);    
}

// Switch the underline cursor off
void SerialLCD::noCursor() 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_CURSOR_OFF);     
}

// Switch the underline cursor on
void SerialLCD::cursor() 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_CURSOR_ON);     
}

// Switch off the blinking cursor
void SerialLCD::noBlink() 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_BLINK_OFF);     
}

// Switch on the blinking cursor
void SerialLCD::blink() 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_BLINK_ON);     
}

// Scroll the display left without changing the RAM
void SerialLCD::scrollDisplayLeft(void) 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_SCROLL_LEFT);
}

// Scroll the display right without changing the RAM
void SerialLCD::scrollDisplayRight(void) 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_SCROLL_RIGHT);
}

// Set the text flow "Left to Right"
void SerialLCD::leftToRight(void) 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_LEFT_TO_RIGHT);
}

// Set the text flow "Right to Left"
void SerialLCD::rightToLeft(void) 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_RIGHT_TO_LEFT);
}

// This will 'right justify' text from the cursor
void SerialLCD::autoscroll(void) 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_AUTO_SCROLL);
}

// This will 'left justify' text from the cursor
void SerialLCD::noAutoscroll(void) 
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);
    SoftwareSerial::write(SLCD_NO_AUTO_SCROLL);
}
void SerialLCD::Power(void)
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_POWER_ON); 
}
void SerialLCD::noPower(void)
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_POWER_OFF); 
}
//Turn off the backlight
void SerialLCD::noBacklight(void)
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_BACKLIGHT_OFF);   
}
//Turn on the back light
void SerialLCD::backlight(void)
{
    SoftwareSerial::write(SLCD_CONTROL_HEADER);   
    SoftwareSerial::write(SLCD_BACKLIGHT_ON);   
}
// Print Commands

void SerialLCD::print(uint8_t b)
{
    SoftwareSerial::write(SLCD_CHAR_HEADER);
    SoftwareSerial::write(b);
}
void SerialLCD::print(const char b[])
{
    SoftwareSerial::write(SLCD_CHAR_HEADER);
    SoftwareSerial::write(b);
}

void SerialLCD::print(unsigned long n, uint8_t base)
{
    unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
    unsigned long i = 0;

    if (base == 0) print(n);

    else if(base!=0)
    {
        if (n == 0) {
            print('0');
            return;
        }

        while (n > 0) {
            buf[i++] = n % base;
            n /= base;
        }

        for (; i > 0; i--)
            print((char) (buf[i - 1] < 10 ?
                          '0' + buf[i - 1] :
                          'A' + buf[i - 1] - 10));
    }
}
