// stdafx.cpp : source file that includes just the standard includes
//	Dialg.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



DWORD HEXS(char *decString)
{
	DWORD hexValue=0;
	DWORD sl=0;
	BOOL isWhile=FALSE;
	DWORD idx=0;
	char str[256];
	BYTE ct=0;

	sl=strlen(decString);
	if((sl>0) && (sl<256))
		isWhile=TRUE;
	strcpy(str,decString);
	idx=0;
	while(isWhile)
	{
		ct=(BYTE)(str[idx]);
		switch(ct)
		{
		case 48: // "0"
			hexValue=hexValue<<4;
			hexValue+=0x0;
			break;
		case 49: // "1"
			hexValue=hexValue<<4;
			hexValue+=0x01;
			break;
		case 50: // "2"
			hexValue=hexValue<<4;
			hexValue+=0x02;
			break;
		case 51: // "3"
			hexValue=hexValue<<4;
			hexValue+=0x03;
			break;
		case 52: // "4"
			hexValue=hexValue<<4;
			hexValue+=0x04;
			break;
		case 53: // "5"
			hexValue=hexValue<<4;
			hexValue+=0x05;
			break;
		case 54: // "6"
			hexValue=hexValue<<4;
			hexValue+=0x06;
			break;
		case 55: // "7"
			hexValue=hexValue<<4;
			hexValue+=0x07;
			break;
		case 56: // "8"
			hexValue=hexValue<<4;
			hexValue+=0x08;
			break;
		case 57: // "9"
			hexValue=hexValue<<4;
			hexValue+=0x09;
			break;
		case 65: // "A"
			hexValue=hexValue<<4;
			hexValue+=0x0a;
			break;
		case 97: // "a"
			hexValue=hexValue<<4;
			hexValue+=0x0a;
			break;
		case 66: // "B"
			hexValue=hexValue<<4;
			hexValue+=0x0b;
			break;
		case 98: // "b"
			hexValue=hexValue<<4;
			hexValue+=0x0b;
			break;
		case 67: // "C"
			hexValue=hexValue<<4;
			hexValue+=0x0c;
			break;
		case 99: // "c"
			hexValue=hexValue<<4;
			hexValue+=0x0c;
			break;
		case 68: // "D"
			hexValue=hexValue<<4;
			hexValue+=0x0d;
			break;
		case 100: // "d"
			hexValue=hexValue<<4;
			hexValue+=0x0d;
			break;
		case 69: // "E"
			hexValue=hexValue<<4;
			hexValue+=0x0e;
			break;
		case 101: // "e"
			hexValue=hexValue<<4;
			hexValue+=0x0e;
			break;
		case 70: // "F"
			hexValue=hexValue<<4;
			hexValue+=0x0f;
			break;
		case 102: // "f"
			hexValue=hexValue<<4;
			hexValue+=0x0f;
			break;
		default: //unknown char
			isWhile=FALSE;
			break;
		}
		idx++;
		if(idx>=sl)
			isWhile=FALSE;
	}

	return  hexValue;
}

void CHTIME(DWORD ctime, DWORD gtime, char *rtString)
{
	DWORD t=0, d=0;
	char s[80];
	WORD hour=0, minute=0, second=0, millseconds=0;

	//  calculate the hour / minute / second / millseconds
	//
	t = ctime + (gtime/20);
	hour = (WORD) (t/3600000);
	t = t - hour*3600000;
	minute = (WORD) (t/60000);
	t = t - minute*60000;
	second = (WORD) (t/1000);
	millseconds = (WORD)(t - second*1000);

	//  link string follow the data
	//
	memset(s, 0, sizeof(s));
	sprintf(s, "-%02d:%02d:%02d.%03d", hour, minute, second, millseconds);
	strcpy(rtString, s);
}