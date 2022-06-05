# Class: 資工三
# Student ID: 107590061
# Name: 巫啟裕

def fcfs(current, register):
    result = abs(current - register[0])

    for i in range(len(register) - 1):
        result += abs(current - register[0])

    print("FCFS total distance: " + str(result))

def sstf(current, register, max_value):
    temp = register[0]
    result = 0
    index = 0

    temp.sort()

    while(len(temp) != 0):
        min_value = max_value

        for i in range(len(temp)):
            if(min_value > abs(current - temp[i])):
                min_value = abs(current - temp[i])
                index = i

        result += abs(temp[index] - current)
        current = temp[index]

        temp.pop(index)

    print("SSTF total distance: " + str(result))

def scan(current, register, max_value):
    temp = register[:]

    temp.append(current)
    temp.sort()

    left_result =  2 * current + abs(current - temp[-1])

    print("Scan left total distance: " + str(left_result))

    right_result = 2 * (max_value - current) + abs(current - temp[0])

    print("Scan right total distance: " + str(right_result))


def cscan(current, register, max_value):
    temp = register[:]

    temp.append(current)
    temp.sort()

    left_result =  2 * max_value - abs(current - temp[temp.index(current) + 1])

    print("C-Scan left total distance: " + str(left_result))

    right_result = 2 * max_value - abs(current - temp[temp.index(current) - 1])

    print("C-Scan right total distance: " + str(right_result))

def main():
    max_value = int(input("Enter the maximum of disk storage: ")) - 1
    current = int(input("Enter the current cylinder: "))
    register = input("Enter the queue of request in FIFO order: ")

    register = register.split()
    register_list = []

    for i in range(len(register)):
        register_list.append(int(register[i]))

    fcfs(current, register_list)
    sstf(current, register_list, max_value)
    scan(current, register_list, max_value)
    cscan(current, register_list, max_value)

main()