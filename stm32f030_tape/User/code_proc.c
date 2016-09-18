#include "ALL_Includes.h"//包含所需的头文件


#if 0
自然二进制数转换到格雷码
－－－－－－－－－－－－
设有 N 位二进制数 B(i)，其中 0 <= i <= N - 1；它可以变换成为同样位数的格雷码 G(i)。
二进制数与格雷码的转换公式如下：

　　G(i) = B(i+1) XOR B(i) ; 0 <= i < N - 1
　　G(i) = B(i)            ;      i = N - 1

如果是通过编程计算进行变换，就需要使用这个公式逐位的计算；
如果是使用硬件电路进行变换，就可以使用做而论道前面在回答问题时给出的电路。

 

格雷码转换到自然二进制数
－－－－－－－－－－－－
设有 N 位格雷码 G(i)，把它转换成自然二进制数的算法如下。

自然二进制码的最高位等于雷码的最高位；
自然二进制码的次高位为最高位自然二进制码与次高位格雷码相异或；
自然二进制码的其余各位与次高位自然二进制码的求法相类似。
转换公式如下：

　　B(i) = G(i)             ;      i = N - 1
　　B(i) = B(i+1) XOR G(i)  ; 0 <= i < N - 1


static gray_binary(int gray_val,int n)
{
	int i;
	int binary = 0;
	for(i = 0 ; i < n; i++){
		(gray_val & (1 << (i+1)))^
	}
}

#endif

#if 1
static char gray2index[64]=
{
	[0x00]=63,
	[0x01]=62,
	[0x05]=61,
	[0x04]=60,
	[0x06]=59,
	[0x07]=58,
	[0x17]=57,
	[0x16]=56,
	[0x14]=55,
	[0x15]=54,
	[0x11]=53,
	[0x10]=52,
	[0x12]=51,
	[0x13]=50,
	[0x1b]=49,
	[0x1a]=48,
	[0x18]=47,
	[0x19]=46,
	[0x1d]=45,
	[0x1c]=44,
	[0x1e]=43,
	[0x1f]=42,
	[0x3f]=41,
	[0x3e]=40,
	[0x3c]=39,
	[0x3d]=38,
	[0x39]=37,
	[0x38]=36,
	[0x3a]=35,
	[0x3b]=34,
	[0x33]=33,
	[0x32]=32,
	[0x30]=31,
	[0x31]=30,
	[0x35]=29,
	[0x34]=28,
	[0x36]=27,
	[0x37]=26,
	[0x27]=25,
	[0x26]=24,
	[0x24]=23,
	[0x25]=22,
	[0x21]=21,
	[0x20]=20,
	[0x22]=19,
	[0x23]=18,
	[0x2b]=17,
	[0x2a]=16,
	[0x28]=15,
	[0x29]=14,
	[0x2d]=13,
	[0x2c]=12,
	[0x2e]=11,
	[0x2f]=10,
	[0x0f]=9,
	[0x0e]=8,
	[0x0c]=7,
	[0x0d]=6,
	[0x09]=5,
	[0x08]=4,
	[0x0a]=3,
	[0x0b]=2,
	[0x03]=1,
	[0x02]=0,
};

#else
static char gray2index[64]=
{
	[0x00]=0,
	[0x01]=1,
	[0x05]=2,
	[0x04]=3,
	[0x06]=4,
	[0x07]=5,
	[0x17]=6,
	[0x16]=7,
	[0x14]=8,
	[0x15]=9,
	[0x11]=10,
	[0x10]=11,
	[0x12]=12,
	[0x13]=13,
	[0x1b]=14,
	[0x1a]=15,
	[0x18]=16,
	[0x19]=17,
	[0x1d]=18,
	[0x1c]=19,
	[0x1e]=20,
	[0x1f]=21,
	[0x3f]=22,
	[0x3e]=23,
	[0x3c]=24,
	[0x3d]=25,
	[0x39]=26,
	[0x38]=27,
	[0x3a]=28,
	[0x3b]=29,
	[0x33]=30,
	[0x32]=31,
	[0x30]=32,
	[0x31]=33,
	[0x35]=34,
	[0x34]=35,
	[0x36]=36,
	[0x37]=37,
//	[0x36]=38,
	[0x27]=38,
	[0x26]=39,
	[0x24]=40,
	[0x25]=41,
	[0x21]=42,
	[0x20]=43,
	[0x22]=44,
	[0x23]=45,
	[0x2b]=46,
	[0x2a]=47,
	[0x28]=48,
	[0x29]=49,
	[0x2d]=50,
	[0x2c]=51,
	[0x2e]=52,
	[0x2f]=53,
	[0x0f]=54,
	[0x0e]=55,
	[0x0c]=56,
	[0x0d]=57,
	[0x09]=58,
	[0x08]=59,
	[0x0a]=60,
	[0x0b]=61,
	[0x03]=62,
	[0x02]=63,
};
#endif


 int binToGray(int bin_val)
{
	return bin_val ^ (bin_val >> 1);
}


 int grayToBin(int gray)
{
//	gray ^= gray >> 32;
	gray ^= gray >> 16;
	gray ^= gray >> 8;
	gray ^= gray >> 4;
	gray ^= gray >> 2;
	gray ^= gray >> 1;
	return gray;
}
 uint16_t gray_to_binary(uint16_t gray)
{	
	uint16_t result = gray & (1 << 15); 
	result |= (gray ^ (result >> 1)) & (1 << 14);
	result |= (gray ^ (result >> 1)) & (1 << 13);
	result |= (gray ^ (result >> 1)) & (1 << 12);
	result |= (gray ^ (result >> 1)) & (1 << 11);	
	result |= (gray ^ (result >> 1)) & (1 << 10);	
	result |= (gray ^ (result >> 1)) & (1 << 9);	
	result |= (gray ^ (result >> 1)) & (1 << 8);	
	result |= (gray ^ (result >> 1)) & (1 << 7);	
	result |= (gray ^ (result >> 1)) & (1 << 6);	
	result |= (gray ^ (result >> 1)) & (1 << 5);	
	result |= (gray ^ (result >> 1)) & (1 << 4);	
	result |= (gray ^ (result >> 1)) & (1 << 3);	
	result |= (gray ^ (result >> 1)) & (1 << 2);	
	result |= (gray ^ (result >> 1)) & (1 << 1);	
	result |= (gray ^ (result >> 1)) & (1 );	
	return result;
}


int get_10_val(int gray_val)
{
	return gray2index[gray_val];
}

//二维码处理
/********************************************************
@val 输入的adc 电压值表示 二维码黑条宽度
*********************************************************/


unsigned int Qr_code_check(int val, int dir)
{
	static int valid_val_cnt;

	int get_val = 0;

	if(val > BLANK_VLA){
		if(dir){

			valid_val_cnt++;
			
		}else{
		
			valid_val_cnt--;
			
			if(valid_val_cnt < 0){
			
				valid_val_cnt = 0;
				
			}
		}
		//printf("val_cnt = %d\n",valid_val_cnt);
		return CONTINUE;
	}
	
	if((valid_val_cnt >= 1)&&(valid_val_cnt <= 4)){

		get_val = 0;
		
	}else if((valid_val_cnt >= 5)&&(valid_val_cnt <= 9)){

		get_val = 1;
		
	}else if(valid_val_cnt >= 10){
	
		get_val = START;
		
	}else if(valid_val_cnt == 0){

		get_val = CONTINUE;
		
	}else{
		get_val = GET_ERROR;
		printf("error %d\n",valid_val_cnt);
	}
	
	valid_val_cnt = 0;
	
	return get_val;
}

