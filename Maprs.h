#ifndef _MAPRS_H
#define _MAPRS_H
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#define M_LOG2E		1.4426950408889634074


enum MaprsDirectionFlag{
    E = 'E',
    N = 'N',
    S = 'S',
    W = 'W',
};

enum MaprsReportType{
    LATLONG,
    DF,
    OBJECT,
    ITEM,
   
};

enum MaprsTimeStampType{
    TIME_DHM,
    TIME_HMS,
    TIME_DMHM,
};

enum MaprsTimeIndicatorType{
    TIME_UTC = 'z',
    TIME_LOC = '/',
};

enum MaprsDatExtensionType{
    PHG,
    RNG,
    DFS,
    CSESPD,
};

enum MaprsObjectState{
    LIVE,
    KILL,
};

struct DMS
{
    uint16_t Hour;
    uint16_t Minute;
    uint16_t Second;
};

struct MaprsLatlong
{
    struct DMS latitude;
    char latFlag;
    struct DMS longitude;
    char longFlag;
};

struct MaprsPHG
{
    uint16_t Power;
    uint16_t Height;
    uint16_t Gain;
    uint16_t Directivity;
};

struct MaprsDFS
{
    uint16_t Strength;
    uint16_t Height;
    uint16_t Gain;
    uint16_t Directivity;
};

struct MaprsCSESPD
{
    uint16_t CSE;
    uint16_t SPD;
};

struct MaprsBRGNRQ
{
    uint16_t BRG;
    uint16_t NRQ;
};

struct MaprsUseConfig
{
    bool UseComment;
    bool UseTimestamp;
    bool UseDataExtension;
    uint16_t DataExtensionType;
    struct MaprsPHG PHG;
    struct MaprsDFS DFS;
    struct MaprsCSESPD CSESPD;
    struct MaprsBRGNRQ MaprsBRGNRQ;
    uint16_t RNG;
    uint16_t TimestampType;
    uint16_t TimeIndicator;
    uint16_t SymTableID;
    uint16_t SymbolCode;
    char Comment[60];
    struct MaprsLatlong Latlong;
    char objectname[10];
};

const char MaprsReportHead[4][2] = {{'!', '='},{'/', '@'},{';'},{')'}};
//============set============
void setMaprsSymTableID(char symboltalbe);
void setMaprsSymbolCode(unsigned char symbolcode);
void SetMaprsPHG(uint16_t power, uint16_t height, uint16_t gain, uint16_t directivity);
void SetMaprsDFS(uint16_t strength, uint16_t height, uint16_t gain, uint16_t directivity);
void SetMaprsRNG(uint16_t rng);
void setMaprsComment(char *str);
void setMaprsLatitude(double latitude,char flag);
void setMaprsLongitude(double longitude,char flag);
char setMaprsObjectName(char *objectname);
//void setMaprsTimeIndicatorType(void);

//============git============
char gitMaprsReportHead(enum MaprsReportType reporttype);
char gitMaprsSymTableID(void);
char gitMaprsSymbolCode(void);
char *gitMapesDataExtension(enum MaprsReportType type);
char *gitMaprsPHG(void);
char *gitMaprsDFS(void);
char *gitMaprsRNG(void);
char *gitMaprsCSESPD(void);
char *gitMaprsBRGNRQ(void);
char *gitMaprsComment(void);
char *gitMaprsLatitude(void);
char *gitMaprsLongitude(void);
char *gitMaprsTimeStamp(void);
char *gitMaprsDHM(void);
char *gitMaprsObjectName(void);
char gitMaprsObjectState(enum MaprsObjectState objectstate);
//============report============
void MaprsLatLongReport(void);
void MaprsMaidenheadReport(void);
void MaprsDFReport(void);
void MaprsObjectReport(void);
void MaprsItemReport(void);
void MaprsMessageReport(void);
void MaprsMessageStateReport(void);

#endif
