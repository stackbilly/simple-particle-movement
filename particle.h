#ifndef PARTICLE_H
#define PARTICLE_H

#include <QPoint>
#include <QColor>

class Particle
{
public:
    Particle(const QPointF& pos = QPointF(0, 0), const QPointF& vel = QPointF(0, 0));

    void update(float deltaTime);
    void applyForce(const QPointF& force);

    QPointF position() const { return m_position; }
    QPointF velocity() const { return m_velocity; }
    float lifespan() const { return m_lifespan; }
    QColor color() const { return m_color; }
    bool isDead() const { return m_lifespan <= 0; }

private:
    QPointF m_position;
    QPointF m_velocity;
    QPointF m_acceleration;
    float m_lifespan;
    QColor m_color;
};

#endif // PARTICLE_H
