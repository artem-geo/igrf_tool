#include "csv_panel.hpp"

#include <csv.hpp>
#include <filesystem>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textfile.h>

namespace {
    void add_choice_vertical_padding(wxChoice* choice)
    {
        auto min_size = choice->GetBestSize();
        min_size.SetHeight(min_size.GetHeight() + choice->FromDIP(4));
        choice->SetMinSize(min_size);
    }
}

namespace panels {
    void Checkboxes::enable(bool is_enable) 
    {
        x->Enable(is_enable);
        y->Enable(is_enable);
        z->Enable(is_enable);
        f->Enable(is_enable);
        d->Enable(is_enable);
        i->Enable(is_enable);
    }

    bool Checkboxes::is_any_checked()
    {
        return (x->IsChecked()) || (y->IsChecked()) || (z->IsChecked()) ||
               (f->IsChecked()) || (d->IsChecked()) || (i->IsChecked());
    }

    void Choices::enable(bool is_enabled)
    {
        lat->Enable(is_enabled);
        lon->Enable(is_enabled);
        alt->Enable(is_enabled);
        date->Enable(is_enabled);
    }

    void Choices::clear()
    {
        lat->Clear();
        lon->Clear();
        alt->Clear();
        date->Clear();
    }

    void Choices::set(const wxArrayString& column_names)
    {
        lat->Set(column_names);
        lon->Set(column_names);
        alt->Set(column_names);
        date->Set(column_names);
    }

    bool Choices::do_all_chosen()
    {
        return (lat->GetCurrentSelection() != -1) && (lon->GetCurrentSelection() != -1) &&
               (alt->GetCurrentSelection() != -1) && (date->GetCurrentSelection() != -1);
    }

    CsvPanel::CsvPanel(wxWindow* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
    {
        auto* vszr_csv = new wxBoxSizer(wxVERTICAL);

        auto* gszr_params = new wxGridSizer(1, 2, 0, 0);

        auto* vszr_columns = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* hszr_lat = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_lat = new wxStaticText(this, wxID_ANY, "Latitude", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_lat->SetToolTip("Latitude WGS84 column in decimal degrees [-90, 90]");
        hszr_lat->Add(sttxt_lat, 0, wxALIGN_CENTER_VERTICAL, 5);
        choices.lat = new wxChoice(this, wxID_ANY);
        add_choice_vertical_padding(choices.lat);
        choices.lat->Enable(false);
        hszr_lat->Add(choices.lat, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        hszr_lat->Add(new wxStaticText(this, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL);
        vszr_columns->Add(hszr_lat, 0, wxEXPAND);

        wxBoxSizer* hszr_lon = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_lon = new wxStaticText(this, wxID_ANY, "Longitude", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_lon->SetToolTip("Longitued WGS84 column in decimal degrees [-180, 180]");
        hszr_lon->Add(sttxt_lon, 0, wxALIGN_CENTER_VERTICAL, 5);
        choices.lon = new wxChoice(this, wxID_ANY);
        add_choice_vertical_padding(choices.lon);
        choices.lon->Enable(false);
        hszr_lon->Add(choices.lon, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        hszr_lon->Add(new wxStaticText(this, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL);
        vszr_columns->Add(hszr_lon, 0, wxEXPAND | wxTOP, 5);

        wxBoxSizer* hszr_alt = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_alt = new wxStaticText(this, wxID_ANY, "Altitude", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_alt->SetToolTip("Altitude column in km AMSL [> -2'300]");
        hszr_alt->Add(sttxt_alt, 0, wxALIGN_CENTER_VERTICAL, 5);
        choices.alt = new wxChoice(this, wxID_ANY);
        add_choice_vertical_padding(choices.alt);
        choices.alt->Enable(false);
        hszr_alt->Add(choices.alt, 3, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        hszr_alt->Add(new wxStaticText(this, wxID_ANY, "km",
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_columns->Add(hszr_alt, 0, wxEXPAND | wxTOP, 5);
        
        auto* hszr_date = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_date = new wxStaticText(this, wxID_ANY, "Date", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_date->SetToolTip("Date column formatted as YYYY/MM/DD");
        hszr_date->Add(sttxt_date, 0, wxALIGN_CENTER_VERTICAL);
        choices.date = new wxChoice(this, wxID_ANY);
        add_choice_vertical_padding(choices.date);
        choices.date->Enable(false);
        hszr_date->Add(choices.date, 3, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        hszr_date->Add(new wxStaticText(this, wxID_ANY, "",
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_columns->Add(hszr_date, 0, wxEXPAND | wxTOP, 5);
            
        gszr_params->Add(vszr_columns, 1, wxEXPAND | wxRIGHT, 5);
        
        auto* vszr_csv_date_calc = new wxBoxSizer(wxVERTICAL);

        auto* hszr_file = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_csv = new wxStaticText(this, wxID_ANY, "CSV file", wxDefaultPosition,
            wxSize(65, -1), 0);
        sttxt_csv->SetToolTip("Choose a CSV file to write IGRF data to");
        hszr_file->Add(sttxt_csv, 0, wxALIGN_CENTER_VERTICAL);
        fpckr_csv = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString,
            "Choose a CSV file", "CSV files (*.csv)|*.csv", wxDefaultPosition,
            wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL | wxFLP_SMALL);
        hszr_file->Add(fpckr_csv, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_csv_date_calc->Add(hszr_file, 0, wxEXPAND, 5);

        auto* gszr_components = new wxGridSizer(2, 3, 5, 10);
        chkbxs.x = new wxCheckBox(this, wxID_ANY, "X");
        chkbxs.y = new wxCheckBox(this, wxID_ANY, "Y");
        chkbxs.z = new wxCheckBox(this, wxID_ANY, "Z");
        chkbxs.x->SetValue(true);
        chkbxs.y->SetValue(true);
        chkbxs.z->SetValue(true);
        chkbxs.f = new wxCheckBox(this, wxID_ANY, "F");
        chkbxs.d = new wxCheckBox(this, wxID_ANY, "D");
        chkbxs.i = new wxCheckBox(this, wxID_ANY, "I");

        gszr_components->Add(chkbxs.x, 1, wxEXPAND | wxALIGN_CENTRE_HORIZONTAL);
        gszr_components->Add(chkbxs.y, 1, wxEXPAND | wxALIGN_CENTRE_HORIZONTAL);
        gszr_components->Add(chkbxs.z, 1, wxEXPAND | wxALIGN_CENTRE_HORIZONTAL);
        gszr_components->Add(chkbxs.f, 1, wxEXPAND | wxALIGN_CENTRE_HORIZONTAL);
        gszr_components->Add(chkbxs.d, 1, wxEXPAND | wxALIGN_CENTRE_HORIZONTAL);
        gszr_components->Add(chkbxs.i, 1, wxEXPAND | wxALIGN_CENTRE_HORIZONTAL);

        chkbxs.enable(false);

        vszr_csv_date_calc->Add(gszr_components, 0, wxEXPAND | wxTOP, 5);
        vszr_csv_date_calc->AddStretchSpacer(1);

        btn_calc = new wxButton(this, wxID_ANY, "Calculate");
        btn_calc->Enable(false);
        vszr_csv_date_calc->Add(btn_calc, 0, wxEXPAND | wxTOP, 5);

        gszr_params->Add(vszr_csv_date_calc, 1, wxEXPAND | wxLEFT, 10);
        vszr_csv->Add(gszr_params, 0, wxEXPAND | wxALL, 10);

        txtctrl_info = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP);
        vszr_csv->Add(txtctrl_info, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

        this->SetSizer(vszr_csv);
        this->Layout();
        vszr_csv->Fit(this);
        Bind(wxEVT_FILEPICKER_CHANGED, &CsvPanel::on_csv, this, fpckr_csv->GetId());
        Bind(wxEVT_CHECKBOX, &CsvPanel::on_choice_checkbox, this, chkbxs.x->GetId());
        Bind(wxEVT_CHECKBOX, &CsvPanel::on_choice_checkbox, this, chkbxs.y->GetId());
        Bind(wxEVT_CHECKBOX, &CsvPanel::on_choice_checkbox, this, chkbxs.z->GetId());
        Bind(wxEVT_CHECKBOX, &CsvPanel::on_choice_checkbox, this, chkbxs.f->GetId());
        Bind(wxEVT_CHECKBOX, &CsvPanel::on_choice_checkbox, this, chkbxs.d->GetId());
        Bind(wxEVT_CHECKBOX, &CsvPanel::on_choice_checkbox, this, chkbxs.i->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_choice_checkbox, this, choices.lat->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_choice_checkbox, this, choices.lon->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_choice_checkbox, this, choices.alt->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_choice_checkbox, this, choices.date->GetId());
    }

    void CsvPanel::on_csv(wxFileDirPickerEvent& event)
    {
        std::string fpath = std::string(fpckr_csv->GetPath());
        if (!std::filesystem::exists(fpath)) {
            fpckr_csv->SetPath("");
            enable_ctrls(false);
            choices.clear();
        } else {
            csv::CSVReader reader(fpath);
            wxArrayString column_names;
            for (const auto& col_name : reader.get_col_names())
                column_names.Add(col_name);
            choices.set(column_names);
            enable_ctrls(true);
        }
        Layout();
    }

    void CsvPanel::on_choice_checkbox(wxCommandEvent& event) 
    {
        btn_calc->Enable(choices.do_all_chosen() && chkbxs.is_any_checked());
    }


    void CsvPanel::enable_ctrls(bool are_enabled)
    {
        choices.enable(are_enabled);
        chkbxs.enable(are_enabled);
    }
}
