//
//  Rectangle.h
//  QuadTree
//
//  Created by Sidharth on 05/01/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __QuadTree__Rectangle__
#define __QuadTree__Rectangle__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "ResourcePath.hpp"
#include "qtree_utility.h"
#include <iostream>

//bounds	 : object coordinate space.
//frame  : world coordinate space.
class Rectangle{
public:
    Rectangle(wle::AABB bounds);
    void update(int dt);
    void render(sf::RenderWindow &w);
	//check if the other rectangle hits. If it does, apply conservation of momentum. Swap speed.
	//swap direction if coming from opposite directions.
    void checkHit(Rectangle *r);
    wle::AABB getFrame(){
        sf::FloatRect r = shape_->getGlobalBounds();
        return wle::AABB(CGRectMake(r.left, r.top, r.width, r.height));
    }

private:
    wle::AABB bounds_;
    sf::RectangleShape *shape_;
    sf::Vector2i *direction_;
    sf::Vector2f *speed_;
	//Calculate if the newPos is out of bounds of the screen, move it in.
	//Use this instead of setting shape_->setPosition()
	void setEffectivePosition(sf::Vector2f newPos);
};

sf::Vector2f pointToVec(wle::Point p);
#endif /* defined(__QuadTree__Rectangle__) */
