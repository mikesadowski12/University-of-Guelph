#include <curl/curl.h>

/*  Description:
 *	Makes a POST to the website specified by url with the data specified in parameters.
 *  Parameters:
 *	url: The url to POST to.
 *	parameters: The data to pass along with the POST
 *  Return:
 *	Returns a pointer to the contents of the POST request. This pointer should be freed
 * 	when done with the data. If there was an error getting the data the pointer will be
 *	NULL.
 */
char* makeCurlCall(char* url, char* parameters);



/*this is a struct,  which we will learn about in a couple weeks
you don't need to do anything with it right now */

typedef struct BufferData {
	char* string;
	size_t length;
} BufferData;



/* these functions are helper functions that you will not need to call */

size_t processPost(void* stream, size_t size, size_t numberOfMembers, BufferData* buffer);
CURL* initializeCurlCall(char* url, char* parameters, BufferData* buffer);
