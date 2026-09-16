#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comp.h"
#include <QMouseEvent>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage image;
    void DrawMandelbrot(QPointF st, QPointF end);
    void Scaling(QPointF st, QPointF end);
    const int maxIterations = 100;
    const int inf = 2;
    QPointF start = QPointF(0.0, 0.0), end = QPointF(2000.0, 1600.0);
    void paintEvent(QPaintEvent *event) override;


    bool selecting = false;
    QPointF selectionStart;
    QPointF selectionEnd;
    void selectRect(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
