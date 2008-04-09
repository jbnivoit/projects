/*
 * conversion in C of the example found at:
 * http://www.wackylabs.net/flickr/flickr-api/examples-part-2
 *
 */
#include "FlickrClient.h"

#include <stdlib.h>
#include <stdio.h>

static void example2(FlickrClient *c);

int main(int argc, char **argv) {
  FlickrClient *c = newFlickrClient(argv[1]);
  example2(c);
  deleteFlickrClient(c);
  return EXIT_SUCCESS;
}

void example2(FlickrClient *c) {
  findingPeople(c);

  static void findingPeople(FlickrClient *c) {

There are a number of methods of finding people. Firstly if you know the users ÒusernameÓ or Òemail addressÓ you can use the find methods.


User user = flickr.PeopleFindByEmail(Ósam@wackylabs.netÓ);

or
User user = flickr.PeopleFindByUsername(ÓSam JudsonÓ);
or

User user = flickr.UrlsLookupUser(Óhttp://www.flickr.com/photos/samjudsonÓ);


(A quick note about ÒusernameÓ. My username is ÒSam JudsonÓ, this is not the same as my URL ÒaliasÓ which is ÒsamjudsonÓ Users can change their username therefore you should never rely on this information to stay the same. Store their user id once you have retrieved it and use that.)


Once you have obtained the User object you can examine its properties. First is the UserId property, e.g. Ò41888973@N00. This will not change for a given user and is used by all other methods that request user specific information. You can work out your own user id by looking at the RSS feed URL for your photos.


The other property available is the Username which contains the current username of the user.


One of the current problems with the FlickrNet API Library is that some properties of some objects are not always populated. This is one of those instances. The User object also contains a Url property, but the People* methods do not return this information and it is therefore null. I am trying to think of a sensible solution to this problem, if you have any ideas then let me know. I suspect it will cause a fairly large rewrite of some parts of the code at some point in the future.
Searching for Photos

To search for photos, either based on tags, text, dates or for a specific user (or a combination of the above) you can use the PhotosSearch method. This method has many overloaded calls, but a new on has been introduced to try and make this much easier.


PhotoSearchOptions options = new PhotoSearchOptions();
options.UserId = Ò41888973@N00; // Specify a particular user
options.Tags = Ònewcastle,bwÓ; // Comma delimited list of tags
options.PerPage = 50;


Photos photos = flickr.PhotosSearch(options);


The Photos class is quite complicated and requires a little explanation of its properties.


Photos.PageNumber - the page returned by the search
Photos.TotalPages - the total number of pages that the search could have returned.
Photos.PhotosPerPage - the number of photos per page
Photos.TotalPhotos - the total number of photos.

Photos.PhotoCollection - A collection (or array if you like) of Photo objects.


So if you search for a particular users photos, and they have 1125 photos, and you request 50 per page, the PhotosPerPage will obviously equal 50, TotalPhotos will equal 1125, PageNumber will be 1, and TotalPages will be 23.


Once you have the photos you can then loop through them using the PhotoCollection property.


foreach(Photo photo in photos.PhotoCollection)
{
    // Do something with the photo
    Console.WriteLine(Óphoto id = Ó + photo.PhotoId);
    Console.WriteLine(Óphoto title = Ó + photo.Title);

}

The PhotoCollection property can either be used as a collection, or a static array of Photo objects.


PhotoCollection collection = Photos.PhotoCollection;
Photo[] array = Photos.PhotoCollection;


If you have two collections of photos, they can be merged using the AddRange method.

collection1.AddRange(collection2); // collection1 now contains all photos from collection1 and collection2 - including duplicates.
The Effect of Authentication
Authentication has an effect on the results which are returned by quite a few methods. It is not actually REQUIRED, but if in place will change the result set. In the above example if the flickr object is created with a API token then this will be sent along with the search and the results will include photos that the user is authorised to see which might not be public (e.g. their own private photos or photos from friends and family which only they are allowed to view).

Wackylabs.Net is 2005 Sam. Rin by Khaled Abou Alfa and Joshua. You can syndicate
both the entries using RSS and the Comments (RSS) . xhtml 1.0 trans / CSS . Proudly powered by WordPress.

