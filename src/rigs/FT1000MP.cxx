/*
 * Yaesu FT-1000MP drivers
 *
 * a part of flrig
 *
 * Copyright 2011, Dave Freese, W1HKJ
 *
 */

#include "FT1000MP.h"
#include <stdio.h>
#include <stdlib.h>

static const char FT1000MPname_[] = "FT-1000MP";

static const char *FT1000MP_modes[] = {
	"LSB",					// 0
	"USB", 					// 1
	"CW-U",   "CW-L", 		// 2, 2+
	"AM",     "AM-syn",		// 3, 3+
	"FM", 					// 4
	"RTTY-L", "RTTY-U",		// 5, 5+
	"PKT-L",  "PKT-FM",		// 6, 6+
	NULL};

static const int FT1000MP_def_bw[] = {
6, 6, 18, 18, 0, 0, 0, 18, 18, 6, 6 };

static const char FT1000MP_mode_type[] = {
	'L', 
	'U', 
	'U', 'L', 
	'U', 'U', 
	'U',
	'L', 'U', 
	'L', 'U' };

static const char FT1000MP_mode[] = {
	0,
	1,
	2, 2,
	3, 3,
	4,
	5, 5,
	6, 6 };

static const char FT1000MP_alt_mode[] = {
	0,			// 0
	0,			// 1
	0,	1,		// 2
	0,	1,		// 3
	0,			// 4
	0,	1,		// 5
	0,	1 };	// 6

static const char *FT1000MP_widths[] = {
"---/6.0", "---/2.4", "---/2.0", "---/500", "---/250",
"2.4/6.0", "2.4/2.4", "2.4/2.0", "2.4/500", "2.4/250",
"2.0/6.0", "2.0/2.4", "2.0/2.0", "2.0/500", "2.0/250",
"500/6.0", "500/2.4", "500/2.0", "500/500", "500/250",
"250/6.0", "250/2.4", "250/2.0", "250/500", "250/250", NULL };

RIG_FT1000MP::RIG_FT1000MP() {
// base class values
	name_ = FT1000MPname_;
	modes_ = FT1000MP_modes;
	bandwidths_ = FT1000MP_widths;
	comm_baudrate = BR4800;
	stopbits = 2;
	comm_retries = 2;
	comm_wait = 5;
	comm_timeout = 50;
	serloop_timing = 200;
	comm_rtscts = true;
	comm_rtsplus = false;
	comm_dtrplus = true;
	comm_catptt = true;
	comm_rtsptt = false;
	comm_dtrptt = false;
	A.freq = 14070000;
	A.imode = 1;
	A.iBW = 1;
	B.freq = 3580000;
	B.imode = 1;
	B.iBW = 1;
	precision = 10;
	max_power = 200;

	has_swr_control =
	has_alc_control =
	has_mode_control =
	has_bandwidth_control =
	has_ptt_control =
	has_tune_control = 
	has_get_info = true;

};

void RIG_FT1000MP::init_cmd()
{
	cmd = "00000";
	for (size_t i = 0; i < 5; i++) cmd[i] = 0;
}

void RIG_FT1000MP::initialize()
{
	init_cmd();
	cmd[4] = 0x81; // switch antenna tuner on
	sendCommand(cmd,0);
LOG_INFO("%s", str2hex(cmd.c_str(), 5));
//	selectA();
}

/*
 returns 32 bytes
 first 16 for vfo-A
 0 - band selection
 1,2,3,4 operating frequency
 5,6 clarifier offset
 7 operating mode
 8 if filter selection
 9 vfo/mem operating flags
 a,b,c,d,e,f NOT used
 repeated for vfo-B

Data captured by AF2M, Mitch

Mode changes bytes 7 / 8; counting from 0
         ---------------------||-||---------------------------------------------------------------------
LSB    : 08 00 57 71 00 00 00 00 11 00 11 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
USB    : 08 00 57 71 00 00 00 01 11 00 11 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
CW-L   : 08 00 57 75 10 00 00 02 01 00 11 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
CW-U   : 08 00 57 75 10 00 00 02 11 00 11 91 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
LSB    : 08 00 57 71 00 00 00 00 11 00 11 11 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
RTTY-L : 08 00 57 63 B8 00 00 05 11 00 11 11 11 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
RTTY-U : 08 00 57 7E 48 00 00 05 91 00 11 11 91 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48

Bandwidth changes (in LSB MODE) 
8.215 filter is in thru mode
Only changing 455 filter, cycling thru from 6k, 2.4k, 2.0k,500, 250.
         ------------------------||---------------------------------------------------------------------
6k     : 08 00 57 71 00 00 00 00 00 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
2.4k   : 08 00 57 71 00 00 00 00 01 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
2.0k   : 08 00 57 71 00 00 00 00 02 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
500    : 08 00 57 71 00 00 00 00 03 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
250    : 08 00 57 71 00 00 00 00 04 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48

8.215 filter is in 500 hz mode.
         ------------------------||---------------------------------------------------------------------
6k     : 08 00 57 71 00 00 00 00 40 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
2.4k   : 08 00 57 71 00 00 00 00 41 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
2.0k   : 08 00 57 71 00 00 00 00 42 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
500    : 08 00 57 71 00 00 00 00 43 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48
250    : 08 00 57 71 00 00 00 00 44 00 00 01 81 81 11 0A 08 00 57 72 60 00 00 00 30 00 30 91 11 11 11 48

Mode changes bytes 7 / 8; counting from 0
         |byte 7| |byte 8|
LSB    : 00000000 00010001
USB    : 00000001 00010001
CW-L   : 00000010 00000001
CW-U   : 00000010 00010001
LSB    : 00000000 00010001
RTTY-L : 00000101 00010001
RTTY-U : 00000101 10010001

         |byte 8|
6k     : 00000000
2.4k   : 00000001
2.0k   : 00000010
500    : 00000011
250    : 00000100

8.215 filter is in 500 hz mode.
         |byte 8|
6k     : 01000000
2.4k   : 01000001
2.0k   : 01000010
500    : 01000011
250    : 01000100
*/

const unsigned char data1[] = {
0x08, 0x00, 0x57, 0x71, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x01, 0x81, 0x81, 0x11, 0x0A,
0x08, 0x00, 0x57, 0x72, 0x60, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x91, 0x11, 0x11, 0x11, 0x48
};
const unsigned char data2[] = {
0x08, 0x00, 0x57, 0x71, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x81, 0x81, 0x11, 0x0A,
0x08, 0x00, 0x57, 0x72, 0x60, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x91, 0x11, 0x11, 0x11, 0x48
};
const unsigned char data3[] = {
0x08, 0x00, 0x57, 0x71, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x01, 0x81, 0x81, 0x11, 0x0A,
0x08, 0x00, 0x57, 0x72, 0x60, 0x00, 0x00, 0x03, 0xB0, 0x00, 0x30, 0x91, 0x11, 0x11, 0x11, 0x48
};
const unsigned char amsync[] = {
0x08, 0x00, 0x57, 0x67, 0x01, 0x00, 0x00, 0x03, 0x80, 0x00, 0x11, 0x11, 0x91, 0x91, 0x11, 0x08,
0x08, 0x00, 0x57, 0x67, 0x02, 0x00, 0x00, 0x01, 0x11, 0x00, 0x11, 0x91, 0x11, 0x11, 0x11, 0xFA
};

void RIG_FT1000MP::get_info(void)
{
	unsigned char *p = 0;
	int ret = 0;
	int alt = 0;
	int md = 0;
	int i;
	init_cmd();
	cmd[3] = 0x03;  // read both vfo's
	cmd[4] = 0x10;
	ret = sendCommand(cmd, 32);
	p = (unsigned char *)replybuff;
//	p = (unsigned char *)amsync; ret = 32;
//LOG_INFO("%d : %s", ret, str2hex(p, ret));
	if (ret == 32) {
		// vfo A data string
		A.freq = ((((((p[1]<<8) + p[2])<<8) + p[3])<<8) + p[4])*10/16;
		md = p[7] & 0x07;
		alt = p[8] & 0x80;
		for (i = 0; i < 11; i++) if (FT1000MP_mode[i] == md) break;
		if (i == 11) i = 0;
		A.imode = i + ((alt == 128) ? 1 : 0);
		A.iBW = 5*((p[8] & 0x70) >> 4) + (p[8] & 0x07);
		if (A.iBW > 24) A.iBW = 24;

		p += 16; // vfo B data string
		B.freq = ((((((p[1]<<8) + p[2])<<8) + p[3])<<8) + p[4])*10/16;
		md = p[7] & 0x07;
		alt = p[8] & 0x80;
		for (i = 0; i < 11; i++) if (FT1000MP_mode[i] == md) break;
		if (i == 11) i = 0;
		B.imode = i + ((alt == 128) ? 1 : 0);
		B.iBW = 5*((p[8] & 0x70) >> 4) + (p[8] & 0x07);
		if (B.iBW > 24) B.iBW = 24;
	}
}

long RIG_FT1000MP::get_vfoA ()
{
	return A.freq;
}

long RIG_FT1000MP::get_vfoB ()
{
	return B.freq;
}

void RIG_FT1000MP::set_vfoA (long freq)
{
	A.freq = freq;
	init_cmd();
	freq /=10; // 1000MP does not support 1 Hz resolution
	for (int i = 0; i < 4; i++) {
		cmd[i] = (unsigned char)(freq % 10); freq /= 10;
		cmd[i] |= (unsigned char)((freq % 10) * 16); freq /= 10;
	}
	cmd[4] = 0x0A;
	sendCommand(cmd, 0);
LOG_INFO("%s", str2hex(cmd.c_str(), cmd.length()));
}

void RIG_FT1000MP::set_vfoB (long freq)
{
	B.freq = freq;
	init_cmd();
	freq /=10; // 1000MP does not support 1 Hz resolution
	for (int i = 0; i < 4; i++) {
		cmd[i] = (unsigned char)(freq % 10); freq /= 10;
		cmd[i] |= (unsigned char)((freq % 10) * 16); freq /= 10;
	}
	cmd[4] = 0x8A;
	sendCommand(cmd, 0);
LOG_INFO("%s", str2hex(cmd.c_str(), cmd.length()));
}

int RIG_FT1000MP::get_modeA()
{
	return A.imode;
}

int RIG_FT1000MP::get_modeB()
{
	return B.imode;
}

void RIG_FT1000MP::set_modeA(int val)
{
	A.imode = val;
	init_cmd();
	cmd[3] = val;
	if (val > 6) cmd[3]++;
	cmd[4] = 0x0C;
	sendCommand(cmd, 0);
LOG_INFO("%s, %s", FT1000MP_modes[A.imode], str2hex(cmd.c_str(),5));
	get_info();
}

void RIG_FT1000MP::set_modeB(int val)
{
	B.imode = val;
	init_cmd();
	cmd[3] = val;
	if (val > 6) cmd[3]++;
	cmd[4] = 0x0C;
	sendCommand(cmd, 0);
LOG_INFO("%s, %s", FT1000MP_modes[B.imode], str2hex(cmd.c_str(),5));
	get_info();
}

int RIG_FT1000MP::get_modetype(int n)
{
	return FT1000MP_mode_type[n];
}

int RIG_FT1000MP::get_bwA()
{
	return A.iBW;
}

void RIG_FT1000MP::set_bwA(int val)
{
	int first_if = val / 5;
	int second_if = val % 5;

	if (!first_if) first_if += 5;
	--first_if;

	if (!second_if) second_if += 5;
	--second_if;

	A.iBW = val;

	init_cmd();
	cmd[0] = 0x01; // 1st IF
	cmd[3] = first_if;
	cmd[4] = 0x8C;
	sendCommand(cmd, 0);
LOG_INFO("%s, %s", FT1000MP_widths[A.iBW], str2hex(cmd.c_str(), 5));
	cmd[0] = 0x02; // 2nd IF
	cmd[3] = second_if;
	sendCommand(cmd, 0);
LOG_INFO("%s, %s", FT1000MP_widths[A.iBW], str2hex(cmd.c_str(), 5));
}

int RIG_FT1000MP::get_bwB()
{
	return B.iBW;
}

void RIG_FT1000MP::set_bwB(int val)
{
	B.iBW = val;
	int first_if = val / 5;
	int second_if = val % 5;
	if (!first_if) first_if += 5;
	--first_if;
	first_if += 0x80; // vfo-B
	if (!second_if) second_if += 5;
	--second_if;
	second_if += 0x80; // vfo-B

	init_cmd();
	cmd[0] = 0x01; // 1st IF
	cmd[3] = first_if;
	cmd[4] = 0x8C;
	sendCommand(cmd, 0);
LOG_INFO("%s, %s", FT1000MP_widths[B.iBW], str2hex(cmd.c_str(), 5));
	cmd[0] = 0x02; // 2nd IF
	cmd[3] = second_if;
	sendCommand(cmd, 0);
LOG_INFO("%s, %s", FT1000MP_widths[B.iBW], str2hex(cmd.c_str(), 5));
}

int  RIG_FT1000MP::def_bandwidth(int m)
{
	return FT1000MP_def_bw[m];
}


void RIG_FT1000MP::selectA()
{
	init_cmd();
	cmd[4] = 0x05;
	sendCommand(cmd, 0);
LOG_INFO("%s", str2hex(cmd.c_str(), 5));
}

void RIG_FT1000MP::selectB()
{
	init_cmd();
	cmd[3] = 0x01;
	cmd[4] = 0x05;
	sendCommand(cmd, 0);
LOG_INFO("%s", str2hex(cmd.c_str(), 5));
}

void RIG_FT1000MP::set_split(bool val)
{
	split = val;
	init_cmd();
	cmd[3] = val ? 0x01 : 0x00;
	cmd[4] = 0x01;
	sendCommand(cmd, 0);
LOG_INFO("%s", str2hex(cmd.c_str(), 5));
}


// Tranceiver PTT on/off
void RIG_FT1000MP::set_PTT_control(int val)
{
	init_cmd();
	if (val) cmd[3] = 1;
	else	 cmd[3] = 0;
	cmd[4] = 0x0F;
	sendCommand(cmd, 0);
LOG_INFO("%s", str2hex(cmd.c_str(), 5));
}

void RIG_FT1000MP::tune_rig()
{
	init_cmd();
	cmd[4] = 0x82; // start antenna tuner
	sendCommand(cmd,0);
	LOG_INFO("%s", str2hex(cmd.c_str(), 5));
}

int  RIG_FT1000MP::get_power_out(void)
{
// power table measured by AF2M
//static int ptable[][] = { {39, 10}, {80, 25}, {122, 50}, {144, 75}, {255, 200} };
	float m, b, pout;
	int pwr;
	unsigned char val = 0;
	init_cmd();
	cmd[0] = 0x80;
	cmd[4] = 0xF7;
	if (sendCommand(cmd,5)) {
		val = (unsigned char)(replybuff[0]);
		if (val < 39) {
			m = 10.0 / 39.0; b = 0;
		} else if (val < 80) {
			m = (25.0 - 15.0)/(80.0 - 39.0);
			b = 25.0 - m * 80.0;
		} else if (val < 122) {
			m = (50.0 - 25.0)/(122.0 - 80.0);
			b = 50.0 - m * 122.0;
		} else if (val < 144) {
			m = (75.0 - 50.0)/(144.0 - 122.0);
			b = 75.0 - m * 144.0;
		} else {
			m = (200.0 - 75.0)/(255.0 - 144.0);
			b = 200.0 - m * 255.0;
		}
		pout = m*val + b;
		pwr = (int)pout;
		if (pwr > 200) pwr = 200;
		if (pwr < 0) pwr = 0;
		LOG_INFO("%s => %d",str2hex(replybuff,1), pwr);
	}
	return (int)(200 * sqrt(pwr/200.0) + 0.5);
}

int  RIG_FT1000MP::get_smeter(void)
{
	unsigned char val = 0;
	init_cmd();
	cmd[4] = 0xF7;
	if (sendCommand(cmd,5)) {
		val = (unsigned char)(replybuff[0]);
		LOG_INFO("%s => %d",str2hex(replybuff,1), val);
	}
	return val * 100 / 255;
}

int  RIG_FT1000MP::get_swr(void)
{
	unsigned char val = 0;
	init_cmd();
	cmd[0] = 0x85;
	cmd[4] = 0xF7;
	if (sendCommand(cmd,5)) {
		val = (unsigned char)(replybuff[0]);
		LOG_INFO("%s => %d",str2hex(replybuff,1), val);
	}
	return val * 100 / 255;
}

int  RIG_FT1000MP::get_alc(void)
{
	unsigned char val = 0;
	init_cmd();
	cmd[0] = 0x81;
	cmd[4] = 0xF7;
	if (sendCommand(cmd,5)) {
		val = (unsigned char)(replybuff[0]);
		LOG_INFO("%s => %d",str2hex(replybuff,1), val);
	}
	return val * 100 / 255;
}

