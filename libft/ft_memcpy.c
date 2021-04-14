#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdest;
	size_t			i;

	i = 0;
	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dest;
	while (i < n && (dest || src))
	{
		cdest[i] = csrc[i];
		++i;
	}
	return (dest);
}
