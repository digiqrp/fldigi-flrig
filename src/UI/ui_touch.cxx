// ----------------------------------------------------------------------------
// Copyright (C) 2014
//              David Freese, W1HKJ
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

void cbMAIN(Fl_Widget *, void *);
void cbSLIDERS(Fl_Widget *, void *);
void cbBUTTONS(Fl_Widget *, void *);
void cbOTHER(Fl_Widget *, void *);

Fl_Menu_Item touch_menu[] = {
 {_("&Files"), 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("E&xit"), 0,  (Fl_Callback*)cb_mnuExit, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {_("&Config"), 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Setup"), 0, 0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Transceiver"), 0,  (Fl_Callback*)cb_mnuConfigXcvr, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {_("tcpip"), 0, (Fl_Callback*)cb_mnuTCPIP, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {_("PTT"), 0, (Fl_Callback*)cb_mnuPTT, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {_("AUX"), 0, (Fl_Callback*)cb_mnuAUX, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Polling"), 0, (Fl_Callback*)cb_Polling, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {_("Start/Stop"), 0, 0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Restore Freq/Mode"), 0,  (Fl_Callback*)cb_mnuRestoreData, 0, 6, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Keep Freq/Mode"), 0,  (Fl_Callback*)cb_mnuKeepData, 0, 134, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {_("UI"), 0, 0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Meter filtering"), 0,  (Fl_Callback*)cb_mnu_meter_filtering, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Tooltips"), 0,  (Fl_Callback*)cb_mnuTooltips, 0, 130, FL_NORMAL_LABEL, 0, 14, 0},
 {_("User Interface"), 0,  (Fl_Callback*)cb_mnuColorConfig, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0},
 {_("&Memory"), 0, 0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Save"), 0,  (Fl_Callback*)cb_save_me, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Manage"), 0,  (Fl_Callback*)cb_Memory, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {_("&Help"), 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {_("On Line Help"), 0,  (Fl_Callback*)cb_mnuOnLineHelp, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {_("&About"), 0,  (Fl_Callback*)cb_mnuAbout, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {_("Send command"), 0, (Fl_Callback*)cb_Send, 0, 128, FL_NORMAL_LABEL, 0, 14, 0},
 {_("&Events"), 0,  (Fl_Callback*)cb_Events, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {_("      "), 0, 0, 0, FL_MENU_DIVIDER, FL_NORMAL_LABEL, 0, 14, 0},
 {_("MAIN   "), 0, (Fl_Callback*)cbMAIN, 0, FL_MENU_RADIO | FL_MENU_VALUE, FL_NORMAL_LABEL, 0, 14, 0},
 {_("SLIDERS   "), 0, (Fl_Callback*)cbSLIDERS, 0, FL_MENU_RADIO, FL_NORMAL_LABEL, 0, 14, 0},
 {_("BUTTONS   "), 0, (Fl_Callback*)cbBUTTONS, 0, FL_MENU_RADIO, FL_NORMAL_LABEL, 0, 14, 0},
 {_("OTHER   "), 0, (Fl_Callback*)cbOTHER, 0, FL_MENU_RADIO | FL_MENU_DIVIDER, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0}
};

Fl_Group *grpMAIN = (Fl_Group *)0;
Fl_Group *grpSLIDERS = (Fl_Group *)0;
Fl_Group *grpBUTTONS = (Fl_Group *)0;
Fl_Group *grpOTHER = (Fl_Group *)0;

void cbMAIN(Fl_Widget *, void *) {
	grpMAIN->show();
	grpSLIDERS->hide();
	grpBUTTONS->hide();
	grpOTHER->hide();
}

void cbSLIDERS(Fl_Widget *, void *) {
	grpMAIN->hide();
	grpSLIDERS->show();
	grpBUTTONS->hide();
	grpOTHER->hide();
}

void cbBUTTONS(Fl_Widget *, void *) {
	grpMAIN->hide();
	grpSLIDERS->hide();
	grpBUTTONS->show();
	grpOTHER->hide();
}

void cbOTHER(Fl_Widget *, void *) {
	grpMAIN->hide();
	grpSLIDERS->hide();
	grpBUTTONS->hide();
	grpOTHER->show();
}

void cb_touch_Vol(Fl_Widget *w, void *d) {
	cb_btnVol(btnVol, 0);
	if (btnVol->active()) Fl::focus(sldrVOLUME);
}

Fl_Group *touch_main_group(int X, int Y, int W, int H)
{
	int ypos = Y + 2;
	int xpos = X + 2;

	Fl_Group *tmg = new Fl_Group(X,Y,W,H);

	grpMAIN = new Fl_Group(xpos, ypos, W-4, H-ypos-2, "");

		ypos += 4;
// meters group
		grpMeters = new Fl_Group(xpos, ypos, 208, 60);
		grpMeters->box(FL_FLAT_BOX);
		grpMeters->color((Fl_Color)246);

		scaleSmeter = new Fl_Box(xpos, ypos, 206, 20);
		scaleSmeter->box(FL_FLAT_BOX);
		scaleSmeter->color((Fl_Color)246);
		scaleSmeter->image(image_S60);

		btnALC_SWR = new Fl_Button(xpos, ypos, 206, 20);
		btnALC_SWR->tooltip(_("Press SWR / ALC"));
		btnALC_SWR->box(FL_FLAT_BOX);
		btnALC_SWR->down_box(FL_FLAT_BOX);
		btnALC_SWR->color((Fl_Color)246);
		btnALC_SWR->image(image_SWR);
		btnALC_SWR->callback((Fl_Callback*)cb_btnALC_SWR);
		btnALC_SWR->hide();

		sldrRcvSignal = new Fl_SigBar(xpos, ypos+22, 200, 6);
		sldrRcvSignal->box(FL_FLAT_BOX);
		sldrRcvSignal->color(FL_BACKGROUND_COLOR);
		sldrRcvSignal->selection_color(FL_BACKGROUND_COLOR);
		sldrRcvSignal->labeltype(FL_NORMAL_LABEL);
		sldrRcvSignal->labelfont(0);
		sldrRcvSignal->labelsize(14);
		sldrRcvSignal->labelcolor(FL_FOREGROUND_COLOR);
		sldrRcvSignal->align(Fl_Align(FL_ALIGN_CENTER));
		sldrRcvSignal->when(FL_WHEN_RELEASE);
		sldrRcvSignal->hide();
		sldrRcvSignal->minimum(0);
		sldrRcvSignal->maximum(100);

		sldrALC = new Fl_SigBar(xpos+2, ypos+22, 200, 6);
		sldrALC->box(FL_FLAT_BOX);
		sldrALC->color(FL_BACKGROUND_COLOR);
		sldrALC->selection_color(FL_BACKGROUND_COLOR);
		sldrALC->labeltype(FL_NORMAL_LABEL);
		sldrALC->labelfont(0);
		sldrALC->labelsize(14);
		sldrALC->labelcolor(FL_FOREGROUND_COLOR);
		sldrALC->align(Fl_Align(FL_ALIGN_CENTER));
		sldrALC->when(FL_WHEN_RELEASE);
		sldrALC->hide();
		sldrALC->minimum(0);
		sldrALC->maximum(100);

		sldrSWR = new Fl_SigBar(xpos+2, ypos+22, 200, 6);
		sldrSWR->box(FL_FLAT_BOX);
		sldrSWR->color(FL_BACKGROUND_COLOR);
		sldrSWR->selection_color(FL_BACKGROUND_COLOR);
		sldrSWR->labeltype(FL_NORMAL_LABEL);
		sldrSWR->labelfont(0);
		sldrSWR->labelsize(14);
		sldrSWR->labelcolor(FL_FOREGROUND_COLOR);
		sldrSWR->align(Fl_Align(FL_ALIGN_CENTER));
		sldrSWR->when(FL_WHEN_RELEASE);
		sldrSWR->hide();
		sldrSWR->minimum(0);
		sldrSWR->maximum(100);

		sldrFwdPwr = new Fl_SigBar(xpos+2, ypos+29, 200, 6);
		sldrFwdPwr->box(FL_FLAT_BOX);
		sldrFwdPwr->color(FL_BACKGROUND_COLOR);
		sldrFwdPwr->selection_color(FL_BACKGROUND_COLOR);
		sldrFwdPwr->labeltype(FL_NORMAL_LABEL);
		sldrFwdPwr->labelfont(0);
		sldrFwdPwr->labelsize(14);
		sldrFwdPwr->labelcolor(FL_FOREGROUND_COLOR);
		sldrFwdPwr->align(Fl_Align(FL_ALIGN_CENTER));
		sldrFwdPwr->when(FL_WHEN_RELEASE);
		sldrFwdPwr->hide();
		sldrFwdPwr->minimum(0);
		sldrFwdPwr->maximum(100);

		scalePower = new Fl_Button(xpos, ypos+36, 206, 20);
		scalePower->tooltip(_("right-click to select power scale"));
		scalePower->box(FL_FLAT_BOX);
		scalePower->down_box(FL_FLAT_BOX);
		scalePower->color((Fl_Color)246);
		scalePower->image(image_P100);
		scalePower->callback((Fl_Callback*)cb_scalePower);

		meter_fill_box = new Fl_Box(xpos+210, ypos+4, 0, 57);
		meter_fill_box->box(FL_FLAT_BOX);
		meter_fill_box->color((Fl_Color)246);
		Fl_Group::current()->resizable(meter_fill_box);

		grpMeters->end();
// end of meters group

// bw / mode selector group
		ypos += 62;
		Fl_Group *grpcombos = new Fl_Group(xpos, ypos, 208, 35);

		opBW = new Fl_ComboBox(xpos, ypos, 115, 35, "");
		opBW->tooltip(_("Select Transceiver Bandwidth"));
		opBW->box(FL_FLAT_BOX);
		opBW->color(FL_BACKGROUND2_COLOR);
		opBW->selection_color(FL_BACKGROUND_COLOR);
		opBW->labeltype(FL_NORMAL_LABEL);
		opBW->labelfont(0);
		opBW->labelsize(12);
		opBW->textfont(0);
		opBW->textsize(14);
		opBW->labelcolor(FL_FOREGROUND_COLOR);
		opBW->callback((Fl_Callback*)cb_opBW);
		opBW->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
		opBW->when(FL_WHEN_RELEASE);
		opBW->end();

		opMODE = new Fl_ComboBox(xpos + opBW->w() + 2, ypos, 208 - opBW->w() - 2, 35, "");
		opMODE->tooltip(_("Select transceiver operating mode"));
		opMODE->box(FL_FLAT_BOX);
		opMODE->color(FL_BACKGROUND2_COLOR);
		opMODE->selection_color(FL_BACKGROUND_COLOR);
		opMODE->labeltype(FL_NORMAL_LABEL);
		opMODE->labelfont(0);
		opMODE->labelsize(12);
		opMODE->labelcolor(FL_FOREGROUND_COLOR);
		opMODE->textfont(0);
		opMODE->textsize(14);
		opMODE->callback((Fl_Callback*)cb_opMODE);
		opMODE->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
		opMODE->when(FL_WHEN_RELEASE);
		opMODE->end();

		btnDSP = new Fl_Button(xpos, ypos, 30, 35, _("L"));
		btnDSP->callback((Fl_Callback*)cb_btnDSP);
		btnDSP->labelsize(14);
		btnDSP->hide();

		opDSP_lo = new Fl_ComboBox(xpos+30, ypos, opBW->w() - 30, 35, "");
		opDSP_lo->tooltip(_("Lo Cut Freq"));
		opDSP_lo->box(FL_FLAT_BOX);
		opDSP_lo->color(FL_BACKGROUND2_COLOR);
		opDSP_lo->selection_color(FL_BACKGROUND_COLOR);
		opDSP_lo->labeltype(FL_NORMAL_LABEL);
		opDSP_lo->labelfont(0);
		opDSP_lo->labelsize(12);
		opDSP_lo->textfont(0);
		opDSP_lo->textsize(14);;
		opDSP_lo->labelcolor(FL_FOREGROUND_COLOR);
		opDSP_lo->callback((Fl_Callback*)cb_opDSP_lo);
		opDSP_lo->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
		opDSP_lo->when(FL_WHEN_RELEASE);
		opDSP_lo->hide();
		opDSP_lo->end();

		opDSP_hi = new Fl_ComboBox(xpos+30, ypos, opBW->w() - 30, 35, "");
		opDSP_hi->tooltip(_("Hi Cut Freq"));
		opDSP_hi->box(FL_FLAT_BOX);
		opDSP_hi->color(FL_BACKGROUND2_COLOR);
		opDSP_hi->selection_color(FL_BACKGROUND_COLOR);
		opDSP_hi->labeltype(FL_NORMAL_LABEL);
		opDSP_hi->labelfont(0);
		opDSP_hi->labelsize(12);
		opDSP_hi->textfont(0);
		opDSP_hi->textsize(14);;
		opDSP_hi->labelcolor(FL_FOREGROUND_COLOR);
		opDSP_hi->callback((Fl_Callback*)cb_opDSP_hi);
		opDSP_hi->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
		opDSP_hi->when(FL_WHEN_RELEASE);
		opDSP_hi->hide();
		opDSP_hi->end();

		grpcombos->end();
// end of bw / mode selector group

		xpos += grpMeters->w() + 2;
		ypos = Y + 2;

		FreqDispA = new cFreqControl(xpos, ypos, 480, 100, _("9"));
		FreqDispA->box(FL_DOWN_BOX);
		FreqDispA->color(FL_BACKGROUND_COLOR);
		FreqDispA->selection_color(FL_BACKGROUND_COLOR);
		FreqDispA->labeltype(FL_NORMAL_LABEL);
		FreqDispA->labelfont(0);
		FreqDispA->labelsize(14);
		FreqDispA->labelcolor(FL_FOREGROUND_COLOR);
		FreqDispA->align(Fl_Align(FL_ALIGN_CENTER));
		FreqDispA->when(FL_WHEN_CHANGED);
		FreqDispA->SetONOFFCOLOR (FL_YELLOW, FL_BLACK);
		FreqDispA->setCallBack(movFreqA);

// FreqDispB hides behind FreqDispA
		FreqDispB = new cFreqControl(xpos, ypos, 480, 100, _("9"));
		FreqDispB->box(FL_DOWN_BOX);
		FreqDispB->color(FL_BACKGROUND_COLOR);
		FreqDispB->selection_color(FL_BACKGROUND_COLOR);
		FreqDispB->labeltype(FL_NORMAL_LABEL);
		FreqDispB->labelfont(0);
		FreqDispB->labelsize(14);
		FreqDispB->labelcolor(FL_FOREGROUND_COLOR);
		FreqDispB->align(Fl_Align(FL_ALIGN_CENTER));
		FreqDispB->when(FL_WHEN_CHANGED);
		FreqDispB->SetONOFFCOLOR (FL_YELLOW, FL_BLACK);
		FreqDispB->setCallBack(movFreqB);
		FreqDispB->hide();

		xpos += FreqDispA->w() + 2;

		btnA = new Fl_Light_Button(xpos, ypos, 49, 49, _("A"));
		btnA->tooltip(_("vfo A"));
		btnA->down_box(FL_THIN_DOWN_BOX);
		btnA->labelsize(16);;
		btnA->callback((Fl_Callback*)cb_btnA);
		btnA->value(!useB);

		btnB = new Fl_Light_Button(xpos, ypos+51, 49, 49, _("B"));
		btnB->tooltip(_("vfo B"));
		btnB->down_box(FL_THIN_DOWN_BOX);
		btnB->labelsize(16);
		btnB->callback((Fl_Callback*)cb_btnB);
		btnB->value(useB);

		xpos = W - 2 - 75;
		btnPTT = new Fl_Light_Button(xpos, ypos, 75, 100, _("PTT"));
		btnPTT->tooltip(_("Xmt On/Off"));
		btnPTT->down_box(FL_THIN_DOWN_BOX);
		btnPTT->labelsize(18);;
		btnPTT->callback((Fl_Callback*)cb_btnPTT);

		xpos = btnA->x() + btnA->w() + 2;
		int ws = btnPTT->x() - 8 - xpos;

		Fl_Group *sliders1 = new Fl_Group(xpos, ypos, ws, H - 30);

		Fl_Group *g1a = new Fl_Group(xpos, ypos, 50, H-30);
			btnVol = new Fl_Light_Button(xpos, ypos + 51, 49, 49, _("Vol"));
			btnVol->tooltip(_("Speaker on/off"));
			btnVol->down_box(FL_THIN_DOWN_BOX);
			btnVol->value(1);
			btnVol->labelsize(15);;
			btnVol->callback((Fl_Callback*)cb_touch_Vol);
		g1a->end();

		Fl_Group *g1b = new Fl_Group(xpos + 50, ypos, ws - 50, H - 30);

//		int swidth = btnPTT->x() - 2 - xpos;
			sldrPOWER = new Fl_Wheel_Value_Slider(xpos+50, ypos, ws-50, 49, _("PWR"));
			sldrPOWER->tooltip(_("Adjust power level"));
			sldrPOWER->type(5);
			sldrPOWER->box(FL_THIN_DOWN_BOX);
			sldrPOWER->color(FL_BACKGROUND_COLOR);
			sldrPOWER->selection_color(FL_BACKGROUND_COLOR);
			sldrPOWER->labeltype(FL_NORMAL_LABEL);
			sldrPOWER->labelfont(0);
			sldrPOWER->labelsize(14);
			sldrPOWER->labelcolor(FL_FOREGROUND_COLOR);
			sldrPOWER->maximum(100);
			sldrPOWER->step(1);
			sldrPOWER->value(15);
			sldrPOWER->textsize(14);
			sldrPOWER->callback((Fl_Callback*)cb_sldrPOWER);
			sldrPOWER->align(Fl_Align(FL_ALIGN_LEFT));
			sldrPOWER->when(FL_WHEN_CHANGED);
			sldrPOWER->reverse(true);

			sldrVOLUME = new Fl_Wheel_Value_Slider(xpos + 50, ypos + 51, ws - 50, 49);
			sldrVOLUME->tooltip(_("Adjust Audio Volume"));
			sldrVOLUME->type(5);
			sldrVOLUME->box(FL_THIN_DOWN_BOX);
			sldrVOLUME->color(FL_BACKGROUND_COLOR);
			sldrVOLUME->selection_color(FL_BACKGROUND_COLOR);
			sldrVOLUME->labeltype(FL_NORMAL_LABEL);
			sldrVOLUME->labelfont(0);
			sldrVOLUME->labelsize(12);
			sldrVOLUME->labelcolor(FL_FOREGROUND_COLOR);
			sldrVOLUME->maximum(100);
			sldrVOLUME->step(1);
			sldrVOLUME->textsize(14);
			sldrVOLUME->callback((Fl_Callback*)cb_sldrVOLUME);
			sldrVOLUME->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
			sldrVOLUME->when(FL_WHEN_CHANGED);
			Fl_Group::current()->resizable(sldrVOLUME);
			sldrVOLUME->reverse(true);

		g1b->end();

		sliders1->resizable(g1b);

		sliders1->end();

	grpMAIN->resizable(sliders1);

	grpMAIN->end();

	xpos = X + 4;
	ypos = Y + 4;

	grpSLIDERS = new Fl_Group(xpos, ypos, W, H-ypos, "");

	int wg = (W - 16) / 3;
	int cw = 60;
	int rh = 48;
	int ch = 100;
	int spw = wg - cw;

		Fl_Group *col1 = new Fl_Group(xpos, ypos, wg, ch);
			Fl_Group *col1a = new Fl_Group(xpos, ypos, cw, ch, "");
			col1a->end();

			Fl_Group *col1b = new Fl_Group(xpos + cw, ypos, spw, ch, "");

			sldrSQUELCH = new Fl_Wheel_Value_Slider(xpos + cw, ypos, spw, rh, _("SQL"));
			sldrSQUELCH->tooltip(_("Adjust Squelch"));
			sldrSQUELCH->type(5);
			sldrSQUELCH->box(FL_THIN_DOWN_BOX);
			sldrSQUELCH->color(FL_BACKGROUND_COLOR);
			sldrSQUELCH->selection_color(FL_BACKGROUND_COLOR);
			sldrSQUELCH->labeltype(FL_NORMAL_LABEL);
			sldrSQUELCH->labelfont(0);
			sldrSQUELCH->labelsize(14);
			sldrSQUELCH->labelcolor(FL_FOREGROUND_COLOR);
			sldrSQUELCH->maximum(100);
			sldrSQUELCH->step(1);
			sldrSQUELCH->value(15);
			sldrSQUELCH->textsize(14);
			sldrSQUELCH->callback((Fl_Callback*)cb_sldrSQUELCH);
			sldrSQUELCH->align(Fl_Align(FL_ALIGN_LEFT));
			sldrSQUELCH->when(FL_WHEN_CHANGED);
			sldrSQUELCH->reverse(true);

			sldrMICGAIN = new Fl_Wheel_Value_Slider(xpos + cw, ypos + ch/2, spw, rh, _("Mic"));
			sldrMICGAIN->tooltip(_("Adjust Mic Gain"));
			sldrMICGAIN->type(5);
			sldrMICGAIN->box(FL_THIN_DOWN_BOX);
			sldrMICGAIN->color(FL_BACKGROUND_COLOR);
			sldrMICGAIN->selection_color(FL_BACKGROUND_COLOR);
			sldrMICGAIN->labeltype(FL_NORMAL_LABEL);
			sldrMICGAIN->labelfont(0);
			sldrMICGAIN->labelsize(14);
			sldrMICGAIN->labelcolor(FL_FOREGROUND_COLOR);
			sldrMICGAIN->maximum(100);
			sldrMICGAIN->step(1);
			sldrMICGAIN->textsize(14);
			sldrMICGAIN->callback((Fl_Callback*)cb_sldrMICGAIN);
			sldrMICGAIN->align(Fl_Align(FL_ALIGN_LEFT));
			sldrMICGAIN->when(FL_WHEN_CHANGED);
			sldrMICGAIN->reverse(true);

			col1b->end();
			col1->resizable(col1b);
		col1->end();

		xpos += wg;
		Fl_Group *sep1 = new Fl_Group(xpos, ypos, 4, ch);
		sep1->box(FL_FLAT_BOX);
		sep1->end();

		xpos += 4;
		Fl_Group *col2 = new Fl_Group(xpos, ypos, wg, ch);
			Fl_Group *col2a = new Fl_Group (xpos, ypos, cw, ch);

			btnIFsh = new Fl_Light_Button(xpos, ypos, cw, rh, _("IFsh"));
			btnIFsh->tooltip(_("IF Shift On/Off"));
			btnIFsh->down_box(FL_THIN_DOWN_BOX);
			btnIFsh->labelsize(16);
			btnIFsh->callback((Fl_Callback*)cb_btnIFsh);

			btnNR = new Fl_Light_Button(xpos, ypos+ch/2, cw, rh, _("NR"));
			btnNR->tooltip(_("Noise Reduction On/Off"));
			btnNR->down_box(FL_THIN_DOWN_BOX);
			btnNR->labelsize(16);
			btnNR->callback((Fl_Callback*)cb_btnNR);

			col2a->end();

			Fl_Group *col2b = new Fl_Group (xpos+cw, ypos, spw, ch);

			sldrIFSHIFT = new Fl_Wheel_Value_Slider(xpos+cw, ypos, spw, rh);
			sldrIFSHIFT->tooltip(_("Adjust IF Shift"));
			sldrIFSHIFT->type(5);
			sldrIFSHIFT->box(FL_THIN_DOWN_BOX);
			sldrIFSHIFT->color(FL_BACKGROUND_COLOR);
			sldrIFSHIFT->selection_color(FL_BACKGROUND_COLOR);
			sldrIFSHIFT->labeltype(FL_NORMAL_LABEL);
			sldrIFSHIFT->labelfont(0);
			sldrIFSHIFT->labelsize(14);
			sldrIFSHIFT->labelcolor(FL_FOREGROUND_COLOR);
			sldrIFSHIFT->minimum(-1000);
			sldrIFSHIFT->maximum(1000);
			sldrIFSHIFT->step(10);
			sldrIFSHIFT->textsize(14);
			sldrIFSHIFT->callback((Fl_Callback*)cb_sldrIFSHIFT);
			sldrIFSHIFT->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
			sldrIFSHIFT->when(FL_WHEN_CHANGED);
			sldrIFSHIFT->reverse(true);

			sldrNR = new Fl_Wheel_Value_Slider(xpos+cw, ypos+ch/2, spw, rh);
			sldrNR->tooltip(_("Adjust noise reduction"));
			sldrNR->type(5);
			sldrNR->box(FL_THIN_DOWN_BOX);
			sldrNR->color(FL_BACKGROUND_COLOR);
			sldrNR->selection_color(FL_BACKGROUND_COLOR);
			sldrNR->labeltype(FL_NORMAL_LABEL);
			sldrNR->labelfont(0);
			sldrNR->labelsize(12);
			sldrNR->labelcolor(FL_FOREGROUND_COLOR);
			sldrNR->maximum(100);
			sldrNR->step(2);
			sldrNR->textsize(14);
			sldrNR->callback((Fl_Callback*)cb_sldrNR);
			sldrNR->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
			sldrNR->when(FL_WHEN_CHANGED);
			sldrNR->reverse(true);

			col2b->end();

			col2->resizable(col2b);

		col2->end();

		xpos += wg;
		Fl_Group *sep2 = new Fl_Group(xpos, ypos, 4, ch);
		sep2->box(FL_FLAT_BOX);
		sep2->end();

		xpos += 4;
		Fl_Group *col3 = new Fl_Group(xpos, ypos, wg, ch, "");
			Fl_Group *col3a = new Fl_Group(xpos, ypos, cw, ch, "");

			btnNotch = new Fl_Light_Button(xpos, ypos, cw, rh, _("Nch"));
			btnNotch->tooltip(_("Notch - Manual (off) Auto (on)"));
			btnNotch->down_box(FL_THIN_DOWN_BOX);
			btnNotch->labelsize(16);
			btnNotch->callback((Fl_Callback*)cb_btnNotch);

			col3a->end();

			Fl_Group *col3b = new Fl_Group(xpos+cw, ypos, spw, ch,"");

			sldrNOTCH = new Fl_Wheel_Value_Slider(xpos+cw, ypos, spw, rh);
			sldrNOTCH->tooltip(_("Adjust Notch Frequency"));
			sldrNOTCH->type(5);
			sldrNOTCH->box(FL_THIN_DOWN_BOX);
			sldrNOTCH->color(FL_BACKGROUND_COLOR);
			sldrNOTCH->selection_color(FL_BACKGROUND_COLOR);
			sldrNOTCH->labeltype(FL_NORMAL_LABEL);
			sldrNOTCH->labelfont(0);
			sldrNOTCH->labelsize(16);
			sldrNOTCH->labelcolor(FL_FOREGROUND_COLOR);
			sldrNOTCH->minimum(-1000);
			sldrNOTCH->maximum(1000);
			sldrNOTCH->step(10);
			sldrNOTCH->textsize(14);
			sldrNOTCH->callback((Fl_Callback*)cb_sldrNOTCH);
			sldrNOTCH->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
			sldrNOTCH->when(FL_WHEN_CHANGED);
			sldrNOTCH->reverse(true);

			sldrRFGAIN = new Fl_Wheel_Value_Slider(xpos+cw, ypos + ch/2, spw, rh, _("RF"));
			sldrRFGAIN->tooltip(_("Adjust RF gain"));
			sldrRFGAIN->type(5);
			sldrRFGAIN->box(FL_THIN_DOWN_BOX);
			sldrRFGAIN->color(FL_BACKGROUND_COLOR);
			sldrRFGAIN->selection_color(FL_BACKGROUND_COLOR);
			sldrRFGAIN->labeltype(FL_NORMAL_LABEL);
			sldrRFGAIN->labelfont(0);
			sldrRFGAIN->labelsize(14);
			sldrRFGAIN->labelcolor(FL_FOREGROUND_COLOR);
			sldrRFGAIN->maximum(100);
			sldrRFGAIN->step(1);
			sldrRFGAIN->value(100);
			sldrRFGAIN->textsize(14);
			sldrRFGAIN->callback((Fl_Callback*)cb_sldrRFGAIN);
			sldrRFGAIN->align(Fl_Align(FL_ALIGN_LEFT));
			sldrRFGAIN->when(FL_WHEN_CHANGED);
			sldrRFGAIN->reverse(true);

			col3b->end();

			col3->resizable(col3b);

		col3->end();

	grpSLIDERS->end();

	xpos = X + 2;
	ypos = Y + 2;

	grpBUTTONS = new Fl_Group(xpos, ypos, W-4, H-ypos-2, "");
		ypos += 4;

		int bw = (W-18)/8;
		int bh = 50;

		ypos += 15;
		xpos = 2;

		btnAttenuator = new Fl_Light_Button(xpos, ypos, bw, bh, _("Att"));
		btnAttenuator->tooltip(_("Attenuator On/Off"));
		btnAttenuator->down_box(FL_THIN_DOWN_BOX);
		btnAttenuator->labelsize(16);
		btnAttenuator->callback((Fl_Callback*)cb_btnAttenuator);

		xpos += btnAttenuator->w() + 2;
		btnPreamp = new Fl_Light_Button(xpos, ypos, bw, bh, _("Pre"));
		btnPreamp->tooltip(_("Preamp On/Off"));
		btnPreamp->down_box(FL_THIN_DOWN_BOX);
		btnPreamp->labelsize(16);
		btnPreamp->callback((Fl_Callback*)cb_btnPreamp);

		xpos += btnPreamp->w() + 2;
		btnNOISE = new Fl_Light_Button(xpos, ypos, bw, bh, _("NB"));
		btnNOISE->tooltip(_("Noise Blanker On/Off"));
		btnNOISE->down_box(FL_THIN_DOWN_BOX);
		btnNOISE->labelsize(16);
		btnNOISE->callback((Fl_Callback*)cb_btnNOISE);

		xpos += btnNOISE->w() + 2;
		btnAutoNotch = new Fl_Light_Button(xpos, ypos, bw, bh, _("AN"));
		btnAutoNotch->tooltip(_("Auto Notch On/Off"));
		btnAutoNotch->down_box(FL_THIN_DOWN_BOX);
		btnAutoNotch->labelsize(16);
		btnAutoNotch->callback((Fl_Callback*)cb_btnAutoNotch);

		xpos += btnAutoNotch->w() + 2;
		btnAswapB = new Fl_Button(xpos, ypos, bw, bh, _("A/B"));
		btnAswapB->tooltip(_("Swap A B\nRight-click; Copy A to B"));
		btnAswapB->down_box(FL_DOWN_BOX);
		btnAswapB->labelsize(16);
		btnAswapB->callback((Fl_Callback*)cb_btnAswapB);

		xpos += btnAswapB->w() + 2;
		btn_K3_swapAB = new Fl_Button(xpos, ypos, bw, bh, _("A/B"));
		btn_K3_swapAB->tooltip(_("Swap A/B"));
		btn_K3_swapAB->down_box(FL_DOWN_BOX);
		btn_K3_swapAB->labelsize(16);
		btn_K3_swapAB->callback((Fl_Callback*)cb_btn_K3_swapAB);
		btn_K3_swapAB->hide();

		xpos += btn_K3_swapAB->w() + 2;
		btnSplit = new Fl_Light_Button(xpos, ypos, bw, bh, _("Split"));
		btnSplit->tooltip(_("Rx-A / Tx-B"));
		btnSplit->down_box(FL_THIN_DOWN_BOX);
		btnSplit->labelsize(16);
		btnSplit->callback((Fl_Callback*)cb_btnSplit);
		btnSplit->value(progStatus.split);

		xpos += btnSplit->w() + 2;
		btnTune = new Fl_Button(xpos, ypos, bw, bh, _("Tune"));
		btnTune->tooltip(_("Momentary Tune"));
		btnTune->labelsize(16);
		btnTune->callback((Fl_Callback*)cb_btnTune);


	grpBUTTONS->end();

	xpos = X;
	ypos = Y;// + 2;
	int tabh = 26;
	int tabb = 70;
	int by = ypos + 40;
	bh = 28;

	grpOTHER = new Fl_Group(xpos, ypos, W, H-ypos, "");

	ypos += 2;
		tabsGeneric = new Fl_Tabs(xpos, ypos, W, H-ypos);

			tabsGeneric->selection_color(FL_LIGHT1);

			genericBands = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Bands"));

				btnBandSelect_1 = new Fl_Button(xpos+4, by, 50, bh, _("1.8"));
				btnBandSelect_1->tooltip(_("160m Band"));
				btnBandSelect_1->color((Fl_Color)246);
				btnBandSelect_1->callback((Fl_Callback*)cb_btnBandSelect_1);

				btnBandSelect_2 = new Fl_Button(xpos+62, by, 50, bh, _("3.5"));
				btnBandSelect_2->tooltip(_("80m band"));
				btnBandSelect_2->color((Fl_Color)246);
				btnBandSelect_2->callback((Fl_Callback*)cb_btnBandSelect_2);

				btnBandSelect_3 = new Fl_Button(xpos+120, by, 50, bh, _("7"));
				btnBandSelect_3->tooltip(_("40m band"));
				btnBandSelect_3->color((Fl_Color)246);
				btnBandSelect_3->callback((Fl_Callback*)cb_btnBandSelect_3);
				btnBandSelect_3->align(Fl_Align(FL_ALIGN_CLIP));

				btnBandSelect_4 = new Fl_Button(xpos+178, by, 50, bh, _("10"));
				btnBandSelect_4->tooltip(_("30m band"));
				btnBandSelect_4->color((Fl_Color)246);
				btnBandSelect_4->callback((Fl_Callback*)cb_btnBandSelect_4);

				btnBandSelect_5 = new Fl_Button(xpos+237, by, 50, bh, _("14"));
				btnBandSelect_5->tooltip(_("20m band"));
				btnBandSelect_5->color((Fl_Color)246);
				btnBandSelect_5->callback((Fl_Callback*)cb_btnBandSelect_5);

				btnBandSelect_6 = new Fl_Button(xpos+295, by, 50, bh, _("18"));
				btnBandSelect_6->tooltip(_("17m band"));
				btnBandSelect_6->color((Fl_Color)246);
				btnBandSelect_6->callback((Fl_Callback*)cb_btnBandSelect_6);

				btnBandSelect_7 = new Fl_Button(xpos+353, by, 50, bh, _("21"));
				btnBandSelect_7->tooltip(_("15m band"));
				btnBandSelect_7->color((Fl_Color)246);
				btnBandSelect_7->callback((Fl_Callback*)cb_btnBandSelect_7);

				btnBandSelect_8 = new Fl_Button(xpos+412, by, 50, bh, _("24"));
				btnBandSelect_8->tooltip(_("12m band"));
				btnBandSelect_8->color((Fl_Color)246);
				btnBandSelect_8->callback((Fl_Callback*)cb_btnBandSelect_8);

				btnBandSelect_9 = new Fl_Button(xpos+470, by, 50, bh, _("28"));
				btnBandSelect_9->tooltip(_("10m band"));
				btnBandSelect_9->color((Fl_Color)246);
				btnBandSelect_9->callback((Fl_Callback*)cb_btnBandSelect_9);

				btnBandSelect_10 = new Fl_Button(xpos+528, by, 50, bh, _("50"));
				btnBandSelect_10->tooltip(_("6m band"));
				btnBandSelect_10->color((Fl_Color)246);
				btnBandSelect_10->callback((Fl_Callback*)cb_btnBandSelect_10);

				btnBandSelect_11 = new Fl_Button(xpos+587, by, 50, bh, _("GEN"));
				btnBandSelect_11->tooltip(_("General RX"));
				btnBandSelect_11->color((Fl_Color)246);
				btnBandSelect_11->callback((Fl_Callback*)cb_btnBandSelect_11);

				opSelect60 = new Fl_ComboBox(xpos+653, by, 100, bh, _("combo"));
				opSelect60->tooltip(_("vfo / 60 meter channel"));
				opSelect60->box(FL_NO_BOX);
				opSelect60->color((Fl_Color)246);
				opSelect60->selection_color(FL_BACKGROUND_COLOR);
				opSelect60->labeltype(FL_NORMAL_LABEL);
				opSelect60->labelfont(0);
				opSelect60->labelsize(12);
				opSelect60->labelcolor(FL_FOREGROUND_COLOR);
				opSelect60->callback((Fl_Callback*)cb_opSelect60);
				opSelect60->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
				opSelect60->when(FL_WHEN_RELEASE);
				opSelect60->end();

			genericBands->end();

			genericCW = new Fl_Group(xpos, ypos+tabh, W, tabb, _("CW"));
				genericCW->color(FL_LIGHT1);
				genericCW->selection_color(FL_LIGHT1);
				genericCW->hide();

				btnSpot = new Fl_Light_Button(
					xpos+13, by, 54, bh, _("Spot"));
				btnSpot->tooltip(_("Spot tone on/off"));
				btnSpot->callback((Fl_Callback*)cb_btnSpot);
				btnSpot->value(progStatus.cw_spot);

				spnr_cw_spot_tone = new Hspinner(
					btnSpot->x() + btnSpot->w() + 75, by,
					5*bh, bh, _("Spot tone"));
				spnr_cw_spot_tone->tooltip(_("Spot tone freq"));
				spnr_cw_spot_tone->type(FL_INT_INPUT);
				spnr_cw_spot_tone->minimum(300);
				spnr_cw_spot_tone->maximum(1050);
				spnr_cw_spot_tone->step(50);
				spnr_cw_spot_tone->value(1050);
				spnr_cw_spot_tone->callback((Fl_Callback*)cb_spnr_cw_spot_tone);
				spnr_cw_spot_tone->value(progStatus.cw_spot);
				spnr_cw_spot_tone->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				spnr_cw_weight = new Hspinner(
					spnr_cw_spot_tone->x() + spnr_cw_spot_tone->w() + 75, by,
					5*bh, bh, _("Weight"));
				spnr_cw_weight->type(FL_INT_INPUT);
				spnr_cw_weight->minimum(2.5);
				spnr_cw_weight->maximum(4.5);
				spnr_cw_weight->value(3);
				spnr_cw_weight->callback((Fl_Callback*)cb_spnr_cw_weight);
				spnr_cw_weight->value(progStatus.cw_weight);
				spnr_cw_weight->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				spnr_cw_wpm = new Hspinner(
					spnr_cw_weight->x() + spnr_cw_weight->w() + 75, by,
					5*bh, bh, _("wpm"));
				spnr_cw_wpm->type(FL_INT_INPUT);
				spnr_cw_wpm->minimum(5);
				spnr_cw_wpm->maximum(80);
				spnr_cw_wpm->step(1);
				spnr_cw_wpm->callback((Fl_Callback*)cb_spnr_cw_wpm);
				spnr_cw_wpm->value(progStatus.cw_wpm);
				spnr_cw_wpm->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				btn_enable_keyer = new Fl_Check_Button(
					spnr_cw_wpm->x() + spnr_cw_wpm->w() + 10, by,
					5*bh, bh, _("Keyer"));
				btn_enable_keyer->tooltip(_("Enable internal keyer"));
				btn_enable_keyer->down_box(FL_DOWN_BOX);
				btn_enable_keyer->callback((Fl_Callback*)cb_btn_enable_keyer);
				btn_enable_keyer->value(progStatus.enable_keyer);

			genericCW->end();

			genericQSK = new Fl_Group(xpos, ypos+tabh, W, tabb, _("QSK"));
				genericQSK->color(FL_LIGHT1);
				genericQSK->selection_color(FL_LIGHT1);
				genericQSK->hide();

				btnBreakIn = new Fl_Light_Button(xpos + 13, by, 54, bh, _("QSK"));
				btnBreakIn->tooltip(_("Full break in on/off"));
				btnBreakIn->callback((Fl_Callback*)cb_btnBreakIn);
				btnBreakIn->value(progStatus.break_in);

				spnr_cw_qsk = new Hspinner(
					btnBreakIn->x() + btnBreakIn->w() + 75, by,
					5*bh, bh, _("Bk-in Dly"));
				spnr_cw_qsk->tooltip(_("msec"));
				spnr_cw_qsk->type(FL_INT_INPUT);
				spnr_cw_qsk->minimum(0);
				spnr_cw_qsk->maximum(100);
				spnr_cw_qsk->step(1);
				spnr_cw_qsk->value(20);
				spnr_cw_qsk->callback((Fl_Callback*)cb_spnr_cw_qsk);
				spnr_cw_qsk->value(progStatus.cw_qsk);
				spnr_cw_qsk->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				spnr_cw_delay = new Hspinner(
					spnr_cw_qsk->x() + spnr_cw_qsk->w() + 75, by, 120, bh, _("QSK delay"));
				spnr_cw_delay->tooltip(_("msec"));
				spnr_cw_delay->type(0);
				spnr_cw_delay->minimum(30);
				spnr_cw_delay->maximum(3000);
				spnr_cw_delay->step(10);
				spnr_cw_delay->callback((Fl_Callback*)cb_spnr_cw_delay);
				spnr_cw_delay->value(progStatus.cw_delay);
				spnr_cw_delay->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

			genericQSK->end();

			genericVOX = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Vox"));
				genericVOX->hide();

				spnr_vox_gain = new Hspinner(xpos+60, by, 5*bh, bh, _("gain"));
				spnr_vox_gain->type(FL_INT_INPUT);
				spnr_vox_gain->minimum(0);
				spnr_vox_gain->maximum(100);
				spnr_vox_gain->step(1);
				spnr_vox_gain->callback((Fl_Callback*)cb_spnr_vox_gain);
				spnr_vox_gain->value(progStatus.vox_gain);
				spnr_vox_gain->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				spnr_anti_vox = new Hspinner(
					spnr_vox_gain->x() +
					spnr_vox_gain->w() + 60,
					by, 5*bh, bh, _("anti"));
				spnr_anti_vox->type(FL_INT_INPUT);
				spnr_anti_vox->minimum(0);
				spnr_anti_vox->maximum(100);
				spnr_anti_vox->step(1);
				spnr_anti_vox->callback((Fl_Callback*)cb_spnr_anti_vox);
				spnr_anti_vox->value(progStatus.vox_anti);
				spnr_anti_vox->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				spnr_vox_hang = new Hspinner(
					spnr_anti_vox->x() +
					spnr_anti_vox->w() + 60,
					by, 5*bh, bh, _("hang"));
				spnr_vox_hang->type(FL_INT_INPUT);
				spnr_vox_hang->minimum(0);
				spnr_vox_hang->maximum(100);
				spnr_vox_hang->step(1);
				spnr_vox_hang->callback((Fl_Callback*)cb_spnr_vox_hang);
				spnr_vox_hang->value(progStatus.vox_hang);
				spnr_vox_hang->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				btn_vox = new Fl_Light_Button(
					spnr_vox_hang->x() +
					spnr_vox_hang->w() + 8,
					by, 70, bh, _("VOX"));
				btn_vox->callback((Fl_Callback*)cb_btn_vox);
				btn_vox->value(progStatus.vox_onoff);

				btn_vox_on_dataport = new Fl_Check_Button(
					btn_vox->x() +
					btn_vox->w() + 8,
					by, 70, bh, _("Data port"));
				btn_vox_on_dataport->tooltip(_("Data port signal triggers VOX"));
				btn_vox_on_dataport->down_box(FL_DOWN_BOX);
				btn_vox_on_dataport->callback((Fl_Callback*)cb_btn_vox_on_dataport);
				btn_vox_on_dataport->value(progStatus.vox_on_dataport);

			genericVOX->end();

			genericSpeech = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Spch"));
				genericSpeech->hide();

				btnCompON = new Fl_Light_Button(xpos+230, by, 70, bh, _("On"));
				btnCompON->callback((Fl_Callback*)cb_btnCompON);
				btnCompON->value(progStatus.compON);

				spnr_compression = new Hspinner(xpos+138, by, 5*bh, bh, _("Compression"));
				spnr_compression->type(FL_INT_INPUT);
				spnr_compression->minimum(0);
				spnr_compression->maximum(100);
				spnr_compression->step(1);
				spnr_compression->callback((Fl_Callback*)cb_spnr_compression);
				spnr_compression->value(progStatus.compression);
				spnr_compression->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

			genericSpeech->end();

			genericRx = new Fl_Group(xpos, ypos+tabh, W, tabb, _("RX"));
				genericRx->hide();

				cbo_nb_level = new Fl_ComboBox(xpos+90, by, 80, bh, _("NB level"));
				cbo_nb_level->tooltip(_("Select Transceiver"));
				cbo_nb_level->box(FL_DOWN_BOX);
				cbo_nb_level->color(FL_BACKGROUND_COLOR);
				cbo_nb_level->selection_color(FL_BACKGROUND_COLOR);
				cbo_nb_level->labeltype(FL_NORMAL_LABEL);
				cbo_nb_level->labelfont(0);
				cbo_nb_level->labelsize(14);
				cbo_nb_level->labelcolor(FL_FOREGROUND_COLOR);
				cbo_nb_level->callback((Fl_Callback*)cb_cbo_nb_level);
				cbo_nb_level->align(Fl_Align(FL_ALIGN_LEFT));
				cbo_nb_level->when(FL_WHEN_RELEASE);
				cbo_nb_level->index(progStatus.nb_level);
				cbo_nb_level->end();

				cbo_agc_level = new Fl_ComboBox(xpos+244, by, 80, bh, _("AGC"));
				cbo_agc_level->tooltip(_("Select Transceiver"));
				cbo_agc_level->box(FL_DOWN_BOX);
				cbo_agc_level->color(FL_BACKGROUND_COLOR);
				cbo_agc_level->selection_color(FL_BACKGROUND_COLOR);
				cbo_agc_level->labeltype(FL_NORMAL_LABEL);
				cbo_agc_level->labelfont(0);
				cbo_agc_level->labelsize(14);
				cbo_agc_level->labelcolor(FL_FOREGROUND_COLOR);
				cbo_agc_level->callback((Fl_Callback*)cb_cbo_agc_level);
				cbo_agc_level->align(Fl_Align(FL_ALIGN_LEFT));
				cbo_agc_level->when(FL_WHEN_RELEASE);
				cbo_agc_level->end();

				spnr_bpf_center = new Hspinner(xpos+474, by, 5*bh, bh, _("BPF Center Freq"));
				spnr_bpf_center->tooltip(_("Bandpass Filter Center Freq"));
				spnr_bpf_center->type(FL_INT_INPUT);
				spnr_bpf_center->minimum(600);
				spnr_bpf_center->maximum(2500);
				spnr_bpf_center->step(10);
				spnr_bpf_center->value(1500);
				spnr_bpf_center->callback((Fl_Callback*)cb_spnr_bpf_center);
				spnr_bpf_center->value(progStatus.bpf_center);
				spnr_bpf_center->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				btn_use_bpf_center = new Fl_Check_Button(
					spnr_bpf_center->x() + spnr_bpf_center->w() + 8,
					by, 50, bh, _("On"));
				btn_use_bpf_center->tooltip(_("Use Filter Center Freq Adj"));
				btn_use_bpf_center->down_box(FL_DOWN_BOX);
				btn_use_bpf_center->value(1);
				btn_use_bpf_center->callback((Fl_Callback*)cb_btn_use_bpf_center);
				btn_use_bpf_center->value(progStatus.use_bpf_center);

			genericRx->end();

			genericMisc = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Misc"));
				genericMisc->hide();

				spnr_vfo_adj = new Hspinner(xpos+100, by, 5*bh, bh, _("Vfo Adj"));
				spnr_vfo_adj->type(FL_INT_INPUT);
				spnr_vfo_adj->callback((Fl_Callback*)cb_spnr_vfo_adj);
				spnr_vfo_adj->value(progStatus.vfo_adj);
				spnr_vfo_adj->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				spnr_line_out = new Hspinner(
					spnr_vfo_adj->x() +
					spnr_vfo_adj->w() + 8,
					by, 5*bh, bh, _("line out"));
				spnr_line_out->type(FL_INT_INPUT);
				spnr_line_out->minimum(0);
				spnr_line_out->maximum(100);
				spnr_line_out->step(1);
				spnr_line_out->value(20);
				spnr_line_out->callback((Fl_Callback*)cb_spnr_line_out);
				spnr_line_out->value(progStatus.line_out);
				spnr_line_out->align(FL_ALIGN_CENTER | FL_ALIGN_BOTTOM);

				btnSpecial = new Fl_Light_Button(
					spnr_line_out->x() +
					spnr_line_out->w() + 8,
					by, 74, bh, _("Special"));
				btnSpecial->callback((Fl_Callback*)cb_btnSpecial);

				btn_xcvr_auto_on = new Fl_Check_Button(
					btnSpecial->x() +
					btnSpecial->w() + 8,
					by, 95, bh, _("Rig autOn"));
				btn_xcvr_auto_on->tooltip(_("Auto Turn Rig On with Flrig startup"));
				btn_xcvr_auto_on->down_box(FL_DOWN_BOX);
				btn_xcvr_auto_on->callback((Fl_Callback*)cb_btn_xcvr_auto_on);
				btn_xcvr_auto_on->value(progStatus.xcvr_auto_on);

				btn_xcvr_auto_off = new Fl_Check_Button(
					btn_xcvr_auto_on->x() +
					btn_xcvr_auto_on->w() + 15,
					by, 95, bh, _("Rig autOff"));
				btn_xcvr_auto_off->tooltip(_("Auto Turn Rig Off with Flrig exit"));
				btn_xcvr_auto_off->down_box(FL_DOWN_BOX);
				btn_xcvr_auto_off->callback((Fl_Callback*)cb_btn_xcvr_auto_off);
				btn_xcvr_auto_off->value(progStatus.xcvr_auto_off);

			genericMisc->end();

			genericRXB = new Fl_Group(xpos, ypos+tabh, W, tabb, _("RIT/XIT/BFO"));
				genericRXB->hide();

				cntRIT = new Hspinner(xpos+10, by, 5*bh, bh, _("Rit"));
				cntRIT->tooltip(_("RIT"));
				cntRIT->type(FL_INT_INPUT);
				cntRIT->labelsize(12);
				cntRIT->minimum(-1000);
				cntRIT->maximum(1000);
				cntRIT->step(10);
				cntRIT->callback((Fl_Callback*)cb_cntRIT);
				cntRIT->align(Fl_Align(FL_ALIGN_RIGHT));

				cntXIT = new Hspinner(
					cntRIT->x() +
					cntRIT->w() + 8,
					by, 5*bh, bh, _("Xit"));
				cntXIT->tooltip(_("XIT"));
				cntXIT->type(FL_INT_INPUT);
				cntXIT->labelsize(12);
				cntXIT->minimum(-1000);
				cntXIT->maximum(1000);
				cntXIT->step(10);
				cntXIT->callback((Fl_Callback*)cb_cntXIT);
				cntXIT->align(Fl_Align(FL_ALIGN_RIGHT));

				cntBFO = new Hspinner(
					cntXIT->x() + cntXIT->w() + 8, by, 5*bh, bh, _("Bfo"));
				cntBFO->tooltip(_("BFO"));
				cntBFO->type(FL_INT_INPUT);
				cntBFO->labelsize(12);
				cntBFO->minimum(0);
				cntBFO->maximum(1000);
				cntBFO->step(10);
				cntBFO->value(600);
				cntBFO->callback((Fl_Callback*)cb_cntBFO);
				cntBFO->align(Fl_Align(FL_ALIGN_RIGHT));

			genericRXB->end();

			genericAux = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Aux"));
				genericAux->hide();

				boxControl = new Fl_Box(xpos+57, by, 130, bh, _("Auxilliary Controls:"));
				boxControl->box(FL_FLAT_BOX);
				boxControl->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));

				btnAuxRTS = new Fl_Light_Button(xpos+272, by, 60, bh, _("RTS"));
				btnAuxRTS->tooltip(_("RTS control pin"));
				btnAuxRTS->down_box(FL_THIN_DOWN_BOX);
				btnAuxRTS->labelsize(12);
				btnAuxRTS->callback((Fl_Callback*)cb_btnAuxRTS);
				btnAuxRTS->value(progStatus.aux_rts);

				btnAuxDTR = new Fl_Light_Button(xpos+200, by, 60, bh, _("DTR"));
				btnAuxDTR->tooltip(_("DTR control pin"));
				btnAuxDTR->down_box(FL_THIN_DOWN_BOX);
				btnAuxDTR->labelsize(12);
				btnAuxDTR->callback((Fl_Callback*)cb_btnAuxDTR);
				btnAuxDTR->value(progStatus.aux_dtr);

				btnDataPort = new Fl_Light_Button(xpos+408, by, 60, bh, _("Data"));
				btnDataPort->tooltip(_("Input on Data Port"));
				btnDataPort->down_box(FL_THIN_DOWN_BOX);
				btnDataPort->labelsize(12);
				btnDataPort->callback((Fl_Callback*)cb_btnDataPort);
				btnDataPort->value(progStatus.data_port);

			genericAux->end();

		tabsGeneric->end();

		xpos = X;
		ypos = Y;

		tabs550 = new Fl_Tabs(xpos, ypos, W, H-ypos);
			tabs550->selection_color(FL_LIGHT1);
			tabs550->hide();

			tt550_CW = new Fl_Group(xpos, ypos+tabh, W, tabb, _("CW"));
				tt550_CW->color(FL_LIGHT1);
				tt550_CW->selection_color(FL_LIGHT1);

				spnr_tt550_cw_wpm = new Hspinner(xpos+60, by, 5*bh, bh, _("wpm"));
				spnr_tt550_cw_wpm->type(FL_INT_INPUT);
				spnr_tt550_cw_wpm->minimum(5);
				spnr_tt550_cw_wpm->maximum(80);
				spnr_tt550_cw_wpm->step(1);
				spnr_tt550_cw_wpm->value(20);
				spnr_tt550_cw_wpm->callback((Fl_Callback*)cb_spnr_tt550_cw_wpm);
				spnr_tt550_cw_wpm->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_cw_wpm->value(progStatus.tt550_cw_wpm);

				spnr_tt550_cw_weight = new Hspinner(
					xpos + 60, by + bh + 2,
					5*bh, bh, _("Weight"));
				spnr_tt550_cw_weight->type(FL_INT_INPUT);
				spnr_tt550_cw_weight->minimum(0.75);
				spnr_tt550_cw_weight->maximum(1.5);
				spnr_tt550_cw_weight->step(0.05);
				spnr_tt550_cw_weight->value(20);
				spnr_tt550_cw_weight->callback((Fl_Callback*)cb_spnr_tt550_cw_weight);
				spnr_tt550_cw_weight->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_cw_weight->value(progStatus.tt550_cw_weight);

				spnr_tt550_cw_qsk = new Hspinner(
					spnr_tt550_cw_weight->x() + spnr_tt550_cw_weight->w() + 60, by,
					5*bh, bh, _("Delay"));
				spnr_tt550_cw_qsk->tooltip(_("QSK delay (msec)"));
				spnr_tt550_cw_qsk->type(FL_INT_INPUT);
				spnr_tt550_cw_qsk->minimum(0);
				spnr_tt550_cw_qsk->maximum(100);
				spnr_tt550_cw_qsk->step(1);
				spnr_tt550_cw_qsk->value(20);
				spnr_tt550_cw_qsk->callback((Fl_Callback*)cb_spnr_tt550_cw_qsk);
				spnr_tt550_cw_qsk->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_cw_qsk->value(progStatus.tt550_cw_qsk);

				spnr_tt550_cw_vol = new Hspinner(
					spnr_tt550_cw_qsk->x() + spnr_tt550_cw_qsk->w() + 60, by,
					5*bh, bh, _("S-T vol"));
				spnr_tt550_cw_vol->tooltip(_("Side tone volume"));
				spnr_tt550_cw_vol->type(FL_INT_INPUT);
				spnr_tt550_cw_vol->minimum(5);
				spnr_tt550_cw_vol->maximum(80);
				spnr_tt550_cw_vol->step(1);
				spnr_tt550_cw_vol->value(20);
				spnr_tt550_cw_vol->callback((Fl_Callback*)cb_spnr_tt550_cw_vol);
				spnr_tt550_cw_vol->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_cw_vol->value(progStatus.tt550_cw_vol);

				spnr_tt550_cw_spot = new Hspinner(
					spnr_tt550_cw_vol->x() + spnr_tt550_cw_vol->w() + 70, by,
					5*bh, bh, _("Spot Vol"));
				spnr_tt550_cw_spot->tooltip(_("Spot volume"));
				spnr_tt550_cw_spot->type(FL_INT_INPUT);
				spnr_tt550_cw_spot->minimum(0);
				spnr_tt550_cw_spot->maximum(100);
				spnr_tt550_cw_spot->step(1);
				spnr_tt550_cw_spot->value(20);
				spnr_tt550_cw_spot->callback((Fl_Callback*)cb_spnr_tt550_cw_spot);
				spnr_tt550_cw_spot->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_cw_spot->value(progStatus.tt550_cw_spot);

				btn_tt550_enable_keyer = new Fl_Check_Button(
					spnr_tt550_cw_spot->x() + spnr_tt550_cw_spot->w() + 60, by,
					63, bh, _("Keyer"));
				btn_tt550_enable_keyer->tooltip(_("Enable keyer"));
				btn_tt550_enable_keyer->down_box(FL_DOWN_BOX);
				btn_tt550_enable_keyer->callback((Fl_Callback*)cb_btn_tt550_enable_keyer);
				btn_tt550_enable_keyer->value(progStatus.tt550_enable_keyer);

			tt550_CW->end();

			tt550_VOX = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Vox"));
				tt550_VOX->hide();

				spnr_tt550_vox_gain = new Hspinner(xpos+60, by, 79, bh, _("gain"));
				spnr_tt550_vox_gain->type(FL_INT_INPUT);
				spnr_tt550_vox_gain->minimum(0);
				spnr_tt550_vox_gain->maximum(100);
				spnr_tt550_vox_gain->step(1);
				spnr_tt550_vox_gain->callback((Fl_Callback*)cb_spnr_tt550_vox_gain);
				spnr_tt550_vox_gain->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_vox_gain->value(progStatus.tt550_vox_gain);

				spnr_tt550_anti_vox = new Hspinner(
					spnr_tt550_vox_gain->x() +
					spnr_tt550_vox_gain->w() + 60, by,
					5*bh, bh, _("anti"));
				spnr_tt550_anti_vox->type(FL_INT_INPUT);
				spnr_tt550_anti_vox->minimum(0);
				spnr_tt550_anti_vox->maximum(100);
				spnr_tt550_anti_vox->step(1);
				spnr_tt550_anti_vox->callback((Fl_Callback*)cb_spnr_tt550_anti_vox);
				spnr_tt550_anti_vox->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_anti_vox->value(progStatus.tt550_vox_anti);

				spnr_tt550_vox_hang = new Hspinner(
					spnr_tt550_anti_vox->x() +
					spnr_tt550_anti_vox->w() + 60, by,
					5*bh, bh, _("hang"));
				spnr_tt550_vox_hang->type(FL_INT_INPUT);
				spnr_tt550_vox_hang->minimum(0);
				spnr_tt550_vox_hang->maximum(100);
				spnr_tt550_vox_hang->step(1);
				spnr_tt550_vox_hang->callback((Fl_Callback*)cb_spnr_tt550_vox_hang);
				spnr_tt550_vox_hang->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_vox_hang->value(progStatus.tt550_vox_hang);

				btn_tt550_vox = new Fl_Light_Button(
					spnr_tt550_vox_hang->x() +
					spnr_tt550_vox_hang->w() + 60, by,
					78, bh, _("VOX"));
				btn_tt550_vox->callback((Fl_Callback*)cb_btn_tt550_vox);
				btn_tt550_vox->value(progStatus.tt550_vox_onoff);

			tt550_VOX->end();

			tt550_Speech = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Spch"));
				tt550_Speech->hide();

				btn_tt550_CompON = new Fl_Light_Button(xpos+60, by, 78, bh, _("On"));
				btn_tt550_CompON->callback((Fl_Callback*)cb_btn_tt550_CompON);
				btn_tt550_CompON->value(progStatus.tt550_compON);

				spnr_tt550_compression = new Hspinner(
					btn_tt550_CompON->x() + btn_tt550_CompON->w() + 60, by,
					5*bh, bh, _("Comp"));
				spnr_tt550_compression->type(FL_INT_INPUT);
				spnr_tt550_compression->minimum(0);
				spnr_tt550_compression->maximum(100);
				spnr_tt550_compression->step(1);
				spnr_tt550_compression->callback((Fl_Callback*)cb_spnr_tt550_compression);
				spnr_tt550_compression->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_compression->value(progStatus.tt550_compression);

				spnr_tt550_mon_vol = new Hspinner(
					spnr_tt550_compression->x() + spnr_tt550_compression->w() + 60, by,
					5*bh, bh, _("Mon vol"));
				spnr_tt550_mon_vol->tooltip(_("Side tone volume"));
				spnr_tt550_mon_vol->type(FL_INT_INPUT);
				spnr_tt550_mon_vol->minimum(0);
				spnr_tt550_mon_vol->maximum(100);
				spnr_tt550_mon_vol->step(1);
				spnr_tt550_mon_vol->value(25);
				spnr_tt550_mon_vol->callback((Fl_Callback*)cb_spnr_tt550_mon_vol);
				spnr_tt550_mon_vol->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_mon_vol->value(progStatus.tt550_mon_vol);

			tt550_Speech->end();

			tt550_Audio = new Fl_Group(xpos, ypos+tabh, W, tabb, _("Audio"));
				tt550_Audio->hide();

				spnr_tt550_line_out = new Hspinner(xpos+60, by, 5*bh, bh, _("line out"));
				spnr_tt550_line_out->type(FL_INT_INPUT);
				spnr_tt550_line_out->minimum(0);
				spnr_tt550_line_out->maximum(100);
				spnr_tt550_line_out->step(1);
				spnr_tt550_line_out->value(20);
				spnr_tt550_line_out->callback((Fl_Callback*)cb_spnr_tt550_line_out);
				spnr_tt550_line_out->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_line_out->value(progStatus.tt550_line_out);

				btnAccInp = new Fl_Check_Button(
					spnr_tt550_line_out->x() + spnr_tt550_line_out->w() + 8, by,
					92, bh, _("Acc Inp."));
				btnAccInp->tooltip(_("Enable to use accessory audio input"));
				btnAccInp->down_box(FL_DOWN_BOX);
				btnAccInp->callback((Fl_Callback*)cb_btnAccInp);
				btnAccInp->value(progStatus.tt550_use_line_in);

			tt550_Audio->end();

			tt550_Rx = new Fl_Group(xpos, ypos+tabh, W, tabb, _("RX"));
				tt550_Rx->hide();

				cbo_tt550_nb_level = new Fl_ComboBox(xpos+80, by, 89, bh, _("NB level"));
				cbo_tt550_nb_level->tooltip(_("Select Transceiver"));
				cbo_tt550_nb_level->box(FL_DOWN_BOX);
				cbo_tt550_nb_level->color(FL_BACKGROUND_COLOR);
				cbo_tt550_nb_level->selection_color(FL_BACKGROUND_COLOR);
				cbo_tt550_nb_level->labeltype(FL_NORMAL_LABEL);
				cbo_tt550_nb_level->labelfont(0);
				cbo_tt550_nb_level->labelsize(14);
				cbo_tt550_nb_level->labelcolor(FL_FOREGROUND_COLOR);
				cbo_tt550_nb_level->callback((Fl_Callback*)cb_cbo_tt550_nb_level);
				cbo_tt550_nb_level->align(Fl_Align(FL_ALIGN_LEFT));
				cbo_tt550_nb_level->when(FL_WHEN_RELEASE);
				cbo_tt550_nb_level->index(progStatus.tt550_nb_level);
				cbo_tt550_nb_level->end();

				cbo_tt550_agc_level = new Fl_ComboBox(
					cbo_tt550_nb_level->x() +
					cbo_tt550_nb_level->w() + 60, by,
					90, bh, _("AGC"));
				cbo_tt550_agc_level->tooltip(_("Select Transceiver"));
				cbo_tt550_agc_level->box(FL_DOWN_BOX);
				cbo_tt550_agc_level->color(FL_BACKGROUND_COLOR);
				cbo_tt550_agc_level->selection_color(FL_BACKGROUND_COLOR);
				cbo_tt550_agc_level->labeltype(FL_NORMAL_LABEL);
				cbo_tt550_agc_level->labelfont(0);
				cbo_tt550_agc_level->labelsize(14);
				cbo_tt550_agc_level->labelcolor(FL_FOREGROUND_COLOR);
				cbo_tt550_agc_level->callback((Fl_Callback*)cb_cbo_tt550_agc_level);
				cbo_tt550_agc_level->align(Fl_Align(FL_ALIGN_LEFT));
				cbo_tt550_agc_level->when(FL_WHEN_RELEASE);
				cbo_tt550_agc_level->index(progStatus.tt550_agc_level);
				cbo_tt550_agc_level->end();

				spnr_tt550_vfo_adj = new Hspinner(
					cbo_tt550_agc_level->x() +
					cbo_tt550_agc_level->w() + 120, by,
					5*bh, bh, _("Vfo Adj(ppm)"));
				spnr_tt550_vfo_adj->callback((Fl_Callback*)cb_spnr_tt550_vfo_adj);
				spnr_tt550_vfo_adj->align(Fl_Align(36));
				spnr_tt550_vfo_adj->value(progStatus.vfo_adj);
				spnr_tt550_vfo_adj->step(1.0);

			tt550_Rx->end();

			tt550_Tx = new Fl_Group(xpos, ypos+tabh, W, tabb, _("TX"));
				tt550_Tx->hide();

				btn_tt550_enable_xmtr = new Fl_Check_Button(xpos+111, by, 78, bh, _("Tx ON"));
				btn_tt550_enable_xmtr->down_box(FL_DOWN_BOX);
				btn_tt550_enable_xmtr->value(1);
				btn_tt550_enable_xmtr->callback((Fl_Callback*)cb_btn_tt550_enable_xmtr);
				btn_tt550_enable_xmtr->value(progStatus.tt550_enable_xmtr);

				btn_tt550_enable_tloop = new Fl_Check_Button(xpos+197, by, 78, bh, _("Tloop"));
				btn_tt550_enable_tloop->down_box(FL_DOWN_BOX);
				btn_tt550_enable_tloop->callback((Fl_Callback*)cb_btn_tt550_enable_tloop);
				btn_tt550_enable_tloop->value(progStatus.tt550_enable_tloop);

				btn_tt550_tuner_bypass = new Fl_Check_Button(xpos+283, by, 78, bh, _("Tuner"));
				btn_tt550_tuner_bypass->tooltip(_("Check to bypass tuner"));
				btn_tt550_tuner_bypass->down_box(FL_DOWN_BOX);
				btn_tt550_tuner_bypass->callback((Fl_Callback*)cb_btn_tt550_tuner_bypass);

				op_tt550_XmtBW = new Fl_ComboBox(xpos+462, by, 112, bh, _("Xmt BW"));
				op_tt550_XmtBW->tooltip(_("Select Transceiver Bandwidth"));
				op_tt550_XmtBW->box(FL_DOWN_BOX);
				op_tt550_XmtBW->color(FL_BACKGROUND_COLOR);
				op_tt550_XmtBW->selection_color(FL_BACKGROUND_COLOR);
				op_tt550_XmtBW->labeltype(FL_NORMAL_LABEL);
				op_tt550_XmtBW->labelfont(0);
				op_tt550_XmtBW->labelsize(12);
				op_tt550_XmtBW->labelcolor(FL_FOREGROUND_COLOR);
				op_tt550_XmtBW->callback((Fl_Callback*)cb_op_tt550_XmtBW);
				op_tt550_XmtBW->align(Fl_Align(FL_ALIGN_LEFT));
				op_tt550_XmtBW->when(FL_WHEN_RELEASE);
				op_tt550_XmtBW->index(progStatus.tt550_xmt_bw);
				op_tt550_XmtBW->end();

				btn_tt550_use_xmt_bw = new Fl_Check_Button(xpos+613, by, 23, bh, _("Enable"));
				btn_tt550_use_xmt_bw->tooltip(_("Use Xmt BW setting"));
				btn_tt550_use_xmt_bw->down_box(FL_DOWN_BOX);
				btn_tt550_use_xmt_bw->callback((Fl_Callback*)cb_btn_tt550_use_xmt_bw);
				btn_tt550_use_xmt_bw->align(Fl_Align(FL_ALIGN_RIGHT));
				btn_tt550_use_xmt_bw->value(progStatus.tt550_use_xmt_bw);

			tt550_Tx->end();

			tt550_302A = new Fl_Group(xpos, ypos+tabh, W, tabb, _("302-A"));
				tt550_302A->hide();

				spnr_tt550_keypad_time_out = new Hspinner(xpos+100, by, 5*bh, bh, _("Time out"));
				spnr_tt550_keypad_time_out->tooltip(_("Clear M302 keypad after ## secs"));
				spnr_tt550_keypad_time_out->minimum(0.5);
				spnr_tt550_keypad_time_out->maximum(10);
				spnr_tt550_keypad_time_out->value(2);
				spnr_tt550_keypad_time_out->callback((Fl_Callback*)cb_spnr_tt550_keypad_time_out);
				spnr_tt550_keypad_time_out->align(Fl_Align(36));
				spnr_tt550_keypad_time_out->value(progStatus.tt550_keypad_timeout/1000.0);
				spnr_tt550_keypad_time_out->step(0.1);

				spnr_tt550_encoder_sensitivity = new Hspinner(
					spnr_tt550_keypad_time_out->x() +
					spnr_tt550_keypad_time_out->w() + 100,
					by, 5*bh, bh, _("Sensitivity"));
				spnr_tt550_encoder_sensitivity->tooltip(_("1 - most sensitive"));
				spnr_tt550_encoder_sensitivity->type(FL_INT_INPUT);
				spnr_tt550_encoder_sensitivity->minimum(1);
				spnr_tt550_encoder_sensitivity->maximum(25);
				spnr_tt550_encoder_sensitivity->step(1);
				spnr_tt550_encoder_sensitivity->value(10);
				spnr_tt550_encoder_sensitivity->callback((Fl_Callback*)cb_spnr_tt550_encoder_sensitivity);
				spnr_tt550_encoder_sensitivity->align(Fl_Align(FL_ALIGN_LEFT));
				spnr_tt550_encoder_sensitivity->value(progStatus.tt550_encoder_sensitivity);

				sel_tt550_encoder_step = new Fl_Choice(
					spnr_tt550_encoder_sensitivity->x() +
					spnr_tt550_encoder_sensitivity->w() + 100,
					by, 80, bh, _("Step size"));
				sel_tt550_encoder_step->down_box(FL_BORDER_BOX);
				sel_tt550_encoder_step->callback((Fl_Callback*)cb_sel_tt550_encoder_step);
				sel_tt550_encoder_step->add("1|10|100|1 K|10 K");
				sel_tt550_encoder_step->value(progStatus.tt550_encoder_step);

			tt550_302A->end();

			tt550_302B = new Fl_Group(xpos, ypos+tabh, W, tabb, _("302-B"));
				tt550_302B->hide();

				sel_tt550_F1_func = new Fl_Choice(xpos+168, by, 111, bh, _("F1"));
				sel_tt550_F1_func->tooltip(_("Assign Func Key"));
				sel_tt550_F1_func->down_box(FL_BORDER_BOX);
				sel_tt550_F1_func->callback((Fl_Callback*)cb_sel_tt550_F1_func);
				sel_tt550_F1_func->add("None|Clear|CW++|CW--|Band++|Band--|Step++|Step--");
				sel_tt550_F1_func->value(progStatus.tt550_F1_func);

				sel_tt550_F2_func = new Fl_Choice(xpos+319, by, 111, bh, _("F2"));
				sel_tt550_F2_func->tooltip(_("Assign Func Key"));
				sel_tt550_F2_func->down_box(FL_BORDER_BOX);
				sel_tt550_F2_func->callback((Fl_Callback*)cb_sel_tt550_F2_func);
				sel_tt550_F2_func->add("None|Clear|CW++|CW--|Band++|Band--|Step++|Step--");
				sel_tt550_F2_func->value(progStatus.tt550_F2_func);

				sel_tt550_F3_func = new Fl_Choice(xpos+465, by, 111, bh, _("F3"));
				sel_tt550_F3_func->tooltip(_("Assign Func Key"));
				sel_tt550_F3_func->down_box(FL_BORDER_BOX);
				sel_tt550_F3_func->callback((Fl_Callback*)cb_sel_tt550_F3_func);
				sel_tt550_F3_func->add("None|Clear|CW++|CW--|Band++|Band--|Step++|Step--");
				sel_tt550_F3_func->value(progStatus.tt550_F3_func);

			tt550_302B->end();

		tabs550->end();

	grpOTHER->end();

	grpMAIN->show();
	grpSLIDERS->hide();
	grpBUTTONS->hide();
	grpOTHER->hide();

	tmg->end();

	return tmg;
}

Fl_Double_Window* touch_rig_window() {
	int mainW = TOUCH_MAINW;
	int mainH = TOUCH_MAINH;
	Fl_Double_Window* w = new Fl_Double_Window(mainW, mainH, _("Flrig"));
	w->align(Fl_Align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE));

	Fl_Group* grp_menu = new Fl_Group(0,0,mainW,30);

		Fl_Menu_Bar *touch_menubar = new Fl_Menu_Bar(0, 0, mainW-64, 28);
		touch_menubar->textsize(18);
		progStatus.tooltips ? (&touch_menu[6])->set() : (&touch_menu[6])->clear();
		touch_menubar->menu(touch_menu);

		Fl_Group *mnu_box = new Fl_Group(mainW-64, 0, 64, 28);
		mnu_box->box(FL_UP_BOX);

			tcpip_box = new Fl_Group(mainW-62, 0, 60, 28);
			tcpip_box->box(FL_FLAT_BOX);

			tcpip_menu_box = new Fl_Box(mainW - 62, 0, 18, 28);
			tcpip_menu_box->box(FL_DIAMOND_BOX);
			tcpip_menu_box->color(FL_GREEN);
			Fl_Box *tcpip_menu_label = new Fl_Box(mainW - 62 + 20, 0, 64 - 22, 28, _("tcpip"));
			tcpip_menu_label->box(FL_FLAT_BOX);
			tcpip_menu_label->align(FL_ALIGN_CENTER);
			tcpip_menu_label->tooltip(_("lit when connected to remote tcpip"));

			tcpip_box->end();
			tcpip_box->hide();

		mnu_box->end();

		grp_menu->resizable(touch_menubar);

	grp_menu->end();

	mnuRestoreData = (touch_menu+12);
	mnuKeepData = (touch_menu+13);
	mnuTooltips = (touch_menu+17);

	btnInitializing = new Fl_Button(0, 28, mainW, mainH - 28, "Initializing");
	btnInitializing->hide();

	txt_encA = new Fl_Output( 0, 28, 90, 20, "");
	txt_encA->box(FL_THIN_DOWN_BOX);
	txt_encA->align(20);
	txt_encA->hide();

	main_group = touch_main_group(0, 28, mainW, mainH);
	main_group->show();

	w->resizable(main_group);

	w->size_range(mainW, mainH, 0, mainH);
	w->end();

	return w;
}
