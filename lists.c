#include "mp3.h"

void filter_search(void)
{
	char opt;

	while(1)
	{
		system("tput reset");
		printf("'A' - Display Sorted Album List\n'S' - Display Sorted Songs List\n'Y' - Display Sorted Year List\n'F' - Find Song\n'B' - Back\n\n");
		__fpurge(stdin);
		scanf("%c", &opt);
		switch(opt)
		{
			case 'a':
			case 'A': sort_albums();
				  continue;
			case 's':
			case 'S': sort_songs();
				  continue;
			case 'y':
			case 'Y': sort_year();
				  continue;
			case 'f':
			case 'F': search_keyword();
				  continue;
			case 'b':
			case 'B': break;
			default: printf("Not a valid option!\n\n");
				 continue;
		}
		break;
	}
}
void sort_albums(void)
{
	int i, j, database_index, song_index;
	int temp, ref;
	char temp_name[60];

	for(i = 0; i < new_database; i++)
	{
		strcpy(sorted_album_list[i].album_name, album[i].album_name);
		sorted_album_list[i].album_pos = i;
	}
			
	for(i = 0; i < new_database - 1; i++)
		for(j = 0; j < new_database - i - 1; j++)
			if(strcmp(sorted_album_list[j].album_name, sorted_album_list[j + 1].album_name) > 0)
			{
				strcpy(temp_name, sorted_album_list[j].album_name);
				strcpy(sorted_album_list[j].album_name, sorted_album_list[j + 1].album_name);
				strcpy(sorted_album_list[j + 1].album_name, temp_name);

				temp = sorted_album_list[j].album_pos;
				sorted_album_list[j].album_pos = sorted_album_list[j + 1].album_pos;
				sorted_album_list[j + 1].album_pos = temp;
			}

	/*Display sorted_album_list*/
	printf("Enter album number as choice\n\n");
	for(i = 0; i < new_database; i++)
		printf("%d - Album : %s\n", i + 1, sorted_album_list[i].album_name);
	printf("\n");	
	scanf("%d", &database_index);
	printf("\n");
	database_index--;
				  
	if(database_index < new_database)
	{
		ref = sorted_album_list[database_index].album_pos;
		printf("Enter song number as choice\n\n");
		for(i = 0; i < album[ref].song_count; i++)
			printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", i + 1, album[ref].song[i], album[ref].album_name, album[ref].artist, album[ref].year);
		printf("\n");
		scanf("%d", &song_index);
		printf("\n");
		song_index--;
		if(song_index < album[ref].song_count)
			printf("Now Playing : %s by %s\n\n", album[ref].song[song_index], album[ref].artist);
		else
			printf("Not a valid option\n\n");
	}
	else
		printf("Not a valid option\n\n");
	__fpurge(stdin); 
	getchar();
}
void sort_songs(void)
{
	int i, j, temp, song_index;
	char temp_name[60];
	
	for(i = 0; i < song_list_count - 1; i++)
		for(j = 0; j < song_list_count - i - 1; j++)
			if(strcmp(song_list[j].song, song_list[j + 1].song) > 0)
			{
				strcpy(temp_name, song_list[j].song);
				strcpy(song_list[j].song, song_list[j + 1].song);
				strcpy(song_list[j + 1].song, temp_name);
				
				temp = song_list[j].album_pos;
				song_list[j].album_pos = song_list[j + 1].album_pos;
				song_list[j + 1].album_pos = temp;
			}
	
	/*Displaying sorted songs list*/
	printf("Enter song number as choice\n\n");
	for(i = 0; i < song_list_count; i++)
		printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", i + 1, song_list[i].song, album[song_list[i].album_pos].album_name, album[song_list[i].album_pos].artist, album[song_list[i].album_pos].year);
	printf("\n");
	scanf("%d", &song_index);
	printf("\n");
	song_index--;
	if(song_index < song_list_count)
		printf("Now Playing : %s by %s\n\n", song_list[song_index].song, album[song_list[song_index].album_pos].artist);
	else
		printf("Not a valid option\n\n");
	__fpurge(stdin); 
	getchar();
}
void sort_year(void)
{
	int i, j, k, temp, database_index, ref_year, song_count = 0, song_index, list_count = 0;
	
	for(i = 0, j = 0; i < new_database; i++)
	{
		if(i == 0)
		{
			sorted_year_list[j].year = album[j].year;
			j++;
		}
		else
		{
			if(album[i].year == album[i - 1].year)
				continue;
			sorted_year_list[j].year = album[i].year;
			j++;
		}
	}
	list_count = j;

	for(i = 0; i < list_count - 1; i++)
		for(j = 0; j < list_count - i - 1; j++)
			if(sorted_year_list[j].year > sorted_year_list[j + 1].year)
			{
				temp = sorted_year_list[j].year;
				sorted_year_list[j].year = sorted_year_list[j + 1].year;
				sorted_year_list[j + 1].year = temp;
			}

	/*Displaying sorted year list*/
	printf("Enter year as choice\n\n");
	for(i = 0; i < list_count; i++)
		printf("%d - Year : %d\n", i + 1, sorted_year_list[i].year);
	printf("\n");	
	scanf("%d", &database_index);
	printf("\n");
	database_index--;
	
	if(database_index < list_count)
	{
		ref_year = sorted_year_list[database_index].year;
		printf("Enter song number as choice\n\n");
		for(i = 0, k = 0; i < new_database; i++)
		{
			if(ref_year == album[i].year)
			{
				song_count += album[i].song_count;
				for(j = 0; j < album[i].song_count; j++)
				{
					printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", k + 1, album[i].song[j], album[i].album_name, album[i].artist, album[i].year);
					k++;
				}
			}
		}
		printf("\n");
		scanf("%d", &song_index);
		printf("\n");
		song_index--;

		if(song_index < song_count)
		{
			for(i = 0, temp = 0; i < new_database; i++)
			{
				if(ref_year == album[i].year)
					temp += album[i].song_count;
				else
					continue;
				if(song_index > temp)
					continue;
				else
				{
					sorted_year_list[database_index].album_pos = i;
					temp -= album[i].song_count;
					song_index -= temp;
					break;
				}
			}		
			printf("Now Playing : %s by %s\n\n", album[sorted_year_list[database_index].album_pos].song[song_index], album[sorted_year_list[database_index].album_pos].artist);
		}
		else
			printf("Not a valid option\n\n");
	}
	else
		printf("Not a valid option\n\n");
	__fpurge(stdin); 
	getchar();
}
void search_keyword(void)
{
	char keyword[60];
	int i, j, len, flag = 0;
	char *check;

	printf("Enter search keyword\n");
	__fpurge(stdin);
	fgets(keyword, 60, stdin);
	len = strlen(keyword);
	if(keyword[len - 1] == '\n')
   		keyword[len - 1] = '\0';
	printf("\n");

	for(i = 0, j = 0; i < song_list_count; i++)
	{
		check = strcasestr(song_list[i].song, keyword);
		if(check != NULL)
		{
			printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", j + 1, song_list[i].song, album[song_list[i].album_pos].album_name, album[song_list[i].album_pos].artist, album[song_list[i].album_pos].year);
			flag = 1;
			j++;
		}
		else
			continue;
	}
	if(flag == 0)
		printf("\nNo match found.\n\n");
	__fpurge(stdin); 
	getchar();
}
void playlists(void)
{
	char opt, ch;
	int i, j, k, l, playlist_index, song_index, flag[maxsongs] = {0}, ref, flag_count = 0, flag_2 = 0;

	for(i = 0; i < new_playlist; i++)
	{
		for(j = 0; j < playlist[i].song_count; j++)
		{
			flag_2 = 0;
			for(k = 0; k < song_list_count; k++)
			{
				if(strcmp(playlist[i].song[j], song_list[k].song) == 0)
					if(song_list[k].album_pos == playlist[i].album_pos[j])
					{
						flag_2 = 1;
						break;
					}
			}
			if(flag_2 == 0)
			{
				for(l = j; l < playlist[i].song_count - 1; l++)
					strcpy(playlist[i].song[l], playlist[i].song[l + 1]);
				playlist[i].song_count--;
			}
		}
	}
				

	while(1)
	{
		system("tput reset");
		printf("'D' - Display Playlists\n'B' - Back\n\n");
		__fpurge(stdin);
		scanf("%c", &opt);
		switch(opt)
		{
			case 'd':
			case 'D': printf("\nEnter playlist number as choice\n\n");
				  for(i = 0; i < new_playlist; i++)
				  	printf("%d - Playlist : %s\n", i + 1, playlist[i].playlist_name);
				  printf("\n");
				  scanf("%d", &playlist_index);
				  printf("\n");
				  playlist_index--;

				  if(playlist_index < new_playlist)
				  {
					printf("Enter song number as choice\n\n");
					for(i = 0; i < playlist[playlist_index].song_count; i++)
						printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", i + 1, playlist[playlist_index].song[i], album[playlist[playlist_index].album_pos[i]].album_name, album[playlist[playlist_index].album_pos[i]].artist, album[playlist[playlist_index].album_pos[i]].year);
					printf("\n");
					scanf("%d", &song_index);
					printf("\n");
					song_index--;
					if(song_index < playlist[playlist_index].song_count)
						printf("Now Playing : %s by %s\n\n", playlist[playlist_index].song[song_index], album[playlist[playlist_index].album_pos[song_index]].artist);
					else
						printf("Not a valid option\n\n");

					/*Add new song*/
					printf("Add new song? <y/n>\n");
					__fpurge(stdin);
					scanf("%c", &ch);
					printf("\n");
					if(ch == 'y')
						{
							printf("Enter song number as choice\n\n");
							for(i = 0, k = 0; i < song_list_count; i++)
							{	
								for(j = 0; j < playlist[playlist_index].song_count; j++)
								{
									if(strcmp(playlist[playlist_index].song[j], song_list[i].song) == 0)
										if(song_list[i].album_pos == playlist[playlist_index].album_pos[j])
											flag[i] = 1;
								}
								if(flag[i] == 0)
								{	
									printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", k + 1, song_list[i].song, album[song_list[i].album_pos].album_name, album[song_list[i].album_pos].artist, album[song_list[i].album_pos].year);
									k++;
								}
							}
							printf("\n");
							__fpurge(stdin);
							scanf("%d", &song_index);
							printf("\n\n");
							song_index;
							i = 0;
							while(flag_count != song_index)
							{
								if(flag[i] == 0)
									flag_count++;
								i++;
							}
							song_index = i - 1;

							/*Adding song to playlist*/
							ref = playlist[playlist_index].song_count;
							strcpy(playlist[playlist_index].song[ref], song_list[song_index].song);
							playlist[playlist_index].album_pos[ref] = song_list[song_index].album_pos;
							playlist[playlist_index].song_count++;
							printf("Playlist updated!\n\n");
						}
					else
						continue;
				  }
				  else
					printf("Not a valid option\n\n");
				  __fpurge(stdin);
				  getchar();
				  continue;
			case 'b':
			case 'B': break;
			default: printf("Not a valid option!\n\n");
				 continue;
		}
		break;
	}	
}
	
