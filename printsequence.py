"""ID"""


def write_order(input_sequence, depth = 0):
    """Print for script."""
    print(input_sequence)
    if all(x == 0 for x in input_sequence):
        print(f"Final Depth: {depth}")
        return
    else:
        next_sequnce = [abs(input_sequence[1] - input_sequence[0]),
                        abs(input_sequence[2] - input_sequence[1]),
                        abs(input_sequence[3] - input_sequence[2]),
                        abs(input_sequence[3] - input_sequence[0])]
        write_order(next_sequnce, depth + 1)




def main():
    """Script."""
    array = []

    # Loop to read in 4 integer values
    for _ in range(4):
        while True:
            try:
                # Prompt the user for an integer input
                user_input = input("Enter an integer: ")
                # Convert the input to an integer
                integer_value = int(user_input)
                # Add the integer to the array
                array.append(integer_value)
                break
            except ValueError:
                print("Invalid input. Please enter an integer.")

    # Print the array
    write_order(array)


main()