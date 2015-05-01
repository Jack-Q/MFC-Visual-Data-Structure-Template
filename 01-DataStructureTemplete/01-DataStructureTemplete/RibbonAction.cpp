#include "stdafx.h"
#include "01-DataStructureTemplete.h"
#include "RibbonAction.h"

RibbonAction::RibbonAction() {
}


RibbonAction::~RibbonAction() {
}

BEGIN_MESSAGE_MAP(RibbonAction, CWnd)
    ON_COMMAND(ID_LIST_ADD, &RibbonAction::OnListAdd)
END_MESSAGE_MAP()


void RibbonAction::OnListAdd() {
    // TODO:  在此添加命令处理程序代码
}
