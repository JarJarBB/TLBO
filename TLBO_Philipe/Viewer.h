#ifndef VIEWER_H
#define VIEWER_H
#include <vector>
#include "graphics.h"
#include "viewPort.hpp"

class Viewer
{
    public:
        Viewer(int largeur,int hauteur);
        void openWindow();
        void closeWindow();
        void waitUntilButton();
        void clear();
        void add(double valeur);
        void afficheInit();
        void afficheVal(int val);
        void drawPoint(int x,int y);
        void drawLine(int x1,int y1,int x2,int y2);
        double pixelX(double x);
        double pixelY(double y);
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

#endif // VIEWER_H
