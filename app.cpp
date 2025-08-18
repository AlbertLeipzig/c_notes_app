#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/*
- Controllers:

    - readSingleNote
    - reddAllNotes
    - createNote
    - updateNote
    - deleteNote
*/

/*
- Creating a Db (.json)
- Linking the db with the project
- Complete and refine the controllers
- Implement some User Interaction
*/

/* CONTROLLERS */

/* Read All Notes */

struct Note
{
    std::string id;
    std::string text;
};

std::vector<Note>
    notes{
        {"erty", "Hello There"}, {"sdfg", "How Are you doing?"}};

void readAllNotes(const std::vector<Note> &notes)
{
    for (const Note &note : notes)
    {
        std::cout << note.text << std::endl;
    }
}

/* const std::string& id */

void readSingleNote(const std::vector<Note> &notes, std::string id)
{

    auto it = std::find_if(std::begin(notes), std::end(notes), [&id](const Note &note)
                           { return note.id == id; });

    if (it == std::end(notes))
    {
        std::cout << "No Note found" << std::endl;
    }
    else
    {
        std::cout << it->text << std::endl;
        /* std::cout << (*it).text << std::endl; */
    }
}

main()
{
    readSingleNote(notes, "sdfg");
    readSingleNote(notes, "slkfgslh");
    return 0;
}