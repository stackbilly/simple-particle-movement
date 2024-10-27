#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,m_gravity(0, 9.81f)
    ,m_lastUpdate(QDateTime::currentMSecsSinceEpoch())
    ,m_isEmitting(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    setMinimumSize(800, 600);
    setMouseTracking(true);

    //setup update timer
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::update);
    m_timer.start(16); //Approximately 60 FPS
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    //Draw particles
    for(const Particle& particle : m_particles)
    {
        painter.setPen(Qt::NoPen);

        //Create gradient for particle
        QRadialGradient gradient(particle.position(), 10);
        QColor particleColor = particle.color();
        particleColor.setAlphaF(particle.lifespan());
        gradient.setColorAt(0, particleColor);
        particleColor.setAlpha(0);
        gradient.setColorAt(1, particleColor);

        painter.setBrush(gradient);
        painter.drawEllipse(particle.position(), 10, 10);
    }
}


void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isEmitting = true;
        addParticle(event->pos());
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(m_isEmitting){
        addParticle(event->pos());
    }
}


void MainWindow::update()
{
    //Calculate delta time
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    float deltaTime = (currentTime - m_lastUpdate) / 1000.0f;
    m_lastUpdate = currentTime;

    //Update particles
    for(auto it = m_particles.begin(); it != m_particles.end();)
    {
        it->applyForce(m_gravity);
        it->update(deltaTime);

        if(it->isDead())
        {
            it = m_particles.erase(it);
        }else{
            ++it;
        }
    }
    repaint();
}


void MainWindow::addParticle(const QPointF& position)
{
    //Random initial velocity
    float angle = QRandomGenerator::global()->bounded(2.0f * M_PI);
    float speed = QRandomGenerator::global()->bounded(50, 150) * 1.0f;

    QPointF velocity(
        cos(angle) * speed,
        sin(angle) * speed
        );

    m_particles.append(Particle(position, velocity));

    //Limit maximum particles
    if(m_particles.size() > 1000){
        m_particles.removeFirst();
    }
}
