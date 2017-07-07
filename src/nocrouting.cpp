#include "nocrouting.h"

#include "noccommon.h"
#include "nocdebug.h"

routingInfo routingXY(unsigned source, unsigned dest)
{

    NoCDebug::printDebug(std::string("Routing XY: " + std::to_string(source) + " --> " + std::to_string(dest)), NoCDebug::Router);

    //Identify Row (Y)
    //Source
    unsigned source_router_y = ceil(float (source + 1) / NOC_ROW_SIZE);
    //Dest
    unsigned dest_router_y = ceil(float (dest + 1) / NOC_ROW_SIZE);
    //DeltaX
    int deltaY = dest_router_y - source_router_y;

    //Identify Column (X)
    //Source
    unsigned source_router_x = (source + 1) - (source_router_y - 1) * NOC_ROW_SIZE;
    //Dest
    unsigned dest_router_x = (dest + 1) - (dest_router_y - 1) * NOC_ROW_SIZE;
    //DeltaY
    int deltaX = dest_router_x - source_router_x;

    NoCDebug::printDebug(std::string("Routing XY: DeltaX " + std::to_string(deltaX) + " DeltaY " + std::to_string(deltaY)), NoCDebug::Router);

    routingInfo rXY;

    //Move in X
    if (deltaX != 0) {

        NoCDebug::printDebug(std::string("Routing XY: Move X"), NoCDebug::Router);

        int stepX = (deltaX > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepX + 1) / NOC_ROW_SIZE);

        // 1. Check if the current router is in same row as the target router (SourceX = UpdateY)
        if (source_router_y == updated_source_router_y) {

            //Move Source
            rXY.position = source + stepX;

            //Link Identification
            if (stepX > 0) {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::West)), NoCDebug::Router);
                rXY.link = Link::West;
            } else {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::East)), NoCDebug::Router);
                rXY.link = Link::East;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing XY: Wrong Move X"), NoCDebug::Router, true);

            rXY.position = source;
            rXY.link = -1;

        }

    }

    //Move in Y
    else if (deltaY != 0) {

        NoCDebug::printDebug(std::string("Routing XY: Move Y"), NoCDebug::Router);

        int stepY = (deltaY > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepY * NOC_ROW_SIZE + 1) / NOC_ROW_SIZE);
        unsigned updated_source_router_x = (source + stepY * NOC_ROW_SIZE + 1) - (updated_source_router_y - 1) * NOC_ROW_SIZE;

        // 1. Check if the current router is in same column as the target router (SourceX = UpdateX)
        if (source_router_x == updated_source_router_x) {

            //Move Source
            rXY.position = source + stepY * NOC_ROW_SIZE;

            //Link Identification
            if (stepY > 0) {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::North)), NoCDebug::Router);
                rXY.link = Link::North;
            } else {
                NoCDebug::printDebug(std::string("Routing XY: Link " + std::to_string(Link::South)), NoCDebug::Router);
                rXY.link = Link::South;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing XY: Wrong Move Y"), NoCDebug::Router, true);

            rXY.position = source;
            rXY.link = -1;

        }

    }

    //In position
    else {

        NoCDebug::printDebug(std::string("Routing XY: In position"), NoCDebug::Router);

        rXY.position = source;
        rXY.link = 0;

    }

    return rXY;

}

routingInfo routingYX(unsigned source, unsigned dest)
{

    NoCDebug::printDebug(std::string("Routing YX: " + std::to_string(source) + " --> " + std::to_string(dest)), NoCDebug::Router);

    //Identify Row (Y)
    //Source
    unsigned source_router_y = ceil(float (source + 1) / NOC_ROW_SIZE);
    //Dest
    unsigned dest_router_y = ceil(float (dest + 1) / NOC_ROW_SIZE);
    //DeltaX
    int deltaY = dest_router_y - source_router_y;

    //Identify Column (X)
    //Source
    unsigned source_router_x = (source + 1) - (source_router_y - 1) * NOC_ROW_SIZE;
    //Dest
    unsigned dest_router_x = (dest + 1) - (dest_router_y - 1) * NOC_ROW_SIZE;
    //DeltaY
    int deltaX = dest_router_x - source_router_x;

    NoCDebug::printDebug(std::string("Routing YX: DeltaX " + std::to_string(deltaX) + " DeltaY " + std::to_string(deltaY)), NoCDebug::Router);

    routingInfo rYX;

    //Move in Y
    if (deltaY != 0) {

        NoCDebug::printDebug(std::string("Routing YX: Move Y"), NoCDebug::Router);

        int stepY = (deltaY > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepY * NOC_ROW_SIZE + 1) / NOC_ROW_SIZE);
        unsigned updated_source_router_x = (source + stepY * NOC_ROW_SIZE + 1) - (updated_source_router_y - 1) * NOC_ROW_SIZE;

        // 1. Check if the current router is in same column as the target router (SourceX = UpdateX)
        if (source_router_x == updated_source_router_x) {

            //Move Source
            rYX.position = source + stepY * NOC_ROW_SIZE;

            //Link Identification
            if (stepY > 0) {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::North)), NoCDebug::Router);
                rYX.link = Link::North;
            } else {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::South)), NoCDebug::Router);
                rYX.link = Link::South;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing YX: Wrong Move Y"), NoCDebug::Router, true);

            rYX.position = source;
            rYX.link = -1;

        }

    }

    //Move in X
    else if (deltaX != 0) {

        NoCDebug::printDebug(std::string("Routing YX: Move X"), NoCDebug::Router);

        int stepX = (deltaX > 0) ? 1 : -1;

        unsigned updated_source_router_y = ceil(float (source + stepX + 1) / NOC_ROW_SIZE);

        // 1. Check if the current router is in same row as the target router (SourceX = UpdateY)
        if (source_router_y == updated_source_router_y) {

            //Move Source
            rYX.position = source + stepX;

            //Link Identification
            if (stepX > 0) {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::West)), NoCDebug::Router);
                rYX.link = Link::West;
            } else {
                NoCDebug::printDebug(std::string("Routing YX: Link " + std::to_string(Link::East)), NoCDebug::Router);
                rYX.link = Link::East;
            }

        }

        //Error
        else {

            NoCDebug::printDebug(std::string("Routing YX: Wrong Move X"), NoCDebug::Router, true);

            rYX.position = source;
            rYX.link = -1;

        }

    }

    //In position
    else {

        NoCDebug::printDebug(std::string("Routing YX: In position"), NoCDebug::Router);

        rYX.position = source;
        rYX.link = 0;

    }

    return rYX;

}

void routingTest(unsigned source, unsigned dest)
{

    //Fail Safe: Source
    if (source < 0 || source > NOC_SIZE - 1) {

        NoCDebug::printDebug(std::string("Routing: Source position isn't part of the NOC"), NoCDebug::Router, true);

    }

    //Fail Safe: Dest
    if (dest < 0 || dest > NOC_SIZE - 1) {

        NoCDebug::printDebug(std::string("Routing: Dest position isn't part of the NOC"), NoCDebug::Router,true);

    }

    //Max Routing steps
    unsigned step_max = (NOC_ROW_SIZE - 1) + unsigned (ceil(float (NOC_SIZE / NOC_ROW_SIZE)) -1);
    //Steps
    unsigned stepXY = 0;

    //Routing Algorithm: XY or YX
    routingInfo routing;

    routing = routingYX(source, dest);

    while (routing.link > 0 && stepXY <= step_max) {

        routing = routingYX(routing.position, dest);
        stepXY++;

    }

    //Error: Diverting Routing
    if (stepXY > step_max) {

        NoCDebug::printDebug(std::string("Routing: Diverting Routing"), NoCDebug::Router, true);

    }

    //Error: Logic Fail
    if (routing.link == -1 || routing.position > NOC_SIZE - 1) {

        NoCDebug::printDebug(std::string("Routing: Logic Fail"), NoCDebug::Router, true);

    }

}
