/* -*- c -*-
 * (C) 2002 Jean-Baptiste Nivoit
 */
#ifndef _candidate_H
#define _candidate_H

typedef enum _DriveType {
	DRIVE_TYPE_UNKNOWN = 0x00,
	DRIVE_TYPE_CDROM   = 0x01,
	DRIVE_TYPE_DVDROM  = 0x02
} DriveType;

typedef struct CandidateDrive CandidateDrive;
struct CandidateDrive {
	char letter;
	char *name;
	DriveType type;
	CandidateDrive *next;
};
CandidateDrive *candidate_drives();
void print_candidate_drive(CandidateDrive *head);
void sort_candidate_drive(CandidateDrive **head);
void free_candidate_drive(CandidateDrive *head);
void for_each_candidate(CandidateDrive *head, void (*f)(CandidateDrive *head));

#endif
