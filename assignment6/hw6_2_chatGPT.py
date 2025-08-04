import threading
import argparse

# Shared counter and a lock (mutex)
counter = 0
counter_lock = threading.Lock()

def increment_counter(target, num_threads):
    global counter

    print(f"Incrementing counter from 0 to {target} using {num_threads} threads")
    
    def worker():
        nonlocal_per_thread = target // num_threads
        for _ in range(nonlocal_per_thread):
            with counter_lock:
                counter += 1

    threads = []
    for _ in range(num_threads):
        t = threading.Thread(target=worker)
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print(f"Final value is {counter}")

def decrement_counter(target, num_threads):
    global counter

    print(f"Decrementing counter from {target} to 0 using {num_threads} threads")
    
    def worker():
        nonlocal_per_thread = target // num_threads
        for _ in range(nonlocal_per_thread):
            with counter_lock:
                counter -= 1

    threads = []
    for _ in range(num_threads):
        t = threading.Thread(target=worker)
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print(f"Final value is {counter}")

def main():
    parser = argparse.ArgumentParser(description="Multithreaded counter using mutex.")
    parser.add_argument('--target', type=int, default=1_000_000_000,
                        help='Target counter value (default: 1000000000)')
    parser.add_argument('--threads', type=int, default=10,
                        help='Number of threads to use (default: 10)')
    args = parser.parse_args()

    increment_counter(args.target, args.threads)
    decrement_counter(args.target, args.threads)

if __name__ == "__main__":
    main()
