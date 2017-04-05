#!/usr/bin/python

"""comm.py is recreating the POSIX comm command.  It will compare two
sorted files line by line, unless given the -u command which will make
comm work even without sorting.  Other parameters supported(same rule
as in POSIX): -1 -2 -3
 Written by Christopher Bachelor

"""

import random, sys
from optparse import OptionParser

class comm:
    try:
        def __init__(self, filename1, filename2, commands):
            if filename1 == '-':     
                file2 = open(filename2, 'r')
                file1 = sys.stdin
            elif filename2 == '-':
                file1 = open(filename1, 'r')
                file2 = sys.stdin
            elif filename1 == '-' and filename2 == '-':
                print("Error: cannot have both stdin inputs")
                exit()
            else:
                file1 = open(filename1, 'r')
                file2 = open(filename2, 'r')
            self.list1 = file1.readlines()
            self.list2 = file2.readlines()
            self.f1 = commands[0]
            self.f2 = commands[1]
            self.f3 = commands[2]
            file1.close()
            file2.close()
    except:
        parser.error("Input contained invalid file")

        
    def uCompare(self):
        count1 = 0
        count2 = 0
        in3 = 0
        in2 = 0
        i = k = j = l = 0
        
        for i in range(len(self.list1)):
            for j in range(len(self.list2)):
                if self.list1[i] == self.list2[j] and in3 == 0:
                    for num in range(0,i+1):
                        if(self.list1[i] == self.list1[num]):
                            count1 = count1 + 1
                    for num2 in range(0,len(self.list2)):
                        if(self.list2[j] == self.list2[num2]):
                            count2 = count2 + 1
                    if count1 == count2:
                        self.linePrint(self.list1[i], 3)
                        in3 = 1
                    elif count1 < count2:
                        self.linePrint(self.list1[i], 3)
                        in3 = 1
                    count1 = 0
                    count2 = 0
            if in3 == 0:
                self.linePrint(self.list1[i], 1)
            in3 = 0

        for k in range(len(self.list2)):
            for l in range(len(self.list1)):
                if self.list2[k] == self.list1[l] and in2 == 0:
                    in3 = 1
                    for num3 in range(0,k+1):
                        if(self.list2[k] == self.list2[num3]):
                            count2 = count2 + 1
                    for num4 in range(0, len(self.list1)):
                        if(self.list1[l] == self.list1[num4]):
                            count1 = count1 + 1
                    if count2 > count1:
                        self.linePrint(self.list2[k], 2)
                        in2 = 1
                        in3 = 0
                    count1 = 0
                    count2 = 0
            if in2 == 0 and in3 == 0:
                self.linePrint(self.list2[k], 2)
            in2 = 0
            in3 = 0
            
    def compare(self):
        m = 0
        n = 0
        while m < len(self.list1) and n < len(self.list2):
            if self.list1[m] < self.list2[n]:
                self.linePrint(self.list1[m], 1)
                m = m+1
            elif self.list1[m] > self.list2[n]:
                self.linePrint(self.list2[n], 2)
                n = n+1
            elif self.list1[m] == self.list2[n]:
                self.linePrint(self.list1[m], 3)
                n = n+1
                m = m+1
        if m < len(self.list1):
            for a in range(m, len(self.list1)):
                self.linePrint(self.list1[a],1)
        if n < len(self.list2):
            for b in range(n, len(self.list2)):
                self.linePrint(self.list2[b], 2)        
        

    def linePrint(self, stringName, column):
        f1 = self.f1
        f2 = self.f2
        f3 = self.f3
        if stringName != '\n':
            if f1 == True and f2 == False and f3 == False:
                if column == 2:
                    sys.stdout.write(stringName)
                if column == 3:
                    sys.stdout.write("\t")
                    sys.stdout.write(stringName)
                
            elif f1 == False and f2 == True and f3 == False:
                if column == 1:
                    sys.stdout.write(stringName)
                if column == 3:
                    sys.stdout.write("\t")
                    sys.stdout.write(stringName)
            elif f1 == False and f2 == False and f3 == True:
                if column == 1:
                    sys.stdout.write(stringName)
                if column == 2:
                    sys.stdout.write("\t")
                    sys.stdout.write(stringName)
            elif f1 == True and f2 == True and f3 == False:
                if column == 3:
                    sys.stdout.write(stringName)
            elif f1 == True and f2 == False and f3 == True:
                if column == 2:
                    sys.stdout.write(stringName)
            elif f1 == False and f2 == True and f3 == True:
                if column == 1:
                    sys.stdout.write(stringName)
            elif f1 == True and f2 == True and f3 == True:    
                pass
            else:
                if column == 1:
                    sys.stdout.write(stringName)
                if column == 2:
                    sys.stdout.write("\t")
                    sys.stdout.write(stringName)
                if column == 3:
                    sys.stdout.write("\t\t")
                    sys.stdout.write(stringName)
                
def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

Output comparison between FILE1 and FILE2 line by line."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="flag1", default=False,
                      help="Suppress output for FILE1")
    parser.add_option("-2",
                      action="store_true", dest="flag2", default=False,
                      help="Suppress output for FILE2")
    parser.add_option("-u",
                      action="store_true", dest="flagu", default=False,
                      help="Suppress output for FILE2")
    parser.add_option("-3",
                      action="store_true", dest="flag3", default=False,
                      help="Suppress output for lines duplicated in FILE1 and FILE2")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        flag1 = bool(options.flag1)
        flag2 = bool(options.flag2)
        flag3 = bool(options.flag3)
        flagu = bool(options.flagu)
    except:
        parser.error("invalid options: {0}".
                     format(options.flag1))
    if len(args) != 2:
        parser.error("Wrong number of File inputs")
    input_file1 = args[0]
    input_file2 = args[1]
    command_list = [flag1, flag2, flag3]
    try:
        commClass = comm(input_file1, input_file2, command_list)
        if flagu == True:
            commClass.uCompare()
        else:
            commClass.compare()
    except IOError as errorVal:
        errno = errorVal.errno
        sterror = errorVal.sterror
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
