#ifndef NmeaParser_H
#define NmeaParser_H

#include <time.h>

#define GPRMC_TERM   "GPRMC"
#define GPGGA_TERM   "GPGGA"
#define GPGSA_TERM   "GPGSA"

typedef unsigned int byte;

class NmeaParser
{
  public:
    NmeaParser();
    bool encode(char c, long nowMsec);
    float getLatitude();
    float getLongitude();
    unsigned short getNumSats();
    unsigned long getSpeedKnots();
    unsigned long getDate();
    unsigned long getTime();
    bool getDatetime(struct tm *timeStruct, int timezone = 0);
    unsigned long getHdop();
    long getAltitudeMeters();
    long getCourseDegrees();

  private:
    bool termComplete(long nowMsec);
    bool verifyChecksum();
    int hexCharToInt(char a);
    long gpsatol(const char *str);
    int gpsstrcmp(const char *str1, const char *str2);
    bool gpsisdigit(char c);
    unsigned long parseDecimal(char *decimal);
    unsigned long parseDegrees(char *degree);

    enum {
      GPS_SENTENCE_OTHER, 
      GPS_SENTENCE_GPGGA, 
      GPS_SENTENCE_GPRMC, 
      GPS_SENTENCE_GPGSA
    };

    bool validSentence;

    typedef struct {
      unsigned long time;
      unsigned long date;
      long latitude;
      long longitude;
      long altitude;
      unsigned long speed;
      unsigned long course;
      unsigned long hdop;
      unsigned long vdop;
      unsigned long pdop;
      unsigned short numsats;
      unsigned long timestamp;
    } GpsData;

    GpsData decodingData;
    GpsData decodedData;

    // parsing state variables
    byte parity;
    bool isChecksumTerm;
    char term[15];
    byte sentenceType;
    byte termNumber;
    byte termOffset;
    bool gpsDataGood;
};

#endif
