#include <wx/app.h>

#include "main_frame.hpp"

class App final : public wxApp
{
public:
    bool OnInit() override
    {
        auto* frame = new main_frame(nullptr, wxID_ANY, "IGRF Tool");
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);
