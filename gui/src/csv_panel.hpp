#pragma once

#include <map>
#include <vector>
#include <wx/arrstr.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

namespace panels {
    class Checkboxes {
    public:
        Checkboxes() = default;
        ~Checkboxes() = default;
        void enable(bool is_enable);
        wxCheckBox* x = nullptr;
        wxCheckBox* y = nullptr;
        wxCheckBox* z = nullptr;
        wxCheckBox* f = nullptr;
        wxCheckBox* d = nullptr;
        wxCheckBox* i = nullptr;
        bool is_any_checked();
    };

    class Choices {
    public:
        Choices() = default;
        ~Choices() = default;
        void enable(bool is_enabled);
        void clear();
        void set(const wxArrayString& column_names);
        wxChoice* lat = nullptr;
        wxChoice* lon = nullptr;
        wxChoice* alt = nullptr;
        wxChoice* date = nullptr;
        bool do_all_chosen();
    };

    class CsvPanel : public wxPanel {
    public:
        CsvPanel(wxWindow* parent);
        ~CsvPanel() = default;
    public:
        wxTextCtrl* txtctrl_file;
        wxFilePickerCtrl* fpckr_csv;
        Checkboxes chkbxs;
        Choices choices;
        wxButton* btn_calc;
        wxTextCtrl* txtctrl_info;
    private:
        void on_csv(wxFileDirPickerEvent& event);
        void on_choice_checkbox(wxCommandEvent& event);   
        void enable_ctrls(bool are_enabled);
    };
}
