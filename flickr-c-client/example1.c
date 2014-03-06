/*
 * conversion in C of the example found at:
 * http://www.wackylabs.net/flickr/flickr-api/examples-part-1
 *
 */
#include "FlickrClient.h"

#include <stdlib.h>
#include <stdio.h>

static void example1(FlickrClient *c);

int main(int argc, char **argv) {
  FlickrClient *c = newFlickrClient(argv[1]);
  example1(c);
  deleteFlickrClient(c);
  return EXIT_SUCCESS;
}

static void example1_cb(void *userData, ...);

void example1(FlickrClient *c) {
  flickr_photos_search("newcastle", TagMode.All, NULL, NULL, &example1_cb);
}
