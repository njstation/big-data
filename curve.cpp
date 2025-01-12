#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
/*
#define SAME_POLARITY_CNT 5
#define JUMP_POLARITY_CNT 2
#define BUF_SIZE 100
int     buf[BUF_SIZE]={-33,-44,-45,-48,-31,-34,-44,-31,-5,-56,266,967,1476,1857,-2133,-2205,-2227,-2206,-2095,2009,1962,1850,1731,1652,1571,1488,1352,1331,1239,1121,1103,-1052,-920,-884,-862,-796,737,731,690,589,575,542,489,478,479,441,383,408,373,305,311,313,255,223,290,252,198,246,229,170,195,208,145,119,157,119,111,155,132,108,128,112,85,98,128,96,72,99,100,64,99,128,66,56,103,80,68,102,86,60,85,99,38,44,117,66,25,96};
struct xy
{
	int x;
	int y;
};
int CheckChargeMotorType(int* buf)
{
    int      i;
    int      sameCnt = 0;
    int      jumpCnt = 0;
    int      ret = 0;
    
    for (i=0; i<BUF_SIZE; i++)  
    {
        if( ((buf[i] > 0) && (buf[i+1] < 0)) ||
            ((buf[i] < 0) && (buf[i+1] > 0)) 
          )
        {
            if(sameCnt >= SAME_POLARITY_CNT)  //serial 5 same polarities...
            {
                jumpCnt++;     
                
                if(jumpCnt >= JUMP_POLARITY_CNT)  //existing 2 times polarity jumps...
                {
                    ret = -1;
                    break;
                }
            }
            
            sameCnt = 0; 
        }
        else
        {
            sameCnt++;
        }
    }
     
    return ret;
}



void filter_value(int* curve)
{
	int lastPoint = 0;
	int curveDiff = 70;
	int curvesize = BUF_SIZE;

	for (int i = 0; i<curvesize; i++)//curvesize: max point number of the curve
	{
		if (i == 0 || i == curvesize - 1)
		{
			//record("x", i);
			//record("y", curve[i]);

			cout << i << ":" << curve[i]<< endl;

			lastPoint = i;
		}
		else if (abs(curve[i] - curve[lastPoint])>curveDiff)//curveDiff: filtering margin
		{
			if (lastPoint != i - 1)
			{
				//record("x", i-1);
				//record("y", curve[i-1]);

				cout << i << ":" << curve[i-1]<< endl;

			}

			//record("x", i);
			//record("y", curve[i]);

			cout << i << ":" << curve[i]<< endl;

			lastPoint = i;
		}
	}

}

vector< struct xy >  filter_ABS_value(vector<int> curve)
{
	int curvesize = curve.size();
	xy axis;
	bool isPeak;
	vector<struct xy > point_vec;
	for (int i = 0; i<curvesize; i++)//curvesize: max point number of the curve
	{

		if (i == 0 || i == curvesize - 1) //first or last point
		{
			//record("x", i);
			//record("y", curve[i]);
			axis.x = i;
			axis.y = abs(curve[i]);
			//cout << axis.x<< " "<< axis.y << endl;
			point_vec.push_back(axis);

		}
		else if (abs(curve[i - 1])<abs(curve[i]) && abs(curve[i + 1])<abs(curve[i]) && abs(curve[i])> 50)
		{
			axis.x = i;
			axis.y = abs(curve[i]);
			cout << curve[i] << " " << axis.y << endl;
			point_vec.push_back(axis);


		}

	}
	return point_vec;
}
*/
static const unsigned short crctab[] =
{ 0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108,
        0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, 0x1231, 0x0210,
        0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B,
        0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401,
        0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE,
        0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6,
        0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D,
        0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, 0x5AF5,
        0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC,
        0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6, 0x7C87, 0x4CE4,
        0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD,
        0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13,
        0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A,
        0x9F59, 0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E,
        0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
        0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1,
        0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, 0xB5EA, 0xA5CB,
        0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3, 0x14A0,
        0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8,
        0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657,
        0x7676, 0x4615, 0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9,
        0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882,
        0x28A3, 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
        0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, 0xFD2E,
        0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07,
        0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D,
        0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74,
        0x2E93, 0x3EB2, 0x0ED1, 0x1EF0 };

static const unsigned short crc16_tab[256] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

typedef    unsigned char  UINT8;
typedef    signed char    INT8;
typedef    unsigned short UINT16;
typedef    signed short   INT16;
typedef    unsigned int   UINT32;
typedef    signed int     INT32;

UINT16 updcrc(UINT16 crc, UINT8 c)
{
    UINT8 tmp;

    tmp = (UINT8) (crc >> 8) ^ c;
    crc = (UINT16) (crc << 8) ^ crctab[tmp];
    return (crc);
}

UINT16 crc16_form1(void *buffer, UINT32 count, UINT16 crc)
{
    UINT8* p;
    p = (UINT8*) buffer;

    for (; count; count--)
    {
        crc = updcrc(crc, *(p)++);
    }
    return crc;
}

UINT16 crc16_form2(UINT8 *buffer, UINT32 size, UINT16 seed)
{
    UINT16 crc = seed;
    while (size--)
        crc = (UINT16) (crc >> 8) ^ crc16_tab[(crc ^ *buffer++) & 0xff];
    return crc;
}

UINT16 crc16_form3(UINT8 *str, UINT32 size, UINT16 seed)
{
    union
    {
        unsigned short word;
        unsigned char bytes[2];
    } crc, crc2;
	crc.word = seed;
	unsigned char *crc_p = (UINT8*)str;
	for (int i=0; i<size ; i++)
	{
		crc.word = (unsigned short)(crc.bytes[0] ^ crc16_tab[*(crc_p++) ^ crc.bytes[1]]);
	}

return crc.word;
}


#include <iostream>
using namespace std;

int result[256]={0};
void generateCombinations(char arr[], int n, char combination[], int index) {
    if (index == n) {
        /*
        for (int i = 0; i < n; i++) {
            printf("%u ", combination[i]);//cout << combination[i];
        }
        cout << endl;
		*/
		static int ii=0;
		ii++;
		int c = crc16_form2((UINT8*)combination,n,1);
		
		result[c/256]++;
		
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
			printf("%6d",result[i*16+j]);
			}
			printf("\n");
		}
		printf("\n\n times=%d, crc=%X, idx=%X\n",ii, c, c/256);
        return;
    }
    
    // 对每个位置尝试不同的字符
    for (int i = 0; i < 255; i++) {
        combination[index] = i;
        generateCombinations(arr, n, combination, index + 1);
    }
}

int main() {
    int n = 40;
    UINT8 arr[n]; // 40个字符的数组
    UINT8 combination[n]; // 用于保存每个组合
    srand(time(NULL));    
	
for (;;)
{
	static int ii=0;
	ii++;
    // 初始化数组
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 256;
    }

	int c = crc16_form2((UINT8*)arr,n,1);
	
	if (c<256)
	{
	result[c%256]++;
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
		printf("%6d",result[i*16+j]);
		}
		printf("\n");
	}
	printf("\n\n times=%d, crc=%X, idx=%X\n",ii, c, c%256);
	}
}

}
/*	
int main() {
    int n = 40;
    char arr[n]; // 40个字符的数组
    char combination[n]; // 用于保存每个组合
    
    // 初始化数组
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    
    generateCombinations(arr, n, combination, 0);
    
    return 0;
}

int main()
{
	int result;
	printf("Enter CRC: ");
	scanf("%d", &result);
	int a=0;
	int b=0;


	char str[8]={0};
	int size = 8;
	for (UINT32 i=0;i<=0xffffffff;i++)
	{
		UINT32 *p_h=(UINT32*)(&str);
		*p_h=i;
		for (UINT32 j=0;j<=0xffffffff;j++)
		{
			UINT32 *p_l=(UINT32*)(&str);
			p_l[1]=j;
			if (crc16_form2((UINT8*)str,size,1)==result) a++;
			if (crc16_form3((UINT8*)str,size,1)==result) b++;

		if (crc16_form2((UINT8*)str,size,1)==result)
		printf("i=%d,j=%d,crc1=%d,crc2=%d\n",i,j,a,b);
		}
	}

//printf("crc1=%X,crc2=%X\n",crc16_form2((UINT8*)str,size,1), crc16_form3((UINT8*)str,size,1));

return 0;

}
*/