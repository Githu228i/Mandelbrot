#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = QImage(2000,1600, QImage::Format_RGB32);
    qDebug() << "Window:" << size();
    qDebug() << "Image:" << image.size();
    DrawMandelbrot(start, end);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    QPainter painter(this);

    painter.drawImage(0, 0, image);

    if (selecting)
    {
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(
            QRectF(selectionStart, selectionEnd).normalized()
            );
    }
}

void MainWindow::DrawMandelbrot(QPointF st, QPointF end) {
    double coefX =
        (mathEnd.x() - mathStart.x()) / image.width();

    double coefY =
        (mathEnd.y() - mathStart.y()) / image.height();

    for (int x = 0; x < image.width(); x++)
    {
        double real = mathStart.x() + x * coefX;

        for (int y = 0; y < image.height(); y++)
        {
            double imag = mathStart.y() + y * coefY;

            comp z(0, 0);
            int iter = 0;

            for (int i = 0; i < maxIterations; i++)
            {
                iter++;

                z = power(z) + comp(real, imag);

                if (sqmodul(z) > inf * inf)
                    break;
            }

            double t = (double)iter / maxIterations;

            QColor color;
            color.setRgbF(t, 0.2, 1.0 - t);

            image.setPixelColor(x, y, color);

            if (iter == maxIterations)
                image.setPixelColor(x, y, Qt::black);
        }
    }

    update();
    qDebug() << "mathStart:" << mathStart;
    qDebug() << "mathEnd:" << mathEnd;
}

void MainWindow::newMandelbrot(QPointF Start, QPointF End) {
    QPair<QPointF, QPointF> points = Scaling(Start, End);
    double coefX = (mathEnd.x() - mathStart.x()) / image.width();
    double coefY = (mathEnd.y() - mathStart.y()) / image.height();

    QPointF newMathStart(mathStart.x() + points.first.x() * coefX, mathStart.y() + points.first.y() * coefY);

    QPointF newMathEnd(mathStart.x() + points.second.x() * coefX, mathStart.y() + points.second.y() * coefY);
    savings.push_back(QPair<QImage, QPair<QPointF, QPointF>>(image, QPair<QPointF, QPointF>(mathStart, mathEnd)));
    mathStart = newMathStart;
    mathEnd = newMathEnd;
    DrawMandelbrot(points.first, points.second);
}

QPair<QPointF, QPointF> MainWindow::Scaling(QPointF st, QPointF end) {
    double distx = end.x() - st.x();
    double disty = end.y() - st.y();

    if (distx / 5 == disty / 4) return(QPair<QPointF, QPointF> (st, end));
    if (distx / 5 < disty / 4) {
        double ref = distx / 5;
        double newdisty = ref * 2;
        double midy = st.y() + disty / 2;
        double newy1 = midy - newdisty;
        double newy2 = midy + newdisty;
        return QPair<QPointF, QPointF> (QPointF(st.x(), newy1), QPointF(end.x(), newy2));
    }
    else {
        double ref = disty / 4;
        double newdistx = ref * 2.5;
        double midx = st.x() + distx / 2;
        double newx1 = midx - newdistx;
        double newx2 = midx + newdistx;
        return QPair<QPointF, QPointF> (QPointF(newx1, st.y()), QPointF(newx2, end.y()));
    }
}


void MainWindow::selectRect(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (event->button() == Qt::LeftButton)
        {
            selecting = true;
            selectionStart = event->position();
            selectionEnd = selectionStart;
        }
    }

    if (event->type() == QEvent::MouseMove)
    {
        if (selecting)
        {
            selectionEnd = event->position();
        }
    }

    if (event->type() == QEvent::MouseButtonRelease)
    {
        if (event->button() == Qt::LeftButton)
        {
            selecting = false;
            selectionEnd = event->position();

            newMandelbrot(selectionStart, selectionEnd);
        }
    }

    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    selectRect(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    selectRect(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    selectRect(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (!savings.empty()) {
            qDebug() << "yooo";
            image = savings[savings.size() - 1].first;
            mathStart = savings[savings.size() - 1].second.first;
            mathEnd = savings[savings.size() - 1].second.second;
            savings.pop_back();
            update();
            return;
        }
        qDebug() << "NNOONONONONONO";

    }

    QMainWindow::keyPressEvent(event);
}
