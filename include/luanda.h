/**
 * @file luanda.h
 * @brief Luanda main header file
 * @author Artem Budnikov
 * @date 9 March 2020
 * 
 * Luanda is a lightweight debugger controlled by the API described in this file.
 * @see link to docs
 */

/**
 * @brief A handle to an inferior process under the controll of the Luanda debugger.
 * 
 * A 'luanda_inferior_t' is used to refer to an inferior when making Luanda API calls.
 */
typedef int luanda_inferior_t;

/**
 * @brief A handle to a breakpoint set  in a specific indefior process under the controll 
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
 * run debugger
 */
void dbg_inferior_exec(const char *path, const char *argv[]);