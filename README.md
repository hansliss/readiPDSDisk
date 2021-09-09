# readiPDSDisk
Read an iNTEL iPDS disk image (655360 bytes), list directory info and extract all files

This is incredibly crude, ugly and uncommented. But it seems to do its job as far as I can tell. Image file is read on stdin and files are
created in current directory.

There is some reference info for the ISIS-II disk format (http://www.nj7p.info/Computers/Old%20Software/Software/ISIS-II_Disk_Formats.txt)
which I started out with, but as far as I can tell, the iPDS images I have do not have the link blocks described on that page. I simply
used the starting (s,h) to find the start address of the file and copied n bytes from there, and the result looks correct to me, for the
files I could verify. However, I can *not* verify this beyond checking the text files I had, and checking that the binaries "looked" similar.

If you have the means to experiment further and find something to improve or correct, by all means do so, and send me a pull request!
