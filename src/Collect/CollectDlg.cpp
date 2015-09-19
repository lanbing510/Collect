
// CollectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Collect.h"
#include "CollectDlg.h"
#include "afxdialogex.h"

#include "Utilties.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCollectDlg dialog



CCollectDlg::CCollectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCollectDlg::IDD, pParent)
	, m_edit_clip(_T(""))
	, m_check_Imgunformat(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hNextClipboard = NULL;
}

void CCollectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CLIP, m_edit_clip);
	DDX_Control(pDX, IDC_EDIT_CLIP, m_control_clip);
	DDX_Control(pDX, IDC_BUTTON_COMMENT, m_button_comment);
	DDX_Check(pDX, IDC_CHECK_IMGUNFORMAT, m_check_Imgunformat);
}

BEGIN_MESSAGE_MAP(CCollectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CCollectDlg::OnBnClickedButtonStart)
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_COMMENT, &CCollectDlg::OnBnClickedButtonComment)
END_MESSAGE_MAP()


// CCollectDlg message handlers

BOOL CCollectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_hNextClipboard = ::SetClipboardViewer(GetSafeHwnd());
	m_bStartCollectFlag = false;
	m_edit_clip = "";

	m_control_clip.SetReadOnly(TRUE);
	m_button_comment.EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_IMGUNFORMAT)->EnableWindow(FALSE);

	setlocale(LC_ALL, "chs");


	//GDI+ 
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCollectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCollectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCollectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCollectDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here

	CString str;
	if (GetDlgItemText(IDC_BUTTON_START, str), str == L"Start Collect")
	{
		File.Open(_T("Collect.html"), CFile::modeNoTruncate | CFile::modeWrite | CFile::modeCreate);
		ULONGLONG dwLength = File.GetLength();
		if (dwLength == 0)
		{
			CString htmlStr = L"<html>\
				\n <head>\
				\n <title>Collect<\/title>\
				\n <basefont face = \"Î¢ÈíÑÅºÚ\" size = \"2\" / >\
				\n <meta http-equiv = \"Content-Type\" content = \"text/html;charset=gb2312\" \/ >\
				\n <meta name = \"exporter-version\" content = \"Evernote Windows/276127; Windows/6.3.9600;\" \/ >\
				\n <style>\
				\n body, td{\
				\n font-family: Î¢ÈíÑÅºÚ;\
				\n font-size: 10pt;}\
				\n <\/style>\
				\n <\/head>\n\
				\n <body>\n"; 
				File.WriteString(htmlStr);
		}
		else
		{
			File.Seek(-LONGLONG(strlen("\n <\/body>\n <\/html>")), CFile::end);
		}


		CString folderPath = L"D:/ImgsCollected/";
		if (!PathIsDirectory(folderPath))
		{
			::CreateDirectory(folderPath, NULL);
		}

		m_bStartCollectFlag = true;
		m_control_clip.SetReadOnly(FALSE);
		m_button_comment.EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_IMGUNFORMAT)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BUTTON_START, L"Stop  Collect");
	}
	else
	{
		File.WriteString(L"\n <\/body>\n<\/html>");
		File.Flush();
		File.Close();
		m_bStartCollectFlag = false;
		m_control_clip.SetReadOnly(TRUE);
		m_button_comment.EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_IMGUNFORMAT)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BUTTON_START, L"Start Collect");

		m_check_Imgunformat = FALSE;
		UpdateData(FALSE);
	}

}



void CCollectDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter)
{
	CDialogEx::OnChangeCbChain(hWndRemove, hWndAfter);

	// TODO: Add your message handler code here

	if (m_hNextClipboard == hWndRemove)
	{
		m_hNextClipboard = hWndAfter;
	}
	else if (m_hNextClipboard)
	{
		::SendMessage(m_hNextClipboard, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter);
	}
}


void CCollectDlg::OnDrawClipboard()
{
	CDialogEx::OnDrawClipboard();
	
	// TODO: Add your message handler code here

	HGLOBAL hClipboardData,hBitmap;
	if (m_hNextClipboard)
	{
		::SendMessage(m_hNextClipboard, WM_DRAWCLIPBOARD, 0, 0);
	}


	unsigned int anFormats[] = { CF_TEXT, CF_BITMAP };
	unsigned int nFormat = GetPriorityClipboardFormat(anFormats, sizeof(anFormats));
	

	if (nFormat == CF_TEXT)
	{
		::OpenClipboard(GetSafeHwnd());
		hClipboardData = GetClipboardData(CF_TEXT);
		CString m_strContent = c2w((char*)(GlobalLock(hClipboardData)));
		GlobalUnlock(hClipboardData);

		if (m_bStartCollectFlag && (File.m_hFile != INVALID_HANDLE_VALUE)&&m_strContent!=L"")
		{
			File.WriteString(L" <div> <hr\/> <\/div>\n");
			File.WriteString(L" <div>" + m_strContent + L"<\/div>\n");
			File.Flush();
		}

		::CloseClipboard();

	}
	else if (nFormat == CF_BITMAP)
	{
		HWND hWnd = GetSafeHwnd();
		::OpenClipboard(hWnd);
		hBitmap = GetClipboardData(CF_BITMAP);
		HDC hDC = ::GetDC(hWnd);
		HDC hdcMem = CreateCompatibleDC(hDC);
		SelectObject(hdcMem, hBitmap);
		SetMapMode(hdcMem, GetMapMode(hDC));

		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);


		if (m_bStartCollectFlag&&hBitmap!=NULL)
		{
			//// ´æÎªBMP
			//CString imgNameBmp = c2w(GenerateFileName().c_str());
			//imgNameBmp = L"D:/ImgsCollected/" + imgNameBmp + L".bmp";
			//SaveBitmap(bm, hDC, (HBITMAP)hBitmap, imgNameBmp);

			// ´æÎªJPG
			Gdiplus::Bitmap* m_pBackBmp = ::new Gdiplus::Bitmap((HBITMAP)::GetCurrentObject(hdcMem, OBJ_BITMAP), NULL);
			CString imgNameJpg = c2w(GenerateFileName().c_str());
			imgNameJpg = L"D:/ImgsCollected/" + imgNameJpg + L".jpg";
			SaveJpg(m_pBackBmp, imgNameJpg);


			CString imgWidth = L"\" width=\"%d\"";
			if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_IMGUNFORMAT))
			{
				imgWidth.Format(imgWidth, bm.bmWidth);
			}
			else
			{
				imgWidth.Format(imgWidth, 600);
			}

			File.WriteString(L" <div> <hr\/> <\/div>\n");
			//File.WriteString(L" <div><img src=\"" + imgNameBmp +imgWidth+ L" \/><\/div>\n"); //Á´½ÓÎªbmp
			File.WriteString(L" <div><img src=\"" + imgNameJpg + imgWidth + L" \/><\/div>\n"); //Á´½ÓÎªjpg
			File.Flush();
		}

		::ReleaseDC(hWnd, hDC);
		DeleteDC(hdcMem);

		::CloseClipboard();

	}
	else
	{
		//Add other functions
	}

}





void CCollectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

	ChangeClipboardChain(GetSafeHwnd());
	m_hNextClipboard = NULL;

}


void CCollectDlg::OnBnClickedButtonComment()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	if (m_bStartCollectFlag && (File.m_hFile != INVALID_HANDLE_VALUE))
	{
		File.WriteString(L" <div>" + m_edit_clip + L"<\/div>\n");
		File.Flush();
	}


	m_edit_clip = "";
	UpdateData(FALSE);

}


void CCollectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	OnBnClickedButtonComment();

	//CDialogEx::OnOK();
}


//void CCollectDlg::OnRadioImgunformat()
//{
//	// TODO: Add your command handler code here
//
//}
