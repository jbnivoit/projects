/* -*- c -*-
 * (C) 2002 Jean-Baptiste Nivoit
 * This code uses the Win32 API and the NTMS API to figure out the list
 * of available CDROM & DVDROM drives installed on a system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "candidate.h"

int main(int argc, char **argv) {

	CandidateDrive *head = candidate_drives();
	print_candidate_drive(head);
	sort_candidate_drive(&head);
	print_candidate_drive(head);
	free_candidate_drive(head);
	return EXIT_SUCCESS;
}

