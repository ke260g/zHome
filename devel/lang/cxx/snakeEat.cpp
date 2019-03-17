#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<stdlib.h>
#include<iostream>
#include<utility>
#include<tuple>
#include<queue>
#include<list>

using namespace cv;
using namespace std;

#define W 8
#define L 10 // length

class Snake {
    public:
        struct torward {
            cv::Point2i lfPoint; // left point
            cv::Point2i rhPoint; // right point
            int direct;
        } head, tail;
        struct segNode {
            struct torward twd;
            int len; // len
        };
        std::queue<struct segNode, std::list<struct segNode>> segQueue;
        int length;
        int width;
        int modifyTorward(struct torward & src, int & newDirect);
        void move(Mat & m, struct torward & twd, int colorVal);
};

// 0 error input, 1 not modify, 2 modify
int Snake::modifyTorward(struct torward & old, int & newDirect) {
    int & oldDirect = old.direct;
    switch (newDirect) {
        case 'w':
            if(oldDirect == 'w')
                return 1;
            if(oldDirect != 's') {
                if(oldDirect == 'a') {
                    old.lfPoint = old.rhPoint;
                    old.rhPoint.x += (this->width - 1);
                }
                if(oldDirect == 'd') {
                    old.rhPoint = old.lfPoint;
                    old.lfPoint.x -= (this->width - 1);
                }
                oldDirect = 'w';
                return 2;
            }
            break;
        case 's':
            if(oldDirect == 's')
                return 1;
            if(oldDirect != 'w') {
                if(oldDirect == 'a') {
                    old.rhPoint = old.lfPoint;
                    old.lfPoint.x += (this->width - 1);
                }
                if(oldDirect == 'd') {
                    old.lfPoint = old.rhPoint;
                    old.rhPoint.x -= (this->width - 1);
                }
                oldDirect = 's';
                return 2;
            }
            break;
        case 'a':
            if(oldDirect == 'a')
                return 1;
            if(oldDirect != 'd') {
                if(oldDirect == 'w') {
                    old.rhPoint = old.lfPoint;
                    old.lfPoint.y += (this->width - 1);
                }
                if(oldDirect == 's') {
                    old.lfPoint = old.rhPoint;
                    old.rhPoint.y -= (this->width - 1);
                }
                oldDirect = 'a';
                return 2;
            }
            break;
        case 'd':
            if(oldDirect == 'd')
                return 1;
            if(oldDirect != 'a') {
                if(oldDirect == 'w') {
                    old.lfPoint = old.rhPoint;
                    old.rhPoint.y += (this->width - 1);
                }
                if(oldDirect == 's') {
                    old.rhPoint = old.lfPoint;
                    old.lfPoint.y -= (this->width - 1);
                }
                oldDirect = 'd';
                return 2;
            }
            break;
        default:
            return 0;
    }
    return 0;
}

void Snake::move(Mat & m, struct torward & twd, int colorVal) {
    auto scl = Scalar(colorVal, colorVal, colorVal);
    switch(twd.direct) {
        case 'w':
            twd.lfPoint.y -= this->width;
            rectangle(m, twd.lfPoint, twd.rhPoint, scl, -1);
            twd.rhPoint.y -= this->width;
            break;
        case 's':
            twd.lfPoint.y += this->width;
            rectangle(m, twd.rhPoint, twd.lfPoint, scl, -1);
            twd.rhPoint.y += this->width;
            break;
        case 'a':
            twd.rhPoint.x -= this->width;
            rectangle(m, twd.rhPoint, twd.lfPoint, scl, -1);
            twd.lfPoint.x -= this->width;
            break;
        case 'd':
            twd.rhPoint.x += this->width;
            rectangle(m, twd.lfPoint, twd.rhPoint, scl, -1);
            twd.lfPoint.x += this->width;
            break;
    }
}

void updateSnake(Mat & m, Snake & snk, int newDirect) {
    int statusDirectModified = snk.modifyTorward(snk.head, newDirect);
    if(statusDirectModified == 0)
        return;
    // segqueue handle
    if(statusDirectModified == 2) {
        snk.segQueue.back().twd = snk.head;
        snk.segQueue.push({snk.head, 0});
    }

    // head pre-move
    snk.move(m, snk.head, 255);
    snk.segQueue.back().len += 1; // first seg plus 1

    // tail pre-move
    snk.move(m, snk.tail, 0);
    snk.segQueue.front().len -= 1; // last seg substract 1

    // change tail
    if(snk.segQueue.front().len == 0) {
        snk.tail = snk.segQueue.front().twd;
        snk.segQueue.pop();
    }
}

int main( int argc, char **argv ) {
    Mat m(Size(320, 240),CV_8UC1);
    memset(m.data, 0, 320*240);

    // init snake
    Snake snk;
    snk.width = W;
    snk.length = L;
    snk.tail = {
        .lfPoint = {80 - 1, 160},
        .rhPoint = {80 - 1, 160 + W - 1},
        .direct = 'd'};
    snk.head = {
        .lfPoint = {80 + L*W - 1, 160},
        .rhPoint = {80 + L*W - 1, 160 + W - 1},
        .direct = 'd'};
    snk.segQueue.push({snk.head, snk.length});

    rectangle(m, Point2i{80, 160}, snk.head.rhPoint, Scalar(100,100,100), -1);

    while(1) {
        imshow("window", m);
        int key = waitKey(1000);
        if(key == 'q')
            break;

        updateSnake(m, snk, key);
    }
    return 0;
}
