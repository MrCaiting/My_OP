/*
scancode_to_ascii.c
convert the scan code of keyboard to ascii
Edited by Zhaoying Dui zdu9
*/
#include "scancode_to_ascii.h"
#define ASCII_LEN 256
#define CAP_LOCK 0x3A
#define KEYS_UPPER 0x58
#define KEYS_LOWER 0x01
#define CAP_A 65
#define CAP_Z 90
#define CAP2LOW 32
#define LEFT_CLT 0
#define LEFT_SHIFT 0
#define RIGHT_SHIFT 0
#define LEFT_ALT 0
#define RIGHT_ALT 0
#define NAN 0
static int cap_flag = 0;
/*  ascii code of the scan code SET 1, the order is for a "US QWERTY" keyboard only,
    from "~" key on the second line of keyboard, to the "space" key on the last line of the keyboard,
    including the keys on the numerical pads on the right of the keyboard */
static char k2a_arr_cap[ASCII_LEN]={
    NAN,27,49,50,51,52,53,54,55,56,57,48,45,
    61,8,9,81,87,69,82,84,89,85,73,79,80,
    91,93,10,LEFT_CLT,65,83,68,70,71,72,74,75,76,
    59,39,96,LEFT_SHIFT,92,90,88,67,86,66,78,77,44,
    46,47,RIGHT_SHIFT,42, LEFT_ALT, 32, NAN, NAN,
    NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
    55, 56, 57, 45, 52, 53, 54, 43, 49, 50, 51, 48, 46,
    NAN, NAN
};
/*
keyscan_to_ascii
DESCRITPTION: convert pressed key to ascii code
INPUT: keyboard press_key scan code
OUTPUT: ascii code
SIDEEFFECT: use the k2a_arr_cap[ASCII_LEN] array to convert pressed scan code to its corresponding ascii code
*/
char keyscan_to_ascii(char press_key){
    /*deal with the case of caps lock */
    if(press_key == CAP_LOCK){
        if(cap_flag) cap_flag = 0;
        else cap_flag = 1;
    }
    /*check if the scan code is valid
      for alphabatical keys, check whether we need to change its upper and lower case*/
    if(press_key<= KEYS_UPPER && press_key >= KEYS_LOWER){
        if(k2a_arr_cap[(int)press_key]<=CAP_Z && k2a_arr_cap[(int)press_key]>=CAP_A){
            if(cap_flag) return k2a_arr_cap[(int)press_key];
            else return k2a_arr_cap[(int)press_key] + CAP2LOW;
        }
        return k2a_arr_cap[(int)press_key];
    }
    else return NAN;
}
