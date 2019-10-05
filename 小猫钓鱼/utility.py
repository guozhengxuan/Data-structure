import queue


def instructions():
    # brief introduction about the little cat fishing game.
    print('''This program is designed to find out the winner of the game.''')
    print('''Please input numbers marked on cards in order and seperate them with ','.''')
    print('''Each player occupies one row.''')
    print('''Assuming the player who holds the first group of cards plays first.''')


def get_cards():
    # receive cards configurations from each player and put them into storage in the type of queue.
    cards = queue.Queue()
    enter = eval(input())
    for num in enter:
        cards.put(num)
    return cards


def winner(cards1, cards2):
    # imitate the realistic gaming scene then deduce who's the winner.
    assert isinstance(cards1, queue.Queue) and isinstance(cards2, queue.Queue), "assure parameter type is queue"
    table = []
    turn = 'first'
    while not cards1.empty() and not cards2.empty():
        if turn == 'first':
            drop = cards1.get()
            if drop in table:
                for card in table[table.index(drop):]:
                    cards1.put(card)
                table = table[:table.index(drop)]
                cards1.put(drop)
            else:
                table.append(drop)
            turn = 'second'

        elif turn == 'second':
            drop = cards2.get()
            if drop in table:
                for card in table[table.index(drop):]:
                    cards2.put(card)
                table = table[:table.index(drop)]
                cards2.put(drop)
            else:
                table.append(drop)
            turn = 'first'

    if cards2.empty():
        return "First player win!"
    elif cards1.empty():
        return "Second player win!"
