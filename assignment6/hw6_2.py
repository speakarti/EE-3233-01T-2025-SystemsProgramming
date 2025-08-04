#!/usr/bin/python3
import threading
import sys
import time

#global variables
counter=0 # global counter to track tasks completed
counter_lock = threading.Lock() # to ensure only one thread increments counter as mutex

#I can visualise this problem as if there are 10 workers and total tasks are 1000000000,
# So we need to divide tasks among workers. and when any tasks gets completed by anyworker he/she has to increment counter by 1 
# so that at any time there is a total number maintained to see how many tasks are completed as whole, in total. 
# To avoid race condition we need to maintain locking mechanism. 


# fucntion will break total tasks into total workers.
def increment_counter(totaltasks,totlworkers):
    print(f"Incrementing counter from 0 to {totaltasks} using '{totlworkers}' threads")
    tasks_per_worker = totaltasks // totlworkers ## modulo division to get intergers

    # worker class, where worker will work on tasks and will increment a shared, global counter by 1 whenevr a tasks finishes.
    def worker():
        global counter
        #nonlocal_per_thread = target // num_threads
        for _ in range(tasks_per_worker):
            with counter_lock:
                counter += 1


    workers=[] # list of workers/threads
    for _ in range(totlworkers): #start a new thread for each worker, and get worker in list of workers
        t = threading.Thread(target=worker)
        workers.append(t)
        t.start()

    for t in workers:
        t.join() # wait for all workers to finish tasks.

    print(f"Final value is {counter}")




# fucntion will break total tasks into total workers.
def decrement_counter(totaltasks,totlworkers):
    print(f"decrementing counter from {totaltasks} to 0 using '{totlworkers}' threads")
    tasks_per_worker = totaltasks // totlworkers ## modulo division to get intergers

    # worker class, where worker will work on tasks and will increment a shared, global counter by 1 whenevr a tasks finishes.
    def worker():
        global counter
        #nonlocal_per_thread = target // num_threads
        for _ in range(tasks_per_worker):
            with counter_lock:
                counter -= 1


    workers=[] # list of workers/threads
    for _ in range(totlworkers): #start a new thread for each worker, and get worker in list of workers
        t = threading.Thread(target=worker)
        workers.append(t)
        t.start()

    for t in workers:
        t.join() # wait for all workers to finish tasks.

    print(f"Final value is {counter}")



def main():
    # will take tasks and workers as input
    argc = len(sys.argv)
    args = sys.argv
    if argc == 3:
        totaltasks=int(args[1])
        totlworkers=int(args[2] )  
    else:
        print(f"Using default values for contents and filename as per instructions")
        totaltasks=1000000000
        totlworkers=10
    
    print(f"totaltasks '{totaltasks}' totlworkers:'{totlworkers}'")

    start_time = time.time()
    increment_counter(totaltasks,totlworkers)
    end_time = time.time()
    print(f"Execution time: {end_time - start_time:.4f} seconds")

    start_time = time.time()
    decrement_counter(totaltasks,totlworkers)
    end_time = time.time()
    print(f"Execution time: {end_time - start_time:.4f} seconds")



if __name__ =='__main__':
    main()
