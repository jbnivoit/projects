/* -*- C -*- */
#ifndef _FlickrClient_H
#define _FlickrClient_H

#include <sys/time.h>

#include "String.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FLICKR_API 

struct FlickrClient;
typedef struct FlickrClient FlickrClient;

  /*
   * Create a new Flickr client object per thread you intend to use it from.
   * Those objects are not shareable between threads.
   */
extern FlickrClient * FLICKR_API newFlickrClient(const char apiKey[32], const char secret[16]);
extern void FLICKR_API deleteFlickrClient(FlickrClient *client);

typedef struct FlickrPhotoContext FlickrPhotoContext;
struct FlickrPhotoContext {
  unsigned int m_id;
  String m_secret;
  String m_title;
  String m_url;
};

typedef unsigned int FlickrResult;
typedef unsigned int FlickrLicenseId;

typedef enum {
  PRIVACY_PRIVATE=1,
  PRIVATE_INVITE_ONLY=2,
  PRIVATE_OPEN=3
} FlickrPrivacyLevel;

typedef enum {
  PHOTO_SZ_SMALLEST,
  PHOTO_SZ_SMALL,
  PHOTO_SZ_THUMBNAIL,
  PHOTO_SZ_MEDIUM,
  PHOTO_SZ_LARGE,
  PHOTO_SZ_ORIGINAL
} FlickrPhotoSize;

typedef enum {
  FORMAT_JPG,
  FORMAT_GIF,
  FORMAT_PNG
} FlickrPhotoFormat;

typedef enum {
  FLICKR_INVALID_ARG=1,
  FLICKR_CATEGORY_NOT_FOUND=1,
  FLICKR_PHOTO_NOT_FOUND=1,
  FLICKR_USER_NOT_FOUND=1,
  FLICKR_BLOG_NOT_FOUND=1,
  FLICKR_TAG_NOT_FOUND=1,
  FLICKR_MINITOKEN_NOT_FOUND=1,
  FLICKR_PHOTO_OWNED_BY_YOU=2,
  FLICKR_MAX_NUMBER_OF_TAGS_REACHED=2,
  FLICKR_NOT_ENOUGH_ARGS=2,
  FLICKR_PHOTO_ALREADY_IN_FAVORITES=3,
  FLICKR_PASSWORD_NEEDED=3,
  FLICKR_INVALID_GRANULARITY=3,
  FLICKR_USER_CANNOT_SEE_PHOTO=4,
  FLICKR_BLOG_POST_FAILED=4,
  FLICKR_INVALID_SIGNATURE=96,
  FLICKR_MISSING_SIGNATURE=97,
  FLICKR_LOGIN_FAILED=98,
  FLICKR_USER_NOT_LOGGED_IN=99,
  FLICKR_INVALID_API_KEY=100,
  FLICKR_SERVICE_CURRENTLY_UNAVAILABLE=105,
  FLICKR_INVALID_FROB=108,
  FLICKR_FORMAT_NOT_FOUND=111,
  FLICKR_METHOD_NOT_FOUND=112,
  FLICKR_INVALID_SOAP_ENVELOPE=114,
  FLICKR_INVALID_XMLRPC_METHOD_CALL=115
} FlickrResultValue;

typedef enum {
  NONE=0,
  LICENSE         = 1<<0, 
  DATE_UPLOAD     = 1<<1, 
  DATE_TAKEN      = 1<<2, 
  OWNER_NAME      = 1<<3, 
  ICON_SERVER     = 1<<4, 
  ORIGINAL_FORMAT = 1<<5, 
  LAST_UPDATE     = 1<<6
} FlickrPhotoExtras;

typedef enum { /* must be set so we can combine it with FlickrPhotoExtras */
  JUST_FRIENDS  = 1<<7,
  SINGLE_PHOTO  = 1<<8,
  INCLUDE_SELF  = 1<<9
} FlickrContactFlags;

struct FlickrPhoto {
  unsigned int m_id;
  String m_secret;
  String m_server;
  unsigned char m_isprimary;
  unsigned char m_ispublic;
  unsigned char m_isfriend;
  unsigned char m_isfamily;
  String m_title;
  String m_description;
  String m_username;
  String m_owner;
};
typedef struct FlickrPhoto FlickrPhoto;

typedef String FlickrCategoryId;
typedef String FlickrGroupId;

typedef enum {
  PERM_NONE,
  PERM_READ,
  PERM_WRITE,
  PERM_DELETE
} FlickrPerm;

typedef enum {
  PERM_NOBODY=0,
  PERM_FRIENDS_AND_FAMILY=1,
  PERM_CONTACTS=2,
  PERM_EVERYBODY=3
} FlickrPermScope;

typedef enum { 
  TAG_MODE_OR, 
  TAG_MODE_AND,
  TAG_MODE_ANY=TAG_MODE_OR,
  TAG_MODE_ALL=TAG_MODE_AND
} FlickrTagMode;

typedef enum {
  SORT_UNSET=0,
  SORT_DATE_POSTED_ASC, 
  SORT_DATE_POSTED_DESC, 
  SORT_DATE_TAKEN_ASC, 
  SORT_DATE_TAKEN_DESC, 
  SORT_INTERESTINGNESS_DESC, 
  SORT_INTERESTINGNESS_ASC, 
  SORT_RELEVANCE
} FlickrSortOrder;

typedef struct FlickrPhotos FlickrPhotos;
struct FlickrPhotos {
  unsigned int m_page;
  unsigned int m_pages;
  unsigned int m_perpage;
  unsigned int m_total;
  FlickrPhoto *m_photos;
};

/* auth methods */
typedef struct FlickrUser FlickrUser;
struct FlickrUser {
  String m_nsid;
  String m_username;
  String m_fullname;
};
extern void FLICKR_API FlickrUser_Init(FlickrUser *p);
extern void FLICKR_API FlickrUser_Destroy(FlickrUser *p);
extern void FLICKR_API FlickrUser_Copy(FlickrUser *dest, const FlickrUser *src);

typedef char FlickrMiniToken[9];
typedef String FlickrAuthToken;

typedef struct FlickrPhotoNote FlickrPhotoNote;
struct FlickrPhotoNote {
  unsigned int x, y, w, h;
  String text;
  
  String m_id;
  String m_author;
  String m_authorname;
};

struct FlickrTag {
  unsigned m_id;
  String m_author;
  String m_authorname;
  String m_raw;
  String m_tagbody;
};
typedef struct FlickrTag FlickrTag;

extern FlickrResult FLICKR_API flickr_auth_checkToken(FlickrClient *client,
				    const FlickrAuthToken *auth_token,
				    void *userData,
				    void (*cb)(void *userData, const String *token, 
					       FlickrPerm perm, const FlickrUser *user));

extern FlickrResult FLICKR_API flickr_auth_getFrob(FlickrClient *client, String *oFrob);
extern void FLICKR_API flickr_auth_url(FlickrClient *client, String *iFrob, FlickrPerm iPerm, String *oUrl);
extern void FLICKR_API flickr_set_authentication_token(FlickrClient *client, const String *token);

extern FlickrResult FLICKR_API flickr_auth_getFullToken(FlickrClient *client,
				      const FlickrMiniToken mini_token,
				      void *userData,
				      void (*cb)(void *userData, const String *token, 
						 FlickrPerm perm, const FlickrUser *user));

extern FlickrResult FLICKR_API flickr_auth_getToken(FlickrClient *client,
				  const String *frob,
				  void *userData,
				  void (*cb)(void *userData, const String *token, 
					     FlickrPerm perm, const FlickrUser *user));

/* blogs methods */
typedef struct FlickrBlog FlickrBlog;
typedef String FlickrBlogId;
typedef String FlickrPhotoId;
typedef String FlickrPhotosetId;
struct FlickrBlog {
  FlickrBlogId  m_id;
  String        m_name;
  unsigned char m_needspassword;
  String        m_url;
};

extern FlickrResult FLICKR_API flickr_blogs_getList(FlickrClient *client, void *userData, void (*cb)(void *userData, const FlickrBlog *blog));
extern FlickrResult FLICKR_API flickr_blogs_postPhoto(FlickrClient *client,
				    const FlickrBlogId  *blog_id,
				    const FlickrPhotoId *photo_id,
				    const String *title,
				    const String *description,
				    const String *blog_password);

/* contacts methods */
typedef enum {
  FLICKR_CONTACT_FRIENDS,
  FLICKR_CONTACT_FAMILY,
  FLICKR_CONTACT_BOTH,
  FLICKR_CONTACT_NEITHER
} FlickrContactFilter;

typedef struct FlickrContact FlickrContact;
struct FlickrContact {
  String m_nsid;
  String m_username;
  String m_realname;
  unsigned char m_iconserver;
  unsigned char m_friend;
  unsigned char m_family;
  unsigned char m_ignored;
};

typedef struct FlickrGroup FlickrGroup;
struct FlickrGroup {
  String m_nsid;
  String m_name;
  String m_description;
  unsigned int m_members;
  unsigned char m_online;
  unsigned char m_inchat;
  unsigned char m_privacy;
  String m_chatnsid;
};

typedef struct FlickrGroups FlickrGroups;
typedef struct FlickrGroupInGroups FlickrGroupInGroups;

struct FlickrGroupInGroups {
  String m_nsid;
  String m_name;
  unsigned char m_eighteenplus;
};
struct FlickrGroups {
  unsigned int m_page;
  unsigned int m_pages;
  unsigned int m_perpage;
  unsigned int m_total;
  FlickrGroupInGroups *m_groups;
};

extern FlickrResult FLICKR_API flickr_contacts_getList(FlickrClient *client, 
			     FlickrContactFilter filter, 
			     void *userData,
			     void (*cb)(void *userData, const FlickrContact *contact));
extern FlickrResult FLICKR_API flickr_contacts_getPublicList(FlickrClient *client,
				   const String *user_id,
				   void *userData,
				   void (*cb)(void *userData, const FlickrContact *contact));

/* favorites methods */

extern FlickrResult FLICKR_API flickr_favorites_add(FlickrClient *client, const FlickrPhotoId *photo_id);

typedef struct FlickrResultPage FlickrResultPage;
struct FlickrResultPage {
  unsigned int m_page;
  unsigned int m_pages;
  unsigned int m_perpage;
  unsigned int m_total;
};

extern FlickrResult FLICKR_API flickr_favorites_getList(FlickrClient *client,
					    const String *user_id, 
					    FlickrPhotoExtras extras,
					    unsigned int per_page,
					    unsigned int page,
					    void *userData,
					    void (*cb)(void *userData, const FlickrResultPage *page,
						       unsigned int offset, const FlickrPhoto *photo));

extern FlickrResult FLICKR_API flickr_favorites_getPublicList(FlickrClient *client,
					    const String *user_id, 
					    FlickrPhotoExtras extras,
					    unsigned int per_page,
					    unsigned int page,
					    void *userData,
					    void (*cb)(void *userData, const FlickrResultPage *page,
						       unsigned int offset, const FlickrPhoto *photo));

extern FlickrResult FLICKR_API flickr_favorites_remove(FlickrClient *client, const FlickrPhotoId *photo_id);

/* groups methods */

extern FlickrResult FLICKR_API flickr_groups_browse(FlickrClient *client,
						    FlickrCategoryId *cat_id,
						    void *userData,
						    void (*subcatCb)(void *userData, FlickrCategoryId *cat_id,
								     String *name, unsigned int count),
						    void (*groupCb)(void *userData, FlickrGroup *group));
  
extern FlickrResult FLICKR_API flickr_groups_getInfo(FlickrClient *client,
						     FlickrGroupId group_id,
						     FlickrGroup *group);

extern FlickrResult FLICKR_API flickr_groups_search(FlickrClient *client,
						    String *text,
						    unsigned int per_page,
						    unsigned int page,
						    void *userData,
						    void (*groupsCb)(void *userData, FlickrGroups *groups));

/* groups_pools methods */

extern FlickrResult FLICKR_API flickr_groups_pools_add(FlickrClient *client,
						       const FlickrPhotoId *photo_id, 
						       const FlickrGroupId *group_id);
extern FlickrResult FLICKR_API flickr_groups_pools_getContext(FlickrClient *client,
							      const FlickrPhotoId *photo_id, 
							      const FlickrGroupId *group_id,
							      void *userData,
							      void (*cb)(void *userData,
									 const FlickrPhotoContext *prev,
									 const FlickrPhotoContext *next));

typedef struct FlickrPoolGroup FlickrPoolGroup;
struct FlickrPoolGroup {
  String m_nsid;
  String m_name;
  unsigned char m_admin;
  unsigned char m_privacy;
  unsigned char m_iconserver;
  unsigned int m_photos;
};

extern FlickrResult FLICKR_API flickr_groups_pools_getGroups(FlickrClient *client,
					   void *userData,
					   void (*cb)(void *userData, const FlickrPoolGroup *group));

typedef struct FlickrPoolPhoto FlickrPoolPhoto;
struct FlickrPoolPhoto {
  unsigned int m_id;
  String m_owner;
  String m_title;
  unsigned char m_ispublic;
  unsigned char m_isfriend;
  unsigned char m_isfamily;
  String m_ownername;
  struct timeval m_dateadded;
};

extern FlickrResult FLICKR_API flickr_groups_pools_getPhotos(FlickrClient *client,
					   const FlickrGroupId *group_id,
					   const String *tag,
					   const String *user_id,
					   int extras,
					   unsigned int per_page,
					   unsigned int page,
					   void *userData,
					   void (*cb)(void *userData, const FlickrPoolPhoto *photo));

extern FlickrResult FLICKR_API flickr_groups_pools_remove(FlickrClient *client,
					const FlickrPhotoId *photo_id, const FlickrGroupId *group_id);

/* interestingness methods */

extern FlickrResult FLICKR_API flickr_interestingness_getList(FlickrClient *client,
					    char date[7],
					    int extras,
					    unsigned int per_page, unsigned int page,
					    unsigned int *total,
					    void *userData,
					    void (*cb)(void *userData, FlickrPoolPhoto *photo));


/* people methods */

extern FlickrResult FLICKR_API flickr_people_findByEmail(FlickrClient *client,
				       const String *find_email,
				       String *nsid, String *username);

extern FlickrResult FLICKR_API flickr_people_findByUsername(FlickrClient *client,
				       const String *iUsername,
				       String *nsid, String *oUsername);
					  
typedef struct FlickrPerson FlickrPerson;
struct FlickrPerson {
  String m_nsid;
  unsigned char m_isadmin;
  unsigned char m_ispro;
  unsigned char m_iconserver;
  String m_username;
  String m_realname;
  String m_mbox_sha1sum;
  String m_location;
  String m_photosurl;
  String m_profileurl;
  time_t m_firstdate;
  String m_firstdatetaken;
  unsigned int m_count;
};

extern FlickrResult FLICKR_API flickr_people_getInfo(FlickrClient *client, const String *nsid, 
				   void *userData,
				   void (*cb)(void *userData, const FlickrPerson *oInfo));

extern FlickrResult FLICKR_API flickr_people_getPublicGroups(FlickrClient *client, const String *nsid,
					   void *userData,
					   void (*groupsCb)(void *userData, const FlickrGroups *groups));

extern FlickrResult FLICKR_API flickr_people_getPublicPhotos(FlickrClient *client, const String *nsid,
					   int extras,
					   unsigned int per_page, unsigned int page, 
					   void *userData,
					   void (*cb)(void *userData, const FlickrPhotos *photos));

typedef struct FlickrUploadStatus FlickrUploadStatus;
struct FlickrUploadStatus {
  unsigned int m_max;
  unsigned int m_used;
  unsigned int m_filesize_max;
};
extern FlickrResult FLICKR_API flickr_people_getUploadStatus(FlickrClient *client,
							     String *id,
							     unsigned char *ispro,
							     String *username,
							     FlickrUploadStatus *status);

/* photos methods */

extern FlickrResult FLICKR_API flickr_photos_addTags(FlickrClient *client,
						     const FlickrPhotoId *photo_id,
						     unsigned int count,
						     String *tags);

extern FlickrResult FLICKR_API flickr_photos_delete(FlickrClient *client,
						    const FlickrPhotoId *photo_id);

extern FlickrResult FLICKR_API flickr_photos_getAllContexts(FlickrClient *client,
							    const FlickrPhotoId *photo_id,
							    void *userData,
							    void (*setCb)(void *userData, const String *id, const String *title),
							    void (*poolCb)(void *userData, const String *id, const String *title));

extern FlickrResult FLICKR_API flickr_photos_getContactsPhotos(FlickrClient *client,
							       unsigned int count,
							       int flags_and_extras,
							       void *userData,
							       void (*cb)(void *userData, 
									  const FlickrResultPage *page,
									  unsigned int offset, 
									  const FlickrPhoto *photo));

extern FlickrResult FLICKR_API flickr_photos_getContactsPublicPhotos(FlickrClient *client,
							       unsigned int count,
							       int flags_and_extras,
							       void *userData,
							       void (*cb)(void *userData, 
									  const FlickrResultPage *page,
									  unsigned int offset, 
									  const FlickrPhoto *photo));

extern FlickrResult FLICKR_API flickr_photos_getContext(FlickrClient *client,
				      FlickrPhotoId *photo_id,
				      void *userData,
				      void (*cb)(void *userData,
						 FlickrPhotoContext *prev,
						 FlickrPhotoContext *next));

typedef struct FlickrPhotoCount FlickrPhotoCount;
struct FlickrPhotoCount {
  unsigned int m_count;
  time_t m_fromdate, m_todate;
};

extern FlickrResult FLICKR_API flickr_photos_getCounts(FlickrClient *client,
				     unsigned int dates_count,
				     time_t *dates,
				     unsigned int taken_dates_count,
				     time_t *taken_dates,
				     void *userData,
				     void (*cb)(void *userData, FlickrPhotoCount *photocount));

typedef struct FlickrPhotoExifData FlickrPhotoExifData;
typedef struct ExifItem ExifItem;
struct ExifItem {
  String m_tagspace;
  unsigned int m_tag;
  String m_label;
  String m_raw;
};
struct FlickrPhotoExifData {
  unsigned int m_id;
  String m_secret;
  unsigned int m_server;
  unsigned int m_items_count;
  ExifItem *m_items;
};

extern FlickrResult FLICKR_API flickr_photos_getExif(FlickrClient *client,
				   const FlickrPhotoId *photo_id,
				   String *secret,
				   void *userData,
				   void (*cb)(void *userData, FlickrPhotoExifData *exif));

typedef struct FlickrPhotoOwner FlickrPhotoOwner;
struct FlickrPhotoOwner {
  String m_nsid;
  String m_username;
  String m_realname;
  String m_location;
};
typedef struct FlickrPhotoVisibility FlickrPhotoVisibility;
struct FlickrPhotoVisibility {
  unsigned char m_is_public;
  unsigned char m_is_friend;
  unsigned char m_is_family;
};

typedef struct FlickrPhotoDates FlickrPhotoDates;
struct FlickrPhotoDates {
  time_t m_posted;
  String m_taken;
  unsigned char m_takengranularity;
  time_t m_lastupdate;
};

typedef struct FlickrPhotoInfo FlickrPhotoInfo;
struct FlickrPhotoInfo {
  String m_id;
  String m_secret;
  String m_server;
  unsigned char m_isfavorite;
  FlickrLicenseId m_license;
  FlickrPhotoFormat m_originalformat;
  unsigned int m_rotation;
  
  FlickrPhotoOwner m_owner;
  String m_title;
  String m_description;
  FlickrPhotoVisibility m_visibility;
  FlickrPhotoDates m_dates;

  FlickrPermScope m_permcomment, m_permaddmeta;
  unsigned char m_cancomment, m_canaddmeta;
  
  FlickrPhotoNote **m_notes;
  unsigned int m_notes_sz;

  FlickrTag **m_tags;
  unsigned int m_tags_sz;

  String m_photopage;
};

extern FlickrResult FLICKR_API flickr_photos_getInfo(FlickrClient *client,
						     const FlickrPhotoId *photo_id,
						     const String *secret,
						     void *userData,
						     void (*cb)(void *userData,
								const FlickrPhotoInfo *info));

typedef struct FlickrDateSearchCriteria FlickrDateSearchCriteria;
struct FlickrDateSearchCriteria {
  time_t m_min_upload_date;
  time_t m_max_upload_date;
  time_t m_min_taken_date;
  time_t m_max_taken_date;
};
extern void FLICKR_API FlickrDateSearchCriteria_Init(FlickrDateSearchCriteria *);
extern void FLICKR_API FlickrDateSearchCriteria_Destroy(FlickrDateSearchCriteria *);

extern FlickrResult FLICKR_API flickr_photos_getNotInSet(FlickrClient *client,
							 FlickrDateSearchCriteria *date_criteria,
							 unsigned int extras,
							 unsigned int per_page,
							 unsigned int page,
							 void *userData,
							 void (*cb)(void *userData, 
								    const FlickrResultPage *page,
								    unsigned int offset, 
								    const FlickrPhoto *photo));

typedef struct FlickrPhotoPerms FlickrPhotoPerms;
struct FlickrPhotoPerms {
  FlickrPhotoVisibility m_visibility;
  FlickrPermScope m_permcomment, m_permaddmeta;
  
};

extern FlickrResult FLICKR_API flickr_photos_getPerms(FlickrClient *client,
						      const String *photo_id,
						      FlickrPhotoPerms *perms);

extern FlickrResult FLICKR_API flickr_photos_getRecent(FlickrClient *client,
						       FlickrPhotoExtras extras,
						       unsigned int per_page,
						       unsigned int page,
						       void *userData,
						       void (*cb)(void *userData, const FlickrResultPage *page,
								  unsigned int offset, const FlickrPhoto *photo));

typedef struct FlickrSize FlickrSize;
struct FlickrSize {
  String m_label;
  unsigned int m_width, m_height;
  String m_source, m_url;
};

extern FlickrResult FLICKR_API flickr_photos_getSizes(FlickrClient *client,
						      const FlickrPhotoId *photo_id,
						      void *userData,
						      void (*cb)(void *userData, const FlickrSize *sz));
		
extern FlickrResult FLICKR_API flickr_photos_getUntagged(FlickrClient *client,
							 FlickrDateSearchCriteria *criteria,
							 FlickrPhotoExtras extras,
							 unsigned int per_page,
							 unsigned int page,
							 void *userData,
							 void (*cb)(void *userData, const FlickrResultPage *page,
								    unsigned int offset, const FlickrPhoto *photo));

extern FlickrResult FLICKR_API flickr_photos_removeTag(FlickrClient *client,
						       const String *tag_id);

typedef struct FlickrSearchCriteria FlickrSearchCriteria;
struct FlickrSearchCriteria {
  String m_user_id;
  String *m_tags;
  unsigned int m_tagsz;
  FlickrTagMode m_tagmode;
  String m_text; 
  FlickrDateSearchCriteria m_date_criteria;
  FlickrLicenseId m_license;
  FlickrSortOrder m_sort;
  unsigned int m_extras;
  unsigned int m_per_page;
  unsigned int m_page;
};
extern void FLICKR_API FlickrSearchCriteria_Init(FlickrSearchCriteria *);
extern void FLICKR_API FlickrSearchCriteria_Destroy(FlickrSearchCriteria *);

extern FlickrResult FLICKR_API flickr_photos_search(FlickrClient *client,
						    const FlickrSearchCriteria *criteria,
						    void *userData,
						    void (*cb)(void *userData, 
							       const FlickrResultPage *page,
							       unsigned int offset, 
							       const FlickrPhoto *photo));

typedef enum {
  ARG_NONE=0,
  ARG_1 = 1<<1,
  ARG_2 = 1<<2,
  ARG_3 = 1<<3
} FlickrArgMask;

extern FlickrResult FLICKR_API flickr_photos_setDates(FlickrClient *client,
						      const FlickrPhotoId *photo_id,
						      FlickrArgMask mask,
						      time_t date_posted,
						      time_t date_taken,
						      unsigned int date_taken_granularity);

  extern FlickrResult FLICKR_API flickr_photos_setMeta(FlickrClient *client,
						       const FlickrPhotoId *photo_id,
						       const String *title,
						       const String *description);

extern FlickrResult FLICKR_API flickr_photos_setPerms(FlickrClient *client,
						      const FlickrPhotoId *photo_id,
						      const FlickrPhotoVisibility *scope,
						      FlickrPermScope perm_comment,
						      FlickrPermScope perm_addmeta);

extern FlickrResult FLICKR_API flickr_photos_setTags(FlickrClient *client,
						     const FlickrPhotoId *photo_id,
						     const String *tags,
						     unsigned int tagssz);

/* photos_licenses methods */
typedef struct FlickrLicense FlickrLicense;
struct FlickrLicense {
  FlickrLicenseId m_id;
  String m_name;
  String m_url;
};

extern FlickrResult FLICKR_API flickr_photos_licenses_getInfo(FlickrClient *client,
							      void *userData,
							      void (*cb)(void *userData, const FlickrLicense *lic));

extern FlickrResult FLICKR_API flickr_photos_licenses_setLicense(FlickrClient *client,
								 const FlickrPhotoId *photo_id,
								 const unsigned int license_id);

/* photos_notes methods */

extern FlickrResult FLICKR_API flickr_photos_notes_add(FlickrClient *client,
						       const FlickrPhotoId *photo_id,
						       const FlickrPhotoNote *note,
						       String *id);
							 
extern FlickrResult FLICKR_API flickr_photos_notes_delete(FlickrClient *client, const String *note_id);

extern FlickrResult FLICKR_API flickr_photos_notes_edit(FlickrClient *client,
							const String *note_id,
							const FlickrPhotoNote *note,
							String *id);

/* photos_transform methods */

extern FlickrResult FLICKR_API flickr_photos_transform_rotate(FlickrClient *client, 
					    const FlickrPhotoId *photo_id,
					    unsigned int degrees);
  
/* photos_upload methods */
typedef enum {
  TICKET_NOT_COMPLETED=0,
  TICKET_COMPLETED=1,
  TICKET_FAILED=2
} FlickrTicketStatus;

typedef struct FlickrTicket FlickrTicket;
struct FlickrTicket {
  String m_id;
  unsigned char m_complete;
  unsigned char m_invalid;
  String m_photoid;
};

extern FlickrResult FLICKR_API flickr_photos_upload_checkTickets(FlickrClient *client,
								 const String *tickets,
								 unsigned int sz,
								 void *userData,
								 void (*cb)(void *userData, const FlickrTicket *ticket));

/* photosets methods */
typedef struct FlickrPhotoset FlickrPhotoset;
struct FlickrPhotoset {
  String m_id;
  String m_primary;
  String m_secret;
  String m_server;
  unsigned int m_photos;
  String m_title;
  String m_description;
  String m_owner;
};

extern FlickrResult FLICKR_API flickr_photosets_addPhoto(FlickrClient *client,
							 const FlickrPhotosetId *photoset_id,
							 const FlickrPhotoId *photo_id);

extern FlickrResult FLICKR_API flickr_photosets_create(FlickrClient *client,
						       const String *title,
						       const String *description,
						       const FlickrPhotoId *primary_photo_id,
						       FlickrPhotosetId *id,
						       String *url);

extern FlickrResult FLICKR_API flickr_photosets_delete(FlickrClient *client,
						       const FlickrPhotosetId *photoset_id);
  
extern FlickrResult FLICKR_API flickr_photosets_editMeta(FlickrClient *client,
							 const FlickrPhotosetId *photoset_id,
							 const String *title,
							 const String *description);


extern FlickrResult FLICKR_API flickr_photosets_editPhotos(FlickrClient *client,
							   const FlickrPhotosetId *photoset_id,
							   const FlickrPhotoId *primary_photo_id,
							   const unsigned int photo_ids_sz,
							   const FlickrPhotoId *photo_ids);

extern FlickrResult FLICKR_API flickr_photosets_getContext(FlickrClient *client,
							   const FlickrPhotoId *photo_id,
							   const FlickrPhotosetId *photoset_id,
					 void *userData,
					 void (*cb)(void *userData,
						    FlickrPhotoContext *prev,
						    FlickrPhotoContext *next));

extern FlickrResult FLICKR_API flickr_photosets_getInfo(FlickrClient *client,
							const FlickrPhotosetId *photoset_id,
							FlickrPhotoset *photoset);

extern unsigned char FLICKR_API flickr_photosets_getList(FlickrClient *client, 
							 const String *user_id, 
							 void *userData, 
							 void (*cb)(void *userData, const FlickrPhotoset *set));

extern FlickrResult FLICKR_API flickr_photosets_getPhotos(FlickrClient *client, 
					FlickrPhotosetId photoset_id,
					int extras,
					void *userData,
					void (*cb)(void *userData, String *id, String *primary, FlickrPhoto *photo));

extern FlickrResult FLICKR_API flickr_photosets_orderSets(FlickrClient *client,
							  const unsigned int photoset_ids_sz,
							  const FlickrPhotosetId *photoset_ids);

extern FlickrResult FLICKR_API flickr_photosets_removePhoto(FlickrClient *client,
							    const FlickrPhotosetId *photoset_id,
							    const FlickrPhotoId *photo_id);

/* reflection methods */
typedef struct FlickrArgumentInfo FlickrArgumentInfo;
struct FlickrArgumentInfo {
  String m_name;
  unsigned char m_optional;
  String m_description;
};
typedef struct FlickrErrorInfo FlickrErrorInfo;
struct FlickrErrorInfo {
  unsigned int m_code;
  String m_message;
  String m_explanation;
};

typedef struct FlickrMethodInfo FlickrMethodInfo;
struct FlickrMethodInfo {
  String m_name;
  unsigned char m_needslogin;
  String m_description;
  String m_response;
  String m_explanation;
  FlickrArgumentInfo *m_args;
  unsigned int m_argsz;
  FlickrErrorInfo *m_errors;
  unsigned int m_errorsz;
};

extern void FLICKR_API FlickrArgumentInfo_Init(FlickrArgumentInfo *arg);
extern void FLICKR_API FlickrErrorInfo_Init(FlickrErrorInfo *arg);
extern void FLICKR_API FlickrMethodInfo_Init(FlickrMethodInfo *arg);

extern void FLICKR_API FlickrArgumentInfo_Destroy(FlickrArgumentInfo *arg);
extern void FLICKR_API FlickrErrorInfo_Destroy(FlickrErrorInfo *arg);
extern void FLICKR_API FlickrMethodInfo_Destroy(FlickrMethodInfo *arg);

extern FlickrResult FLICKR_API flickr_reflection_getMethodInfo(FlickrClient *client,
							       const char *method_name,
							       FlickrMethodInfo *oMethodInfo);
extern FlickrResult FLICKR_API flickr_reflection_getMethods(FlickrClient *client,
							    void *userData,
							    void (*cb)(void *userData,
								       const String *method));
							      

/* tags methods */

extern FlickrResult FLICKR_API flickr_tags_getListPhoto(FlickrClient *client, 
				      FlickrPhotoId *photo_id,
				      void *userData, 
				      void (*cb)(void *userData, FlickrTag *tag));
extern FlickrResult FLICKR_API flickr_tags_getListUser(FlickrClient *client,
				     String *user_id,
				     void *userData,
				     void (*cb)(void *userData, String *tag));
extern FlickrResult FLICKR_API flickr_tags_getListUserPopular(FlickrClient *client,
					    String *user_id,
					    unsigned int count,
					    void *userData,
					    void (*cb)(void *userData, String *tag, unsigned int count));
extern FlickrResult FLICKR_API flickr_tags_getRelated(FlickrClient *client, String *tag,
				    void *userData,
				    void (*cb)(void *userData, const String *tag));

/* test methods */
typedef struct FlickrRequestArg FlickrRequestArg;
struct FlickrRequestArg {
  const char *m_arg;
  const char *m_value;
};

extern FlickrResult FLICKR_API flickr_test_echo(FlickrClient *client, const FlickrRequestArg args[], const unsigned int argsz);
extern FlickrResult FLICKR_API flickr_test_login(FlickrClient *client, String *id, String *username);

/* urls methods */

extern FlickrResult FLICKR_API flickr_urls_getGroup(FlickrClient *client,
						    const FlickrGroupId *group_id,
						    String *url);

extern FlickrResult FLICKR_API flickr_urls_getUserPhotos(FlickrClient *client,
							 const String *user_id,
							 String *url);

extern FlickrResult FLICKR_API flickr_urls_getUserProfile(FlickrClient *client,
							 const String *user_id,
							 String *url);

extern FlickrResult FLICKR_API flickr_urls_lookupGroup(FlickrClient *client,
						       const String *url,
						       String *id, String *name);

extern FlickrResult FLICKR_API flickr_urls_lookupUser(FlickrClient *client,
						      const String *url,
						      String *id, String *name);

/* Photo URLs mapping methods */
typedef struct FlickrPhotoSpec FlickrPhotoSpec;
struct FlickrPhotoSpec {
  unsigned int m_id;
  unsigned int m_server_id; 
  String *m_secret;
  FlickrPhotoSize m_sz;
  FlickrPhotoFormat m_fmt;
};

extern void FLICKR_API flickr_build_photo_url(unsigned int id, unsigned int server_id, const String *secret, FlickrPhotoSize sz, String *url);
extern void FLICKR_API flickr_build_photo_url_from_spec(FlickrPhotoSpec *spec, String *url);
extern void FLICKR_API flickr_split_photo_url(const String *url, FlickrPhotoSpec *spec);

  /*
   * last arg is photo-id if sync mode, ticket-id if async mode.
   */
extern FlickrResult FLICKR_API flickr_upload(FlickrClient *client,
					     const String *photo_file,
					     const FlickrPhoto *photo_args,
					     const String *tags,
					     unsigned int tagssz,
					     unsigned char async,
					     void *pUserData,
					     void (*progress_cb)(void *pUserData, size_t sz),
					     String *photo_or_ticket_id);

#ifdef __cplusplus
}
#endif

#endif
