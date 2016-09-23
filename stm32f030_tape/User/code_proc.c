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
/*******************条形码值*************************************/
static char bar_code_conversion[]=
{
[0x07]=1,
[0x0b]=2,
[0x0d]=3,
[0x0e]=4,
[0x16]=5,
[0x19]=6,
[0x29]=7,
[0x31]=8,
[0x32]=9,
[0x2a]=10,
[0x15]=11,
[0x13]=12,
[0x23]=13,
[0x25]=14,
[0x26]=15,
[0x1a]=16,
[0x1c]=17,
[0x2c]=18,
[0x34]=19,
[0x38]=20
};
#if 0
static char bar_code_arry[]=
{
 0x07,0x0b,0x0d,0x0e,0x16,
 0x19,0x29,0x31,0x32,0x2a,
 0x15,0x13,0x23,0x25,0x26,
 0x1a,0x1c,0x2c,0x34,0x38
 };
 
static int is_bar_code(int bar_code)
{
	int i ;
	for(i = 0 ; i < arry_size(bar_code_arry);i++){
		if(bar_code == bar_code_arry[i]){
			return 1;
		}
	}
	return 0;
}
#else
static int bar_code_index(int bar_code)
{
	if((bar_code & 0x3f) != bar_code){
		return -1;
	}
	
	return bar_code_conversion[bar_code];
}

static int is_bar_code(int bar_code)
{
	if(bar_code_index(bar_code) <= 0){
		return 0;
	}
	
	return 1;
}
#endif
/********************************************************/

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



//条形码
/********************************************************
@val 输入的adc 电压值表示 条形码黑条宽度
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
		
		return CONTINUE;
	}
	
	if((valid_val_cnt >= 1)&&(valid_val_cnt <= 4)){

		get_val = 0;
		//printf("0: %d\n",valid_val_cnt);
	}else if((valid_val_cnt >= 5)&&(valid_val_cnt <= 9)){

		get_val = 1;
		//printf("1: %d\n",valid_val_cnt);
	}else if(valid_val_cnt >= 10){
	
		get_val = START;
		//printf("s: %d\n",valid_val_cnt);
	}else if(valid_val_cnt == 0){

		get_val = CONTINUE;
		
	}else{
		get_val = GET_ERROR;
		printf("error %d\n",valid_val_cnt);
	}
	
	valid_val_cnt = 0;
	
	return get_val;
}

//==================================================
typedef enum
{ 
	F_DIR,//forward dirction
	R_DIR//reverse direction
}dir_e;

typedef struct _bar_statuts
{
	uint8_t bar_code;//当前条形码
	uint8_t bar_code_white;
	uint8_t bar_code_index;//当前条形码转化成10进制	
	uint8_t bar_code_index_white;//当前条形码转化成10进制
	uint8_t coded_disk_val;//码盘数值
	uint8_t res;
	uint16_t c_bar_code;//正在识别的条形码
	
}bar_status_t;

typedef struct __tape_run_t
{
	int inch_val;//数值 英寸
	bar_status_t bc_status;
	uint8_t direction;
	uint8_t res[3];
}tape_run_t;

typedef struct __bar_code_t
{
	bar_status_t bc_status;
	uint8_t f_start;
	uint8_t black_cnt;//黑条纹
	uint8_t white_cnt;//空条纹
	uint8_t direction;


}bar_code_t;

static tape_run_t g_tape_run =
{
	.inch_val = -1,
	.bc_status = {0},
	.direction = F_DIR,
};

static bar_code_t g_bar_code = 
{
	.bc_status = {0},
	.f_start = 0xff,
	.black_cnt = 0,
};

#define V_0_L 1
#define V_0_H 4
#define V_1_L 5
#define V_1_H 9
#define V_S_L 10
#define V_S_H 18


/*
bref:识别条形码

@1 input_cd_val  input coded disk val

*/
#if 0
void bar_code_proc(int input_cd_val, int adc_val)
{
	bar_code_t *pb = &g_bar_code;
	static char test[16]={0};
	uint8_t dir_change = pb->direction;

	if(input_cd_val > pb->coded_disk_val){
		pb->direction = F_DIR;
		
	}else {
		//翻转情况 63->0
		if(pb->coded_disk_val - input_cd_val > 50){
			pb->direction = F_DIR;
		}else{
			pb->direction = R_DIR;
		}
	}

	dir_change = (dir_change == pb->direction) ? 0 : 1;

	pb->coded_disk_val = input_cd_val;
	
	if(adc_val > BLANK_VLA){
		test[pb->black_cnt] = input_cd_val;

		pb->black_cnt++;
		
		return ;
	}else{
		
	}
	
	if(pb->black_cnt  == 0){
		
		
	}else if((pb->black_cnt  >= V_0_L)&&(pb->black_cnt  <= V_0_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1;
		
		//printf("0: %d\n",pb->black_cnt );
	}else if((pb->black_cnt  >= V_1_L)&&(pb->black_cnt  <= V_1_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1 | 1;
		
		//printf("1: %d\n",pb->black_cnt );
	}else if((pb->black_cnt  >= V_S_L)&&(pb->black_cnt  <= V_S_H)){
		//检测到start 标记	
		if(is_bar_code(pb->bc_status.c_bar_code)){
			int bci ,bci1;
			if(pb->direction == R_DIR){
				pb->bc_status.bar_code = 0;
				pb->bc_status.c_bar_code &= 0x3f;
				pb->bc_status.bar_code |= (!!(pb->bc_status.c_bar_code & (1<< 5)))<< 0;
				pb->bc_status.bar_code |= (!!(pb->bc_status.c_bar_code & (1<< 4)))<< 1;
				pb->bc_status.bar_code |= (!!(pb->bc_status.c_bar_code & (1<< 3)))<< 2;
				pb->bc_status.bar_code |= (!!(pb->bc_status.c_bar_code & (1<< 2)))<< 3;
				pb->bc_status.bar_code |= (!!(pb->bc_status.c_bar_code & (1<< 1)))<< 4;
				pb->bc_status.bar_code |= (!!(pb->bc_status.c_bar_code & (1<< 0)))<< 5;
			}else{
				pb->bc_status.bar_code = pb->bc_status.c_bar_code;
			}

			pb->bc_status.bar_code_index  = bar_code_index(pb->bc_status.bar_code);
			
		}else{
			printf("error of 0x%x\n",pb->bc_status.c_bar_code);
		}
	
		pb->bc_status.c_bar_code = 0;
		
		printf("s: %d 0x%02x %02d %02d\n",pb->black_cnt, pb->bc_status.bar_code ,pb->bc_status.bar_code_index ,input_cd_val);

		int i = 0;

		for(i = 0 ; i < pb->black_cnt;i++){
			printf("%02d,",test[i]);
		}

		printf("\n===============================\n");
		
		memset(test,0,sizeof(test));
		
	}else {
		printf("error %d\n",pb->black_cnt);
	}
	
	pb->black_cnt = 0;
	
}

#else
static int code_reverse(int code,int bit_cnt)
{
	int ret = 0, i = 0;
	code &= (1<<bit_cnt) - 1;
	
	for(i = 0; i < bit_cnt; i++){
		ret |= (!!(code & (1<< (bit_cnt -1 - i))))<< i;
	}
	#if 0
	ret |= (!!(code & (1<< 5)))<< 0;
	ret |= (!!(code & (1<< 4)))<< 1;
	ret |= (!!(code & (1<< 3)))<< 2;
	ret |= (!!(code & (1<< 2)))<< 3;
	ret |= (!!(code & (1<< 1)))<< 4;
	ret |= (!!(code & (1<< 0)))<< 5;
	#endif
	return ret;
}
static void get_odd_even_bit(int code, int *odd, int *event)
{
	int old_tmp = 0;
	int event_tmp = 0;	
	int i;
	
	for (i = 0 ; i < 32; i++){
		if(i&1){//even
			event_tmp |= (!!(code & (1<<i)))<<(i-1);
		}else{//odd
			old_tmp   |= (!!(code & (1<<i)))<<(i>>1);
		}
	}

	if(odd){
		*odd = old_tmp;
	}
	
	if(event){
		*event = event_tmp;
	}
}
static void white_proc(bar_code_t *pb)
{
	int odd,even;
	if(pb->white_cnt == 0){
		
		
	}else if((pb->white_cnt  >= V_0_L)&&(pb->white_cnt	<= V_0_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1;
		
		//printf("0: %d\n",pb->black_cnt );
	}else if((pb->white_cnt  >= V_1_L)&&(pb->white_cnt	<= V_1_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1 | 1;
		
		//printf("1: %d\n",pb->black_cnt );
	}else if((pb->white_cnt  >= V_S_L)&&(pb->white_cnt	<= V_S_H)){
		//检测到stop 标记	
		get_odd_even_bit(pb->bc_status.c_bar_code,&odd,&even);

		printf("========= 0x%04x 0x%02x 0x%02x\n",pb->bc_status.c_bar_code,odd,even);

		
		if(is_bar_code(odd)){
		//if(1){
			if(pb->direction == R_DIR){
				pb->bc_status.bar_code = code_reverse( pb->bc_status.c_bar_code, 12);
			}else{
				pb->bc_status.bar_code = pb->bc_status.c_bar_code;
			}
			pb->bc_status.bar_code_index  = bar_code_index(pb->bc_status.bar_code);
			
		}else{
			printf("error of 0x%x\n",pb->bc_status.c_bar_code);
		}
			
		printf("white: %d 0x%02x %02d %02d\n",pb->white_cnt, pb->bc_status.bar_code ,pb->bc_status.c_bar_code,pb->bc_status.coded_disk_val);
		pb->bc_status.c_bar_code = 0;
		
	}else {
		printf("white error %d\n",pb->white_cnt);
	}
	
	pb->white_cnt = 0;
}


static void black_proc(bar_code_t *pb)
{
	if(pb->black_cnt  == 0){
		
		
	}else if((pb->black_cnt  >= V_0_L)&&(pb->black_cnt  <= V_0_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1;
		
		//printf("0: %d\n",pb->black_cnt );
	}else if((pb->black_cnt  >= V_1_L)&&(pb->black_cnt  <= V_1_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1 | 1;
		
		//printf("1: %d\n",pb->black_cnt );
	}else if((pb->black_cnt  >= V_S_L)&&(pb->black_cnt  <= V_S_H)){
		//检测到start 标记	
		//if(is_bar_code(pb->bc_status.c_bar_code)){
		#if 0
		if(1){
			
			if(pb->direction == R_DIR){
				pb->bc_status.bar_code = code_reverse( pb->bc_status.c_bar_code,12);

			}else{
				pb->bc_status.bar_code = pb->bc_status.c_bar_code;
			}

			pb->bc_status.bar_code_index  = bar_code_index(pb->bc_status.bar_code);
			
		}else{
			printf("error of 0x%x\n",pb->bc_status.c_bar_code);
		}
		#endif
		pb->bc_status.c_bar_code = 0;
		
		printf("black: %d 0x%02x %02d %02d\n",pb->black_cnt, pb->bc_status.bar_code ,pb->bc_status.bar_code_index,pb->bc_status.coded_disk_val);
		
	}else {
		printf("black error %d\n",pb->black_cnt);
	}
	
	pb->black_cnt = 0;
}

static void blank_proc_1(bar_code_t *pb, int cnt)
{
	int odd,even;
	if(cnt == 0){
		
		
	}else if((cnt  >= V_0_L)&&(cnt	<= V_0_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1;
		
	}else if((cnt  >= V_1_L)&&(cnt	<= V_1_H)){

		pb->bc_status.c_bar_code = pb->bc_status.c_bar_code << 1 | 1;
		
	}else if((cnt >= V_S_L)&&(cnt	<= V_S_H)){
		//检测到stop 标记	
		
		if(pb->direction == R_DIR){
			if(pb->black_cnt){//start
				pb->bc_status.c_bar_code = 0;
				return;
			}			
			pb->bc_status.c_bar_code = code_reverse( pb->bc_status.c_bar_code, 12);
			
		}else{
			if(pb->white_cnt){//start
				pb->bc_status.c_bar_code = 0;
				return;
			}
		}
		
		get_odd_even_bit(pb->bc_status.c_bar_code,&odd,&even);

		printf("======0x%04x 0x%02x 0x%02x\n",pb->bc_status.c_bar_code,odd,even);
		
		if(is_bar_code(odd)){
		
			pb->bc_status.bar_code = pb->bc_status.c_bar_code;
			
			pb->bc_status.bar_code_index  = bar_code_index(pb->bc_status.bar_code);
			
		}else{
			printf("error of 0x%x\n",pb->bc_status.c_bar_code);
		}
			
		printf("%d 0x%02x %02d %02d\n",cnt, pb->bc_status.bar_code ,pb->bc_status.c_bar_code,pb->bc_status.coded_disk_val);
		pb->bc_status.c_bar_code = 0;
		
	}else {
		printf("white error %d\n",cnt);
	}
	
}

void bar_code_proc(int input_cd_val, int adc_val)
{
	bar_code_t *pb = &g_bar_code;
	static char test[16]={0};
	int blank_cnt = 0;
	uint8_t dir_change = pb->direction;

	if(input_cd_val > pb->bc_status.coded_disk_val){
		pb->direction = F_DIR;
		
	}else {
		//翻转情况 63->0
		if(pb->bc_status.coded_disk_val - input_cd_val > 50){
			pb->direction = F_DIR;
		}else{
			pb->direction = R_DIR;
		}
	}

	dir_change = (dir_change == pb->direction) ? 0 : 1;

	pb->bc_status.coded_disk_val = input_cd_val;
	
	if(adc_val >= BLANK_VLA){
	
		test[pb->black_cnt] = input_cd_val;

		pb->black_cnt++;
		
		if(pb->white_cnt){
			blank_cnt = pb->white_cnt;
			pb->white_cnt = 0;
		}
		
	}else if(adc_val <= WHITE_VLA){

		pb->white_cnt++;
		
		if(pb->black_cnt){
			blank_cnt = pb->black_cnt;
			pb->black_cnt = 0;
		}
		
	}else{
		
	}
	if(blank_cnt){
		blank_proc_1(pb,blank_cnt);
	}
	return ;
	
}

#endif

int inch_proc(int input_cd_val)
{

	tape_run_t *ptr = &g_tape_run;

	bar_code_t *pbc = &g_bar_code;//更新

	int bci;
	
	if(ptr->bc_status.bar_code_index != pbc->bc_status.bar_code_index){
	//说明条形码有更新
		bci = ptr->bc_status.bar_code_index - pbc->bc_status.bar_code_index ;
		
		if(bci > 0){
			
		}else{
			
		}
		
	}else{
	
		if(ptr->bc_status.bar_code_index <= 0){
			//说明第一次初始化
		}else{
			
		}
		
	}

	return 0;
}


