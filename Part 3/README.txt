This part introduces the concept of virtual memory and paging technique.
Our launch paging technique defaults to loading two pages of the program into RAM when it
is first launched. A page is 4 lines of code. If the program has 4 or less lines of code, then
only one page is loaded. If the program has more than 8 lines of code, then only the first
two pages are loaded. 
When the cpu requests a page, it first seeks it in the frames of RAM; if not present, it 
will load it from the backing store into the RAM. However, if RAM has no more space, we signal a 
page fault and will perform swapping algorithm between the disk and RAM by extracting a random number
that does not belong to the file.