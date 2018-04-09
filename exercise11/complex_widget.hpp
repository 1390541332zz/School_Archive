#ifndef COMPLEX_WIDGET_H
#define COMPLEX_WIDGET_H

#include <cmath>
#include <memory>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDoubleValidator>

class ComplexWidget : public QWidget 
{
    Q_OBJECT

private:
    double real  = 0;
    double imag  = 0;
    double mag   = 0;
    double phase = 0;

    std::unique_ptr<QGridLayout> layout;

    std::unique_ptr<QLineEdit> real_text;
    std::unique_ptr<QLineEdit> imag_text;
    
    std::unique_ptr<QLabel> real_label;
    std::unique_ptr<QLabel> imag_label;  
    std::unique_ptr<QLabel> mag_label;
    std::unique_ptr<QLabel> phase_label;    

    void update_vals();
public:
    ComplexWidget();
    ~ComplexWidget();

    double getRealPart() const noexcept;
    double getImaginaryPart() const noexcept;
    double getMagnitude() const noexcept;
    double getPhase() const noexcept;

public slots:
    void update_real(QString const& str);
    void update_imag(QString const& str);
};

#endif
