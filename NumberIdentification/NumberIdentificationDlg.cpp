
// NumberIdentificationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NumberIdentification.h"
#include "NumberIdentificationDlg.h"
#include "afxdialogex.h"
#include"mycore.h"
#include"recognize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNumberIdentificationDlg 对话框



CNumberIdentificationDlg::CNumberIdentificationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMBERIDENTIFICATION_DIALOG, pParent)
	, res(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strFilePath = _T("");
	strFileName = _T("");
}

void CNumberIdentificationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, res);
	DDX_Control(pDX, IDC_IMAGE, m_img);
}

BEGIN_MESSAGE_MAP(CNumberIdentificationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNumberIdentificationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNumberIdentificationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CNumberIdentificationDlg::OnBnClickedButton3)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_32771, &CNumberIdentificationDlg::On32771)
	ON_COMMAND(ID_32772, &CNumberIdentificationDlg::On32772)
END_MESSAGE_MAP()


// CNumberIdentificationDlg 消息处理程序

BOOL CNumberIdentificationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNumberIdentificationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNumberIdentificationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();

		CPaintDC   dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);  //对话框的背景图片  

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNumberIdentificationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNumberIdentificationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//进度条置为零
	//CProgressCtrl  *prgs = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS);
	//prgs->SetPos(0);
	//选择图片
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*||"), this);
	fileDlg.DoModal();
	//获取图片路径和图片名称
	strFilePath = fileDlg.GetPathName();
	strFileName = fileDlg.GetFileName();
	//判断路径不为空
	if (strFilePath == _T(""))
	{
		return;
	}
	CImage image;
	image.Load(strFilePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面
	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象


	int x = image.GetWidth();
	int y = image.GetHeight();
	//Picture Control的ID为IDC_IMAGE
	CWnd* pWnd = GetDlgItem(IDC_IMAGE);
	pWnd->GetClientRect(rectControl);


	CDC* pDc = GetDlgItem(IDC_IMAGE)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_IMAGE))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);                //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	pWnd->ReleaseDC(pDc);
}


void CNumberIdentificationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Ptr<SVM> svm = Algorithm::load<SVM>(g_SVM);

	Mat srcImage(500, 500, CV_8UC1, Scalar::all(0)), image;
	namedWindow(WINDOW_NAME);

	for (;;)
	{
		BoxExtractor box;
		srcImage.copyTo(image);
		int key = box.MouseDraw(WINDOW_NAME, image, Scalar::all(255), 5);
		if (key != 13)
			break;

		vector<Mat> arr;
		getSegment(image, arr, image);

		Mat imageDataMat;
		float ans = -1;
		CString str;
		for (int i = 0; i < arr.size(); ++i)
		{
			
			Mat imageDataMat;
			getMixedFeature(arr[i], imageDataMat, Size(28, 28));
			float ans = (float)svm->predict(imageDataMat);
			str.Format(_T("%1.0f"), ans);
			res = res + str;
		}
		imshow(WINDOW_NAME, image);
		UpdateData(false);
		res = _T("");

		key = waitKey(0);
		if (key == 27)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	destroyWindow(WINDOW_NAME);
}
	



void CNumberIdentificationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (strFilePath == _T(""))
	{
		MessageBox(_T("请选择图片！"));
	}
	else
	{
		Mat srcImage;
		USES_CONVERSION;
		srcImage = imread(W2A(strFilePath));
		resize(srcImage, srcImage, Size(1024, 768), 0, 0, INTER_AREA);
		Mat dstImage = srcImage.clone();

		preProcess(srcImage, dstImage);
	
		vector<Mat> arr;
	
		getSegment(dstImage, arr, srcImage);
		namedWindow(WINDOW_NAME);
		//resizeImage(srcImage, Size(800, 600));
		imshow(WINDOW_NAME, srcImage);
		CString str;
		Mat imageDataMat;
		Ptr<SVM> svm = Algorithm::load<SVM>(g_SVM);
		for (int i = 0; i < arr.size(); ++i)
		{
			Mat imageDataMat;
			getMixedFeature(arr[i], imageDataMat, Size(28, 28));
			imageDataMat.convertTo(imageDataMat, CV_32FC1);
			float ans = (float)svm->predict(imageDataMat);
			str.Format(_T("%1.0f"), ans);
			res = res + str;
		}
		UpdateData(false);
		res = _T("");

		int time = waitKey(0);
		if (time == 13)
		{
			destroyWindow(WINDOW_NAME);
		}
	}
	
}




HBRUSH CNumberIdentificationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{
		return m_brush1;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0, 180, 0));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_brush1;

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_brush1;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CNumberIdentificationDlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"操作：1.图片识别：先从文件夹中选择图片，点击识别按钮（需要等待10s左右）2.手写识别：点击手写识别按钮（需要等待10s左右），任意绘画数字，按下回车显示结果，按下Esc退出");
}


void CNumberIdentificationDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"@XQL");
}
