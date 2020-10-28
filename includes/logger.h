#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>


/* Extern Variables */
extern char log_buffer[1024];


/* Forward Declarations */
typedef struct LogNode_ LogNode;
typedef struct LogList_ LogList;


/* Structures */
typedef struct LogMap_
{
	unsigned int size;
	LogList **lists;
} LogMap;


/* Functions */
void log_map_init(LogMap *lm);

void log_init(char *key);

void log_map_release(LogMap *lm); 

#define log_map_destroy(lm) log_map_release((lm)); free((lm))

void end_log();

void log_map_add(LogMap *lm, char *key);

void log_add(char *key);

LogNode* log_map_get(LogMap *lm, char *key);

LogNode* log_get(char *key);

void log_map_write(LogMap *lm, char *key, const char *message);

void log_write_(char *key);

#define log_write(message, ...) sprintf(log_buffer, (message), ##__VA_ARGS__);\
	log_write_(__FILE__)

#endif
