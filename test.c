char *concatenate_strings(t_node *node, char *s) {
    if (!ft_strncmp(node->type, "space", 5)) {
        return ft_strjoin(s, node->value);
    }
    return s;
}


t_command *create_command(char *s, int fd_in, int fd_out) {
    char **array = ft_array(NULL, s);
    t_command *new = ft_lstnew_cmd(array, fd_in, fd_out);
    return new;
}

// Function to add a command to the list
void add_command_to_list(t_command **cmd, t_command *new) {
    ft_lstadd_back_cmd(cmd, new);
}

void handle_file_descriptors(t_node *node, int *fd_in, int *fd_out) {
    if (!ft_strncmp(node->type, "pipe", 4)) {
        int fd[2];
        pipe(fd);
        *fd_out = fd[1];
        *fd_in = fd[0];
    }
}

void execute_commands(t_command *cmd) 
{
    t_command *tmp = cmd;
    while(tmp) {
        tmp->cmd = ft_pathname(getenv("PATH"), tmp->cmd);
        tmp = tmp->next;
    }
    while(cmd) {
        make_process(cmd);
        cmd = cmd->next;
    }
    wait(NULL);
    wait(NULL);
}

void set_newlist(t_node *node) {
    t_command *cmd = NULL;
    char *s = NULL;
    int fd_out = 1;
    int fd_in = 0;

    while (node) {
        s = concatenate_strings(node, s);
        if (!ft_strncmp(node->type, "pipe", 4) || !ft_strncmp(node->type, "space", 5)) {
            if (s) {
                t_command *new = create_command(s, fd_in, fd_out);
                add_command_to_list(&cmd, new);
                s = NULL;
            }
            handle_file_descriptors(node, &fd_in, &fd_out);
        }
        node = node->next;
    }

    if (s) {
        t_command *new = create_command(s, fd_in, fd_out);
        add_command_to_list(&cmd, new);
    }

    printf("-------------commands------------\n");
    display_cmd(cmd);
    printf("-------------fin commands-------------\n");

    execute_commands(cmd);
}
