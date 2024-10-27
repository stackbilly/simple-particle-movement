#include "particle.h"
#include <QRandomGenerator>

Particle::Particle(const QPointF& pos, const QPointF& vel)
    : m_position(pos),
    m_velocity(vel),
    m_acceleration(0,0),
    m_lifespan(1.0f)
{
    // Random color initialization
    m_color = QColor::fromHsv(
        QRandomGenerator::global() -> bounded(360), //Hue
        QRandomGenerator::global() -> bounded(128, 256), //Saturation
        QRandomGenerator::global() -> bounded(128, 256) //Value
        );
}

void Particle::update(float deltaTime)
{
    m_velocity += m_acceleration * deltaTime;
    m_position += m_velocity * deltaTime;
    m_acceleration *= 0;
    m_lifespan -= deltaTime * 0.5f;
}

void Particle::applyForce(const QPointF& force)
{
    m_acceleration += force;
}
