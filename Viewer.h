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
    virtual void add(double valeur) {valeur = valeur;}
    virtual void afficheInit() {}
    virtual void afficheVal(int val) {val = val;}
    virtual void drawPoint(int x, int y) {x = y = x;}
    virtual void drawLine(int x1, int y1, int x2, int y2) {x1 = y1 = x2 = y2 = x1;}
    virtual double pixelX(double x) {return x;}
    virtual double pixelY(double y) {return y;}
};

#endif // VIEWER_H
