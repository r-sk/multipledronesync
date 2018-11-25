#include <Arduino.h>
#include "rashikMSP.h"

void MSP::begin(Stream& stream, uint32_t timeout)
{
  _stream = &stream;
  _timeout = timeout;
}

void MSP::command(uint8_t msgID, void * payload, uint8_t size)
{
  _stream->write('$');
  _stream->write('M');
  _stream->write('<');
  _stream->write(size);
  
  _stream->write(msgID);
  uint8_t checksum = size ^ msgID;
  
  uint8_t * payloadPtr = (uint8_t*)payload;
  
  for (uint8_t i = 0; i < size; ++i)
  {
    uint8_t b = *(payloadPtr++);
    checksum ^= b;
    _stream->write(b);
  }
  
  _stream->write(checksum);
}

void MSP::request(uint8_t msgID)
{
  _stream->write('$');
  _stream->write('M');
  _stream->write('<');
  _stream->write((uint8_t)0);
  
  _stream->write(msgID);
  uint8_t checksum = msgID;
  
  _stream->write(checksum);

 // Serial.println("Request sent");
}

uint8_t MSP::response(void * payload)
{
    uint8_t header[3];
    uint8_t msgID;

    if( _stream->available() )
    {
       _stream->readBytes((uint8_t*)header, 3);

       if (header[0] == '$' && header[1] == 'M' && header[2] == '>')
       {
          uint8_t size = _stream->read();
          msgID = _stream->read();

          uint8_t * payloadPtr = (uint8_t*)payload;

          //Serial.println("Now reading payloads" );
          
          _stream->readBytes(payloadPtr, size);

          uint8_t checksum = _stream->read();      
    
       }
       else
          Serial.println(" X X X X X Corrupted Data X X X X X");
    }

    
    _stream->flush();

    return msgID;
}

void MSP::check()
{
  uint8_t dataa[100]; 
  uint8_t bufsize = _stream->available();
  
  Serial.print("Buffer size: " + String(bufsize) + "\t" );

  _stream->readBytes((uint8_t*)dataa, bufsize);

  for(int i = 0; i<bufsize; i++)
  {
    if( i <3)   Serial.print( (char)(dataa[i] ) );
    else        Serial.print( dataa[i]  );
    
    Serial.print("\t"); 
  }

  Serial.println(); 
}


void MSP::set_raw_rc(rc_struct rc)
{
  data[0] = (rc.roll & 0x00FF);
  data[1] = (rc.roll & 0xFF00) >> 8;

  data[2] = (rc.pitch & 0x00FF);
  data[3] = (rc.pitch & 0xFF00) >> 8;

  data[4] = (rc.throttle & 0x00FF);
  data[5] = (rc.throttle & 0xFF00) >> 8;

  data[6] = (rc.yaw & 0x00FF);
  data[7] = (rc.yaw & 0xFF00) >> 8;

  data[8] = (rc.aux1 & 0x00FF);
  data[9] = (rc.aux1 & 0xFF00) >> 8;

  data[10] = (rc.aux2 & 0x00FF);
  data[11] = (rc.aux2 & 0xFF00) >> 8;

  data[12] = (rc.aux3 & 0x00FF);
  data[13] = (rc.aux3 & 0xFF00) >> 8;

  data[14] = (rc.aux4 & 0x00FF);
  data[15] = (rc.aux4 & 0xFF00) >> 8;

  command(SET_RAW_RC, data, sizeof(rc));
  
}

orientation MSP::get_orientation()
{
  orientation o;
  int16_t y;
  int16_t p;
  int16_t r;

  uint8_t respond_ID;

  request(MSP_ATTITUDE);
  respond_ID = response( r_data);

//  check();
      
  o.yaw = 5; o.pitch = 5; o.roll = 5;
  

  r = r_data[0] | (r_data[1] << 8);
  p = r_data[2] | (r_data[3] << 8);
  y = r_data[4] | (r_data[5] << 8);
  

  o.yaw = y/1.0;
  o.pitch = p/10.0;
  o.roll = r/10.0;
  
  return o;
  
}
