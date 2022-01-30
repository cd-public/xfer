import karel

def main():
    ideal_start()
    create_checkerboard()
    check_for_the_stupid_single_case()
"""A Function where Karel creates a checkerboard, as long as it"""
"""is a rectngle with no obstacles"""


def create_checkerboard():
    while front_is_clear():
        ideal_start()
        across()
        back()
        if front_is_blocked():
            ideal_start() 
        else:
            up()
            across2()
            back()
        if front_is_blocked():
            ideal_start() 
            up()
            if front_is_blocked():
                across()
                back()
"""Creates a checkerboard in most cases."""

def check_for_the_stupid_single_case():
    turn_left()
    if left_is_blocked():
        if front_is_blocked():
            if right_is_blocked():
                turn_right()
                across()
                back()
"""The only part of this assignment I had a problem with with the 1x8 or 8x1 case"""
"""So I decided to just make a whole function to check if we are in the 1x8 case"""
def ideal_start():
    if facing_east():
        turn_left()
    if facing_south():
        turn_left()
        turn_left()
    if facing_west():
        turn_right()
    """A function to make sure Karel is facing the correct direction."""

def turn_right():
    turn_left()
    turn_left()
    turn_left()
"""Turns Karel right"""

def across():
    turn_right()
    put_beeper()
    while front_is_clear():
        move()
        if front_is_clear():
            move()
            put_beeper()
"""Turns karel and creates a line of beepers"""


def across2():
    turn_right()
    while front_is_clear():
        move()
        put_beeper()
        if front_is_clear():
            move()
"""Turns Karel and creates a line of beepers in opposing places to the across function"""

def back():
    turn_left()
    turn_left()
    while front_is_clear():
        move()
    turn_right()
"""Brings Karel back to its original position and turns Karel"""

def up():
    move()
"""Just moves Karel up a row"""