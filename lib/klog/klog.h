
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef K_LOG_GUARD
#define K_LOG_GUARD

//
// Begin file contents //
//

#include <inttypes.h>
#include <pgmspace.h>
    
#define K_LOG_MAX_LINES 100 //3000
#define K_LOG_MAX_SIZE 1048576 // Megabyte // In bytes
#define K_LOG_MAX_AUTHOR_LEN 32

typedef uint32_t position_t;
enum LOG_CATEGORY {
    LOG_NORMAL,
    LOG_DEBUG,
    LOG_WARN,
    LOG_ALERT,
    LOG_CRITICAL
};


// Log structure
struct log_entry
{
    size_t length;                    // Length of characters in log entry
    char *message;                        // Pointer to log entry
    LOG_CATEGORY category {LOG_NORMAL};
    
    union {
        char author_str[K_LOG_MAX_AUTHOR_LEN]; // Author
        char *author_ptr;
    } author;
    unsigned int author_len {0}; // If above zero then author_ptr is used instead

    __useconds_t entered; 
    uint8_t opts = 0x0; // Entry bitmask for options
        // Bit options
            // Bit 8 : 
            // Bit 7 : 
            // Bit 6 : 
            // Bit 5 : 
            // Bit 4 : 
            // Bit 3 : 
            // Bit 1 : 
            // Bit 1 :  author is author_ptr
};

position_t klog_add(position_t, position_t);
struct log_entry *add_new_entry(char *, size_t);
const char *get_line(position_t);

position_t klog_size();
struct log_entry *klog_entry(position_t);
position_t get_first_index();
position_t get_last_index();

// char **get_log();

//
// End file contents
//

#ifdef __cplusplus


struct log_entry *add_entry(char * , size_t = 0, char * = NULL, LOG_CATEGORY = LOG_NORMAL);

}
#endif

#endif