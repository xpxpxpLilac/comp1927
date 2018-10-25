// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

void testInsertBefore(DLList myList);
void testInsertAfter(DLList myList);
void testDelete(DLList myList);


int main(int argc, char *argv[])
{
    DLList myList;
    myList = getDLList(stdin);
    testInsertBefore(myList);
    testInsertAfter(myList);
    testDelete(myList);

    
    return 0;
}


void testInsertBefore(DLList myList){
    printf("\n");
    printf("===========\n");
    printf("==Performing DLListBefore==\n");
    printf("\n");

    // list is empty
    if(DLListLength(myList) == 0) {
        printf("== State before operation ==\n");
        printf("Empty list\n");
        printf("==Inserting *****==\n");
        char *n = "*****";
        DLListBefore(myList,n);
        char *curr = DLListCurrent(myList);
        int num = DLListLength(myList);
        printf("== State after operation ==");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("=============\n");
	
        assert(validDLList(myList));
    } else if(DLListLength(myList) == 1) {
        printf("==Inserting ***** before first node==\n");
        printf("== State before operation ==\n");
        char* curr = DLListCurrent(myList);
        int num =  DLListLength(myList);
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        char *n = "*****";
        DLListBefore(myList,n);
        curr = DLListCurrent(myList);
        num = DLListLength(myList);
        printf("== State after operation ==\n");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");

        assert(validDLList(myList));
    } else {
        printf("==Inserting ***** before first node==\n");
        printf("\n");


        printf("== State before operation ==\n");
        char* curr = DLListCurrent(myList);
        int num =  DLListLength(myList);
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("\n");

        char *n = "*****";
        DLListBefore(myList,n);
        curr = DLListCurrent(myList);
        num = DLListLength(myList);
        printf("\n");
        printf("== State after operation ==\n");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is %s\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");
        printf("\n");

        assert(validDLList(myList));
     

        // curr is not first, insert before
        if(DLListLength(myList) >= 3){
        DLListMoveTo(myList,3);

        printf("==Inserting &&&&& before third node==\n");
        printf("== State before operation ==\n");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");

        char *m = "&&&&&";
        DLListBefore(myList,m);
        curr = DLListCurrent(myList);
        num = DLListLength(myList);
        //putDLList(stdout,myList);
        printf("== State after operation ==");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");

        assert(validDLList(myList));
    	}

    }

}




void testInsertAfter(DLList myList){
        printf("=============\n");
        printf("==Performing DLListAfter==\n");
    // list is empty
    if(DLListLength(myList) == 0) {
        printf("== State before operation ==\n");
        printf("Empty list\n");
        printf("==Inserting ***** ==\n");
        char *n = "*****";
        DLListAfter(myList,n);
        char *curr = DLListCurrent(myList);
        int num = DLListLength(myList);
        //putDLList(stdout,myList);
        printf("== State after operation ==\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");
        assert(validDLList(myList));

    } else if(DLListLength(myList) == 1) {
        printf("==Inserting ***** after first node==\n");
        printf("== State before operation ==\n");
        char* curr = DLListCurrent(myList);
        int num =  DLListLength(myList);
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        char *n = "*****";
        DLListAfter(myList,n);
        curr = DLListCurrent(myList);
        num = DLListLength(myList);
        printf("== State after operation ==\n");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");

        assert(validDLList(myList));

    } else {
        printf("==Inserting ***** after first node==\n");
        printf("== State before operation ==\n");
        char *curr = DLListCurrent(myList);
        int num =  DLListLength(myList);
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("\n");

        char *n = "*****";
        DLListAfter(myList,n);
        curr = DLListCurrent(myList);
        num = DLListLength(myList);
        printf("\n");
        printf("== State after operation ==\n");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is %s\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("==============\n");
        printf("\n");

        assert(validDLList(myList));

        // curr is not first, insert before
        if(DLListLength(myList) >= 3){
        DLListMoveTo(myList,3);
        printf("===============\n");
        printf("==Inserting &&&&& after third node==\n");
        printf("== State before operation ==\n");
        putDLList(stdout,myList);

        char *m = "&&&&&";
        DLListAfter(myList,m);
        curr = DLListCurrent(myList);
        num = DLListLength(myList);
        printf("== State after operation ==\n");
        putDLList(stdout,myList);
        printf("\n");
        printf("Value of curr is '%s'\n",curr);
        printf("Value of nitems is %d\n",num);
        printf("===============\n");

        assert(validDLList(myList));

        printf("==============\n");
        }

    }

}


void testDelete(DLList myList){

    printf("==Performing DLListDelete==\n");
    printf("\n");

    printf("== State before operation ==\n");
    char *curr = DLListCurrent(myList);
    int num =  DLListLength(myList);
    putDLList(stdout,myList);
    printf("==============\n");
    printf("Value of curr is '%s'\n",curr);
    printf("Value of nitems is %d\n",num);
    printf("\n");

    DLListDelete(myList);
    curr = DLListCurrent(myList);
    num = DLListLength(myList);
    printf("\n");
    printf("== State after operation ==\n");
    putDLList(stdout,myList);
    printf("==============\n");
    printf("Value of curr is %s\n",curr);
    printf("Value of nitems is %d\n",num);
    printf("==============\n");

    printf("\n");
    
    assert(validDLList(myList));

}
