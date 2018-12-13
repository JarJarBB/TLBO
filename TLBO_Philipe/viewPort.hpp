#ifndef viewPort_hpp
#define viewPort_hpp

class viewPort {
    
public :
    viewPort(double sourceMin, double sourceMax, double destinationMin, double destinationMax);
    double destinationFromSource(double source) const;
    double sourceFromDestination(double destination) const;
    
private:
    double d_sourceMin, d_sourceMax;
    double d_destinationMin, d_destinationMax;
    double d_delta;
};


#endif /* viewPort_hpp */
