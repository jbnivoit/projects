CC=cc
LD=cc -bind_at_load
#LD=ld -bind_at_load
GPERF=gperf -C
AR=ar
RANLIB=ranlib -s
CFLAGS=-g -Wall
LDFLAGS=
CURL_LIB=../webcollage/curl-7.15.0/lib/.libs/libcurl.a -lssl -lcrypto -lz
#CURL_LIB=-lcurl -lssl -lcrypto
#LIBS=$(CURL_LIB) -lexpat
LIBS=$(CURL_LIB) ../webcollage/expat-1.95.8/.libs/libexpat.a
#-lSystem

all : test_mapping_urls test_String test_test_echo test_test_login test_people_findByEmail test_people_findByUsername test_people_getInfo test_auth_getFrob test_auth_getToken test_hex test_photos_licenses_getInfo test_photos_search test_photos_getRecent favcol clockr

libFlickrClient.a : FlickrClientImpl_auth.o FlickrClientImpl_blogs.o FlickrClientImpl_contacts.o FlickrClientImpl_favorites.o FlickrClientImpl_groups.o FlickrClientImpl_groups_pools.o FlickrClientImpl_interestingness.o FlickrClientImpl_mapping_urls.o FlickrClientImpl_people.o FlickrClientImpl_photos.o FlickrClientImpl_photos_licenses.o FlickrClientImpl_photos_notes.o FlickrClientImpl_photos_transform.o FlickrClientImpl_photos_upload.o FlickrClientImpl_photosets.o FlickrClientImpl_reflection.o FlickrClientImpl_tags.o FlickrClientImpl_test.o FlickrClientImpl_urls.o String.o FlickrClientImpl.o FlickrRequest.o FlickrClientImpl_upload.o FlickrXmlHandler.o list.o Stack.o FlickrDate.o
	$(AR) -r libFlickrClient.a FlickrClientImpl_auth.o FlickrClientImpl_blogs.o FlickrClientImpl_contacts.o FlickrClientImpl_favorites.o FlickrClientImpl_groups.o FlickrClientImpl_groups_pools.o FlickrClientImpl_interestingness.o FlickrClientImpl_mapping_urls.o FlickrClientImpl_people.o FlickrClientImpl_photos.o FlickrClientImpl_photos_licenses.o FlickrClientImpl_photos_notes.o FlickrClientImpl_photos_transform.o FlickrClientImpl_photos_upload.o FlickrClientImpl_photosets.o FlickrClientImpl_reflection.o FlickrClientImpl_tags.o FlickrClientImpl_test.o FlickrClientImpl_urls.o String.o FlickrClientImpl.o FlickrRequest.o FlickrClientImpl_upload.o FlickrXmlHandler.o list.o Stack.o FlickrDate.o
	$(RANLIB) libFlickrClient.a

flickr_people_getInfo_gperf.c : flickr_people_getInfo.g
	$(GPERF) -t --hash-fn-name=hashGetInfoElement --word-array-name=getInfoWordList flickr_people_getInfo.g > flickr_people_getInfo_gperf.c 

flickr_photos_getInfo_gperf.c : flickr_photos_getInfo.g
	$(GPERF) -t --hash-fn-name=hashGetInfoElement --word-array-name=getInfoWordList flickr_photos_getInfo.g > flickr_photos_getInfo_gperf.c 

FlickrClient.h : String.h

FlickrClientImpl.h : FlickrClient.h

list.o : list.c list.h
	$(CC) $(CFLAGS) -o list.o -c list.c

Stack.o : Stack.c Stack.h list.h
	$(CC) $(CFLAGS) -o Stack.o -c Stack.c

FlickrRequest.o : FlickrRequest.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrRequest.o -c FlickrRequest.c

FlickrClientImpl.o : FlickrClientImpl.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl.o -c FlickrClientImpl.c

FlickrXmlHandler.o : FlickrXmlHandler.c FlickrXmlHandler.h
	$(CC) $(CFLAGS) -o FlickrXmlHandler.o -c FlickrXmlHandler.c

FlickrDate.o : FlickrDate.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrDate.o -c FlickrDate.c

FlickrClientImpl_auth.o : FlickrClientImpl_auth.c FlickrClientImpl.h FlickrXmlHandler.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_auth.o -c FlickrClientImpl_auth.c

FlickrClientImpl_blogs.o : FlickrClientImpl_blogs.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_blogs.o -c FlickrClientImpl_blogs.c

FlickrClientImpl_contacts.o : FlickrClientImpl_contacts.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_contacts.o -c FlickrClientImpl_contacts.c

FlickrClientImpl_favorites.o : FlickrClientImpl_favorites.c FlickrClientImpl.h FlickrXmlHandler.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_favorites.o -c FlickrClientImpl_favorites.c

FlickrClientImpl_groups.o : FlickrClientImpl_groups.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_groups.o -c FlickrClientImpl_groups.c

FlickrClientImpl_groups_pools.o : FlickrClientImpl_groups_pools.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_groups_pools.o -c FlickrClientImpl_groups_pools.c

FlickrClientImpl_interestingness.o : FlickrClientImpl_interestingness.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_interestingness.o -c FlickrClientImpl_interestingness.c

FlickrClientImpl_mapping_urls.o : FlickrClientImpl_mapping_urls.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_mapping_urls.o -c FlickrClientImpl_mapping_urls.c

FlickrClientImpl_people.o : FlickrClientImpl_people.c FlickrClientImpl.h flickr_people_getInfo_gperf.c
	$(CC) $(CFLAGS) -o FlickrClientImpl_people.o -c FlickrClientImpl_people.c

FlickrClientImpl_photos.o : FlickrClientImpl_photos.c FlickrClientImpl.h flickr_photos_getInfo_gperf.c FlickrXmlHandler.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_photos.o -c FlickrClientImpl_photos.c

FlickrClientImpl_photos_licenses.o : FlickrClientImpl_photos_licenses.c FlickrClientImpl.h FlickrXmlHandler.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_photos_licenses.o -c FlickrClientImpl_photos_licenses.c

FlickrClientImpl_photos_notes.o : FlickrClientImpl_photos_notes.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_photos_notes.o -c FlickrClientImpl_photos_notes.c

FlickrClientImpl_photos_transform.o : FlickrClientImpl_photos_transform.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_photos_transform.o -c FlickrClientImpl_photos_transform.c

FlickrClientImpl_photos_upload.o : FlickrClientImpl_photos_upload.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_photos_upload.o -c FlickrClientImpl_photos_upload.c

FlickrClientImpl_photosets.o : FlickrClientImpl_photosets.c FlickrClientImpl.h FlickrXmlHandler.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_photosets.o -c FlickrClientImpl_photosets.c

FlickrClientImpl_reflection.o : FlickrClientImpl_reflection.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_reflection.o -c FlickrClientImpl_reflection.c

FlickrClientImpl_tags.o : FlickrClientImpl_tags.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_tags.o -c FlickrClientImpl_tags.c

FlickrClientImpl_test.o : FlickrClientImpl_test.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_test.o -c FlickrClientImpl_test.c

FlickrClientImpl_urls.o : FlickrClientImpl_urls.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_urls.o -c FlickrClientImpl_urls.c

FlickrClientImpl_upload.o : FlickrClientImpl_upload.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o FlickrClientImpl_upload.o -c FlickrClientImpl_upload.c

String.o : String.c String.h
	$(CC) $(CFLAGS) -o String.o -c String.c

example1.o : example1.c FlickrClient.h
	$(CC) $(CFLAGS) -o example1.o -c example1.c

example2.o : example2.c FlickrClient.h
	$(CC) $(CFLAGS) -o example2.o -c example2.c

test.o : test.c test.h
	$(CC) $(CFLAGS) -o test.o -c test.c

test_mapping_urls.o : test_mapping_urls.c FlickrClient.h
	$(CC) $(CFLAGS) -o test_mapping_urls.o -c test_mapping_urls.c

test_mapping_urls : test_mapping_urls.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_mapping_urls test_mapping_urls.o libFlickrClient.a $(LIBS)

test_test_echo.o : test_test_echo.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_test_echo.o -c test_test_echo.c

test_test_echo : test_test_echo.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_test_echo test_test_echo.o test.o libFlickrClient.a $(LIBS)

test_test_login.o : test_test_login.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_test_login.o -c test_test_login.c

test_test_login : test_test_login.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_test_login test_test_login.o test.o libFlickrClient.a $(LIBS)

test_photos_search.o : test_photos_search.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_photos_search.o -c test_photos_search.c

test_photos_search : test_photos_search.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_photos_search test_photos_search.o test.o libFlickrClient.a $(LIBS)

test_photos_getRecent.o : test_photos_getRecent.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_photos_getRecent.o -c test_photos_getRecent.c

test_photos_getRecent : test_photos_getRecent.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_photos_getRecent test_photos_getRecent.o test.o libFlickrClient.a $(LIBS)

test_photos_licenses_getInfo.o : test_photos_licenses_getInfo.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_photos_licenses_getInfo.o -c test_photos_licenses_getInfo.c

test_photos_licenses_getInfo : test_photos_licenses_getInfo.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_photos_licenses_getInfo test_photos_licenses_getInfo.o test.o libFlickrClient.a $(LIBS)

test_people_findByEmail.o : test_people_findByEmail.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_people_findByEmail.o -c test_people_findByEmail.c

test_people_findByEmail : test_people_findByEmail.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_people_findByEmail test_people_findByEmail.o test.o libFlickrClient.a $(LIBS)

test_people_findByUsername.o : test_people_findByUsername.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_people_findByUsername.o -c test_people_findByUsername.c

test_people_findByUsername : test_people_findByUsername.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_people_findByUsername test_people_findByUsername.o test.o libFlickrClient.a $(LIBS)

test_people_getInfo.o : test_people_getInfo.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_people_getInfo.o -c test_people_getInfo.c

test_people_getInfo : test_people_getInfo.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_people_getInfo test_people_getInfo.o test.o libFlickrClient.a $(LIBS)

test_auth_getFrob.o : test_auth_getFrob.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_auth_getFrob.o -c test_auth_getFrob.c

test_auth_getFrob : test_auth_getFrob.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_auth_getFrob test_auth_getFrob.o test.o libFlickrClient.a $(LIBS)

test_auth_getToken.o : test_auth_getToken.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o test_auth_getToken.o -c test_auth_getToken.c

test_auth_getToken : test_auth_getToken.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_auth_getToken test_auth_getToken.o test.o libFlickrClient.a $(LIBS)

test_String.o : test_String.c String.h
	$(CC) $(CFLAGS) -o test_String.o -c test_String.c

test_String : test_String.o test.o String.o
	$(LD) $(LDFLAGS) -o test_String test_String.o String.o $(LIBS)

test_hex.o : test_hex.c FlickrClientImpl.h
	$(CC) $(CFLAGS) -o test_hex.o -c test_hex.c

test_hex : test_hex.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o test_hex test_hex.o libFlickrClient.a $(LIBS)

favcol.o : favcol.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o favcol.o -c favcol.c

favcol : favcol.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o favcol favcol.o test.o libFlickrClient.a $(LIBS)

clockr.o : clockr.c FlickrClient.h test.h
	$(CC) $(CFLAGS) -o clockr.o -c clockr.c

clockr : clockr.o test.o libFlickrClient.a
	$(LD) $(LDFLAGS) -o clockr clockr.o test.o libFlickrClient.a $(LIBS)

clean :
	$(RM) *.o *.a flickr_people_getInfo_gperf.c flickr_photos_getInfo_gperf.c test_mapping_urls test_String test_test_echo test_test_login test_people_findByEmail test_people_findByUsername test_people_getInfo test_auth_getFrob test_auth_getToken test_hex test_photos_licenses_getInfo test_photos_search test_photos_getRecent favcol clockr
