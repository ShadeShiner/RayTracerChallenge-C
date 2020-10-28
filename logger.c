#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct LogNode_
{
	char *name;
	FILE *fp;
	struct LogNode_ *next;
};


typedef struct LogList_
{
	LogNode *front;
	LogNode *back;
} LogList;


/* Global Variables */
LogMap *LOGGER = NULL;
char log_buffer[1024];

/* Functions */

/* LogNode */
static void log_node_init(LogNode *ln, char *name)
{
	ln->name = strdup(name);

	// Assuming the name passed in is a *.c file
	// *.c -> *.txt is an extra two characters, plus one for null-terminating character
	unsigned int name_len = strlen(name) + 3;
	char output_file_name[name_len];
	strcpy(output_file_name, name);
	output_file_name[name_len - 4] = 't';
	output_file_name[name_len - 3] = 'x';
	output_file_name[name_len - 2] = 't';
	output_file_name[name_len - 1] = '\0';

	ln->fp = fopen(output_file_name, "a");
	ln->next = NULL;
}

static int log_node_equal(LogNode *ln, const char *file_name)
{
	return strcmp(ln->name, file_name);
}

static void log_node_release(LogNode *ln)
{
	free(ln->name);
	fclose(ln->fp);
}

#define log_node_destroy(fn) log_node_release((fn)); free((fn))

/* LogList */
static void log_list_init(LogList *ll)
{
	ll->front = NULL;
	ll->back = NULL;
}

static void log_list_add(LogList *ll, char *name)
{
	LogNode *node = (LogNode *)malloc(sizeof(LogNode));
	log_node_init(node, name);
	if (ll->front == NULL)
	{
		ll->front = node;
		ll->back = node;
	}
	else
	{
		ll->back->next = node;
	}
}

static LogNode* log_list_get(LogList *ll, const char *file_name)
{
	for (LogNode *curr = ll->front; curr != NULL; curr = curr->next)
	{
		if (log_node_equal(curr, file_name) == 0)
			return curr;
	}
	return NULL;
}

static void log_list_release(LogList *ll)
{
	LogNode *prev = NULL;
	LogNode *curr = ll->front;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		log_node_destroy(prev);
	}
}

#define log_list_destroy(ll) log_list_release((ll)); free((ll));

/* LogMap */
void log_map_init(LogMap *lm)
{
	lm->size = 0;
	lm->lists = (LogList **)malloc(sizeof(LogList *) * 26);
	for (int i = 0; i < 26; ++i)
	{
		lm->lists[i] = (LogList *)malloc(sizeof(LogList));
		log_list_init(lm->lists[i]);
	}
}

void log_init(char *key)
{
	if (LOGGER == NULL)
	{
		LOGGER = (LogMap *)malloc(sizeof(LogMap));
		log_map_init(LOGGER);
	}
	if (log_get(key) == NULL)
		log_add(key);
}

void log_map_release(LogMap *lm)
{
	for (int i = 0; i < 26; ++i)
	{
		log_list_destroy(lm->lists[i]);
	}
}

void end_log()
{
	log_map_destroy(LOGGER);
	LOGGER = NULL;
}

#define log_map_destroy(lm) log_map_release((lm)); free((lm))

static int hash(const char *str)
{
	if (str[0] >= 'a' && str[0] <= 'z')
		return str[0] - 'a';
	else
		return str[0] - 'A';
};


void log_map_add(LogMap *lm, char *key)
{
	int index = hash(key);
	log_list_add(lm->lists[index], key);
}

void log_add(char *key)
{
	log_map_add(LOGGER, key);
}

LogNode* log_map_get(LogMap *lm, char *key)
{
	int index = hash(key);
	return log_list_get(lm->lists[index], key);
}

LogNode* log_get(char *key)
{
	return log_map_get(LOGGER, key);
}

void log_map_write(LogMap *lm, char *key, const char *message)
{
	LogNode *node = log_map_get(lm, key);
	fprintf(node->fp, message);
}

void log_write_(char *key)
{
	if (LOGGER == NULL || log_get(key) == NULL)
		log_init(key);
	log_map_write(LOGGER, key, log_buffer);
}

