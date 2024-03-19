import random


def generate_data(n):
    data = [str(random.randint(1, 100000)) for _ in range(n)]
    return ' '.join(data)


n = int(input("please enter the numbers you want to generate:"))
test_data = generate_data(n)

with open('data.in', 'w') as file:
    file.write(str(n)+' ')
    file.write(test_data)
