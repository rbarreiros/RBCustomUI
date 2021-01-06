#include "qencoderdial.h"

#include <QPainter>
#include <QColor>
#include <cmath>

using namespace RBCustomUI;

QEncoderDial::QEncoderDial(QWidget *parent,
                           double knobRadius,
                           double knobMargin)
    : QDial(parent),
      m_knobRadius(knobRadius),
      m_knobMargin(knobMargin)
{
    // Default Range
    setRange(0, 100);
}

void QEncoderDial::setKnobRadius(double knobRadius)
{
    m_knobRadius = knobRadius;
}

double QEncoderDial::getKnobRadius() const
{
    return m_knobRadius;
}

void QEncoderDial::setKnobMargin(double knobMargin)
{
    m_knobMargin = knobMargin;
}

double QEncoderDial::getKnobMargin() const
{
    return m_knobMargin;
}

void QEncoderDial::paintEvent(QPaintEvent *)
{
    static const double degree270 = 1.5 * M_PI;
    static const double degree225 = 1.25 * M_PI;

    QPainter painter(this);

    painter.setBackgroundMode(Qt::OpaqueMode);     // So that we can use the background color
    painter.setRenderHint(QPainter::Antialiasing); // Smooth out the circle
    painter.setBrush(painter.background());        // Use background color

    QColor pointColor(painter.pen().color());      // Store color from stylesheet, pen will be overriden

    painter.setPen(QPen(Qt::NoPen));               // No border
    painter.drawEllipse(0, 0, QDial::height(), QDial::height()); // Draw first circle
    painter.setBrush(QBrush(pointColor));          // Reset color to pointColor from stylesheet

    // Get ratio between current value and maximum to calculate angle
    double ratio = static_cast<double>(QDial::value()) / QDial::maximum();

    // The maximum amount of degrees is 270, offset by 225
    double angle = ratio * degree270 - degree225;

    // Radius of background circle
    double r = QDial::height() / 2.0;

    // Add r to have (0,0) in center of dial
    double y = sin(angle) * (r - m_knobRadius - m_knobMargin) + r;
    double x = cos(angle) * (r - m_knobRadius - m_knobMargin) + r;

    // Draw the ellipse
    painter.drawEllipse(QPointF(x,y), m_knobRadius, m_knobRadius);
}
