///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "main_frame.hpp"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame() 
	: wxFrame(nullptr, wxID_ANY, "IGRF ", wxDefaultPosition, wxSize(550,360), 
		wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* vszr = new wxBoxSizer(wxVERTICAL);

	ntb = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	pnl_point = new wxPanel(ntb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* vszr_point = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* hszr_params = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* vszr_coords = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* hszr_lon = new wxBoxSizer(wxHORIZONTAL);

	
	hszr_lon->Add(new wxStaticText(pnl_point, wxID_ANY, "Longitude", wxDefaultPosition, wxDefaultSize, 0), 
		1, wxALIGN_CENTER_VERTICAL, 5);
	txtctrl_lon = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	hszr_lon->Add(txtctrl_lon, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
	hszr_lon->Add(new wxStaticText(pnl_point, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")), 
		wxDefaultPosition, wxDefaultSize, 0), 0, wxALIGN_CENTER_VERTICAL);
	vszr_coords->Add(hszr_lon, 0, wxEXPAND, 5);

	wxBoxSizer* hszr_lat = new wxBoxSizer( wxHORIZONTAL );
	hszr_lat->Add(new wxStaticText(pnl_point, wxID_ANY, "Latitude", wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);
	txtctrl_lat = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_lat->Add(txtctrl_lat, 3, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
	hszr_lat->Add(new wxStaticText(pnl_point, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")), 
		wxDefaultPosition, wxDefaultSize, 0), 0, wxALIGN_CENTER_VERTICAL);
	vszr_coords->Add(hszr_lat, 0, wxEXPAND | wxTOP, 5);

	wxBoxSizer* hszr_alt = new wxBoxSizer(wxHORIZONTAL);
	hszr_alt->Add(new wxStaticText(pnl_point, wxID_ANY, "Altitude", wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);
	txtctrl_alt = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_alt->Add(txtctrl_alt, 3, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	hszr_alt->Add(new wxStaticText(pnl_point, wxID_ANY, wxString("km    "), 
		wxDefaultPosition, wxDefaultSize, 0), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	vszr_coords->Add(hszr_alt, 0, wxEXPAND | wxTOP, 5);

	wxBoxSizer* vszr_calc = new wxBoxSizer(wxVERTICAL);
	vszr_calc->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* hszr_calc = new wxBoxSizer(wxHORIZONTAL);
	hszr_calc->Add(new wxStaticText(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0),
		1, 0, 5);
	btn_calc = new wxButton(pnl_point, wxID_ANY, "Calculate", wxDefaultPosition, wxDefaultSize, 0);
	hszr_calc->Add(btn_calc, 3, wxEXPAND | wxLEFT, 5);
	hszr_calc->Add(new wxStaticText( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0),
		0, wxLEFT, 5);
	vszr_calc->Add(hszr_calc, 1, wxEXPAND, 5);
	vszr_coords->Add(vszr_calc, 1, wxEXPAND, 5);
	hszr_params->Add(vszr_coords, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);

	clndr = new wxCalendarCtrl(pnl_point, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( -1,-1 ), 
		wxCAL_MONDAY_FIRST | wxCAL_SHOW_HOLIDAYS);
	hszr_params->Add(clndr, 1, wxEXPAND | wxRIGHT, 10);

	vszr_point->Add(hszr_params, 0, wxBOTTOM | wxEXPAND | wxTOP, 10);

	wxBoxSizer* hszr_results = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* vszr_results1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* hszr_x = new wxBoxSizer(wxHORIZONTAL);
	hszr_x->Add(new wxStaticText(pnl_point, wxID_ANY, _("X"), wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);

	txtctrl_res_x = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_x->Add(txtctrl_res_x, 4, wxALIGN_CENTER_VERTICAL, 5);
	hszr_x->Add(new wxStaticText(pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0),
		0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	vszr_results1->Add( hszr_x, 1, wxEXPAND, 5);

	wxBoxSizer* hszr_y = new wxBoxSizer(wxHORIZONTAL);
	hszr_y->Add(new wxStaticText(pnl_point, wxID_ANY, _("Y"), wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);
	txtctrl_res_y = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_y->Add(txtctrl_res_y, 4, wxALIGN_CENTER_VERTICAL, 5);
	hszr_y->Add(new wxStaticText(pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0),
		0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	vszr_results1->Add(hszr_y, 1, wxEXPAND | wxTOP, 5);

	wxBoxSizer* hszr_z = new wxBoxSizer( wxHORIZONTAL );
	hszr_z->Add(new wxStaticText(pnl_point, wxID_ANY, _("Z"), wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);
	txtctrl_res_z = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_z->Add(txtctrl_res_z, 4, wxALIGN_CENTER_VERTICAL, 5);
	hszr_z->Add(new wxStaticText(pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize(35, -1), 0),
		0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	vszr_results1->Add(hszr_z, 1, wxEXPAND | wxTOP, 5);
	hszr_results->Add(vszr_results1, 1, wxEXPAND | wxRIGHT, 5);

	wxBoxSizer* vszr_results2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* hszr_f = new wxBoxSizer(wxHORIZONTAL);
	hszr_f->Add(new wxStaticText(pnl_point, wxID_ANY, _("F"), wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);

	txtctrl_res_f = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_f->Add(txtctrl_res_f, 4, wxALIGN_CENTER_VERTICAL, 5);
	hszr_f->Add(new wxStaticText(pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0),
		0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	vszr_results2->Add(hszr_f, 1, wxEXPAND, 5);

	wxBoxSizer* hszr_d = new wxBoxSizer(wxHORIZONTAL);
	hszr_d->Add( new wxStaticText(pnl_point, wxID_ANY, _("D"), wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);
	txtctrl_res_d = new wxTextCtrl(pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	hszr_d->Add(txtctrl_res_d, 4, wxALIGN_CENTER_VERTICAL, 5);
	hszr_d->Add(new wxStaticText(pnl_point, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
		wxDefaultPosition, wxSize( 35,-1 ), 0),
		0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	vszr_results2->Add(hszr_d, 1, wxEXPAND | wxTOP, 5);

	wxBoxSizer* hszr_i = new wxBoxSizer(wxHORIZONTAL);
	hszr_i->Add(new wxStaticText(pnl_point, wxID_ANY, _("I"), wxDefaultPosition, wxDefaultSize, 0),
		1, wxALIGN_CENTER_VERTICAL, 5);

	txtctrl_res_i = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	hszr_i->Add(txtctrl_res_i, 4, wxALIGN_CENTER_VERTICAL, 5);
	hszr_i->Add(new wxStaticText(pnl_point, wxID_ANY, wxString("dec ").append(wxString::FromUTF8("\xc2\xb0")),
		wxDefaultPosition, wxSize( 35,-1 ), 0),
		0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	vszr_results2->Add(hszr_i, 1, wxEXPAND | wxTOP, 5);

	hszr_results->Add(vszr_results2, 1, wxEXPAND | wxLEFT, 5);
	hszr_results->Add(0, 0, 1, wxEXPAND, 5);

	vszr_point->Add(hszr_results, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 10);

	pnl_point->SetSizer(vszr_point);
	pnl_point->Layout();
	vszr_point->Fit(pnl_point);
	ntb->AddPage(pnl_point, _("Point"), true);


	pnl_file = new wxPanel(ntb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	ntb->AddPage( pnl_file, _("File"), false );

	vszr->Add( ntb, 1, 0, 0 );


	this->SetSizer( vszr );
	this->Layout();

	this->Centre( wxBOTH );
}
