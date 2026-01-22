#ifndef KILO_H
#define KILO_H

#include <termios.h>
#include <time.h>

/* macros */
#define CTRL_KEY(k) ((k) & 0x1f)
#define EDITOR_VER "0.1"
#define EDITOR_TAB_STOP 8
#define EDITOR_QUIT_TIMES 3

/* structs */
typedef struct erow {
    int size;
    char *chars;
    int rsize;
    char *render;
} erow;

struct editorConfig {
    int cx, cy, rx;
    int rowoff, coloff;
    int screenrows, screencols;
    int numrows;
    erow *row;
    char statusmsg[80];
    time_t statusmsg_time;
    struct termios orig_termios;
    char *filename;
    int dirty;
};

extern struct editorConfig E;

enum editorKey {
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

/* abuf */
struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT { NULL, 0 }

// Term
void die(const char *s);
void disable_raw(void);
void enable_raw(void);
int  editor_read(void);
int  get_cursor_pos(int *rows, int *cols);
int  get_window_size(int *rows, int *cols);

// Buffer
void ab_append(struct abuf *ab, const char *s, int len);
void ab_free(struct abuf *ab);

// Input
void editor_move_cursor(int key);
void editor_process(void);
char *editor_prompt(char *prompt, void (*callback)(char *, int));

// Output
int  editor_row_cx2rx(erow *row, int cx);
int  editor_row_rx2cx(erow *row, int rx);
void editor_scroll(void);
void editor_draw_rows(struct abuf *ab);
void editor_draw_bar(struct abuf *ab);
void editor_draw_statusmsg(struct abuf *ab);
void editor_clear(void);
void editor_set_statusmsg(const char *fmt, ...);

// Row
void editor_update_row(erow *row);
void editor_insert_row(int at, char *s, size_t len);
void editor_row_append_string(erow *row, char *s, size_t len);
void editor_row_insert_char(erow *row, int at, int c);
void editor_row_del_char(erow *row, int at);
void editor_free_row(erow *row);
void editor_del_row(int at);

// Editing
void editor_insert_char(int c);
void editor_del_char(void);
void editor_insert_newline(void);

// File I/O
char *editor_rows_to_str(int *buflen);
void editor_save(void);
void editor_open(char *filename);

// Find
void editor_find_callback(char *query, int key);
void editor_find(void);

// INIT
void init(void);

#endif /* KILO_H */
