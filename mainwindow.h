#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comp.h"
#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>

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
    QPair<QPointF, QPointF> Scaling(QPointF st, QPointF end);
    const int maxIterations = 100;
    const int inf = 2;
    QPointF start = QPointF(0.0, 0.0), end = QPointF(2000.0, 1600.0);
    QPointF mathStart = QPointF(-2.0, -1.2);
    QPointF mathEnd = QPointF(1.0, 1.2);
    void paintEvent(QPaintEvent *event) override;

    void newMandelbrot(QPointF Start, QPointF End);

    QVector<QPair<QImage, QPair<QPointF, QPointF>>> savings;


    bool selecting = false;
    QPointF selectionStart;
    QPointF selectionEnd;
    void selectRect(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
