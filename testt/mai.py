def read_file(file_name):
    with open(file_name) as file:
        lines = file.readlines()
    return lines

def read_first_2_elements(lines):
    result = []
    for line in lines:
        result.append(line.split()[0:2])
    return result

def convert_tol_ist(lines):
    result = []
    for line in lines:
        result.append([i for i in line])
    return result

def print_to_file(file_name, lines):
    with open(file_name, 'w') as file:
        for line in lines:
            file.write("["+ line[1]+","+line[0]+"]"+"\n")

def a():
    hex_file_path = 'test3_2.txt'  # Replace with the actual file path

    int_list = []

    with open(hex_file_path, 'r') as file:
        lines = file.readlines()

        for i in range(0, len(lines), 10):
            hex_lines = lines[i:i+10]

            int_set = []
            for line in hex_lines:
                hex_num = line.strip('[]\n').replace(',', '')
                int_num = int(hex_num, 16)
                int_set.append(int_num)

            int_list.append(int_set)

    return int_list
def b(int_list):
    average_list = []

    for sublist in int_list:
        sublist_average = sum(sublist) / len(sublist)
        average_list.append(sublist_average)
    divided_list = [num / 100 for num in average_list]

    print(divided_list)





def main():
    lines = read_file('test2.txt')
    lines = read_first_2_elements(lines)
    lines = convert_tol_ist(lines)
    print_to_file('test3_2.txt', lines)
    int_list =  a()
    b(int_list)
    

if __name__ == '_main_':
    main()