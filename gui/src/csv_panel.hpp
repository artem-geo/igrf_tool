#pragma once

#include <wx/button.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

namespace panels {
    class CsvPanel : public wxPanel {
    public:
        CsvPanel(wxWindow* parent);
        ~CsvPanel() = default;

    public:
        wxTextCtrl* txtctrl_file;
        wxButton* btn_load;
        wxChoice* choice_lat;
        wxChoice* choice_lon;
        wxChoice* choice_alt;
        wxChoice* choice_date;
        wxButton* btn_calc;
        wxTextCtrl* txtctrl_info;

    private:
        void on_load(wxCommandEvent& event);
        void on_column_choice(wxCommandEvent& event);
        void on_calc(wxCommandEvent& event);
        void update_calc_button();
    };
}
