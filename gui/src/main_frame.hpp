#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/calctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>
class MainFrame : public wxFrame
{
	private:

	protected:
		wxNotebook* ntb;
		wxPanel* pnl_point;
		wxTextCtrl* txtctrl_lon;
		wxTextCtrl* txtctrl_lat;
		wxTextCtrl* txtctrl_alt;
		wxButton* btn_calc;
		wxCalendarCtrl* clndr;
		wxTextCtrl* txtctrl_res_x;
		wxTextCtrl* txtctrl_res_y;
		wxTextCtrl* txtctrl_res_z;
		wxTextCtrl* txtctrl_res_f;
		wxTextCtrl* txtctrl_res_d;
		wxTextCtrl* txtctrl_res_i;
		wxPanel* pnl_file;

	public:
		MainFrame();
		~MainFrame() = default;

};

