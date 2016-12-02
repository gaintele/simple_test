#! /usr/bin/python
#coding:utf-8
import sys

def main(argv):
    if len(argv) < 2:
        print "less of args"
        exit(1)

    filename = argv[1]
    fp = open(filename, "r")
    content = fp.readlines()
    for line in content:
        print line.strip()

if __name__ == '__main__':
    main(sys.argv)
