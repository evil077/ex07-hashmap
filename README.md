## Exercise: Hash Map (25 Points)

The purpose of this assignment is for your to implement another Abstract Data Type(ADT), the Hash Map.

The first thing you will need to do is fork and clone this assignment
from GitHub. Follow the instructions
[here](https://github.com/vcc-csv15-fall2018/Course-Information/wiki)
to get started.

Be sure that you fork the project first and use the URL from
the forked project when you clone it in CLion.

### Problem Description

The problem for this assignment to complete the implementation of a hash map.

Also, if templates are confusing see (this)[http://www.cplusplus.com/doc/oldtutorial/templates/] article that hopefully
explains what's going on better.

To start with, I've provided you with most of the code for a hash map. It's in `include/hash_map.h`. The work
you do for this assignment is to replace all the comments that say `// Put your code here` with you code that
implements the methods as described below.

In this assignment, I've attempted to copy the STL (Standard Template Library) as exact as I possibly could. If anything
is unclear, or if you want to see some example code, take a look at the [`std::unordered_map`](http://www.cplusplus.com/reference/unordered_map/unordered_map/) documentation. I've 
used the descriptions from there in the descriptions of the methods you need to implement from there.

Your job, should you choose to accept it, is to implement the code between the `{}` in all the functions
above that are not implemented, and have the comment `// Put your code here`. You can add more data members besides `_buckets`, `_size`, and `_capacity`. But
that should not be necessary. Also, feel free to change any of those names to something that makes more sense 
to you, but you probably don't want to change the type.

The following table describes what each function that you need to implement should do:

| Function name | Returns        | Input Parameters    | Description |
|---------------|----------------|---------------------|-------------------|
| empty         | bool           | none                | Returns a bool value indicating whether the unordered_map container is empty, i.e. whether its size is 0. |
| size          | size_t         | none                | Returns the number of elements in the unordered_map container.|
| bucket_count  | size_t         | none                | Returns the number of buckets in the unordered_map container.<br/> A bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key. |
| clear         | none           | none                | All the elements in the unordered_map container are dropped: their destructors are called, and they are removed from the container, leaving it with a size of 0. |
| insert        | Iterator       | KeyType &key, const ValueType &value | The function inserts a new element with that key and returns a reference to its mapped value. Notice that this always increases the container size by one, even if no mapped value is assigned to the element (the element is constructed using its default constructor). |
| erase         | Iterator<br/>_Return an iterator pointing to the position immediately following the last of the elements erased._ | iterator where      |Removes from the unordered_map container either a single element or a range of elements ([first,last)). |
| erase         | Iterator<br/>_Return an iterator pointing to the position immediately following the last of the elements erased._ | iterator first, iterator last | Removes from the unordered_map container either a single element or a range of elements ([first,last)). |
| erase         | Iterator<br/>_Returns the number of elements erased, which in unordered_map containers (that have unique keys), this is 1 if an element with a key value of k existed (and thus was subsequently erased), and zero otherwise._ | const KeyType &key  | Removes from the unordered_map container either a single element or a range of elements ([first,last)).
| find          | Iterator<br>_An iterator to the element, if the specified key value is found, or HashMap::end if the specified key is not found in the container._       | const KeyType &key  | Searches the container for an element with k as key and returns an iterator to it if found, otherwise it returns an iterator to unordered_map::end (the element past the end of the container). |
| swap          | none           | HashMap &other   | Exchanges the content of the container by the content of ump, which is another unordered_map object containing elements of the same type. Sizes may differ. |

### Writing the code for this Project

Writing the code for this project is very simple. Simply create the one file below
`main.cc` in CLion
and then copy the content into the files.

#### Header file

In this project, the header file is provided for you. Do all your work in `include/hash_map.h`

#### Implementation file

In CLion in the project explorer, right-click the `src` directory
and chose `New => C++ Source File`.

Under **Name** fill in
main, for the code you write for testing and completing the assignment.
CLion will add the extension, but by default
adds the `.cpp` extension. All projects in this class will
use the `.cc` extension. Select `.cc` in the **Type** drop-down
and press **OK**. You should now see the file `main.cc` in
the project explorer in the `src` directory.

Properly set up the namespaces and implement the function described above in this file.

### Running the code for this project

Running this code should be straightforward. In the drop-down
menu in the upper right-hand corner you should see a **Run
Configuration** called `HashMap | Debug`. Make sure this
configuration is selected and press the play button next to it.
In the **Run** view below the code you should see the output
of running the program. It should look something like this:

```bash
/Users/username/githubusername/ex07-hashmap/bin/
ccc => 13
bbc => 2
bbb => 48
aaa => 1
abb => 42
42

Process finished with exit code 0
```
Success! Now you can move on to testing your code. Remember that your output might be
different, but should look similar to this.

### Testing the code for this project

Testing the code for this project is similar to running your code
as outlined above. In the drop-down menu in the upper right-hand
corner select the configuration `HashMap_Gtest` and press the
play button next to it. In the **Run** view below the code you should
see the output of running these tests. It should look something
like this:

```bash
Running main() from gtest_main.cc
[==========] Running 5 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 5 tests from HashMapTest
[ RUN      ] HashMapTest.Construction
[       OK ] HashMapTest.Construction (0 ms)
[ RUN      ] HashMapTest.InsertFind
[       OK ] HashMapTest.InsertFind (0 ms)
[ RUN      ] HashMapTest.Erase
[       OK ] HashMapTest.Erase (0 ms)
[ RUN      ] HashMapTest.Swap
[       OK ] HashMapTest.Swap (0 ms)
[ RUN      ] HashMapTest.Rehash
[       OK ] HashMapTest.Rehash (0 ms)

Your unit test score is 20 out of 20
The assignment is worth a total of 25 where the remaining points
comes from grading related to documentation, algorithms, and other
criteria.

[----------] 5 tests from HashMapTest (1 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 5 tests.

Process finished with exit code 0
```

Remember, red good, green bad. If your tests pass you should see green
text and your code ran fine. You should also see your score for this
assignment minus code styling points which I will add later.

### Submitting the code for this project

First, right click on the project name, then select `Git -> Commit Directory...`.
Make sure only the files you want to push are selected, `main.cc` and `hash_map.h`.
Then uncheck `Perform code analysis` and `Check TODO`. It's OK to leave them checked,
but committing will take longer. Leave `Run git hooks` checked. Put a message in `Commit Message`
and then press the **Commit** button. If anything goes wrong check the _Version Control_ view
in the lower left corner and select the _Console_ tab.

Finally, right click on the project name,
then select `Git -> Repository -> Push...`. Follow the onscreen directions
and press **OK**. This step will run the tests again, check that everything is OK
and then submit them to the cloud to have the tests run for grading.

If you do not understand these directions, or wish to do them on the command
line rather than in CLion, then read these [directions](https://github.com/vcc-csv15-fall2018/Course-Information/wiki/How-to-Turn-In-Every-Project).