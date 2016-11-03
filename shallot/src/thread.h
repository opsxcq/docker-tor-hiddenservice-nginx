#ifndef THREAD_H
#define THREAD_H

void *worker(void *params);
void *monitor_proc(void *unused);

#endif
