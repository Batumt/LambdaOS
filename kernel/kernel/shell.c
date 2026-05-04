#include <stdio.h>           
#include <string.h>          

#include <kernel/kernel.h>   
#include <kernel/scrn.h>     
#include <kernel/cmos.h>     
#include <kernel/shell.h>
#include <kernel/irq.h>

char shell_buffer[256];
int buffer_idx = 0;

void shell_prompt(){
    printf("\n$ ");
}

void shell_init(){
    cls();
    printf("Welcome to LambdaOS Alpha !\n");
    printf("Type 'help' for available command list\n");
    shell_prompt();
}

void execute_command(char *cmd, char *arg){
    if (strcmp(cmd, "help") == 0){
    printf("\nCommands: 'help', 'cls', 'date', 'version', ");
    printf("\n'color(e.g color 0x1f)', 'lambdafetch','reboot', 'hi'");
    } else if (strcmp(cmd, "cls") == 0){
        cls();
    } else if (strcmp(cmd, "lambdafetch") == 0){
        lambdafetch();
    }else if (strcmp(cmd, "date") == 0){
        get_date_string();
    } else if (strcmp(cmd, "hi") == 0){
    printf("\nHello, This is LambdaOS !");
    } else if (strcmp(cmd, "version") == 0){
    printf("\nLambdaOS 1.0");
    }else if(strcmp(cmd, "reboot") == 0) {
    printf("\nSystem Rebooting...");

        reboot();
    }else if (strcmp(cmd, "color") == 0){ 
        if(arg == 0){
    printf("\ne.g color 0x0f");
        } else {
            unsigned char new_color = hex_to_int(arg);
            set_screen_attrib(new_color);
            cls(); 
    printf("Color changed !");
        }
    } else if (strlen(cmd) > 0) { 
    printf("\nUnknown command!: ");
    printf("%s", cmd);
    }
}

void shell_input(unsigned char c) {
    if (c == '\n') {
        shell_buffer[buffer_idx] = '\0'; 
        char *cmd = shell_buffer;
        char *arg = 0;

        for(int i = 0; shell_buffer[i] != '\0'; i++){
            if(shell_buffer[i] == ' '){
                shell_buffer[i] = '\0';
                arg = &shell_buffer[i + 1];
                break;
            }
        }
        execute_command(cmd, arg);
        buffer_idx = 0;
        shell_prompt();
    }else if (c == '\b') {
        if (buffer_idx > 0) {
            buffer_idx--;
            putch_backspace();
        }
    }else {
        if (buffer_idx < 256) {
            shell_buffer[buffer_idx++] = c;
            putch(c);
        }
    }
}

void lambdafetch(){
    set_screen_attrib(0x0B); 
    
    printf("\n");
    printf("     .==++++==.          \n");
    printf("     |XXXXXXXX|          \n");
    printf("     '--..|XXX|          LambdaOS v1.0\n");
    printf("          |XXX|          --------------\n");
    printf("          |XXX|          Kernel: Custom x86\n");
    printf("         /XXXXX\\         Arch: i386-elf\n");
    printf("        /XXXXXXX\\        Shell: LambdaShell 0.1\n");
    printf("       /XXX/^\\XXX\\       Display: VGA Text Mode\n");
    printf("      /XXX/   \\XXX\\      Developed by: Batum Topaloglu\n");
    printf("     /XXX/     \\XXX\\     \n");
    printf("  ..|XXX|       |XXX|..  \n");
    printf("  |XXXXX|       |XXXXX|  \n");
    printf("  '-----'       '-----'  \n");
    
    set_screen_attrib(0x0F); 
    printf("\n$ ");
}