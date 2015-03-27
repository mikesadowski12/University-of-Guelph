/*************************main.c****************************
Student Name: Michael Sadowski                      Student Number:  0864810
Date: Feb 10th, 2014                       Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "curl_util.h"


/*this is the only function you need to use from this set of utilities.  
the other functions are helpping functions */

char* makeCurlCall(char* url, char* parameters) 
{
	CURL* curlData;
	BufferData buffer;
	CURLcode response;

	/* Initialize the buffer */
	buffer.string = malloc(sizeof(char));
	buffer.string[0] = '\0';
	buffer.length = 0;
	curlData = initializeCurlCall(url, parameters, &buffer);

	/* On first call initialize the CurlData buffer and make the POST */
	response = curl_easy_perform(curlData);
	if (response != CURLE_OK) 
	{
		return NULL;
	}
	/* Clean up curl stuff */
	curl_easy_cleanup(curlData);
	return buffer.string;
}

/*everything from here down in this file are helper functions that you do not need to call */

size_t processPost(void* stream, size_t size, size_t numberOfMembers, BufferData* buffer) 
{
	/* Reallocate the CurlData buffer to fit the extra data */
	size_t newLength = buffer->length + size*numberOfMembers;
	buffer->string = realloc(buffer->string, newLength+1);
	if (buffer->string == NULL) 
	{
		fprintf(stderr, "Failed to get data\n");
		exit(EXIT_FAILURE);
	}

	/* Copy the data to the CurlData buffer and update its length */
	memcpy(buffer->string + buffer->length, stream, size*numberOfMembers);
	buffer->string[newLength] = '\0';
	buffer->length = newLength;
        return size*numberOfMembers;
}


CURL* initializeCurlCall(char* url, char* parameters, BufferData* buffer) 
{
	CURL* curlData;

	/* Initialize the curl options */
	curlData = curl_easy_init();
    curl_easy_setopt(curlData, CURLOPT_URL, url);
    curl_easy_setopt(curlData, CURLOPT_POSTFIELDS, parameters);
    curl_easy_setopt(curlData, CURLOPT_WRITEFUNCTION, processPost);
    curl_easy_setopt(curlData, CURLOPT_WRITEDATA, buffer);

	return curlData;
}



