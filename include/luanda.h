/**
 * @file luanda.h
 * @brief Luanda main header file
 * @author Artem Budnikov
 * @date 9 March 2020
 * 
 * Luanda is a lightweight debugger controlled by the API described in this file.
 * @see https://github.com/budn1k0ver/luanda
 */

/**
 * @brief A handle to an inferior process under the controll of the Luanda debugger.
 * 
 * A 'luanda_inferior_t' is used to refer to an inferior when making Luanda API calls.
 */
typedef int luanda_inferior_t;

/**
 * @brief A handle to a breakpoint set in a specific inferior process under the controll 
 * of the Luanda debugger.
 * 
 * A 'luanda_breakpoint_t' handle is used to refer to a breakpoint in Luanda debugger calls.
 * 
 * A 'luanda_breakpoint_t' handle is only meaningful given a specific inferior. That is, 
 * the handle must always be used in conjuction with a 'luanda_inferior_t'.
 */
typedef int luanda_breakpoint_t;

/**
 * @brief A function pointer used as a callback
 * 
 * @see luanda_breakpoint_set_callback
 */
typedef void (*luanda_breakpoint_callback_t)(luanda_inferior_t, luanda_breakpoint_t);

/**
 * @brief Set the global brakpoint callback.
 * 
 * @param callback A function that will be called whenever a breackpoint is encountered
 */
void luanda_breakpoint_set_callback(luanda_breakpoint_callback_t);

/**
 * @brief Create and execute a new inferior processes.
 * 
 * @param path The full path to the binary to execute.
 * @param argv A NULL terminated list of command line arguments to pass to the inferior process.
 * @return Returns a handle for the new inferior. `luanda_inferior_t`
 * 
 * The argumentsto this function match those of execv(3) 
 */
luanda_inferior_t luanda_inferior_exec(const char *path, char *const argv[]);

/**
 * @brief Set a breakpoint in `inferior` at `location`
 * 
 * `luanda_inferior_set_breakpoint` will set a breakpoint in the inferior 
 * so that when the breakpoint is encountered callbackwill be called
 * 
 * @param inferior The handle of the inferior process in which to set the breakpoint
 * @param location The location at which to set the breakpoint
 * @return Returns a handle for the new breakpoint. `luanda_breakpoint_t`
 */
luanda_breakpoint_t luanda_inferior_set_breakpoint(luanda_inferior_t inferior, char *location);

/**
 * @brief Continue execution of `inferior`
 * 
 * Continue the execution of a stopped process.
 * 
 * @param inferior The handle of a stopped inferior process 
 * which should continue execution.
 */
void luanda_inferior_continue(luanda_inferior_t inferior);