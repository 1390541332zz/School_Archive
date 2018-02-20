#include "complex_widget.hpp"

ComplexWidget::ComplexWidget()
  : layout(std::unique_ptr<QGridLayout>(new QGridLayout))
  , real_text(std::unique_ptr<QLineEdit>(new QLineEdit))
  , imag_text(std::unique_ptr<QLineEdit>(new QLineEdit))
  , real_label(std::unique_ptr<QLabel>(new QLabel(tr("Real"))))
  , imag_label(std::unique_ptr<QLabel>(new QLabel(tr("Imaginary"))))
  , mag_label(std::unique_ptr<QLabel>(new QLabel(tr("Magnitude: "))))
  , phase_label(std::unique_ptr<QLabel>(new QLabel(tr("Phase: "))))
{
    
    
    real_text->setValidator(new QDoubleValidator(real_text.get()));
    imag_text->setValidator(new QDoubleValidator(imag_text.get()));
    
    QObject::connect(real_text.get(), &QLineEdit::textChanged, 
                     this, &ComplexWidget::update_real);
    QObject::connect(imag_text.get(), &QLineEdit::textChanged, 
                     this, &ComplexWidget::update_imag);

    layout->addWidget(real_label.get(),   0, 0);
    layout->addWidget(real_text.get(),    0, 1);
    layout->addWidget(imag_label.get(),   0, 2);
    layout->addWidget(imag_text.get(),    0, 3);
    layout->addWidget(mag_label.get(),    1, 0, 1, 2);
    layout->addWidget(phase_label.get(),  1, 2, 1, 2);
    setLayout(layout.get());
}

ComplexWidget::~ComplexWidget() {}

void ComplexWidget::update_real(QString const& str)
{
    real = str.toDouble(); 
    update_vals();
}
void ComplexWidget::update_imag(QString const& str)
{ 
    imag = str.toDouble();
    update_vals();
}

void ComplexWidget::update_vals() 
{
    mag = std::sqrt(std::pow(real, 2) + std::pow(imag, 2));
    if ((real == 0) && (imag == 0)) {
        phase = 0;
    } else {
        phase = std::atan2(imag, real);
    }

    mag_label->setText("Magnitude: " + QString::number(mag,   'f', 2));
    phase_label->setText("Phase: "   + QString::number(phase, 'f', 2));
}

double ComplexWidget::getRealPart() const noexcept
{
    return real;
}

double ComplexWidget::getImaginaryPart() const noexcept
{
    return imag;
}

double ComplexWidget::getMagnitude() const noexcept
{
    return mag;
}

double ComplexWidget::getPhase() const noexcept
{
    return phase;
}
