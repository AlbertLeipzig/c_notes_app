#include "controllers.h"

/*
- Refine the controllers
- Implement some User Interaction with a GUI (qt)
*/





main()
{
    /* readSingleNote("sdfg");
    readSingleNote("dfghdfjh");
    readAllNotes(); */
    Note n{"sdrjkgbskdfgb", "An even newer Note"};
    createNote(n, "notesDb.json");
    /* deleteNote("sfglkjzdfgjsbdfg", "notesDb.json"); */
    /* updateNote("fghlksdjfñglksdjfg", "Updated Text", "notesDb.json"); */
    readAllNotes();
    return 0;
}