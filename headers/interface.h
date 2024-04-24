#ifndef INTERFACE_H
#define INTERFACE_H

void render_exit_button();
void render_play_pause_button();
void render_reset_button();

void *print_pause_play_state(void *);
void *display_coord(void *);
void *print_speed(void *);

#endif