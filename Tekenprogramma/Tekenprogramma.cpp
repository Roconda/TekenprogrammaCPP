
// Tekenprogramma.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Tekenprogramma.h"
#include "MainFrm.h"
#include "Settings.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTekenprogrammaApp

BEGIN_MESSAGE_MAP(CTekenprogrammaApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTekenprogrammaApp::OnAppAbout)
	ON_COMMAND(ID_SHAPES_RECTANGLE, &CTekenprogrammaApp::OnShapesRectangle)
	ON_COMMAND(ID_SHAPES_CIRCLE, &CTekenprogrammaApp::OnShapesCircle)
	ON_COMMAND(ID_SHAPES_LINE, &CTekenprogrammaApp::OnShapesLine)
	ON_COMMAND(ID_FILE_SAVETOFILE, &CTekenprogrammaApp::OnFileSavetofile)
	ON_COMMAND(ID_FILE_OPENFILE, &CTekenprogrammaApp::OnFileOpenfile)
END_MESSAGE_MAP()


// CTekenprogrammaApp construction

CTekenprogrammaApp::CTekenprogrammaApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Tekenprogramma.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTekenprogrammaApp object

CTekenprogrammaApp theApp;


// CTekenprogrammaApp initialization

BOOL CTekenprogrammaApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);


	// Check circle by default
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_SHAPES_CIRCLE, MF_CHECKED | MF_BYCOMMAND);


	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CTekenprogrammaApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CTekenprogrammaApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CTekenprogrammaApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTekenprogrammaApp message handlers
void CTekenprogrammaApp::OnShapesCircle()
{
	Settings::shapeSelected = 0;

	CMenu *pMenu = AfxGetMainWnd()->GetMenu();

	pMenu->CheckMenuItem(ID_SHAPES_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPES_LINE, MF_UNCHECKED | MF_BYCOMMAND);

	pMenu->CheckMenuItem(ID_SHAPES_CIRCLE, MF_CHECKED | MF_BYCOMMAND);
}

void CTekenprogrammaApp::OnShapesRectangle()
{
	Settings::shapeSelected = 1;

	CMenu *pMenu = AfxGetMainWnd()->GetMenu();

	pMenu->CheckMenuItem(ID_SHAPES_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPES_LINE, MF_UNCHECKED | MF_BYCOMMAND);

	pMenu->CheckMenuItem(ID_SHAPES_RECTANGLE, MF_CHECKED | MF_BYCOMMAND);
}



void CTekenprogrammaApp::OnShapesLine()
{
	Settings::shapeSelected = 2;

	CMenu *pMenu = AfxGetMainWnd()->GetMenu();

	pMenu->CheckMenuItem(ID_SHAPES_CIRCLE, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem(ID_SHAPES_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);

	pMenu->CheckMenuItem(ID_SHAPES_LINE, MF_CHECKED | MF_BYCOMMAND);
}


void CTekenprogrammaApp::OnFileSavetofile()
{
	// legacy
}


void CTekenprogrammaApp::OnFileOpenfile()
{
	// legacy
}
