#include "ViewerBGI.h"
#include <sstream>
#include "graphics.h"

ViewerBGI::ViewerBGI(int largeur,int hauteur):
    d_hauteur{hauteur},
    d_largeur{largeur},
    d_open{false},
    CoordonneesY{0,hauteur,hauteur-decalageY,decalageY},
    CoordonneesX{0,largeur,decalageX,largeur-decalageX},
    d_points{} {}

void ViewerBGI::openWindow() {
    opengraphsize(d_largeur+65,d_hauteur+15); /** il faut rajouter des constantes car WinBGi rogne le bord des fenêtres */
    d_open=true;
}

void ViewerBGI::closeWindow() {
    closegraph();
    d_open=false;
    }

void ViewerBGI::waitUntilButton() {
    getch();
    }

void ViewerBGI::clear(){
    cleardevice();
    }

void ViewerBGI::add(double valeur){
    if (d_points.size() < Max_Element){
        d_points.push_back(valeur);}
    else {
        for(int i=0;i<d_points.size()-1;i++){
            d_points[i]=d_points[i+1];
        }
        d_points[d_points.size()-1]=valeur;
    }
}

void ViewerBGI::drawPoint(int x,int y){
    fillellipse(pixelX(x),pixelY(y),3,3);
    }

void ViewerBGI::drawLine(int x1,int y1,int x2,int y2){
    line(pixelX(x1),pixelY(y1),pixelX(x2),pixelY(y2));
    drawPoint(x2,y2);
}

void ViewerBGI::afficheInit(){
    std::ostringstream ost1;
    ost1 << d_points[0];
    outtextxy(5, 5, ost1.str().c_str());
    if(d_points.size()>1){
        std::ostringstream ost2;
        ost2 << d_points.back();
        outtextxy(pixelX(d_largeur)-20, pixelY(d_hauteur*d_points[d_points.size()-1]/d_points[0])-20, ost2.str().c_str());}
    if(d_points.size()>0){
        drawPoint(0,d_hauteur);
        afficheVal(1);
    }
    delay(2);
}

void ViewerBGI::afficheVal(int val){
    if(d_points.size()>val){
        drawLine(d_largeur*(val-1)/(d_points.size()-1),
                 d_hauteur*d_points[val-1]/d_points[0],
                 d_largeur*val/(d_points.size()-1),
                 d_hauteur*d_points[val]/d_points[0]);

        afficheVal(val+1);
    }
}

double ViewerBGI::pixelX(double x){
    return CoordonneesX.destinationFromSource(x);
}

double ViewerBGI::pixelY(double y){
    return CoordonneesY.destinationFromSource(y);
}
