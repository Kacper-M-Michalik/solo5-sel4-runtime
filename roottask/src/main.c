#include <sel4/sel4.h>
#include <sel4runtime.h>
#include <simple/simple.h>
#include <simple-default/simple-default.h>
#include <sel4platsupport/bootinfo.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    //Setup logging/debugging info
    //seL4_CapInitThreadTCB provided by sel4runtime.h
    NAME_THREAD(seL4_CapInitThreadTCB, "roottask");
    zf_log_set_tag_prefix("ROOTTASK:");

    //Read boot up information
    seL4_BootInfo* bootInfo = platsupport_get_bootinfo();
    ZF_LOGF_IF(bootInfo == NULL, "Failed to get bootinfo.");

    size_t initialCNodeSize = 1lu<<(bootInfo->initThreadCNodeSizeBits);
    printf("Initial CNode is %zu slots in size\n", initialCNodeSize);

    simple_t simple_env;  
    simple_default_init_bootinfo(&simple_env, bootInfo);
    simple_print(&simple_env);

    printf("Read bootinfo successfully.\n");

    while (true) {}

    return 0;
}