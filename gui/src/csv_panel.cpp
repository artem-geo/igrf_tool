#include "csv_panel.hpp"

#include <array>
#include <vector>

#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textfile.h>

namespace {
    std::vector<wxString> parse_header(const wxString& line)
    {
        std::vector<wxString> columns;
        wxString column;
        bool quoted = false;

        for (std::size_t i = 0; i < line.length(); ++i) {
            const wxUniChar character = line[i];

            if (character == '"') {
                if (quoted && i + 1 < line.length() && line[i + 1] == '"') {
                    column += '"';
                    ++i;
                } else {
                    quoted = !quoted;
                }
            } else if (character == ',' && !quoted) {
                columns.push_back(column.Strip(wxString::both));
                column.clear();
            } else {
                column += character;
            }
        }

        columns.push_back(column.Strip(wxString::both));
        return columns;
    }

    wxString normalized(wxString value)
    {
        value.MakeLower();
        value.Replace("_", "");
        value.Replace("-", "");
        value.Replace(" ", "");
        return value;
    }

    void select_matching_column(wxChoice* choice, const std::vector<wxString>& names)
    {
        for (unsigned int i = 0; i < choice->GetCount(); ++i) {
            const wxString candidate = normalized(choice->GetString(i));
            for (const wxString& name : names) {
                if (candidate == name) {
                    choice->SetSelection(i);
                    return;
                }
            }
        }
    }
}

namespace panels {
    CsvPanel::CsvPanel(wxWindow* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
    {
        auto* vszr_csv = new wxBoxSizer(wxVERTICAL);

        auto* gszr_params = new wxGridSizer(1, 2, 0, 0);

        auto* vszr_coords = new wxBoxSizer(wxVERTICAL);

        auto* hszr_lat = new wxBoxSizer(wxHORIZONTAL);
        hszr_lat->Add(new wxStaticText(this, wxID_ANY, "Latitude",
            wxDefaultPosition, wxSize(65, -1)), 0, wxALIGN_CENTER_VERTICAL);
        choice_lat = new wxChoice(this, wxID_ANY);
        choice_lat->Enable(false);
        hszr_lat->Add(choice_lat, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_coords->Add(hszr_lat, 0, wxEXPAND);

        auto* hszr_lon = new wxBoxSizer(wxHORIZONTAL);
        hszr_lon->Add(new wxStaticText(this, wxID_ANY, "Longitude",
            wxDefaultPosition, wxSize(65, -1)), 0, wxALIGN_CENTER_VERTICAL);
        choice_lon = new wxChoice(this, wxID_ANY);
        choice_lon->Enable(false);
        hszr_lon->Add(choice_lon, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_coords->Add(hszr_lon, 0, wxEXPAND | wxTOP, 5);

        auto* hszr_alt = new wxBoxSizer(wxHORIZONTAL);
        hszr_alt->Add(new wxStaticText(this, wxID_ANY, "Altitude",
            wxDefaultPosition, wxSize(65, -1)), 0, wxALIGN_CENTER_VERTICAL);
        choice_alt = new wxChoice(this, wxID_ANY);
        choice_alt->Enable(false);
        hszr_alt->Add(choice_alt, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_coords->Add(hszr_alt, 0, wxEXPAND | wxTOP, 5);

        gszr_params->Add(vszr_coords, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);

        auto* vszr_csv_date_calc = new wxBoxSizer(wxVERTICAL);

        auto* hszr_file = new wxBoxSizer(wxHORIZONTAL);
        hszr_file->Add(new wxStaticText(this, wxID_ANY, "CSV file",
            wxDefaultPosition, wxSize(65, -1)), 0, wxALIGN_CENTER_VERTICAL);
        txtctrl_file = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
        hszr_file->Add(txtctrl_file, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        btn_load = new wxButton(this, wxID_ANY, "...");
        hszr_file->Add(btn_load, 0, wxALIGN_CENTER_VERTICAL);
        vszr_csv_date_calc->Add(hszr_file, 0, wxEXPAND);

        auto* hszr_date = new wxBoxSizer(wxHORIZONTAL);
        hszr_date->Add(new wxStaticText(this, wxID_ANY, "Date",
            wxDefaultPosition, wxSize(65, -1)), 0, wxALIGN_CENTER_VERTICAL);
        choice_date = new wxChoice(this, wxID_ANY);
        choice_date->Enable(false);
        hszr_date->Add(choice_date, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_csv_date_calc->Add(hszr_date, 0, wxEXPAND | wxTOP, 5);

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

        Bind(wxEVT_BUTTON, &CsvPanel::on_load, this, btn_load->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_column_choice, this, choice_lat->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_column_choice, this, choice_lon->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_column_choice, this, choice_alt->GetId());
        Bind(wxEVT_CHOICE, &CsvPanel::on_column_choice, this, choice_date->GetId());
        Bind(wxEVT_BUTTON, &CsvPanel::on_calc, this, btn_calc->GetId());
    }

    void CsvPanel::on_load(wxCommandEvent& event)
    {
        wxFileDialog dialog(this, "Load CSV file", wxEmptyString, wxEmptyString,
            "CSV files (*.csv)|*.csv|All files (*.*)|*.*",
            wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (dialog.ShowModal() != wxID_OK) {
            return;
        }

        wxTextFile file(dialog.GetPath());
        if (!file.Open() || file.GetLineCount() == 0) {
            wxMessageBox("The selected file is empty or could not be opened.",
                "CSV load error", wxOK | wxICON_ERROR, this);
            return;
        }

        const std::vector<wxString> columns = parse_header(file.GetFirstLine());
        file.Close();

        if (columns.empty()) {
            wxMessageBox("No columns were found in the CSV header.",
                "CSV load error", wxOK | wxICON_ERROR, this);
            return;
        }

        const std::array<wxChoice*, 4> choices {
            choice_lat, choice_lon, choice_alt, choice_date
        };

        for (wxChoice* choice : choices) {
            choice->Clear();
            for (const wxString& column : columns) {
                choice->Append(column);
            }
            choice->Enable(true);
        }

        select_matching_column(choice_lat, {"latitude", "lat"});
        select_matching_column(choice_lon, {"longitude", "lon", "lng", "long"});
        select_matching_column(choice_alt, {"altitude", "alt", "elevation"});
        select_matching_column(choice_date, {"date", "datetime", "time"});

        txtctrl_file->SetValue(dialog.GetPath());
        txtctrl_info->SetValue(wxString::Format("Loaded %zu columns from %s.",
            columns.size(), dialog.GetFilename()));
        update_calc_button();
    }

    void CsvPanel::on_column_choice(wxCommandEvent& event)
    {
        update_calc_button();
    }

    void CsvPanel::on_calc(wxCommandEvent& event)
    {
        txtctrl_info->SetValue("CSV calculation is not implemented yet.");
    }

    void CsvPanel::update_calc_button()
    {
        const std::array<int, 4> selections {
            choice_lat->GetSelection(),
            choice_lon->GetSelection(),
            choice_alt->GetSelection(),
            choice_date->GetSelection()
        };

        bool valid = true;
        for (std::size_t i = 0; i < selections.size(); ++i) {
            if (selections[i] == wxNOT_FOUND) {
                valid = false;
                break;
            }
            for (std::size_t j = i + 1; j < selections.size(); ++j) {
                if (selections[i] == selections[j]) {
                    valid = false;
                    break;
                }
            }
        }

        btn_calc->Enable(valid);
    }
}
