# CLox Hash Table

CLox VM implements a hash table to efficiently search for and add variables using their variable names. The hash table
is also used to retrieve and add class instance fields, providing fast access and manipulation of these data structures.

A hash table associates a set of keys with a set of values. Each key/value pair is an entry in the hash table. The
primary advantage of a hash table is its ability to quickly locate a value given its key, which is achieved through the
use of a hash function. Additionally, hash tables can dynamically add new key/value pairs and delete entries by their
key, making them flexible and efficient for various data management tasks.

## 1. Bucket Array

The core of a hash table is the bucket array. This array is a collection of "buckets," where each bucket can hold
multiple entries. The hash function determines the index of the bucket for a given key. Ideally, each bucket contains a
unique set of keys, but due to the finite size of the bucket array and the infinite number of possible keys,
collisions (where multiple keys map to the same bucket) can occur. The bucket array structure helps in organizing and
managing these entries efficiently.

### 1.1 Load Factor

The load factor is a measure of how full the hash table is. It is defined as the ratio of the number of entries to the
number of buckets in the array. A high load factor indicates that the hash table is becoming full, which can lead to
more collisions and decreased performance. To maintain efficient operations, the hash table typically resizes the bucket
array when the load factor exceeds a certain threshold. This resizing involves creating a new, larger bucket array and
rehashing all existing entries to distribute them evenly across the new buckets. Managing the load factor ensures that
the hash table remains efficient as it grows.

## 2. Collision Resolution

Collision resolution is a crucial aspect of hash table implementation. When two or more keys hash to the same bucket
index, the hash table must handle these collisions to maintain efficient data access. Common collision resolution
strategies include chaining, where each bucket contains a linked list of entries, and open addressing, where the hash
table searches for the next available bucket. CLox VM's hash table implementation uses linear probing to handle these
collisions.

### 2.1 Linear Probing

In linear probing, if a collision occurs, the hash table checks the next bucket in the array and continues
checking subsequent buckets until it finds an empty one. This approach ensures that the hash table remains efficient
even in the presence of collisions, as it provides a simple and effective way to resolve conflicts without needing
additional data structures like linked lists.

## 3. Hash Function

The hash function is a critical component of the hash table. It takes a key and computes an index in the bucket array
where the corresponding value should be stored. A good hash function generates a fixed-size integer hash code that
varies based on every bit of the original data. The hash function used in CLox VM meets three important criteria:

1. Deterministic: The same input will always produce the same hash code.
2. Uniform: It distributes keys evenly across the bucket array, minimizing collisions.
3. Fast: It computes hash codes quickly to ensure efficient access times.

CLox uses the FNV-1a hash function, which is known for its simplicity, speed, and good distribution properties. FNV-1a
processes each byte of the input and combines them into a single hash code, making it a suitable choice for the
performance needs of CLox VM.

### 3.1 FNV-1a Hash Function

The FNV-1a hash function is a variant of the Fowler-Noll-Vo hash function, which is designed to be fast and effective
for hashing strings and other data. It works by initializing a hash value to a large prime number(typically 2166136261 for 32-bit) and then iteratively
processing each byte of the input data. For each byte, the hash value is XORed with the byte, then multiplied by a prime
number (typically 16777619 for 32-bit hashes). This combination of XOR and multiplication provides a good mix of bits,
ensuring that small changes in the input produce significantly different hash values.

## 4. Hash Table

In CLox, the hash table module is defined as a struct Table, which consists of the following components:

- count: The number of entries currently in the hash table.
- capacity: The capacity of the hash table, representing the number of buckets in the bucket array.
- entries: An array of Entry structs, where each Entry holds a key-value pair.

CLox's hash table implementation only increases in size and does not shrink. When the load factor exceeds 0.75, the hash
table resizes by increasing the capacity and reallocating memory for the entries array. This process involves creating a
new, larger array and rehashing all existing entries to ensure even distribution across the new buckets.

When deleting an entry, CLox uses a tombstone to mark the deleted entry. This approach maintains the integrity of the
linear probing sequence, ensuring that the hash table can continue to probe for other entries that may have collided and
been placed further along in the array.

## 5. String Interning