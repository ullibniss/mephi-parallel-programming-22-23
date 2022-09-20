import random

def array_gen(amount: int=10, size: int=10000000):
    for i in range(amount):
        mas = [str(random.randint(0, size)) for a in range(size)]
        mas_str = ' '.join(mas)
        with open(f"arrays_dir/array{i}.txt", "a") as file:
            file.write(mas_str)
            print(f"Array { i } generated")

if __name__ == '__main__':
    array_gen()