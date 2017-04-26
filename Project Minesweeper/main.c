#include"header.h"

int Display_x=500;
int Display_y=200;



int main(int argc, char **argv)
{
    struct Menu *menu_pointer = &menu;
    initializing_menu_structure(menu_pointer);
    initialization();
    Grid_height=12; Grid_width=12;
    fields_to_open=5; Lvl=9;
    Screenwidth = Grid_width*32; Screenheight = Grid_height*32+11;
    display = al_create_display(Screenwidth, Screenheight);
    al_set_window_position(display,Display_x,Display_y);
    al_set_window_title(display,"Minesweeper");

START:
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_resize_display(display,Grid_width*32,Grid_height*32+11);
    al_set_window_position(display,Display_x,Display_y);
    Screenwidth = Grid_width*32; Screenheight = Grid_height*32+11;
    load_highscores(easy, medium, hard);

    const float FPS=5;
    float seconds=0, xf=0, yf=0;
    bool playing=false, stop = false,lost = false, won=false, draw=false;
    int mines_nr=0, flags=0, len=32, message_box_lost=1, *pt, x=0, y=0;
    int field[Declared_Grid_width][Declared_Grid_height], sfield[Declared_Grid_width][Declared_Grid_height];
    int customized_heigth=10, customized_width=10,customized_level=1; coord_x=70;

    handle_bitmaps(LOAD);

    for(int i=0; i <Declared_Grid_width; i++)
        for(int j=0; j<Declared_Grid_height; j++)
            field[i][j] = 0;

    mines_nr = place_mines(sfield,field, Grid_height, Grid_width, Lvl);
    fields_to_open = (Grid_height-2) * (Grid_width-2) - mines_nr;
    prepare_grid(sfield,field, Grid_height, Grid_width);
    flags = mines_nr;
    pt=&fields_to_open;

    timer=al_create_timer(1.0/FPS);
    event_queue = al_create_event_queue();
    register_event_sources();

    for(int i=0; i<21; i++)
        name[i] = '\0';

    al_start_timer(timer);

    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {
        al_get_keyboard_state(&keyboard);
        al_get_mouse_state(&mouse);

        if(fields_to_open==0 && !menu.won_menu_opened && !lost)
        {
            stop=true;
            won=true;
            menu.won_menu_opened=true;
        }

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue,&event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            x=(event.mouse.x)/len; y=(event.mouse.y)/len;
            xf=(event.mouse.x)/(float)len; yf=(event.mouse.y)/(float)len;

            if(event.mouse.button &1)
            {
                handle_won_menu(menu_pointer,x,y,seconds);
                handle_customized(menu_pointer,&x,&y,&xf,&yf);
                handle_highscores_menu(menu_pointer, &x, &y);

                if(x>3 && x<6 && y==9 && menu.customized_menu_opened)
                {
                    menu.customized_menu_opened = false;
                    Grid_height=menu.customized_heigth+2;
                    Grid_width=menu.customized_width+2;
                    Lvl=10-menu.customized_level;
                    goto START;
                }

                if(menu.level_menu_really_opened)
                    if(x>4 && x <6 && y>0 && y<9)
                        switch(y)
                        {
                        case 1: Lvl=9; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 2: Lvl=8; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 3: Lvl=7; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 4: Lvl=6; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 5: Lvl=5; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 6: Lvl=4; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 7: Lvl=3; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        case 8: Lvl=2; menu.level_menu_opened=false; menu.level_menu_really_opened=false; goto START; break;
                        }
                    else
                    {
                        menu.level_menu_really_opened=false;
                        menu.dont_touch_the_board=true;
                        menu.level_menu_opened=false;
                    }

                if(menu.options_menu_opened && menu.options_menu_clicks==1)
                    if(x>3 && x<8)
                    {
                        if(y==1) {menu.options_menu_clicks=0; menu.options_menu_opened=false; goto START;}
                        if(y==2) {menu.options_menu_clicks=0; stop=true;}//pause
                        if(y==3) {menu.options_menu_clicks=0; break;}//exit
                    }

                if(menu.game_menu_opened && menu.game_menu_clicks==1)
                    if(x>0 && x<5)
                        switch(y)
                        {
                        case 1:
                            menu.level_menu_opened=true;
                            break;
                        case 2:
                            menu.game_menu_opened=false; menu.game_menu_clicks=0; Lvl=9;
                            Grid_height=12; Grid_width=12;
                            Display_x=500; Display_y=200;
                            menu.lvl_easy=true;
                            menu.lvl_hard=false;
                            menu.lvl_medium=false;
                            goto START;
                            break;
                        case 3:
                            menu.game_menu_opened=false; menu.game_menu_clicks=0; Lvl=5;
                            Grid_width=22; Grid_height=22;
                            Display_x=400; Display_y=100;
                            menu.lvl_easy=false;
                            menu.lvl_hard=false;
                            menu.lvl_medium=true;
                            goto START;
                            break;
                        case 4:
                            menu.game_menu_opened=true; menu.game_menu_clicks=0; Lvl=2;
                            Grid_width=42; Grid_height=22;
                            menu.lvl_easy=false;
                            menu.lvl_hard=true;
                            menu.lvl_medium=false;
                            goto START;
                            break;
                        case 5:
                            menu.customized_menu_opened = true;
                            menu.dont_touch_the_board=true;
                            break;
                        case 6:
                            menu.highscores_menu_opened=true;
                            menu.dont_touch_the_board=true;
                            break;
                        }

                handle_game_menu(menu_pointer,x,y);
                handle_options_menu(menu_pointer,x,y);
                handle_help_menu(menu_pointer,x,y);
                if(y==0)//kliknieciew gorny przycisk zamyka(otwiera) menu i u(nie)mozliwia dalszą grę
                {
                    if(x==1 || x==2 || x==3)
                    {
                        menu.game_menu_clicks++;//wylaczenie
                        menu.game_menu_opened=true;
                    }
                    if(x==4 || x==5 || x==6)
                    {
                        menu.options_menu_clicks++;
                        menu.options_menu_opened=true;
                    }
                    handle_help_menu(menu_pointer,x,y);
                }

                else if(!menu.dont_touch_the_board)
                {
                    stop=false;
                    if(playing==false) playing=true;
                    if(sfield[x][y]==11);
                    else if (field[x][y]==0) show_empty_field(x,y,sfield,field,ALL_DIR, Grid_height, Grid_width, pt);
                    else if(!won && !lost)
                    {
                        sfield[x][y]=field[x][y];
                        if(sfield[x][y]==9) lost=true;
                        fields_to_open--;
                    }
                }
            }
            else if(event.mouse.button &2)
            {
                if(!menu.dont_touch_the_board)
                {
                    stop=false;
                    if(playing==false) playing=true;
                    if (sfield[x][y]==12) sfield[x][y]=10;
                    else if(sfield[x][y]==11 && !won && !lost)
                    {
                        sfield[x][y]=12;
                        flags++;
                    }
                    else
                    {
                        if(flags>-Flags_below_zero && (sfield[x][y]!=field[x][y]) && !won && !lost)
                        {
                            sfield[x][y]=11;
                            flags--;
                        }
                    }
                }
            }
        }
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if (sfield[x][y]==9) stop=true;
            if(playing && seconds<999 && !stop && !won && !lost) seconds += 1/FPS;
            draw=true;
        }

        if(lost && message_box_lost==1)
        {
            message_box_lost++;
            al_show_native_message_box(display,"YOU LOST","Maybe next time you'll do better!","",NULL,NULL);
        }

        if(draw)
        {
            draw=false;
            draw_frames(Screenwidth, Screenheight, Grid_width, Grid_height);
            for (int i=1; i<=Grid_width-2; i++)
                for (int j=1; j<=Grid_height-2; j++)
                {
                    if(won && sfield[i][j]!=field[i][j]) sfield[i][j]=11;
                    if (sfield[x][y]==9)
                    {
                        al_draw_bitmap(bomb_death,x*len,y*len,0);
                        if(sfield[i][j]==11)
                        {
                            if(field[i][j]!=9);
                        }
                        else
                            sfield[i][j]=field[i][j];
                        lost=true;
                    }
                    al_draw_bitmap_region(tiles,sfield[i][j]*len,0,len,len,i*len,j*len,0);
                    if(sfield[i][j]==11 && lost)
                    {
                        if(field[i][j]!=9)
                            al_draw_bitmap(bomb_misflagged,i*len,j*len,0);
                        if(field[i][j]==9)
                            sfield[i][j]=field[i][j];
                    }
                    draw_mines(&mines_nr, Screenheight, Screenwidth, Grid_height);
                    draw_flags(&flags,Screenheight,Screenwidth,Grid_height);
                    draw_time(&seconds,Screenheight,Screenwidth,Grid_height);
                }
            handle_level_menu(menu_pointer,x,y);
            if(menu.game_menu_clicks==2)
            {
                menu.game_menu_opened=false;
                menu.game_menu_clicks=0;
            }
            if(menu.options_menu_clicks==2)
            {
                menu.options_menu_opened=false;
                menu.options_menu_clicks=0;
            }
            handle_help_menu(menu_pointer,x,y);
            if(y==0 && (x==1 || x==2 || x==3) && menu.game_menu_clicks==1) al_draw_bitmap(game_menu, 32,32,0);
            if(y==0 && (x==4 || x==5 || x==6) && menu.options_menu_clicks==1) al_draw_bitmap(options_menu, 128,32,0);
            handle_customized(menu_pointer,&x,&y,&xf,&yf);
            handle_highscores_menu(menu_pointer,&x,&y);
            handle_won_menu(menu_pointer,x,y,seconds);
            al_flip_display();
            al_clear_to_color(al_map_rgb(50,50,50));
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    handle_bitmaps(DESTROY);
    return 0;
}

