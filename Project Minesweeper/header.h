#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>

#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define Declared_Grid_height 22
#define Declared_Grid_width 42
#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255,255,255)
#define Flags_below_zero 99

int Grid_height;
int Grid_width;
int Screenwidth;
int Screenheight;
int Lvl;
int coord_x;
int fields_to_open;
char name[21];
int *pt;

ALLEGRO_DISPLAY *display;
ALLEGRO_KEYBOARD_STATE keyboard;
ALLEGRO_MOUSE_STATE mouse;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *tiles;
ALLEGRO_BITMAP *mine;
ALLEGRO_BITMAP *timing;
ALLEGRO_BITMAP *flag;
ALLEGRO_BITMAP *clockk;
ALLEGRO_BITMAP *left_edge;
ALLEGRO_BITMAP *lower_left_corner;
ALLEGRO_BITMAP *lower_right_corner;
ALLEGRO_BITMAP *bottom_edge;
ALLEGRO_BITMAP *upper_right_corner;
ALLEGRO_BITMAP *upper_left_corner;
ALLEGRO_BITMAP *upper_edge;
ALLEGRO_BITMAP *game_button;
ALLEGRO_BITMAP *options_button;
ALLEGRO_BITMAP *help_button;
ALLEGRO_BITMAP *first_upper_edge;
ALLEGRO_BITMAP *game_menu;
ALLEGRO_BITMAP *options_menu;
ALLEGRO_BITMAP *help_menu;
ALLEGRO_BITMAP *level_menu;
ALLEGRO_BITMAP *bomb_death;
ALLEGRO_BITMAP *bomb_misflagged;
ALLEGRO_BITMAP *customized_menu;
ALLEGRO_BITMAP *highscores_menu;
ALLEGRO_BITMAP *save_score;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue;

typedef bool level;

struct Menu
{
    bool won_menu_opened, dont_touch_the_board, level_menu_opened,level_menu_really_opened, game_menu_opened;
    bool options_menu_opened,help_menu_opened, customized_menu_opened, highscores_menu_opened;
    int customized_heigth, customized_width,customized_level;
    int game_menu_clicks, options_menu_clicks;
    level lvl_hard,lvl_easy,lvl_medium;
};

struct Menu menu;

struct Highscore
{
    char name[25];
};
struct Highscore easy[3];
struct Highscore medium[3];
struct Highscore hard[3];

typedef struct Record
{
    char name[21];
    int sec;
} Record;

enum Direction {UP=1,DOWN=2,LEFT=3,RIGHT=4,ALL_DIR=5};
enum Bitmaps {LOAD=1,DESTROY=2};

int initialization();
void show_empty_field(int x, int y, int sfield[Declared_Grid_width][Declared_Grid_height], int field[Declared_Grid_width][Declared_Grid_height],int dir, int Grid_height, int Grid_width, int* fields_to_open);
int place_mines(int sfield[Declared_Grid_width][Declared_Grid_height], int field[Declared_Grid_width][Declared_Grid_height], int Grid_height, int Grid_width, int Lvl);
void prepare_grid(int sfield[Declared_Grid_width][Declared_Grid_height], int field[Declared_Grid_width][Declared_Grid_height], int Grid_height, int Grid_width);
int sort_by_time(const void *v1, const void *v2);
void Sort(char name_of_file[20]);
void save_highscore_change(level hard, level medium, level easy, char* name, int sec);
char* player_name(int *coord_x, char* name);
void load_highscores(struct Highscore *easy,struct Highscore *medium,struct Highscore *hard);
void handle_bitmaps(int what_to_do);
void draw_frames(int Screenwidth, int Screenheight, int Grid_width, int Grid_height);
void register_event_sources();
void initializing_menu_structure(struct Menu *menu);
void handle_help_menu(struct Menu *menu, int x,int y);
void handle_won_menu(struct Menu *menu, int x, int y, int seconds);
void handle_highscores_menu(struct Menu *menu, int *x, int *y);
void handle_customized(struct Menu *menu, int *x, int *y, float *xf, float *yf);
void handle_level_menu(struct Menu *menu, int x, int y);
void handle_game_menu(struct Menu *menu, int x, int y);
void handle_options_menu(struct Menu *menu, int x, int y);
void draw_flags(int *flags, int Screenheight, int Screenwidth, int Grid_height);
void draw_mines(int *mines_nr, int Screenheight, int Screenwidth, int Grid_height);
void draw_time(float *secondsf,int Screenheight,int Screenwidth,int Grid_height);
#endif
