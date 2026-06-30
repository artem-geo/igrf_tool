#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame()
        : wxFrame(nullptr, wxID_ANY, "wxWidgets on Linux", wxDefaultPosition, wxSize(600, 400))
    {
        auto* panel = new wxPanel(this);
        auto* text = new wxStaticText(panel, wxID_ANY, "Hello from wxWidgets");

        auto* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(text, 0, wxALL, 20);

        panel->SetSizer(sizer);
    }
};

class App : public wxApp {
public:
    bool OnInit() override
    {
        auto* frame = new MainFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);