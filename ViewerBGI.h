#ifndef VIEWERBGI_H
#define VIEWERBGI_H

#include "Viewer.h"
#include <vector>
#include "viewPort.hpp"

class ViewerBGI : public Viewer
{
    public:
        ViewerBGI(int largeur = 800, int hauteur = 600);
        virtual void openWindow() override;
        virtual void closeWindow() override;
        virtual void waitUntilButton() override;
        virtual void clear() override;
        virtual void add(double valeur) override;
        virtual void afficheInit() override;
        virtual void afficheVal(int val) override;
        virtual void drawPoint(int x,int y) override;
        virtual void drawLine(int x1,int y1,int x2,int y2) override;
        virtual double pixelX(double x) override;
        virtual double pixelY(double y) override;
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

#endif // VIEWERBGI_H
