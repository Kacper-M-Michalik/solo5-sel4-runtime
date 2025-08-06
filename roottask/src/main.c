#include <sel4/sel4.h>
#include <sel4runtime.h>
#include <simple/simple.h>
#include <simple-default/simple-default.h>
#include <sel4platsupport/bootinfo.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    printf("Hello, World!\n");

    seL4_BootInfo *info = platsupport_get_bootinfo();

    size_t initial_cnode_object_size = 1lu<<(info->initThreadCNodeSizeBits);
    printf("Initial CNode is %zu slots in size\n", initial_cnode_object_size);

    simple_t simple_env;  
    simple_default_init_bootinfo(&simple_env, info);

    printf("Test\n");

    return 0;
}