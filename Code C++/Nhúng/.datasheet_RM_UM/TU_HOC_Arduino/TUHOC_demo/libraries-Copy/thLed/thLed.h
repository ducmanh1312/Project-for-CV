/*

TUHOC - thLed library

History

version 1.0 - 150226
  Initial release - quang.dinh@dtt.vn

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#ifndef THLED_H
#define THLED_H

#include "Arduino.h"

#define LED_OFF 0
#define LED_ON  1

class thLedClass 
{
  public:
    static void begin(byte SDI, byte SCK, byte RCK);
    static void begin(byte SDI, byte SCK, byte RCK, byte numModules);
    static void begin(byte SDI, byte SCK, byte RCK, byte numModules, boolean autoUpdate);
    	
    static void setBitmap(byte module, byte bitmap);
    
    static void setLed(byte pos, byte state);
	  
    static void clearAll();
       
    static void update();
};

extern thLedClass thLed;

#define  AUTO_UPDATE    (true)
#define  MANUAL_UPDATE  (false)

#endif
