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
```
void *test(void *data)
{
  printf("Hello");
  return(0);
}

int main()
{
  pthread_t id;
  pthread_create(&id, NULL, test, NULL); //the 4th param is an argument to the fun(3rd param)
  //join or detach
  return(0);
}
```

**remember that main() is a thread itself that can finish before your second thread is executed (in case of the code above). To make thread wait until the specific one is finished, use following ->

## thread_join / thread_detach

```
int pthread_join(pthread_t thread, void **retval);
```
The pthread_join() function waits for the thread specified by thread to terminate.  If that thread has already terminated, then  pthread_join() returns immediately.  The thread specified by thread must be joinable. If  retval  is  not NULL, then pthread_join() copies the exit status of the target thread (i.e., the value that the target thread  supplied  to pthread_exit(3)) into the location pointed to by retval. 
If  multiple  threads  simultaneously try to join with the same thread, the results are undefined.  If the  thread  calling  pthread_join()  is canceled,  then  the  target thread will remain joinable (i.e., it will not be detached).

RETURN VALUE
On success, pthread_join() returns 0; on error,  it  returns  an  error number.

```
void *test(void *data)
{
  printf("Hello");
  return(0);
}

int main()
{
  pthread_t id;
  pthread_create(&id, NULL, test, NULL); //the 4th param is an argument to the fun(3rd param)
  pthread_join(&id)
  return(0);
}
```

```
int pthread_detach(pthread_t thread);
```
The  pthread_detach() function marks the thread identified by thread as detached.  When a detached thread terminates, its resources  are  auto‐matically  released  back  to  the  system without the need for another thread to join with the terminated thread.


RETURN VALUE
On  success,  pthread_detach() returns 0; on error, it returns an error number.

!! pthread_join() blocks the calling thread until the specified thread completes and allows retrieving the exit status of the joined thread.
!! pthread_detach() marks a thread as detached, allowing it to clean up its resources independently upon completion, without the need for another thread to join it.
