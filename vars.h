/*----------------------------------------------------------------------------
VARS.H
----------------------------------------------------------------------------*/
#ifndef VAR_DEFS          // Make sure this file is included only once
#define VAR_DEFS 1
/*----------------------------------------------
Setup variable declaration macros.
----------------------------------------------*/
#ifndef VAR_DECLS
# define _DECL extern
# define _INIT(x)
#else
# define _DECL
# define _INIT(x)  = x
#endif
/*---------------------------------------------
 Bits
---------------------------------------------*/
_DECL int Sony_bits _INIT(12);
_DECL int Samsung_bits _INIT(32);
_DECL int Panasonic_bits _INIT(48);
/*----------------------------------------------
Samsung TV
----------------------------------------------*/
_DECL unsigned long SamTV_power _INIT(0x7F802FD);
_DECL unsigned long SamTV_v_up _INIT(0x7F807F8);
_DECL unsigned long SamTV_v_down _INIT(0x7F80BF4);
_DECL unsigned long SamTV_c_up _INIT(0x7F812ED);
_DECL unsigned long SamTV_c_down _INIT(0x7F810EF);
_DECL unsigned long SamTV_mute _INIT(0x7F80FF0);
/*----------------------------------------------
Sony TV
----------------------------------------------*/
_DECL unsigned long SonyTV_power _INIT(0xA90);
_DECL unsigned long SonyTV_v_up _INIT(0x490);
_DECL unsigned long SonyTV_v_down _INIT(0xC90);
_DECL unsigned long SonyTV_c_up _INIT(0x90);
_DECL unsigned long SonyTV_c_down _INIT(0x890);
_DECL unsigned long SonyTV_mute _INIT(0x290);
/*----------------------------------------------
Sony CD Player
----------------------------------------------*/
_DECL unsigned long SonyCD_power _INIT(0xA91);
_DECL unsigned long SonyCD_v_up _INIT(0x491);
_DECL unsigned long SonyCD_v_down _INIT(0xC91);
_DECL unsigned long SonyCD_play _INIT(0x4D1);
_DECL unsigned long SonyCD_pause _INIT(0x9D1);
_DECL unsigned long SonyCD_stop _INIT(0x1D1);
_DECL unsigned long SonyCD_next _INIT(0x8D1);
_DECL unsigned long SonyCD_prev _INIT(0xD1);
_DECL unsigned long SonyCD_shuffle _INIT(0xAD1);
/*----------------------------------------------
Panasonic DVD Player
----------------------------------------------*/
_DECL unsigned long DVD_power _INIT(0x40040500BCB9);
_DECL unsigned long DVD_v_up _INIT(0x400405000401);
_DECL unsigned long DVD_v_down _INIT(0x400405008481);
_DECL unsigned long DVD_play _INIT(0x400405005055);
_DECL unsigned long DvD_pause _INIT(0x400405006065);
_DECL unsigned long DVD_stop _INIT(0x400405000005);
_DECL unsigned long DVD_mute _INIT(0x400405004C49);
_DECL unsigned long DVD_ff _INIT(0x400405005257);
_DECL unsigned long DVD_rew _INIT(0x400405009297);
_DECL unsigned long DVD_up _INIT(0x400405006C69);
_DECL unsigned long DVD_down _INIT(0x40040500ACA9);
_DECL unsigned long DVD_left _INIT(0x40040500ECE9);
_DECL unsigned long DVD_right _INIT(0x400405006C69);
_DECL unsigned long DVD_select _INIT(0x400405006366);
#endif
/*----------------------------------------------------------------------------
----------------------------------------------------------------------------*/
