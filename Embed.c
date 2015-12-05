/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * Stego.c: A program for manipulating images                           *
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
void setlsbs(unsigned char *p, unsigned char b0, int iterator);
int main(int argc, char *argv[])
{
  int i, j, k, cover_bits, bits;
  struct Buffer b = {NULL, 0, 0};
  struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
  struct Image covImg = {0, NULL, NULL, NULL, NULL, 0, 0};
  char *s;
  byte b0;
   
  if (argc != 4) 
    {
      printf("\n%s <cover_file> <stego_file> <file_to_hide> \n", argv[0]);
      exit(1);
    }
  ReadImage(argv[1],&img);       // read image file into the image buffer img
                                 // the image is an array of unsigned chars (bytes) of NofR rows
                                 // NofC columns, it should be accessed using provided macros
  ReadBinaryFile(argv[3],&b);     // Read binary data
  s = strchr(argv[3],(int)'.');
  if (strlen(s)!=4) s = ".txt";
  printf("hidden file type = <%s>\n",s+1);

  // hidden information 
  // first two bytes is the size of the hidden file
  // next 4 bytes is the extension (3 letters & \0)
  if (!GetColor)
    cover_bits = img.NofC*img.NofR;
  else 
    cover_bits = 3*img.NofC*img.NofR;    
  bits = (6+b.size)*8;
  if (bits > cover_bits)
    {
      printf("Cover file is not large enough %d (bits) > %d (cover_bits)\n",bits,cover_bits);
      exit(1);
    }
  // embed two size bytes
  // 
  //
  printf("b.size is: %d\n", b.size);
	//Create array that will hold the two least significant bytes of b.size.
	unsigned char data[4];
	//Assign bytes using bitwise operators 
	data[0] = (unsigned char) b.size;
	data[1] = (unsigned char) (b.size >> 8);
	//set LSbs of the image usign setlsbs
	setlsbs(img.gray, data[0], 0);
	setlsbs(img.gray, data[1], 1);
	// embed 4 file extension characters (to make it easy for the extraction)
	for(i = 0; i<strlen(s); i++)
	{
		setlsbs(img.gray, s[i], i+2);
	}  
  for (i=0; i<b.size; i++)
    {
      // here you embed information into the image one byte at the time
      // note that you should change only the least significant bits of the image
		setlsbs(img.gray, GetByte(i), i+6);
    }

  WriteImage(argv[2],img);  // output stego file (cover_file + file_to_hide)
}
//Added iterator argument to allow to pick which eight bytes to hide b0 in
void setlsbs(unsigned char *p, unsigned char b0, int iterator)
{
	int modBitIter = iterator*8;
	int bits[8];
	bits[0] =  (b0 & 0x01 ? 1 : 0);
	bits[1] =  (b0 & 0x02 ? 1 : 0);
	bits[2] =  (b0 & 0x04 ? 1 : 0);
	bits[3] = (b0 & 0x08 ? 1 : 0);
	bits[4] = (b0 & 0x10 ? 1 : 0);
	bits[5] = (b0 & 0x20 ? 1 : 0);
	bits[6] = (b0 & 0x40 ? 1 : 0);
	bits[7] = (b0 & 0x80 ? 1 : 0);
	int i;
	for(i=0; i<8; i++)
	{
		//check the LSB of the element in the array and the bit of b0.
		//If LSB == 0 && b0 == 1, left shifting LSB gets 1.
		//If LSB == 1 && b0 == 0, XOR left shifting will nullify the 1 giving 0.
		if ((p[modBitIter]& 0x01 ? 1 : 0))
		{
			if(!bits[i])
				p[modBitIter] ^= (1 << 0);
		}
		else
		{
			if (bits[i])
				p[modBitIter] ^= (1 << 0);
		}
		modBitIter++;
	}
}
