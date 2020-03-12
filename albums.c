#include "mp3.h"

void albums(void)
{
	int database_index, song_index, i, len, j, flag = 0;
	char opt, buffer[40];

	while(1)
	{
		system("tput reset");
		printf("'L' - List Albums\n'C' - Create New Album\n'D' - Delete Album\n'B' - Back\n\n");
		__fpurge(stdin);
		scanf("%c", &opt);
		switch(opt)
		{
			case 'l':
			case 'L': printf("Enter album number as choice\n\n");
				  for(i = 0; i < new_database; i++)
					  printf("%d - Album : %s\n", i + 1, album[i].album_name);
				  printf("\n");	
				  scanf("%d", &database_index);
				  printf("\n");
				  database_index--;
				  
				  if(database_index < new_database)
				  {
					  printf("Enter song number as choice\n\n");
					  for(i = 0; i < album[database_index].song_count; i++)
						  printf("%-3d - Song : %-15s\tArtist : %-45s\tYear : %d\n", i + 1, album[database_index].song[i], album[database_index].artist, album[database_index].year);
					  printf("\n");
					  scanf("%d", &song_index);
					  printf("\n");
					  song_index--;
					  if(song_index < album[database_index].song_count)
					  	printf("Now Playing : %s by %s\n\n", album[database_index].song[song_index], album[database_index].artist);
					  else
						  printf("Not a valid option\n\n");
				  }
				  else
					  printf("Not a valid option\n\n");
				  __fpurge(stdin); 
				  getchar();
				  continue;
			case 'c':
			case 'C': printf("Enter album name\n");
				  __fpurge(stdin);
				  fgets(buffer, 40, stdin);
				  len = strlen(buffer);
				  if(buffer[len - 1] == '\n')
   					  buffer[len - 1] = '\0';

				  for(i = 0; i < new_database; i++)
				  {
				  	if(strcmp(album[i].album_name, buffer) == 0)
					{
						printf("\nAlbum already exists!\n");
						flag = 1;
						__fpurge(stdin); 
						getchar();
						break;
					}
				  }
				  if(flag == 0)
				  {
					  strcpy(album[new_database].album_name, buffer);
					  
					  printf("\nEnter album year\n");
					  __fpurge(stdin);
					  scanf("%d", &album[new_database].year);

					  printf("\nEnter artist name\n");
					  __fpurge(stdin);
					  fgets(album[new_database].artist, 60, stdin);
					  len = strlen(album[new_database].artist);
					  if(album[new_database].artist[len - 1] == '\n')
	   					  album[new_database].artist[len - 1] = '\0';

					  printf("\nEnter number of songs in album\n");
					  scanf("%d", &album[new_database].song_count);

					  for(i = 0; i < album[new_database].song_count; i++)
					  {
					  	printf("\nEnter name of song %d\n", i + 1);
						__fpurge(stdin);
						fgets(album[new_database].song[i], 40, stdin);
						len = strlen(album[new_database].song[i]);
						if(album[new_database].song[i][len - 1] == '\n')
	   						album[new_database].song[i][len - 1] = '\0';
						
						/*Copy to song_list*/					
						strcpy(song_list[song_list_count].song, album[new_database].song[i]);
						song_list[song_list_count].album_pos = new_database;
						song_list_count++;
					  }
					  new_database++;
					  printf("\n");
				  }
					  continue;
			case 'd':
			case 'D': printf("Enter album number to delete\n\n");
				  for(i = 0; i < new_database; i++)
					  printf("%d - Album : %s\n", i + 1, album[i].album_name);
				  printf("\n");	
				  scanf("%d", &database_index);
				  printf("\n\n");
				  database_index--;
				  
				  for(i = database_index; i < new_database - 1; i++)
				  {
				  	strcpy(album[i].album_name, album[i + 1].album_name);
					strcpy(album[i].artist, album[i + 1].artist);
					album[i].song_count = album[i + 1].song_count;
					album[i].year = album[i + 1].year;
					for(j = 0; j < album[i + 1].song_count; j++)
						strcpy(album[i].song[j], album[i + 1].song[j]);
				  }
				  new_database--;
				  
				  for(i = 0, song_list_count = 0; i < album[new_database].song_count; i++)
				  {
					/*Copy to song_list*/
					strcpy(song_list[song_list_count].song, album[new_database].song[i]);
					song_list[song_list_count].album_pos = new_database;
					song_list_count++;
				  }
				  printf("Album deleted!\n\n");
				  __fpurge(stdin); 
				  getchar();
				  continue;
			case 'b':
			case 'B': break;
			default: printf("\nNot a valid option\n\n");
				 __fpurge(stdin); 
				 getchar();
				 continue;
		}
		break;
	}
}
void songs(void)
{
	int i, j, song_index, database_index, flag = 0, len, song_pos, temp = 0, ref;
	char opt, buffer[60];

	while(1)
	{
		system("tput reset");
		flag = 0;
		printf("'L' - List Songs\n'A' - Add New Song\n'D' - Delete Song\n'B' - Back\n\n");
		__fpurge(stdin);
		scanf("%c", &opt);
		switch(opt)
		{
			case 'l':
			case 'L': printf("Enter song number as choice\n\n");
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
				  continue;
			case 'a':
			case 'A': printf("\nEnter name of song\n");
				  __fpurge(stdin);
				  fgets(song_list[song_list_count].song, 40, stdin);
					len = strlen(song_list[song_list_count].song);
					if(song_list[song_list_count].song[len - 1] == '\n')
   						song_list[song_list_count].song[len - 1] = '\0';
					
				  printf("\nEnter name of album\n");
				  __fpurge(stdin);
				  fgets(buffer, 40, stdin);
					len = strlen(buffer);
					if(buffer[len - 1] == '\n')
   						buffer[len - 1] = '\0';

				  for(i = 0; i < new_database; i++)
				  {
				  	if(strcmp(album[i].album_name, buffer) == 0)
					{
						song_list[song_list_count].album_pos = i;
						strcpy(album[i].song[album[i].song_count], song_list[song_list_count].song);
						album[i].song_count++;
						flag = 1;
						printf("\nAdding song to existing album\n");
						__fpurge(stdin); 
						getchar();
						break;
					}
				  }
				  if(flag == 0)
				  {
					strcpy(album[i].song[album[i].song_count], song_list[song_list_count].song);
					album[i].song_count++;

					strcpy(album[new_database].album_name, buffer);
					song_list[song_list_count].album_pos = new_database;

					printf("\nEnter name of artist\n");
				  	__fpurge(stdin);
				  	fgets(buffer, 60, stdin);
					len = strlen(buffer);
					if(buffer[len - 1] == '\n')
   						buffer[len - 1] = '\0';
					
					strcpy(album[new_database].artist, buffer);

					printf("\nEnter album year\n");
				  	scanf("%d", &album[new_database].year);
					
					new_database++;
				  }
				  song_list_count++;					
				  printf("\n");
				  continue;
			case 'd':
			case 'D': printf("Enter song number to delete\n\n");
				  for(i = 0; i < song_list_count; i++)
					printf("%-3d - Song : %-20s\tAlbum : %-20s\tArtist : %-45s\tYear : %d\n", i + 1, song_list[i].song, album[song_list[i].album_pos].album_name, album[song_list[i].album_pos].artist, album[song_list[i].album_pos].year);
				  printf("\n");
				  scanf("%d", &song_index);
				  printf("\n\n");
				  song_index--;
	
				  for(i = 0; i < song_list[song_index].album_pos; i++)
					temp += album[i].song_count;
				  song_pos = song_index - temp - 1;

				  if(song_index < song_list_count)
				  {
					ref = song_list[song_index].album_pos;
					for(i = song_index; i < song_list_count - 1; i++)
				  		strcpy(song_list[i].song, song_list[i + 1].song);
				  	song_list_count--;
					for(i = song_pos; i < album[ref].song_count - 1; i++)
						strcpy(album[ref].song[i], album[ref].song[i + 1]);
				  	album[ref].song_count--;
					printf("Song deleted!\n\n");
				  }
				  else
					printf("Not a valid option\n\n");
				  __fpurge(stdin); 
				  getchar();
			case 'b':
			case 'B': break;
			default: printf("\nNot a valid option\n\n");
				 __fpurge(stdin); 
				 getchar();
				 continue;
		}
		break;
	}	
}
