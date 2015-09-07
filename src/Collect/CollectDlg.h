
// CollectDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCollectDlg dialog
class CCollectDlg : public CDialogEx
{
// Construction
public:
	CCollectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COLLECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);

private:
	HWND m_hNextClipboard;
	bool m_bStartCollectFlag;
	CStdioFile File;
public:
	afx_msg void OnDrawClipboard();
	afx_msg void OnDestroy();
	CString m_edit_clip;
	afx_msg void OnBnClickedButtonComment();
	virtual void OnOK();
	CEdit m_control_clip;
	CButton m_button_comment;
	BOOL m_check_Imgunformat;
};
