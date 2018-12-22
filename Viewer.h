#ifndef VIEWER_H
#define VIEWER_H
#include <vector>
#include "graphics.h"
#include "viewPort.hpp"

class Viewer
{
    public:
        Viewer(int largeur = 800, int hauteur = 600);
        virtual ~Viewer() {}
        virtual void openWindow();
        virtual void closeWindow();
        virtual void waitUntilButton();
        virtual void clear();
        virtual void add(double valeur);
        virtual void afficheInit();
        virtual void afficheVal(int val);
        virtual void drawPoint(int x,int y);
        virtual void drawLine(int x1,int y1,int x2,int y2);
        virtual double pixelX(double x);
        virtual double pixelY(double y);
    private:
        std::vector<double> d_points;
        int d_largeur;
        int d_hauteur;
        bool d_open;
        const int Max_Element = 30;
        const int decalageY = 20;
        const int decalageX = 20;
        viewPort CoordonneesY;
        viewPort CoordonneesX;
};

class NoViewer : public Viewer
{
public:
    NoViewer() : Viewer{} {}
    virtual void openWindow() override {}
    virtual void closeWindow() override {}
    virtual void waitUntilButton() override {}
    virtual void clear() override {}
    virtual void add(double valeur) override {}
    virtual void afficheInit() override {}
    virtual void afficheVal(int val) override {}
    virtual void drawPoint(int x,int y) override {}
    virtual void drawLine(int x1,int y1,int x2,int y2) override {}
    virtual double pixelX(double x) override {return 0;}
    virtual double pixelY(double y) override {return 0;}
};


#endif // VIEWER_H
