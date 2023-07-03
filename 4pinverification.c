#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define PIN_LENGTH 4
#define CORRECT_PIN "5309"

int main()
{
    initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled
    noecho(); // Don't echo input characters

    int ch;
    int pinIndex = 0;
    char pin[PIN_LENGTH + 1];

    clear(); // Clear the screen

    while (1)
    {
        mvprintw(0, 0, "Enter your 4-digit PIN: ");
        mvprintw(1, 0, "PIN: %-*s", PIN_LENGTH, pin);

        ch = getch(); // Get user input

        if (ch >= '0' && ch <= '9')
        {
            if (pinIndex < PIN_LENGTH)
            {
                pin[pinIndex++] = ch;
                mvaddch(1, pinIndex + 5, 'X'); // Display X for entered digit
                refresh();
            }
        }
        else if (ch == KEY_BACKSPACE || ch == 127)
        {
            if (pinIndex > 0)
            {
                pin[--pinIndex] = '\0';
                mvaddch(1, pinIndex + 5, ' '); // Clear X for deleted digit
                refresh();
            }
        }
        else if (ch == '\n')
        {
            if (pinIndex == PIN_LENGTH)
            {
                pin[PIN_LENGTH] = '\0'; // Null-terminate the PIN string

                if (strcmp(pin, CORRECT_PIN) == 0)
                {
                    clear();
                    mvprintw(0, 0, "PIN is correct! Access granted.\n");
                    refresh();
                    getch(); // Wait for user to press any key
                    break;
                }
                else
                {
                    clear();
                    mvprintw(0, 0, "Incorrect PIN! Please try again.\n");
                    refresh();
                    getch(); // Wait for user to press any key
                    clear();
                    pinIndex = 0; // Reset PIN entry
                }
            }
            else
            {
                clear();
                mvprintw(0, 0, "PIN must be 4 digits long! Please try again.\n");
                refresh();
                getch(); // Wait for user to press any key
                clear();
                pinIndex = 0; // Reset PIN entry
            }
        }
    }

    endwin(); // End ncurses

    return 0;
}

