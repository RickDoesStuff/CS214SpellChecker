SpellChecker
============

For Rutgers CS214 Systems Programming Project 2

## Names and RUIDs

Ron Cohen (rc1456) and Enrico Aquino (eja97)

## User Manuel

Type or copy and paste the following commands into the terminal after downloading

```bash
tar -xf your-p2.tar 
cd P2 
make
```
This how you run the program
```
./spchk dict my_file my_dir
```

## Testing Plan

For our testing, we implemented our own dictionary with words that we found from `dict.txt`, the larger dictionary provided to us. We gave ourselves a buffer size of 128, once it reaches it's max size, it checks if it reached the end of the file and will expand if it's not at the end. From there we added words to `small_dict.txt` and changed the `paragraph.txt` to better suit our test cases. We started off testing our programs ability to read the words from `small_dict.txt`, once the words were being properly read, we moved on to the second stage of the program. 

Stage two of the program was to read from `paragraph.txt`, then compare each word from the file to `small_dict.txt`. After comparing strings, we were then tasked with counting the number line (row) and the location of the first char (column) of the word. We made the `paragraph.txt` have several lines and each line hosted several sentences, the program counted each line and char it found. We made sure spacing was erratic to catch any bugs like counting whitespace or new line as a word or if it missed a word. This also intentionally tested how the counting works, to see if it was marking the right location. 

The final stage of our project was recusive search through the directory. We made `test` directory to see if the program would seach for files. After this, we set the file path to the spell checker program to see if it can read the file from the information it was given. Once testing was done, we added an additional file to see if our program was searching through the directory. Finaly, we moved onto recurisve search through dictionaries. We made the variable `fullPath` to keep track of the whole path. We used the variable `entry` to keep track of the current file/directory and we concatenate to `filePath`. If entry is a `.txt` file, it will be returned. Otherwise, it will continue to search the current directory for a `.txt` file or another directory to search through. We tested this by making several directories and filling them with files that have differen't extentions. 

### Design Choice

For our method of storing the dictionary contents, we sorted the contents using quick sort and stored everything in a binary tree. We used quick sort for it's fast sorting capabilities and we used a binary tree for faster searching. 

For our method of counting rows and columns, we incorperated it into the read function that we have, `next_word`. This was done to keep things simple allowing use to store the dictionary and read the file using the same function. When reading the dictionary, we set the values for `row` and `col` as `NULL` when passing it through the function to avoid unnecessary counting.

When making the directory search function, we decided to have the file path put in a char array with a size of 4096. This was done to ensure we do not run out of space in case of extremely long directory names. 

### Test Cases

A test case we have is we have a text file containing all correct words and sentences we made. This includes many types of puncutation to ensure that the puncuation trimming works.

Another test case we have it a file for hyphenated words, this allows us to ensure all parts of the hyphenated words are correct. We also make sure inside the hyphenated words nothing gets trimmed off. 

We also have a few text files inside of subdirectories that we search, these files contain valid sentences, blank lines, wrong words, and numbers inside of words. This allows our code to test even the most messed up files.