#include <stdio.h>
#include <string.h>
#include "Maprs.h"

extern struct MaprsUseConfig MaprsUseConfig;
int main(void){

    MaprsUseConfig.UseComment = true;
    MaprsUseConfig.UseTimestamp = true;
    MaprsUseConfig.TimestampType = TIME_DHM;
    MaprsUseConfig.TimeIndicator = TIME_UTC;
    MaprsUseConfig.UseDataExtension = true;
    MaprsUseConfig.DataExtensionType = PHG;

    memcpy(&MaprsUseConfig.Comment, "Helloword", 10);

    setMaprsLatitude(49.00000000000000, 'E');
    setMaprsLongitude(113.00000000000000, 'N');
    setMaprsSymTableID('\\');
    setMaprsSymbolCode('r');
    SetMaprsPHG(500,25,10,80);
    SetMaprsRNG(560);
    SetMaprsDFS(500,25,10,80);
    printf("\n");
    setMaprsObjectName("Obj");
    printf("\n");
    
    MaprsUseConfig.CSESPD.CSE = 88;
    MaprsUseConfig.CSESPD.SPD = 36;
    MaprsUseConfig.MaprsBRGNRQ.BRG = 270;
    MaprsUseConfig.MaprsBRGNRQ.NRQ = 729;

    MaprsLatLongReport();
    printf("\n");
    MaprsDFReport();
    printf("\n");
    MaprsObjectReport();
    return 0;
}
