/*
 Quadtree
 
 */
#ifndef __QuadTree__qtree__
#define __QuadTree__qtree__

#include <vector>
#include "qtree_utility.h"

namespace wle {
    
    class QuadTree {
    public:
        QuadTree(int level, AABB bounds);
        void clear();
        void insert(AABB obj);
        std::vector<AABB>retrieve(AABB forObject);
        
    private:
        const int kMaxObjects = 10;
        const int kMaxLevels = 5;
        typedef int NEWS;
        const NEWS SW = 0;
        const NEWS SE = 1;
        const NEWS NW = 2;
        const NEWS NE = 3;
        const NEWS XX = -1;
        int level_;
        std::vector<AABB> objects_;   //Objects in this node
        AABB bounds_;
        QuadTree *child_[4];            //sw, se, nw, ne
        void split();
        NEWS getIndex(AABB rect);
    };
    
}
#endif
//EOF