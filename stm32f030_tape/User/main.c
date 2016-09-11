#include "ALL_Includes.h"//包含所需的头文件
#define MAX_BIT 8
void ALL_Config(void);

extern void init_code_input(void);
extern int get_code_input(void);
extern int get_Infrared_input(void);
extern void set_infrared_en(int enable);
extern int gpio_bit_val;
static int binToGray(int bin_val);
static int grayToBin(int gray);
static uint16_t gray_to_binary(uint16_t gray);
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
	[0x36]=38,
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

static int get_rever_code_input(void)
{
		
		int code_val,i;
		int code_rev_val = 0;
		code_val = get_code_input();

		for( i = 0 ; i < MAX_BIT; i++){
		
			if(code_val & (1 << i)){
				code_rev_val = code_rev_val | (1<< (MAX_BIT - 1 - i));
			}
		}
		
		return code_rev_val >> 2;
		//return code_val ;
		
}

static void printf_bit(short byte)
{
	int i;
	char str_byte[MAX_BIT+1]={0};
	
	for(i = 0 ;i < MAX_BIT ; i++){
		if(byte & (1<<i)){
			str_byte[MAX_BIT - 1 - i] = '1';
		}else{
			str_byte[MAX_BIT - 1 - i] = '0';
		}
	}

	str_byte[MAX_BIT] = '\n';
	
	printf("0x%02x,%s\n",byte,str_byte);
	//printf("[0x%02x]=,\n",byte,str_byte);
}
int main(void)
{	
	int code_val , i, adc_val,adc_val_tmp;
	int new_code,ag = 0;
	ALL_Config();
	
	init_code_input();
	
	for(i = 0 ; i < 64; i++){
		code_val = binToGray(i);
		printf("+++i = %d \t",i);
		printf_bit(code_val);
		code_val = grayToBin(code_val);
		printf("---i = %d \t",code_val);
		printf_bit(code_val);
	}

	board_ADC_init();

//set_infrared_en(0);
	code_val = 0;
	adc_val = 0;

	while(1){
		//gpio_bit_val
		if( code_val != gpio_bit_val ){
			//printf_bit(gpio_bit_val);
			//i = gray_to_binary((uint16_t)gpio_bit_val);
			code_val = gpio_bit_val;
			printf("0x%08x %d\n",gpio_bit_val,gray2index[code_val]);
			 
		}
		if(is_ADC_end())
		{
		
			adc_val_tmp = get_vol_val();
			if((adc_val_tmp - adc_val > 100)
			   ||(adc_val - adc_val_tmp> 100)){
				adc_val = adc_val_tmp;
				printf("vol = %d\n",adc_val);
			}
		//	Delay(800000);
		}		
	}
	
	#if 0
	while(1){
		LED_ON();
		//delay_ms(10);
		
		new_code = get_code_input();
		if(new_code != code_val){
			code_val = new_code;
			LED_OFF();
			//printf("---> 0x%x\n",code_val);
			printf_bit(code_val);
			set_infrared_en(0);
			printf("infrared = ");
			ag = get_Infrared_input();
			printf("%d \n",ag);
			set_infrared_en(1);
			//i = gray_to_binary((uint16_t)code_val);
			//printf("bin = %d |\t",i);
			//i = grayToBin(code_val);
			#if 0
			if(gray2index[code_val] == 0){
				ag++;
				ag = ag % 6;
			}
			
			printf("%d %d\n",gray2index[code_val],(gray2index[code_val] + ag*64)*15 / 16);
			#endif
		}
		//delay_ms(10);
	}
	#endif
}

/************************
函数功能：总初始化
输入参数：无
输出参数：无
备    注：无
************************/
void ALL_Config(void)
{
    Delay_Init(8);
	LED_Init();
	USART1_Init(115200);
}


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

static int binToGray(int bin_val)
{
	return bin_val ^ (bin_val >> 1);
}


static int grayToBin(int gray)
{
//	gray ^= gray >> 32;
	gray ^= gray >> 16;
	gray ^= gray >> 8;
	gray ^= gray >> 4;
	gray ^= gray >> 2;
	gray ^= gray >> 1;
	return gray;
}
static uint16_t gray_to_binary(uint16_t gray)
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



