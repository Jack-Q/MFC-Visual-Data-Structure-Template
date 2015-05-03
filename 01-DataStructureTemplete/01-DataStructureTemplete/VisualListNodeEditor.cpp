// ListNodeEditor.cpp : 实现文件
//

#include "stdafx.h"
#include "01-DataStructureTemplete.h"
#include "VisualListNodeEditor.h"
#include "afxdialogex.h"
#include "VisualListNodeBase.h"


// CListNodeEditor 对话框

IMPLEMENT_DYNAMIC(VisualListNodeEditor, CDialogEx)

VisualListNodeEditor::VisualListNodeEditor(VisualListNodeBase &node, CWnd* pParent /*= NULL*/)
    : m_node(node) ,CDialogEx(VisualListNodeEditor::IDD, pParent) {

}

VisualListNodeEditor::~VisualListNodeEditor()
{
}

void VisualListNodeEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VisualListNodeEditor, CDialogEx)
    ON_BN_CLICKED(IDOK, &VisualListNodeEditor::OnBnClickedOk)
END_MESSAGE_MAP()


// CListNodeEditor 消息处理程序


void VisualListNodeEditor::OnBnClickedOk() {
    // TODO:  在此添加控件通知处理程序代码
    CString restlt;
    GetDlgItemTextW(IDC_EDIT, restlt);
    m_node.SetContent(restlt);

    CDialogEx::OnOK();
}


BOOL VisualListNodeEditor::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    SetDlgItemTextW(IDC_EDIT, m_node.GetContent());
    GetDlgItem(IDC_EDIT)->SetActiveWindow();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
