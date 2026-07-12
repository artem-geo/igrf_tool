///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "main_frame.hpp"

///////////////////////////////////////////////////////////////////////////

main_frame::main_frame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* vszr;
	vszr = new wxBoxSizer( wxVERTICAL );

	ntb = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	pnl_point = new wxPanel( ntb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* vszr_point;
	vszr_point = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* hszr_params;
	hszr_params = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* vszr_coords;
	vszr_coords = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* hszr_long;
	hszr_long = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( pnl_point, wxID_ANY, _("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	hszr_long->Add( m_staticText1, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl1 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl1->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl1->SetMaxLength( 20 );
	}
	#else
	m_textCtrl1->SetMaxLength( 20 );
	#endif
	hszr_long->Add( m_textCtrl1, 3, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );

	m_staticText2 = new wxStaticText( pnl_point, wxID_ANY, _("dec °"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	hszr_long->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_coords->Add( hszr_long, 0, wxEXPAND, 5 );

	wxBoxSizer* hszr_lat;
	hszr_lat = new wxBoxSizer( wxHORIZONTAL );

	m_staticText11 = new wxStaticText( pnl_point, wxID_ANY, _("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	hszr_lat->Add( m_staticText11, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl11 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl11->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl11->SetMaxLength( 20 );
	}
	#else
	m_textCtrl11->SetMaxLength( 20 );
	#endif
	hszr_lat->Add( m_textCtrl11, 3, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );

	m_staticText21 = new wxStaticText( pnl_point, wxID_ANY, _("dec °"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	hszr_lat->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_coords->Add( hszr_lat, 0, wxEXPAND|wxTOP, 5 );

	wxBoxSizer* hszr_alt;
	hszr_alt = new wxBoxSizer( wxHORIZONTAL );

	m_staticText111 = new wxStaticText( pnl_point, wxID_ANY, _("Altitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	hszr_alt->Add( m_staticText111, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl111 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl111->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl111->SetMaxLength( 20 );
	}
	#else
	m_textCtrl111->SetMaxLength( 20 );
	#endif
	hszr_alt->Add( m_textCtrl111, 3, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );

	m_staticText211 = new wxStaticText( pnl_point, wxID_ANY, _("km    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	hszr_alt->Add( m_staticText211, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_coords->Add( hszr_alt, 0, wxEXPAND|wxTOP, 5 );

	wxBoxSizer* hszr_calc;
	hszr_calc = new wxBoxSizer( wxVERTICAL );


	hszr_calc->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* hszr3;
	hszr3 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText8 = new wxStaticText( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	hszr3->Add( m_staticText8, 1, 0, 5 );

	m_button1 = new wxButton( pnl_point, wxID_ANY, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	hszr3->Add( m_button1, 3, wxEXPAND|wxLEFT, 5 );

	m_staticText7 = new wxStaticText( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	hszr3->Add( m_staticText7, 0, wxLEFT, 5 );


	hszr_calc->Add( hszr3, 1, wxEXPAND, 5 );


	vszr_coords->Add( hszr_calc, 1, wxEXPAND, 5 );


	hszr_params->Add( vszr_coords, 1, wxEXPAND|wxLEFT|wxRIGHT, 10 );

	clndr = new wxCalendarCtrl( pnl_point, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( -1,-1 ), wxCAL_MONDAY_FIRST|wxCAL_SHOW_HOLIDAYS );
	hszr_params->Add( clndr, 1, wxEXPAND|wxRIGHT, 10 );


	vszr_point->Add( hszr_params, 0, wxBOTTOM|wxEXPAND|wxTOP, 10 );

	wxBoxSizer* hszr_results;
	hszr_results = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* vszr_results1;
	vszr_results1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* hszr_x;
	hszr_x = new wxBoxSizer( wxHORIZONTAL );

	m_staticText12 = new wxStaticText( pnl_point, wxID_ANY, _("X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	hszr_x->Add( m_staticText12, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl12 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl12->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl12->SetMaxLength( 20 );
	}
	#else
	m_textCtrl12->SetMaxLength( 20 );
	#endif
	hszr_x->Add( m_textCtrl12, 4, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText22 = new wxStaticText( pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_staticText22->Wrap( -1 );
	hszr_x->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_results1->Add( hszr_x, 1, wxEXPAND, 5 );

	wxBoxSizer* hszr_y;
	hszr_y = new wxBoxSizer( wxHORIZONTAL );

	m_staticText121 = new wxStaticText( pnl_point, wxID_ANY, _("Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText121->Wrap( -1 );
	hszr_y->Add( m_staticText121, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl121 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl121->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl121->SetMaxLength( 20 );
	}
	#else
	m_textCtrl121->SetMaxLength( 20 );
	#endif
	hszr_y->Add( m_textCtrl121, 4, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText221 = new wxStaticText( pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_staticText221->Wrap( -1 );
	hszr_y->Add( m_staticText221, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_results1->Add( hszr_y, 1, wxEXPAND|wxTOP, 5 );

	wxBoxSizer* hszr_z;
	hszr_z = new wxBoxSizer( wxHORIZONTAL );

	m_staticText122 = new wxStaticText( pnl_point, wxID_ANY, _("Z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText122->Wrap( -1 );
	hszr_z->Add( m_staticText122, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl122 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl122->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl122->SetMaxLength( 20 );
	}
	#else
	m_textCtrl122->SetMaxLength( 20 );
	#endif
	hszr_z->Add( m_textCtrl122, 4, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText222 = new wxStaticText( pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_staticText222->Wrap( -1 );
	hszr_z->Add( m_staticText222, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_results1->Add( hszr_z, 1, wxEXPAND|wxTOP, 5 );


	hszr_results->Add( vszr_results1, 1, wxEXPAND|wxRIGHT, 5 );

	wxBoxSizer* vszr_results2;
	vszr_results2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* hszr_f;
	hszr_f = new wxBoxSizer( wxHORIZONTAL );

	m_staticText123 = new wxStaticText( pnl_point, wxID_ANY, _("F"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText123->Wrap( -1 );
	hszr_f->Add( m_staticText123, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl123 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl123->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl123->SetMaxLength( 20 );
	}
	#else
	m_textCtrl123->SetMaxLength( 20 );
	#endif
	hszr_f->Add( m_textCtrl123, 4, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText223 = new wxStaticText( pnl_point, wxID_ANY, _("nT"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_staticText223->Wrap( -1 );
	hszr_f->Add( m_staticText223, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_results2->Add( hszr_f, 1, wxEXPAND, 5 );

	wxBoxSizer* hszr_d;
	hszr_d = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1211 = new wxStaticText( pnl_point, wxID_ANY, _("D"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1211->Wrap( -1 );
	hszr_d->Add( m_staticText1211, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl1211 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl1211->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl1211->SetMaxLength( 20 );
	}
	#else
	m_textCtrl1211->SetMaxLength( 20 );
	#endif
	hszr_d->Add( m_textCtrl1211, 4, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText2211 = new wxStaticText( pnl_point, wxID_ANY, _("dec °"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_staticText2211->Wrap( -1 );
	hszr_d->Add( m_staticText2211, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_results2->Add( hszr_d, 1, wxEXPAND|wxTOP, 5 );

	wxBoxSizer* hszr_i;
	hszr_i = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1221 = new wxStaticText( pnl_point, wxID_ANY, _("I"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1221->Wrap( -1 );
	hszr_i->Add( m_staticText1221, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl1221 = new wxTextCtrl( pnl_point, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textCtrl1221->HasFlag( wxTE_MULTILINE ) )
	{
	m_textCtrl1221->SetMaxLength( 20 );
	}
	#else
	m_textCtrl1221->SetMaxLength( 20 );
	#endif
	hszr_i->Add( m_textCtrl1221, 4, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText2221 = new wxStaticText( pnl_point, wxID_ANY, _("dec °"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_staticText2221->Wrap( -1 );
	hszr_i->Add( m_staticText2221, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	vszr_results2->Add( hszr_i, 1, wxEXPAND|wxTOP, 5 );


	hszr_results->Add( vszr_results2, 1, wxEXPAND|wxLEFT, 5 );


	hszr_results->Add( 0, 0, 1, wxEXPAND, 5 );


	vszr_point->Add( hszr_results, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 10 );


	pnl_point->SetSizer( vszr_point );
	pnl_point->Layout();
	vszr_point->Fit( pnl_point );
	ntb->AddPage( pnl_point, _("Point"), true );
	pnl_file = new wxPanel( ntb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	ntb->AddPage( pnl_file, _("File"), false );

	vszr->Add( ntb, 1, 0, 0 );


	this->SetSizer( vszr );
	this->Layout();

	this->Centre( wxBOTH );
}

main_frame::~main_frame()
{
}
