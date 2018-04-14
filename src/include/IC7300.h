// ----------------------------------------------------------------------------
// Copyright (C) 2014
//              David Freese, W1HKJ
// Modified: January 2017
//              Andy Stewart, KB1OIQ
//
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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#ifndef _IC7300_H
#define _IC7300_H

#include "IC746.h"

class RIG_IC7300 : public RIG_ICOM  {
public:
	RIG_IC7300();
	~RIG_IC7300(){}

	void initialize();

	void selectA();
	void selectB();

	long get_vfoA ();
	void set_vfoA (long freq);

	long get_vfoB(void);
	void set_vfoB(long f);

	void set_modeA(int val);
	int  get_modeA();

	void set_modeB(int val);
	int  get_modeB();

	bool can_split();
	void set_split(bool);
	int  get_split();

	bool canswap() { return true; }
	bool ICswap() { return true; }

//	bool hasA2b() { return true; }

	void set_bwA(int val);
	int  get_bwA();

	void set_bwB(int val);
	int  get_bwB();

	int  adjust_bandwidth(int m);
	int  def_bandwidth(int m);

	void set_mic_gain(int v);
	void get_mic_gain_min_max_step(int &min, int &max, int &step);
	int  get_mic_gain();

	void set_compression(int, int);
	void get_compression(int &on, int &val);
	void get_comp_min_max_step(int &min, int &max, int &step) {
		min = 0; max = 10; step = 1; }

	void set_vox_onoff();

	void set_vox_gain();
	void get_vox_gain_min_max_step(int &min, int &max, int &step);

	void set_vox_hang();
	void get_vox_hang_min_max_step(int &min, int &max, int &step);

	void set_vox_anti();
	void get_vox_anti_min_max_step(int &min, int &max, int &step);

	void set_cw_wpm();
	void get_cw_wpm_min_max(int &min, int &max);

	void enable_break_in();
	void set_cw_qsk();
	void get_cw_qsk_min_max_step(double &min, double &max, double &step);

	void set_cw_spot_tone();
	void get_cw_spot_tone_min_max_step(int &min, int &max, int &step);

	void set_cw_vol();

	const char **bwtable(int m);

	void set_PTT_control(int val);
	int  get_PTT();

	void set_volume_control(int val);
	int  get_volume_control();
	void get_vol_min_max_step(int &min, int &max, int &step);

	int  get_smeter();
	int  get_power_out(void);
	int  get_swr(void);
	int  get_alc(void);

	void set_power_control(double val);
	int  get_power_control();
	void get_pc_min_max_step(double &min, double &max, double &step);

	void set_rf_gain(int val);
	int  get_rf_gain();
	void get_rf_min_max_step(double &min, double &max, double &step);

	void set_preamp(int val);
	int  get_preamp();
	int  next_preamp();

	void set_attenuator(int val);
	int  get_attenuator();
	int  next_attenuator();

	void set_noise(bool val);
	int  get_noise();
	void set_nb_level(int val);
	int  get_nb_level();

	void set_noise_reduction(int val);
	int  get_noise_reduction();
	void set_noise_reduction_val(int val);
	int  get_noise_reduction_val();
	void get_nr_min_max_step(int &min, int &max, int &step) {
		min = 0; max = 15; step = 1; }

	void set_if_shift(int val);
	void get_if_min_max_step(int &min, int &max, int &step);
	bool get_if_shift(int &val);

	void set_squelch(int val);
	int  get_squelch();

	void set_notch(bool on, int val);
	bool get_notch(int &val);
	void get_notch_min_max_step(int &min, int &max, int &step);

	void set_auto_notch(int val);
	int  get_auto_notch();

	int  get_agc();
	int  incr_agc();
	const char *agc_label();
	int  agc_val();

	void tune_rig();

	void setVfoAdj(double v);
	double getVfoAdj();
	void get_vfoadj_min_max_step(int &min, int &max, int &step) {
		min = 0; max = 100; step = 1; }

};

#endif
