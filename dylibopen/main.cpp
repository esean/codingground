#include <iostream>
#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    void* Bus1a_handle = dlopen("libftd2xx.dylib", RTLD_LOCAL);
    if (Bus1a_handle) {
	printf("[%s] Opened libftd2xx.dylib\n",__FILE__);
#if 0
        char* (*b1a_name)() = dlsym(Bus1a_handle, "B1a_name");
        if (b1a_name) {
            printf("[%s] libBus1a.B1a_name() = %s\n",
                __FILE__, b1a_name());
        } else {
		printf("[%s] could not find symbol\n",__FILE__);
	}
#endif
    }
    else {
        printf("[%s] Unable to open libBus1a.dylib: %s\n",
            __FILE__, dlerror());
    }
    dlclose(Bus1a_handle);

    return 0;
}
