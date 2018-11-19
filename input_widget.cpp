#include "input_widget.hpp"

InputWidget::InputWidget(QWidget* parent)
  : QPlainTextEdit(parent) 
  , evalKey(new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Return), this))
{
    connect(evalKey, &QShortcut::activated, this, &InputWidget::scriptEvalUpdate);
    setObjectName("input");
}

InputWidget::~InputWidget() {}

void InputWidget::keyPressEvent(QKeyEvent* e)
{
    if ((e->key() == Qt::Key_Return) && (e->modifiers() == Qt::ShiftModifier)) {
       emit scriptEvalUpdate(); 
    } else {
        QPlainTextEdit::keyPressEvent(e);
    }
}
