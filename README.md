# cpp_practice_projects
1. Smorse: Encodes a message with morse code.
2. Decode: Decodes a morse code message.
3. File calculator: Calculates the size of all files on your computer (excludes node_modules, Library, venv, opt). Two methods of calculating: recursively and using threads.

NOTE: currently I implemented the threading wrong so it is essentially only using a single thread at a time. I will be working to change it to actual multithreading. The folder list should be locked with mutex and each thread should should be running a while loop to try and lock the folder list. If it can lock the folder list, it will take the first folder in the list and run the program to search for more folders and add file sizes. Once it finishes, it will try and lock the folder list again to deposit new folders into the folder list. If a thread locks the folder list and the folder list is empty, the thread exits.
