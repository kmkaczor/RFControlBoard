#include <string.h>
#include "klog.h"
#include <Arduino.h>

// Helpers

static struct log_entry * _insert(position_t, char *, size_t, char *, LOG_CATEGORY);
static inline position_t _next(position_t);
static inline position_t _prev(position_t);
static inline position_t _add(position_t, position_t);


struct _log
{
    position_t position_start{0};
    position_t position_end{0};
    position_t size{0};
    log_entry log[K_LOG_MAX_LINES];

} k_log = {0, 0, 0, 0};

struct log_entry * _insert(position_t index, char * message, size_t len, char *author,  LOG_CATEGORY category)
{
    if (author == NULL)
        k_log.log[index].author.author_ptr = (char *)"Unknown\0";
    else
        strncpy(k_log.log[index].author.author_str, author, K_LOG_MAX_AUTHOR_LEN);
    
    k_log.log[index].entered = millis();
    k_log.log[index].length = len;
    extmem_free(k_log.log[index].message);
    k_log.log[index].message = message;
    k_log.position_end = _next(index);

    return &k_log.log[index];
}


struct log_entry *add_new_entry(char *message, size_t len)
{
    position_t current_index = k_log.position_end;
    LOG_CATEGORY category = LOG_NORMAL;

    if (current_index == k_log.position_start - 1)
        k_log.position_start = _next(k_log.position_start);
    else
        k_log.size++;

    return _insert(current_index, message, len, "System", category);
}

/*
char *get_log_debug()
{
    char *debug = "position_start: %d\nposition_end: %d\n";
    char ret[85];
    snprintf(ret, 85, debug, get_first_index(), k_log.size);
    return ret;
}
*/
position_t klog_size()
{
    return k_log.size;
}

position_t get_first_index()
{
    return k_log.position_start;
}
position_t get_last_index()
{
    return k_log.position_end;
}

struct log_entry *klog_entry(position_t line)
{
    position_t entry = _add(k_log.position_start, line);
    // Return NULL if the line exceeds the size. Perhaps modulo instead?
    if (entry > k_log.size)
        return NULL;

    return (struct log_entry *)&k_log.log[entry];
}

const char *get_line(position_t line = 0)
{
    position_t abs_line = _add(k_log.position_start, line);
    // Return NULL if the line exceeds the size. Perhaps modulo instead?
    if (abs_line > k_log.size)
        return NULL;

    struct log_entry entry = k_log.log[abs_line];
    return entry.message;
    return "FAIL";
}

position_t klog_add(position_t n, position_t d)
{
    return (n + d) % K_LOG_MAX_LINES;
}

static inline position_t _next(position_t n)
{
    return (n + 1) % K_LOG_MAX_LINES;
}

static inline position_t _add(position_t n, position_t d)
{
    return (n + d) % K_LOG_MAX_LINES;
}

static inline position_t _prev(position_t n)
{
    return (n - 1) % K_LOG_MAX_LINES;
}


// C++ extensions

#ifdef __cplusplus

struct log_entry *add_entry(char *message, size_t len, char * author, LOG_CATEGORY category)
{
    position_t current_index = k_log.position_end;

    if (current_index == k_log.position_start - 1)
        k_log.position_start = _next(k_log.position_start);
    else
        k_log.size++;

    return _insert(current_index, message, len, author, category);

}
#endif