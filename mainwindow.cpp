#include "mainwindow.h"
#include <QPainter>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Clock");
    setFixedSize(400, 400);

    center = QPoint(width() / 2, height() / 2);
    radius = qMin(width(), height()) / 2 - 20;

    milliseconds = QTime::currentTime().msec();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
    timer->start(40);
}

MainWindow::~MainWindow()
{
    delete timer;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    // рисую циферблат часов
    painter.setBrush(QColor(200, 200, 200));
    painter.drawEllipse(center, radius, radius);

    // рисую градационные шкалы минут
        painter.setPen(QColor(100, 100, 100));
        for (int i = 0; i < 60; i++) {
            double angle = i * 6.0;
            QPoint outerPoint(center.x() + (radius - 5) * cos(angle * M_PI / 180),
                               center.y() + (radius - 5) * sin(angle * M_PI / 180));
            QPoint innerPoint(center.x() + (radius - 15) * cos(angle * M_PI / 180),
                               center.y() + (radius - 15) * sin(angle * M_PI / 180));
            painter.drawLine(outerPoint, innerPoint);
        }

        // рисую цыфры
        painter.setPen(Qt::black);
        QFont font;
        font.setPointSize(radius / 17);
        painter.setFont(font);
        for (int i = 1; i <= 12; ++i) {
            QString digit = QString::number(i);
            double angle = (i - 3) * 30.0;
            QPoint digitPos(center.x() + (radius - 30) * cos(angle * M_PI / 180) - painter.fontMetrics().horizontalAdvance(digit) / 2,
                            center.y() + (radius - 30) * sin(angle * M_PI / 180) + painter.fontMetrics().height() / 4);

            painter.drawText(digitPos, digit);
        }

    // рисую стрелки часов
    QTime time = QTime::currentTime();
    double hourAngle = 30.0 * ((time.hour() + time.minute() / 60.0));
    double minuteAngle = 6.0 * time.minute()+ 0.1 * (time.second() + 0.001 * milliseconds);
    double secondAngle = 6.0 * time.second() + 0.006 * milliseconds;

    drawClockHand(&painter, hourAngle, radius / 2, 8);
    drawClockHand(&painter, minuteAngle, radius * 2 / 3, 6);
    drawClockHand(&painter, secondAngle, radius * 4 / 5, 2);

    // рисую центральную точку
    painter.setBrush(Qt::black);
    painter.drawEllipse(center, 5, 5);
}

void MainWindow::drawClockHand(QPainter *painter, double angle, int length, int width)
{
    painter->save();
    painter->translate(center);
    painter->rotate(angle);
    painter->setBrush(Qt::black);
    painter->drawRect(-width / 2, -length, width, length);
    painter->restore();
}

void MainWindow::updateClock()
{
    milliseconds = QTime::currentTime().msec();
    update();
}
