These demos show the differences between copying a file using `mmap()` and `read/write()`.

You should take into consideration testing the copying process:
  - after dropping caches;
  - on local storage;
  - on shared storage (e.g., NFS).

Copy file using:
   - `mmap` (map both files in memory and use `memcpy`)
   - `read/write`

Usage:
```
student@vm:~/copy$ make
student@vm:~/copy$ bash create-file.sh a.rand 1GB # it will take a while
student@vm:~/copy$ sync; echo 1 | sudo tee /proc/sys/vm/drop_caches
student@vm:~/copy$ /usr/bin/time ./cp_mmap a.rand b.rand
student@vm:~/copy$ sync; echo 1 | sudo tee /proc/sys/vm/drop_caches
student@vm:~/copy$ /usr/bin/time ./cp_rdwr a.rand b.rand
```


