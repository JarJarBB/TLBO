#ifndef VIEWERBGI_H
#define VIEWERBGI_H

#include "Viewer.h"
#include <vector>
#include "viewPort.hpp"

class ViewerBGI : public Viewer
{
    public:
        ViewerBGI(int largeur = 800, int hauteur = 600);
        virtual void openWindow();
        virtual void closeWindow();
        virtual void waitUntilButton();
        virtual void clear();
        virtual void add(double valeur);
        virtual void afficheInit();
        virtual void afficheVal(int val);
        virtual void drawPoint(int x, int y);
        virtual void drawLine(int x1, int y1, int x2, int y2);
        virtual double pixelX(double x);
        virtual double pixelY(double y);
    private:
        std::vector<double> d_points;
        int d_largeur;
        int d_hauteur;
        bool d_open;
        viewPort CoordonneesY;
        viewPort CoordonneesX;
};

#endif // VIEWERBGI_H
