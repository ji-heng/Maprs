#include "Maprs.h"



struct MaprsLatlong MaprsLatlong;
struct MaprsPHG MaprsPHG;
struct MaprsUseConfig MaprsUseConfig;
extern const char MaprsReportHead[4][2];


double log2(double n)
{
    return log(n) * M_LOG2E;
};

void decimal2DMS(double decimalDegrees,struct DMS *DMS){
     float e;
    int H;
    int M;
    int S;
    
    DMS->Hour = (uint16_t)(decimalDegrees);//度
    DMS->Minute = (uint16_t)((decimalDegrees - DMS->Hour)*60); //分
    DMS->Second = (uint16_t)(((decimalDegrees- DMS->Hour)*60 - DMS->Minute) *60);   //秒

    e = ((decimalDegrees-DMS->Hour)*60 - DMS->Minute) *60 - DMS->Second; //四舍五入

    if(5<=(uint16_t)(e*10)){
        DMS->Second +=1;
    }
    if(60==DMS->Second){
        DMS->Second = 0;
        DMS->Minute +=1;
    }
    if (60==DMS->Minute){
         DMS->Minute = 0;
        DMS->Hour +=1;
    }
}


char getMaprsReportHead(enum MaprsReportType reporttype){
    switch (reporttype){
    case LATLONG:
        return MaprsReportHead[MaprsUseConfig.UseComment][MaprsUseConfig.UseTimestamp];
        break;
    case DF:
        return MaprsReportHead[MaprsUseConfig.UseComment][MaprsUseConfig.UseTimestamp];
        break;
    case OBJECT:
        return MaprsReportHead[OBJECT][0];
        break;
    default:
        return ' ';
        break;
    }
}

char *getMaprsDHM(void){
    static char DHMstr[8];
    sprintf(DHMstr,"092345%c",MaprsUseConfig.TimeIndicator);
    return DHMstr;
}

char *getMaprsTimeStamp(void){
    if(MaprsUseConfig.UseTimestamp){
        switch (MaprsUseConfig.TimestampType){
        case TIME_DHM:
            return getMaprsDHM();
            break;
        case TIME_HMS:
            /* code */
            break;
        default:
            return "\0";
            break;
        }
    }
}

char *girMaprsLatitude(void){
     static char latstr[9];
     sprintf(latstr,"%02d%02d.%02d%c",MaprsUseConfig.Latlong.latitude.Hour,MaprsUseConfig.Latlong.latitude.Minute,MaprsUseConfig.Latlong.latitude.Second,MaprsUseConfig.Latlong.latFlag);
     return latstr;
}

void setMaprsLatitude(double latitude,char flag){
    decimal2DMS(latitude,&MaprsUseConfig.Latlong.latitude);
    MaprsUseConfig.Latlong.latFlag = flag;
    DEBUG("latitude.Hour = %d\n",MaprsUseConfig.Latlong.latitude.Hour);
    DEBUG("latitude.Minute = %d\n",MaprsUseConfig.Latlong.latitude.Minute);
    DEBUG("latitude.Second = %d\n",MaprsUseConfig.Latlong.latitude.Second);
}

char *getMaprsLongitude(void){
     static char longstr[10];
     sprintf(longstr,"%03d%02d.%02d%c",MaprsUseConfig.Latlong.longitude.Hour,MaprsUseConfig.Latlong.longitude.Minute,MaprsUseConfig.Latlong.longitude.Second,MaprsUseConfig.Latlong.longFlag);
     return longstr;
}

void setMaprsLongitude(double longitude,char flag){
    decimal2DMS(longitude,&MaprsUseConfig.Latlong.longitude);
    MaprsUseConfig.Latlong.longFlag = flag;
    DEBUG("longitude.Hour = %d\n",MaprsUseConfig.Latlong.longitude.Hour);
    DEBUG("longitude.Minute = %d\n",MaprsUseConfig.Latlong.longitude.Minute);
    DEBUG("longitude.Second = %d\n",MaprsUseConfig.Latlong.longitude.Second);
}

char *getMaprsComment(void){
    if(MaprsUseConfig.UseComment){
        return MaprsUseConfig.Comment;
    }else{
        return "\0";
    }
}

char *getMaprsPHG(void){
    static char phgstr[8];
    sprintf(phgstr,"PHG%d%d%d%d",MaprsUseConfig.PHG.Power,MaprsUseConfig.PHG.Height,MaprsUseConfig.PHG.Gain,MaprsUseConfig.PHG.Directivity);
    return phgstr;
}

void SetMaprsPHG(uint16_t power,uint16_t height,uint16_t gain,uint16_t directivity){
    power = (uint16_t)sqrt(power);
    height =  (uint16_t)log2((height/10.0)+1);
    directivity = (uint16_t)directivity/45;

    MaprsUseConfig.PHG.Power = power>9?9:power;
    MaprsUseConfig.PHG.Height = height>9?9:height;
    MaprsUseConfig.PHG.Gain = gain>9?9:gain;
    MaprsUseConfig.PHG.Directivity = directivity>360?0:directivity;

    DEBUG("PHG.Power = %d (W)\n",MaprsUseConfig.PHG.Power);
    DEBUG("PHG.height = %d (Feet)\n",MaprsUseConfig.PHG.Height);
    DEBUG("PHG.Gain = %d (dB)\n",MaprsUseConfig.PHG.Gain);
    DEBUG("PHG.Directivity = %d (deg)\n",MaprsUseConfig.PHG.Directivity);
}

char *getMaprsRNG(void){
    static char rngstr[8];
    sprintf(rngstr,"RNG%04d",MaprsUseConfig.RNG);
    return rngstr;
}

void SetMaprsRNG(uint16_t rng){
    MaprsUseConfig.RNG = rng>9999?9999:rng;
}

char *getMaprsDFS(void){
    static char dfsstr[8];
    sprintf(dfsstr,"DFS%d%d%d%d",MaprsUseConfig.DFS.Strength,MaprsUseConfig.DFS.Height,MaprsUseConfig.DFS.Gain,MaprsUseConfig.DFS.Directivity);
    return dfsstr;
}

void SetMaprsDFS(uint16_t strength, uint16_t height, uint16_t gain, uint16_t directivity){
    height =  (uint16_t)log2((height/10.0)+1);
    directivity = (uint16_t)directivity/45;

    MaprsUseConfig.DFS.Strength = strength>9?9:strength;
    MaprsUseConfig.DFS.Height = height>9?9:height;
    MaprsUseConfig.DFS.Gain = gain>9?9:gain;
    MaprsUseConfig.DFS.Directivity = directivity>360?0:directivity;

    DEBUG("DFS.Strength = %d (S-points)\n",MaprsUseConfig.DFS.Strength);
    DEBUG("DFS.height = %d (Feet)\n",MaprsUseConfig.DFS.Height);
    DEBUG("DFS.Gain = %d (dB)\n",MaprsUseConfig.DFS.Gain);
    DEBUG("DFS.Directivity = %d (deg)\n",MaprsUseConfig.DFS.Directivity);
}

char *getMaprsCSESPD(void){
    static char csespdstr[8];
    sprintf(csespdstr,"%03d/%03d",MaprsUseConfig.CSESPD.CSE,MaprsUseConfig.CSESPD.SPD);
    return csespdstr;
}

char *getMaprsBRGNRQ(void){
    static char brgnrqtr[9];
    sprintf(brgnrqtr,"/%03d/%03d",MaprsUseConfig.MaprsBRGNRQ.BRG,MaprsUseConfig.MaprsBRGNRQ.NRQ);
    return brgnrqtr;
}

char *getMapesDataExtension(enum MaprsReportType type){
   if (type == DF){
       return getMaprsCSESPD();
   };
   if(MaprsUseConfig.UseDataExtension){
        switch (MaprsUseConfig.DataExtensionType)
        {
        case PHG:
            return getMaprsPHG();
        case RNG:
            return getMaprsRNG();
        case DFS:
            return getMaprsDFS();
        case CSESPD:
            return getMaprsCSESPD();  
        default:
            return "\0";
            break;
        }
   };
    return "\0";
}

void setMaprsSymTableID(char symboltalbe){
    if(symboltalbe=='/'|| symboltalbe == '\\'){
        MaprsUseConfig.SymTableID = (char)symboltalbe;
    }
}

char getMaprsSymTableID(void)
{
    return MaprsUseConfig.SymTableID;
}

void setMaprsSymbolCode(unsigned char symbolcode){
    if(isprint(symbolcode)){
        MaprsUseConfig.SymbolCode = (char)symbolcode;
    }
}

char getMaprsSymbolCode(void)
{
    return MaprsUseConfig.SymbolCode;
}

char *getMaprsObjectName(void){
    return MaprsUseConfig.objectname;
}

char setMaprsObjectName(char *objectname){
    for (int i=0;i<9;i++){
        if(*objectname == '\0'){
            MaprsUseConfig.objectname[i] = '-';
        }else{
            MaprsUseConfig.objectname[i] = *objectname++;
        }
    }
    MaprsUseConfig.objectname[9] = '\0';
}

char getMaprsObjectState(enum MaprsObjectState objectstate){
    switch (objectstate)
    {
    case LIVE:
        return '*';
        break;
    case KILL:
        return '_';
    default:
        return ' ';
        break;
    }
}

void MaprsLatLongReport(void)
{
     printf("%c%s%s%c%s%c%s%s\n",getMaprsReportHead(LATLONG),getMaprsTimeStamp(),girMaprsLatitude(),getMaprsSymTableID(),getMaprsLongitude(),getMaprsSymbolCode(),getMapesDataExtension(LATLONG),getMaprsComment());
}

void MaprsDFReport(void){
    printf("%c%s%s%c%s%c%s%s%s\n",getMaprsReportHead(LATLONG),getMaprsTimeStamp(),girMaprsLatitude(),getMaprsSymTableID(),getMaprsLongitude(),getMaprsSymbolCode(),getMapesDataExtension(DF),getMaprsBRGNRQ(),getMaprsComment());
}

void MaprsObjectReport(void){
    MaprsUseConfig.UseTimestamp = true;
    printf("%c%s%c%s\n",getMaprsReportHead(OBJECT),getMaprsObjectName(),getMaprsObjectState(LIVE),getMaprsTimeStamp());
}
