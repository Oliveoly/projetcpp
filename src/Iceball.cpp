#include "Iceball.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Hero.h"

extern std::vector<std::unique_ptr<Element>> elements;

Iceball::Iceball(double x, double y, int dir) : Element(x, y)
{
    collider.setSize(cd::Vector2<float>(30.0, 15.0));
    solid = false;
    texture = TextureManager::getTexture("iceball");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 32, 64, 32));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    switch (dir)
    {
    case 0: //Down
        move_x = 0;
        move_y = speed;
        set_y(y + 27);
        sprite.rotate(90);
        break;
    case 1: //Left
        move_x = -speed;
        move_y = 0;
        sprite.rotate(180);
        set_x(x - 27);
        break;
    case 2: //Right
        move_x = speed;
        move_y = 0;
        set_x(x + 27);
        break;
    case 3: //Up
        move_x = 0;
        move_y = -speed;
        sprite.rotate(-90);
        set_y(y - 27);
        break;
    }


};

void Iceball::update_sprite()
{
    sprite.setPosition(get_x(), get_y());

    anim.x = (anim.x + 1) % 5;
    sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 32, 64, 32));
}

void Iceball::action()
{
    if (lifetimer.getElapsedTime().asSeconds() > 3)
    {
        to_destroy = true;
        return;
    }

    //se d�placer dans la bonne direction
    set_x(get_x() + move_x);
    set_y(get_y() + move_y);

    sprite.setPosition(get_x(), get_y());

    std::vector<std::unique_ptr<Element>>::iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
    {
        Ennemy* ennemy_ptr = dynamic_cast<Ennemy*>(it->get());
        if (ennemy_ptr && collider.intersects(((*it)->get_collider())))
        {
            std::cout << "freeze !" << std::endl;
            //Geler l'ennemi
            ennemy_ptr->freeze();
            to_destroy = true;
        }
    }
    
}

