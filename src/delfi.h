#ifndef DELFI_H
#define DELFI_H


// Runfile

struct runfile {
    char *name;
    char *bin;
    char *argv;
};

extern struct runfile R;

char *trim_runfile(char *s);
void parse_runfile(void);
int exec_runfile(void);

#endif /* DELFI_H */