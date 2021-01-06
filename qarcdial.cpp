#include "qarcdial.h"

#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QRectF>
#include <QPen>
#include <QResizeEvent>

using namespace RBCustomUI;

QArcDial::QArcDial(QWidget* parent)
: QDial(parent)
{ }

QArcDial::QArcDial(const QString& text,
                       QWidget* parent,
                       int minimum,
                       int maximum)
: QDial(parent),
  m_text(text),
  m_arcRect(new QRectF),
  m_valueRect(new QRectF),
  m_textRect(new QRectF),
  m_arcColor(new QColor),
  m_arcPen(new QPen)
{
    QDial::setRange(minimum, maximum);
    QDial::setCursor(Qt::PointingHandCursor);

    connect(this, &QDial::valueChanged,
            this, &QArcDial::updateValue);

    setMinimumSize(100,100);
    setMaximumAngle(-360);
    setStartAngle(270);
    updateValue(QDial::value());
}

QArcDial::~QArcDial() = default;

void QArcDial::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // So that we can use the background color
    // Otherwise the background is transparent
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setRenderHint(QPainter::Antialiasing);  // Smooth out the circle
    painter.setBrush(painter.background());         // Use background color

    // Get current pen before resetting so we have
    // access to the color() method which returns the
    // color from the stylesheet
    QPen textPen = painter.pen();

    painter.setPen(QPen(Qt::NoPen));                // No border
    painter.drawEllipse(QDial::rect());             // Draw background circle
    painter.setPen(textPen);
    painter.drawText(*m_textRect, Qt::AlignHCenter | Qt::AlignBottom, m_text);
    painter.drawText(*m_valueRect, Qt::AlignCenter, m_valueString);
    painter.setPen(*m_arcPen);
    painter.drawArc(*m_arcRect, m_startAngle, m_angleSpan);
}

void QArcDial::resizeEvent(QResizeEvent* event)
{
    QDial::setMinimumSize(event->size());
    double width = QDial::width() - (2 * m_arcWidth);
    double height = width / 2;
    *m_textRect = QRectF(m_arcWidth, m_arcWidth, width, height);
    *m_valueRect = QRectF(m_arcWidth, height, width, height);
    *m_arcRect = QRectF(m_arcWidth / 2,
                       m_arcWidth / 2,
                       QDial::width() - m_arcWidth,
                       QDial::height() - m_arcWidth);
}

void QArcDial::updateValue(int value)
{
    //double value = QDial::value();

    // Get ratio between current value and maximum to calculate angle
    double ratio = value / QDial::maximum();
    m_angleSpan = m_maximumAngleSpan * ratio;
    m_valueString = QString::number(value);
}

void QArcDial::setArcWidth(double px)
{
    m_arcWidth = px;
    *m_arcRect = QRectF(m_arcWidth / 2,
                        m_arcWidth / 2,
                        QDial::width() - m_arcWidth,
                        QDial::height() - m_arcWidth);

    m_arcPen->setWidth(m_arcWidth);
}

void QArcDial::setText(const QString& text)
{
    m_text = text;
}

QString QArcDial::getText() const
{
    return m_text;
}

double QArcDial::getArcWidth() const
{
    return m_arcWidth;
}

void QArcDial::setMaximumAngle(double angle)
{
    m_maximumAngleSpan = angle * 16;
}

double QArcDial::getMaximumAngle() const
{
    return m_maximumAngleSpan / 16;
}

void QArcDial::setStartAngle(double angle)
{
    m_startAngle = angle * 16;
}

double QArcDial::getStartAngle() const
{
    return m_startAngle / 16;
}

void QArcDial::setArcColor(const QString& color)
{
    m_arcColor->setNamedColor(color);
    m_arcPen->setColor(*m_arcColor);
}

QString QArcDial::getArcColor() const
{
    return m_arcColor->name();
}
