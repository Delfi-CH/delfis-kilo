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
char *find_bin_in_path(const char *binname);

#endif /* DELFI_H */