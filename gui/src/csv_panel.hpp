#pragma once

#include <wx/arrstr.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

namespace panels {
    class ChkBoxes {
    public:
        ChkBoxes() = default;
        ~ChkBoxes() = default;
        void enable(bool is_enable) {
            chk_x->Enable(is_enable);
            chk_y->Enable(is_enable);
            chk_z->Enable(is_enable);
            chk_f->Enable(is_enable);
            chk_d->Enable(is_enable);
            chk_i->Enable(is_enable);
        }
        wxCheckBox* chk_x = nullptr;
        wxCheckBox* chk_y = nullptr;
        wxCheckBox* chk_z = nullptr;
        wxCheckBox* chk_f = nullptr;
        wxCheckBox* chk_d = nullptr;
        wxCheckBox* chk_i = nullptr;
    };
    class CsvPanel : public wxPanel {
    public:
        CsvPanel(wxWindow* parent);
        ~CsvPanel() = default;

    public:
        wxTextCtrl* txtctrl_file;
        wxFilePickerCtrl* fpckr_csv;
        ChkBoxes chkbxs;
        wxChoice* choice_lat;
        wxChoice* choice_lon;
        wxChoice* choice_alt;
        wxChoice* choice_date;
        wxButton* btn_calc;
        wxTextCtrl* txtctrl_info;

    private:
        void on_csv(wxFileDirPickerEvent& event);
        
        void on_lat(wxCommandEvent& event);
        void on_lon(wxCommandEvent& event);
        void on_alt(wxCommandEvent& event);
        void on_date(wxCommandEvent& event);

        void on_x(wxCommandEvent& event);
        void on_y(wxCommandEvent& event);
        void on_z(wxCommandEvent& event);
        void on_f(wxCommandEvent& event);
        void on_d(wxCommandEvent& event);
        void on_i(wxCommandEvent& event);
        
        void enable_ctrls(bool are_enabled);
    };
}
