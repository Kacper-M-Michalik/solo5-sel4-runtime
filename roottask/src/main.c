#include <sel4/sel4.h>
#include <sel4runtime.h>
#include <simple/simple.h>
#include <simple-default/simple-default.h>
#include <stdio.h>

int main(void)
{
    seL4_BootInfo* bootinfo = sel4runtime_bootinfo();
    simple_t simple_env;

    simple_default_init_bootinfo(&simple_env, bootinfo);

    printf("Booted and read BootInfo.");

    return 0;
}
