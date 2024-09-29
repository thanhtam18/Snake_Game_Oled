#include "Arduino.h"

#define LOGO_HEIGHT   50
#define LOGO_WIDTH    50

const unsigned char icon [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xdf, 0xfc, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xdf, 0xfc, 0xff, 0xff, 
	0xff, 0xfe, 0xc0, 0xdb, 0x6c, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xdf, 0xfc, 0xff, 0xff, 0xff, 0xfe, 
	0xc0, 0xdf, 0xfc, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xcf, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xdf, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0xc0, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 
	0xdb, 0xff, 0xff, 0xff, 0xff, 0xf6, 0xc0, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xf6, 0xc0, 0xdb, 0xff, 
	0xff, 0xfe, 0x00, 0xf6, 0xc0, 0xdb, 0xff, 0xff, 0xfc, 0x00, 0xf6, 0xc0, 0xdb, 0xc3, 0xff, 0xfd, 
	0xb2, 0x76, 0xc0, 0xdb, 0x93, 0xff, 0xfc, 0x00, 0x76, 0xc0, 0xdb, 0x83, 0xff, 0xfc, 0x00, 0x76, 
	0xc0, 0xdb, 0xc7, 0xff, 0xfd, 0xb2, 0x76, 0xc0, 0xdb, 0xff, 0xc0, 0x00, 0x30, 0x76, 0xc0, 0xdb, 
	0xff, 0x80, 0x00, 0x30, 0x76, 0xc0, 0xdb, 0xff, 0x92, 0x6d, 0xb2, 0x76, 0xc0, 0xdb, 0xff, 0x80, 
	0x00, 0x30, 0x76, 0xc0, 0xdb, 0xff, 0x80, 0x00, 0x70, 0x76, 0xc0, 0xdb, 0xff, 0x93, 0xff, 0xf2, 
	0x76, 0xc0, 0xdb, 0xff, 0x83, 0xff, 0xf0, 0x76, 0xc0, 0xdb, 0xff, 0x83, 0xff, 0xf0, 0xf6, 0xc0, 
	0xdb, 0xff, 0x93, 0xff, 0xff, 0xf6, 0xc0, 0xdb, 0xff, 0x93, 0xff, 0xff, 0xf6, 0xc0, 0xdb, 0x00, 
	0x03, 0xff, 0xfd, 0xf6, 0xc0, 0xdb, 0x24, 0x93, 0xff, 0xf0, 0xf6, 0xc0, 0xdb, 0x24, 0x93, 0xff, 
	0xf2, 0x76, 0xc0, 0xdb, 0x00, 0x07, 0xff, 0xf0, 0xf6, 0xc0, 0xdb, 0xff, 0xff, 0xff, 0xf8, 0xf6, 
	0xc0, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xf6, 0xc0, 0xd9, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xc0, 0xd8, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xdf, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0xc0, 0xd8, 0x00, 0x7f, 0xff, 0xff, 0xb6, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};