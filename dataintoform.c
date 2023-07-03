#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_ADDRESS_LENGTH 30

int main()
{
    initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled
    noecho(); // Don't echo input characters

    char first_name[MAX_NAME_LENGTH + 1] = "";
    char last_name[MAX_NAME_LENGTH + 1] = "";
    char address[MAX_ADDRESS_LENGTH + 1] = "";

    int ch;
    int field_index = 0; // 0: First Name, 1: Last Name, 2: Address
    int cursor_x, cursor_y;

    clear(); // Clear the screen

    while (1)
    {
        mvprintw(0, 0, "First Name: %-*s", MAX_NAME_LENGTH, first_name);
        mvprintw(1, 0, "Last Name: %-*s", MAX_NAME_LENGTH, last_name);
        mvprintw(2, 0, "Address: %-*s", MAX_ADDRESS_LENGTH, address);

        // Move the cursor to the current field
        if (field_index == 0)
            move(0, strlen("First Name: "));
        else if (field_index == 1)
            move(1, strlen("Last Name: "));
        else if (field_index == 2)
            move(2, strlen("Address: "));

        refresh();

        ch = getch(); // Get user input
        getyx(stdscr, cursor_y, cursor_x); // Get current cursor position

        if (ch == '\n')
        {
            if (field_index < 2)
                field_index++; // Move to the next field
            else
                break; // Exit when the Address field is filled
        }
        else if (ch == KEY_BACKSPACE || ch == 127)
        {
            // Delete the last character in the current field
            if (field_index == 0 && cursor_x > strlen("First Name: "))
                first_name[--cursor_x - strlen("First Name: ")] = '\0';
            else if (field_index == 1 && cursor_x > strlen("Last Name: "))
                last_name[--cursor_x - strlen("Last Name: ")] = '\0';
            else if (field_index == 2 && cursor_x > strlen("Address: "))
                address[--cursor_x - strlen("Address: ")] = '\0';
        }
        else if (cursor_x < COLS - 1) // Limit input to field width
        {
            // Append the entered character to the current field
            if (field_index == 0 && strlen(first_name) < MAX_NAME_LENGTH)
                first_name[cursor_x - strlen("First Name: ")] = ch;
            else if (field_index == 1 && strlen(last_name) < MAX_NAME_LENGTH)
                last_name[cursor_x - strlen("Last Name: ")] = ch;
            else if (field_index == 2 && strlen(address) < MAX_ADDRESS_LENGTH)
                address[cursor_x - strlen("Address: ")] = ch;

            cursor_x++;
        }
    }

    clear();
    mvprintw(0, 0, "First Name: %s", first_name);
    mvprintw(1, 0, "Last Name: %s", last_name);
    mvprintw(2, 0, "Address:%s",address);

