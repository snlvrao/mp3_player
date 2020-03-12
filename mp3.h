#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxdatabase 10
#define maxsongs 100
#define maxplaylists 10

int new_database;
int new_playlist;
int song_list_count;
struct database
{
	char album_name[30];
	char song[maxdatabase][30];
	char artist[50];
	int song_count;
	int year;
};
struct database album[maxdatabase];
struct album_database
{
	char album_name[30];
	int album_pos;
};
struct album_database sorted_album_list[maxdatabase];
struct song_database
{
	char song[30];
	int album_pos;
};
struct song_database song_list[maxsongs];
struct year_database
{
	int year;
	int album_pos;
};
struct year_database sorted_year_list[maxdatabase];
struct playlist_database
{
	char playlist_name[40];
	char song[maxplaylists][40];
	int album_pos[maxplaylists];
	int song_count;
};
struct playlist_database playlist[maxplaylists];
void albums(void);
void songs(void);
void sort_albums(void);
void sort_songs(void);
void sort_year(void);
void filter_search(void);
void search_keyword(void);
void playlists(void);
