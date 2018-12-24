#ifndef VIEWER_H
#define VIEWER_H

class Viewer
{
public:
    Viewer() {}
    virtual ~Viewer() {}
    virtual void openWindow() {}
    virtual void closeWindow() {}
    virtual void waitUntilButton() {}
    virtual void clear() {}
    virtual void add(double valeur) {}
    virtual void afficheInit() {}
    virtual void afficheVal(int val) {}
    virtual void drawPoint(int x,int y) {}
    virtual void drawLine(int x1,int y1,int x2,int y2) {}
    virtual double pixelX(double x) {return 0;}
    virtual double pixelY(double y) {return 0;}
};

#endif // VIEWER_H
