#ifndef QARCDIAL_H
#define QARCDIAL_H

/**
  * QT Encoder Dial
  *
  * Based in http://thecodeinn.blogspot.com/2015/03/customizing-qdials-in-qt-part-2.html
  * by Peter Goldsborough
  */

#include "RBCustomUI_global.h"
#include <QDial>
#include <QString>
#include <QSharedPointer>

class QColor;
class QRectF;
class QPen;

namespace RBCustomUI
{

class RBCUSTOMUI_EXPORT QArcDial : public QDial
{
    Q_OBJECT
    Q_PROPERTY(QString arcColor READ getArcColor WRITE setArcColor)
    Q_PROPERTY(double arcWidth READ getArcWidth WRITE setArcWidth)

public:
    explicit QArcDial(QWidget* parent = nullptr);
    QArcDial(const QString& text,
             QWidget * parent = nullptr,
             int minimum = 0,
             int maximum = 999);
    ~QArcDial();

    void setArcColor(const QString& color);
    QString getArcColor() const;
    void setStartAngle(double angle);
    double getStartAngle() const;
    void setMaximumAngle(double angle);
    double getMaximumAngle() const;
    void setArcWidth(double px);
    double getArcWidth() const;
    void setText(const QString& text);
    QString getText() const;

private slots:
    void updateValue();

private:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void resizeEvent(QResizeEvent* event) override;

    double m_maximumAngleSpan;
    double m_startAngle;
    double m_arcWidth;
    double m_angleSpan;
    QString m_valueString;
    QString m_text;
    QSharedPointer<QRectF> m_arcRect;
    QSharedPointer<QRectF> m_valueRect;
    QSharedPointer<QRectF> m_textRect;
    QSharedPointer<QColor> m_arcColor;
    QSharedPointer<QPen> m_arcPen;

}; // class QArcDial
}; // namespace RBCustomUI

#endif // QARCDIAL_H
