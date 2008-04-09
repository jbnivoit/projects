#include "FlickrClientImpl.h"

const char *dateTakenGranularity(unsigned int date_taken_granularity)
{
  switch(date_taken_granularity) {
  case 6: return "6";
  case 4: return "4";
  case 0:
  default: return "0";
  }
}

const char *date(FlickrClient *client, time_t dateval)
{
  return makeIntString(client,dateval);
}
