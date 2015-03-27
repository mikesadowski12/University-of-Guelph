/*Justin Carvalho*/

/*config*/
#define OUTPUTFILE "./listTest.csv"


/*program*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "linkedList.h"

#define STRUCTFAILURE 1
#define LISTFAILURE 2
#define TESTFAILURE 3
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"

MusicRec* createRecord_basicTest();
void printRecord_basicTest(MusicRec* pRecord);
MusicRec* addToFront_basicTest(MusicRec* head);
MusicRec* addToBack_basicTest(MusicRec* head, int expectedLength);
bool length_test(MusicRec* head, int expectedLength);
void getLastItem_fullTest(MusicRec* head);
MusicRec* removeFromFront_fullTest(MusicRec* head);
MusicRec* removeFromBack_fullTest(MusicRec* head);
void isEmpty_basicTest(MusicRec* head);
void removes_emptyTest();

void segfault_sigaction(int signal, siginfo_t *si, void *arg);
void normalizeFile();

FILE* output = NULL;
char* username = NULL;
int printedCols = 0;

int main(int argc, char* argv[]) {
	MusicRec* head = NULL;
	struct sigaction sa; 

	if (argc != 2) {
		fprintf(stderr, "Incorrect number of cmdline arguments\n");
		fprintf(stderr, "Expected 1, provided %d\n", argc - 1);
		fprintf(stderr, "Usage: ./runnable <username>\n");
		exit(TESTFAILURE);	
	}
	username = strdup(argv[1]);
	if (!username) {
		fprintf(stderr, "Couldn't malloc memory for username %s\n", argv[1]);
		exit(TESTFAILURE);
	}

	/*segfault catcher*/
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	output = fopen(OUTPUTFILE, "a");
	if (!output) {
		fprintf(stderr, "Couldn't open %s for appending\n", OUTPUTFILE);
		exit(TESTFAILURE);
	}
	fprintf(output, "%s,", username);
	
	head = createRecord_basicTest();
	if (!head) {
		exit(STRUCTFAILURE);
	}

	printRecord_basicTest(head);

	head = addToFront_basicTest(head);
	if (!head) {
		exit(STRUCTFAILURE);
	}
	if(length_test(head, 2) == false) {
		exit(LISTFAILURE);
	}
	head = addToBack_basicTest(head, 3);
	if (!head) {
		exit(LISTFAILURE);
	}
	getLastItem_fullTest(head);
	head = removeFromFront_fullTest(head);
	if (!head) {
		exit(LISTFAILURE);
	}
	head = removeFromBack_fullTest(head);
	if (!head) {
		exit(LISTFAILURE);
	}
	isEmpty_basicTest(head);
	removes_emptyTest();

	fprintf(output, "\n");

	fclose(output);
	free(username);
	return 0;
}

MusicRec* createRecord_basicTest() {
	char* title;
	char* artist;
	MusicRec* testRecord = NULL;
	bool pass = true;

	title = malloc(11 * sizeof(char)); /*'Stir It Up\0'*/
	if (!title) {
		fprintf(stderr, "%s: !TESTERROR: malloc failed\n", username);
		return NULL;
	}
	artist = malloc(11 * sizeof(char)); /*Bob Marley\0'*/
	if (!artist) {
		fprintf(stderr, "%s: !TESTERROR: malloc failed\n", username);
		free(title);
		return NULL;
	}

	strcpy(title, "Stir It Up");
	strcpy(artist, "Bob Marley");

	testRecord = createRecord(title, artist, 2.10, 319, 'r');
	if (!testRecord) {
		fprintf(output, "0,");
		printedCols++;
		return NULL; 
	}

	if ( strcmp(title, testRecord->title) != 0 )
		pass = false;
	if ( strcmp(artist, testRecord->artist) != 0 )
		pass = false;
	if ( ((double)2.10) != testRecord->sizeInKB )
		pass = false;
	if ( 319 != testRecord->lengthInSeconds )
		pass = false;
	if ( 'r' != testRecord->type )
		pass = false;

	free(title);
	free(artist);
	title = artist = NULL;

	if (testRecord->title == NULL && testRecord->artist == NULL)
		pass = false;

	testRecord->title[6] = 'a';
	testRecord->artist[9] = 'a';
	if (testRecord->title[6] == 'a' && testRecord->artist[9] == 'a') {
		/*good*/
	} else {
		pass = false;
	}

	testRecord->title[6] = 't';
	testRecord->artist[9] = 'y';

	/*passed*/
	if (pass) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
	}
	return testRecord;
}

void printRecord_basicTest(MusicRec* pRecord) {
	char* returnedString = NULL;
	char* testString = NULL; 

	returnedString = printRecord(pRecord);
	if (!returnedString) {
		fprintf(output, "0,");
		printedCols++;
		return; 
	}

	testString = malloc(34 * sizeof(char));
	if (!testString) {
		fprintf(stderr, "%s: !TESTERROR: malloc failed\n", username);
		return;
	}
	strcpy(testString, "Stir It Up (Bob Marley):319[2.10]");

	if (strcmp(returnedString, testString) == 0) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
	}

	free(testString);
	testString = NULL;
	free(returnedString);
	returnedString = NULL;
}

bool length_test(MusicRec* head, int expectedLength) {
	MusicRec* i;
	int length = 0;
	if (head == NULL) {
		fprintf(output, "0,");
		printedCols++;
		return -1;
	}
	for (i=head; i!=NULL; i=i->next) {
		length++;
	}
	if (length == expectedLength) {
		fprintf(output, "1,");
		printedCols++;
		return true;
	} else {
		fprintf(output, "0,");
		printedCols++;
		return false;
	}
}

MusicRec* addToFront_basicTest(MusicRec *record) {
	MusicRec* head = NULL;
	MusicRec* headRecord = NULL;

	headRecord = createRecord("TNT", "ACDC", 3.10, 419, 's');
	if (!headRecord) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	head = addToFront(record, headRecord);
	if (head == NULL) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}
	if (head->title == NULL || head->artist == NULL) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	fprintf(output, "1,");
	printedCols++;
	return head;
}


MusicRec* addToBack_basicTest(MusicRec* head, int expectedLength) {
	int length=0;
	MusicRec* i;
	MusicRec* back;
	MusicRec* newHead;

	back = createRecord("Pokemon Theme", "Jason Paige", 1.1, 230, 'p');
	if (!back) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	newHead = addToBack(head, back);

	if (newHead == head) {
		/*good*/
	} else {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	for (i=head; i->next!=NULL; i=i->next) {
		length++;
	}
	length++;
	if (length != expectedLength) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	if (back == i) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	return newHead;
}

void getLastItem_fullTest(MusicRec* head) {
	MusicRec* end;
	end = getLastItem(head);
	if (!end) {
		fprintf(output, "0,");
		printedCols++;
		return;
	}
	if (strcmp(end->title, "Pokemon Theme") == 0) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
	}
}

MusicRec* removeFromFront_fullTest(MusicRec* head) {
	MusicRec* newhead;
	newhead = removeFromFront(head);
	if (!newhead) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	if (strcmp(newhead->title, "Stir It Up") == 0) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}
	free(head);
	return newhead;
}

MusicRec* removeFromBack_fullTest(MusicRec* head) {
	MusicRec* deleted;
	deleted = removeFromBack(head);
	if (!deleted) {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}
	if (strcmp(deleted->title, "Pokemon Theme") == 0) {
		/*good*/
	} else {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	if (head->next == NULL) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
		return NULL;
	}

	return head;
}

void isEmpty_basicTest(MusicRec* head) {
	bool pass = true;
	if (isEmpty(head) == false) {
		/*good*/
	}  else {
		pass = false;
	}
	free(head);
	head = NULL;
	if (isEmpty(head) == true) {
		/*good*/
	}  else {
		pass = false;
	}

	if (pass == true) {
		fprintf(output, "1,");
		printedCols++;
	} else {
		fprintf(output, "0,");
		printedCols++;
	}
}

void removes_emptyTest() {
	bool pass = true;
	if (removeFromFront(NULL) == NULL) {
		/*good*/
	}  else {
		pass = false;
	}

	if (removeFromBack(NULL) == NULL) {
		/*good*/
	}  else {
		pass = false;
	}

	if (pass == true) {
		fprintf(output, "1");
		printedCols++;
	} else {
		fprintf(output, "0");
		printedCols++;
	}
}

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	fprintf(stderr, "%s: Caught segfault at address %p\n", username, si->si_addr);
	normalizeFile();
	exit(0);
}

void normalizeFile() {
	while (printedCols < 9) {
		fprintf(output, "0,");
		printedCols++;
	}
	if (printedCols < 10) {
		fprintf(output, "0\n");
	}
}

/*Justin Carvalho*/
