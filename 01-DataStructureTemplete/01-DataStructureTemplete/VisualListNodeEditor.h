#pragma once
#include "VisualListNodeBase.h"


// CListNodeEditor 对话框

class VisualListNodeEditor : public CDialogEx
{
	DECLARE_DYNAMIC(VisualListNodeEditor)

public:
    VisualListNodeEditor(VisualListNodeBase &node, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VisualListNodeEditor();

// 对话框数据
	enum { IDD = IDD_LIST_NODE_EDIT };

private:
    VisualListNodeBase &m_node;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
