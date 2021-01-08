#ifndef QENCODERDIAL_H
#define QENCODERDIAL_H

/**
  * QT Encoder Dial
  *
  * Based in http://thecodeinn.blogspot.com/2015/02/customizing-qdials-in-qt-part-1.html
  * by Peter Goldsborough
  */

#include "RBCustomUI_global.h"
#include <QDial>

namespace RBCustomUI
{

class RBCUSTOMUI_EXPORT QEncoderDial : public QDial
{
    Q_OBJECT
    Q_PROPERTY(double knobRadius READ getKnobRadius WRITE setKnobRadius)
    Q_PROPERTY(double knobMargin READ getKnobMargin WRITE setKnobMargin)

public:
    QEncoderDial(QWidget *parent = nullptr,
                 double knobRadius = 5,
                 double knobMargin = 5);

    void setKnobRadius(double knobRadius);
    double getKnobRadius() const;
    void setKnobMargin(double knobMargin);
    double getKnobMargin() const;

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    double m_knobRadius;
    double m_knobMargin;

}; // class QEncoderDial
}; // namespace RBCustomUI

#endif // QENCODERDIAL_H
