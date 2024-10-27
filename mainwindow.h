#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QDateTime>
#include <QPainter>
#include "particle.h"

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

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void update();

private:
    void addParticle(const QPointF& position);
    void updateParticles();

    QVector<Particle> m_particles;
    QTimer m_timer;
    QPointF m_gravity;
    qint64 m_lastUpdate;
    bool m_isEmitting;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
