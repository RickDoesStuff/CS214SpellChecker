SpellChecker
============

For Rutgers CS214 Systems Programming Project 1

## Names and RUIDs

Ron Cohen (rc1456) and Enrico Aquino (eja97)

## User Manuel

Type or copy and paste the following commands into the terminal after downloading

```
tar -xf p2.tar 
cd P2 
make ./spchk
./spchk dict my_file my_directory
```

## Testing Plan

For our testing, we implemented our own dictionary with words that we found from `dict.txt`, the larger dictionary provided to us. We gave ourselves a buffer size of 128, once it reaches it's max size, it checks if it reached the end of the file and will expand if it's not at the end. From there we added words to `small_dict.txt` and changed the `paragraph.txt` to better suit our test cases. We started off testing our programs ability to read the words from `small_dict.txt`, once the words were being properly read, we moved on to the second stage of the program. 
Stage two of the program was to make it read from `paragraph.txt`, then we have to compare the string from the dictionary and the string from the paragraph. After comparing strings, we were then tasked with counting the number line (row) and the location of the char (column) on the line. We made the `paragraph.txt` have several lines and each line hosted several sentences, the program counted each line and char it found. 

