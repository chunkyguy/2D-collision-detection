//
//  qtree_utility.h
//  QuadTree
//
//  Created by Sidharth on 04/01/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __QuadTree__qtree_utility__
#define __QuadTree__qtree_utility__
#include <CoreGraphics/CoreGraphics.h>
#include <vector>
#include <iostream>

namespace wle{    
    // Point:    CGPoint
    class Point{
    private:
        CGPoint p_;
    public:
        double getX(){
            return p_.x;
        }
        double getY(){
            return p_.y;
        }
        CGPoint getCGPoint(){
            return p_;
        }
        Point(double x, double y) : p_(CGPointMake(x, y)){
        }
    };
    
    // AABB:  CGRect
    class AABB{
    private:
        CGRect r_;
    public:
        AABB(Point center, Point half_dimension){
            r_ = CGRectMake(center.getX()-half_dimension.getX(), center.getY()-half_dimension.getY(), half_dimension.getX()*2, half_dimension.getY()*2);
        }
        
        AABB(CGRect r) : r_(r){
        }
        
        bool containsPoint(Point p){
            return CGRectContainsPoint(r_, p.getCGPoint());
        }
        
        bool containsRect(AABB &r){
            return CGRectContainsRect(r_, r.getCGRect());
        }
        
        bool intersects(AABB r){
            return CGRectIntersectsRect(r_, r.getCGRect());
        }
        
        CGRect getCGRect(){
            return r_;
        }
        
        Point getCenter(){
            return Point(r_.origin.x, r_.origin.y);
        }
        
        Point getSize(){
            return Point(r_.size.width, r_.size.height);
        }
        
        //sw, se, nw, ne
        std::vector<AABB> subdivide(){
            CGRect w, e;
            CGRectDivide(r_, &w, &e, CGRectGetWidth(r_)/2, CGRectMinXEdge);
            CGRect nw, sw;
            CGRectDivide(w, &nw, &sw, CGRectGetHeight(w)/2, CGRectMinYEdge);
            CGRect ne, se;
            CGRectDivide(r_, &ne, &se, CGRectGetHeight(e)/2, CGRectMinYEdge);
            
            AABB sw_(sw), se_(se), nw_(nw), ne_(ne);
            std::vector<AABB> sub;
            sub.push_back(sw_);
            sub.push_back(se_);
            sub.push_back(nw_);
            sub.push_back(ne_);
            return sub;
        }
        
        friend std::ostream &operator<<(std::ostream &os, const AABB &vec){
            os  << "{{" << vec.r_.origin.x << "," << vec.r_.origin.y << "},{" << vec.r_.size.width << "," << vec.r_.size.height << "}}";
            return os;
        }
    };

}
#endif /* defined(__QuadTree__qtree_utility__) */
