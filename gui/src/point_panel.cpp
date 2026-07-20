#include "igrf/igrf.hpp"
#include "point_panel.hpp"

#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/valtext.h>

namespace panels {
    PointPanel::PointPanel(wxWindow* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
    {
        wxBoxSizer* vszr_point = new wxBoxSizer(wxVERTICAL);
        wxGridSizer* gszr_params = new wxGridSizer(1, 2, 0, 0);
        wxBoxSizer* vszr_coords = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* hszr_lat = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_lat = new wxStaticText(this, wxID_ANY, "Latitude", wxDefaultPosition, wxSize(65, -1), 0);
        sttxt_lat->SetToolTip("Latitude WGS84 in decimal degrees [-90, 90]");
        hszr_lat->Add(sttxt_lat, 0, wxALIGN_CENTER_VERTICAL, 5);
        txtctrl_lat = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
            wxTextValidator(wxFILTER_NUMERIC));
        hszr_lat->Add(txtctrl_lat, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        hszr_lat->Add(new wxStaticText(this, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
            wxDefaultPosition, wxSize(30, -1), 0), 0, wxALIGN_CENTER_VERTICAL);
        vszr_coords->Add(hszr_lat, 0, wxEXPAND, 5);

        wxBoxSizer* hszr_lon = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_lon = new wxStaticText(this, wxID_ANY, "Longitude", wxDefaultPosition, wxSize(65, -1), 0);
        sttxt_lon->SetToolTip("Longitued WGS84 in decimal degrees [-180, 180]");
        hszr_lon->Add(sttxt_lon, 0, wxALIGN_CENTER_VERTICAL, 5);
        txtctrl_lon = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
            wxTextValidator(wxFILTER_NUMERIC));
        hszr_lon->Add(txtctrl_lon, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        hszr_lon->Add(new wxStaticText(this, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
            wxDefaultPosition, wxSize(30, -1), 0), 0, wxALIGN_CENTER_VERTICAL);
        vszr_coords->Add(hszr_lon, 0, wxEXPAND | wxTOP, 5);

        wxBoxSizer* hszr_alt = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* sttxt_alt = new wxStaticText(this, wxID_ANY, "Altitude", wxDefaultPosition, wxSize(65, -1), 0);
        sttxt_alt->SetToolTip("Altitude in km AMSL [> -2'300]");
        hszr_alt->Add(sttxt_alt, 0, wxALIGN_CENTER_VERTICAL, 5);
        txtctrl_alt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
            wxTextValidator(wxFILTER_NUMERIC));
        hszr_alt->Add(txtctrl_alt, 3, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        hszr_alt->Add(new wxStaticText(this, wxID_ANY, "km",
            wxDefaultPosition, wxSize(30, -1), 0), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_coords->Add(hszr_alt, 0, wxEXPAND | wxTOP, 5);
        gszr_params->Add(vszr_coords, 1, wxEXPAND | wxRIGHT, 5);

        wxBoxSizer* vszr_dtcalc = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* hszr_date = new wxBoxSizer(wxHORIZONTAL);
        hszr_date->Add(new wxStaticText(this, wxID_ANY, "IGRF date", wxDefaultPosition, wxSize(65, -1), 0),
            0, wxALIGN_CENTER_VERTICAL);
        dtpckr = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize);
        hszr_date->Add(dtpckr, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_dtcalc->Add(hszr_date, 0, wxEXPAND);

        vszr_dtcalc->AddStretchSpacer(1);
        
        wxBoxSizer* hszr_btn = new wxBoxSizer(wxHORIZONTAL);
        hszr_btn->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(65, -1), 0),
            0, wxALIGN_CENTER_VERTICAL, 5);
        btn_calc = new wxButton(this, wxID_ANY, "Calculate", wxDefaultPosition, wxDefaultSize, 0);
        btn_calc->Enable(false);
        hszr_btn->Add(btn_calc, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        vszr_dtcalc->Add(hszr_btn, 0, wxEXPAND);

        gszr_params->Add(vszr_dtcalc, 1, wxEXPAND | wxLEFT, 5);

        vszr_point->Add(gszr_params, 0, wxALL | wxEXPAND, 15);

        wxGridSizer* gszr_results = new wxGridSizer(2, 3, 5, 10);

        auto add_result = [this, gszr_results](const wxString& name, const wxString& unit,
                                                   wxTextCtrl*& result) {
            wxBoxSizer* hszr_result = new wxBoxSizer(wxHORIZONTAL);
            hszr_result->Add(new wxStaticText(this, wxID_ANY, name, wxDefaultPosition, wxSize(10, -1), 0),
                0, wxALIGN_CENTER_VERTICAL);
            result = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                wxTE_READONLY, wxTextValidator(wxFILTER_NUMERIC));
            hszr_result->Add(result, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
            hszr_result->Add(new wxStaticText(this, wxID_ANY, unit, wxDefaultPosition, wxSize(35, -1), 0),
                0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
            gszr_results->Add(hszr_result, 1, wxEXPAND);
        };

        const wxString degrees = wxString("dec ").append(wxString::FromUTF8("\xc2\xb0"));
        add_result(_("X"), _("nT"), txtctrl_res_x);
        add_result(_("Y"), _("nT"), txtctrl_res_y);
        add_result(_("Z"), _("nT"), txtctrl_res_z);
        add_result(_("F"), _("nT"), txtctrl_res_f);
        add_result(_("D"), degrees, txtctrl_res_d);
        add_result(_("I"), degrees, txtctrl_res_i);

        vszr_point->Add(gszr_results, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 15);

        this->SetSizer(vszr_point);
        this->Layout();
        vszr_point->Fit(this);

        Bind(wxEVT_TEXT, &PointPanel::on_lon, this, txtctrl_lon->GetId());
        Bind(wxEVT_TEXT, &PointPanel::on_lat, this, txtctrl_lat->GetId());
        Bind(wxEVT_TEXT, &PointPanel::on_alt, this, txtctrl_alt->GetId());
        Bind(wxEVT_BUTTON, &PointPanel::on_calc, this, btn_calc->GetId());
    }
    
    void PointPanel::on_lon(wxCommandEvent& event)
    {
        btn_calc->Enable(!txtctrl_lon->IsEmpty() &&
                         !txtctrl_lon->IsEmpty() &&
                         !txtctrl_alt->IsEmpty());
    }
    
    void PointPanel::on_lat(wxCommandEvent& event)
    {
        btn_calc->Enable(!txtctrl_lon->IsEmpty() &&
                         !txtctrl_lon->IsEmpty() &&
                         !txtctrl_alt->IsEmpty());
    }
    
    void PointPanel::on_alt(wxCommandEvent& event)
    {
        btn_calc->Enable(!txtctrl_lon->IsEmpty() &&
                         !txtctrl_lon->IsEmpty() &&
                         !txtctrl_alt->IsEmpty());
    }

    void PointPanel::on_calc(wxCommandEvent& event)
    {
        try {
            double lat, lon, alt;
            txtctrl_lat->GetValue().ToDouble(&lat);
            txtctrl_lon->GetValue().ToDouble(&lon);
            txtctrl_alt->GetValue().ToDouble(&alt);

            auto dt = dtpckr->GetValue();
            int year = dt.GetYear();
            unsigned month = dt.GetMonth() + 1; // +1 since GetMonth()->[0, 11]
            unsigned day = dt.GetDay();
            
            auto field = igrf::calc_igrf({lat, lon, alt}, {year, month, day});
            txtctrl_res_x->SetValue(wxString::Format(wxT("%.2f"), field.X));
            txtctrl_res_y->SetValue(wxString::Format(wxT("%.2f"), field.Y));
            txtctrl_res_z->SetValue(wxString::Format(wxT("%.2f"), field.Z));

            double total_f = igrf::get_total(field);
            double decl = igrf::get_decl(field);
            double incl = igrf::get_incl(field);

            txtctrl_res_f->SetValue(wxString::Format(wxT("%.2f"), total_f));
            txtctrl_res_d->SetValue(wxString::Format(wxT("%.1f"), decl));
            txtctrl_res_i->SetValue(wxString::Format(wxT("%.1f"), incl));
            
        } catch(std::exception& e) {
            wxMessageBox(e.what(), "Error", wxICON_EXCLAMATION);
        }
    }

}
