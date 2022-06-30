
// egedemirci_hw6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cegedemirci_hw6Dlg dialog
class Cegedemirci_hw6Dlg : public CDialogEx
{
// Construction
public:
	Cegedemirci_hw6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EGEDEMIRCI_HW6_DIALOG };

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
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit3();
	CEdit operand_1;
	CEdit operand_2;
	int radio_add;
	int radio_or;
	int radio_xor;
	CButton check_shift;
	CListBox list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	int groupedRadioButtons;
	CButton groupedRadioButton;
	CButton groupRadio;
	int groupRadioButtons;
	int groupRadioButton;
	afx_msg void OnBnClickedRadio5();
	CButton isPressedAnd;
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnLbnSelchangeList2();
	CComboBox leftright;
	CEdit bitstoshift;
};
