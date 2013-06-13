/* 
 * File:   datatypes.h
 * Author: AranHase
 *
 * Created on June 9, 2013, 11:25 PM
 */

#ifndef DATATYPES_H
#define	DATATYPES_H

typedef union
{
  unsigned char byte;
  struct
  {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
  } bits;
} bybit;

typedef union {
    struct {
        unsigned char byte1;
        unsigned char byte2;
    } bytes;
    struct {
        unsigned char b00 : 1;
        unsigned char b01 : 1;
        unsigned char b02 : 1;
        unsigned char b03 : 1;
        unsigned char b04 : 1;
        unsigned char b05 : 1;
        unsigned char b06 : 1;
        unsigned char b07 : 1;
        unsigned char b08 : 1;
        unsigned char b09 : 1;
        unsigned char b10 : 1;
        unsigned char b11 : 1;
        unsigned char b12 : 1;
        unsigned char b13 : 1;
        unsigned char b14 : 1;
        unsigned char b15 : 1;
    } id;
} sensors;

#endif	/* DATATYPES_H */

