#pragma once

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
		// wxPanel* pnl_file;

	public:
		MainFrame();
		~MainFrame() = default;

};

