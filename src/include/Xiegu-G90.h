// ----------------------------------------------------------------------------
// Copyright (C) 2020
//              David Freese, W1HKJ
//              Mark Gregory, G4LCH
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
// aunsigned long int with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#ifndef _Xiegu_G90_H
#define _Xiegu_G90_H
#include "IC746.h"

class RIG_Xiegu_G90 : public RIG_ICOM {
public:
	RIG_Xiegu_G90();
	~RIG_Xiegu_G90(){}

	bool CW_sense;

	void initialize();

	void selectA();
	void selectB();

	bool check();

	unsigned long int get_vfoA ();
	void set_vfoA (unsigned long int freq);

	unsigned long int get_vfoB(void);
	void set_vfoB(unsigned long int f);

	void set_modeA(int val);
	int  get_modeA();

	void set_modeB(int val);
	int  get_modeB();

	void set_attenuator( int val );

	void set_preamp(int val);
	int  get_preamp();

	void set_noise(bool val);
	int get_noise();

	void set_compression(int, int);
	void get_compression(int &, int &);

	void get_cw_wpm_min_max(int &min, int &max) {
		min = 6; max = 48; }

	void set_cw_wpm();

	bool  canswap() { return true; }

	bool can_split();
	void set_split(bool val);
	int get_split();

	void set_PTT_control(int val);

    void tune_rig(int how);
    int get_tune();

	void set_power_control(double val);
	int  get_power_control();
	void get_pc_min_max_step(double &min, double &max, double &step);

	void set_volume_control(int val);
	int  get_volume_control();
	void get_vol_min_max_step(int &min, int &max, int &step);

	void set_squelch(int val);
	int  get_squelch();

	int  get_smeter();
	int  get_swr();
	int  get_power_out();

	void set_band_selection(int v);
	void get_band_selection(int v);

	int  get_agc();
	int  incr_agc();
	const char *agc_label();
	int  agc_val();

};

#endif
