#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

int main() {

	HANDLE h;
	DWORD threadID;
	CreateThread(NULL, 0, /*function name*/, /*arguments to function or null*/, &threadID);

	while (1) {
		
		FILE *fp;
		char str[50]; // string off whitelisted programs
		char whitelist[200][50]; // where the strings are getting pushed into
		
		int lc = 0; // list counter for the whitelist
		char* filename = "whitelist.txt"; // whitelist file name

		fp = fopen(filename, "r"); // open file
		if (fp == NULL) { // check if null
			printf("Could not open file %s", filename);
			fflush(stdout);
			return 0; // return 0 if null
		}
		while (fgets(str, 20, fp) != NULL) { // if line is not empty/NULL

			strcpy(&whitelist[lc][0], str); // copy str in whitelist
			char* p = strchr(&whitelist[lc][0], '\n'); // remove newline from whitelist entry
			if (p) { // if newline is not null
				*p = '\0'; // set newline to null terminator
			}
			lc++; // +1 on list counter

			//Sleep(1000);
		}

		fclose(fp); // closes file

		HWND hWnd = GetForegroundWindow(); // contains path of foregroundwindow
		const int nMaxCount = 300; // max byte size of windowTile
		char windowTitle[nMaxCount]; // char array of the foregroundwindows name
		int i = GetWindowText( // gets foregroundwindows name and puts it into windowTile
							  hWnd,
							  windowTitle,
							  sizeof(windowTitle)
		);

		for (int x = 0; x < lc; x++) {

			char search[] = ""; // name of thing to search
		
			if (strstr(windowTitle, &whitelist[x][0]) != NULL) // substring is found
			{
				//printf("'%s' contains '%s'\n", windowTitle, whitelist[x][0]);
				printf(" yes");
			}
			else // Substring not found 
			{
				//printf("'%s' doesn't contain '%s'\n", windowTitle, whitelist[x][0]);
				printf(" no");
			}
			
			fflush(stdout);
			Sleep(1000); // 1000 is one second wait time
		}
	}

	return 0; // end program
}

