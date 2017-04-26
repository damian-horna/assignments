#include "header.h"


int place_mines(int sfield[Declared_Grid_width][Declared_Grid_height], int field[Declared_Grid_width][Declared_Grid_height],int Grid_height, int Grid_width, int Lvl)
{
    int mines_nr=0;
    for (int i=1; i<=Grid_width-2; i++)
        for (int j=1; j<=Grid_height-2; j++)
        {
            sfield[i][j]=10;
            if (rand()%Lvl==0)
            {
                field[i][j]=9;
                mines_nr++;
            }
            else field[i][j]=0;
        }
    return mines_nr;
}

void prepare_grid(int sfield[Declared_Grid_width][Declared_Grid_height], int field[Declared_Grid_width][Declared_Grid_height], int Grid_height, int Grid_width)
{
    for (int i=1; i<=Grid_width-2; i++)
        for (int j=1; j<=Grid_height-2; j++)
        {
            int n=0;
            if (field[i][j]==9) continue;
            if (field[i+1][j]==9) n++;
            if (field[i][j+1]==9) n++;
            if (field[i-1][j]==9) n++;
            if (field[i][j-1]==9) n++;
            if (field[i+1][j+1]==9) n++;
            if (field[i-1][j-1]==9) n++;
            if (field[i-1][j+1]==9) n++;
            if (field[i+1][j-1]==9) n++;
            field[i][j]=n;
        }
}

void show_empty_field(int x, int y, int sfield[Declared_Grid_width][Declared_Grid_height], int field[Declared_Grid_width][Declared_Grid_height], int dir, int Grid_height, int Grid_width, int* fields_to_open)
{
    if (x>Grid_width-2 || y>Grid_height-2 || x<1 || y<1 || sfield[x][y]==field[x][y]) return;
    else if(field[x][y]!=0)
    {
        if(sfield[x][y]!=11)
        {
            sfield[x][y] = field[x][y];
            --(*fields_to_open);
        }
        return;
    }
    else if(field[x][y]==0)
    {
        if(sfield[x][y]!=11)
        {
            sfield[x][y] = field[x][y];
            --(*fields_to_open);
        }
        switch(dir)
        {
        case UP:
            show_empty_field(x,y-1,sfield,field,UP, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x+1,y,sfield,field,RIGHT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x-1,y,sfield,field,LEFT, Grid_height, Grid_width, fields_to_open);
            break;
        case DOWN:
            show_empty_field(x+1,y,sfield,field,RIGHT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x-1,y,sfield,field,LEFT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x,y+1,sfield,field,DOWN, Grid_height, Grid_width, fields_to_open);
            break;
        case LEFT:
            show_empty_field(x-1,y,sfield,field,LEFT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x,y+1,sfield,field,DOWN, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x,y-1,sfield,field,UP, Grid_height, Grid_width, fields_to_open);
            break;
        case RIGHT:
            show_empty_field(x+1,y,sfield,field,RIGHT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x,y+1,sfield,field,DOWN, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x,y-1,sfield,field,UP, Grid_height, Grid_width, fields_to_open);
            break;
        case ALL_DIR:
            show_empty_field(x+1,y,sfield,field,RIGHT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x-1,y,sfield,field,LEFT, Grid_height, Grid_width, fields_to_open);
            show_empty_field(x,y+1,sfield,field,DOWN, Grid_height, Grid_width,fields_to_open);
            show_empty_field(x,y-1,sfield,field,UP, Grid_height, Grid_width,fields_to_open);
            break;

        }
    }
}

void Sort(char name_of_file[20])
{


    Record records[10];
    int i=0;
    FILE* file = fopen(name_of_file,"r");
    while(fscanf(file, "%s %d",&records[i].name, &records[i].sec)!=EOF)
    {
        i++;
        if(i==10) break;
    }

    fclose(file);
    size_t size = i;
    qsort(records, size, sizeof(Record), sort_by_time);
    FILE* fp = fopen(name_of_file,"w");

    for(int j=0; j<i; j++)
    {
        fprintf(fp,"%s %d\n",records[j].name,records[j].sec);
    }
    fclose(fp);


}

int sort_by_time(const void *v1, const void *v2)
{
    const Record *p1 = (Record *)v1;
    const Record *p2 = (Record *)v2;
    if (p1->sec < p2->sec)
        return -1;
    else if (p1->sec > p2->sec)
        return +1;
    else
        return 0;
}
char* player_name(int *coord_x, char * name)
{
    char signs[47]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z',
                     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
                    };
    al_draw_line(*coord_x,194 , *coord_x,210, BLACK, 1);
    for (int i=0; i<47; i++)
    {
        if (al_key_down(&keyboard, i))
        {
            if (strlen(name)<21)
            {
                name[(*coord_x-70)/8] = signs[i-1];
                *coord_x+=8;
            }
        }
    }
    if (al_key_down(&keyboard, ALLEGRO_KEY_BACKSPACE))
    {
        if (strlen(name)>0 && *coord_x!=70)
        {
            name[(*coord_x-70)/8-1] = '\0';
        }

        if (*coord_x>77)
        {
            *coord_x-=8;
        }
    }

    if (al_key_down(&keyboard, ALLEGRO_KEY_LEFT))
    {
        if (*coord_x>77)
        {
            *coord_x-=8;
        }
    }

    if (al_key_down(&keyboard, ALLEGRO_KEY_RIGHT))
    {
        if (*coord_x<70+8*strlen(name))
        {
            *coord_x+=8;
        }
        al_rest(0.15);
    }
    al_draw_text(font, BLACK, 70, 194, 0, name);

    return name;
}
void save_highscore_change(level hard, level medium, level easy, char* name, int sec)
{
    FILE *fr;
    FILE *fw;
    char temp[10][25];
    if(hard)
    {
        fr=fopen("hs_hard","r");
        for(int i=0; i<10; i++)
            fgets(temp[i],24,fr);
        fclose(fr);
        fw=fopen("hs_hard","w");
        fprintf(fw,"%s %d\n",name,sec);
        for(int i=0; i<10; i++)
            fprintf(fw,"%s\n",temp[i]);
        fclose(fw);

    }
    else if(medium)
    {
        fr=fopen("hs_medium","r");
        for(int i=0; i<10; i++)
            fgets(temp[i],24,fr);
        fclose(fr);
        fw=fopen("hs_medium","w");
        fprintf(fw,"%s %d\n",name,sec);
        for(int i=0; i<10; i++)
            fprintf(fw,"%s\n",temp[i]);
        fclose(fw);
    }
    else if(easy)
    {
        fr=fopen("hs_easy","r");
        for(int i=0; i<10; i++)
            fgets(temp[i],24,fr);
        fclose(fr);
        fw=fopen("hs_easy","w");
        fprintf(fw,"%s %d\n",name,sec);
        for(int i=0; i<10; i++)
            fprintf(fw,"%s",temp[i]);
        fclose(fw);
    }

}

void load_highscores(struct Highscore *easy,struct Highscore *medium,struct Highscore *hard)
{
    FILE* hs_easy;
    FILE* hs_medium;
    FILE* hs_hard;

    Sort("hs_easy");
    Sort("hs_medium");
    Sort("hs_hard");

    if ((hs_easy = fopen("hs_easy", "r")) == NULL)
    {
        printf("\nError while opening the file  %s.\n", "hs_easy");
        exit(1);
    }
    if ((hs_medium = fopen("hs_medium", "r")) == NULL)
    {
        printf("\nError while opening the file  %s.\n", "hs_medium");
        exit(1);
    }
    if ((hs_hard = fopen("hs_hard", "r")) == NULL)
    {
        printf("\nError while opening the file  %s.\n", "hs_hard");
        exit(1);
    }


    char *pos;
    for(int i=0; i<3; i++)
    {
        fgets(easy[i].name, 80, hs_easy);
        if ((pos=strchr(easy[i].name, '\n')) != NULL)
            *pos = '\0';

        fgets(medium[i].name, 80, hs_medium);
        if ((pos=strchr(medium[i].name, '\n')) != NULL)
            *pos = '\0';

        fgets(hard[i].name, 80, hs_hard);
        if ((pos=strchr(hard[i].name, '\n')) != NULL)
            *pos = '\0';
    }
    fclose(hs_easy);
    fclose(hs_hard);
    fclose(hs_medium);
}
void handle_bitmaps(int what_to_do)
{
    switch(what_to_do)
    {
    case LOAD:
    tiles = al_load_bitmap("images/tiles.jpg");
    mine = al_load_bitmap("images/mine30x30.jpg");
    timing = al_load_bitmap("images/timing.jpg");
    flag = al_load_bitmap("images/flag23x23.jpg");
    clockk = al_load_bitmap("images/clock.jpg");
    left_edge = al_load_bitmap("images/left_edge.jpg");
    lower_left_corner = al_load_bitmap("images/lower_left_corner.jpg");
    lower_right_corner = al_load_bitmap("images/lower_right_corner.jpg");
    bottom_edge = al_load_bitmap("images/bottom_edge.jpg");
    upper_right_corner = al_load_bitmap("images/upper_right_corner.jpg");
    upper_left_corner = al_load_bitmap("images/upper_left_corner.jpg");
    upper_edge = al_load_bitmap("images/upper_edge.jpg");
    game_button = al_load_bitmap("images/game_button.jpg");
    options_button = al_load_bitmap("images/options_button.jpg");
    help_button = al_load_bitmap("images/help_button.jpg");
    first_upper_edge = al_load_bitmap("images/first_upper_edge.jpg");
    game_menu = al_load_bitmap("images/game_menu.jpg");
    options_menu = al_load_bitmap("images/options_menu.jpg");
    help_menu = al_load_bitmap("images/help_menu.jpg");
    level_menu = al_load_bitmap("images/level_menu.jpg");
    bomb_death = al_load_bitmap("images/bomb_death.jpg");
    bomb_misflagged = al_load_bitmap("images/bomb_misflagged.jpg");
    customized_menu = al_load_bitmap("images/customized_menu.jpg");
    highscores_menu = al_load_bitmap("images/highscores_menu.jpg");
    save_score = al_load_bitmap("images/save_score.jpg");

        break;
    case DESTROY:
        al_destroy_bitmap(tiles);
        al_destroy_bitmap(mine);
    al_destroy_bitmap(timing);
    al_destroy_bitmap(flag);
    al_destroy_bitmap(clockk);
    al_destroy_bitmap(left_edge);
    al_destroy_bitmap(lower_left_corner);
    al_destroy_bitmap(lower_right_corner);
    al_destroy_bitmap(bottom_edge);
    al_destroy_bitmap(upper_left_corner);
    al_destroy_bitmap(upper_right_corner);
    al_destroy_bitmap(upper_edge);
    al_destroy_bitmap(game_button);
    al_destroy_bitmap(help_button);
    al_destroy_bitmap(options_button);
    al_destroy_bitmap(first_upper_edge);
    al_destroy_bitmap(game_menu);
    al_destroy_bitmap(help_menu);
    al_destroy_bitmap(options_menu);
    al_destroy_bitmap(level_menu);
    al_destroy_bitmap(bomb_death);
    al_destroy_bitmap(bomb_misflagged);
    al_destroy_bitmap(customized_menu);
    al_destroy_bitmap(highscores_menu);
    al_destroy_bitmap(save_score);
        break;
    }
}
int initialization()
{
    srand(time(NULL));
    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    if(!al_init_image_addon())
    {
        fprintf(stderr, "Error while initializing image addon!\n");
        return -1;
    }
    if(!al_init_font_addon())
    {
        fprintf(stderr, "Error while initializing font addon!\n");
        return -1;
    }
      if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Error while initializing primitives addon!\n");
        return -1;
    }
      if(!al_init_ttf_addon())
    {
        fprintf(stderr, "Error while initializing ttf addon!\n");
        return -1;
    }
      if(!al_install_mouse())
    {
        fprintf(stderr, "Error while installing mouse!\n");
        return -1;
    }
      if(!al_install_keyboard())
    {
        fprintf(stderr, "Error while installing keyboard!\n");
        return -1;
    }
    font=al_load_ttf_font("Courier New.ttf",14,NULL);
}
void draw_frames(int Screenwidth, int Screenheight, int Grid_width, int Grid_height)
{
            al_draw_bitmap(lower_left_corner,0,Screenheight-43,0);
            al_draw_bitmap(lower_right_corner,Screenwidth-32,Screenheight-43,0);
            al_draw_bitmap(upper_right_corner,Screenwidth-32,0,0);
            al_draw_bitmap(upper_left_corner,0,0,0);
            for (int i=1; i<=Grid_width-2; i++)
            {
                al_draw_bitmap(upper_edge,i*32,0,0);
                al_draw_bitmap(bottom_edge,i*32,Screenheight-43,0);
            }
                for (int j=1; j<=Grid_height-2; j++)
            {
                al_draw_bitmap(left_edge,0,j*32,0);
                al_draw_bitmap(left_edge,Grid_width*32-32,j*32,0);
            }
            al_draw_bitmap(game_button,32,0,0);
            al_draw_bitmap(options_button,32+96,0,0);
            al_draw_bitmap(help_button,32+96+96,0,0);
            al_draw_bitmap(first_upper_edge,32+96+96+96,0,0);
}
void register_event_sources()
{
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}
void initializing_menu_structure(struct Menu *menu)
{
    menu->won_menu_opened=false;
    menu->dont_touch_the_board=false;
    menu->level_menu_opened=false;
    menu->level_menu_really_opened=false;
    menu->game_menu_opened=false;
    menu->options_menu_opened=false;
    menu->help_menu_opened = false;
    menu->customized_menu_opened=false;
    menu->highscores_menu_opened=false;
    menu->customized_heigth=10;
    menu->customized_width=10;
    menu->customized_level=1;
    menu->game_menu_clicks=0;
    menu->options_menu_clicks=0;
    menu->lvl_hard=false;
    menu->lvl_easy=true;
    menu->lvl_medium=false;
}
void handle_help_menu(struct Menu *menu, int x,int y)
{
    if((x<7 || y>1 || x>9) && menu->help_menu_opened)//klikniecie nie w menu gdy jest ono otwarte zamyka je i nie powoduje zmian na mapie
    {
        menu->dont_touch_the_board=true;
        menu->help_menu_opened=false;
    }
    if(y==0 && (x==7 || x==8 || x==9))
    {
        menu->help_menu_opened=true;
    }

    if(menu->help_menu_opened)
        if(x>6 && x<10 && y==1)
        {
            system("firefox http://www.chezpoor.com/minesweeper/help/minehelpinstructions.html");
            menu->dont_touch_the_board=true;
            menu->help_menu_opened=false;
        }

    if(y==0 && (x==7 || x==8 || x==9) && menu->help_menu_opened) al_draw_bitmap(help_menu, 224,32,0);
}

void handle_won_menu(struct Menu *menu, int x, int y, int seconds)
{
    if(menu->won_menu_opened)
    {
        menu->dont_touch_the_board=true;
        if(x>4 && x<7 && y==9)
        {
            fields_to_open=1;
            menu->won_menu_opened=false;
            save_highscore_change(menu->lvl_hard,menu->lvl_medium,menu->lvl_easy,name,(int)seconds);
            load_highscores(easy, medium, hard);
        }
    }
    if(!menu->won_menu_opened) menu->dont_touch_the_board=false;
    if(menu->won_menu_opened)
    {
        al_draw_bitmap(save_score,32,32,0);
        player_name(&coord_x, name);
    }
}

void handle_customized(struct Menu *menu, int *x, int *y, float *xf, float *yf)
{
    int xx=*x, yy = *y, xff = *xf, yff = *yf;
    if(menu->customized_menu_opened)
    {
        menu->dont_touch_the_board=true;
        if(*xf>=6 && *xf<7 && *yf>=2 && *yf<2.5) menu->customized_width++;
        if(*xf>=6 && *xf<7 && *yf>=2.5 && *yf<3) menu->customized_width--;
        if(*xf>=6 && *xf<7 && *yf>=4 && *yf<4.5) menu->customized_heigth++;
        if(*xf>=6 && *xf<7 && *yf>=4.5 && *yf<5) menu->customized_heigth--;
        if(*xf>=6 && *xf<7 && *yf>=6 && *yf<6.5) menu->customized_level++;
        if(*xf>=6 && *xf<7 && *yf>=6.5 && *yf<7) menu->customized_level--;
        if(menu->customized_width>40 || menu->customized_width<10) menu->customized_width=10;
        if(menu->customized_heigth>20 || menu->customized_heigth<10) menu->customized_heigth=10;
        if(menu->customized_level>8 || menu->customized_level<1) menu->customized_level=1;
        if (!(xx>3 && xx<6 && yy==9))
        {
            *xf=0;
            *yf=0;
            *x=0;
            *y=0;
        }
    }

    if(!menu->customized_menu_opened) menu->dont_touch_the_board=false;
    if(menu->customized_menu_opened)
    {
        al_draw_bitmap(customized_menu,32,32,0);
        al_draw_bitmap_region(timing,(menu->customized_width/10+1)*13,0,13,23,163,68,0);
        al_draw_bitmap_region(timing,(menu->customized_width%10+1)*13,0,13,23,163+13,68,0);
        al_draw_bitmap_region(timing,(menu->customized_heigth/10+1)*13,0,13,23,163,132,0);
        al_draw_bitmap_region(timing,(menu->customized_heigth%10+1)*13,0,13,23,163+13,132,0);
        al_draw_bitmap_region(level_menu,0,(menu->customized_level-1)*32,32,32,160,192,0);
    }
    if(menu->customized_menu_opened)
        if(xx>5 && xx<8 && yy==9) menu->customized_menu_opened=false;
}
void handle_highscores_menu(struct Menu *menu, int *x, int *y)
{
    int xx=*x, yy = *y;

    if(!menu->highscores_menu_opened) menu->dont_touch_the_board=false;
    if(menu->highscores_menu_opened)
    {
        al_draw_bitmap(highscores_menu,32,32,0);
        for(int i=0; i<3; i++)
        {
            al_draw_text(font, al_map_rgb(0, 0, 0), 192,60+i*16, 1,easy[i].name);
            al_draw_text(font, al_map_rgb(0, 0, 0), 192,136+i*16, 1,medium[i].name);
            al_draw_text(font, al_map_rgb(0, 0, 0), 192,219+i*16, 1,hard[i].name);
        }
    }
    if(menu->highscores_menu_opened)
    {
        menu->dont_touch_the_board=true;
        if(xx>4 && xx<7 && yy==9) menu->highscores_menu_opened=false;
    }
}

void handle_level_menu(struct Menu *menu, int x, int y)
{
    if(menu->level_menu_opened)
            {
                al_draw_bitmap(level_menu,160,32,0);
                al_draw_bitmap(game_menu, 32,32,0);
                menu->level_menu_really_opened=true;
                menu->dont_touch_the_board=true;
            }
    if(!menu->level_menu_opened) menu->dont_touch_the_board=false;
}
void handle_game_menu(struct Menu *menu, int x, int y)
{
    if((!(y==0 && (x==1 || x==2 || x==3)) || (x<1 || y>6 || x>3)) && menu->game_menu_opened)//klikniecie nie w menu gdy jest ono otwarte zamyka je i nie powoduje zmian na mapie
    {
                    menu->game_menu_clicks=2; // wylaczenie menu dopiero po obiegu
                    menu->dont_touch_the_board=true;
    }
}
void handle_options_menu(struct Menu *menu, int x, int y)
{
    if((!(y==0 && (x==4 || x==5 || x==6)) || (x<4 || y>3 || x>6)) && menu->options_menu_opened)//klikniecie nie w menu gdy jest ono otwarte zamyka je i nie powoduje zmian na mapie
                {
                    menu->options_menu_clicks=2; // wylaczenie menu dopiero po obiegu
                    menu->dont_touch_the_board=true;
                }
}
void draw_flags(int *flags, int Screenheight, int Screenwidth, int Grid_height)
{
    al_draw_bitmap_region(flag,0,0,23,23,Screenwidth-112,Grid_height*32-23,0);
    if(*flags>=0)
    {
        al_draw_bitmap_region(timing,(*flags/100+1)*13,0,13,23,Screenwidth-89,Grid_height*32-23,0);
        al_draw_bitmap_region(timing,((*flags%100)/10+1)*13,0,13,23,Screenwidth-76,Grid_height*32-23,0);
        al_draw_bitmap_region(timing,(*flags%10+1)*13,0,13,23,Screenwidth-63,Grid_height*32-23,0);
    }
    else
    {
    al_draw_bitmap_region(timing,0,0,13,23,Screenwidth-89,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,(-1*(*flags)/10+1)*13,0,13,23,Screenwidth-76,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,(-1*(*flags)%10+1)*13,0,13,23,Screenwidth-63,Grid_height*32-23,0);
    }
}

void draw_mines(int *mines_nr, int Screenheight, int Screenwidth, int Grid_height)
{
    al_draw_bitmap_region(mine,0,0,30,30,Screenwidth/2-35,Grid_height*32-27,0);
    al_draw_bitmap_region(timing,(*mines_nr/100+1)*13,0,13,23,Screenwidth/2-5,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,((*mines_nr%100)/10+1)*13,0,13,23,Screenwidth/2+8,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,(*mines_nr%10+1)*13,0,13,23,Screenwidth/2+21,Grid_height*32-23,0);
}
void draw_time(float *secondsf,int Screenheight,int Screenwidth,int Grid_height)
{
    int seconds = (int)(*secondsf);
    al_draw_bitmap_region(clockk,0,0,23,23,50,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,((int)seconds/100+1)*13,0,13,23,50+23,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,(((int)seconds%100)/10+1)*13,0,13,23,50+23+13,Grid_height*32-23,0);
    al_draw_bitmap_region(timing,((int)seconds%10+1)*13,0,13,23,50+23+13+13,Grid_height*32-23,0);
}
