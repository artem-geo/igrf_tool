#pragma once

#include "csv_panel.hpp"
#include "point_panel.hpp"

#include <wx/notebook.h>
#include <wx/frame.h>

using namespace panels;
class MainFrame : public wxFrame
{
	private:

	protected:
		wxNotebook* ntb;
		PointPanel* pnl_point;
		CsvPanel* pnl_csv;

	public:
		MainFrame();
		~MainFrame() = default;

};
