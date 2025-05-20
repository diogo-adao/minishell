#include "../../../includes/minishell.h"

int *exit_status_ptr(void)
{
    static int  status = 0;
    return (&status);
}

void set_exit_status(int new_status)
{
    *exit_status_ptr() = new_status;
}

int get_exit_status(void)
{
    return (*exit_status_ptr());
}