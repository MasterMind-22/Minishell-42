int	ft_count_arguments(char *input)
{
	t_vars	var;

	var.i = 0;
	var.count = 0;
	while (input[var.i])
	{
		while (input[var.i] && is_space(input[var.i]))
			var.i++;
		if (input[var.i] == '\"')
		{
			var.i++;
			var.count++;
			while (input[var.i] && input[var.i] != '\"')
				var.i++;
			var.i++;
		}
		else if (input[var.i])
		{
			while (input[var.i] && input[var.i] != ' ' && input[var.i] != '\"')
				var.i++;
			var.count++;
		}
	}
	return (var.count);
}