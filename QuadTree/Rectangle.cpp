//
//  Rectangle.cpp
//  QuadTree
//
//  Created by Sidharth on 05/01/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Rectangle.h"
#include "Constants.h"

Rectangle::Rectangle(wle::AABB bounds):
shape_(0),
bounds_(bounds){
    shape_ = new sf::RectangleShape(pointToVec(bounds.getSize()));
    shape_->setPosition(pointToVec(bounds.getCenter()));
    shape_->setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));
    direction_ = new sf::Vector2i(rand()%2?-1:1, rand()%2?-1:1);
    speed_ = new sf::Vector2f(rand()/double(RAND_MAX) + 0.1, rand()/double(RAND_MAX) + 0.1);
}

void Rectangle::render(sf::RenderWindow &w){
    w.draw(*shape_);
}

void Rectangle::setEffectivePosition(sf::Vector2f newPos){
	if(newPos.x < 0){
		direction_->x *= -1;
		newPos.x += shape_->getSize().x;
	}else if(newPos.x > SCREEN_WIDTH){
		direction_->x *= -1;
		newPos.x -= shape_->getSize().x;
	}
	
	if(newPos.y < 0){
		direction_->y *= -1;
		newPos.y += shape_->getSize().y;
	}else if(newPos.y > SCREEN_HEIGHT){
		direction_->y *= -1;
		newPos.y -= shape_->getSize().y;
	}
	
	shape_->setPosition(newPos);
}

void Rectangle::update(int dt){
    double newX = shape_->getPosition().x;
    double newY = shape_->getPosition().y;
    newX += direction_->x * speed_->x;
    newY += direction_->y * speed_->y;
	sf::Vector2f newPos(newX, newY);
	setEffectivePosition(newPos);
}
void Rectangle::checkHit(Rectangle *r){
    wle::AABB fr1 = this->getFrame();
    wle::AABB fr2 = r->getFrame();
   // std::cout << fr1 << "\t\t" << fr2 <<std::endl;
    if(fr1.intersects(fr2)){
        std::cout << "HIT" << std::endl;

//        if(diff_x > 0){
//
//        }
        
        //conservation of momentum
        sf::Vector2i tmpDir(*direction_);
        direction_->x = r->direction_->x;   direction_->y = r->direction_->y;
        r->direction_->x = tmpDir.x;        r->direction_->y = tmpDir.y;
        sf::Vector2f tmpSpeed(*speed_);
        speed_->x = r->speed_->x;   speed_->y = r->speed_->y;
        r->speed_->x = tmpSpeed.x;  r->speed_->y = tmpSpeed.y;
        

        double diff_x = fr1.getCenter().getX() - fr2.getCenter().getX();
        double diff_y = fr1.getCenter().getY() - fr2.getCenter().getY();

		sf::Vector2f newPos(shape_->getPosition().x + diff_x/2, shape_->getPosition().y + diff_y/2);
		setEffectivePosition(newPos);
        //shape_->setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));

		sf::Vector2f newPos2(r->shape_->getPosition().x - diff_x/2, r->shape_->getPosition().y - diff_y/2);
		r->setEffectivePosition(newPos2);
        //r->shape_->setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));
    }
}

sf::Vector2f pointToVec(wle::Point p){
    return sf::Vector2f(p.getX(), p.getY());
}
//EOF