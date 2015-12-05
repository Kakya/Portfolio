/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*//*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * StegoExtract.c: A program for Extracting binary files                           *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"

#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 

#define PRINTBIN(x)  printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));
unsigned char getlsbs(unsigned char *p, int iterator);
int main(int argc, char *argv[])
{
	//Initialize variables used to extract the payloads.
	unsigned char result1, result2; 
	int origResult;
	struct Buffer b = {(byte *)malloc(sizeof(byte)*MIN_BUFFER_SIZE), 0, 0};
	struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
	ReadImage(argv[1], &img);
	//Get the size of the file from the first two bytes of the Stego image.
	result1 = getlsbs(img.gray, 0);
	result2 = getlsbs(img.gray, 1);	
	//Merge them using bitwise operators.
	origResult = (result1+(result2<<8));
	b.size = origResult;
	b.max_size = MIN_BUFFER_SIZE;
	char s[4];
	int i;
	//Reverse the method of encrypting the extension of the file.
	for(i=0; i<4; i++)
	{
		s[i] = getlsbs(img.gray, i+2);
	}
	char data[b.size];
	for (i=0; i<b.size; i++)
    {
      //Reverse Process of Stego to retrieve the data hidden inside the image.
	  SetByte(i, ((byte)getlsbs(img.gray, i+6)));
    }
	WriteBinaryFile(argv[2], b);
}
unsigned char getlsbs(unsigned char *p, int iterator)
{
	unsigned char result;
	result = 0;
	int modBitIter = iterator*8;
	int i;
	int bits[8];
	bits[0] =  (result & 0x01 ? 1 : 0);
	bits[1] =  (result & 0x02 ? 1 : 0);
	bits[2] =  (result & 0x04 ? 1 : 0);
	bits[3] = (result & 0x08 ? 1 : 0);
	bits[4] = (result & 0x10 ? 1 : 0);
	bits[5] = (result & 0x20 ? 1 : 0);
	bits[6] = (result & 0x40 ? 1 : 0);
	bits[7] = (result & 0x80 ? 1 : 0);
	
	for(i=0; i<8; i++)
	{
		if ((p[modBitIter]& 0x01 ? 1 : 0))
		{
			if(!bits[i])
				result ^= (1 << i);
		}
		else
		{
			if (bits[i])
				result ^= (1 << i);
		}
		modBitIter++;
	}
	return result;
}
