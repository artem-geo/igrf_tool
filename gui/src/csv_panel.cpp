#include "csv_panel.hpp"

#include <array>
#include <vector>

#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textfile.h>

namespace {
    
}

namespace panels {
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
        choice_lat = new wxChoice(this, wxID_ANY);
        choice_lat->Enable(false);
        hszr_lat->Add(choice_lat, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        hszr_lat->Add(new wxStaticText(this, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL);
        vszr_columns->Add(hszr_lat, 0, wxEXPAND, 5);

        wxBoxSizer* hszr_lon = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_lon = new wxStaticText(this, wxID_ANY, "Longitude", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_lon->SetToolTip("Longitued WGS84 column in decimal degrees [-180, 180]");
        hszr_lon->Add(sttxt_lon, 0, wxALIGN_CENTER_VERTICAL, 5);
        choice_lon = new wxChoice(this, wxID_ANY);
        choice_lon->Enable(false);
        hszr_lon->Add(choice_lon, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        hszr_lon->Add(new wxStaticText(this, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL);
        vszr_columns->Add(hszr_lon, 0, wxEXPAND | wxTOP, 5);

        wxBoxSizer* hszr_alt = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_alt = new wxStaticText(this, wxID_ANY, "Altitude", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_alt->SetToolTip("Altitude column in km AMSL [> -2'300]");
        hszr_alt->Add(sttxt_alt, 0, wxALIGN_CENTER_VERTICAL, 5);
        choice_alt = new wxChoice(this, wxID_ANY);
        choice_alt->Enable(false);
        hszr_alt->Add(choice_alt, 3, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        hszr_alt->Add(new wxStaticText(this, wxID_ANY, "km",
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_columns->Add(hszr_alt, 0, wxEXPAND | wxTOP, 5);
        
        auto* hszr_date = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_date = new wxStaticText(this, wxID_ANY, "Date", wxDefaultPosition, 
            wxSize(65, -1), 0);
        sttxt_date->SetToolTip("Date column formatted as YYYY/MM/DD");
        hszr_date->Add(sttxt_date, 0, wxALIGN_CENTER_VERTICAL);
        choice_date = new wxChoice(this, wxID_ANY);
        choice_date->Enable(false);
        hszr_date->Add(choice_date, 3, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        hszr_date->Add(new wxStaticText(this, wxID_ANY, "",
            wxDefaultPosition, wxSize(32, -1), 0), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_columns->Add(hszr_date, 0, wxEXPAND | wxTOP, 5);
            
        gszr_params->Add(vszr_columns, 1, wxEXPAND | wxRIGHT, 5);

        
        auto* vszr_csv_date_calc = new wxBoxSizer(wxVERTICAL);

        auto* hszr_file = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_csv = new wxStaticText(this, wxID_ANY, "CSV file",
            wxDefaultPosition, wxSize(65, -1));
        sttxt_csv->SetToolTip("Choose a CSV file to write IGRF data to");
        hszr_file->Add(sttxt_csv, 0, wxALIGN_CENTER_VERTICAL);
        fpckr_csv = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString,
            "Choose a CSV file", "CSV files (*.csv)|*.csv", wxDefaultPosition,
            wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL | wxFLP_SMALL);
        hszr_file->Add(fpckr_csv, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_csv_date_calc->Add(hszr_file, 0, wxEXPAND);







        btn_calc = new wxButton(this, wxID_ANY, "Calculate");
        btn_calc->Enable(false);
        vszr_csv_date_calc->Add(btn_calc, 0, wxEXPAND | wxTOP, 5);

        gszr_params->Add(vszr_csv_date_calc, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
        vszr_csv->Add(gszr_params, 0, wxEXPAND | wxTOP | wxBOTTOM, 10);

        txtctrl_info = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP);
        vszr_csv->Add(txtctrl_info, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

        SetSizer(vszr_csv);
        Layout();
    }
}
