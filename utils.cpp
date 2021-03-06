#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/time.h>

#include "utils.h"

using namespace std;

void hex_dump( const void *address, uint16_t length)
{
    if (length == 0xffff)
        abort();

	char linebuf[80];
	char *p, *q, *hex, *chars;
   unsigned char ch;
   uint16_t i;
   const char *data = static_cast<const char*>(address);

   hex = linebuf;
   // start printing ASCII characters at position <chars>
   chars = hex + (16 * 3 + 3);

   for(i = 0; i < length; )
   {
   	p = hex;
   	q = chars;
      do {
      	ch = *data++;
      	if ((i & 15) == 8)
      	{
      		// insert space between two sets of 8 bytes
				*p++ = ' ';
				*q++ = ' ';
      	}
      	p[0] = "0123456789abcdef"[ch >> 4];
      	p[1] = "0123456789abcdef"[ch & 0x0F];
      	p[2] = ' ';
      	p += 3;
         *q++ = isprint(ch) ? ch : '.';
      } while ((++i < length) && (i & 15));
		// add missing spaces between hex and printed chars
		memset( p, ' ', chars - p);
			*q = '\0';								// null terminate ASCII characters
			puts( linebuf);
   }
}

string getTime()
{
    timeval tv;
    gettimeofday(&tv, 0);

    stringstream ss;
    ss << tv.tv_sec << "." << tv.tv_usec;

    return ss.str();
}
