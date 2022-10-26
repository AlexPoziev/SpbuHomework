#include "listTest.h"

bool fullTest(void) {

}

bool testCreateList(void) {
    List* list = createList();
    bool result = list != NULL;
    deleteList(&list);
    return result;
}

bool testCreatePosition(void) {
    Position* position = createPosition();
    bool result = position != NULL;
    deletePosition(&position);

    return result;
}

bool testDeletePosition(void)
{
    List* list = createList();
    in
    Position* position = getFirst(list);
    bool result = position != NULL;
    deletePosition(&position);
    deleteList(&list);

    return result && position == NULL;
}