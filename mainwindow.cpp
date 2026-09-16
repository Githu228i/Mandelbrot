#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = QImage(size(), QImage::Format_RGB32);
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
    double coefX = (3.0) / size().width();
    double coefY = (2.4) / size().height();
    st.setX(-2 + start.x() * coefX);
    st.setY(-1.2 + start.y() * coefY);
    end.setX(-2 + end.x() * coefX);
    end.setY(-1.2 + end.y() * coefY);
    double coef = (end.x() - st.x()) / size().width();

    for (int x = 0; x < size().width(); x++) {
        double real = st.x() + x * coef;
        for (int y = 0; y < size().height(); y++) {
            double imag = st.y() + y * coef;
            comp z(0, 0);
            int iter = 0;

            for (int i = 0; i < maxIterations; i++) {
                iter++;
                z = power(z) + comp(real, imag);
                if (sqmodul(z) > inf * inf) {
                    break;
                }
            }



            double t = (double)iter / maxIterations;
            QColor color;
            color.setRgbF(t, 0.2, 1.0 - t);
            image.setPixelColor(x, y, color);
        if (iter == maxIterations) image.setPixelColor(x, y, Qt::black);
        }
    }
}


void MainWindow::Scaling(QPointF st, QPointF end) {

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

            double coefX = 3.0 / size().width();
            double coefY = 2.4 / size().height();

            QPointF mathStart(
                -2.0 + selectionStart.x() * coefX,
                -1.2 + selectionStart.y() * coefY
                );

            QPointF mathEnd(
                -2.0 + selectionEnd.x() * coefX,
                -1.2 + selectionEnd.y() * coefY
                );

            qDebug() << "Pixel start:" << selectionStart;
            qDebug() << "Pixel end:" << selectionEnd;

            qDebug() << "Math start:" << mathStart;
            qDebug() << "Math end:" << mathEnd;
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
