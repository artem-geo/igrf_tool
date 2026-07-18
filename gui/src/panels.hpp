#pragma once

#include <wx/button.h>
#include <wx/calctrl.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

namespace panels {
    class PointPanel : public wxPanel {
    public:
        PointPanel(wxWindow* parent);
        ~PointPanel() = default;
    public:
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
    private:
        void on_lon(wxCommandEvent& event);
        void on_lat(wxCommandEvent& event);
        void on_alt(wxCommandEvent& event);
        void on_calc(wxCommandEvent& event);
    };
}