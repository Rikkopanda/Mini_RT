#include "parser.h"

t_object	*new_object(t_objectid type, void *object)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->object = object;
	new->next = NULL;
	return (new);
}

t_object	*last_object(t_object *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	append_object(t_object **head, t_object *object)
{
	if (!head)
		return ;
	if (!*head)
		*head = object;
	else
		last_object(*head)->next = object;
}

void	clear_objects(t_object *current)
{
	t_object	*tmp;

	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->object);
		free(tmp);
	}
}

void	object_removetype(t_object **head, t_objectid type)
{
	t_object	*current;
	t_object	*remove;

	current = *head;
	while (current->next)
	{
		// if (current->type == CAMERA)
		// // {
		// // 	// t_camera *carmeraptr;

		// // 	// carmeraptr = current;
			print_camera_data(current);
		// // 	// exit(0);
		// // }
		if (current->next->type == type)
		{
			remove = current->next;
			current->next = remove->next;
			free(remove->object);
			free(remove);
		}
		else
			current = current->next;
	}
	if ((*head)->type == type)
	{
		remove = *head;
		*head = remove->next;
		free(remove->object);
		free(remove);
	}
}
