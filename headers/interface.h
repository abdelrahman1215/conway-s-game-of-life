#ifndef INTERFACE_H
#define INTERFACE_H

#define button_index 1
#define box_index 2
#define button_highlight_index 3

void render_exit_button();
void render_play_pause_button();
void render_reset_button();

void highlight_exit_button();
void highlight_play_pause_button();
void highlight_reset_button();


void unhighlight_exit_button();
void unhighlight_play_pause_button();
void unhighlight_reset_button();

void *render_interface(void *);

#endif