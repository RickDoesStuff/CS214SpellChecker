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
The final stage of our project was recusive search through the directory. We made `test` directory to see if the program would seach for files through it. After this, we sent the file path to the spell checker programe to see if it can read the file from the information it was given. Once testing for that was done, we added an additional file to see if our program was actually searching through the directories. Finaly, we moved onto recurisve search through dictionaries. We made the variable `fullPath` to keep track of the whole path. We used the variable `entry` to keep track of the file/directory and we concatenate to `filePath`. If entry is a `.txt` file, it will be returned. Otherwise, it will continue to search the current directory for a `.txt` file or another directory to search through.

### Design Choice

For our method of storing the dictionary contents, we sorted the contents using quick sort and stored everything in a binary tree. We used quick sort for it's fast sorting capabilities and we used a binary tree for faster searching. 

For our method of counting rows and columns, we incorperated it into the read function that we have, `next_word`. This was done to keep things simple allowing use to store the dictionary and read the file using the same function. When reading the dictionary, we just set the values as `NULL` when passing it through the function to avoid unnecessary counting.

