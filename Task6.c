#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLACE_COUNT 12
int places_free = PLACE_COUNT;

typedef struct _Seat
{
	int id;
	int taken;
	char first_name[80];
	char last_name[80];
} Seat;

Seat arr[PLACE_COUNT];
int ids[PLACE_COUNT];

void add(int);
void rem(int);

void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

int main()
{
	FILE *flightInfo = fopen("flight.bin", "rb");
	
	if (flightInfo == NULL)
	{
		for (int i = 0; i < PLACE_COUNT; i++)
		{
			arr[i].id = i + 1;
			arr[i].taken = 0;
			arr[i].first_name[0] = '\0';
			arr[i].last_name[0] = '\0';
		}
	}
	else
	{
		fread(arr, sizeof(Seat), PLACE_COUNT, flightInfo);
		fclose(flightInfo);
        for (int i = 0; i < PLACE_COUNT; i++)
            if (arr[i].taken)
            {
                add(i);
            }
	}

	while (1)
	{
		char code;
		printf("a - Show the amount of unbooked places\n");
		printf("b - Show the list of unbooked places\n");
		printf("c - Show the list of booked places\n");
		printf("d - Book place\n");
		printf("e - Unbook place\n");
		printf("f - Quit\n\n");

		scanf(" %c", &code);
		getchar();
		switch (code)
		{
		case 'a':
		{
			printf("%d\n", places_free);
			break;
		}

		case 'b':
		{
			for (int i = 0; i < PLACE_COUNT; i++)
				if (!arr[i].taken)
                    printf("%d\n", arr[i].id);
            break;
		}

		case 'c':
		{
			/*for (int i = 0; i < PLACE_COUNT; i++)
				if (arr[i].taken)
					printf("%d: %s %s\n", arr[i].id, arr[i].first_name, arr[i].last_name);*/
            for (int i = 0; i < PLACE_COUNT - places_free; i++)
                printf("%d: %s, %s\n", arr[ids[i] - 1].id, arr[ids[i] - 1].last_name, arr[ids[i] - 1].first_name);
            break;
		}

		case 'd':
		{
			int seatCode;
			char firstName[80];
			char lastName[80];
			char confirm;

			printf("Enter the seat code: ");
			scanf("%d", &seatCode);
			getchar();
			if (seatCode < 1 || seatCode > PLACE_COUNT)
			{
				printf("Error: invalid seat code\n");
				break;
			}
			if (arr[seatCode - 1].taken)
			{
				printf("Error: seat already booked\n");
				break;
			}

			printf("Enter your first name: ");
			scanf("%s", firstName);
			getchar();
			printf("Enter your last name: ");
			scanf("%s", lastName);
			getchar();

			printf("You want to book seat #%d for passenger %s %s. Press \'y\' to confirm booking.\n", seatCode, firstName, lastName);
			scanf("%c", &confirm);
			getchar();
			if (confirm == 'y')
			{
                arr[seatCode - 1].id = seatCode;
				arr[seatCode - 1].taken = 1;
				strcpy(arr[seatCode - 1].first_name, firstName);
				strcpy(arr[seatCode - 1].last_name, lastName);
                //places_free--;
                add(seatCode - 1);
			}
			break;
		}

		case 'e':
		{
			int seatCode;
			char confirm;

			printf("Enter the seat code: ");
			scanf("%d", &seatCode);
			getchar();
			if (seatCode < 1 || seatCode > PLACE_COUNT)
			{
				printf("Error: invalid seat code\n");
				break;
			}
			if (!arr[seatCode - 1].taken)
			{
				printf("Error: seat not booked\n");
				break;
			}
			
			/*printf ("Enter your first name: ");
                        scanf("%s", firstName);
                        getchar();
			if (strcmp(firstName, arr[seatCode - 1].first_name) != 0)
			{
                                printf("Error: incorrect first name\n");
                                break;
                        }	
                        printf("Enter your last name: ");
                        scanf("%s", lastName);
                        getchar();
			if (strcmp(lastName, arr[seatCode - 1].last_name) != 0)
                        {
                                printf("Error: incorrect last name\n");
                                break;
                        }
             */

         		printf("You want to unbook seat #%d for passenger %s %s. Press \'y\' to confirm unbooking.\n", seatCode, arr[seatCode - 1].first_name, arr[seatCode - 1].last_name);
                        scanf("%c", &confirm);
                        getchar();
			if (confirm == 'y')
            {
				arr[seatCode - 1].taken = 0;
                //places_free++;
                rem(arr[seatCode - 1].id);
            }
			break;
		}

		case 'f':
		{
			FILE *outputFile = fopen("flight.bin", "wb");
			fwrite(arr, sizeof(Seat), PLACE_COUNT, outputFile);
			fclose(outputFile);
			return 0;
		}

		default:
			break;
		}

		printf("\n");
	}
	return 0;
}

void add (int idx)
{
    ids[PLACE_COUNT - places_free] = arr[idx].id;
    for (int i = PLACE_COUNT - 1 - places_free; i >= 0; i--)
    {
        int res = strcmp(arr[ids[i] - 1].last_name, arr[idx].last_name);
        if (res > 0 || (res == 0 && strcmp(arr[ids[i] - 1].first_name, arr[idx].first_name) > 0))
        {
            swap(&(ids[i]), &(ids[i + 1]));
        }
        else
            break;
    }
    places_free--;
}

void rem(int idx)
{
    int indexof;
    for (int i = 0; i < PLACE_COUNT - places_free; i++)
        if (ids[i] == idx)
        {
            indexof = i;
            break;
        }
    for (int i = indexof + 1; i < PLACE_COUNT - places_free; i++)
    {
        swap(&(ids[i]), &(ids[i - 1]));
    }
    places_free++;
}