import copy


class Life:
    row = 30
    col = 60
    __configuration = []
    for i in range(row + 2):
        zero = []
        for j in range(col + 2):
            zero.append(0)
        __configuration.append(zero)

    def __init__(self, living_cells):
        self.living_cells = living_cells
        try:
            for cell_pair in self.living_cells:
                self.__configuration[cell_pair[0]][cell_pair[1]] = 1
        except TypeError:
            raise TypeError("please input living cells' coordinates in tuples.")

    def show(self):
        print("This is the present life configuration:")
        for row in range(1, self.row + 1):
            for col in range(1, self.col + 1):
                if self.__configuration[row][col] == 1:
                    print('*', end=' ')
                else:
                    print(' ', end=' ')
            print('\n')

    def __count_neighbors(self, row, col):
        neighbors = 0
        for around_row in range(row - 1, row + 2):
            for around_col in range(col - 1, col + 2):
                if self.__configuration[around_row][around_col] == 1:
                    neighbors += 1
        neighbors -= self.__configuration[row][col]
        return neighbors

    def update(self):
        new_configuration = copy.deepcopy(self.__configuration)
        for row in range(1, self.row + 1):
            for col in range(1, self.col + 1):
                neighbors = self.__count_neighbors(row, col)
                if neighbors == 3:
                    new_configuration[row][col] = 1
                elif neighbors == 2:
                    continue
                else:
                    new_configuration[row][col] = 0
        self.__configuration = new_configuration


def get_living_cells():
    living_cells = []
    print("Please enter coordinates of living cells, separate them with ','.")
    print("Input -1, -1 to terminate entering.")
    coordinates = eval(input())
    while coordinates != (-1, -1):
        living_cells.append(coordinates)
        coordinates = eval(input())
    return living_cells


def get_command():
    command = input("Continue generate new configuration or not? input y or n: ")
    while command not in ('y', 'Y', 'n', 'N'):
        command = input("Please response with letter y or n: ")
    if command in ('y', 'Y'):
        return True
    else:
        return False
