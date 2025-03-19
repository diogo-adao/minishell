/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:41:05 by ppassos           #+#    #+#             */
/*   Updated: 2025/03/12 14:11:04 by ppassos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_type(t_token *list)
{
    if (ft_strncmp(list->value, ">", 2) == 0 )
        return(OUTPUT);
    if (ft_strncmp(list->value, ">>", 3) == 0 )
        return(APPEND);
    if (ft_strncmp(list->value, "<", 2) == 0 )
        return(INPUT);
    if (ft_strncmp(list->value, "<<", 3) == 0 )
        return(HEREDOC);
    return(0);
}
int redir_count(t_token *list)
{
     int i;
     
    i = 0;
    while (list != NULL)
    {
        if (list && list->type == STRING)
            list = list->next;
        if (list && list->type == REDIR)
        {
            i += 2;
            list = list->next;
            list = list->next;
        }
        if (list && list->type == PIPE)
            break;
    }
    return (i);
}

int string_count(t_token *list)
{
    int i;

    i = 0;
    while (list)
    {
        if (list && list->type == STRING)
        {
            i++;
            list = list->next;
        }
        if (list && list->type == REDIR)
        {
            list = list->next;
            list = list->next;
        }
        if (list && list->type == PIPE)
            break;
    }
    return (i);
}
char **arg_fill(char **args, t_token *list, int i)
{

    i = 0;
    while (list && !(list->type == PIPE))
    {
        if (list && list->type == STRING)
            args[i++] = ft_strdup(list->value);
        if (list && list->type == REDIR)
            list = list->next;
        if (list && list->next)
            list = list->next;
        else
            break;
    }
    args[i] = NULL;
    return(args);
}
t_redir **redir_fill(t_redir **redir, t_token *list, int i)
{
    i = 0;
    while (list && !(list->type == PIPE))
    {
        if (list && list->type == REDIR)
        {
            redir[i] = malloc(sizeof(t_redir));
            if (!redir[i])
                    return (NULL);
            redir[i]->flag = get_type(list);
            list = list->next;
            redir[i]->file = ft_strdup(list->value); // problemas aqui
            i++;
        }
        if (list && list->next)
            list = list->next;
        else
            break;
    }
    redir[i] = NULL;
    return(redir);
}
t_cmd *execute_p(t_token *list)
{
    t_cmd *exec;
    t_cmd *head;
    int count_redir;
    int count_s;
    int i;

    exec = malloc(sizeof(t_cmd));
    if (!exec)
        return (NULL);
    ft_memset(exec, 0, sizeof(t_cmd));
    head = exec;
    while (list)
    {
        count_s = string_count(list);
        count_redir = redir_count(list);
        if (count_s > 0)
        {
            exec->args = malloc(sizeof(char *) * (count_s + 1));
            if (!exec->args)
                return (NULL);
            i = 0;
            exec->args = arg_fill(exec->args, list, i);
            count_s = 0;
        }
        if (count_redir > 0)
        {
            exec->redir = malloc(sizeof(t_redir *) * (count_redir / 2 + 1));
            if (!exec->redir)
                return (NULL);
            i = 0;
            exec->redir = redir_fill(exec->redir, list, i);
            count_redir = 0;
        }
        while(list && list->type != PIPE)
            list = list->next;
        if (list && list->type == PIPE) // problemas
        {
            exec->next = malloc(sizeof(t_cmd));
            if (!exec->next)
                return (NULL);
            ft_memset(exec->next, 0, sizeof(t_cmd));
            exec->next->prev = exec;
            exec = exec->next;
        }
        if (list && list->next)
            list = list->next;
        else
            break;
    }
    if (!exec->redir)
        exec->redir = NULL;
    return (head);
}
