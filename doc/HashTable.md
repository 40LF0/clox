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

## 3. Hash Function

## 4. Hash Table

## 5. String Interning