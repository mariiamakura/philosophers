# philosophers
The basics of threading a process

## materials to read/watch
[Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLyX5J0h01rlHpZEBfyxhiSZXDFx4y6Cna)

## creating threads 

```
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*fun)(void *), void *arg);
```
The pthread_create() function is used to create a new thread, with attributes specified by attr, within a process.  If attr is NULL, the default attributes are used.  If the attributes specified by attr are modified later, the thread's attributes are not affected.  Upon successful completion pthread_create() will store the ID of the created thread in the location specified by thread.

RETURN VALUES
If successful, the pthread_create() function will return zero.  Otherwise an error number will be returned to indicate the error.
