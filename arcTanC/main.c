#include <stdio.h>
#include <stdint.h>

typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;

#define ABS(_x)      (((_x)>0) ? (_x) : (-(_x)))

#define ATAN_TABLE_SIZE 32

static const UINT8 atanTable[ATAN_TABLE_SIZE] =
{
    0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 22, 24, 25, 27,
    28, 29, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
};  
    
INT16 arctan2( INT16 y, INT16 x )
{
    UINT16 ax = ABS(x);
    UINT16 ay = ABS(y);
    UINT8 angle;
            
    if (ax == 0 && ay == 0)
        return 0;
    else if (ax == 0)
        return (y > 0) ? 90 : -90;
    else if (ay == 0)
        return (x > 0) ? 0 : 180;
        
    if (ay == ax)
        angle = 45;
    else if (ax < ay)
        angle = atanTable[(ax * ATAN_TABLE_SIZE)/ay];
    else
        angle = atanTable[(ay * ATAN_TABLE_SIZE)/ax];

   if (x>0 && y>0)
       return (ax<ay) ? 90 - angle : angle;
   else if (x>0 && y<0)
       return (ax<ay) ? -90 + angle : -angle;
   else if (x<0 && y<0)
       return (ax<ay) ? -90 - angle : -180 + angle;
   else if (x<0 && y>0)
       return (ax<ay) ? 90 + angle : 180 - angle;

   return 0;
}

int main(int c, char *d[]) {
	UINT8 i,j;
	for(i=0,j=100;i<=100;i++,j--) {
		printf("%d %d => %d\n",i,j,arctan2(i,j));
	} 
	return 0;
}
