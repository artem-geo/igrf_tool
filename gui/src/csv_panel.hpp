#pragma once

#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

namespace panels {
    class CsvPanel : public wxPanel {
    public:
        CsvPanel(wxWindow* parent);
        ~CsvPanel() = default;

    public:
        wxTextCtrl* txtctrl_file;
        wxFilePickerCtrl* fpckr_csv;
        wxChoice* choice_lat;
        wxChoice* choice_lon;
        wxChoice* choice_alt;
        wxChoice* choice_date;
        wxButton* btn_calc;
        wxTextCtrl* txtctrl_info;

    private:

    };
}
