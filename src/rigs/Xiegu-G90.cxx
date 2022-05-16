// ----------------------------------------------------------------------------
// Copyright (C) 2020
//              David Freese, W1HKJ
//              Mark Gregory, G4LCH
//
// Version 1.0.8
// This file is part of flrig.
//
// flrig is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// flrig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// aunsigned long int with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include "Xiegu-G90.h"

#include <iostream>
#include <sstream>

const char Xiegu_G90name_[] = "Xiegu-G90";

// these are only defined in this file undef'd at end of file

#define NUM_MODES  5

static int agcval = 0;

enum { LSB_g90, USB_g90, AM_g90, CW_g90, CWR_g90 };

const char *Xiegu_G90modes_[] = {
"LSB", "USB", "AM", "CW", "CW-R", NULL};

static char Xiegu_G90_mode_type[] = {
	'L', 'U', 'U', 'L', 'L', 'U' };

const char Xiegu_G90_mode_nbr[] = {
	0x00, // Select the LSB mode
	0x01, // Select the USB mode
	0x02, // Select the AM mode
	0x03, // Select the CW mode
	0x07, // Select the CW-R mode
};

const char *Xiegu_G90_ssb_bws[] = { "N/A", NULL };
static int Xiegu_G90_vals_ssb_bws[] = { 1, WVALS_LIMIT };

struct bpair {Fl_Widget *widget; std::string lbl;};
static bpair bpcomp;

static void btn_label(void *p)
{
	bpair *bp = (bpair *)p;
	Fl_Button *b = (Fl_Button *)bp->widget;
	const char *lbl = bp->lbl.c_str();
	if (!bp) { std::cout << "invalid bpair" << std::endl; return; }
	if (!b) { std::cout << "button not valid" << std::endl; return; }
	if (!lbl) { std::cout << "invalid label" << std::endl; return; }
	b->label(lbl);
	b->redraw();
}

static GUI Xiegu_G90_widgets[]= {
	{ (Fl_Widget *)btnVol,        2, 125,  50 },	//0
	{ (Fl_Widget *)sldrVOLUME,   54, 125, 156 },	//1
	{ (Fl_Widget *)btnAGC,        2, 145,  50 },	//2
	{ (Fl_Widget *)sldrSQUELCH, 266, 125, 156 },	//3
	{ (Fl_Widget *)sldrPOWER,   266, 145, 156 },	//4
	{ (Fl_Widget *)NULL, 0, 0, 0 }
};

void RIG_Xiegu_G90::initialize()
{
	Xiegu_G90_widgets[0].W = btnVol;
	Xiegu_G90_widgets[1].W = sldrVOLUME;
	Xiegu_G90_widgets[2].W = btnAGC;
	Xiegu_G90_widgets[3].W = sldrSQUELCH;
	Xiegu_G90_widgets[4].W = sldrPOWER;

	btn_icom_select_10->deactivate();
	btn_icom_select_11->deactivate();
	btn_icom_select_12->deactivate();
	btn_icom_select_13->deactivate();

	choice_rTONE->deactivate();
	choice_tTONE->deactivate();

}

RIG_Xiegu_G90::RIG_Xiegu_G90() {
	defaultCIV = 0x70;
	name_ = Xiegu_G90name_;
	modes_ = Xiegu_G90modes_;
	bandwidths_ = Xiegu_G90_ssb_bws;
	bw_vals_ = Xiegu_G90_vals_ssb_bws;
	_mode_type = Xiegu_G90_mode_type;
	adjustCIV(defaultCIV);

	comm_retries = 2;
	comm_wait = 20;
	comm_timeout = 50;
	comm_echo = true;
	comm_rtscts = false;
	comm_rtsplus = true;
	comm_dtrplus = true;
	comm_catptt = true;
	comm_rtsptt = false;
	comm_dtrptt = false;

	widgets = Xiegu_G90_widgets;

	has_smeter = true;
	has_power_out = true;
	has_swr_control = true;

	has_split = false;
	has_split_AB = false;

	has_mode_control = true;
	has_bandwidth_control = false;

	has_power_control = true;
	has_volume_control = true;
	has_sql_control = false;

	has_noise_control = true;

	has_attenuator_control = true;
	has_preamp_control = true;

	has_ptt_control = true;
	has_tune_control = true;

	has_agc_control = true;
	has_extras = true;

	has_cw_wpm = true;
	has_cw_vol = true;

	has_band_selection = true;

	has_compON = false;

	has_nb_level = false;

	precision = 1;
	ndigits = 9;
	A.filter = B.filter = 1;

	def_freq = A.freq = 14074000;
	def_mode = A.imode = 1;
	def_bw = A.iBW = 0;

	B.freq = 7070000;
	B.imode = 1;
	B.iBW = 0;

};

//======================================================================
// Xiegu_G90 unique commands
//======================================================================

bool RIG_Xiegu_G90::check ()
{
	bool ok = false;
	string resp = pre_fm;
	resp += '\x03';
	cmd = pre_to;
	cmd += '\x03';
	cmd.append( post );
	ok = waitFOR(11, "check vfo");
	igett("check()");
	return ok;
}

static bool Xiegu_G90onA = true;

void RIG_Xiegu_G90::selectA()
{
	cmd = pre_to;
	cmd += '\x07';
	cmd += '\x00';
	cmd.append(post);
	set_trace(2, "selectA()", str2hex(cmd.c_str(), cmd.length()));
	waitFB("select A");
	igett("select A");
	Xiegu_G90onA = true;
}

void RIG_Xiegu_G90::selectB()
{
	cmd = pre_to;
	cmd += '\x07';
	cmd += '\x01';
	cmd.append(post);
	isett("selectB()");
	waitFB("select B");
	Xiegu_G90onA = false;
}

unsigned long int RIG_Xiegu_G90::get_vfoA ()
{
	if (useB) return A.freq;
	string resp = pre_fm;
	resp += '\x03';
	cmd = pre_to;
	cmd += '\x03';
	cmd.append( post );
	if (waitFOR(11, "get vfo A")) {
		igett("get_vfoA()");
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p+5] == -1)
				A.freq = 0;
			else
				A.freq = fm_bcd_be(replystr.substr(p+5), 10);
		}
	}
	return A.freq;
}

void RIG_Xiegu_G90::set_vfoA (unsigned long int freq)
{
	A.freq = freq;
	cmd = pre_to;
	cmd += '\x05';
	cmd.append( to_bcd_be( freq, 10 ) );
	cmd.append( post );
	waitFB("set vfo A");
	isett("set_vfoA()");
}

unsigned long int RIG_Xiegu_G90::get_vfoB ()
{
	if (!useB) return B.freq;
	string resp = pre_fm;
	resp += '\x03';
	cmd = pre_to;
	cmd += '\x03';
	cmd.append( post );
	if (waitFOR(11, "get vfo B")) {
		igett("get_vfoB()");
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p+5] == -1)
				A.freq = 0;
			else
				B.freq = fm_bcd_be(replystr.substr(p+5), 10);
		}
	}
	return B.freq;
}

void RIG_Xiegu_G90::set_vfoB (unsigned long int freq)
{
	B.freq = freq;
	cmd = pre_to;
	cmd += '\x05';
	cmd.append( to_bcd_be( freq, 10 ) );
	cmd.append( post );
	waitFB("set vfo B");
	isett("set_vfoB()");
}

bool RIG_Xiegu_G90::can_split()
{
	return true;
}

void RIG_Xiegu_G90::set_split(bool val)
{
	split = val;
	cmd = pre_to;
	cmd += 0x0F;
	cmd += val ? 0x01 : 0x00;
	cmd.append(post);
	waitFB(val ? "set split ON" : "set split OFF");
	isett("set_split()");
}

int RIG_Xiegu_G90::get_split()
{
	int read_split = 0;
	cmd.assign(pre_to);
	cmd.append("\x0F");
	cmd.append( post );
	if (waitFOR(9, "get split")) {
		string resp = pre_fm;
		resp.append("\x0F");
		size_t p = replystr.find(resp);
		if (p != string::npos)
			read_split = replystr[p+5];
		if (read_split != 0xFA) // fail byte
			split = read_split;
	}
	igett("get_split()");
	return split;
}

// Tranceiver PTT on/off
void RIG_Xiegu_G90::set_PTT_control(int val)
{
	cmd = pre_to;
	cmd += '\x1c';
	cmd += '\x00';
	cmd += (unsigned char) val;
	cmd.append( post );
	waitFB("set ptt");
	ptt_ = val;
	isett("set_PTT()");
}

void RIG_Xiegu_G90::tune_rig(int how)
{
    cout << "TUNE" << endl;
    cmd = pre_to;
    cmd.append("\x1c\x01");
    switch (how) {
        default:
        case 0:
            cmd += '\x00';
            break;
        case 1:
            cmd += '\x01';
            break;
        case 2:
            cmd += '\x02';
            break;
    }
    cmd.append( post );
    waitFB("tune rig");
    ICtrace("tune rig", replystr);
}

int RIG_Xiegu_G90::get_tune()
{
    string resp;
    string cstr = "\x1C\x01";
    cmd.assign(pre_to).append(cstr).append(post);
    resp.assign(pre_fm).append(cstr);
    int val = tune_;
    if (waitFOR(8, "get TUNE")) {
        size_t p = replystr.rfind(resp);
        if (p != string::npos)
            val = replystr[p + 6];
    }
    return (tune_ = val);
}



void RIG_Xiegu_G90::set_modeA(int val)
{
	A.imode = val;
	cmd = pre_to;
	cmd += '\x06';
	cmd += Xiegu_G90_mode_nbr[val];
	cmd += A.filter;
	cmd.append( post );
	waitFB("set mode A");
	isett("set mode A()");
}

int RIG_Xiegu_G90::get_modeA()
{
	int md = 0;
	size_t p = 0;
	cmd = pre_to;
	cmd += '\x04';
	cmd.append(post);
	string resp = pre_fm;
	resp += '\x04';

	if (waitFOR(8, "get mode A")) {
		p = replystr.rfind(resp);
		if (p != std::string::npos) {
			if (replystr[p+5] == -1) { md = filA = 0; }
			else {
				for (md = 0; md < NUM_MODES; md++)
					if (replystr[p+5] == Xiegu_G90_mode_nbr[md]) 
						break;
				A.filter = replystr[p+6];
				if (md == NUM_MODES) {
					checkresponse();
					return A.imode;
				}
			}
		}
		igett("get_modeA()");
	} else {
		checkresponse();
		return A.imode;
	}

	A.imode = md;

	return A.imode;
}

void RIG_Xiegu_G90::set_modeB(int val)
{
	B.imode = val;
	cmd = pre_to;
	cmd += '\x06';
	cmd += Xiegu_G90_mode_nbr[val];
	cmd += B.filter;
	cmd.append( post );
	waitFB("set mode B");
	isett("set mode B()");
}

int RIG_Xiegu_G90::get_modeB()
{
	int md = 0;
	size_t p = 0;

	cmd = pre_to;
	cmd += '\x04';
	cmd.append(post);
	string resp = pre_fm;
	resp += '\x04';

	if (waitFOR(8, "get mode B")) {
		igett("get_modeB()");
		p = replystr.rfind(resp);
		if (p != std::string::npos) {
			if (replystr[p+5] == -1) { md = filB = 0; }
			else {
				for (md = 0; md < NUM_MODES; md++)
					if (replystr[p+5] == Xiegu_G90_mode_nbr[md]) 
						break;
				if (md > 6) md -= 2;
				B.filter = replystr[p+6];
				if (md == NUM_MODES) {
					checkresponse();
					return A.imode;
				}
			}
		}
	} else {
		checkresponse();
		return B.imode;
	}

	return B.imode;
}

void RIG_Xiegu_G90::set_attenuator(int val)
{
   if (val) {
		atten_level = 1;
		atten_label("ATT", true);
	} else {
		atten_level = 0;
		atten_label("ATT", false);
	}

	cmd = pre_to;
	cmd += '\x11';
	cmd += atten_level ? '\x01' : '\x00';
	cmd.append( post );
	set_trace(2, "set_attenuator()", str2hex(cmd.c_str(), cmd.length()));
	waitFB("set att");
}

void RIG_Xiegu_G90::set_preamp(int val)
{
	cmd = pre_to;
	cmd += '\x16';
	cmd += '\x02';

	if (val) {
		preamp_label("PRE", true);
		cmd += '\x01';
	} else {
		preamp_label("PRE", false);
		cmd += '\x00';
	}

	cmd.append( post );
	waitFB(	(val == 0) ? "set Preamp OFF" : "set Preamp ON");

	set_trace(2, "set_preamp()", str2hex(cmd.c_str(), cmd.length()));
}


int RIG_Xiegu_G90::get_preamp()
{
	string cstr = "\x16\x02";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(8, "get Preamp Level")) {
		get_trace(2, "get_preamp()", str2hex(replystr.c_str(), replystr.length()));
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			preamp_level = replystr[p+6];
		if (preamp_level == 1)
			preamp_label("PRE", true);
		else
			preamp_label("PRE", false);
	}
	return preamp_level;
}

static int compon = 0;
static int compval = 0;

void RIG_Xiegu_G90::get_compression(int &on, int &val)
{
	on = compon;
	val = compval;
}

void RIG_Xiegu_G90::set_compression(int on, int val)
{
	compon = on;
	if (on) {
		cmd = pre_to;
		cmd.append("\x16\x44");
		cmd += '\x01';
		cmd.append(post);
		waitFB("set Comp ON");
		bpcomp.lbl = "COMP on";
	} else{
		cmd.assign(pre_to).append("\x16\x44");
		cmd += '\x00';
		cmd.append(post);
		waitFB("set Comp OFF");
		bpcomp.lbl = "COMP off";
	}
	bpcomp.widget = btnCompON;
	Fl::awake(btn_label, &bpcomp);
}


// CW controls

void RIG_Xiegu_G90::set_cw_wpm()
{
	cmd.assign(pre_to).append("\x14\x0C"); // values 0-255 = 5 to 50 WPM
	cmd.append(to_bcd(round((progStatus.cw_wpm - 6) * 255 / (50 - 5)), 3));
	cmd.append( post );
	waitFB("SET cw wpm");
}

static int hexval(int hex)
{
	int val = 0;
	val += 10 * ((hex >> 4) & 0x0F);
	val += hex & 0x0F;
	return val;
}

static char hexchr(int val)
{
	static char c;
	c = ((val / 10) << 4) + (val % 10);
	return c;
}

struct meterpair {int mtr; float val;};

// Exact power matches as verified with RIG
static meterpair pwrtbl[] = { 
{ 13, 1 },
{ 26, 2 },
{ 39, 3 },
{ 52, 4 },
{ 65, 5 },
{ 78, 6 },
{ 92, 7 },
{ 105, 8 },
{ 118, 9 },
{ 131, 10 },
{ 144, 11 },
{ 157, 12 },
{ 170, 13 },
{ 183, 14 },
{ 200, 15 },
{ 213, 16 },
{ 226, 17 },
{ 239, 18 },
{ 251, 19 },
{ 255, 20 }
};

void RIG_Xiegu_G90::set_power_control(double val)
{
	cmd = pre_to;
	cmd.append("\x14\x0A");
	int p = 0;
	for (int n = 0; n < 20; n++){
		if (val <= pwrtbl[n].val) {
			p = pwrtbl[n].mtr;
			break;
		}
	}
	cmd += hexchr (p / 100);
	cmd += hexchr (p % 100);
	cmd.append( post );
	set_trace(2, "set_power_control()", str2hex(cmd.c_str(), cmd.length()));
	waitFB("set power");
}

int RIG_Xiegu_G90::get_power_control()
{
	int val = pwrtbl[int(progStatus.power_level) - 1].mtr;

	string cstr = "\x14\x0A";
	string resp = pre_fm;
	cmd = pre_to;
	cmd.append(cstr).append(post);
	resp.append(cstr);
	if (waitFOR(9, "get power")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p + 7] == '\xFD') {
				val = hexval(replystr[p + 6]);
			} else {
				val = 100 * hexval(replystr[p + 6]) + hexval(replystr[p + 7]);
			}
		}
	}
	int pwr = 0;
	for (int n = 0; n < 20; n++) {
		if (val <= pwrtbl[n].mtr) {
			pwr = pwrtbl[n].val;
			break;
		}
	}

	get_trace(2, "get_power_control()", str2hex(replystr.c_str(), replystr.length()));

	return pwr;
}

void RIG_Xiegu_G90::get_pc_min_max_step(double &min, double &max, double &step)
{
	min = 1; max = 20; step = 1;
}

/*
1W = xFE xFE x88 xE0 x14 x0A x00 x00 xFD
2W = xFE xFE x88 xE0 x14 x0A x00 x13 xFD
3W = xFE xFE x88 xE0 x14 x0A x00 x26 xFD
4W = xFE xFE x88 xE0 x14 x0A x00 x40 xFD
5W = xFE xFE x88 xE0 x14 x0A x00 x53 xFD
6W = xFE xFE x88 xE0 x14 x0A x00 x67 xFD
7W = xFE xFE x88 xE0 x14 x0A x00 x80 xFD
8W = xFE xFE x88 xE0 x14 x0A x00 x93 xFD
9W = xFE xFE x88 xE0 x14 x0A x01 x07 xFD
10W = xFE xFE x88 xE0 x14 x0A x01 x20 xFD
11W = xFE xFE x88 xE0 x14 x0A x01 x34 xFD
12W = xFE xFE x88 xE0 x14 x0A x01 x47 xFD
13W = xFE xFE x88 xE0 x14 x0A x01 x61 xFD
14W = xFE xFE x88 xE0 x14 x0A x01 x74 xFD
15W = xFE xFE x88 xE0 x14 x0A x01 x87 xFD
16W = xFE xFE x88 xE0 x14 x0A x02 x01 xFD
17W = xFE xFE x88 xE0 x14 x0A x02 x14 xFD
18W = xFE xFE x88 xE0 x14 x0A x02 x28 xFD
19W = xFE xFE x88 xE0 x14 x0A x02 x41 xFD
20W = xFE xFE x88 xE0 x14 x0A x02 x55 xFD
*/

int RIG_Xiegu_G90::get_power_out(void)
{
	string cstr = "\x15\x11";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	int mtr= 0;
	if (waitFOR(5, "get power out")) {
	    cout << "GET PWR" << endl;
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p + 7] == '\xFD') {
                mtr = ceil(fm_bcd(replystr.substr(p + 6), 1) );
			} else {
                mtr = ceil(fm_bcd(replystr.substr(p + 6), 1) );
                mtr = mtr + ceil(fm_bcd(replystr.substr(p + 7), 1) )+100;
			}
		}
	}
    mtr = (int)ceil(mtr / 10);
	get_trace(2, "get_power_out()", str2hex(replystr.c_str(), replystr.length()));
	return mtr;
}

// Volume control val 0 ... 100
void RIG_Xiegu_G90::set_volume_control(int val)
{
	cmd = pre_to;
	cmd.append("\x14\x01");
	val *= 255; val /= 100;
	cmd += hexchr(val / 100);
	cmd += hexchr(val % 100);
	cmd.append( post );
	set_trace(2, "set_volume_control()", str2hex(cmd.c_str(), cmd.length()));
	waitFB("set vol");
}

int RIG_Xiegu_G90::get_volume_control()
{
	int val = progStatus.volume;
	string cstr = "\x14\x01";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(5, "get vol")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p + 7] == '\xFD') {
				val = hexval(replystr[p + 6]);
			} else {
				val = 100 * hexval(replystr[p + 6]) + hexval(replystr[p + 7]);
			}
		}
		val *= 100;
		val /= 255;
	}
	get_trace(2, "get_volume_control()", str2hex(replystr.c_str(), replystr.length()));
	return val;
}

void RIG_Xiegu_G90::set_squelch(int val)
{
	cmd = pre_to;
	cmd.append("\x14\x03");
	cmd.append(bcd255(val));
	cmd.append( post );
	set_trace(2, "set_squelch()", str2hex(cmd.c_str(), cmd.length()));
	waitFB("set Sqlch");
}

int  RIG_Xiegu_G90::get_squelch()
{
	int val = progStatus.squelch;
	string cstr = "\x14\x03";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(5, "get squelch")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			val = num100(replystr.substr(p+6));
	}
	get_trace(2, "get_squelch()", str2hex(replystr.c_str(), replystr.length()));
	return val;
}

void RIG_Xiegu_G90::get_vol_min_max_step(int &min, int &max, int &step)
{
	min = 0; max = 100; step = 1;
}

static meterpair smtrtbl[] = {
	{ 0,   0  }, // s0 -128dbm
	{ 10,  5  }, // s1 -121dbm
	{ 22,  11 }, // s2 -115dbm
	{ 35,  16 }, // s3 -109dbm	
	{ 56,  21 }, // s4 -102dbm
	{ 71,  26 }, // s5 -95dbm
	{ 89,  31 }, // s6 -88dbm
	{ 109, 37 }, // s7 -80dbm
	{ 132, 43 }, // s8 -71dbm
	{ 147, 50 }, // s9 -65dbm
	{ 168, 58 }, // s9+10 -57dbm
	{ 173, 66 }, // s9+20 -55dbm
	{ 183, 74 }, // s9+30 -51dbm
	{ 193, 82 }, // s9+40 -47dbm
	{ 201, 90 }, // s9+50 -45dbm
	{ 209, 100 } // s9+60 -42dbm
};

int RIG_Xiegu_G90::get_smeter()
{
	string cstr = "\x15\x02";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	int mtr= 0;
	if (waitFOR(8, "get smeter")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p + 7] == '\xFD') {
				mtr = hexval(replystr[p + 6]);
			} else {
				mtr = hexval(replystr[p + 6]);
				mtr += 100 * hexval(replystr[p + 7]);
			}
			if (mtr < 0) mtr = 0;
			if (mtr > 241) mtr = 241;
			size_t i = 0;
			for (i = 0; i < sizeof(smtrtbl) / sizeof(meterpair) - 1; i++)
				if (mtr >= smtrtbl[i].mtr && mtr < smtrtbl[i+1].mtr)
					break;
			mtr = (int)ceil(smtrtbl[i].val + 
				(smtrtbl[i+1].val - smtrtbl[i].val)*(mtr - smtrtbl[i].mtr)/(smtrtbl[i+1].mtr - smtrtbl[i].mtr));
			if (mtr > 100) mtr = 100;
		}
	}
	get_trace(2, "get_smeter()", str2hex(replystr.c_str(), replystr.length()));
	return mtr;
}

int RIG_Xiegu_G90::get_swr()
{
    string cstr = "\x15\x12";
    string resp = pre_fm;
    resp.append(cstr);
    cmd = pre_to;
    cmd.append(cstr);
    cmd.append( post );
    int mtr= -1;
    if (waitFOR(6, "get SWR")) {
        get_trace(2, "get_swr()", str2hex(replystr.c_str(), replystr.length()));
        size_t p = replystr.rfind(resp);
        if (p != string::npos) {
            mtr = ceil(fm_bcd(replystr.substr(p + 6), 1) );
        }
    }
    mtr = (int)ceil(mtr /10);
    return mtr;
}


void RIG_Xiegu_G90::set_noise(bool val)
{  
   cmd = pre_to;
	cmd.append("\x16\x22");
	cmd += val ? 1 : 0;
	cmd.append(post);
	set_trace(2, "set_noise()", str2hex(cmd.c_str(), cmd.length()));
	waitFB("set noise");
}

int RIG_Xiegu_G90::get_noise()
{
	string cstr = "\x16\x22";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(8, "get noise")) {
		size_t p = replystr.rfind(resp);
	get_trace(2, "get_noise()", str2hex(replystr.c_str(), replystr.length()));
	if (p != string::npos)
		return (replystr[p+6] ? 1 : 0);
	}
	return progStatus.noise;
}

void RIG_Xiegu_G90::get_band_selection(int v)
{
	int bandfreq, bandmode;
	switch (v) {
		default:
		case 1: bandfreq = progStatus.f160;
				bandmode = progStatus.m160;
				break;
		case 2: bandfreq = progStatus.f80;
				bandmode = progStatus.m80;
				break;
		case 3: bandfreq = progStatus.f40;
				bandmode = progStatus.m40;
				break;
		case 4: bandfreq = progStatus.f30;
				bandmode = progStatus.m30;
				break;
		case 5: bandfreq = 14074000L;
				bandmode = progStatus.m20;
				break;
		case 6: bandfreq = progStatus.f17;
				bandmode = progStatus.m17;
				break;
		case 7: bandfreq = progStatus.f15;
				bandmode = progStatus.m15;
				break;
		case 8: bandfreq = progStatus.f12;
				bandmode = progStatus.m12;
				break;
		case 9: bandfreq = progStatus.f10;
				bandmode = progStatus.m10;
				break;
	}
	if (useB) {
		set_vfoB(bandfreq);
		set_modeB(bandmode);
	} else {
		set_vfoA(bandfreq);
		set_modeA(bandmode);
		}
	set_trace(1, "get band selection");
}

void RIG_Xiegu_G90::set_band_selection(int v)
{

	switch (v) {
		default:
		case 1: progStatus.f160 = vfo->freq;
				progStatus.m160 = vfo->imode;
				break;
		case 2: progStatus.f80 = vfo->freq;
				progStatus.m80 = vfo->imode;
				break;
		case 3: progStatus.f40 = vfo->freq;
				progStatus.m40 = vfo->imode;
				break;
		case 4: progStatus.f30 = vfo->freq;
				progStatus.m30 = vfo->imode;
				break;
		case 5: progStatus.f20 = vfo->freq;
				progStatus.m20 = vfo->imode;
				break;
		case 6: progStatus.f17 = vfo->freq;
				progStatus.m17 = vfo->imode;
				break;
		case 7: progStatus.f15 = vfo->freq;
				progStatus.m15 = vfo->imode;
				break;
		case 8: progStatus.f12 = vfo->freq;
				progStatus.m12 = vfo->imode;
				break;
		case 9: progStatus.f10 = vfo->freq;
				progStatus.m10 = vfo->imode;
				break;
	}
	set_trace(1, "set_band_selection()");
}

int  RIG_Xiegu_G90::get_agc()
{
    cmd = pre_to;
    cmd.append("\x16\x12");
    cmd.append(post);
    if (waitFOR(8, "get AGC")) {
        size_t p = replystr.find(pre_fm);
        if (p == string::npos) return agcval;
        return (agcval = replystr[p + 6]); // 1 = off, 2 = FAST, 3 = SLOW 4 = AUTO
    }
    get_trace(2, "get_agc()", str2hex(replystr.c_str(), replystr.length()));
    return agcval;
}

int RIG_Xiegu_G90::incr_agc()
{
    agcval++;
    if (agcval == 4) agcval = 0;
    cmd = pre_to;
    cmd.append("\x16\x12");
    cmd += agcval;
    cmd.append(post);
    waitFB("set AGC");
    return agcval;
}

static const char *agcstrs[] = {"AGC", "FST", "SLO","AUT"};
const char *RIG_Xiegu_G90::agc_label()
{
    return agcstrs[agcval];
}

int  RIG_Xiegu_G90::agc_val()
{
    return (agcval);
}

