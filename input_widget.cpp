#include "input_widget.hpp"

InputWidget::InputWidget(QWidget* parent) : QPlainTextEdit(parent) 
{
    setObjectName("input");
}

InputWidget::~InputWidget() {}
