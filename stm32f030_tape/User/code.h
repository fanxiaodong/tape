#ifndef __code_h__
#define __code_h__

#define BLANK_VLA   700
#define WHITE_VLA   400

#define CONTINUE    0x55
#define START       0xaa
#define STOP        0xa0
#define GET_ERROR   0xff

void set_infrared_en(int enable);
int get_Infrared_input(void);
int get_code_input(void);
void init_code_input(void);
int get_10_val(int gray_val);
unsigned int Qr_code_check(int val,int dir);
void printf_bit(short byte);

int binToGray(int bin_val);
int grayToBin(int gray);
uint16_t gray_to_binary(uint16_t gray);

void bar_code_proc(int input_cd_val, int adc_val);
int inch_proc(int input_cd_val);


#endif
