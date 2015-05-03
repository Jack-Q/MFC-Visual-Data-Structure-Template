// ListNodeEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "01-DataStructureTemplete.h"
#include "VisualListNodeEditor.h"
#include "afxdialogex.h"
#include "VisualListNodeBase.h"


// CListNodeEditor �Ի���

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


// CListNodeEditor ��Ϣ�������


void VisualListNodeEditor::OnBnClickedOk() {
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString restlt;
    GetDlgItemTextW(IDC_EDIT, restlt);
    m_node.SetContent(restlt);

    CDialogEx::OnOK();
}


BOOL VisualListNodeEditor::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    SetDlgItemTextW(IDC_EDIT, m_node.GetContent());
    GetDlgItem(IDC_EDIT)->SetActiveWindow();
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}
