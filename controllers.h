#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

struct Note
{
    std::string id;
    std::string text;
};

inline void to_json(json &j, const Note &n)
{
    j = json{{"id", n.id}, {"text", n.text}};
}

inline void from_json(const json &j, Note &n)
{
    j.at("id").get_to(n.id);
    j.at("text").get_to(n.text);
}

/* CONTROLLERS */

/* Read All Notes */

void readAllNotes()
{
    std::ifstream file("notesDb.json");

    if (!file.is_open())
    {
        std::cerr << "Failed to open notesDb.json\n";
        return;
    }

    json j;
    file >> j;

    std::vector<Note> notes = j.get<std::vector<Note>>();

    for (auto &note : notes)
    {
        std::cout << note.id << " : " << note.text << std::endl;
    }
}

/* readSingleNote */

void readSingleNote(const std::string &id)
{
    std::ifstream file("notesDb.json");

    if (!file.is_open())
    {
        std::cerr << "Failed to open notesDb.json\n";
        return;
    }

    json j;
    file >> j;

    std::vector<Note> notes = j.get<std::vector<Note>>();

    auto it = std::find_if(notes.begin(), notes.end(), [&](const Note &note)
                           { return note.id == id; });

    if (it == notes.end())
    {
        std::cerr << "No Note found\n";
    }
    else
    {
        std::cout << it->id << " : " << it->text << std::endl;
        /* std::cout << (*it).text << std::endl; */
    }
}

/* createNote */

void createNote(const Note &newNote, const std::string &filename)
{
    std::ifstream inFile(filename);
    json j;

    if (inFile.is_open())
    {
        inFile >> j; // read existing JSON
    }
    inFile.close();

    // Make sure file contained an array
    if (!j.is_array())
    {
        j = json::array();
    }

    // Push the new note
    j.push_back({{"id", newNote.id}, {"text", newNote.text}});

    // Save back
    std::ofstream outFile(filename);
    outFile << j.dump(2); // pretty print
    outFile.close();
}

/* updateNote */

void updateNote(const std::string &id, const std::string newText, const std::string &fileName)
{
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Cannot open file \n";
        return;
    }

    json j;
    inFile >> j;
    inFile.close();

    auto it = std::find_if(std::begin(j), std::end(j), [&](const json &note)
                           { return note["id"] == id; });

    if (it != j.end())
    {
        (*it)["text"] = newText;
    }
    else
    {
        std::cerr << "Note not found\n ";
        return;
    }

    std::ofstream outFile(fileName);
    outFile << j.dump(2);
    outFile.close();
}

/* why  & in updateNote  const std::string& fileName and not in deleteNote*/

/* deleteNote */

void deleteNote(const std::string id, const std::string fileName)
{
    std::ifstream inFile(fileName);

    if (!inFile.is_open())
    {
        std::cerr << "Cannot open file \n";
        return;
    }

    json j;
    inFile >> j;
    inFile.close();

    auto it = std::remove_if(std::begin(j), std::end(j), [&](const json &note)
                             { return note["id"] == id; });

    j.erase(it, std::end(j));

    std::ofstream outFile(fileName);
    outFile << j.dump(2);
    outFile.close();
}