#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;
    int milliseconds;

    QPoint center;
    int radius;

    void drawClockHand(QPainter *painter, double angle, int length, int width);

private slots:
    void updateClock();
};

#endif // MAINWINDOW_H
