//
//  qtree.cpp
//  QuadTree
//
//  Created by Sidharth on 05/01/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "qtree.h"
#include <algorithm>

namespace wle{
    //Create QuadTree
    QuadTree::QuadTree(int level, AABB bounds) :
    bounds_(bounds),
    level_(level){
        for (int i = 0; i < 4; i++) {
            child_[i] = 0;
        }
    }

    //recursively clear QuadTree
    void QuadTree::clear(){
        objects_.clear();
        for(int i = 0; i < 4; i++){
            if(child_[i]){
                child_[i]->clear();
                child_[i] = 0;
            }
        }
    }
    
    //Split into sub quads
    void QuadTree::split(){
        Point sizeHalf(bounds_.getSize().getX()/2, bounds_.getSize().getY()/2);
        Point center = bounds_.getCenter();

        child_[SW] = new QuadTree(level_+1, AABB(Point(center.getX()-sizeHalf.getX(), center.getY()-sizeHalf.getY()), sizeHalf));
        child_[SE] = new QuadTree(level_+1, AABB(Point(center.getX()+sizeHalf.getX(), center.getY()-sizeHalf.getY()), sizeHalf));
        child_[NW] = new QuadTree(level_+1, AABB(Point(center.getX()-sizeHalf.getX(), center.getY()+sizeHalf.getY()), sizeHalf));
        child_[NE] = new QuadTree(level_+1, AABB(Point(center.getX()+sizeHalf.getX(), center.getY()+sizeHalf.getY()), sizeHalf));
    }
    
    //Determine which sub-quad the object belongs to.
    //-1 means boundary case. Hence in the parent node.
    QuadTree::NEWS QuadTree::getIndex(wle::AABB rect){
        for(int index = 0;index < 4; index++){
            if(child_[index] && child_[index]->bounds_.containsRect(rect)){
                return index;
            }
        }
        return XX;
    }
    
    //Insert object into quadtree. If this node exceeds the limit, split it.
    void QuadTree::insert(wle::AABB obj){
        if(child_[SW]){
            NEWS n = getIndex(obj);
            if(n != XX){
                child_[n]->insert(obj);
                return;
            }
        }
        
        objects_.push_back(obj);
        if(objects_.size() > kMaxObjects && level_ < kMaxLevels){
            if(!child_[SW]){
                split();
            }
            
            for (std::vector<AABB>::iterator it = objects_.begin(); it != objects_.end();) {
                NEWS n = getIndex(*it);
                if(n != XX){
                    child_[n]->insert(*it);
                    objects_.erase(it);
                }else{
                    it++;
                }
            }
        }
    }
    
    //Return all objects that could collide for given object
    std::vector<AABB> QuadTree::retrieve(wle::AABB forObject){
        std::vector<AABB> res;  //result
        
        NEWS n = getIndex(forObject);
        if(n != XX && child_[SW]){
            std::vector<AABB> tmp = child_[n]->retrieve(forObject);
            res.resize(tmp.size(),forObject);
            std::copy(tmp.begin(), tmp.end(), res.begin());
        }
        
        return res;
    }
}
//EOF