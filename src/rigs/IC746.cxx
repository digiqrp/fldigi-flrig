/*
 * Icom IC-746, 746PRO
 * 
 * a part of flrig
 *
 * Copyright 2009, Dave Freese, W1HKJ
 *
 */

#include "IC746.h"

//=============================================================================
// IC-746, IC746PRO
//=============================================================================

const char IC746name_[] = "IC-746";

const char *IC746modes_[] = {
		"LSB", "USB", "AM", "CW", "RTTY", "FM", "CW-R", "RTTY-R", NULL};
// mode values are 0, 1, 2, 3, 4, 5, 7, 8
const char IC746_mode_type[] =
	{ 'L', 'U', 'U', 'U', 'L', 'U', 'L', 'U'};

const char *IC746_widths[] = { "NORM", "NARR", NULL};

RIG_IC746::RIG_IC746() {
	defaultCIV = 0x56;
	name_ = IC746name_;
	modes_ = IC746modes_;
	bandwidths_ = IC746_widths;
	_mode_type = IC746_mode_type;

	comm_baudrate = BR9600;
	stopbits = 1;
	comm_retries = 2;
	comm_wait = 5;
	comm_timeout = 50;
	comm_echo = true;
	comm_rtscts = false;
	comm_rtsplus = true;
	comm_dtrplus = true;
	comm_catptt = true;
	comm_rtsptt = false;
	comm_dtrptt = false;
	A.imode = 1;
	A.iBW = 0;
	A.freq = 14070000L;
	B.imode = 1;
	B.iBW = 0;
	B.freq = 14070000L;
	A.iBW = 1;
	ICvol = 0;

	has_power_control = true;
	has_volume_control = true;
	has_mode_control = true;
	has_bandwidth_control = true;
	has_micgain_control = true;
	has_notch_control = true;
	has_attenuator_control = true;
	has_preamp_control = true;
	has_ifshift_control = true;
	has_ptt_control = true;
	has_tune_control = true;
	has_swr_control = true;
	has_noise_control = true;
	has_noise_reduction = true;
	has_noise_reduction_control = true;
	has_alc_control = true;
	has_rf_control = true;
	has_sql_control = true;
	restore_mbw = true;

};

//=============================================================================
// 746PRO
const char IC746PROname_[] = "IC-746PRO";

const char *IC746PROmodes_[] = {
		"LSB", "USB", "AM", "CW", "RTTY", "FM", "CW-R", "RTTY-R",
		"D-LSB", "D-USB", "D-FM", NULL};

const char IC746PRO_mode_type[] =
	{ 'L', 'U', 'U', 'U', 'L', 'U', 'L', 'U',
	  'L', 'U', 'U' };

const char *IC746PRO_SSBwidths[] = {
  "50",  "100",  "150",  "200",  "250",  "300",  "350",  "400",  "450",  "500",
"600",   "700",  "800",  "900", "1000", "1100", "1200", "1300", "1400", "1500",
"1600", "1700", "1800", "1900", "2000", "2100", "2200", "2300", "2400", "2500",
"2600", "2700", "2800", "2900", "3000", "3100", "3200", "3300", "3400", "3500",
"3600",
NULL};

const char *IC746PRO_RTTYwidths[] = {
  "50",  "100",  "150",  "200",  "250",  "300",  "350",  "400",  "450",  "500",
 "600",  "700",  "800",  "900", "1000", "1100", "1200", "1300", "1400", "1500",
"1600", "1700", "1800", "1900", "2000", "2100", "2200", "2300", "2400", "2500",
"2600", "2700",
NULL};

const char *IC746PRO_AMFMwidths[] = { "FILT-1", "FILT-2", "FILT-3", NULL };

RIG_IC746PRO::RIG_IC746PRO() {
	defaultCIV = 0x66;
	name_ = IC746PROname_;
	modes_ = IC746PROmodes_;
	bandwidths_ = IC746PRO_SSBwidths;
	_mode_type = IC746PRO_mode_type;
	atten_level = 0;
	preamp_level = 0;
	def_mode = 9;
	defbw_ = 32;
	deffreq_ = 14070000;
	adjustCIV(defaultCIV);
};

void RIG_IC746::selectA()
{
	cmd = pre_to;
	cmd += '\x07';
	cmd += '\x00';
	cmd.append(post);
	waitFB("sel A");
}

void RIG_IC746::selectB()
{
	cmd = pre_to;
	cmd += '\x07';
	cmd += '\x01';
	cmd.append(post);
	waitFB("sel B");
}

long RIG_IC746::get_vfoA ()
{
	string cstr = "\x03";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(11, "get vfo A")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			A.freq = fm_bcd_be(&replystr[p+5], 10);
	}
	return A.freq;
}

void RIG_IC746::set_vfoA (long freq)
{
	A.freq = freq;
	cmd = pre_to;
	cmd += '\x05';
	cmd.append( to_bcd_be( freq, 10 ) );
	cmd.append( post );
	waitFB("set vfo A");
}

long RIG_IC746::get_vfoB ()
{
	string cstr = "\x03";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(11, "get vfo B")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			B.freq = fm_bcd_be(&replystr[p+5], 10);
	}
	return B.freq;
}

void RIG_IC746::set_vfoB (long freq)
{
	B.freq = freq;
	cmd = pre_to;
	cmd += '\x05';
	cmd.append( to_bcd_be( freq, 10 ) );
	cmd.append( post );
	waitFB("set vfo B");
}

int RIG_IC746::get_smeter()
{
	string cstr = "\x15\x02";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(9, "get smeter")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			return fm_bcd(&replystr[p+6], 3) / 2.55;
	}
	return 0;
}

// Volume control val 0 ... 100

void RIG_IC746::set_volume_control(int val)
{
	ICvol = (int)(val);
	cmd = pre_to;
	cmd.append("\x14\x01");
	cmd.append(to_bcd(ICvol, 3));
	cmd.append( post );
	waitFB("set vol");
}

int RIG_IC746::get_volume_control()
{
	string cstr = "\x14\x01";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(9, "get vol")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			return ((int)(fm_bcd(&replystr[p+6],3)));
	}
	return 0;
}

void RIG_IC746::get_vol_min_max_step(int &min, int &max, int &step)
{
	min = 0; max = 255; step = 1;
}

// Tranceiver PTT on/off
void RIG_IC746::set_PTT_control(int val)
{
	cmd = pre_to;
	cmd += '\x1c';
	cmd += '\x00';
	cmd += (unsigned char) val;
	cmd.append( post );
	waitFB("set PTT");
}

void RIG_IC746::set_attenuator(int val)
{
	cmd = pre_to;
	cmd += '\x11';
	cmd += val ? 0x20 : 0x00;
	cmd.append( post );
	waitFB("set att");
	if (!val) {
		preamp_level--;
		if (preamp_level < 0) preamp_level = 2;
		set_preamp(1);
	}
}

int RIG_IC746::get_attenuator()
{
	string cstr = "\x11";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(7, "get att")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			return (replystr[p+5] ? 1 : 0);
	}
	return 0;
}

void RIG_IC746::set_preamp(int val)
{
	if (preamp_level == 0) {
		preamp_level = 1;
		preamp_label("Pre 1", true);
	} else if (preamp_level == 1) {
		preamp_level = 2;
		preamp_label("Pre 2", true);
	} else if (preamp_level == 2) {
		preamp_level = 0;
		preamp_label("Pre", false);
	}
	cmd = pre_to;
	cmd += '\x16';
	cmd += '\x02';
	cmd += (unsigned char) preamp_level;
	cmd.append( post );
	waitFB("set preamp");
}

int RIG_IC746::get_preamp()
{
	string cstr = "\x16\x02";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(8, "get preamp")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			if (replystr[p+6] == 0x01) {
				preamp_label("Pre 1", true);
				preamp_level = 1;
			} else if (replystr[p+6] == 0x02) {
				preamp_label("Pre 2", true);
				preamp_level = 2;
			} else {
				preamp_label("Pre", false);
				preamp_level = 0;
			}
		}
	}
	return preamp_level;
}

// changed noise blanker to noise reduction
void RIG_IC746::set_noise(bool val)
{
	cmd = pre_to;
	cmd.append("\x16\x22");
	cmd += val ? 1 : 0;
	cmd.append(post);
	waitFB("set noise");
}

int RIG_IC746::get_noise()
{
	string cstr = "\x16\x22";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(9, "get noise")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			return (replystr[p+6] ? 1 : 0);
	}
	return 0;
}

void RIG_IC746::set_noise_reduction(int val)
{
	cmd = pre_to;
	cmd.append("\x16\x40");
	cmd += val ? 1 : 0;
	cmd.append(post);
	waitFB("set NR");
}

int RIG_IC746::get_noise_reduction()
{
	string cstr = "\x16\x40";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(9, "get NR")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			return (replystr[p+6] ? 1 : 0);
	}
	return 0;
}

// 0 < val < 100
void RIG_IC746::set_noise_reduction_val(int val)
{
	cmd = pre_to;
	cmd.append("\x14\x06");
	cmd.append(to_bcd(val * 255 / 100, 3));
	cmd.append(post);
	waitFB("set NR val");
}

int RIG_IC746::get_noise_reduction_val()
{
	string cstr = "\x14\x06";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(9, "get NR val")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			return ((int)(fm_bcd(&replystr[p+6],3) / 2.55));
	}
	return 0;
}

void RIG_IC746::set_modeA(int val)
{
	A.imode = val;
	cmd = pre_to;
	cmd += '\x06';
	cmd += val > 5 ? val + 1 : val;
	cmd += A.iBW; // filter #1
	cmd.append( post );
	waitFB("set mode A");
}

int RIG_IC746::get_modeA()
{
	string cstr = "\x04";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(8, "get mode A")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			A.imode = replystr[p+5];
			if (A.imode > 6) A.imode--;
			A.iBW = replystr[p+6];
		}
	}
	return A.imode;
}

void RIG_IC746::set_bwA(int val)
{
	A.iBW = val + 1;
	set_modeA(A.imode);
}

int RIG_IC746::get_bwA()
{
	return A.iBW - 1;
}

void RIG_IC746::set_modeB(int val)
{
	B.imode = val;
	cmd = pre_to;
	cmd += '\x06';
	cmd += val > 5 ? val + 1 : val;
	cmd += B.iBW; // filter #1
	cmd.append( post );
	waitFB("set mode B");
}

int RIG_IC746::get_modeB()
{
	string cstr = "\x04";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(8, "get mode B")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			B.imode = replystr[p+5];
			if (B.imode > 6) B.imode--;
			B.iBW = replystr[p+6];
		}
	}
	return B.imode;
}

void RIG_IC746::set_bwB(int val)
{
	B.iBW = val + 1;
	set_modeB(B.imode);
}

int RIG_IC746::get_bwB()
{
	return B.iBW - 1;
}

int RIG_IC746::get_modetype(int n)
{
	return _mode_type[n];
}

void RIG_IC746::set_mic_gain(int val)
{
	val = (int)(val * 255 / 100);
	cmd = pre_to;
	cmd.append("\x14\x0B");
	cmd.append(to_bcd(val,3));
	cmd.append(post);
	waitFB("set mic");
}

void RIG_IC746::get_mic_gain_min_max_step(int &min, int &max, int &step)
{
	min = 0;
	max = 100;
	step = 1;
}

void RIG_IC746::set_if_shift(int val)
{
	int shift = (int)((val + 50) * 2.56 );
	if (shift == 256) shift = 255;
	cmd = pre_to;
	cmd.append("\x14\x07");
	cmd.append(to_bcd(shift, 3));
	cmd.append(post);
	waitFB("set IF on/off");

	cmd = pre_to;
	cmd.append("\x14\x08");
	cmd.append(to_bcd(shift, 3));
	cmd.append(post);
	waitFB("set IF val");
}

void RIG_IC746::get_if_min_max_step(int &min, int &max, int &step)
{
	min = -50;
	max = +50;
	step = 2;
}

int ICsql = 0;
void RIG_IC746::set_squelch(int val)
{
	ICsql = (int)(val * 255 / 100);
	cmd = pre_to;
	cmd.append("\x14\x03");
	cmd.append(to_bcd(ICsql, 3));
	cmd.append( post );
	waitFB("set sql");
}

int ICrfg = 0;
void RIG_IC746::set_rf_gain(int val)
{
	ICrfg = (int)(val * 255 / 100);
	cmd = pre_to;
	cmd.append("\x14\x02");
	cmd.append(to_bcd(ICrfg, 3));
	cmd.append( post );
	waitFB("set rf gain");
}

void RIG_IC746::set_power_control(double val)
{
	cmd = pre_to;
	cmd.append("\x14\x0A");
	cmd.append(to_bcd((int)(val * 255 / 100), 3));
	cmd.append( post );
	waitFB("set power");
}

void RIG_IC746::set_split(bool val)
{
	cmd = pre_to;
	cmd += 0x0F;
	cmd += val ? 0x10 : 0x00;
	cmd.append(post);
	waitFB("set split");
}

//======================================================================
// IC746PRO unique commands
//======================================================================

void RIG_IC746PRO::set_modeA(int val)
{
	A.imode = val;
	bool datamode = false;
	switch (val) {
		case 10 : val = 5; datamode = true; break;
		case 9  : val = 1; datamode = true; break;
		case 8  : val = 0; datamode = true; break;
		case 7  : val = 8; break;
		case 6  : val = 7; break;
		default: break;
	}
	cmd = pre_to;
	cmd += '\x06';
	cmd += val;
	cmd += A.iBW;
	cmd.append( post );
	waitFB("set mode A");
	if (datamode) { // LSB / USB ==> use DATA mode
		cmd = pre_to;
		cmd.append("\x1A\x06\x01");
		cmd.append(post);
		waitFB("data mode");
	}
}

int RIG_IC746PRO::get_modeA()
{
	int md;
	string cstr = "\x04";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(8, "get mode A")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			md = replystr[p+5];
			if (md > 6) md--;
			A.iBW = replystr[p+6];
			cstr = "\x1A\x06";
			resp = pre_fm;
			resp.append(cstr);
			cmd = pre_to;
			cmd.append(cstr);
			cmd.append(post);
			if (waitFOR(8, "data ?")) {
				p = replystr.rfind(resp);
				if (p != string::npos) {
					if (replystr[p+6]) {
						switch (md) {
							case 0 : md = 8; break;
							case 1 : md = 9; break;
							case 5 : md = 10; break;
							default : break;
						}
					}
				}
			}
			A.imode = md;
		}
	}
	return A.imode;
}

void RIG_IC746PRO::set_modeB(int val)
{
	B.imode = val;
	bool datamode = false;
	switch (val) {
		case 10 : val = 5; datamode = true; break;
		case 9  : val = 1; datamode = true; break;
		case 8  : val = 0; datamode = true; break;
		case 7  : val = 8; break;
		case 6  : val = 7; break;
		default: break;
	}
	cmd = pre_to;
	cmd += '\x06';
	cmd += val;
	cmd += B.iBW;
	cmd.append( post );
	waitFB("set mode B");
	if (datamode) { // LSB / USB ==> use DATA mode
		cmd = pre_to;
		cmd.append("\x1A\x06\x01");
		cmd.append(post);
		waitFB("data mode");
	}
}

int RIG_IC746PRO::get_modeB()
{
	int md;
	string cstr = "\x04";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append(post);
	if (waitFOR(8, "get mode B")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos) {
			md = replystr[p+5];
			if (md > 6) md--;
			B.iBW = replystr[p+6];
			cstr = "\x1A\x06";
			resp = pre_fm;
			resp.append(cstr);
			cmd = pre_to;
			cmd.append(cstr);
			cmd.append(post);
			if (waitFOR(8, "data ?")) {
				p = replystr.rfind(resp);
				if (p != string::npos) {
					if (replystr[p+6]) {
						switch (md) {
							case 0 : md = 8; break;
							case 1 : md = 9; break;
							case 5 : md = 10; break;
							default : break;
						}
					}
				}
			}
			B.imode = md;
		}
	}
	return B.imode;
}

int RIG_IC746PRO::adjust_bandwidth(int m)
{
	if (m == 0 || m == 1 || m == 8 || m == 9) { //SSB
		bandwidths_ = IC746PRO_SSBwidths;
		return (32);
	}
	if (m == 3 || m == 6) { //CW
		bandwidths_ = IC746PRO_SSBwidths;
		return (14);
	}
	if (m == 4 || m == 7) { //RTTY
		bandwidths_ = IC746PRO_RTTYwidths;
		return (28);
	}
	bandwidths_ = IC746PRO_AMFMwidths;
	return (0);
}

int RIG_IC746PRO::def_bandwidth(int m)
{
	if (m == 0 || m == 1 || m == 8 || m == 9) { //SSB
		return (32);
	}
	if (m == 3 || m == 6) { //CW
		return (14);
	}
	if (m == 4 || m == 7) { //RTTY
		return (28);
	}
	bandwidths_ = IC746PRO_AMFMwidths;
	return (0);
}

const char **RIG_IC746PRO::bwtable(int m)
{
	if (m == 0 || m == 1 || m == 8 || m == 9) //SSB
		return IC746PRO_SSBwidths;
	if (m == 3 || m == 6) //CW
		return IC746PRO_SSBwidths;
	if (m == 4 || m == 7) //RTTY
		return IC746PRO_RTTYwidths;
	return IC746PRO_AMFMwidths;
}

int RIG_IC746PRO::get_swr()
{
	string cstr = "\x15\x12";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(9, "get swr")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
		return (int)(fm_bcd(&replystr[p + 6],3) / 2.55 );
	}
	return -1;
}

int RIG_IC746PRO::get_alc()
{
	string cstr = "\x15\x13";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(9, "get alc")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
		return (int)(fm_bcd(&replystr[p + 6],3) / 2.55 );
	}
	return -1;
}

// Transceiver power level return power in watts
int RIG_IC746PRO::get_power_out()
{
	string cstr = "\x15\x11";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(9, "get power")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
		return (int)(fm_bcd(&replystr[p + 6],3) / 2.55 );
	}
	return -1;
}

void RIG_IC746PRO::tune_rig()
{
	cmd = pre_to;
	cmd.append("\x1c\x01\x02");
	cmd.append( post );
	waitFB("tune");
}

void RIG_IC746PRO::set_bwA(int val)
{
	if (bandwidths_ == IC746PRO_AMFMwidths) {
		A.iBW = val + 1;
		set_modeA(A.imode);
		return;
	}

	A.iBW = val;
	cmd = pre_to;
	cmd.append("\x1A\x03");
	cmd.append(to_bcd(A.iBW,2));
	cmd.append( post );
	waitFB("set bw A");
}

int  RIG_IC746PRO::get_bwA()
{
	if (bandwidths_ == IC746PRO_AMFMwidths) {
		return A.iBW - 1;
	}
	string cstr = "\x1A\x03";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(8, "get bw A")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			A.iBW = (int)(fm_bcd(&replystr[p + 6], 2));
	}
	return A.iBW;
}

void RIG_IC746PRO::set_bwB(int val)
{
	if (bandwidths_ == IC746PRO_AMFMwidths) {
		B.iBW = val + 1;
		set_modeB(B.imode);
		return;
	}

	B.iBW = val;
	cmd = pre_to;
	cmd.append("\x1A\x03");
	cmd.append(to_bcd(B.iBW,2));
	cmd.append( post );
	waitFB("set bw B");
}

int  RIG_IC746PRO::get_bwB()
{
	if (bandwidths_ == IC746PRO_AMFMwidths) {
		return B.iBW - 1;
	}
	string cstr = "\x1A\x03";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(8, "get bw B")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			B.iBW = (int)(fm_bcd(&replystr[p + 6], 2));
	}
	return B.iBW;
}

int RIG_IC746PRO::get_attenuator()
{
	string cstr = "x11";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(7, "get att")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
		return (int)(fm_bcd(&replystr[p + 5],3) / 2.55 );
	}
	return 0;
}

void RIG_IC746PRO::set_attenuator(int val)
{
	int cmdval = val ? 0x20 : 0x00;
	cmd = pre_to;
	cmd += '\x11';
	cmd += cmdval;
	cmd.append( post );
	waitFB("set att");
}

bool IC_notchon = false;
void RIG_IC746PRO::set_notch(bool on, int val)
{
	int notch = (int)(val/20.0 + 128);
	if (notch > 256) notch = 255;
	if (on != IC_notchon) {
		cmd = pre_to;
		cmd.append("\x16\x48");
		cmd += on ? '\x01' : '\x00';
		cmd.append(post);
		waitFB("set notch");
		IC_notchon = on;
	}

	if (on) {
		cmd = pre_to;
		cmd.append("\x14\x0D");
		cmd.append(to_bcd(notch,3));
		cmd.append(post);
		waitFB("set notch val");
	}
}

bool RIG_IC746PRO::get_notch(int &val)
{
	bool on = false;
	val = 0;

	string cstr = "\x16\x48";
	string resp = pre_fm;
	resp.append(cstr);
	cmd = pre_to;
	cmd.append(cstr);
	cmd.append( post );
	if (waitFOR(8, "get notch")) {
		size_t p = replystr.rfind(resp);
		if (p != string::npos)
			on = replystr[p + 6] ? 1 : 0;
		cmd = pre_to;
		resp = pre_fm;
		cstr = "\x14\x0D";
		cmd.append(cstr);
		resp.append(cstr);
		cmd.append(post);
		if (waitFOR(9, "get notch val")) {
			size_t p = replystr.rfind(resp);
			if (p != string::npos)
				val = 20*(fm_bcd(&replystr[p + 6],3) - 128);
		}
	}
	return on;
}

void RIG_IC746PRO::get_notch_min_max_step(int &min, int &max, int &step)
{
	min = -1280;
	max = 1280;
	step = 20;
}

