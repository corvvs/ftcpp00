./test > my.log
diff -u <(cut -d ' ' -f 2 my.log ) <(cut -d ' ' -f 2 19920104_091532.log)
