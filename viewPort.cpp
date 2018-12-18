#include "viewPort.hpp"

viewPort::viewPort(double sourceMin, double sourceMax, double destinationMin, double destinationMax) : d_sourceMin{sourceMin}, d_sourceMax{sourceMax}, d_destinationMin{destinationMin}, d_destinationMax{destinationMax}, d_delta{(d_destinationMax - d_destinationMin) / (d_sourceMax - d_sourceMin)}
{}

double viewPort::destinationFromSource(double source) const
{
    return d_destinationMin + d_delta * (source - d_sourceMin);
}

double viewPort::sourceFromDestination(double destination) const
{
    return d_sourceMin + (destination - d_destinationMin) / d_delta;
}
