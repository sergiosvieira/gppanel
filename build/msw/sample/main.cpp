// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//gpPanel widget
#include <gpPanel.h>
#include <gpLineLayer.h>
#include <gpMultiplotLayer.h>

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
private:
    void gpTest(wxWindow* parentWindow);
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);

void MyApp::gpTest(wxWindow* parentWindow)
{
    // A panel is a container for one or more charts
    gpPanel* graphPanel = new gpPanel( parentWindow, wxNewId(), wxDefaultPosition,wxSize(240,336) );
	gpMultiPlotLayer* multiLayer = new gpMultiPlotLayer(_("Bar Chart Layer"), _("sample number"), _("y"));
	//multiLayer->invertYScale(true);


	//prec datas
	multiLayer->type(gpMultiPlotLayer::Type::LINE);
	gpSeries* sb = multiLayer->AddSeriesLayer("S");
	sb->invert(false);
	sb->SetPen((wxPen&)*wxBLUE_PEN);
	sb->SetBrush((wxBrush&)*wxBLUE_BRUSH);

	sb->DataPush(0, 0.0);
	sb->DataPush(0.980, 5.660);
	sb->DataPush(5.540, 47.260);
	sb->DataPush(21.340, 277.390);

	//VOL
	multiLayer->type(gpMultiPlotLayer::Type::POINT);
	gpSeries* sq = multiLayer->AddSeriesLayer("Q");
	sq->invert(false);
	sq->SetPen((wxPen&)*wxRED_PEN);
	sq->SetBrush((wxBrush&)*wxRED_BRUSH);

	sq->DataPush(0, 0.0);
	sq->DataPush(0.980, 5.660);
	sq->DataPush(5.540, 47.260);
	sq->DataPush(21.340, 277.390);

	//EVAP
	multiLayer->type(gpMultiPlotLayer::Type::LINE);
	gpSeries* sp = multiLayer->AddSeriesLayer("V");
	sp->invert(true);
	sp->SetPen((wxPen&)*wxYELLOW_PEN);
	sp->SetBrush((wxBrush&)*wxYELLOW_BRUSH);

	/*sp->DataPush(1, 0.71437);
	sp->DataPush(2, 0.527526);
	sp->DataPush(3, 0.375912);
	sp->DataPush(4, 0.353638);
	sp->DataPush(5, 0.484907);
	sp->DataPush(6, 0.669034);
	sp->DataPush(7, 0.959391);
	sp->DataPush(8, 1.19247);
	sp->DataPush(9, 1.26814);
	sp->DataPush(10, 1.24076);*/

	graphPanel->AddLayer(multiLayer);
	multiLayer->RefreshChart();
	graphPanel->Fit(multiLayer);
}

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame( "wxWidgets Demo", wxPoint(50, 50), wxSize(850, 640) );
    gpTest(frame);
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "gpPanel sample app" );
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' gpPanel sample",
        "About gpPanel Sample", wxOK | wxICON_INFORMATION );
}
