//
//  1401_CircleandRectangleOverlapping.cpp
//  cppleetcode
//
//  Created by yuxin on 11/27/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include <algorithm>


class CirleAndRectangleOverlapping {
    
public:
    bool doit_math(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {

        auto min_abs = [&](int a, int b) {
            
            if (a < 0 && b > 0)
                return 0;
            else if (a > 0)
                return a * a;
            else
                return b * b;
        };
        
        
        return min_abs(x1 - x_center, x2 - x_center) + min_abs(y1 - y_center, y2 - y_center) <= radius * radius;
    }
    
    
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        
        int x = std::max(x1 , std::min(x2 , x_center));
        int y = std::max(y1 , std::min(y2 , y_center));
        return (x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) <= radius * radius;
    }
};



void test_1401_circle_rectangle_overlapping() {
    

    CirleAndRectangleOverlapping().doit_math(2, 6, 8, 5, 1,10,4);
    
}
