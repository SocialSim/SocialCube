num = 0
with open('log_poisson.txt', 'r') as file:
	lines = file.readlines()
	for l in lines:
		num += int(l.split(' = ')[1])

print('num = ', num)
