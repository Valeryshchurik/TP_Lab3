#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	struct tm *currentTimeinfo; // Structure contains information about current time
    struct tm *birthDate = malloc(sizeof(struct tm)); // Structure contains information about user's birth time
	time_t currentRawtime;
	time_t birthRawtime;

	time(&currentRawtime);
	currentTimeinfo = localtime(&currentRawtime);
	
    printf("Enter your date and time of birth (dd.mm.yyyy hh:mm): ");
	scanf("%d.%d.%d %d:%d", &(birthDate->tm_mday), &(birthDate->tm_mon), &(birthDate->tm_year), &(birthDate->tm_hour), &(birthDate->tm_min));
	
    // Adjusting data so that mktime function would work correctly
    birthDate->tm_mon--;
	birthDate->tm_year -= 1900;
	birthDate->tm_sec = 0;
	birthRawtime = mktime(birthDate);
    
	printf("Current time: %d.%d.%d %d:%d\n", currentTimeinfo->tm_mday, currentTimeinfo->tm_mon + 1, currentTimeinfo->tm_year + 1900, currentTimeinfo->tm_hour, currentTimeinfo->tm_min);
    
    printf("Your birth time: %d.%d.%d %d:%d\n", birthDate->tm_mday, birthDate->tm_mon + 1, birthDate->tm_year + 1900, birthDate->tm_hour, birthDate->tm_min);
    
    printf("Your age in seconds = %d\n", (int)currentRawtime - (int)birthRawtime);
	free(birthDate);
}

