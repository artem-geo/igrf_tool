#include "main_frame.hpp"

#include <wx/icon.h>
#include <wx/sizer.h>

MainFrame::MainFrame() 
	: wxFrame(nullptr, wxID_ANY, "IGRF Calculator", wxDefaultPosition, wxSize(500,255),
		wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL | ~wxRESIZE_BORDER)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* vszr = new wxBoxSizer(wxVERTICAL);

	ntb = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	pnl_point = new PointPanel(ntb);
	ntb->AddPage(pnl_point, "Point", true);

	pnl_csv = new CsvPanel(ntb);
	ntb->AddPage(pnl_csv, "CSV", false);

	// temporary ////////////////////////////////
	ntb->SetSelection(1);
	/////////////////////////////////////////////

	vszr->Add(ntb, 1, 0, 0);

	this->SetMinSize(this->GetSize());
	this->SetMaxSize(this->GetSize());

	this->SetSizer(vszr);
	this->Layout();

	this->Centre(wxBOTH);
}
