#!/usr/bin/python3
import hashlib
import sys
import os

# function to get command line arguments as file name and hash algo
def main():
    argc = len(sys.argv)
    HashAlgo='sha256'
    print(hashlib.algorithms_available)
    hash_algo_set = hashlib.algorithms_available
    if argc >= 2:
        
        filename=sys.argv[1]
        if not os.path.exists(filename):
            print(f"usage: python3 hash.py example.txt <optional:algorithms>")
            exit()
            
        #print(f"arguments count is :{argc}")
        if argc >= 3:
            if sys.argv[2] is not None:
                if sys.argv[2] in hash_algo_set:
                    HashAlgo=sys.argv[2] 
                    print(f"Using command line provided hash algo: {HashAlgo}")
                else:                    
                    print(f"Hash argument provided is not from valid list of hash functions, so using the dafault hash algo: {HashAlgo}")                    
                    print(f"Complete list of valid valid hash functions: {hash_algo_set} \n")
        else:
            print(f"Hash argument not provided, using the dafault sha256 hash. hash algo: {HashAlgo}")
        
        # calling the hashing algo to get hash values
        hash_function_algo = hashlib.new(HashAlgo)
        with open(filename, "rb") as f:
            while chunk := f.read(8192):
                hash_function_algo.update(chunk)
        
        print(f"{HashAlgo} hash of {filename}: {hash_function_algo.hexdigest()}")

    else:
        print(f"usage: python3 hash.py example.txt <optional:algorithms>")


if __name__ == '__main__':
    main()