#ifndef SHELL_H
#define SHELL_H

extern void shell_init();
extern void shell_input(unsigned char c);
extern void execute_command(char *cmd, char *arg);
extern unsigned char hex_to_int(char *str);
extern int strcmp(const char *s1, const char *s2);
extern void get_date_string(void); 
extern void lambdafetch(void);

#endif