void	ft_free_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
		garbage_malloc_free((void **)&arrays[i++]);
	garbage_malloc_free((void **)&arrays);
}
