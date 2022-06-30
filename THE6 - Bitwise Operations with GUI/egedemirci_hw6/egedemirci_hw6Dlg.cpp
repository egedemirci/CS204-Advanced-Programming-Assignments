
// egedemirci_hw6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "egedemirci_hw6.h"
#include "egedemirci_hw6Dlg.h"
#include "afxdialogex.h"

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


// Cegedemirci_hw6Dlg dialog

 Cegedemirci_hw6Dlg::Cegedemirci_hw6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cegedemirci_hw6Dlg::IDD, pParent)
	, groupRadioButton(0)
 {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void Cegedemirci_hw6Dlg::DoDataExchange(CDataExchange* pDX)
{
	/*variables. */
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, operand_1);
	DDX_Control(pDX, IDC_EDIT1, operand_2);
	DDX_Control(pDX, IDC_CHECK1, check_shift);
	DDX_Control(pDX, IDC_LIST2, list);
	DDX_Radio(pDX, IDC_RADIO5, groupRadioButton);
	DDX_Control(pDX, IDC_COMBO1, leftright);
	DDX_Control(pDX, IDC_EDIT3, bitstoshift);
}

BEGIN_MESSAGE_MAP(Cegedemirci_hw6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &Cegedemirci_hw6Dlg::OnBnClickedCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cegedemirci_hw6Dlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT3, &Cegedemirci_hw6Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &Cegedemirci_hw6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO5, &Cegedemirci_hw6Dlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &Cegedemirci_hw6Dlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &Cegedemirci_hw6Dlg::OnBnClickedRadio7)
	ON_LBN_SELCHANGE(IDC_LIST2, &Cegedemirci_hw6Dlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// Cegedemirci_hw6Dlg message handlers

BOOL Cegedemirci_hw6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	leftright.SetCurSel(0);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cegedemirci_hw6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cegedemirci_hw6Dlg::OnPaint()
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
HCURSOR Cegedemirci_hw6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool isShiftPressed = false;
void Cegedemirci_hw6Dlg::OnBnClickedCheck1()
{
	//check_shift was selected so enable the windows. */
	if (check_shift.GetCheck())
	{
		leftright.EnableWindow(TRUE);
		bitstoshift.EnableWindow(TRUE);
	}
	else
	{
		// "check_shift" was clicked, but now it isn't selected, meaning it was previously selected, so we can disable the advanced list
		leftright.EnableWindow(FALSE);
		bitstoshift.EnableWindow(FALSE);
	}	// TODO: Add your control notification handler code here
}


void Cegedemirci_hw6Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void Cegedemirci_hw6Dlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  Add your control notification handler code here
}

int maxSize = 0; /*This variable controls the length of the result. */
bool isAndPressed = true; /*boolean for and button, it controls the and button, default it's true. */
bool isOrPressed = false;  /*boolean for or button, it controls the or button, default it's false. */
bool isXorPressed = false; /*boolean for xor button, it controls the xor button, default it's false. */
void Cegedemirci_hw6Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	 /*op_1,op_2 takes texts from operand windows, result is for the output of the list, 
	 calculate is real string result of the proess, shift and wheretoshift is for shifting process. */
	CString op_1, op_2, result, calculate,shift,wheretoshift;
	unsigned int firstOperand,secOperand, intResult,shifting; /*these variables will be unsigned int. */
	//get a DC
	CDC *pDC = GetDC();
	CFont *pOldFont = pDC->SelectObject(GetFont());
	//select the listbox font into the dc
	CSize cz;
	bool contin = true;
	operand_1.GetWindowTextW(op_1); /*takes word from first window of the operand 1. */
	operand_2.GetWindowTextW(op_2);  /*takes word from first window of the operand 2. */
	bitstoshift.GetWindowTextW(shift); /*takes word from the shifting window. */
	firstOperand = _tcstoul(op_1,nullptr,10); /*convert word of the window of the operand 1 to unsigned int. */
	secOperand = _tcstoul(op_2,nullptr,10); /*convert word of the window of the operand 2 to unsigned int. */
	shifting = _tcstoul(shift,nullptr,10); /*convert word of the window of the shift to unsigned int. */
	if ((op_1 == "" || op_2 == "")){ /*if both operand are empty, output is error message. */
			result = "At least 1 operand was not entered";
			contin = false; /*don't continue after this part. */
	}
	/*if shift is checked by the user but entered "" as a output, we should pr'nt error message. */
	if (check_shift.GetCheck() == true && shift == "" && contin == true){ 
		result = "Specify how many bits you want to shift";
		contin = false; /*won't continue to operand process. */
	}
	if (check_shift.GetCheck() == true && shift != "" && contin == true){
		 /*we are taking the input from the combobox, this code is taken from the GUI document. */
		leftright.GetWindowTextW(wheretoshift);
		if (wheretoshift == "Left"){
			firstOperand = firstOperand << shifting; /*if wheretoshift is left, shift firstoperand and secondoperand to the left by shifting. */
			secOperand = secOperand << shifting;
		}
		if (wheretoshift == "Right"){ /*same process as above. */
			firstOperand = firstOperand >> shifting;
			secOperand = secOperand >> shifting;
		}
	}
	if (contin==true){ /*if continue is true enter the operand process. */
		if (isAndPressed == true){ 
				intResult = firstOperand & secOperand; /*if and is pressed calculate the intResult. */
				op_1.Format(_T("%u"), firstOperand);  /*convert it to string again for the result part. */
				op_2.Format(_T("%u"), secOperand);  
				calculate.Format(_T("%u"), intResult); /*same process. */
				result = op_1 + " AND " + op_2 + " = " + calculate ; /*output will be this part. */
				isOrPressed = false; isXorPressed = false; /*if and pressed, orPressed and xorpressed will be false. */
		}
		else if (isOrPressed == true){
				intResult = firstOperand | secOperand; /*if or is pressed calculate the intResult. */
				op_1.Format(_T("%u"), firstOperand);  /*convert it to string again for the result part. */
				op_2.Format(_T("%u"), secOperand); 
				calculate.Format(_T("%u"), intResult); /*same process. */
				result = op_1 + " OR " + op_2 +" = " + calculate ; /*output will be this part. */
				isAndPressed = false; isXorPressed = false; /*if or pressed, andPressed and xorpressed will be false. */
		} 
		else if (isXorPressed == true){
				intResult = firstOperand ^ secOperand; /*if or is pressed calculate the intResult. */
				op_1.Format(_T("%u"), firstOperand);   /*convert it to string again for the result part. */
				op_2.Format(_T("%u"), secOperand); 
				calculate.Format(_T("%u"), intResult); /*same process. */
				result = op_1 + " XOR " + op_2 +" = " + calculate ; /*output will be this part. */
				isAndPressed = false; isOrPressed = false; /*if xor pressed, orPressed and Andpressed will be false. */
		}
	}
	list.AddString(result); /*addString to the result. */
	cz = pDC->GetTextExtent(result);// Returns the size of the string to cz object
	if(cz.cx > maxSize){// cz.cx keeps the horizontal length of the string. We compare
		maxSize = cz.cx;} // it with maxSize and update the maxSize if the condition
	list.SetHorizontalExtent(maxSize+4); /*taken from the GUI document. */
}

void Cegedemirci_hw6Dlg::OnBnClickedRadio5() /*when AndPressed, boolean about the and will be true and others will be false. */
{
	isAndPressed = true;
	isOrPressed = false;
	isXorPressed = false;
}


void Cegedemirci_hw6Dlg::OnBnClickedRadio6() /*when OrPressed, boolean about the or will be true and others will be false. */
{
	isOrPressed = true;
	isXorPressed = false;
	isAndPressed = false;
}


void Cegedemirci_hw6Dlg::OnBnClickedRadio7() /*when XorPressed, boolean about the xor will be true and others will be false. */
{
	isOrPressed = false;
	isXorPressed = true;
	isAndPressed = false;
}


void Cegedemirci_hw6Dlg::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}