#include <stdio.h>
#include <stdint.h>

typedef uint8_t FP_UINT8;
typedef int16_t FP_INT16;
typedef uint16_t FP_UINT16;

#define FP_ABS(_x)      (((_x)>0) ? (_x) : (-(_x)))

#define ATAN_TABLE_SIZE 32

static const FP_UINT8 atanTable[ATAN_TABLE_SIZE] =
{
    0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 22, 24, 25, 27,
    28, 29, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
};  
    
FP_INT16 fp_arctan2( FP_INT16 y, FP_INT16 x )
{
    FP_UINT16 ax = FP_ABS(x);
    FP_UINT16 ay = FP_ABS(y);
    FP_UINT8 angle;
            
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
	FP_UINT8 i,j;
	for(i=0,j=100;i<=100;i++,j--) {
		printf("%d %d => %d\n",i,j,fp_arctan2(i,j));
	} 
	return 0;
}
