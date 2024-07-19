import csv
import random
import string


def generate_random_headers(num_headers):
    return [
        "".join(random.choices(string.ascii_uppercase, k=50)) for _ in range(num_headers)
    ]


def generate_random_row(num_columns):
    return [str(random.randint(100000, 9999999999)) for _ in range(num_columns)]


def generate_csv_file(filename, num_headers, num_rows):
    headers = generate_random_headers(num_headers)
    rows = [generate_random_row(num_headers) for _ in range(num_rows)]

    with open(filename, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(headers)
        writer.writerows(rows)

    return headers, rows


filename = "tests/mock/many_numbers.csv"
num_headers = 256
num_rows = 30
headers, rows = generate_csv_file(filename, num_headers, num_rows)

filename, headers[:5], rows[:5]
