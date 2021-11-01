/**
  \file      modules.h
  \brief     Modular kernel support.
  \details   This header file is used to support a more modular kernel.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __MODULES_H
#define __MODULES_H

#define true 1
#define false 0

typedef int bool;

int count;

/**
  \struct module_t
  \brief Module typedef struct

  This struct consists of:
	I. usermode: Toggles usermode
	II. enabled: Toggles if the module is enabled
	III. initialized: Toggles if the module has been initialized
	IV. name: The name of the module. Similar to a import in Java, but not backwards
	V. description: The description of the module. This description is displayed with the `man` function
	VI. dependencies: List of strings of dependencies. Each dependency's name should follow the convention established by `name`.
*/
typedef struct module_t {
	bool usermode;
	bool enabled;
	bool initialized;
	char* name;
	char* description;
	char** dependencies;
} module_t;

module_t modules[256];

/**
	\brief Creates a module with the name `name`, and the description `description`
*/
module_t MODULE(char* name, char* description);

/**
	\brief Initializes the module `module`
*/
void INIT(module_t module);

/**
	\brief Disables the module `module`
*/
void DISABLE(module_t module);
/**
	\brief Enables the module `module`
*/
void ENABLE(module_t module);

/**
	\brief Sets dependencies of module `module` to dependencies `dependencies`
*/
void DEPS(module_t module, char** dependencies);

#endif