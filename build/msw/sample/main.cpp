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
	multiLayer->type(gpMultiPlotLayer::Type::BAR);
	gpSeries* sb = multiLayer->AddSeriesLayer("S");
	sb->invert(true);
	sb->SetPen((wxPen&)*wxBLACK_PEN);
	sb->SetBrush((wxBrush&)*wxBLUE_BRUSH);

	sb->DataPush(1, 0.684604);
	sb->DataPush(2, 0.940523);
	sb->DataPush(3, 1.34745);
	sb->DataPush(4, 1.49117);
	sb->DataPush(5, 1.18517);
	sb->DataPush(6, 0.784354);
	sb->DataPush(7, 0.371638);
	sb->DataPush(8, 0.0551886);
	sb->DataPush(9, 0.0369086);
	sb->DataPush(10, 0.0285642);

	//VOL
	multiLayer->type(gpMultiPlotLayer::Type::AREA);
	gpSeries* sq = multiLayer->AddSeriesLayer("Q");
	sq->invert(false);
	sq->SetPen((wxPen&)*wxRED_PEN);
	sq->SetBrush((wxBrush&)*wxRED_BRUSH);

	sq->DataPush(1, 8.35);
	sq->DataPush(2, 7.225);
	sq->DataPush(3, 7.2343);
	sq->DataPush(4, 6.1669);
	sq->DataPush(5, 7.0073);
	sq->DataPush(6, 8.4302);
	sq->DataPush(7, 17.849);
	sq->DataPush(8, 15.405);
	sq->DataPush(9, 11.458);
	sq->DataPush(10, 15.144);

	//EVAP
	multiLayer->type(gpMultiPlotLayer::Type::LINE);
	gpSeries* sp = multiLayer->AddSeriesLayer("V");
	sp->invert(false);
	sp->SetPen((wxPen&)*wxYELLOW_PEN);
	sp->SetBrush((wxBrush&)*wxYELLOW_BRUSH);

	sp->DataPush(1, 0.71437);
	sp->DataPush(2, 0.527526);
	sp->DataPush(3, 0.375912);
	sp->DataPush(4, 0.353638);
	sp->DataPush(5, 0.484907);
	sp->DataPush(6, 0.669034);
	sp->DataPush(7, 0.959391);
	sp->DataPush(8, 1.19247);
	sp->DataPush(9, 1.26814);
	sp->DataPush(10, 1.24076);

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
