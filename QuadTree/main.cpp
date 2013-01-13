//
//  Main.cpp
//  QuadTree
//
//  Created by Sidharth on 05/01/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include "Rectangle.h"
#include "Constants.h"
#include "quadtree/qtree.h"
#include <sstream>

class RectangleFactory {
    Rectangle *r_;
public:
    Rectangle *get(wle::Point p = wle::Point(rand()%SCREEN_WIDTH,rand()%SCREEN_HEIGHT) ){
        return new Rectangle(wle::AABB(p,wle::Point(10, 10)));
    }
};

void checkCollisionQuadTree(std::vector<Rectangle *>objs){
    //create
    std::vector<Rectangle *>::iterator it = objs.begin();
    wle::QuadTree *root = new wle::QuadTree(0, (*it)->getFrame());
    while(it != objs.end()){
        root->insert((*it)->getFrame());
        it++;
    }
    
    
    //done
    root->clear();
    delete root;
}

//Do O(n^2) check
void checkCollision(std::vector<Rectangle *> &objs){
    std::vector<Rectangle *>::iterator it = objs.begin();
    while(it != objs.end()){
        for(std::vector<Rectangle *>::iterator it2 = it + 1; it2 != objs.end(); it2++){
            (*it)->checkHit(*it2);
        }
        it++;
    }
}


int main (int argc, const char * argv[]){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window");
    
//    // Load a sprite to display
//    sf::Texture texture;
//    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg"))
//    	return EXIT_FAILURE;
//    sf::Sprite sprite(texture);
//
//    // Create a graphical text to display
//    sf::Font font;
//    if (!font.loadFromFile(resourcePath() + "sansation.ttf"))
//    	return EXIT_FAILURE;
//    sf::Text text("Hello SFML", font, 50);
//    text.setColor(sf::Color::Black);
//
//    // Load a music to play
//    sf::Music music;
//    if (!music.openFromFile(resourcePath() + "nice_music.ogg"))
//    	return EXIT_FAILURE;
//
//    // Play the music
//    music.play();

    //    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf"))
        return EXIT_FAILURE;
    int objects = 0;
    sf::Text text("Objects: ", font, 50);
    text.setPosition(0, SCREEN_HEIGHT/2);
    text.setColor(sf::Color::Green);

    srand(time(0));
    sf::Clock c;
    std::vector<Rectangle *>entities_;
    RectangleFactory rf;
//    entities_.push_back(rf.get(wle::Point(rand()%SCREEN_WIDTH, SCREEN_HEIGHT/2)));
//    entities_.push_back(rf.get(wle::Point(rand()%SCREEN_WIDTH, SCREEN_HEIGHT/2)));

    // Start the game loop
    while (window.isOpen()){
    	// Process events
    	sf::Event event;
    	while (window.pollEvent(event)){
    		// Close window : exit
    		if (event.type == sf::Event::Closed)
    			window.close();
            
    		// Escape pressed : exit
    		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    			window.close();
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                entities_.push_back(rf.get());
                objects++;
                std::ostringstream stream;
                stream << "Objects: " << objects;
                text.setString(stream.str());
            }
    	}

        //Update
        //check collision
        checkCollision(entities_);
        int dt = c.getElapsedTime().asMilliseconds();
        for(std::vector<Rectangle *>::iterator it = entities_.begin(); it != entities_.end(); it++){
            (*it)->update(dt);
        }
        c.restart();
        
    	// Clear screen
    	window.clear(sf::Color(255, 255, 255));
        window.draw(text);
        for(std::vector<Rectangle *>::iterator it = entities_.begin(); it != entities_.end(); it++){
            (*it)->render(window);
        }
    	// Update the window
    	window.display();
    }
	return EXIT_SUCCESS;
}
