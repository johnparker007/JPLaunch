#ifndef __INPUT_CONSTANTS_H__
#define __INPUT_CONSTANTS_H__

// These are copied from z88dk/include/_DEVELOPMENT/sdcc/input/input_zx.h:

#define IN_KEY_SCANCODE_DISABLE  0xffff
#define IN_KEY_SCANCODE_ANYKEY   0x1f00

#define IN_KEY_SCANCODE_CAPS   0x01fe
#define IN_KEY_SCANCODE_SYM    0x027f

#define IN_KEY_SCANCODE_ENTER  0x01bf
#define IN_KEY_SCANCODE_SPACE  0x017f

#define IN_KEY_SCANCODE_a      0x01fd
#define IN_KEY_SCANCODE_b      0x107f
#define IN_KEY_SCANCODE_c      0x08fe
#define IN_KEY_SCANCODE_d      0x04fd
#define IN_KEY_SCANCODE_e      0x04fb
#define IN_KEY_SCANCODE_f      0x08fd
#define IN_KEY_SCANCODE_g      0x10fd
#define IN_KEY_SCANCODE_h      0x10bf
#define IN_KEY_SCANCODE_i      0x04df
#define IN_KEY_SCANCODE_j      0x08bf
#define IN_KEY_SCANCODE_k      0x04bf
#define IN_KEY_SCANCODE_l      0x02bf
#define IN_KEY_SCANCODE_m      0x047f
#define IN_KEY_SCANCODE_n      0x087f
#define IN_KEY_SCANCODE_o      0x02df
#define IN_KEY_SCANCODE_p      0x01df
#define IN_KEY_SCANCODE_q      0x01fb
#define IN_KEY_SCANCODE_r      0x08fb
#define IN_KEY_SCANCODE_s      0x02fd
#define IN_KEY_SCANCODE_t      0x10fb
#define IN_KEY_SCANCODE_u      0x08df
#define IN_KEY_SCANCODE_v      0x10fe
#define IN_KEY_SCANCODE_w      0x02fb
#define IN_KEY_SCANCODE_x      0x04fe
#define IN_KEY_SCANCODE_y      0x10df
#define IN_KEY_SCANCODE_z      0x02fe

#define IN_KEY_SCANCODE_0      0x01ef
#define IN_KEY_SCANCODE_1      0x01f7
#define IN_KEY_SCANCODE_2      0x02f7
#define IN_KEY_SCANCODE_3      0x04f7
#define IN_KEY_SCANCODE_4      0x08f7
#define IN_KEY_SCANCODE_5      0x10f7
#define IN_KEY_SCANCODE_6      0x10ef
#define IN_KEY_SCANCODE_7      0x08ef
#define IN_KEY_SCANCODE_8      0x04ef
#define IN_KEY_SCANCODE_9      0x02ef

#define IN_STICK_FIRE    0x80
#define IN_STICK_FIRE_1  0x80
#define IN_STICK_FIRE_2  0x40
#define IN_STICK_FIRE_3  0x20

#define IN_STICK_UP      0x01
#define IN_STICK_DOWN    0x02
#define IN_STICK_LEFT    0x04
#define IN_STICK_RIGHT   0x08

// -------------- end of constants copied from z88dk/include/_DEVELOPMENT/sdcc/input/input_zx.h ----------------------------

// TODO proper input, sinclair/kempston/redefinable keys
#define kInputScancodeUp	(IN_KEY_SCANCODE_q)
#define kInputScancodeDown	(IN_KEY_SCANCODE_a)
#define kInputScancodeLeft	(IN_KEY_SCANCODE_o)
#define kInputScancodeRight	(IN_KEY_SCANCODE_p)
#define kInputScancodeFire	(IN_KEY_SCANCODE_SPACE)
#define kInputScancodeReset	(IN_KEY_SCANCODE_r)

#define kInputScancodeInputMode	(IN_KEY_SCANCODE_i)


#endif
