#ifndef __MODULES_H
#define __MODULES_H

#define true 1
#define false 0

typedef int bool;

typedef struct module_t {
	bool usermode;
	bool enabled;
	bool initialized;
	char* name;
	char* description;
} module_t;

module_t MODULE(char* name, char* description);

void INIT(module_t module);

void DISABLE(module_t module);
void ENABLE(module_t module);

#endif