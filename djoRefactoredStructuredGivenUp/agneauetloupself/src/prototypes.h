#ifndef PROTOH
#define PROTOH

void interface_make(t_tout* tout);
GtkWidget* interface_make_window();
void interface_make_table_and_buttons_attach_and_link_them(GtkWidget* pVbox,t_tout* tout);
void interface_redraw_positions(t_tout* tout);
void players_game_init(t_player player1_info, t_player player2_info, t_tout* tout);
int memory_get_type_to_unselected(int type);
t_position* memory_get_pos_from_coords(t_coords coords,t_tout* tout);
int players_try_set_selection(t_tout* tout);
void players_empty_selection(t_tout* tout,gboolean force);
void interface_redraw_button(t_position position);

#endif