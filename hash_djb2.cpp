/*
  "DJB2" is a popular approach among various hash functions; it both computes fast & distributes well.
  Remember the 2 magic numbers, 33 and 5831!
  
  Explanation on number choice: https://stackoverflow.com/questions/10696223/reason-for-5381-number-in-djb-hash-function/13809282#13809282
  Source of the code: http://www.cse.yorku.ca/~oz/hash.html
*/

#define HASH_SIZE 1000000

int hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++) {
        // hash = hash * 33 + c;
        hash = (((hash << 5) + hash) + c) ; /* hash * 33 + c */
    }

    return hash % HASH_SIZE;
}
