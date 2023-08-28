#include "NmeaParser.h"

#include <iostream>
#include <time.h>

using namespace std;

NmeaParser::NmeaParser()
{
  validSentence = false;
  termNumber = 0;
  parity = 0;
}

bool NmeaParser::encode(char c, long nowMsec)
{
  validSentence = false;

  switch (c) {
    case ',': // term terminators
      parity ^= c;
    case '\r':
    case '\n':
    case '*':
      if (termOffset < sizeof(term)) {
        term[termOffset] = 0;
        validSentence = termComplete(nowMsec);
      }

      ++termNumber;
      termOffset = 0;
      isChecksumTerm = c == '*';
      return validSentence;

    case '$': // sentence begin
      termNumber = termOffset = 0;
      parity = 0;
      sentenceType = GPS_SENTENCE_OTHER;
      isChecksumTerm = false;
      gpsDataGood = false;
      return validSentence;
  }

  // ordinary characters
  if (termOffset < sizeof(term) - 1) {
    term[termOffset++] = c;
  }

  if (!isChecksumTerm) {
    parity ^= c;
  }
  return validSentence;
}

bool NmeaParser::termComplete(long nowMsec)
{
  if (isChecksumTerm) {
    return verifyChecksum();
  }

  // the first term determines the sentence type
  if (termNumber == 0)
  {
    if (!gpsstrcmp(term, GPRMC_TERM))
      sentenceType = GPS_SENTENCE_GPRMC;
    else if (!gpsstrcmp(term, GPGGA_TERM))
      sentenceType = GPS_SENTENCE_GPGGA;
    else if (!gpsstrcmp(term, GPGSA_TERM))
      sentenceType = GPS_SENTENCE_GPGSA;
    else
      sentenceType = GPS_SENTENCE_OTHER;

    return false;
  }

  if (sentenceType == GPS_SENTENCE_OTHER || ! term[0]) {
    return false;
  }
  
  if (sentenceType == GPS_SENTENCE_GPGGA) {
    switch (termNumber) {
      case 1:
        decodingData.time = parseDecimal(term);
        decodingData.timestamp = nowMsec;
        break;
      case 2:
        decodingData.latitude = parseDegrees(term);
        break;
      case 3:
        if (term[0] == 'S') {
          decodingData.latitude = -decodingData.latitude;
        }
        break;
      case 4:
        decodingData.longitude = parseDegrees(term);
        break;
      case 5:
        if (term[0] == 'W') {
          decodingData.longitude = -decodingData.longitude;
        }
        break;
      case 6:
        gpsDataGood = term[0] > '0';
        break;
      case 7:
        decodingData.numsats = gpsatol(term);
        break;
      case 8:
        decodingData.hdop = parseDecimal(term);
        break;
      case 9:
        decodingData.altitude = gpsatol(term);
        break;
    }
    return false;
  }

  if (sentenceType == GPS_SENTENCE_GPGSA) {
    switch(termNumber) {
      case 2:
        gpsDataGood = term[0] != '1';
        break;
      case 15:
        decodingData.pdop = gpsatol(term);
        break;
      case 16:
        decodingData.hdop = gpsatol(term);
        break;
      case 17:
        decodingData.vdop = gpsatol(term);
        break;
    }
    return false;
  }

  if (sentenceType == GPS_SENTENCE_GPRMC) {
    switch(termNumber) {
      case 2:
        gpsDataGood = term[0] == 'A';
        break;
      case 7:
        decodingData.speed = parseDecimal(term);
        break;
      case 8:
        decodingData.course = parseDecimal(term);
        break;
      case 9:
        decodingData.date = gpsatol(term);
        break;
    }
    return false;
  }

  return false;
}

unsigned long NmeaParser::getDate()
{
  return decodedData.date;
}

unsigned long NmeaParser::getTime()
{
  return decodedData.time;
}

float NmeaParser::getLatitude()
{
  return decodedData.latitude / 1000000.0;
}

float NmeaParser::getLongitude()
{
  return decodedData.longitude / 1000000.0;
}

unsigned short NmeaParser::getNumSats()
{
  return decodedData.numsats;
}

unsigned long NmeaParser::getHdop()
{
  return decodedData.hdop;
}

long NmeaParser::getAltitudeMeters()
{
  return decodedData.altitude;
}

unsigned long NmeaParser::getSpeedKnots()
{
  return decodedData.speed / 100;
}

long NmeaParser::getCourseDegrees()
{
  return decodedData.course / 100;
}

bool NmeaParser::verifyChecksum()
{
    byte checksum = 16 * hexCharToInt(term[0]) + hexCharToInt(term[1]);
    if (checksum == parity && gpsDataGood) {
      decodedData = decodingData;
      return true;
    }
    return false;
}

int NmeaParser::hexCharToInt(char a)
{
  if (a >= 'A' && a <= 'F')
    return a - 'A' + 10;
  else if (a >= 'a' && a <= 'f')
    return a - 'a' + 10;
  else
    return a - '0';
}

long NmeaParser::gpsatol(const char *str)
{
  long ret = 0;
  while (gpsisdigit(*str))
    ret = 10 * ret + *str++ - '0';
  return ret;
}

int NmeaParser::gpsstrcmp(const char *str1, const char *str2)
{
  while (*str1 && *str1 == *str2)
    ++str1, ++str2;
  return *str1;
}

bool NmeaParser::gpsisdigit(char c)
{ 
  return c >= '0' && c <= '9';
}

unsigned long NmeaParser::parseDecimal(char *decimal)
{
  bool isneg = *decimal == '-';
  if (isneg) ++decimal;
  unsigned long ret = 100UL * gpsatol(decimal);
  while (gpsisdigit(*decimal)) ++decimal;
  if (*decimal == '.')
  {
    if (gpsisdigit(decimal[1]))
    {
      ret += 10 * (decimal[1] - '0');
      if (gpsisdigit(decimal[2]))
        ret += decimal[2] - '0';
    }
  }
  return isneg ? -ret : ret;
}

unsigned long NmeaParser::parseDegrees(char *degree)
{
  char *p;
  unsigned long left_of_decimal = gpsatol(degree);
  unsigned long hundred1000ths_of_minute = (left_of_decimal % 100UL) * 100000UL;
  for (p=degree; gpsisdigit(*p); ++p);
  if (*p == '.') {
    unsigned long mult = 10000;
    while (gpsisdigit(*++p)) {
      hundred1000ths_of_minute += mult * (*p - '0');
      mult /= 10;
    }
  }
  return (left_of_decimal / 100) * 1000000 + (hundred1000ths_of_minute + 3) / 6;
}

time_t NmeaParser::convertDateAndTimeToEpochTime(
    unsigned long dateParam, // format ddmmyy
    unsigned long timeParam // format hhmmsscc
) {

  time_t rawtime;
  time(&rawtime);
  time_t localTimestamp = mktime(localtime(&rawtime));
  time_t utcTimestamp = mktime(gmtime(&rawtime));
  int localTimezone = (localTimestamp - utcTimestamp) / 3600;

  struct tm timeStruct;
  timeStruct.tm_mday = dateParam / 10000;
  timeStruct.tm_mon = ((dateParam - timeStruct.tm_mday * 10000) / 100);
  timeStruct.tm_year = dateParam - timeStruct.tm_mday * 10000 -  (timeStruct.tm_mon + 1) * 100 + 2000 - 1900;
  timeStruct.tm_hour = timeParam / 1000000;
  timeStruct.tm_min = (timeParam - timeStruct.tm_hour * 1000000) / 10000;
  timeStruct.tm_sec = (timeParam - timeStruct.tm_hour * 1000000 - timeStruct.tm_min * 10000) / 100;

  cout << "dateParam: " << dateParam << endl;
  cout << "tm_hour: " << timeStruct.tm_hour << endl;
  cout << "tm_min: " << (timeParam - timeStruct.tm_hour * 1000000) / 10000 << endl;
  cout << "tm_sec: " << (timeParam - timeStruct.tm_hour * 1000000 - timeStruct.tm_min * 10000) / 100 << endl;

  printf ( "The current date/time is: %s", asctime(&timeStruct));

  cout << "localTimezone: " << localTimezone << endl;
  cout << "timestamp: " << mktime(&timeStruct) << endl;
  cout << "localTimestamp: " << mktime(&timeStruct) - (localTimezone * 3600 * -1) << endl;

  return mktime(&timeStruct) - (localTimezone * 3600 * -1);
  // return mktime(&timeStruct);
}

struct tm * NmeaParser::getDatetime(int timezone)
{
  if (
    decodedData.date == 0
    || decodedData.time == 0
  ) {
    return NULL;
  }

  time_t t = convertDateAndTimeToEpochTime(decodedData.date, decodedData.time) - (timezone * 3600);
  return gmtime(&t);
}
