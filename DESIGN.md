# Basic Key Value Data Store

### API of Key Value Data Store

1. SET key, value
   
   Store the key, value pair in the data store.

2. GET key
   
   Returns key, value pair if SET (key, value) was called before calling GET.


3. Delete or TTL

   Not available.


### **Implementation Sketch**

The Basic KV Data Store is composed of three layers of storage.

#### **Volatile Storage**

- Only good for performance
- Can not survive application crash or restarts.

#### **Persistent Storage**

- Can survive application crash and restarts.
- Can not survive kernel crash.
- Can not survive hard disk failure

#### **Replicated Storage**

- Can survive mutliple type of node failures.

**The following modules implements the three layers.**


#### **KV Store  [Volatile Storage]**

   1. Maintain in-memory K, V dictionary data structure. This can be whatever standard library is providing no fancy stuff.

   2. GET : Served from the In-memory dictionary.

   3. SET : Calls append(log_entry) in WAL.
      If success Updates In-memory dictionary.
            Else returns error (Indicates - WAL is failing)


#### **WAL (Write Ahead Log) [Persistent Storage]**

1.  append(log_entry) : Persists log_entry to the hard disk

    Technical comments : 
      - For Each log comment calculate checksum and make it part of the log_entry.
      - Linux write syscall can return partial writes.
      - Sucessful return of write syscall do not guarantee that data is actually on the disk. Kernel buffers the	data in its memory and transparently makes the data available from in-memory to other processes.
      - To handle the above, Kernel can be forced to write the data to hard disk using fsync systemcall.
      - fsync is slow because it actually writes to disk.
      - fsync is triggered periodically to force write to disk.
      - There is a potential data loss here,
        where Kernel can crash before fsync get called.
      - Application can crash without data loss as kernel eventually writes to the file. [NEED TO CONFIRM]


2.    replay(logIndex):
      - KV Store can call this to replay all logs and reach latest state.
      - Discard - log_entries with bad checksum (NEED TO THINK ABOUT ERROR SCENARIOS)
      
#### **RAFT [Replicated Storage]**

Implementation Guide - Raft Extended Paper - In Search of an Understandable Consensus Algorithm
(Extended Version) **especially Figure 2. which presents a condensed psuedo-code for Raft algorithm.**


All networking will be implemented using ZeroMQ [https://zguide.zeromq.org/]


**Resources**

MIT Distributed System Labs : http://nil.csail.mit.edu/6.824/2022/labs/lab-raft.html
- Assignment for building Distributed KV using Raft in Go

Etcd WAL Implementation : https://github.com/etcd-io/etcd/tree/main/server/storage/wal

Replicated Log Pattern : https://martinfowler.com/articles/patterns-of-distributed-systems/replicated-log.html

Patterns of Distributed Systems : https://martinfowler.com/articles/patterns-of-distributed-systems/




    
