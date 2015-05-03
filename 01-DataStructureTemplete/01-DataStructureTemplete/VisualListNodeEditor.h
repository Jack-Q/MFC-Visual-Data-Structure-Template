#pragma once
#include "VisualListNodeBase.h"


// CListNodeEditor �Ի���

class VisualListNodeEditor : public CDialogEx
{
	DECLARE_DYNAMIC(VisualListNodeEditor)

public:
    VisualListNodeEditor(VisualListNodeBase &node, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~VisualListNodeEditor();

// �Ի�������
	enum { IDD = IDD_LIST_NODE_EDIT };

private:
    VisualListNodeBase &m_node;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
