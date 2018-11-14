#include "input_widget.hpp"

InputWidget::InputWidget(QWidget* parent) : QPlainTextEdit(parent) 
{
    setObjectName("Input");
}

InputWidget::~InputWidget() {}
