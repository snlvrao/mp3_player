#include "mp3.h"

void init_database()
{
	FILE *fptr;
	int len, i;
	char buffer[10];

	fptr = fopen("database.txt", "r");

	if (fptr == NULL)
    	{
        	printf("File does not exist\n\n") ;
		exit(0);
    	}
	else
	{
		while(fgets(album[new_database].album_name, 60, fptr) != NULL)
		{
			len = strlen(album[new_database].album_name);
			if(album[new_database].album_name[len - 1] == '\n')
   				album[new_database].album_name[len - 1] = '\0';

			fgets(album[new_database].artist, 60, fptr);
			len = strlen(album[new_database].artist);
			if(album[new_database].artist[len - 1] == '\n')
   				album[new_database].artist[len - 1] = '\0';
			
			fgets(buffer, 10, fptr);
			len = strlen(buffer);
			if(buffer[len - 1] == '\n')
   				buffer[len - 1] = '\0';
			album[new_database].year = strtod(buffer, NULL); //Convert string to integer

			fgets(buffer, 10, fptr);
			len = strlen(buffer);
			if(buffer[len - 1] == '\n')
   				buffer[len - 1] = '\0';
			album[new_database].song_count = strtod(buffer, NULL); //Convert string to integer

			for(i = 0; i < album[new_database].song_count; i++)
			{
				fgets(album[new_database].song[i], 60, fptr);
				len = strlen(album[new_database].song[i]);
				if(album[new_database].song[i][len - 1] == '\n')
   					album[new_database].song[i][len - 1] = '\0';
				
				/*Copy to song_list*/
				strcpy(song_list[song_list_count].song, album[new_database].song[i]);
				song_list[song_list_count].album_pos = new_database;
				song_list_count++;
			}
			new_database++;
		}
	}	
	fclose(fptr);
	
	/*Initialising Playlist database*/
	strcpy(playlist[0].playlist_name, "Playlist_1");
	strcpy(playlist[0].song[0], song_list[4].song);
	playlist[0].album_pos[0] = song_list[4].album_pos;
	playlist[0].song_count++;

	strcpy(playlist[0].song[1], song_list[8].song);
	playlist[0].album_pos[1] = song_list[8].album_pos;
	playlist[0].song_count++;

	strcpy(playlist[0].song[2], song_list[1].song);
	playlist[0].album_pos[2] = song_list[1].album_pos;
	playlist[0].song_count++;

	strcpy(playlist[0].song[3], song_list[3].song);
	playlist[0].album_pos[3] = song_list[3].album_pos;
	playlist[0].song_count++;
	
	new_playlist++;
	
	strcpy(playlist[1].playlist_name, "Playlist_2");
	strcpy(playlist[1].song[0], song_list[2].song);
	playlist[1].album_pos[0] = song_list[2].album_pos;
	playlist[1].song_count++;

	strcpy(playlist[1].song[1], song_list[5].song);
	playlist[1].album_pos[1] = song_list[5].album_pos;
	playlist[1].song_count++;

	strcpy(playlist[1].song[2], song_list[7].song);
	playlist[1].album_pos[2] = song_list[7].album_pos;
	playlist[1].song_count++;

	strcpy(playlist[1].song[3], song_list[9].song);
	playlist[1].album_pos[3] = song_list[9].album_pos;
	playlist[1].song_count++;
	
	new_playlist++;
}
int main(void)
{	
	char opt;

	init_database();
	while(1)
	{
		system("tput reset");
		printf("Main Menu\n\n");
		printf("'A' - Albums\n'S' - Songs\n'P' - Playlists\n'F' - Filter Search\n\n");
		__fpurge(stdin);
		scanf("%c", &opt);
		switch(opt)
		{
			case 'a':
			case 'A': albums();
				  continue;
			case 's':
			case 'S': songs();
				  continue;
			case 'p':
			case 'P': playlists();
				  continue;
			case 'f':
			case 'F': filter_search();
				  continue;
			default: printf("Not a valid option!\n\n");
				 continue;
		}
	}
}
